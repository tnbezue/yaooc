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
	this->icol_=1;
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
bool yaooc_odbc_statement_bindcol(pointer p,void* data,SQLLEN column_size,SQLSMALLINT c_data_type)
{
  yaooc_odbc_statement_pointer this=p;
	return SQLBindCol(this->statement_handle_,this->icol_++,c_data_type,data,column_size,NULL) == SQL_SUCCESS;
}

bool yaooc_odbc_statement_bindparam(pointer p,void* data,SQLLEN column_size,SQLSMALLINT c_data_type)
{
  yaooc_odbc_statement_pointer this=p;
	return SQLBindParameter(this->statement_handle_,this->icol_++,SQL_PARAM_INPUT,c_data_type,SQL_DEFAULT,
					column_size,0,data,column_size,NULL) == SQL_SUCCESS;
}

/* Table implementation for yaooc_odbc_statement */
bool yaooc_odbc_statement_bindcol_chr(pointer p,char* v)
{
	return yaooc_odbc_statement_bindcol(p,v,sizeof(char),SQL_C_STINYINT);
}

bool yaooc_odbc_statement_bindcol_uchr(pointer p,unsigned char* v)
{
	return yaooc_odbc_statement_bindcol(p,v,sizeof(unsigned char),SQL_C_UTINYINT);
}

bool yaooc_odbc_statement_bindcol_short(pointer p,short* v)
{
	return yaooc_odbc_statement_bindcol(p,v,sizeof(short),SQL_C_SSHORT);
}

bool yaooc_odbc_statement_bindcol_ushort(pointer p,unsigned short* v)
{
	return yaooc_odbc_statement_bindcol(p,v,sizeof(unsigned short),SQL_C_USHORT);
}

bool yaooc_odbc_statement_bindcol_int(pointer p,int* v)
{
	return yaooc_odbc_statement_bindcol(p,v,sizeof(int),SQL_C_SLONG);
}

bool yaooc_odbc_statement_bindcol_uint(pointer p,unsigned int* v)
{
	return yaooc_odbc_statement_bindcol(p,v,sizeof(unsigned int),SQL_C_ULONG);
}

bool yaooc_odbc_statement_bindcol_long(pointer p,long long* v)
{
	return yaooc_odbc_statement_bindcol(p,v,sizeof(long long),SQL_C_SBIGINT);
}

bool yaooc_odbc_statement_bindcol_ulong(pointer p,unsigned long long* v)
{
	return yaooc_odbc_statement_bindcol(p,v,sizeof(unsigned long long),SQL_C_UBIGINT);
}

bool yaooc_odbc_statement_bindcol_dbl(pointer p,double* v)
{
	return yaooc_odbc_statement_bindcol(p,v,sizeof(double),SQL_C_DOUBLE);
}

bool yaooc_odbc_statement_bindcol_str(pointer p,char* v,SQLLEN l)
{
	return yaooc_odbc_statement_bindcol(p,v,l,SQL_C_CHAR);
}

bool yaooc_odbc_statement_bindcol_blob(pointer p,void* v,SQLLEN l)
{
	return yaooc_odbc_statement_bindcol(p,v,l,SQL_C_BINARY);
}

bool yaooc_odbc_statement_bindcol_time(pointer p,TIME_STRUCT* v)
{
	return yaooc_odbc_statement_bindcol(p,v,sizeof(TIME_STRUCT),SQL_C_TYPE_TIME);
}

bool yaooc_odbc_statement_bindcol_date(pointer p,DATE_STRUCT* v)
{
	return yaooc_odbc_statement_bindcol(p,v,sizeof(DATE_STRUCT),SQL_C_TYPE_DATE);
}

bool yaooc_odbc_statement_bindcol_ts(pointer p,TIMESTAMP_STRUCT* v)
{
	return yaooc_odbc_statement_bindcol(p,v,sizeof(TIMESTAMP_STRUCT),SQL_C_TYPE_TIMESTAMP);
}
///////

bool yaooc_odbc_statement_bindparam_chr(pointer p,char* v)
{
	return yaooc_odbc_statement_bindparam(p,v,sizeof(char),SQL_C_STINYINT);
}

bool yaooc_odbc_statement_bindparam_uchr(pointer p,unsigned char* v)
{
	return yaooc_odbc_statement_bindparam(p,v,sizeof(unsigned char),SQL_C_UTINYINT);
}

bool yaooc_odbc_statement_bindparam_short(pointer p,short* v)
{
	return yaooc_odbc_statement_bindparam(p,v,sizeof(short),SQL_C_SSHORT);
}

bool yaooc_odbc_statement_bindparam_ushort(pointer p,unsigned short* v)
{
	return yaooc_odbc_statement_bindparam(p,v,sizeof(unsigned short),SQL_C_USHORT);
}

bool yaooc_odbc_statement_bindparam_int(pointer p,int* v)
{
	return yaooc_odbc_statement_bindparam(p,v,sizeof(int),SQL_C_SLONG);
}

bool yaooc_odbc_statement_bindparam_uint(pointer p,unsigned int* v)
{
	return yaooc_odbc_statement_bindparam(p,v,sizeof(unsigned int),SQL_C_ULONG);
}

