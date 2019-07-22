
m4_define([yaooc_major], [1])
m4_define([yaooc_minor], [3])
m4_define([yaooc_level], [1])
m4_define([yaooc_version],[yaooc_major.yaooc_minor.yaooc_level])

AC_PREREQ([2.50])
AC_INIT([yaooc],[yaooc_version])
AM_INIT_AUTOMAKE([foreign 1.13 subdir-objects -Wall ])
AC_CONFIG_SRCDIR([src/new.c])

AC_CANONICAL_HOST

AC_PROG_CC
AC_PROG_INSTALL
AM_PROG_AR
AC_CONFIG_MACRO_DIRS([m4])
AC_CHECK_HEADER_STDBOOL
AC_FUNC_MALLOC

# need -fms_extensions for anonymous struct members
CFLAGS="$CFLAGS -D_GNU_SOURCE -Wall -fms-extensions"

# -Wno-microsoft so clang doesn't produce warnings
if test "x$ac_ct_CC" = xclang; then
	CFLAGS="$CFLAGS -Wno-microsoft"
fi

# Checks for header files.
#AC_CONFIG_HEADERS([include/yaooc/config.h])
AC_CHECK_HEADERS([fcntl.h inttypes.h stddef.h stdint.h stdlib.h string.h unistd.h])
AC_CHECK_FUNCS([memchr memmove memrchr memset strchr getcwd gettimeofday socket strcasecmp strcspn strdup strrchr strspn strstr])
AC_FUNC_REALLOC
AC_TYPE_INT64_T
AC_TYPE_MODE_T
AC_TYPE_OFF_T
AC_TYPE_PID_T
AC_TYPE_SIZE_T
AC_TYPE_UID_T
AC_TYPE_UINT32_T
AC_FUNC_MKTIME

AC_MSG_CHECKING(for debugging)
AC_ARG_ENABLE(debug,[AS_HELP_STRING([--enable-debug],[compile for debugging])],
	[ CFLAGS="$CFLAGS -g -D__DEBUG__" ],
	[ ]
)

AC_MSG_CHECKING(for ODBC support)
AC_CHECK_HEADER(sql.h)
case $host_os in
	mingw* | cygwin*)
		# Assume odbc32 lib is present
		LIBS="$LIBS -lodbc32"
	;;

	*)
	AC_CHECK_LIB(odbc,SQLAllocHandle,
		[
			LIBS="-lodbc"
		],
		[
			AC_MSG_ERROR(odbc library not found)
		]
	)
esac

# For Windows, add -lws2_32 for networking support
case $host_os in
	mingw* | cygwin*)
		# Assume odbc32 lib is present
		LIBS="$LIBS -lws2_32"
	;;
esac

AC_MSG_CHECKING(for garbage collection)
AC_ARG_ENABLE([gc],[AC_HELP_STRING([--enable-gc],[compile using garbage collection])],
	[
		AC_CHECK_HEADER(gc/gc.h,
      AC_CHECK_LIB(gc,GC_malloc,
        [
          CFLAGS="$CFLAGS -D__YAOOC_USE_GC__"
          LIBS="$LIBS -lgc"
        ],
        [
          AC_MSG_FAILURE([Garbage collection library not found])
        ]
      )
    )
  ]
)

AC_SUBST(YAOOC_MAJOR_VERSION,yaooc_major)
AC_SUBST(YAOOC_MINOR_VERSION,yaooc_minor)
AC_SUBST(YAOOC_PATCH_LEVEL,yaooc_level)

AC_MSG_CHECKING(to use tre)
AC_ARG_WITH([tre],
  [AS_HELP_STRING([--with-tre],[use tre regular expression (yes to use tre, no to use system (gnu) re)])],
	[
		AC_CHECK_HEADER(tre/tre.h)
		AC_CHECK_LIB([tre],[tre_regcomp],
			[
				CFLAGS="$CFLAGS -D__YAOOC_USE_TRE__"
				LIBS="$LIBS -ltre"
			],
			[
				AC_MSG_FAILURE([tre library not found. Modify CFLAGS and LDFLAGS then rerun configure. Or specify --without-tre])
			]
		)
	],
	[
		AC_CHECK_LIB(c,regcomp,[],[AC_MSG_ERROR(suitable regular expression library not found)])
	]
)

AC_CONFIG_FILES([yaooc-config Makefile])

LT_INIT

AC_OUTPUT

chmod +x yaooc-config
