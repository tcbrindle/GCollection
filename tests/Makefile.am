
include Makefile.tests

NULL =

noinst_PROGRAMS = \
	test-array-list-iterator \
	test-array-list \
	${NULL}

TEST_PROGS += test-array-list-iterator
test_array_list_iterator_SOURCES = test-array-list-iterator.c
test_array_list_iterator_CFLAGS = -I{top_srcdir} ${GCOLLECTION_CFLAGS}
test_array_list_iterator_LDADD = ${GCOLLECTION_LIBS} ${top_builddir}/gcollection/libgcollection.la


TEST_PROGS += test-array-list
test_array_list_SOURCES = test-array-list.c
test_array_list_CFLAGS = -I{top_srcdir} ${GCOLLECTION_CFLAGS}
test_array_list_LDADD = ${GCOLLECTION_LIBS} ${top_builddir}/gcollection/libgcollection.la


-include $(top_srcdir)/git.mk