bool yaooc_odbc_statement_bindparam_long(pointer p,long long* v)
{
	return yaooc_odbc_statement_bindparam(p,v,sizeof(long long),SQL_C_SBIGINT);
}

bool yaooc_odbc_statement_bindparam_ulong(pointer p,unsigned long long* v)
{
	return yaooc_odbc_statement_bindparam(p,v,sizeof(unsigned long long),SQL_C_UBIGINT);
}

bool yaooc_odbc_statement_bindparam_dbl(pointer p,double* v)
{
	return yaooc_odbc_statement_bindparam(p,v,sizeof(double),SQL_C_DOUBLE);
}

bool yaooc_odbc_statement_bindparam_str(pointer p,char* v,SQLLEN l)
{
	return yaooc_odbc_statement_bindparam(p,v,l,SQL_C_CHAR);
}

bool yaooc_odbc_statement_bindparam_blob(pointer p,void* v,SQLLEN l)
{
	return yaooc_odbc_statement_bindparam(p,v,l,SQL_C_BINARY);
}

bool yaooc_odbc_statement_bindparam_time(pointer p,TIME_STRUCT* v)
{
	return yaooc_odbc_statement_bindparam(p,v,sizeof(TIME_STRUCT),SQL_C_TYPE_TIME);
}

bool yaooc_odbc_statement_bindparam_date(pointer p,DATE_STRUCT* v)
{
	return yaooc_odbc_statement_bindparam(p,v,sizeof(DATE_STRUCT),SQL_C_TYPE_DATE);
}

bool yaooc_odbc_statement_bindparam_ts(pointer p,TIMESTAMP_STRUCT* v)
{
	return yaooc_odbc_statement_bindparam(p,v,sizeof(TIMESTAMP_STRUCT),SQL_C_TYPE_TIMESTAMP);
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
  .bindcol_chr = (bool(*)(pointer, char*)) yaooc_odbc_statement_bindcol_chr,
  .bindcol_uchr = (bool(*)(pointer, unsigned char*)) yaooc_odbc_statement_bindcol_uchr,
  .bindcol_short = (bool(*)(pointer, short*)) yaooc_odbc_statement_bindcol_short,
  .bindcol_ushort = (bool(*)(pointer, unsigned short*)) yaooc_odbc_statement_bindcol_ushort,
  .bindcol_int = (bool(*)(pointer, int*)) yaooc_odbc_statement_bindcol_int,
  .bindcol_uint = (bool(*)(pointer, unsigned int*)) yaooc_odbc_statement_bindcol_uint,
  .bindcol_long = (bool(*)(pointer, long long*)) yaooc_odbc_statement_bindcol_long,
  .bindcol_ulong = (bool(*)(pointer, unsigned long long*)) yaooc_odbc_statement_bindcol_ulong,
  .bindcol_dbl = (bool(*)(pointer, double*)) yaooc_odbc_statement_bindcol_dbl,
  .bindcol_str = (bool(*)(pointer, char*, SQLLEN)) yaooc_odbc_statement_bindcol_str,
  .bindcol_blob = (bool(*)(pointer, void*, SQLLEN)) yaooc_odbc_statement_bindcol_blob,
  .bindcol_time = (bool(*)(pointer, TIME_STRUCT*)) yaooc_odbc_statement_bindcol_time,
  .bindcol_date = (bool(*)(pointer, DATE_STRUCT*)) yaooc_odbc_statement_bindcol_date,
  .bindcol_ts = (bool(*)(pointer, TIMESTAMP_STRUCT*)) yaooc_odbc_statement_bindcol_ts,
  .bindparam_chr = (bool(*)(pointer, char*)) yaooc_odbc_statement_bindparam_chr,
  .bindparam_uchr = (bool(*)(pointer, unsigned char*)) yaooc_odbc_statement_bindparam_uchr,
  .bindparam_short = (bool(*)(pointer, short*)) yaooc_odbc_statement_bindparam_short,
  .bindparam_ushort = (bool(*)(pointer, unsigned short*)) yaooc_odbc_statement_bindparam_ushort,
  .bindparam_int = (bool(*)(pointer, int*)) yaooc_odbc_statement_bindparam_int,
  .bindparam_uint = (bool(*)(pointer, unsigned int*)) yaooc_odbc_statement_bindparam_uint,
  .bindparam_long = (bool(*)(pointer, long long*)) yaooc_odbc_statement_bindparam_long,
  .bindparam_ulong = (bool(*)(pointer, unsigned long long*)) yaooc_odbc_statement_bindparam_ulong,
  .bindparam_dbl = (bool(*)(pointer, double*)) yaooc_odbc_statement_bindparam_dbl,
  .bindparam_str = (bool(*)(pointer, char*, SQLLEN)) yaooc_odbc_statement_bindparam_str,
  .bindparam_blob = (bool(*)(pointer, void*, SQLLEN)) yaooc_odbc_statement_bindparam_blob,
  .bindparam_time = (bool(*)(pointer, TIME_STRUCT*)) yaooc_odbc_statement_bindparam_time,
  .bindparam_date = (bool(*)(pointer, DATE_STRUCT*)) yaooc_odbc_statement_bindparam_date,
  .bindparam_ts = (bool(*)(pointer, TIMESTAMP_STRUCT*)) yaooc_odbc_statement_bindparam_ts,
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
		yaooc_odbc_connection_commit(this);
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

