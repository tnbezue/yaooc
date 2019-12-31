#include <yaooc/odbc.h>
yaooc_odbc_exception_class_table_t yaooc_odbc_exception_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_exception_class_table,
.type_name_ = (const char*)"yaooc_odbc_exception_t",
.swap = (void(*)(pointer,pointer)) yaooc_odbc_exception_swap,
.what = (const char*(*)(const_pointer)) yaooc_odbc_exception_what,
.error_code = (int(*)(const_pointer)) yaooc_odbc_exception_error_code,
};
const type_info_t __yaooc_odbc_exception_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_odbc_exception_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_odbc_exception_class_table,
.parent_=&__yaooc_exception_ti
};
const type_info_t* const yaooc_odbc_exception_ti=&__yaooc_odbc_exception_ti;
MINI_MAP_IMPLEMENTATION(yaooc_string,yaooc_string,map_odbc_string_string);


void yaooc_odbc_environment_default_ctor(pointer __pthis__)
{
yaooc_odbc_environment_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_odbc_environment);



      
      if(yaooc_odbc_environment_henv_ == SQL_NULL_HANDLE) {
        
        if(SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &yaooc_odbc_environment_henv_) == SQL_SUCCESS) {
          
          if(SQLSetEnvAttr(yaooc_odbc_environment_henv_, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0) != SQL_SUCCESS) {
            yaooc_odbc_environment_dtor(this);
            yaooc_odbc_environment_henv_=SQL_NULL_HANDLE;
          }
        }
      } else {
        
        puts("Only one ODBC environment allowed");
        exit(1);
      }
    
}
void yaooc_odbc_environment_dtor(pointer __pthis__)
{
yaooc_odbc_environment_pointer this=__pthis__;(void)this;


      if(yaooc_odbc_environment_henv_ != SQL_NULL_HANDLE)
        SQLFreeHandle(SQL_HANDLE_ENV,yaooc_odbc_environment_henv_);
    
}
 SQLHENV yaooc_odbc_environment_henv_=SQL_NULL_HANDLE;
map_odbc_string_string_t* yaooc_odbc_environment_get_drivers(pointer __pthis__)
{
yaooc_odbc_environment_pointer this=__pthis__;(void)this;

      map_odbc_string_string_t *drivers = new(map_odbc_string_string);
      SQLCHAR driver[256];
      SQLCHAR attr[256];
      SQLSMALLINT driver_ret;
      SQLSMALLINT attr_ret;
      yaooc_string_t key,value;
      newp(&key,yaooc_string);
      newp(&value,yaooc_string);
      SQLRETURN ret = SQLDrivers(yaooc_odbc_environment_henv_,SQL_FETCH_FIRST,
            driver, sizeof(driver), &driver_ret,
            attr, sizeof(attr), &attr_ret);
      while(SQL_SUCCEEDED(ret)) {
        M(&key,set,(const char*)driver);
        M(&value,set,(const char*)attr);
        M(drivers,insert,&key,&value);
        
          ret = SQLDrivers(yaooc_odbc_environment_henv_,SQL_FETCH_NEXT,
            driver, sizeof(driver), &driver_ret,
            attr, sizeof(attr), &attr_ret);
      }
      deletep(&key,yaooc_string);
      deletep(&value,yaooc_string);
      return drivers;
    
}
map_odbc_string_string_t* yaooc_odbc_environment_get_sources(pointer __pthis__)
{
yaooc_odbc_environment_pointer this=__pthis__;(void)this;

      map_odbc_string_string_t* sources = new(map_odbc_string_string);
      char dsn[256];
      char desc[256];
      yaooc_string_t key,value;
      newp(&key,yaooc_string);
      newp(&value,yaooc_string);
      SQLSMALLINT dsn_ret;
      SQLSMALLINT desc_ret;
      SQLRETURN ret = SQLDataSources(yaooc_odbc_environment_henv_,SQL_FETCH_FIRST,(SQLCHAR*)dsn, sizeof(dsn),
              &dsn_ret,(SQLCHAR*)desc, sizeof(desc), &desc_ret);

      while(SQL_SUCCEEDED(ret)) {
    
        M(&key,set,dsn);
        M(&value,set,desc);
        M(sources,insert,&key,&value);
    
    
        ret = SQLDataSources(yaooc_odbc_environment_henv_,SQL_FETCH_NEXT,(SQLCHAR*)dsn, sizeof(dsn),
              &dsn_ret,(SQLCHAR*)desc, sizeof(desc), &desc_ret);
      }
      deletep(&key,yaooc_string);
      deletep(&value,yaooc_string);
      return sources;
    
}
yaooc_odbc_environment_class_table_t yaooc_odbc_environment_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_object_class_table,
.type_name_ = (const char*)"yaooc_odbc_environment_t",
.swap = (void(*)(pointer,pointer)) yaooc_odbc_environment_swap,
};
const type_info_t __yaooc_odbc_environment_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_odbc_environment_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_odbc_environment_default_ctor,
.dtor_=yaooc_odbc_environment_dtor,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_odbc_environment_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_odbc_environment_ti=&__yaooc_odbc_environment_ti;
static void yaooc_odbc_statement_set_handle(pointer,SQLHSTMT);
static void yaooc_odbc_statement_set_handle(pointer __pthis__,SQLHSTMT h)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->set_handle(this,h)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      this->statement_handle_=h;
    
