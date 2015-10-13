
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
test_array_list (void)
{
  g_autoptr(GcArrayList) array_list = gc_array_list_new ();
  g_assert_nonnull (array_list);

  for (int i = 0; i < NUM_OBJECTS; i++)
    {
      g_autoptr(TestObject) test_obj = test_object_new (i);
      gc_array_list_append (array_list, test_obj);
    }

  g_assert_cmpint (gc_array_list_get_size (array_list), ==, NUM_OBJECTS);


  g_autoptr(GcIterator) iter = gc_iterable_iterator (GC_ITERABLE (array_list));

  while (gc_iterator_next (iter) != 0) {
      TestObject *t = TEST_OBJECT (gc_iterator_get (iter));
      g_print ("%i\n", t->index);
  }
}

int
main(int argc, char **argv)
{
   g_test_init(&argc, &argv, NULL);
   g_test_add_func("/GCollection/ArrayList", test_array_list);
   return g_test_run();
}

