/* gc-array-list.h
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

#ifndef GC_ARRAY_LIST_H
#define GC_ARRAY_LIST_H

#include <glib-object.h>

G_BEGIN_DECLS

#define GC_TYPE_ARRAY_LIST (gc_array_list_get_type())

G_DECLARE_FINAL_TYPE (GcArrayList, gc_array_list, GC, ARRAY_LIST, GObject)

GcArrayList     *gc_array_list_new                    (void);

GcArrayList     *gc_array_list_new_with_element_type  (GType element_type);

GcArrayList     *gc_array_list_new_from_ptr_array     (GPtrArray  *ptr_array);

GcArrayList     *gc_array_list_new_full               (GType          element_type,
                                                       GBoxedCopyFunc copy_func,
                                                       GDestroyNotify free_func);

GPtrArray       *gc_array_list_get_ptr_array          (GcArrayList *array);

gpointer         gc_array_list_get                    (GcArrayList *array,
                                                       guint        index);

guint            gc_array_list_get_size               (GcArrayList *array);

gboolean         gc_array_list_get_is_empty           (GcArrayList *array);

void             gc_array_list_append                 (GcArrayList *array,
                                                       gpointer     value);

G_END_DECLS

#endif /* GC_ARRAY_LIST_H */
