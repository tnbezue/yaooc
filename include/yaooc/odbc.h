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

MINI_MAP_DEFINITION(yaooc_string,yaooc_string,map_odbc_string_string)

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

yaooc_class_instance(yaooc_odbc_environment) {
  yaooc_object_class_instance_t;
};

yaooc_class(yaooc_odbc_environment);

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
  Class Definition for yaooc_odbc_value
*/
yaooc_class_table(yaooc_odbc_value) {
  yaooc_object_class_table_t;
  SQLSMALLINT (*c_data_type)(const_pointer);
  SQLLEN (*column_size)(const_pointer);
  void* (*data)(pointer);
};
#define yaooc_odbc_value_parent_class_table ((yaooc_object_class_table_t*)(yaooc_odbc_value_class_table.parent_class_table_))

yaooc_class_instance(yaooc_odbc_value) {
  yaooc_object_class_instance_t;
};

yaooc_class(yaooc_odbc_value);

/* Type Info Prototypes for yaooc_odbc_value */
//void yaooc_odbc_value_default_ctor(pointer);
//void yaooc_odbc_value_dtor(pointer);
//void yaooc_odbc_value_copy_ctor(pointer,const_pointer);
//void yaooc_odbc_value_assign(pointer,const_pointer);

/* Constructors prototypes for yaooc_odbc_value */

/* Table prototypes for yaooc_odbc_value */
#define yaooc_odbc_value_swap yaooc_object_swap
SQLSMALLINT yaooc_odbc_value_c_data_type(const_pointer);
SQLLEN yaooc_odbc_value_column_size(const_pointer);
void* yaooc_odbc_value_data(pointer);

/* Protected prototypes for yaooc_odbc_value */

/*
  Class Definition for yaooc_odbc_integer
*/
yaooc_class_table(yaooc_odbc_integer) {
  yaooc_odbc_value_class_table_t;
  long long (*get)(const_pointer);
  void (*set)(pointer, long long);
};
#define yaooc_odbc_integer_parent_class_table ((yaooc_odbc_value_class_table_t*)(yaooc_odbc_integer_class_table.parent_class_table_))

yaooc_class_instance(yaooc_odbc_integer) {
  yaooc_odbc_value_class_instance_t;
  long long value_;
};

yaooc_class(yaooc_odbc_integer);

/* Type Info Prototypes for yaooc_odbc_integer */
void yaooc_odbc_integer_default_ctor(pointer);
#define yaooc_odbc_integer_dtor yaooc_odbc_value_dtor
void yaooc_odbc_integer_copy_ctor(pointer,const_pointer);
void yaooc_odbc_integer_assign(pointer,const_pointer);

/* Constructors prototypes for yaooc_odbc_integer */

/* Table prototypes for yaooc_odbc_integer */
#define yaooc_odbc_integer_swap yaooc_odbc_value_swap
SQLSMALLINT yaooc_odbc_integer_c_data_type(const_pointer);
SQLLEN yaooc_odbc_integer_column_size(const_pointer);
void* yaooc_odbc_integer_data(pointer);
long long yaooc_odbc_integer_get(const_pointer);
void yaooc_odbc_integer_set(pointer, long long);

/* Protected prototypes for yaooc_odbc_integer */

/*
  Class Definition for yaooc_odbc_unsigned_integer
*/
yaooc_class_table(yaooc_odbc_unsigned_integer) {
  yaooc_odbc_value_class_table_t;
  unsigned long long (*get)(const_pointer);
  void (*set)(pointer, unsigned long long);
};
#define yaooc_odbc_unsigned_integer_parent_class_table ((yaooc_odbc_value_class_table_t*)(yaooc_odbc_unsigned_integer_class_table.parent_class_table_))

yaooc_class_instance(yaooc_odbc_unsigned_integer) {
  yaooc_odbc_value_class_instance_t;
  unsigned long long value_;
};

yaooc_class(yaooc_odbc_unsigned_integer);

