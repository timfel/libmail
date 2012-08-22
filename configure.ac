AC_CONFIG_MACRO_DIR([m4])
m4_define([maj_version], [0])
m4_define([min_version], [1])
m4_define([api_current], [1])
m4_define([api_revision], [0])
m4_define([api_compatibility], [1])

AC_PREREQ(2.61)
AC_INIT([libmail], [maj_version.min_version], [https://github.com/timfel/libmail])
AM_INIT_AUTOMAKE

LT_INIT

VERSION_MAJOR=maj_version
VERSION_MINOR=min_version
VERSION="$VERSION_MAJOR.$VERSION_MINOR"
test -d .git && VERSION="$VERSION-dev-"`date +'%Y%m%d'`
AC_DEFINE_UNQUOTED(LIBMAIL_VERSION, "$VERSION", [define this to the version of libmail])
AC_SUBST(VERSION)

AC_PROG_CC
AC_PROG_CPP

AC_ARG_ENABLE([debug],
	AC_HELP_STRING([--enable-debug], [setup flags for debugging (default=no)]),
	[CFLAGS="$CFLAGS -ggdb -O0"],
	[CFLAGS="$CFLAGS -O2"; LDFLAGS="$LDFLAGS -s"])

AC_ARG_WITH([libetpan],
	AC_HELP_STRING([--with-libetpan=DIR], [prefix directory for libetpan]),
	[CPPFLAGS="$CPPFLAGS -I$withval/include/"; LDFLAGS="$LDFLAGS -L$withval/lib/"],
	[])

AC_CHECK_LIB([etpan], [libetpan_get_version_major], [], [AC_MSG_ERROR([libetpan is required])])
AC_CHECK_HEADER([libetpan.h], [], [AC_MSG_ERROR([libetpan headers are required])])

AC_CONFIG_FILES([Makefile])
AC_CONFIG_HEADERS([config.h])
AC_OUTPUT
