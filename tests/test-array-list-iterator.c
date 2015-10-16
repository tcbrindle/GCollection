/* test-array-list-iterator.c
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

#include <gcollection/gcollection.h>

#define NUM_OBJECTS (1000 * 1000)

static void
test_array_list_iterator_basic (void)
{
  GPtrArray *array = g_ptr_array_sized_new (NUM_OBJECTS);
  g_autoptr (GcIterator) iter = NULL;
  int i = 0;


  for (i = 0; i < NUM_OBJECTS; i++)
    {
      g_ptr_array_add (array, GINT_TO_POINTER (i));
    }

  g_assert_cmpuint (array->len, ==, NUM_OBJECTS);

  iter = gc_array_list_iterator_new_for_ptr_array (array);
  i = 0;

  while (gc_iterator_next (iter)) {
    g_assert_cmpint (i++, ==, GPOINTER_TO_INT (gc_iterator_get (iter)));
  }
}

int
main(int argc, char **argv)
{
  g_test_init(&argc, &argv, NULL);
  g_test_add_func("/GCollection/ArrayListIterator/Basic",
                  test_array_list_iterator_basic);
  return g_test_run();
}

