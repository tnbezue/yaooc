/* Begin YAOOCPP output */

#include <yaooc/odbc.h>
#include <stdio.h>

MINI_MAP_IMPLEMENTATION(yaooc_string,yaooc_string,map_odbc_string_string)

/* Type Info implemmentation for yaooc_odbc_exception */
/* Constructors implementation for yaooc_odbc_exception */

/* Private methods implementation for yaooc_odbc_exception */

/* Protected implementation for yaooc_odbc_exception */

/* Table implementation for yaooc_odbc_exception */

/* Class table definition for yaooc_odbc_exception */
yaooc_odbc_exception_class_table_t yaooc_odbc_exception_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_exception_class_table,
  .type_name_ = (const char*) "yaooc_odbc_exception_t",
  .swap = (void(*)(pointer, pointer)) yaooc_odbc_exception_swap,
  .what = (const char*(*)(const_pointer)) yaooc_odbc_exception_what,
};

/* Type info structure for yaooc_odbc_exception */
DEFINE_TYPE_INFO(yaooc_odbc_exception,N,N,N,N,N,N,N,Y,yaooc_exception);


/* Private variables implementation for yaooc_odbc_environment */
static SQLHENV yaooc_odbc_environment_henv_ = SQL_NULL_HANDLE;

/* Private methods prototypes for yaooc_odbc_environment */

/* Type Info implemmentation for yaooc_odbc_environment */
void yaooc_odbc_environment_default_ctor(pointer p)
{
  yaooc_odbc_environment_pointer this=p;
	// only one handle needed per application.
  if(yaooc_odbc_environment_henv_ == SQL_NULL_HANDLE) {
		/* Allocate an environment handle */
		if(SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &yaooc_odbc_environment_henv_) == SQL_SUCCESS) {
			/* We want ODBC 3 support */
			if(SQLSetEnvAttr(yaooc_odbc_environment_henv_, SQL_ATTR_ODBC_VERSION, (void *) SQL_OV_ODBC3, 0) != SQL_SUCCESS) {
				yaooc_odbc_environment_dtor(this);
				yaooc_odbc_environment_henv_=SQL_NULL_HANDLE;
			}
		}
	} else {
    /* ** FIX ME ** should throw exception */
    puts("Only one ODBC environment allowed");
    exit(1);
  }
}

void yaooc_odbc_environment_dtor(pointer p)
{
	if(yaooc_odbc_environment_henv_ != SQL_NULL_HANDLE)
		SQLFreeHandle(SQL_HANDLE_ENV,yaooc_odbc_environment_henv_);
}

/* Constructors implementation for yaooc_odbc_environment */

/* Private methods implementation for yaooc_odbc_environment */

/* Protected implementation for yaooc_odbc_environment */
yaooc_odbc_environment_t* yaooc_odbc_environment_current_environment(pointer p)
{
	return yaooc_odbc_environment_henv_;
}

map_odbc_string_string_t* yaooc_odbc_environment_get_drivers(pointer p)
{
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
//		if (ret == SQL_SUCCESS_WITH_INFO) printf("\tdata truncation\n");
			ret = SQLDrivers(yaooc_odbc_environment_henv_,SQL_FETCH_NEXT,
				driver, sizeof(driver), &driver_ret,
				attr, sizeof(attr), &attr_ret);
  }
	deletep(&key,yaooc_string);
	deletep(&value,yaooc_string);
	return drivers;
}

map_odbc_string_string_t* yaooc_odbc_environment_get_sources(pointer p)
{
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
//		printf("%s - %s\n", dsn, desc);
		M(&key,set,dsn);
		M(&value,set,desc);
		M(sources,insert,&key,&value);
//		(*sources)[string_t(reinterpret_cast<char*>(dsn))]=desc;
//		if (ret == SQL_SUCCESS_WITH_INFO) printf("\tdata truncation\n");
		ret = SQLDataSources(yaooc_odbc_environment_henv_,SQL_FETCH_NEXT,(SQLCHAR*)dsn, sizeof(dsn),
					&dsn_ret,(SQLCHAR*)desc, sizeof(desc), &desc_ret);
	}
	deletep(&key,yaooc_string);
	deletep(&value,yaooc_string);
	return sources;
}


/* Table implementation for yaooc_odbc_environment */
SQLHENV yaooc_odbc_environment_env(pointer p)
{
	return yaooc_odbc_environment_henv_;
}


/* Class table definition for yaooc_odbc_environment */
yaooc_odbc_environment_class_table_t yaooc_odbc_environment_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "yaooc_odbc_environment_t",
  .swap = (void(*)(pointer, pointer)) yaooc_odbc_environment_swap,
  .env = (SQLHENV(*)(pointer)) yaooc_odbc_environment_env,
};

/* Type info structure for yaooc_odbc_environment */
DEFINE_TYPE_INFO(yaooc_odbc_environment,Y,Y,N,N,N,N,N,Y,yaooc_object);

/* Private variables implementation for yaooc_odbc_value */

/* Private methods prototypes for yaooc_odbc_value */

/* Type Info implemmentation for yaooc_odbc_value */
/*
void yaooc_odbc_value_default_ctor(pointer p)
{
  yaooc_odbc_value_pointer this=p;
}

void yaooc_odbc_value_dtor(pointer p)
{
  yaooc_odbc_value_pointer this=p;
}

void yaooc_odbc_value_copy_ctor(pointer p,const_pointer s)
{
  yaooc_odbc_value_default_ctor(p);
  yaooc_odbc_value_assign(p,s);
}

void yaooc_odbc_value_assign(pointer p,const_pointer s)
{
  yaooc_odbc_value_pointer this=p;
  yaooc_odbc_value_const_pointer src=s;
}
*/
/* Constructors implementation for yaooc_odbc_value */

/* Private methods implementation for yaooc_odbc_value */

/* Protected implementation for yaooc_odbc_value */

/* Table implementation for yaooc_odbc_value */
SQLSMALLINT yaooc_odbc_value_c_data_type(const_pointer p)
{
  return 0; // Maybe should be SQL_C_DEFAULT
}

