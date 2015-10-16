/* gc-array-list-iterator.h
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

#ifndef GC_ARRAY_LIST_ITERATOR_H
#define GC_ARRAY_LIST_ITERATOR_H

#include "gc-array-list.h"
#include "gc-iterator.h"

G_BEGIN_DECLS

#define GC_TYPE_ARRAY_LIST_ITERATOR (gc_array_list_iterator_get_type())

G_DECLARE_FINAL_TYPE (GcArrayListIterator, gc_array_list_iterator, GC, ARRAY_LIST_ITERATOR, GcIterator)

GcIterator *gc_array_list_iterator_new (GcArrayList *array_list);

GcIterator *gc_array_list_iterator_new_for_ptr_array (GPtrArray *ptr_array);

G_END_DECLS

#endif /* GC_ARRAY_LIST_ITERATOR_H */
