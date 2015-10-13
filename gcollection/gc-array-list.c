/* gc-array-list.c
 *
 * Copyright (C) 2015 Tristan Brindle <t.c.brindle@gmail.com>
 *
 * This file is free software; you can redistribute it and/or modify it
 * under the terms of the GNU Lesser General Public License as
 * published by the Free Software Foundation; either version 3 of the
 * License, or (at your option) any later version.
 *
 * This file is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "gc-array-list.h"

#include "gc-iterable.h"
#include "gc-iterator.h"

struct _GcArrayList
{
  GPtrArray *ptr_array;
  GType element_type;
  GBoxedCopyFunc copy_func;
  GDestroyNotify free_func;
};

static void gc_array_list_iterable_init (GcIterableInterface *iface);
static GcIterator *gc_array_list_iter_new (GcArrayList *array);

G_DEFINE_TYPE_WITH_CODE (GcArrayList, gc_array_list, G_TYPE_OBJECT,
                         G_IMPLEMENT_INTERFACE (GC_TYPE_ITERABLE,
                                                gc_array_list_iterable_init))

enum {
  PROP_0,
  PROP_PTR_ARRAY,
  PROP_ELEMENT_TYPE,
  PROP_COPY_FUNC,
  PROP_FREE_FUNC,
  PROP_SIZE,
  PROP_EMPTY,
  LAST_PROP
};

static GParamSpec *gParamSpecs [LAST_PROP];

/*****************************************************************************
 *
 * Public API
 *
 *****************************************************************************/

/**
 * gc_array_list_new:
 *
 * Returns: (transfer full): A new #GcArrayList
 */
GcArrayList *
gc_array_list_new (void)
{
  return gc_array_list_new_with_element_type (G_TYPE_OBJECT);
}

/**
 * gc_array_list_new_with_element_type:
 * @element_type: A #GObject-derived #GType
 *
 * Creates a new #GcArrayList and sets the element type to @element_type.
 * All elements added to the array must either be derived from or implement
 * @element_type.
 *
 * This means that @element_type must be derived from #GObject. If this is not
 * the case (for example if you are storing a boxed type in an arraylist), use
 * gc_array_list_new_full().
 *
 * Returns: (transfer full): A new #GcArrayList
 */
GcArrayList *
gc_array_list_new_with_element_type (GType element_type)
{
  g_return_val_if_fail (g_type_is_a (element_type, G_TYPE_OBJECT), NULL);

  return gc_array_list_new_full (element_type,
                                 g_object_ref,
                                 g_object_unref);
}

/**
 * gc_array_list_new_from_ptr_array:
 * @ptr_array: A #GPtrArray
 *
 * Returns: (transfer full): A new #GArrayList
 */
GcArrayList *
gc_array_list_new_from_ptr_array (GPtrArray *ptr_array)
{
  return g_object_new (GC_TYPE_ARRAY_LIST,
                       "ptr-array", ptr_array,
                       NULL);
}

/**
 * gc_array_list_new_full:
 * @element_type: #GType of elements to be contained in the new array
 * @copy_func: Function to copy elements into the array
 * @free_func: Function to free elements removed from the array
 */
GcArrayList *
gc_array_list_new_full (GType element_type,
                        GBoxedCopyFunc copy_func,
                        GDestroyNotify free_func)
{
  return g_object_new (GC_TYPE_ARRAY_LIST,
                       "element-type", element_type,
                       "copy-func", copy_func,
                       "free-func", free_func,
                       NULL);
}

/**
 * gc_array_list_get_element_type:
 * @array: A #GcArrayList
 *
 * Returns: The #GType of the elements contained in @array, as set at
 *   array construction
 */
GType
gc_array_list_get_element_type (GcArrayList *self)
{
  g_return_val_if_fail (GC_IS_ARRAY_LIST (self), G_TYPE_INVALID);

  return self->element_type;
}

/**
 * gc_array_list_get_size:
 * @array: A #GcArrayList
 *
 * Returns: The number of elements currently in the array
 */
gsize
gc_array_list_get_size (GcArrayList *self)
{
  g_return_val_if_fail (GC_IS_ARRAY_LIST (self), -1);

  return self->ptr_array->len;
}

