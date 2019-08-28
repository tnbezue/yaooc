/*
		Copyright (C) 2016-2019  by Terry N Bezue

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
#ifndef __ODBC_INCLUDED__
#define __ODBC_INCLUDED__

/* Begin YAOOCPP output */

#include <yaooc/map.h>
#include <yaooc/string.h>
#include <yaooc/exception.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include <sql.h>
#include <sqlext.h>

MINI_MAP_DEFINITION(yaooc_string,yaooc_string,map_odbc_string_string);

/*
  Class Definition for yaooc_odbc_exception
*/
yaooc_class_table(yaooc_odbc_exception) {
  yaooc_exception_class_table_t;
};
#define yaooc_odbc_exception_parent_class_table ((yaooc_exception_class_table_t*)(yaooc_odbc_exception_class_table.parent_class_table_))

yaooc_class_instance(yaooc_odbc_exception) {
  yaooc_exception_class_instance_t;
};

yaooc_class(yaooc_odbc_exception);

/* Type Info Prototypes for yaooc_odbc_exception */
#define yaooc_odbc_exception_default_ctor yaooc_exception_default_ctor
#define yaooc_odbc_exception_dtor yaooc_exception_dtor
#define yaooc_odbc_exception_copy_ctor yaooc_exception_copy_ctor
#define yaooc_odbc_exception_assign yaooc_exception_assign

/* Constructors prototypes for yaooc_odbc_exception */
#define yaooc_odbc_exception_ctor_v yaooc_exception_ctor_v

/* Table prototypes for yaooc_odbc_exception */
#define yaooc_odbc_exception_swap yaooc_exception_swap
#define yaooc_odbc_exception_what yaooc_exception_what

/* Protected prototypes for yaooc_odbc_exception */


/*
  Class Definition for yaooc_odbc_environment
*/
yaooc_class_table(yaooc_odbc_environment) {
  yaooc_object_class_table_t;
  SQLHENV (*env)(pointer);
};
#define yaooc_odbc_environment_parent_class_table ((yaooc_object_class_table_t*)(yaooc_odbc_environment_class_table.parent_class_table_))

/*
yaooc_class_instance(yaooc_odbc_environment) {
  yaooc_object_class_instance_t;
};

yaooc_class(yaooc_odbc_environment);
*/
typedef struct yaooc_odbc_environment_s yaooc_odbc_environment_t;
typedef struct yaooc_odbc_environment_s * const yaooc_odbc_environment_pointer;
typedef const struct yaooc_odbc_environment_s * const yaooc_odbc_environment_const_pointer;
extern yaooc_odbc_environment_class_table_t yaooc_odbc_environment_class_table;
extern const type_info_t __yaooc_odbc_environment_ti;
extern const type_info_t* const yaooc_odbc_environment_ti;
struct yaooc_odbc_environment_s
{
	const yaooc_odbc_environment_class_table_t* class_table_;
};

/* Type Info Prototypes for yaooc_odbc_environment */
void yaooc_odbc_environment_default_ctor(pointer);
void yaooc_odbc_environment_dtor(pointer);
#define yaooc_odbc_environment_copy_ctor yaooc_object_copy_ctor
#define yaooc_odbc_environment_assign yaooc_object_assign

/* Constructors prototypes for yaooc_odbc_environment */

/* Table prototypes for yaooc_odbc_environment */
#define yaooc_odbc_environment_swap yaooc_object_swap
SQLHENV yaooc_odbc_environment_env(pointer);

/* Protected prototypes for yaooc_odbc_environment */
extern yaooc_odbc_environment_t* yaooc_odbc_environment_current_environment(pointer);
extern map_odbc_string_string_t* yaooc_odbc_environment_get_drivers(pointer);
extern map_odbc_string_string_t* yaooc_odbc_environment_get_sources(pointer);

/*
  Class Definition for yaooc_odbc_statement
*/
yaooc_class_table(yaooc_odbc_statement) {
  yaooc_object_class_table_t;
  bool (*bindcol_chr)(pointer, char*);
  bool (*bindcol_uchr)(pointer, unsigned char*);
  bool (*bindcol_short)(pointer, short*);
  bool (*bindcol_ushort)(pointer, unsigned short*);
  bool (*bindcol_int)(pointer, int*);
  bool (*bindcol_uint)(pointer, unsigned int*);
  bool (*bindcol_long)(pointer, long long*);
  bool (*bindcol_ulong)(pointer, unsigned long long*);
  bool (*bindcol_dbl)(pointer, double*);
  bool (*bindcol_str)(pointer, char*, SQLLEN);
  bool (*bindcol_blob)(pointer, void*, SQLLEN);
  bool (*bindcol_time)(pointer, TIME_STRUCT*);
  bool (*bindcol_date)(pointer, DATE_STRUCT*);
  bool (*bindcol_ts)(pointer, TIMESTAMP_STRUCT*);
  bool (*bindparam_chr)(pointer, char*);
  bool (*bindparam_uchr)(pointer, unsigned char*);
  bool (*bindparam_short)(pointer, short*);
  bool (*bindparam_ushort)(pointer, unsigned short*);
  bool (*bindparam_int)(pointer, int*);
  bool (*bindparam_uint)(pointer, unsigned int*);
  bool (*bindparam_long)(pointer, long long*);
  bool (*bindparam_ulong)(pointer, unsigned long long*);
  bool (*bindparam_dbl)(pointer, double*);
  bool (*bindparam_str)(pointer, char*, SQLLEN);
  bool (*bindparam_blob)(pointer, void*, SQLLEN);
  bool (*bindparam_time)(pointer, TIME_STRUCT*);
  bool (*bindparam_date)(pointer, DATE_STRUCT*);
  bool (*bindparam_ts)(pointer, TIMESTAMP_STRUCT*);
  bool (*fetch)(pointer);
  bool (*execute)(pointer);
};
#define yaooc_odbc_statement_parent_class_table ((yaooc_object_class_table_t*)(yaooc_odbc_statement_class_table.parent_class_table_))


