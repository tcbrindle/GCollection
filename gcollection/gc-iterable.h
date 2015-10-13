/* gc-iterable.h
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

#ifndef GC_ITERABLE_H
#define GC_ITERABLE_H

#include "gc-iterator.h"

G_BEGIN_DECLS

#define GC_TYPE_ITERABLE               (gc_iterable_get_type ())
#define GC_ITERABLE_GET_INTERFACE(obj) (G_TYPE_INSTANCE_GET_INTERFACE ((obj), GC_TYPE_ITERABLE, GcIterableInterface))

G_DECLARE_INTERFACE (GcIterable, gc_iterable, GC, ITERABLE, GObject)

struct _GcIterableInterface
{
    GTypeInterface parent;

    GcIterator *(*iterator) (GcIterable *iterable);

    gpointer padding [8];
};

GcIterator 	*gc_iterable_iterator		(GcIterable *iterable);

G_END_DECLS

#endif /* GC_ITERABLE_H */