/* Type Info Prototypes for yaooc_odbc_unsigned_integer */
void yaooc_odbc_unsigned_integer_default_ctor(pointer);
#define yaooc_odbc_unsigned_integer_dtor yaooc_odbc_value_dtor
void yaooc_odbc_unsigned_integer_copy_ctor(pointer,const_pointer);
void yaooc_odbc_unsigned_integer_assign(pointer,const_pointer);

/* Constructors prototypes for yaooc_odbc_unsigned_integer */

/* Table prototypes for yaooc_odbc_unsigned_integer */
#define yaooc_odbc_unsigned_integer_swap yaooc_odbc_value_swap
SQLSMALLINT yaooc_odbc_unsigned_integer_c_data_type(const_pointer);
SQLLEN yaooc_odbc_unsigned_integer_column_size(const_pointer);
void* yaooc_odbc_unsigned_integer_data(pointer);
unsigned long long yaooc_odbc_unsigned_integer_get(const_pointer);
void yaooc_odbc_unsigned_integer_set(pointer, unsigned long long);

/* Protected prototypes for yaooc_odbc_unsigned_integer */

/*
  Class Definition for yaooc_odbc_real
*/
yaooc_class_table(yaooc_odbc_real) {
  yaooc_odbc_value_class_table_t;
  double (*get)(const_pointer);
  void (*set)(pointer, double);
};
#define yaooc_odbc_real_parent_class_table ((yaooc_odbc_value_class_table_t*)(yaooc_odbc_real_class_table.parent_class_table_))

yaooc_class_instance(yaooc_odbc_real) {
  yaooc_odbc_value_class_instance_t;
  double value_;
};

yaooc_class(yaooc_odbc_real);

/* Type Info Prototypes for yaooc_odbc_real */
void yaooc_odbc_real_default_ctor(pointer);
#define yaooc_odbc_real_dtor yaooc_odbc_value_dtor
void yaooc_odbc_real_copy_ctor(pointer,const_pointer);
void yaooc_odbc_real_assign(pointer,const_pointer);

/* Constructors prototypes for yaooc_odbc_real */

/* Table prototypes for yaooc_odbc_real */
#define yaooc_odbc_real_swap yaooc_odbc_value_swap
SQLSMALLINT yaooc_odbc_real_c_data_type(const_pointer);
SQLLEN yaooc_odbc_real_column_size(const_pointer);
void* yaooc_odbc_real_data(pointer);
double yaooc_odbc_real_get(const_pointer);
void yaooc_odbc_real_set(pointer, double);

/* Protected prototypes for yaooc_odbc_real */

/*
  Class Definition for yaooc_odbc_string
*/
yaooc_class_table(yaooc_odbc_string) {
  yaooc_odbc_value_class_table_t;
  const char* (*get)(const_pointer);
  void (*set)(pointer, const char*);
  void (*setn)(pointer, const char*, size_t);
};
#define yaooc_odbc_string_parent_class_table ((yaooc_odbc_value_class_table_t*)(yaooc_odbc_string_class_table.parent_class_table_))

yaooc_class_instance(yaooc_odbc_string) {
  yaooc_odbc_value_class_instance_t;
  size_t size_;
  char* value_;
};

yaooc_class(yaooc_odbc_string);

/* Type Info Prototypes for yaooc_odbc_string */
void yaooc_odbc_string_default_ctor(pointer);
void yaooc_odbc_string_dtor(pointer);
void yaooc_odbc_string_copy_ctor(pointer,const_pointer);
void yaooc_odbc_string_assign(pointer,const_pointer);

/* Constructors prototypes for yaooc_odbc_string */
void yaooc_odbc_string_size(pointer,va_list);

/* Table prototypes for yaooc_odbc_string */
#define yaooc_odbc_string_swap yaooc_odbc_value_swap
SQLSMALLINT yaooc_odbc_string_c_data_type(const_pointer);
SQLLEN yaooc_odbc_string_column_size(const_pointer);
void* yaooc_odbc_string_data(pointer);
const char* yaooc_odbc_string_get(const_pointer);
void yaooc_odbc_string_set(pointer, const char*);
void yaooc_odbc_string_setn(pointer, const char*, size_t);

