
m4_define([yaooc_major], [1])
m4_define([yaooc_minor], [3])
m4_define([yaooc_level], [1])
m4_define([yaooc_version],[yaooc_major.yaooc_minor.yaooc_level])


AC_PREREQ([2.50])
AC_INIT([yaooc],[yaooc_version])
AM_INIT_AUTOMAKE([foreign 1.13 subdir-objects -Wall ])
AC_CONFIG_SRCDIR([src/new.c])
AC_PROG_CC
AC_PROG_INSTALL
AM_PROG_AR
AC_CONFIG_MACRO_DIRS([m4])
AC_CHECK_HEADER_STDBOOL
AC_FUNC_MALLOC

CFLAGS="$CFLAGS -fms-extensions -pthread -D_GNU_SOURCE"

# Checks for header files.
AC_CHECK_HEADERS([fcntl.h inttypes.h stddef.h stdint.h stdlib.h string.h unistd.h])
AC_CHECK_FUNCS([memchr memmove memset strchr ])

AC_MSG_CHECKING(for debuggin)
AC_ARG_ENABLE(debug,[ --enable-debug   compile for debugging])
AC_MSG_RESULT([$enable_debug])
if test "x$enable_debug" = "xyes"; then
	CFLAGS="$CFLAGS -g -D__DEBUG__"
fi

AC_MSG_CHECKING(for garbage collection)
AC_ARG_ENABLE(gc,[ --enable-gc   compile using garbage collection])
AC_MSG_RESULT([$enable_gc])
if test "x$enable_gc" = "xyes"; then
  AC_CHECK_HEADER(gc/gc.h)
  AC_CHECK_LIB(gc,GC_malloc)
	CFLAGS="$CFLAGS -D__YAOOC_USE_GC__"
fi

AC_SUBST(YAOOC_MAJOR_VERSION,yaooc_major)
AC_SUBST(YAOOC_MINOR_VERSION,yaooc_minor)
AC_SUBST(YAOOC_PATCH_LEVEL,yaooc_level)

AC_MSG_CHECKING(to use tre)
AC_ARG_WITH(tre,[   --with-tre        use tre regular expression (yes to use tre, no to use system (gnu) re)])
if test "x$with_tre" = "xyes"; then
	AC_CHECK_HEADER(tre/tre.h)
	AC_CHECK_LIB(tre,tre_regcomp)
	if test "x$ac_cv_lib_tre_tre_regcomp" = "xyes"; then
		CFLAGS="$CFLAGS -D__YAOOC_USE_TRE__"
	else
		AC_MSG_ERROR(tre library not found. Modify CFLAGS and LDFLAGS then rerun configure. Or specify --without-tre)
	fi
else
	AC_CHECK_LIB(c,regcomp)
	if test "$ac_cv_lib_c_regcomp" = "xyes"; then
		AC_MSG_ERROR(suitable regular expression library not found)
	fi
fi

AC_CONFIG_FILES([yaooc-config Makefile])

LT_INIT

AC_OUTPUT

chmod +x yaooc-config