SQLLEN yaooc_odbc_value_column_size(const_pointer p)
{
  return 0;
}

void* yaooc_odbc_value_data(pointer p)
{
  return NULL;
}


/* Class table definition for yaooc_odbc_value */
yaooc_odbc_value_class_table_t yaooc_odbc_value_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "yaooc_odbc_value_t",
  .swap = (void(*)(pointer, pointer)) yaooc_odbc_value_swap,
  .c_data_type = (SQLSMALLINT(*)(const_pointer)) yaooc_odbc_value_c_data_type,
  .column_size = (SQLLEN(*)(const_pointer)) yaooc_odbc_value_column_size,
  .data = (void*(*)(pointer)) yaooc_odbc_value_data,
};

/* Type info structure for yaooc_odbc_value */
DEFINE_TYPE_INFO(yaooc_odbc_value,N,N,N,N,N,N,N,Y,yaooc_object);

/* Private variables implementation for yaooc_odbc_integer */

/* Private methods prototypes for yaooc_odbc_integer */

/* Type Info implemmentation for yaooc_odbc_integer */
void yaooc_odbc_integer_default_ctor(pointer p)
{
  yaooc_odbc_integer_pointer this=p;
//  yaooc_odbc_value_default_ctor(this);
  this->value_ = 0;
}

void yaooc_odbc_integer_copy_ctor(pointer p,const_pointer s)
{
//  yaooc_odbc_integer_default_ctor(p);
  yaooc_odbc_integer_assign(p,s);
}

void yaooc_odbc_integer_assign(pointer p,const_pointer s)
{
  yaooc_odbc_integer_pointer this=p;
  yaooc_odbc_integer_const_pointer src=s;
//  yaooc_odbc_value_assign(this,src);
  this->value_ = src->value_;
}

/* Constructors implementation for yaooc_odbc_integer */

/* Private methods implementation for yaooc_odbc_integer */

/* Protected implementation for yaooc_odbc_integer */

/* Table implementation for yaooc_odbc_integer */
SQLSMALLINT yaooc_odbc_integer_c_data_type(const_pointer p)
{
  return SQL_C_SBIGINT;
}

SQLLEN yaooc_odbc_integer_column_size(const_pointer p)
{
  return sizeof(long long);
}

void* yaooc_odbc_integer_data(pointer p)
{
  yaooc_odbc_integer_pointer this=p;
  return &this->value_;
}

long long yaooc_odbc_integer_get(const_pointer p)
{
  yaooc_odbc_integer_const_pointer this=p;
  return this->value_;
}

void yaooc_odbc_integer_set(pointer p,long long v)
{
  yaooc_odbc_integer_pointer this=p;
	this->value_=v;
}


/* Class table definition for yaooc_odbc_integer */
yaooc_odbc_integer_class_table_t yaooc_odbc_integer_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_odbc_value_class_table,
  .type_name_ = (const char*) "yaooc_odbc_integer_t",
  .swap = (void(*)(pointer, pointer)) yaooc_odbc_integer_swap,
  .c_data_type = (SQLSMALLINT(*)(const_pointer)) yaooc_odbc_integer_c_data_type,
  .column_size = (SQLLEN(*)(const_pointer)) yaooc_odbc_integer_column_size,
  .data = (void*(*)(pointer)) yaooc_odbc_integer_data,
  .get = (long long(*)(const_pointer)) yaooc_odbc_integer_get,
  .set = (void(*)(pointer, long long)) yaooc_odbc_integer_set,
};

/* Type info structure for yaooc_odbc_integer */
DEFINE_TYPE_INFO(yaooc_odbc_integer,Y,N,Y,Y,N,N,N,Y,yaooc_odbc_value);

/* Private variables implementation for yaooc_odbc_unsigned_integer */

/* Private methods prototypes for yaooc_odbc_unsigned_integer */

/* Type Info implemmentation for yaooc_odbc_unsigned_integer */
void yaooc_odbc_unsigned_integer_default_ctor(pointer p)
{
  yaooc_odbc_unsigned_integer_pointer this=p;
//  yaooc_odbc_value_default_ctor(this);
  this->value_ = 0;
}

void yaooc_odbc_unsigned_integer_copy_ctor(pointer p,const_pointer s)
{
//  yaooc_odbc_unsigned_integer_default_ctor(p);
  yaooc_odbc_unsigned_integer_assign(p,s);
}

void yaooc_odbc_unsigned_integer_assign(pointer p,const_pointer s)
{
  yaooc_odbc_unsigned_integer_pointer this=p;
  yaooc_odbc_unsigned_integer_const_pointer src=s;
//  yaooc_odbc_value_assign(this,src);
  this->value_ = src->value_;
}

/* Constructors implementation for yaooc_odbc_unsigned_integer */

/* Private methods implementation for yaooc_odbc_unsigned_integer */

/* Protected implementation for yaooc_odbc_unsigned_integer */

/* Table implementation for yaooc_odbc_unsigned_integer */
SQLSMALLINT yaooc_odbc_unsigned_integer_c_data_type(const_pointer p)
{
  return SQL_C_UBIGINT;
}

SQLLEN yaooc_odbc_unsigned_integer_column_size(const_pointer p)
{
  return sizeof(unsigned long long);
}

void* yaooc_odbc_unsigned_integer_data(pointer p)
{
  yaooc_odbc_unsigned_integer_pointer this=p;
  return &this->value_;
}

unsigned long long yaooc_odbc_unsigned_integer_get(const_pointer p)
{
  yaooc_odbc_unsigned_integer_const_pointer this=p;
	return this->value_;
}

void yaooc_odbc_unsigned_integer_set(pointer p,unsigned long long v)
{
  yaooc_odbc_unsigned_integer_pointer this=p;
	this->value_=v;
}


