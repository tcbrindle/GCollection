/* gc-iterator.h
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

#ifndef GC_ITERATOR_H
#define GC_ITERATOR_H

#include <glib-object.h>

G_BEGIN_DECLS

#define GC_TYPE_ITERATOR (gc_iterator_get_type())

G_DECLARE_DERIVABLE_TYPE (GcIterator, gc_iterator, GC, ITERATOR, GObject)

struct _GcIteratorClass
{
    GObjectClass parent;

    gboolean (*next) (GcIterator *iterator);

    gpointer (*get)  (GcIterator *iterator);

    gpointer padding [8];
};

gboolean        gc_iterator_next        (GcIterator *iterator);

gpointer        gc_iterator_get         (GcIterator *iterator);

G_END_DECLS

#endif /* GC_ITERATOR_H */
