## Process this file with automake to produce Makefile.in

NULL =

lib_LTLIBRARIES = libgcollection.la

libgcollection_la_SOURCES = \
	gc-array-list.c gc-array-list.h \
	gc-iterable.c gc-iterable.h \
	gc-iterator.c gc-iterator.h \
	$(NULL)

libgcollection_la_CPPFLAGS = \
	${GCOLLECTION_CFLAGS} \
	${NULL}

libgcollection_la_CFLAGS =\
	-Wall\
	-g \
	${NULL}

libgcollection_la_LDFLAGS = \
	-version-info $(GCOLLECTION_LT_VERSION) \
	$(NULL)

libgcollection_la_LIBADD = \
	$(GCOLLECTION_LIBS) \
	${NULL}

include_HEADERS = \
	gc-array-list.h \
	gc-iterable.h \
	gc-iterator.h \
	${NULL}

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = gcollection.pc

-include $(INTROSPECTION_MAKEFILE)
INTROSPECTION_GIRS =
INTROSPECTION_SCANNER_ARGS = \
    --add-include-path=$(srcdir) \
    --symbol-prefix=gc \
    --warn-all -v
INTROSPECTION_COMPILER_ARGS = --includedir=$(srcdir)

if HAVE_INTROSPECTION
introspection_sources = $(libgcollection_la_SOURCES)

GCollection-1.0.gir: libgcollection.la
GCollection_1_0_gir_INCLUDES = GObject-2.0
GCollection_1_0_gir_CFLAGS = $(INCLUDES)
GCollection_1_0_gir_LIBS = libgcollection.la
GCollection_1_0_gir_FILES = $(introspection_sources)
GCollection_1_0_gir_SCANNERFLAGS = --c-include "gcollection.h"
INTROSPECTION_GIRS += GCollection-1.0.gir

girdir = $(datadir)/gir-1.0
gir_DATA = $(INTROSPECTION_GIRS)

typelibdir = $(libdir)/girepository-1.0
typelib_DATA = $(INTROSPECTION_GIRS:.gir=.typelib)

CLEANFILES = $(gir_DATA) $(typelib_DATA)


if ENABLE_VAPIGEN
include $(VAPIGEN_MAKEFILE)

gcollection.vapi: GCollection-1.0.gir gcollection.deps

VAPIGEN_VAPIS = \
	gcollection.vapi \
	${NULL}

gcollection_vapi_DEPS = glib-2.0 gobject-2.0
gcollection_vapi_METADATADIRS = $(srcdir)
gcollection_vapi_FILES = GCollection-1.0.gir

VAPI_DEPS = $(VAPIGEN_VAPIS:.vapi=.deps)

gcollection.deps: Makefile.am
	$(AM_V_GEN) echo $(gcollection_vapi_DEPS) | tr ' ' '\n' > $@

vapidir = $(datadir)/vala/vapi
vapi_DATA = \
	$(VAPIGEN_VAPIS) \
	$(VAPI_DEPS) \
	${NULL}

CLEANFILES += \
	$(VAPIGEN_VAPIS) \
	$(VAPI_DEPS) \
	${NULL}

endif # ENABLE_VAPIGEN
endif # HAVE_INTROSPECTION

EXTRA_DIST = \
	gcollection.pc.in \
	${NULL}

-include $(top_srcdir)/git.mk