/* Class table definition for yaooc_odbc_unsigned_integer */
yaooc_odbc_unsigned_integer_class_table_t yaooc_odbc_unsigned_integer_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_odbc_value_class_table,
  .type_name_ = (const char*) "yaooc_odbc_unsigned_integer_t",
  .swap = (void(*)(pointer, pointer)) yaooc_odbc_unsigned_integer_swap,
  .c_data_type = (SQLSMALLINT(*)(const_pointer)) yaooc_odbc_unsigned_integer_c_data_type,
  .column_size = (SQLLEN(*)(const_pointer)) yaooc_odbc_unsigned_integer_column_size,
  .data = (void*(*)(pointer)) yaooc_odbc_unsigned_integer_data,
  .get = (unsigned long long(*)(const_pointer)) yaooc_odbc_unsigned_integer_get,
  .set = (void(*)(pointer, unsigned long long)) yaooc_odbc_unsigned_integer_set,
};

/* Type info structure for yaooc_odbc_unsigned_integer */
DEFINE_TYPE_INFO(yaooc_odbc_unsigned_integer,Y,N,Y,Y,N,N,N,Y,yaooc_odbc_value);

/* Private variables implementation for yaooc_odbc_real */

/* Private methods prototypes for yaooc_odbc_real */

/* Type Info implemmentation for yaooc_odbc_real */
void yaooc_odbc_real_default_ctor(pointer p)
{
  yaooc_odbc_real_pointer this=p;
//  yaooc_odbc_value_default_ctor(this);
  this->value_ = 0;
}

void yaooc_odbc_real_copy_ctor(pointer p,const_pointer s)
{
//  yaooc_odbc_real_default_ctor(p);
  yaooc_odbc_real_assign(p,s);
}

void yaooc_odbc_real_assign(pointer p,const_pointer s)
{
  yaooc_odbc_real_pointer this=p;
  yaooc_odbc_real_const_pointer src=s;
//  yaooc_odbc_value_assign(this,src);
  this->value_ = src->value_;
}

/* Constructors implementation for yaooc_odbc_real */

/* Private methods implementation for yaooc_odbc_real */

/* Protected implementation for yaooc_odbc_real */

/* Table implementation for yaooc_odbc_real */
SQLSMALLINT yaooc_odbc_real_c_data_type(const_pointer p)
{
  return SQL_C_DOUBLE;
}

SQLLEN yaooc_odbc_real_column_size(const_pointer p)
{
  return sizeof(double);
}

void* yaooc_odbc_real_data(pointer p)
{
  yaooc_odbc_real_pointer this=p;
	return &this->value_;
}

double yaooc_odbc_real_get(const_pointer p)
{
  yaooc_odbc_real_const_pointer this=p;
	return this->value_;
}

void yaooc_odbc_real_set(pointer p,double v)
{
  yaooc_odbc_real_pointer this=p;
	this->value_=v;
}


/* Class table definition for yaooc_odbc_real */
yaooc_odbc_real_class_table_t yaooc_odbc_real_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_odbc_value_class_table,
  .type_name_ = (const char*) "yaooc_odbc_real_t",
  .swap = (void(*)(pointer, pointer)) yaooc_odbc_real_swap,
  .c_data_type = (SQLSMALLINT(*)(const_pointer)) yaooc_odbc_real_c_data_type,
  .column_size = (SQLLEN(*)(const_pointer)) yaooc_odbc_real_column_size,
  .data = (void*(*)(pointer)) yaooc_odbc_real_data,
  .get = (double(*)(const_pointer)) yaooc_odbc_real_get,
  .set = (void(*)(pointer, double)) yaooc_odbc_real_set,
};

/* Type info structure for yaooc_odbc_real */
DEFINE_TYPE_INFO(yaooc_odbc_real,Y,N,Y,Y,N,N,N,Y,yaooc_odbc_value);

/* Private variables implementation for yaooc_odbc_string */

/* Private methods prototypes for yaooc_odbc_string */

/* Type Info implemmentation for yaooc_odbc_string */
void yaooc_odbc_string_default_ctor(pointer p)
{
  yaooc_odbc_string_pointer this=p;
//  yaooc_odbc_value_default_ctor(this);
  this->size_=256;
  this->value_ = MALLOC(256);
}

void yaooc_odbc_string_dtor(pointer p)
{
  yaooc_odbc_string_pointer this=p;
  if(this->value_)
     FREE(this->value_);
  this->value_ = NULL;
}

void yaooc_odbc_string_copy_ctor(pointer p,const_pointer s)
{
  yaooc_odbc_string_default_ctor(p);
  yaooc_odbc_string_assign(p,s);
}

void yaooc_odbc_string_assign(pointer p,const_pointer s)
{
  yaooc_odbc_string_pointer this=p;
  yaooc_odbc_string_const_pointer src=s;
//  yaooc_odbc_value_assign(this,src);
  if(this->size_ != src->size_) {
		FREE(this->value_);
		this->value_=malloc(this->size_=src->size_);
	}
  strncpy(this->value_,src->value_,this->size_);
	this->value_[this->size_-1]=0;
}

/* Constructors implementation for yaooc_odbc_string */
void yaooc_odbc_string_size(pointer p,va_list args)
{
  yaooc_odbc_string_pointer this=p;
	this->size_= va_arg(args, size_t);
	this->value_=malloc(this->size_);
}


/* Private methods implementation for yaooc_odbc_string */

/* Protected implementation for yaooc_odbc_string */

/* Table implementation for yaooc_odbc_string */
SQLSMALLINT yaooc_odbc_string_c_data_type(const_pointer p)
{
  return SQL_C_CHAR;
}

SQLLEN yaooc_odbc_string_column_size(const_pointer p)
{
  yaooc_odbc_string_const_pointer this=p;
  return this->size_;
}

void* yaooc_odbc_string_data(pointer p)
{
  yaooc_odbc_string_pointer this=p;
  return this->value_;
}

const char* yaooc_odbc_string_get(const_pointer p)
{
  yaooc_odbc_string_const_pointer this=p;
  return this->value_;
}

void yaooc_odbc_string_setn(pointer p,const char* v,size_t n)
{
  yaooc_odbc_string_pointer this=p;
	n = n < this->size_ ? n : this->size_;
	strncpy(this->value_,v,n);
	this->value_[n]=0;
}