/* Protected prototypes for yaooc_odbc_string */

/*
  Class Definition for yaooc_odbc_blob
*/
yaooc_class_table(yaooc_odbc_blob) {
  yaooc_odbc_value_class_table_t;
  void* (*get)(const_pointer);
  void (*setn)(pointer, void*, size_t);
};
#define yaooc_odbc_blob_parent_class_table ((yaooc_odbc_value_class_table_t*)(yaooc_odbc_blob_class_table.parent_class_table_))

yaooc_class_instance(yaooc_odbc_blob) {
  yaooc_odbc_value_class_instance_t;
  size_t size_;
  void* value_;
};

yaooc_class(yaooc_odbc_blob);

/* Type Info Prototypes for yaooc_odbc_blob */
void yaooc_odbc_blob_default_ctor(pointer);
void yaooc_odbc_blob_dtor(pointer);
void yaooc_odbc_blob_copy_ctor(pointer,const_pointer);
void yaooc_odbc_blob_assign(pointer,const_pointer);

/* Constructors prototypes for yaooc_odbc_blob */
void yaooc_odbc_blob_size(pointer,va_list);

/* Table prototypes for yaooc_odbc_blob */
#define yaooc_odbc_blob_swap yaooc_odbc_value_swap
SQLSMALLINT yaooc_odbc_blob_c_data_type(const_pointer);
SQLLEN yaooc_odbc_blob_column_size(const_pointer);
void* yaooc_odbc_blob_data(pointer);
void* yaooc_odbc_blob_get(const_pointer);
void yaooc_odbc_blob_set(pointer, void*, size_t);

/* Protected prototypes for yaooc_odbc_blob */

/*
  Class Definition for yaooc_odbc_time
*/
yaooc_class_table(yaooc_odbc_time) {
  yaooc_odbc_value_class_table_t;
  TIME_STRUCT (*get)(const_pointer);
  void (*set)(pointer, TIME_STRUCT);
  int (*get_secs)(const_pointer);
  void (*set_secs)(pointer, int);
};
#define yaooc_odbc_time_parent_class_table ((yaooc_odbc_value_class_table_t*)(yaooc_odbc_time_class_table.parent_class_table_))

yaooc_class_instance(yaooc_odbc_time) {
  yaooc_odbc_value_class_instance_t;
  TIME_STRUCT value_;
};

yaooc_class(yaooc_odbc_time);

/* Type Info Prototypes for yaooc_odbc_time */
void yaooc_odbc_time_default_ctor(pointer);
#define yaooc_odbc_time_dtor yaooc_odbc_value_dtor
void yaooc_odbc_time_copy_ctor(pointer,const_pointer);
void yaooc_odbc_time_assign(pointer,const_pointer);

/* Constructors prototypes for yaooc_odbc_time */

/* Table prototypes for yaooc_odbc_time */
#define yaooc_odbc_time_swap yaooc_odbc_value_swap
SQLSMALLINT yaooc_odbc_time_c_data_type(const_pointer);
SQLLEN yaooc_odbc_time_column_size(const_pointer);
void* yaooc_odbc_time_data(pointer);
TIME_STRUCT yaooc_odbc_time_get(const_pointer);
void yaooc_odbc_time_set(pointer, TIME_STRUCT);

/* Protected prototypes for yaooc_odbc_time */

/*
  Class Definition for yaooc_odbc_date
*/
yaooc_class_table(yaooc_odbc_date) {
  yaooc_odbc_value_class_table_t;
  DATE_STRUCT (*get)(const_pointer);
  void (*set)(pointer, DATE_STRUCT);
  time_t (*get_time)(const_pointer);
  void (*set_time)(pointer, time_t);
};
#define yaooc_odbc_date_parent_class_table ((yaooc_odbc_value_class_table_t*)(yaooc_odbc_date_class_table.parent_class_table_))

