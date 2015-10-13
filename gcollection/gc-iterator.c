/* gc-iterator.c
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

#include "gc-iterator.h"

G_DEFINE_ABSTRACT_TYPE (GcIterator, gc_iterator, G_TYPE_OBJECT)

static void
gc_iterator_class_init (GcIteratorClass *klass)
{
}

static void
gc_iterator_init (GcIterator *self)
{
}

/**
 * gc_iterator_next:
 * @iterator: A #GcIterator instance
 *
 * Returns: %TRUE if the next call to gc_iterator_get () will succeed
 */
gboolean
gc_iterator_next (GcIterator *self)
{
    return GC_ITERATOR_GET_CLASS (self)->next (self);
}

/**
 * gc_iterator_get:
 * @iterator: A #GcIterator instance
 *
 * Returns: (transfer none): The next value
 */
gpointer
gc_iterator_get (GcIterator *self)
{
    return GC_ITERATOR_GET_CLASS (self)->get (self);
}