void yaooc_odbc_string_set(pointer p,const char* v)
{
	yaooc_odbc_string_setn(p,v,SIZE_MAX);
/*  yaooc_odbc_string_pointer this=p;
	n = n < this->size_ ? n : this->size_;
	strncpy(this->value_,v,n);
	this->value_[n]=0;*/
}


/* Class table definition for yaooc_odbc_string */
yaooc_odbc_string_class_table_t yaooc_odbc_string_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_odbc_value_class_table,
  .type_name_ = (const char*) "yaooc_odbc_string_t",
  .swap = (void(*)(pointer, pointer)) yaooc_odbc_string_swap,
  .c_data_type = (SQLSMALLINT(*)(const_pointer)) yaooc_odbc_string_c_data_type,
  .column_size = (SQLLEN(*)(const_pointer)) yaooc_odbc_string_column_size,
  .data = (void*(*)(pointer)) yaooc_odbc_string_data,
  .get = (const char*(*)(const_pointer)) yaooc_odbc_string_get,
  .set = (void(*)(pointer, const char*)) yaooc_odbc_string_set,
  .setn = (void(*)(pointer, const char*, size_t)) yaooc_odbc_string_set,
};

/* Type info structure for yaooc_odbc_string */
DEFINE_TYPE_INFO(yaooc_odbc_string,Y,Y,Y,Y,N,N,N,Y,yaooc_odbc_value);

/* Private variables implementation for yaooc_odbc_blob */

/* Private methods prototypes for yaooc_odbc_blob */

/* Type Info implemmentation for yaooc_odbc_blob */
void yaooc_odbc_blob_default_ctor(pointer p)
{
  yaooc_odbc_blob_pointer this=p;
//  yaooc_odbc_value_default_ctor(this);
	this->size_=1024;
  this->value_ = malloc(1024);
}

void yaooc_odbc_blob_dtor(pointer p)
{
  yaooc_odbc_blob_pointer this=p;
  if(this->value_)
     FREE(this->value_);
  this->value_ = NULL;
}

void yaooc_odbc_blob_copy_ctor(pointer p,const_pointer s)
{
  yaooc_odbc_blob_default_ctor(p);
  yaooc_odbc_blob_assign(p,s);
}

void yaooc_odbc_blob_assign(pointer p,const_pointer s)
{
  yaooc_odbc_blob_pointer this=p;
  yaooc_odbc_blob_const_pointer src=s;
//  yaooc_odbc_value_assign(this,src);
  if(this->size_ != src->size_) {
		FREE(this->value_);
		this->value_=malloc(this->size_=src->size_);
	}
  memcpy(this->value_,src->value_,this->size_);
}

/* Constructors implementation for yaooc_odbc_blob */
void yaooc_odbc_blob_size(pointer p,va_list args)
{
	yaooc_odbc_blob_pointer this=p;
	this->size_ = va_arg(args, size_t);
	this->value_=malloc(this->size_);
}


/* Private methods implementation for yaooc_odbc_blob */

/* Protected implementation for yaooc_odbc_blob */

/* Table implementation for yaooc_odbc_blob */
SQLSMALLINT yaooc_odbc_blob_c_data_type(const_pointer p)
{
  return SQL_C_CHAR;
}

SQLLEN yaooc_odbc_blob_column_size(const_pointer p)
{
  yaooc_odbc_blob_const_pointer this=p;
	return this->size_;
}

void* yaooc_odbc_blob_data(pointer p)
{
  yaooc_odbc_blob_pointer this=p;
	return this->value_;
}

void* yaooc_odbc_blob_get(const_pointer p)
{
  yaooc_odbc_blob_const_pointer this=p;
	return this->value_;
}

void yaooc_odbc_blob_setn(pointer p,void* v,size_t n)
{
  yaooc_odbc_blob_pointer this=p;
	memcpy(this->value_,v,n<this->size_?n:this->size_);
}


/* Class table definition for yaooc_odbc_blob */
yaooc_odbc_blob_class_table_t yaooc_odbc_blob_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_odbc_value_class_table,
  .type_name_ = (const char*) "yaooc_odbc_blob_t",
  .swap = (void(*)(pointer, pointer)) yaooc_odbc_blob_swap,
  .c_data_type = (SQLSMALLINT(*)(const_pointer)) yaooc_odbc_blob_c_data_type,
  .column_size = (SQLLEN(*)(const_pointer)) yaooc_odbc_blob_column_size,
  .data = (void*(*)(pointer)) yaooc_odbc_blob_data,
  .get = (void*(*)(const_pointer)) yaooc_odbc_blob_get,
  .setn = (void(*)(pointer, void*, size_t)) yaooc_odbc_blob_setn,
};

/* Type info structure for yaooc_odbc_blob */
DEFINE_TYPE_INFO(yaooc_odbc_blob,Y,Y,Y,Y,N,N,N,Y,yaooc_odbc_value);

/* Private variables implementation for yaooc_odbc_time */

/* Private methods prototypes for yaooc_odbc_time */

/* Type Info implemmentation for yaooc_odbc_time */
void yaooc_odbc_time_default_ctor(pointer p)
{
  yaooc_odbc_time_pointer this=p;
//  yaooc_odbc_value_default_ctor(this);
  memset(&this->value_,0,sizeof(TIME_STRUCT));
}

void yaooc_odbc_time_copy_ctor(pointer p,const_pointer s)
{
//  yaooc_odbc_time_default_ctor(p);
  yaooc_odbc_time_assign(p,s);
}

void yaooc_odbc_time_assign(pointer p,const_pointer s)
{
  yaooc_odbc_time_pointer this=p;
  yaooc_odbc_time_const_pointer src=s;
//  yaooc_odbc_value_assign(this,src);
  this->value_ = src->value_;
}

/* Constructors implementation for yaooc_odbc_time */

/* Private methods implementation for yaooc_odbc_time */

/* Protected implementation for yaooc_odbc_time */

