/* gc-iterable.c
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

#include "gc-iterable.h"

G_DEFINE_INTERFACE (GcIterable, gc_iterable, G_TYPE_OBJECT)

static void
gc_iterable_default_init (GcIterableInterface *iface)
{
}

/**
 * gc_iterable_iterator:
 * @iterable: A #GcIterable
 *
 * FIXME
 *
 * Returns: (transfer full): A new iterator
 */
GcIterator *
gc_iterable_iterator (GcIterable *self)
{
    return GC_ITERABLE_GET_INTERFACE(self)->iterator(self);
}

