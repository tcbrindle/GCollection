
AC_INIT(gcollection, 1.0.0)
m4_ifdef([AM_SILENT_RULES],[AM_SILENT_RULES([yes])])

AC_CONFIG_AUX_DIR(build-aux)
AC_CONFIG_MACRO_DIR(m4)
AM_INIT_AUTOMAKE([-Wno-portability no-dist-gzip dist-xz])
AC_CONFIG_HEADERS([config.h])
AM_MAINTAINER_MODE

AC_PROG_CC
AM_PROG_CC_C_O
AM_PROG_VALAC

# Before making a release, the LT_VERSION string should be modified.
# The string is of the form C:R:A.
# - If interfaces have been changed or added, but binary compatibility has
#   been preserved, change to C+1:0:A+1
# - If binary compatibility has been broken (eg removed or changed interfaces)
#   change to C+1:0:0
# - If the interface is the same as the previous version, change to C:R+1:A

GCOLLECTION_LT_VERSION=0:0:0
AC_SUBST(GCOLLECTION_LT_VERSION)

LT_INIT

GOBJECT_REQUIRED=2.36.0

PKG_CHECK_MODULES(GCOLLECTION,
[
    gobject-2.0 >= $GOBJECT_REQUIRED
])
AC_SUBST(GCOLLECTION_CFLAGS)
AC_SUBST(GCOLLECTION_LIBS)

GTK_DOC_CHECK(1.20, [--flavour no-tmpl])

GOBJECT_INTROSPECTION_CHECK([1.2.9])

VALA_REQUIRED=0.18.0
VAPIGEN_CHECK($VALA_REQUIRED)

#if test "$enable_vala" != "no"; then
#	AC_PATH_PROG([VALAC], [valac], [])
#fi
#AM_CONDITIONAL(HAVE_VALAC, test "x$VALAC" != "x")

AC_PATH_PROG([GTESTER], [gtester])
AC_PATH_PROG([GTESTER_REPORT], [gtester-report])
AM_CONDITIONAL(ENABLE_GLIB_TEST, test "x$enable_glibtest" = "xyes")

AC_OUTPUT([
Makefile
docs/Makefile
docs/version.xml
gcollection/gcollection.pc
gcollection/Makefile
tests/Makefile
])