/* Table implementation for yaooc_odbc_time */
SQLSMALLINT yaooc_odbc_time_c_data_type(const_pointer p)
{
	return SQL_C_TYPE_TIME;
}

SQLLEN yaooc_odbc_time_column_size(const_pointer p)
{
	return sizeof(TIME_STRUCT);
}

void* yaooc_odbc_time_data(pointer p)
{
  yaooc_odbc_time_pointer this=p;
  return &this->value_;
}

TIME_STRUCT yaooc_odbc_time_get(const_pointer p)
{
  yaooc_odbc_time_const_pointer this=p;
	return this->value_;
}

void yaooc_odbc_time_set(pointer p,TIME_STRUCT v)
{
  yaooc_odbc_time_pointer this=p;
	this->value_ = v;
}

int yaooc_odbc_time_get_secs(const_pointer p)
{
  yaooc_odbc_time_const_pointer this=p;
  return this->value_.hour*3600 + this->value_.minute*60 + this->value_.second;
}

void yaooc_odbc_time_set_secs(pointer p,int secs)
{
  yaooc_odbc_time_pointer this=p;
	this->value_.minute = secs / 60;
	this->value_.second = secs % 60;
	this->value_.hour = this->value_.minute / 60;
	this->value_.minute %= 60;
}


/* Class table definition for yaooc_odbc_time */
yaooc_odbc_time_class_table_t yaooc_odbc_time_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_odbc_value_class_table,
  .type_name_ = (const char*) "yaooc_odbc_time_t",
  .swap = (void(*)(pointer, pointer)) yaooc_odbc_time_swap,
  .c_data_type = (SQLSMALLINT(*)(const_pointer)) yaooc_odbc_time_c_data_type,
  .column_size = (SQLLEN(*)(const_pointer)) yaooc_odbc_time_column_size,
  .data = (void*(*)(pointer)) yaooc_odbc_time_data,
  .get = (TIME_STRUCT(*)(const_pointer)) yaooc_odbc_time_get,
  .set = (void(*)(pointer, TIME_STRUCT)) yaooc_odbc_time_set,
  .get_secs = (int(*)(const_pointer)) yaooc_odbc_time_get_secs,
  .set_secs = (void(*)(pointer, int)) yaooc_odbc_time_set_secs,
};

/* Type info structure for yaooc_odbc_time */
DEFINE_TYPE_INFO(yaooc_odbc_time,Y,N,Y,Y,N,N,N,Y,yaooc_odbc_value);

/* Private variables implementation for yaooc_odbc_date */

/* Private methods prototypes for yaooc_odbc_date */

/* Type Info implemmentation for yaooc_odbc_date */
void yaooc_odbc_date_default_ctor(pointer p)
{
  yaooc_odbc_date_pointer this=p;
//  yaooc_odbc_value_default_ctor(this);
  memset(&this->value_,0,sizeof(DATE_STRUCT));
}

void yaooc_odbc_date_copy_ctor(pointer p,const_pointer s)
{
//  yaooc_odbc_date_default_ctor(p);
  yaooc_odbc_date_assign(p,s);
}

void yaooc_odbc_date_assign(pointer p,const_pointer s)
{
  yaooc_odbc_date_pointer this=p;
  yaooc_odbc_date_const_pointer src=s;
//  yaooc_odbc_value_assign(this,src);
  this->value_ = src->value_;
}

/* Constructors implementation for yaooc_odbc_date */

/* Private methods implementation for yaooc_odbc_date */

/* Protected implementation for yaooc_odbc_date */

/* Table implementation for yaooc_odbc_date */
SQLSMALLINT yaooc_odbc_date_c_data_type(const_pointer p)
{
	return SQL_C_TYPE_DATE;
}

SQLLEN yaooc_odbc_date_column_size(const_pointer p)
{
  return sizeof(DATE_STRUCT);
}

void* yaooc_odbc_date_data(pointer p)
{
  yaooc_odbc_date_pointer this=p;
  return &this->value_;
}

DATE_STRUCT yaooc_odbc_date_get(const_pointer p)
{
  yaooc_odbc_date_const_pointer this=p;
  return this->value_;
}

void yaooc_odbc_date_set(pointer p,DATE_STRUCT v)
{
  yaooc_odbc_date_pointer this=p;
	this->value_=v;
}

time_t yaooc_odbc_date_get_time(const_pointer p)
{
  yaooc_odbc_date_const_pointer this=p;
	struct tm tm;
	memset(&tm,0,sizeof(struct tm));
	tm.tm_year = this->value_.year-1900;
	tm.tm_mday=this->value_.day;
	tm.tm_mon=this->value_.month-1;
	tm.tm_isdst=-1;
	return mktime(&tm);
}

void yaooc_odbc_date_set_time(pointer p,time_t t)
{
  yaooc_odbc_date_pointer this=p;
	struct tm *tm = localtime(&t);
	this->value_.year = tm->tm_year + 1900;
	this->value_.day = tm->tm_mday;
	this->value_.month=tm->tm_mon+1;
}


/* Class table definition for yaooc_odbc_date */
yaooc_odbc_date_class_table_t yaooc_odbc_date_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_odbc_value_class_table,
  .type_name_ = (const char*) "yaooc_odbc_date_t",
  .swap = (void(*)(pointer, pointer)) yaooc_odbc_date_swap,
  .c_data_type = (SQLSMALLINT(*)(const_pointer)) yaooc_odbc_date_c_data_type,
  .column_size = (SQLLEN(*)(const_pointer)) yaooc_odbc_date_column_size,
  .data = (void*(*)(pointer)) yaooc_odbc_date_data,
  .get = (DATE_STRUCT(*)(const_pointer)) yaooc_odbc_date_get,
  .set = (void(*)(pointer, DATE_STRUCT)) yaooc_odbc_date_set,
  .get_time = (time_t(*)(const_pointer)) yaooc_odbc_date_get_time,
  .set_time = (void(*)(pointer, time_t)) yaooc_odbc_date_set_time,
};