/**
 * gc_array_list_get_is_empty:
 * @array: A #GcArrayList
 *
 * Returns: %TRUE if @array is currently empty
 */
gboolean
gc_array_list_get_is_empty (GcArrayList *self)
{
  g_return_val_if_fail (GC_IS_ARRAY_LIST (self), FALSE);

  return (self->ptr_array->len == 0);
}

/**
 * gc_array_list_get:
 * @array: A #GcArrayList
 * @index: A position in the array
 *
 * Returns: The element at position @index in @array
 */
gpointer
gc_array_list_get (GcArrayList *self, gsize index)
{
  g_return_val_if_fail (GC_IS_ARRAY_LIST (self), NULL);
  g_return_val_if_fail (index < 0, NULL);
  g_return_val_if_fail (index >= self->ptr_array->len, NULL);

  return g_ptr_array_index (self->ptr_array, index);
}

/**
 * gc_ptr_array_set
 * @array: A #GcArrayList
 * @index: A position in the array
 * @value: The new value to store in @array
 */
void
gc_array_list_set (GcArrayList *self, gsize index, gpointer value)
{
  gpointer old_element = NULL;
  gpointer new_element = NULL;

  g_return_if_fail (GC_IS_ARRAY_LIST (self));
  g_return_if_fail (index < 0);
  g_return_if_fail (index >= self->ptr_array->len);

  /* We have to be a bit careful here in the case where the old element holds
   * a reference to the new element; we need to ensure we ref the new element
   * before unreffing the old
   */
  new_element = self->copy_func (value);
  old_element = gc_array_list_get (self, index);

  g_ptr_array_index (self->ptr_array, index) = new_element;

  self->free_func (old_element);
}

void
gc_array_list_append (GcArrayList *self, gpointer value)
{
  g_return_if_fail (GC_IS_ARRAY_LIST (self));

  g_ptr_array_add (self->ptr_array, self->copy_func (value));
}

/******************************************************************************
 *
 * Internal functions
 *
 ******************************************************************************/

static GcIterator *
gc_array_list_iterator (GcIterable *iterable)
{
  g_return_val_if_fail (GC_IS_ARRAY_LIST (iterable), NULL);

  return gc_array_list_iter_new ((GcArrayList *) iterable);
}

static void
gc_array_list_constructed (GObject *object)
{
  GcArrayList *self = GC_ARRAY_LIST (object);

  self->ptr_array = g_ptr_array_new_with_free_func (self->free_func);
}

static void
gc_array_list_finalize (GObject *object)
{
    GcArrayList *self = (GcArrayList *)object;

    g_ptr_array_unref (self->ptr_array);

    G_OBJECT_CLASS (gc_array_list_parent_class)->finalize (object);
}

static void
gc_array_list_get_property (GObject    *object,
                            guint       prop_id,
                            GValue     *value,
                            GParamSpec *pspec)
{
    GcArrayList *self = GC_ARRAY_LIST (object);

    switch (prop_id)
      {
      case PROP_PTR_ARRAY:
        g_value_set_boxed (value, self->ptr_array);
        break;

      case PROP_ELEMENT_TYPE:
        g_value_set_gtype (value, self->element_type);
        break;

      case PROP_SIZE:
        g_value_set_ulong (value, self->ptr_array->len);
        break;

      case PROP_EMPTY:
        g_value_set_boolean (value, self->ptr_array->len == 0);
        break;

      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      }
}

static void
gc_array_list_set_property (GObject      *object,
                            guint         prop_id,
                            const GValue *value,
                            GParamSpec   *pspec)
{
    GcArrayList *self = GC_ARRAY_LIST (object);

    switch (prop_id)
      {
      case PROP_PTR_ARRAY:
        g_assert_null (self->ptr_array);
        self->ptr_array = g_value_dup_boxed (value);
        break;

      case PROP_ELEMENT_TYPE:
        self->element_type = g_value_get_gtype (value);
        break;

      case PROP_COPY_FUNC:
        g_assert_null (self->copy_func);
        self->copy_func = g_value_get_pointer (value);
        break;

      case PROP_FREE_FUNC:
        g_assert_null (self->free_func);
        self->free_func = g_value_get_pointer (value);
        break;

      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      }
}

