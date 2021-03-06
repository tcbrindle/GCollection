/* gcollection.h
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

#ifndef GCOLLECTION_H
#define GCOLLECTION_H

#include "gc-array-list.h"
#include "gc-array-list-iterator.h"
#include "gc-iterable.h"
#include "gc-iterator.h"

#define GC_FOREACH(_var, _container, _code) { \
    GcIterator *_gcIter = gc_iterable_iterator (GC_ITERABLE (_container)); \
    while (gc_iterator_next (_gcIter)) { \
        _var = gc_iterator_get (_gcIter); \
        _code \
    } \
    g_object_unref (_gcIter); }

#endif /* GCOLLECTION_H */