#undef PM
#undef super
}
void yaooc_odbc_statement_default_ctor(pointer __pthis__)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_odbc_statement);



      
      THROW(new_ctor(yaooc_odbc_exception,yaooc_odbc_exception_ctor_v,"ODBC statement can only be created from connection"));
    
}
void yaooc_odbc_statement_dtor(pointer __pthis__)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;


      if(this->statement_handle_ != SQL_NULL_HANDLE) {
        SQLCloseCursor(this->statement_handle_);
        SQLFreeHandle(SQL_HANDLE_STMT,this->statement_handle_);
        this->statement_handle_ = SQL_NULL_HANDLE;
      }
    
}
bool yaooc_odbc_statement_bindcol(pointer __pthis__,void* data,SQLLEN column_size,SQLSMALLINT c_data_type)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;

      return SQLBindCol(this->statement_handle_,this->icol_++,c_data_type,data,column_size,NULL) == SQL_SUCCESS;
    
}
bool yaooc_odbc_statement_bindparam(pointer __pthis__,void* data,SQLLEN column_size,SQLSMALLINT c_data_type)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;

      return SQLBindParameter(this->statement_handle_,this->icol_++,SQL_PARAM_INPUT,c_data_type,SQL_DEFAULT,
              column_size,0,data,column_size,NULL) == SQL_SUCCESS;
    
}
bool yaooc_odbc_statement_bindcol_chr(pointer __pthis__,char* v)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindcol_chr(this,v)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindcol(this,v,sizeof(char),SQL_C_STINYINT);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindcol_uchr(pointer __pthis__,unsigned char* v)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindcol_uchr(this,v)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindcol(this,v,sizeof(unsigned char),SQL_C_UTINYINT);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindcol_short(pointer __pthis__,short* v)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindcol_short(this,v)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindcol(this,v,sizeof(short),SQL_C_SSHORT);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindcol_ushort(pointer __pthis__,unsigned short* v)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindcol_ushort(this,v)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindcol(this,v,sizeof(unsigned short),SQL_C_USHORT);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindcol_int(pointer __pthis__,int* v)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindcol_int(this,v)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindcol(this,v,sizeof(int),SQL_C_SLONG);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindcol_uint(pointer __pthis__,unsigned int* v)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindcol_uint(this,v)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindcol(this,v,sizeof(unsigned int),SQL_C_ULONG);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindcol_long(pointer __pthis__,long long* v)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindcol_long(this,v)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindcol(this,v,sizeof(long long),SQL_C_SBIGINT);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindcol_ulong(pointer __pthis__,unsigned long long* v)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindcol_ulong(this,v)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindcol(this,v,sizeof(unsigned long long),SQL_C_UBIGINT);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindcol_dbl(pointer __pthis__,double* v)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindcol_dbl(this,v)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindcol(this,v,sizeof(double),SQL_C_DOUBLE);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindcol_str(pointer __pthis__,char* v,SQLLEN l)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindcol_str(this,v,l)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindcol(this,v,l,SQL_C_CHAR);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindcol_blob(pointer __pthis__,void* v,SQLLEN l)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindcol_blob(this,v,l)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindcol(this,v,l,SQL_C_BINARY);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindcol_time(pointer __pthis__,TIME_STRUCT* v)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindcol_time(this,v)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindcol(this,v,sizeof(TIME_STRUCT),SQL_C_TYPE_TIME);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindcol_date(pointer __pthis__,DATE_STRUCT* v)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindcol_date(this,v)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindcol(this,v,sizeof(DATE_STRUCT),SQL_C_TYPE_DATE);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindcol_ts(pointer __pthis__,TIMESTAMP_STRUCT* v)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindcol_ts(this,v)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindcol(this,v,sizeof(TIMESTAMP_STRUCT),SQL_C_TYPE_TIMESTAMP);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindparam_chr(pointer __pthis__,char* v)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindparam_chr(this,v)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindparam(this,v,sizeof(char),SQL_C_STINYINT);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindparam_uchr(pointer __pthis__,unsigned char* v)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindparam_uchr(this,v)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindparam(this,v,sizeof(unsigned char),SQL_C_UTINYINT);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindparam_short(pointer __pthis__,short* v)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindparam_short(this,v)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindparam(this,v,sizeof(short),SQL_C_SSHORT);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindparam_ushort(pointer __pthis__,unsigned short* v)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindparam_ushort(this,v)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindparam(this,v,sizeof(unsigned short),SQL_C_USHORT);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindparam_int(pointer __pthis__,int* v)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindparam_int(this,v)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindparam(this,v,sizeof(int),SQL_C_SLONG);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindparam_uint(pointer __pthis__,unsigned int* v)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindparam_uint(this,v)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindparam(this,v,sizeof(unsigned int),SQL_C_ULONG);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindparam_long(pointer __pthis__,long long* v)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindparam_long(this,v)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindparam(this,v,sizeof(long long),SQL_C_SBIGINT);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindparam_ulong(pointer __pthis__,unsigned long long* v)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindparam_ulong(this,v)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindparam(this,v,sizeof(unsigned long long),SQL_C_UBIGINT);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindparam_dbl(pointer __pthis__,double* v)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindparam_dbl(this,v)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindparam(this,v,sizeof(double),SQL_C_DOUBLE);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindparam_str(pointer __pthis__,char* v,SQLLEN l)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindparam_str(this,v,l)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindparam(this,v,l,SQL_C_CHAR);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindparam_blob(pointer __pthis__,void* v,SQLLEN l)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindparam_blob(this,v,l)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindparam(this,v,l,SQL_C_BINARY);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindparam_time(pointer __pthis__,TIME_STRUCT* v)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindparam_time(this,v)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindparam(this,v,sizeof(TIME_STRUCT),SQL_C_TYPE_TIME);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindparam_date(pointer __pthis__,DATE_STRUCT* v)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindparam_date(this,v)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindparam(this,v,sizeof(DATE_STRUCT),SQL_C_TYPE_DATE);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_bindparam_ts(pointer __pthis__,TIMESTAMP_STRUCT* v)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->bindparam_ts(this,v)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_odbc_statement_bindparam(this,v,sizeof(TIMESTAMP_STRUCT),SQL_C_TYPE_TIMESTAMP);
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_fetch(pointer __pthis__)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->fetch(this)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      SQLRETURN ret = SQLFetch(this->statement_handle_);
      









      return ret == SQL_SUCCESS;
    
