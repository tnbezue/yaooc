#ifndef __ODBC_INCLUDED__
#define __ODBC_INCLUDED__
#include <yaooc/new.h>
#include <yaooc/object.h>
#include <yaooc/exception.h>
yaooc_class_table(yaooc_odbc_exception) {
  yaooc_exception_class_table_t;
};
#define yaooc_odbc_exception_parent_class_table ((yaooc_exception_class_table_t*)(yaooc_odbc_exception_class_table.parent_class_table_))

yaooc_class_instance(yaooc_odbc_exception) {
  yaooc_exception_class_instance_t;
};

yaooc_class(yaooc_odbc_exception);
#define yaooc_odbc_exception_ctor_v yaooc_exception_ctor_v
#define yaooc_odbc_exception_swap yaooc_exception_swap
#define yaooc_odbc_exception_what yaooc_exception_what
#define yaooc_odbc_exception_error_code yaooc_exception_error_code
#include <yaooc/map.h>
#include <yaooc/string.h>
#include <yaooc/exception.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include <sql.h>
#include <sqlext.h>
MINI_MAP_DEFINITION(yaooc_string,yaooc_string,map_odbc_string_string);

yaooc_class_table(yaooc_odbc_environment) {
  yaooc_object_class_table_t;
};
#define yaooc_odbc_environment_parent_class_table ((yaooc_object_class_table_t*)(yaooc_odbc_environment_class_table.parent_class_table_))
yaooc_class_without_instance(yaooc_odbc_environment);
void yaooc_odbc_environment_default_ctor(pointer);
void yaooc_odbc_environment_dtor(pointer);
#define yaooc_odbc_environment_swap yaooc_object_swap
extern  SQLHENV yaooc_odbc_environment_henv_;
 map_odbc_string_string_t* yaooc_odbc_environment_get_drivers(pointer);
 map_odbc_string_string_t* yaooc_odbc_environment_get_sources(pointer);
yaooc_class_table(yaooc_odbc_statement) {
  yaooc_object_class_table_t;
bool (*bindcol_chr)(pointer,char*);
bool (*bindcol_uchr)(pointer,unsigned char*);
bool (*bindcol_short)(pointer,short*);
bool (*bindcol_ushort)(pointer,unsigned short*);
bool (*bindcol_int)(pointer,int*);
bool (*bindcol_uint)(pointer,unsigned int*);
bool (*bindcol_long)(pointer,long long*);
bool (*bindcol_ulong)(pointer,unsigned long long*);
bool (*bindcol_dbl)(pointer,double*);
bool (*bindcol_str)(pointer,char*,SQLLEN);
bool (*bindcol_blob)(pointer,void*,SQLLEN);
bool (*bindcol_time)(pointer,TIME_STRUCT*);
bool (*bindcol_date)(pointer,DATE_STRUCT*);
bool (*bindcol_ts)(pointer,TIMESTAMP_STRUCT*);
bool (*bindparam_chr)(pointer,char*);
bool (*bindparam_uchr)(pointer,unsigned char*);
bool (*bindparam_short)(pointer,short*);
bool (*bindparam_ushort)(pointer,unsigned short*);
bool (*bindparam_int)(pointer,int*);
bool (*bindparam_uint)(pointer,unsigned int*);
bool (*bindparam_long)(pointer,long long*);
bool (*bindparam_ulong)(pointer,unsigned long long*);
bool (*bindparam_dbl)(pointer,double*);
bool (*bindparam_str)(pointer,char*,SQLLEN);
bool (*bindparam_blob)(pointer,void*,SQLLEN);
bool (*bindparam_time)(pointer,TIME_STRUCT*);
bool (*bindparam_date)(pointer,DATE_STRUCT*);
bool (*bindparam_ts)(pointer,TIMESTAMP_STRUCT*);
bool (*fetch)(pointer);
bool (*execute)(pointer);
};
#define yaooc_odbc_statement_parent_class_table ((yaooc_object_class_table_t*)(yaooc_odbc_statement_class_table.parent_class_table_))

yaooc_class_instance(yaooc_odbc_statement) {
SQLHSTMT statement_handle_;
unsigned int icol_;
};