yaooc_class_instance(yaooc_odbc_date) {
  yaooc_odbc_value_class_instance_t;
  DATE_STRUCT value_;
};

yaooc_class(yaooc_odbc_date);

/* Type Info Prototypes for yaooc_odbc_date */
void yaooc_odbc_date_default_ctor(pointer);
#define yaooc_odbc_date_dtor yaooc_odbc_value_dtor
void yaooc_odbc_date_copy_ctor(pointer,const_pointer);
void yaooc_odbc_date_assign(pointer,const_pointer);

/* Constructors prototypes for yaooc_odbc_date */

/* Table prototypes for yaooc_odbc_date */
#define yaooc_odbc_date_swap yaooc_odbc_value_swap
SQLSMALLINT yaooc_odbc_date_c_data_type(const_pointer);
SQLLEN yaooc_odbc_date_column_size(const_pointer);
void* yaooc_odbc_date_data(pointer);
DATE_STRUCT yaooc_odbc_date_get(const_pointer);
void yaooc_odbc_date_set(pointer, DATE_STRUCT);

/* Protected prototypes for yaooc_odbc_date */

/*
  Class Definition for yaooc_odbc_timestamp
*/
yaooc_class_table(yaooc_odbc_timestamp) {
  yaooc_odbc_value_class_table_t;
  TIMESTAMP_STRUCT (*get)(const_pointer);
  void (*set)(pointer, TIMESTAMP_STRUCT);
  time_t (*get_time)(const_pointer);
  void (*set_time)(pointer, time_t);
};
#define yaooc_odbc_timestamp_parent_class_table ((yaooc_odbc_value_class_table_t*)(yaooc_odbc_timestamp_class_table.parent_class_table_))

yaooc_class_instance(yaooc_odbc_timestamp) {
  yaooc_odbc_value_class_instance_t;
  TIMESTAMP_STRUCT value_;
};

yaooc_class(yaooc_odbc_timestamp);

/* Type Info Prototypes for yaooc_odbc_timestamp */
void yaooc_odbc_timestamp_default_ctor(pointer);
#define yaooc_odbc_timestamp_dtor yaooc_odbc_value_dtor
void yaooc_odbc_timestamp_copy_ctor(pointer,const_pointer);
void yaooc_odbc_timestamp_assign(pointer,const_pointer);

/* Constructors prototypes for yaooc_odbc_timestamp */

/* Table prototypes for yaooc_odbc_timestamp */
#define yaooc_odbc_timestamp_swap yaooc_odbc_value_swap
SQLSMALLINT yaooc_odbc_timestamp_c_data_type(const_pointer);
SQLLEN yaooc_odbc_timestamp_column_size(const_pointer);
void* yaooc_odbc_timestamp_data(pointer);
TIMESTAMP_STRUCT yaooc_odbc_timestamp_get(const_pointer);
void yaooc_odbc_timestamp_set(pointer, TIMESTAMP_STRUCT);

/* Protected prototypes for yaooc_odbc_timestamp */

/*
  Class Definition for yaooc_odbc_statement
*/
yaooc_class_table(yaooc_odbc_statement) {
  yaooc_object_class_table_t;
  bool (*bindcols)(pointer, void*, ...);
  bool (*bindparams)(pointer, void*, ...);
  bool (*fetch)(pointer);
  bool (*execute)(pointer);
};
#define yaooc_odbc_statement_parent_class_table ((yaooc_object_class_table_t*)(yaooc_odbc_statement_class_table.parent_class_table_))

yaooc_class_instance(yaooc_odbc_statement) {
  yaooc_object_class_instance_t;
  SQLHSTMT statement_handle_;
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
bool yaooc_odbc_statement_bindcols(pointer, void*, ...);
bool yaooc_odbc_statement_bindparams(pointer, void*, ...);
bool yaooc_odbc_statement_fetch(pointer);
bool yaooc_odbc_statement_execute(pointer);

/* Protected prototypes for yaooc_odbc_statement */

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
  yaooc_object_class_instance_t;
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