#undef PM
#undef super
}
bool yaooc_odbc_statement_execute(pointer __pthis__)
{
yaooc_odbc_statement_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_statement_parent_class_table->execute(this)
#define PM(method,...) CTM((*yaooc_odbc_statement_parent_class_table),this,method,## __VA_ARGS__)


      SQLRETURN ret = SQLExecute(this->statement_handle_); 
      









      return ret==SQL_SUCCESS;
    
#undef PM
#undef super
}
yaooc_odbc_statement_class_table_t yaooc_odbc_statement_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_object_class_table,
.type_name_ = (const char*)"yaooc_odbc_statement_t",
.swap = (void(*)(pointer,pointer)) yaooc_odbc_statement_swap,
.bindcol_chr = (bool(*)(pointer,char*)) yaooc_odbc_statement_bindcol_chr,
.bindcol_uchr = (bool(*)(pointer,unsigned char*)) yaooc_odbc_statement_bindcol_uchr,
.bindcol_short = (bool(*)(pointer,short*)) yaooc_odbc_statement_bindcol_short,
.bindcol_ushort = (bool(*)(pointer,unsigned short*)) yaooc_odbc_statement_bindcol_ushort,
.bindcol_int = (bool(*)(pointer,int*)) yaooc_odbc_statement_bindcol_int,
.bindcol_uint = (bool(*)(pointer,unsigned int*)) yaooc_odbc_statement_bindcol_uint,
.bindcol_long = (bool(*)(pointer,long long*)) yaooc_odbc_statement_bindcol_long,
.bindcol_ulong = (bool(*)(pointer,unsigned long long*)) yaooc_odbc_statement_bindcol_ulong,
.bindcol_dbl = (bool(*)(pointer,double*)) yaooc_odbc_statement_bindcol_dbl,
.bindcol_str = (bool(*)(pointer,char*,SQLLEN)) yaooc_odbc_statement_bindcol_str,
.bindcol_blob = (bool(*)(pointer,void*,SQLLEN)) yaooc_odbc_statement_bindcol_blob,
.bindcol_time = (bool(*)(pointer,TIME_STRUCT*)) yaooc_odbc_statement_bindcol_time,
.bindcol_date = (bool(*)(pointer,DATE_STRUCT*)) yaooc_odbc_statement_bindcol_date,
.bindcol_ts = (bool(*)(pointer,TIMESTAMP_STRUCT*)) yaooc_odbc_statement_bindcol_ts,
.bindparam_chr = (bool(*)(pointer,char*)) yaooc_odbc_statement_bindparam_chr,
.bindparam_uchr = (bool(*)(pointer,unsigned char*)) yaooc_odbc_statement_bindparam_uchr,
.bindparam_short = (bool(*)(pointer,short*)) yaooc_odbc_statement_bindparam_short,
.bindparam_ushort = (bool(*)(pointer,unsigned short*)) yaooc_odbc_statement_bindparam_ushort,
.bindparam_int = (bool(*)(pointer,int*)) yaooc_odbc_statement_bindparam_int,
.bindparam_uint = (bool(*)(pointer,unsigned int*)) yaooc_odbc_statement_bindparam_uint,
.bindparam_long = (bool(*)(pointer,long long*)) yaooc_odbc_statement_bindparam_long,
.bindparam_ulong = (bool(*)(pointer,unsigned long long*)) yaooc_odbc_statement_bindparam_ulong,
.bindparam_dbl = (bool(*)(pointer,double*)) yaooc_odbc_statement_bindparam_dbl,
.bindparam_str = (bool(*)(pointer,char*,SQLLEN)) yaooc_odbc_statement_bindparam_str,
.bindparam_blob = (bool(*)(pointer,void*,SQLLEN)) yaooc_odbc_statement_bindparam_blob,
.bindparam_time = (bool(*)(pointer,TIME_STRUCT*)) yaooc_odbc_statement_bindparam_time,
.bindparam_date = (bool(*)(pointer,DATE_STRUCT*)) yaooc_odbc_statement_bindparam_date,
.bindparam_ts = (bool(*)(pointer,TIMESTAMP_STRUCT*)) yaooc_odbc_statement_bindparam_ts,
.fetch = (bool(*)(pointer)) yaooc_odbc_statement_fetch,
.execute = (bool(*)(pointer)) yaooc_odbc_statement_execute,
};
const type_info_t __yaooc_odbc_statement_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_odbc_statement_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_odbc_statement_default_ctor,
.dtor_=yaooc_odbc_statement_dtor,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_odbc_statement_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_odbc_statement_ti=&__yaooc_odbc_statement_ti;
static void yaooc_odbc_statement_ctor_private(pointer p,va_list args)
{
  yaooc_odbc_statement_pointer this=p;
  this->statement_handle_ = SQL_NULL_HANDLE;
	this->icol_=1;
}