yaooc_class(yaooc_odbc_statement);
void yaooc_odbc_statement_default_ctor(pointer);
void yaooc_odbc_statement_dtor(pointer);
#define yaooc_odbc_statement_swap yaooc_object_swap
 bool yaooc_odbc_statement_bindcol_chr(pointer,char*);
 bool yaooc_odbc_statement_bindcol_uchr(pointer,unsigned char*);
 bool yaooc_odbc_statement_bindcol_short(pointer,short*);
 bool yaooc_odbc_statement_bindcol_ushort(pointer,unsigned short*);
 bool yaooc_odbc_statement_bindcol_int(pointer,int*);
 bool yaooc_odbc_statement_bindcol_uint(pointer,unsigned int*);
 bool yaooc_odbc_statement_bindcol_long(pointer,long long*);
 bool yaooc_odbc_statement_bindcol_ulong(pointer,unsigned long long*);
 bool yaooc_odbc_statement_bindcol_dbl(pointer,double*);
 bool yaooc_odbc_statement_bindcol_str(pointer,char*,SQLLEN);
 bool yaooc_odbc_statement_bindcol_blob(pointer,void*,SQLLEN);
 bool yaooc_odbc_statement_bindcol_time(pointer,TIME_STRUCT*);
 bool yaooc_odbc_statement_bindcol_date(pointer,DATE_STRUCT*);
 bool yaooc_odbc_statement_bindcol_ts(pointer,TIMESTAMP_STRUCT*);
 bool yaooc_odbc_statement_bindparam_chr(pointer,char*);
 bool yaooc_odbc_statement_bindparam_uchr(pointer,unsigned char*);
 bool yaooc_odbc_statement_bindparam_short(pointer,short*);
 bool yaooc_odbc_statement_bindparam_ushort(pointer,unsigned short*);
 bool yaooc_odbc_statement_bindparam_int(pointer,int*);
 bool yaooc_odbc_statement_bindparam_uint(pointer,unsigned int*);
 bool yaooc_odbc_statement_bindparam_long(pointer,long long*);
 bool yaooc_odbc_statement_bindparam_ulong(pointer,unsigned long long*);
 bool yaooc_odbc_statement_bindparam_dbl(pointer,double*);
 bool yaooc_odbc_statement_bindparam_str(pointer,char*,SQLLEN);
 bool yaooc_odbc_statement_bindparam_blob(pointer,void*,SQLLEN);
 bool yaooc_odbc_statement_bindparam_time(pointer,TIME_STRUCT*);
 bool yaooc_odbc_statement_bindparam_date(pointer,DATE_STRUCT*);
 bool yaooc_odbc_statement_bindparam_ts(pointer,TIMESTAMP_STRUCT*);
 bool yaooc_odbc_statement_fetch(pointer);
 bool yaooc_odbc_statement_execute(pointer);
 bool yaooc_odbc_statement_bindcol(pointer,void*,SQLLEN,SQLSMALLINT);
 bool yaooc_odbc_statement_bindparam(pointer,void*,SQLLEN,SQLSMALLINT);
yaooc_class_table(yaooc_odbc_connection) {
  yaooc_object_class_table_t;
yaooc_odbc_statement_t* (*exec_direct)(pointer,const char*);
yaooc_odbc_statement_t* (*prepare)(pointer,const char*);
void (*connect)(pointer,const char*);
void (*disconnect)(pointer);
void (*auto_commit)(pointer,bool);
void (*commit)(pointer);
void (*rollback)(pointer);
};
#define yaooc_odbc_connection_parent_class_table ((yaooc_object_class_table_t*)(yaooc_odbc_connection_class_table.parent_class_table_))

yaooc_class_instance(yaooc_odbc_connection) {
SQLHDBC connection_handle_;
};

yaooc_class(yaooc_odbc_connection);
void yaooc_odbc_connection_default_ctor(pointer);
void yaooc_odbc_connection_dtor(pointer);
void yaooc_odbc_connection_ctor_connect_str(pointer,va_list);
#define yaooc_odbc_connection_swap yaooc_object_swap
 yaooc_odbc_statement_t* yaooc_odbc_connection_exec_direct(pointer,const char*);
 yaooc_odbc_statement_t* yaooc_odbc_connection_prepare(pointer,const char*);
 void yaooc_odbc_connection_connect(pointer,const char*);
 void yaooc_odbc_connection_disconnect(pointer);
 void yaooc_odbc_connection_auto_commit(pointer,bool);
 void yaooc_odbc_connection_commit(pointer);
 void yaooc_odbc_connection_rollback(pointer);

#endif