/* Type info structure for yaooc_odbc_date */
DEFINE_TYPE_INFO(yaooc_odbc_date,Y,N,Y,Y,N,N,N,Y,yaooc_odbc_value);

/* Private variables implementation for yaooc_odbc_timestamp */

/* Private methods prototypes for yaooc_odbc_timestamp */

/* Type Info implemmentation for yaooc_odbc_timestamp */
void yaooc_odbc_timestamp_default_ctor(pointer p)
{
  yaooc_odbc_timestamp_pointer this=p;
//  yaooc_odbc_value_default_ctor(this);
  memset(&this->value_,0,sizeof(TIMESTAMP_STRUCT));
}

void yaooc_odbc_timestamp_copy_ctor(pointer p,const_pointer s)
{
//  yaooc_odbc_timestamp_default_ctor(p);
  yaooc_odbc_timestamp_assign(p,s);
}

void yaooc_odbc_timestamp_assign(pointer p,const_pointer s)
{
  yaooc_odbc_timestamp_pointer this=p;
  yaooc_odbc_timestamp_const_pointer src=s;
//  yaooc_odbc_value_assign(this,src);
  this->value_ = src->value_;
}

/* Constructors implementation for yaooc_odbc_timestamp */

/* Private methods implementation for yaooc_odbc_timestamp */

/* Protected implementation for yaooc_odbc_timestamp */

/* Table implementation for yaooc_odbc_timestamp */
SQLSMALLINT yaooc_odbc_timestamp_c_data_type(const_pointer p)
{
  return SQL_C_TYPE_TIMESTAMP;
}

SQLLEN yaooc_odbc_timestamp_column_size(const_pointer p)
{
  return sizeof(TIMESTAMP_STRUCT);
}

void* yaooc_odbc_timestamp_data(pointer p)
{
  yaooc_odbc_timestamp_pointer this=p;
  return &this->value_;
}

TIMESTAMP_STRUCT yaooc_odbc_timestamp_get(const_pointer p)
{
  yaooc_odbc_timestamp_const_pointer this=p;
  return this->value_;
}

void yaooc_odbc_timestamp_set(pointer p,TIMESTAMP_STRUCT v)
{
  yaooc_odbc_timestamp_pointer this=p;
	this->value_=v;
}

time_t yaooc_odbc_timestamp_get_time(const_pointer p)
{
  yaooc_odbc_timestamp_const_pointer this=p;
	struct tm tm;
	memset(&tm,0,sizeof(struct tm));
	tm.tm_year = this->value_.year-1900;
	tm.tm_mday=this->value_.day;
	tm.tm_mon=this->value_.month-1;
	tm.tm_hour=this->value_.hour;
	tm.tm_min=this->value_.minute;
	tm.tm_sec=this->value_.second;
	tm.tm_isdst=-1;
	return mktime(&tm);

}

void yaooc_odbc_timestamp_set_time(pointer p,time_t t)
{
  yaooc_odbc_timestamp_pointer this=p;
	struct tm *tm = localtime(&t);
	this->value_.year = tm->tm_year + 1900;
	this->value_.day = tm->tm_mday;
	this->value_.month=tm->tm_mon+1;
	this->value_.hour=tm->tm_hour;
	this->value_.minute=tm->tm_min;
	this->value_.second=tm->tm_sec;
}


/* Class table definition for yaooc_odbc_timestamp */
yaooc_odbc_timestamp_class_table_t yaooc_odbc_timestamp_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_odbc_value_class_table,
  .type_name_ = (const char*) "yaooc_odbc_timestamp_t",
  .swap = (void(*)(pointer, pointer)) yaooc_odbc_timestamp_swap,
  .c_data_type = (SQLSMALLINT(*)(const_pointer)) yaooc_odbc_timestamp_c_data_type,
  .column_size = (SQLLEN(*)(const_pointer)) yaooc_odbc_timestamp_column_size,
  .data = (void*(*)(pointer)) yaooc_odbc_timestamp_data,
  .get = (TIMESTAMP_STRUCT(*)(const_pointer)) yaooc_odbc_timestamp_get,
  .set = (void(*)(pointer, TIMESTAMP_STRUCT)) yaooc_odbc_timestamp_set,
  .get_time = (time_t(*)(const_pointer)) yaooc_odbc_timestamp_get_time,
  .set_time = (void(*)(pointer, time_t)) yaooc_odbc_timestamp_set_time,
};

/* Type info structure for yaooc_odbc_timestamp */
DEFINE_TYPE_INFO(yaooc_odbc_timestamp,Y,N,Y,Y,N,N,N,Y,yaooc_odbc_value);

/* Private variables implementation for yaooc_odbc_statement */

/* Private methods prototypes for yaooc_odbc_statement */
static void yaooc_odbc_statement_set_handle(pointer, SQLHSTMT);

/* Type Info implemmentation for yaooc_odbc_statement */
void yaooc_odbc_statement_default_ctor(pointer p)
{
	/* This should throw an exception.  Statements are only created from connection */
	THROW(new_ctor(yaooc_odbc_exception,yaooc_odbc_exception_ctor_v,"ODBC statement can only be created from connection"));
}

void yaooc_odbc_statement_private_ctor(pointer p,va_list args)
{
	/* This should throw an exception.  Statements are only created from connection */
  yaooc_odbc_statement_pointer this=p;
  this->statement_handle_ = SQL_NULL_HANDLE;
}

void yaooc_odbc_statement_dtor(pointer p)
{
  yaooc_odbc_statement_pointer this=p;
	if(this->statement_handle_ != SQL_NULL_HANDLE) {
		SQLCloseCursor(this->statement_handle_);
		SQLFreeHandle(SQL_HANDLE_STMT,this->statement_handle_);
		this->statement_handle_ = SQL_NULL_HANDLE;
	}
}

void yaooc_odbc_statement_assign(pointer p,const_pointer s)
{
  yaooc_odbc_statement_pointer this=p;
  yaooc_odbc_statement_const_pointer src=s;
  this->statement_handle_ = src->statement_handle_;
}

/* Constructors implementation for yaooc_odbc_statement */