void yaooc_odbc_connection_default_ctor(pointer __pthis__)
{
yaooc_odbc_connection_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_odbc_connection);



      this->connection_handle_ = SQL_NULL_HANDLE;
    
}
void yaooc_odbc_connection_dtor(pointer __pthis__)
{
yaooc_odbc_connection_pointer this=__pthis__;(void)this;


      M(this,disconnect);
    
}
void yaooc_odbc_connection_ctor_connect_str(pointer __pthis,va_list __con_args__){
yaooc_odbc_connection_pointer this=__pthis;(void)this;
const char* connect_str = va_arg(__con_args__,const char*);

call_default_ctor_static(this,yaooc_odbc_connection);


      M(this,connect,connect_str);
    
}
yaooc_odbc_statement_t* yaooc_odbc_connection_exec_direct(pointer __pthis__,const char* str)
{
yaooc_odbc_connection_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_connection_parent_class_table->exec_direct(this,str)
#define PM(method,...) CTM((*yaooc_odbc_connection_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_odbc_statement_t *stmt = new_ctor(yaooc_odbc_statement,yaooc_odbc_statement_ctor_private,NULL);
      SQLHSTMT handle;
      if(SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_STMT, this->connection_handle_, &handle))) {
        SQLRETURN rc= SQLExecDirect(handle,(SQLCHAR*)str,SQL_NTS);
        


        if(SQL_SUCCEEDED(rc)) {
          


          yaooc_odbc_statement_set_handle(stmt,handle);
        } else {
    





          SQLCloseCursor(handle);
          SQLFreeHandle(SQL_HANDLE_STMT,handle);
        }
      }
      return stmt;
    