static void
gc_array_list_class_init (GcArrayListClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);

  object_class->constructed = gc_array_list_constructed;
  object_class->finalize = gc_array_list_finalize;
  object_class->get_property = gc_array_list_get_property;
  object_class->set_property = gc_array_list_set_property;

  gParamSpecs[PROP_PTR_ARRAY] =
      g_param_spec_boxed ("ptr-array", "ptr-array",
                          "The underlying GPtrArray of the ArrayList",
                          G_TYPE_PTR_ARRAY,
                          G_PARAM_STATIC_STRINGS |
                          G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY);

  gParamSpecs[PROP_ELEMENT_TYPE] =
      g_param_spec_gtype ("element-type", "element-type",
                          "GType of the contained elements",
                          G_TYPE_NONE,
                          G_PARAM_STATIC_STRINGS |
                          G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY);

  gParamSpecs[PROP_COPY_FUNC] =
      g_param_spec_pointer ("copy-func", "copy-func",
                            "GBoxedCopyFunc used to copy elements into the array",
                            G_PARAM_STATIC_STRINGS |
                            G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY);

  gParamSpecs[PROP_FREE_FUNC] =
      g_param_spec_pointer ("free-func", "free-func",
                            "GDestroyNotify used to free elements removed from the array",
                            G_PARAM_STATIC_STRINGS |
                            G_PARAM_READWRITE | G_PARAM_CONSTRUCT_ONLY);

  gParamSpecs[PROP_SIZE] =
      g_param_spec_ulong ("size", "size",
                          "Number of elements in the array",
                          0, G_MAXSIZE, 0,
                          G_PARAM_STATIC_STRINGS |
                          G_PARAM_READABLE);

  gParamSpecs[PROP_EMPTY] =
      g_param_spec_boolean ("empty", "empty",
                            "Whether the container is empty or not",
                            TRUE,
                            G_PARAM_STATIC_STRINGS |
                            G_PARAM_READABLE);

  g_object_class_install_properties (object_class, LAST_PROP, gParamSpecs);
}

static void
gc_array_list_init (GcArrayList *self)
{
}

static void
gc_array_list_iterable_init (GcIterableInterface *iface)
{
    iface->iterator = gc_array_list_iterator;
}

/******************************************************************************
 *
 * Iterator definition
 *
 ******************************************************************************/

#define GC_TYPE_ARRAY_LIST_ITER (gc_array_list_iter_get_type ())

G_DECLARE_FINAL_TYPE (GcArrayListIter, gc_array_list_iter, GC, ARRAY_LIST_ITER, GcIterator)

struct _GcArrayListIter
{
  GcArrayList *array;
  gsize pos;
};

G_DEFINE_TYPE (GcArrayListIter, gc_array_list_iter, GC_TYPE_ITERATOR)

static GcIterator *
gc_array_list_iter_new (GcArrayList *array)
{
  GcArrayListIter *iter = g_object_new (GC_TYPE_ARRAY_LIST_ITER, NULL);
  iter->array = g_object_ref (array);

  return GC_ITERATOR (iter);
}

static gboolean
gc_array_list_iter_next (GcIterator *iter)
{
  return FALSE;
}

static gpointer
gc_array_list_iter_get (GcIterator *iter)
{
  return NULL;
}

static void
gc_array_list_iter_finalize (GObject *object)
{
  GcArrayListIter *self = GC_ARRAY_LIST_ITER (object);

  g_clear_object (&self->array);

  G_OBJECT_CLASS (gc_array_list_iter_parent_class)->finalize (object);
}

static void
gc_array_list_iter_class_init (GcArrayListIterClass *klass)
{
  GObjectClass *object_class = G_OBJECT_CLASS (klass);
  GcIteratorClass *iter_class = GC_ITERATOR_CLASS (klass);

  object_class->finalize = gc_array_list_iter_finalize;

  iter_class->next = gc_array_list_iter_next;
  iter_class->get = gc_array_list_iter_get;
}

static void
gc_array_list_iter_init (GcArrayListIter *self)
{
}