/* Private methods implementation for yaooc_odbc_statement */
static void yaooc_odbc_statement_set_handle(pointer p,SQLHSTMT h)
{
  yaooc_odbc_statement_pointer this=p;
	this->statement_handle_=h;
}


/* Protected implementation for yaooc_odbc_statement */

/* Table implementation for yaooc_odbc_statement */
bool yaooc_odbc_statement_bindcols(pointer p,void* v,... )
{
  yaooc_odbc_statement_pointer this=p;
  bool ret=false;
	if(v) {
		ret=true;
		va_list args;
		va_start(args,v);
		SQLUSMALLINT icol=1;
		yaooc_odbc_value_t* val=v;
		while(val) {
			if(SQLBindCol(this->statement_handle_,icol,M(val,c_data_type),M(val,data),M(val,column_size),NULL) != SQL_SUCCESS) {
				ret=false;
				break;
			}
			val=va_arg(args,yaooc_odbc_value_t*);
			icol++;
		}
		va_end(args);
	}
  return ret;
}

bool yaooc_odbc_statement_bindparams(pointer p,void* v,... )
{
  yaooc_odbc_statement_pointer this=p;
  bool ret=false;
	if(this->statement_handle_ != SQL_NULL_HANDLE && v) {
		va_list args;
		ret=true;
		SQLUSMALLINT iparam=1;
		va_start(args,v);
		yaooc_odbc_value_t* val=v;
		while(val) {
			if(SQLBindParameter(this->statement_handle_,iparam,SQL_PARAM_INPUT,M(val,c_data_type),SQL_DEFAULT,
					M(val,column_size),0,M(val,data),M(val,column_size),NULL) != SQL_SUCCESS) {
				ret=false;
				break;
			}
			val=va_arg(args,yaooc_odbc_value_t*);
			iparam++;
		}
		va_end(args);
	}
  return ret;
}

bool yaooc_odbc_statement_fetch(pointer p)
{
  yaooc_odbc_statement_pointer this=p;
	SQLRETURN ret = SQLFetch(this->statement_handle_); // == SQL_SUCCESS;
/*	debug(1) {
		printf("Fetch: %d\n",ret);
		printf("Fetch handle: %p\n",statement_handle_);
		SQLCHAR state[256];
		SQLCHAR msg[256];
		SQLINTEGER err_ptr;
		SQLSMALLINT text_len;
		SQLGetDiagRec(SQL_HANDLE_STMT,statement_handle_,1,state,&err_ptr,msg,256,&text_len);
		printf("%s %d %s %d\n",state,err_ptr,msg,text_len);
	}*/
	return ret==SQL_SUCCESS;
}

bool yaooc_odbc_statement_execute(pointer p)
{
  yaooc_odbc_statement_pointer this=p;
	SQLRETURN ret = SQLExecute(this->statement_handle_); // == SQL_SUCCESS;
/*	debug(1) {
		printf("Execute: %d\n",ret);
		printf("Execute handle: %p\n",statement_handle_);
		SQLCHAR state[256];
		SQLCHAR msg[256];
		SQLINTEGER err_ptr;
		SQLSMALLINT text_len;
		SQLGetDiagRec(SQL_HANDLE_STMT,statement_handle_,1,state,&err_ptr,msg,256,&text_len);
		printf("%s %d %s %d\n",state,err_ptr,msg,text_len);
	}*/
	return ret==SQL_SUCCESS;
}


/* Class table definition for yaooc_odbc_statement */
yaooc_odbc_statement_class_table_t yaooc_odbc_statement_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "yaooc_odbc_statement_t",
  .swap = (void(*)(pointer, pointer)) yaooc_odbc_statement_swap,
  .bindcols = (bool(*)(pointer, void*, ...)) yaooc_odbc_statement_bindcols,
  .bindparams = (bool(*)(pointer, void*, ...)) yaooc_odbc_statement_bindparams,
  .fetch = (bool(*)(pointer)) yaooc_odbc_statement_fetch,
  .execute = (bool(*)(pointer)) yaooc_odbc_statement_execute,
};

/* Type info structure for yaooc_odbc_statement */
DEFINE_TYPE_INFO(yaooc_odbc_statement,Y,Y,N,Y,N,N,N,Y,yaooc_object);

/* Private variables implementation for yaooc_odbc_connection */

/* Private methods prototypes for yaooc_odbc_connection */

/* Type Info implemmentation for yaooc_odbc_connection */
void yaooc_odbc_connection_default_ctor(pointer p)
{
  yaooc_odbc_connection_pointer this=p;
  this->connection_handle_ = SQL_NULL_HANDLE;
}

void yaooc_odbc_connection_dtor(pointer p)
{
  yaooc_odbc_connection_pointer this=p;
	yaooc_odbc_connection_disconnect(this);
}

/* Constructors implementation for yaooc_odbc_connection */
void yaooc_odbc_connection_connect_str(pointer p,va_list args)
{
  yaooc_odbc_connection_pointer this=p;
	const char* str= va_arg(args, const char*);
	yaooc_odbc_connection_default_ctor(this);
	yaooc_odbc_connection_connect(this,str);
}


/* Private methods implementation for yaooc_odbc_connection */

/* Protected implementation for yaooc_odbc_connection */

/* Table implementation for yaooc_odbc_connection */
yaooc_odbc_statement_t* yaooc_odbc_connection_exec_direct(pointer p,const char* str)
{
	yaooc_odbc_connection_pointer this=p;
 	yaooc_odbc_statement_t *stmt = new_ctor(yaooc_odbc_statement,yaooc_odbc_statement_private_ctor,NULL);
	SQLHSTMT handle;
	if(SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_STMT, this->connection_handle_, &handle))) {
		SQLRETURN rc= SQLExecDirect(handle,(SQLCHAR*)str,SQL_NTS);
		debug(1) {
			printf("%d\n",rc);
		}
		if(SQL_SUCCEEDED(rc)) {
			debug(1) {
				printf("Exec direct succeeded. Set statement handle handle: %p\n",handle);
			}
			yaooc_odbc_statement_set_handle(stmt,handle);
		} else {
/*			SQLCHAR* state=new SQLCHAR[256];
			SQLCHAR* msg=new SQLCHAR[256];
			SQLINTEGER err_ptr;
			SQLSMALLINT text_len;
			SQLGetDiagRec(SQL_HANDLE_STMT,handle,1,state,&err_ptr,msg,256,&text_len);
			printf("%s %d %s %d\n",state,err_ptr,msg,text_len);*/
			SQLCloseCursor(handle);
			SQLFreeHandle(SQL_HANDLE_STMT,handle);
		}
	}
	return stmt;
}