#undef PM
#undef super
}
yaooc_odbc_statement_t* yaooc_odbc_connection_prepare(pointer __pthis__,const char* str)
{
yaooc_odbc_connection_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_connection_parent_class_table->prepare(this,str)
#define PM(method,...) CTM((*yaooc_odbc_connection_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_odbc_statement_t *stmt = new_ctor(yaooc_odbc_statement,yaooc_odbc_statement_ctor_private,NULL);
      SQLHSTMT handle;
      if(SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_STMT, this->connection_handle_, &handle))) {
        SQLRETURN rc= SQLPrepare(handle,(SQLCHAR*)str,SQL_NTS);
        


        if(SQL_SUCCEEDED(rc)) {
          


          yaooc_odbc_statement_set_handle(stmt,handle);
        } else {
          





          SQLCloseCursor(handle);
          SQLFreeHandle(SQL_HANDLE_STMT,handle);
        }
      }
      return stmt;
    
#undef PM
#undef super
}
void yaooc_odbc_connection_connect(pointer __pthis__,const char* str)
{
yaooc_odbc_connection_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_connection_parent_class_table->connect(this,str)
#define PM(method,...) CTM((*yaooc_odbc_connection_parent_class_table),this,method,## __VA_ARGS__)


      M(this,disconnect);
      SQLRETURN rc = SQLAllocHandle(SQL_HANDLE_DBC, yaooc_odbc_environment_henv_, &this->connection_handle_);
      if(rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) {
        yaooc_odbc_connection_auto_commit(this,false); 
        rc=SQLDriverConnect(this->connection_handle_, NULL, (SQLCHAR*)str, SQL_NTS,
            NULL, 0, NULL, SQL_DRIVER_NOPROMPT);
      }
    


      if(rc != SQL_SUCCESS) {
    





        M(this,disconnect);
      }
    
#undef PM
#undef super
}
void yaooc_odbc_connection_disconnect(pointer __pthis__)
{
yaooc_odbc_connection_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_connection_parent_class_table->disconnect(this)
#define PM(method,...) CTM((*yaooc_odbc_connection_parent_class_table),this,method,## __VA_ARGS__)


      if(this->connection_handle_ != SQL_NULL_HANDLE) {
        M(this,commit);
        SQLDisconnect(this->connection_handle_);
        SQLFreeHandle(SQL_HANDLE_DBC, this->connection_handle_);
        this->connection_handle_=SQL_NULL_HANDLE;
      }
    
#undef PM
#undef super
}
void yaooc_odbc_connection_auto_commit(pointer __pthis__,bool on)
{
yaooc_odbc_connection_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_connection_parent_class_table->auto_commit(this,on)
#define PM(method,...) CTM((*yaooc_odbc_connection_parent_class_table),this,method,## __VA_ARGS__)


      if(this->connection_handle_ != SQL_NULL_HANDLE)
        SQLSetConnectAttr(this->connection_handle_,SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)(long)(on ? SQL_TRUE : SQL_FALSE), 0);
    
