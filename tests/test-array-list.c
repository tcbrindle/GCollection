
#include <gcollection/gcollection.h>

#define NUM_OBJECTS 5

#define TEST_TYPE_OBJECT (test_object_get_type())

G_DECLARE_FINAL_TYPE (TestObject, test_object, TEST, OBJECT, GObject)

struct _TestObject
{
  GObject parent;

  int index;
};

G_DEFINE_TYPE (TestObject, test_object, G_TYPE_OBJECT)

static TestObject *
test_object_new (int index)
{
  TestObject *self = g_object_new (TEST_TYPE_OBJECT, NULL);
  self->index = index;
  return self;
}

static void
test_object_class_init (TestObjectClass *klass)
{
}

static void
test_object_init (TestObject *self)
{
}


static void
test_array_list_construct (void)
{
  GcArrayList *array_list = gc_array_list_new ();
  g_assert_nonnull (array_list);
  g_assert_true (gc_array_list_get_is_empty (array_list));
  g_object_unref (array_list);

  array_list = gc_array_list_new_with_element_type (TEST_TYPE_OBJECT);
  g_assert_nonnull (array_list);
  g_assert_true (gc_array_list_get_is_empty (array_list));
  g_object_unref (array_list);

  g_autoptr(GPtrArray) ptr_array = g_ptr_array_new_with_free_func (g_object_unref);
  array_list = gc_array_list_new_from_ptr_array (ptr_array);
  g_assert_nonnull (array_list);
  g_assert_true (gc_array_list_get_is_empty (array_list));
  g_object_unref (array_list);

  array_list = gc_array_list_new_full (TEST_TYPE_OBJECT,
                                       g_object_unref);
  g_assert_nonnull (array_list);
  g_assert_true (gc_array_list_get_is_empty (array_list));
  g_object_unref (array_list);
}

static void
test_array_list_append (void)
{
  g_autoptr(GcArrayList) array_list = gc_array_list_new ();
  int i;

  for (i = 0; i < NUM_OBJECTS; i++)
    {
      gc_array_list_append (array_list, test_object_new (i));
    }
  g_assert_false (gc_array_list_get_is_empty (array_list));
  g_assert_cmpuint (gc_array_list_get_size (array_list), ==, NUM_OBJECTS);

  i = 0;
  GC_FOREACH (TestObject *t, array_list, {
      g_assert_cmpint (t->index, ==, i++);
  });
}

static void
test_array_list_clear (void)
{
  g_autoptr (GcArrayList) array_list = gc_array_list_new();
  gc_array_list_append (array_list, test_object_new (0));
  g_assert_false (gc_array_list_get_is_empty (array_list));
  gc_array_list_clear (array_list);
  g_assert_true (gc_array_list_get_is_empty (array_list));
}

static void
test_array_list_prepend (void)
{
  int i;
  g_autoptr(GcArrayList) array_list = gc_array_list_new_full (TEST_TYPE_OBJECT,
                                                              g_object_unref);

  for (i = 0; i < NUM_OBJECTS; i++)
    {
      TestObject *test_obj = test_object_new (i);
      gc_array_list_prepend (array_list, test_obj);
    }
  g_assert_cmpuint (gc_array_list_get_size (array_list), ==, NUM_OBJECTS);

  i = NUM_OBJECTS;
  GC_FOREACH (TestObject *t, array_list, {
      g_assert_cmpint (t->index, ==, --i);
  });

}

static void
test_array_list_get (void)
{
  g_autoptr(GcArrayList) array_list = gc_array_list_new_full (TEST_TYPE_OBJECT,
                                                              g_object_unref);

  TestObject *in = test_object_new (-1);

  gc_array_list_append (array_list, in);

  TestObject *out = gc_array_list_get (array_list, 0);

  g_assert (in == out);
}

static void
test_array_list_set (void)
{
  g_autoptr(GcArrayList) array_list = gc_array_list_new_full (TEST_TYPE_OBJECT,
                                                              g_object_unref);
  for (int i = 0; i < NUM_OBJECTS; i++)
    {
      gc_array_list_append (array_list, test_object_new (i));
    }

  TestObject *in = test_object_new (-1);
  gc_array_list_set (array_list, 3, in);

  TestObject *out = gc_array_list_get (array_list, 3);

  g_assert (in == out);
}

static void
test_array_list_insert (void)
{
  g_autoptr(GcArrayList) array_list = gc_array_list_new_full (TEST_TYPE_OBJECT,
                                                              g_object_unref);
  for (int i = 0; i < NUM_OBJECTS; i++)
    {
      gc_array_list_append (array_list, test_object_new (i));
    }


  TestObject *in = test_object_new (-1);
  gc_array_list_insert (array_list, 3, in);

  g_assert_cmpuint (gc_array_list_get_size (array_list), ==, NUM_OBJECTS + 1);

  TestObject *out = gc_array_list_get (array_list, 3);

  g_assert (in == out);
}

int
main(int argc, char **argv)
{
  g_test_init(&argc, &argv, NULL);
  g_test_add_func("/GCollection/ArrayList/Construct", test_array_list_construct);
  g_test_add_func("/GCollection/ArrayList/Append", test_array_list_append);
  g_test_add_func("/GCollection/ArrayList/Clear", test_array_list_clear);
  g_test_add_func("/GCollection/ArrayList/Prepend", test_array_list_prepend);
  g_test_add_func("/GCollection/ArrayList/Get", test_array_list_get);
  g_test_add_func("/GCollection/ArrayList/Set", test_array_list_set);
  g_test_add_func("/GCollection/ArrayList/Insert", test_array_list_insert);

  return g_test_run();
}