yaooc_odbc_statement_t* yaooc_odbc_connection_prepare(pointer p,const char* str)
{
  yaooc_odbc_connection_pointer this=p;
 	yaooc_odbc_statement_t *stmt = new_ctor(yaooc_odbc_statement,yaooc_odbc_statement_private_ctor,NULL);
	SQLHSTMT handle;
	if(SQL_SUCCEEDED(SQLAllocHandle(SQL_HANDLE_STMT, this->connection_handle_, &handle))) {
		SQLRETURN rc= SQLPrepare(handle,(SQLCHAR*)str,SQL_NTS);
		debug(1) {
			printf("%d\n",rc);
		}
		if(SQL_SUCCEEDED(rc)) {
			debug(1) {
				printf("Prepare handle: %p\n",handle);
			}
			yaooc_odbc_statement_set_handle(stmt,handle);
		} else {
/*			SQLCHAR* state=new SQLCHAR[256];
			SQLCHAR* msg=new SQLCHAR[256];
			SQLINTEGER err_ptr;
			SQLSMALLINT text_len;
			SQLGetDiagRec(SQL_HANDLE_STMT,handle,1,state,&err_ptr,msg,256,&text_len);
			printf("%s %d %s %d\n",state,err_ptr,msg,text_len);*/
			SQLCloseCursor(handle);
			SQLFreeHandle(SQL_HANDLE_STMT,handle);
		}
	}
	return stmt;
}

void yaooc_odbc_connection_connect(pointer p,const char* str)
{
  yaooc_odbc_connection_pointer this=p;
	yaooc_odbc_connection_disconnect(this);
	SQLRETURN rc = SQLAllocHandle(SQL_HANDLE_DBC, yaooc_odbc_environment_henv_, &this->connection_handle_);
	if(rc == SQL_SUCCESS || rc == SQL_SUCCESS_WITH_INFO) {
		yaooc_odbc_connection_auto_commit(this,false); // autocommit off by default
		rc=SQLDriverConnect(this->connection_handle_, NULL, (SQLCHAR*)str, SQL_NTS,
				NULL, 0, NULL, SQL_DRIVER_NOPROMPT);
	}
/*	debug(DEBUG_CONNECTION) {
		rc == SQL_SUCCESS ? puts("Connected") : puts("Failed connect");
	}*/
	if(rc != SQL_SUCCESS) {
/*		SQLCHAR state[256];
		SQLCHAR msg[256];
		SQLINTEGER err_ptr;
		SQLSMALLINT text_len;
		SQLGetDiagRec(SQL_HANDLE_DBC,connection_handle_,1,state,&err_ptr,msg,256,&text_len);
		printf("%s %d %s %d\n",state,err_ptr,msg,text_len);*/
		yaooc_odbc_connection_disconnect(this);
	}
}

void yaooc_odbc_connection_disconnect(pointer p)
{
  yaooc_odbc_connection_pointer this=p;
	if(this->connection_handle_ != SQL_NULL_HANDLE) {
		SQLDisconnect(this->connection_handle_);
		SQLFreeHandle(SQL_HANDLE_DBC, this->connection_handle_);
		this->connection_handle_=SQL_NULL_HANDLE;
	}
}

void yaooc_odbc_connection_auto_commit(pointer p,bool on)
{
  yaooc_odbc_connection_pointer this=p;
	if(this->connection_handle_ != SQL_NULL_HANDLE)
		SQLSetConnectAttr(this->connection_handle_,SQL_ATTR_AUTOCOMMIT, (SQLPOINTER)(long)(on ? SQL_TRUE : SQL_FALSE), 0);
}

void yaooc_odbc_connection_commit(pointer p)
{
  yaooc_odbc_connection_pointer this=p;
	if(this->connection_handle_ != SQL_NULL_HANDLE)
		SQLEndTran(SQL_HANDLE_DBC,this->connection_handle_,SQL_COMMIT);
}

void yaooc_odbc_connection_rollback(pointer p)
{
  yaooc_odbc_connection_pointer this=p;
	if(this->connection_handle_ != SQL_NULL_HANDLE)
		SQLEndTran(SQL_HANDLE_DBC,this->connection_handle_,SQL_ROLLBACK);
}


/* Class table definition for yaooc_odbc_connection */
yaooc_odbc_connection_class_table_t yaooc_odbc_connection_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "yaooc_odbc_connection_t",
  .swap = (void(*)(pointer, pointer)) yaooc_odbc_connection_swap,
  .exec_direct = (yaooc_odbc_statement_t*(*)(pointer, const char*)) yaooc_odbc_connection_exec_direct,
  .prepare = (yaooc_odbc_statement_t*(*)(pointer, const char*)) yaooc_odbc_connection_prepare,
  .connect = (void(*)(pointer, const char*)) yaooc_odbc_connection_connect,
  .disconnect = (void(*)(pointer)) yaooc_odbc_connection_disconnect,
  .auto_commit = (void(*)(pointer, bool)) yaooc_odbc_connection_auto_commit,
  .commit = (void(*)(pointer)) yaooc_odbc_connection_commit,
  .rollback = (void(*)(pointer)) yaooc_odbc_connection_rollback,
};

/* Type info structure for yaooc_odbc_connection */
DEFINE_TYPE_INFO(yaooc_odbc_connection,Y,Y,N,N,N,N,N,Y,yaooc_object);

/* End YAOOCPP output */