yaooc_class_instance(yaooc_odbc_statement) {
  SQLHSTMT statement_handle_;
	unsigned int icol_;
};

yaooc_class(yaooc_odbc_statement);

/* Type Info Prototypes for yaooc_odbc_statement */
void yaooc_odbc_statement_default_ctor(pointer);
void yaooc_odbc_statement_dtor(pointer);
#define yaooc_odbc_statement_copy_ctor yaooc_object_copy_ctor
void yaooc_odbc_statement_assign(pointer,const_pointer);

/* Constructors prototypes for yaooc_odbc_statement */

/* Table prototypes for yaooc_odbc_statement */
#define yaooc_odbc_statement_swap yaooc_object_swap
bool yaooc_odbc_statement_bindcol_chr(pointer, char*);
bool yaooc_odbc_statement_bindcol_uchr(pointer, unsigned char*);
bool yaooc_odbc_statement_bindcol_short(pointer, short*);
bool yaooc_odbc_statement_bindcol_ushort(pointer, unsigned short*);
bool yaooc_odbc_statement_bindcol_int(pointer, int*);
bool yaooc_odbc_statement_bindcol_uint(pointer, unsigned int*);
bool yaooc_odbc_statement_bindcol_long(pointer, long long*);
bool yaooc_odbc_statement_bindcol_ulong(pointer, unsigned long long*);
bool yaooc_odbc_statement_bindcol_dbl(pointer, double*);
bool yaooc_odbc_statement_bindcol_str(pointer, char*, SQLLEN);
bool yaooc_odbc_statement_bindcol_blob(pointer, void*, SQLLEN);
bool yaooc_odbc_statement_bindcol_time(pointer, TIME_STRUCT*);
bool yaooc_odbc_statement_bindcol_date(pointer, DATE_STRUCT*);
bool yaooc_odbc_statement_bindcol_ts(pointer, TIMESTAMP_STRUCT*);
bool yaooc_odbc_statement_bindparam_chr(pointer, char*);
bool yaooc_odbc_statement_bindparam_uchr(pointer, unsigned char*);
bool yaooc_odbc_statement_bindparam_short(pointer, short*);
bool yaooc_odbc_statement_bindparam_ushort(pointer, unsigned short*);
bool yaooc_odbc_statement_bindparam_int(pointer, int*);
bool yaooc_odbc_statement_bindparam_uint(pointer, unsigned int*);
bool yaooc_odbc_statement_bindparam_long(pointer, long long*);
bool yaooc_odbc_statement_bindparam_ulong(pointer, unsigned long long*);
bool yaooc_odbc_statement_bindparam_dbl(pointer, double*);
bool yaooc_odbc_statement_bindparam_str(pointer, char*, SQLLEN);
bool yaooc_odbc_statement_bindparam_blob(pointer, void*, SQLLEN);
bool yaooc_odbc_statement_bindparam_time(pointer, TIME_STRUCT*);
bool yaooc_odbc_statement_bindparam_date(pointer, DATE_STRUCT*);
bool yaooc_odbc_statement_bindparam_ts(pointer, TIMESTAMP_STRUCT*);
bool yaooc_odbc_statement_fetch(pointer);
bool yaooc_odbc_statement_execute(pointer);

/* Protected prototypes for yaooc_odbc_statement */
bool yaooc_odbc_statement_bindcol(pointer, void*, SQLLEN, SQLSMALLINT);
bool yaooc_odbc_statement_bindparam(pointer, void*, SQLLEN, SQLSMALLINT);

/*
  Class Definition for yaooc_odbc_connection
*/
yaooc_class_table(yaooc_odbc_connection) {
  yaooc_object_class_table_t;
  yaooc_odbc_statement_t* (*exec_direct)(pointer, const char*);
  yaooc_odbc_statement_t* (*prepare)(pointer, const char*);
  void (*connect)(pointer, const char*);
  void (*disconnect)(pointer);
  void (*auto_commit)(pointer, bool);
  void (*commit)(pointer);
  void (*rollback)(pointer);
};
#define yaooc_odbc_connection_parent_class_table ((yaooc_object_class_table_t*)(yaooc_odbc_connection_class_table.parent_class_table_))

yaooc_class_instance(yaooc_odbc_connection) {
  SQLHDBC connection_handle_;
};

yaooc_class(yaooc_odbc_connection);

/* Type Info Prototypes for yaooc_odbc_connection */
void yaooc_odbc_connection_default_ctor(pointer);
void yaooc_odbc_connection_dtor(pointer);
#define yaooc_odbc_connection_copy_ctor yaooc_object_copy_ctor
#define yaooc_odbc_connection_assign yaooc_object_assign

/* Constructors prototypes for yaooc_odbc_connection */
void yaooc_odbc_connection_connect_str(pointer,va_list);

/* Table prototypes for yaooc_odbc_connection */
#define yaooc_odbc_connection_swap yaooc_object_swap
yaooc_odbc_statement_t* yaooc_odbc_connection_exec_direct(pointer, const char*);
yaooc_odbc_statement_t* yaooc_odbc_connection_prepare(pointer, const char*);
void yaooc_odbc_connection_connect(pointer, const char*);
void yaooc_odbc_connection_disconnect(pointer);
void yaooc_odbc_connection_auto_commit(pointer, bool);
void yaooc_odbc_connection_commit(pointer);
void yaooc_odbc_connection_rollback(pointer);

/* Protected prototypes for yaooc_odbc_connection */

/* End YAOOCPP output */


#endif
