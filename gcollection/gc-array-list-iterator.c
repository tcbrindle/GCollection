/* gc-array-list-iterator.c
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

#include "gc-array-list-iterator.h"

struct _GcArrayListIterator
{
  GcIterator parent;

  GPtrArray *ptr_array;
  guint pos;
};

G_DEFINE_TYPE (GcArrayListIterator, gc_array_list_iterator, GC_TYPE_ITERATOR)

GcIterator *
gc_array_list_iterator_new (GcArrayList *array_list)
{
  g_return_val_if_fail (GC_IS_ARRAY_LIST (array_list), NULL);

  return gc_array_list_iterator_new_for_ptr_array (
            gc_array_list_get_ptr_array (array_list));
}

GcIterator *
gc_array_list_iterator_new_for_ptr_array (GPtrArray *ptr_array)
{
  GcArrayListIterator *iter = g_object_new (GC_TYPE_ARRAY_LIST_ITERATOR, NULL);
  iter->ptr_array = ptr_array;

  return GC_ITERATOR (iter);
}

static gboolean
gc_array_list_iterator_next (GcIterator *iter)
{
  GcArrayListIterator *self = GC_ARRAY_LIST_ITERATOR (iter);
  return (++self->pos < self->ptr_array->len);
}

static gpointer
gc_array_list_iterator_get (GcIterator *iter)
{
  GcArrayListIterator *self = GC_ARRAY_LIST_ITERATOR (iter);
  return g_ptr_array_index (self->ptr_array, self->pos);
}

static void
gc_array_list_iterator_class_init (GcArrayListIteratorClass *klass)
{
  GcIteratorClass *iter_class = GC_ITERATOR_CLASS (klass);

  iter_class->next = gc_array_list_iterator_next;
  iter_class->get = gc_array_list_iterator_get;
}

static void
gc_array_list_iterator_init (GcArrayListIterator *self)
{
  self->pos = -1;
}