#undef PM
#undef super
}
void yaooc_odbc_connection_commit(pointer __pthis__)
{
yaooc_odbc_connection_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_connection_parent_class_table->commit(this)
#define PM(method,...) CTM((*yaooc_odbc_connection_parent_class_table),this,method,## __VA_ARGS__)


      if(this->connection_handle_ != SQL_NULL_HANDLE)
        SQLEndTran(SQL_HANDLE_DBC,this->connection_handle_,SQL_COMMIT);
    
#undef PM
#undef super
}
void yaooc_odbc_connection_rollback(pointer __pthis__)
{
yaooc_odbc_connection_pointer this=__pthis__;(void)this;
#define super() yaooc_odbc_connection_parent_class_table->rollback(this)
#define PM(method,...) CTM((*yaooc_odbc_connection_parent_class_table),this,method,## __VA_ARGS__)


      if(this->connection_handle_ != SQL_NULL_HANDLE)
        SQLEndTran(SQL_HANDLE_DBC,this->connection_handle_,SQL_ROLLBACK);
    
#undef PM
#undef super
}
yaooc_odbc_connection_class_table_t yaooc_odbc_connection_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_object_class_table,
.type_name_ = (const char*)"yaooc_odbc_connection_t",
.swap = (void(*)(pointer,pointer)) yaooc_odbc_connection_swap,
.exec_direct = (yaooc_odbc_statement_t*(*)(pointer,const char*)) yaooc_odbc_connection_exec_direct,
.prepare = (yaooc_odbc_statement_t*(*)(pointer,const char*)) yaooc_odbc_connection_prepare,
.connect = (void(*)(pointer,const char*)) yaooc_odbc_connection_connect,
.disconnect = (void(*)(pointer)) yaooc_odbc_connection_disconnect,
.auto_commit = (void(*)(pointer,bool)) yaooc_odbc_connection_auto_commit,
.commit = (void(*)(pointer)) yaooc_odbc_connection_commit,
.rollback = (void(*)(pointer)) yaooc_odbc_connection_rollback,
};
const type_info_t __yaooc_odbc_connection_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_odbc_connection_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_odbc_connection_default_ctor,
.dtor_=yaooc_odbc_connection_dtor,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_odbc_connection_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_odbc_connection_ti=&__yaooc_odbc_connection_ti;
