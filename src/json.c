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

#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <yaooc/json.h>

static const char* yaooc_json_type_strings[] =
  {
    "JSON_UNDEFINED" , "JSON_NULL", "JSON_BOOL" , "JSON_INTEGER" , "JSON_REAL" ,
    "JSON_STRING", "JSON_ARRAY", "JSON_OBJECT"
  };
/*  Begin YAOOC PreProcessor generated content */

/* Private items for yaooc_json_exception */

/* Protected items for yaooc_json_exception */


/* Typeinfo for yaooc_json_exception */

/* Constructors for yaooc_json_exception */

/* Class table methods for yaooc_json_exception */

/* Class table for yaooc_json_exception */
yaooc_json_exception_class_table_t yaooc_json_exception_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_exception_class_table,
  .type_name_ = (const char*) "yaooc_json_exception_t",
  .swap = (void (*) (pointer p,pointer)) yaooc_json_exception_swap,
  .what = (const char* (*) (const_pointer p)) yaooc_json_exception_what,
};


DEFINE_TYPE_INFO(yaooc_json_exception,N,N,N,N,N,N,N,Y,yaooc_exception);


/* Private items for yaooc_json_value */

/* Protected items for yaooc_json_value */


/* Typeinfo for yaooc_json_value */
void yaooc_json_value_default_ctor(pointer p)
{
  yaooc_json_value_pointer this=p;
  this->type_=JSON_UNDEFINED;
  this->real_=0; /* Set other union members to zero as well */
}

void yaooc_json_value_dtor(pointer p)
{
  yaooc_json_value_pointer this=p;
  M(this,virtual_dtor);
}

void yaooc_json_value_copy_ctor(pointer d,const_pointer s)
{
  yaooc_json_value_default_ctor(d);
  yaooc_json_value_const_pointer src=s;
  src->class_table_->virtual_copy_ctor(d,s);
//  M(dst,virtual_copy_ctor,s);
}

void yaooc_json_value_assign(pointer d,const_pointer s)
{
//  yaooc_json_value_pointer dst=d;
  yaooc_json_value_const_pointer src=s;
//  M(dst,virtual_assign,s);
  src->class_table_->virtual_assign(d,s);
}

bool yaooc_json_value_less_than_compare(const_pointer p1,const_pointer p2)
{
  yaooc_json_value_const_pointer vp1=p1;
  yaooc_json_value_const_pointer vp2=p2;
  if(vp1->type_ != vp2->type_) {
		THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,
				"Attempt compare different json types: %s and %s",
				yaooc_json_type_strings[vp1->type_],yaooc_json_type_strings[vp2->type_]));
  }
  return M(vp1,virtual_less_than_compare,vp2);
}

void yaooc_json_value_to_stream(const_pointer p,pointer s)
{
	yaooc_json_value_const_pointer this=p;
	M(this,print,s);
}
/* Constructors for yaooc_json_value */

/* Class table methods for yaooc_json_value */
void yaooc_json_value_virtual_dtor(pointer p)
{
}

void yaooc_json_value_virtual_copy_ctor(pointer p,const_pointer s)
{
  yaooc_json_value_pointer this=p;
  yaooc_json_value_const_pointer src=p;
  THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,
				"copy ctor %s to %s\n",yaooc_json_type_strings[src->type_],
    yaooc_json_type_strings[this->type_]));
}

/*
*/
void yaooc_json_value_virtual_assign(pointer p,const_pointer s)
{
  yaooc_json_value_pointer this=p;
  yaooc_json_value_const_pointer src=s;
	THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,
				"Trying to assign %d to %d\n",src->type_,this->type_));
}

bool yaooc_json_value_virtual_less_than_compare(const_pointer p,const_pointer o)
{
  return false;
}

yaooc_json_type_t yaooc_json_value_type(const_pointer p)
{
  return ((yaooc_json_value_const_pointer)p)->type_;
}

void yaooc_json_value_print(const_pointer p,ostream_pointer s)
{
}


/* Class table for yaooc_json_value */
yaooc_json_value_class_table_t yaooc_json_value_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "yaooc_json_value_t",
  .swap = (void (*) (pointer,pointer)) yaooc_json_value_swap,
  .virtual_dtor = (void (*) (pointer)) yaooc_json_value_virtual_dtor,
  .virtual_copy_ctor = (void (*) (pointer,const_pointer)) yaooc_json_value_virtual_copy_ctor,
  .virtual_assign = (void (*) (pointer,const_pointer)) yaooc_json_value_virtual_assign,
  .virtual_less_than_compare = (bool (*) (const_pointer,const_pointer)) yaooc_json_value_virtual_less_than_compare,
  .type = (yaooc_json_type_t (*) (const_pointer)) yaooc_json_value_type,
  .print = (void (*) (const_pointer,ostream_pointer)) yaooc_json_value_print,
};


DEFINE_TYPE_INFO(yaooc_json_value,Y,Y,Y,Y,Y,N,N,Y,yaooc_object);
/* Private items for yaooc_json_null */

/* Protected items for yaooc_json_null */


/* Typeinfo for yaooc_json_null */
void yaooc_json_null_default_ctor(pointer p)
{
  yaooc_json_null_pointer this=p;
  yaooc_json_value_default_ctor(p);
  this->type_=JSON_NULL;
}
/*
void yaooc_json_null_copy_ctor(pointer d,const_pointer s)
{
  yaooc_json_null_pointer dst=d;
  yaooc_json_value_default_ctor(d);
  dst->type_=JSON_NULL;
}
*/
/* Constructors for yaooc_json_null */

/* Class table methods for yaooc_json_null */
void yaooc_json_null_virtual_dtor(pointer p)
{
}

void yaooc_json_null_virtual_copy_ctor(pointer p,const_pointer s)
{
  yaooc_json_null_pointer dst=p;
  dst->type_=JSON_NULL;
}

void yaooc_json_null_virtual_assign(pointer p,const_pointer s)
{
  yaooc_json_null_pointer this=p;
  if(this->type_==JSON_UNDEFINED || this->type_==JSON_NULL) {
    this->class_table_=&yaooc_json_null_class_table;
    this->type_=JSON_NULL;
  } else {
    THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,
				"Attempt to assign JSON_NULL to %s",yaooc_json_type_strings[this->type_]));
  }
}

bool yaooc_json_null_virtual_less_than_compare(const_pointer p,const_pointer o)
{
  return false;
}

void yaooc_json_null_print(const_pointer p,ostream_pointer s)
{
	yaooc_ostream_pointer strm=s;
  M(strm,printf,"null");
}


/* Class table for yaooc_json_null */
yaooc_json_null_class_table_t yaooc_json_null_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_json_value_class_table,
  .type_name_ = (const char*) "yaooc_json_null_t",
  .swap = (void (*) (pointer p,pointer)) yaooc_json_null_swap,
  .virtual_dtor = (void (*) (pointer p)) yaooc_json_null_virtual_dtor,
  .virtual_copy_ctor = (void (*) (pointer,const_pointer)) yaooc_json_null_virtual_copy_ctor,
  .virtual_assign = (void (*) (pointer,const_pointer)) yaooc_json_null_virtual_assign,
  .virtual_less_than_compare = (bool (*) (const_pointer,const_pointer)) yaooc_json_null_virtual_less_than_compare,
  .type = (yaooc_json_type_t (*) (const_pointer)) yaooc_json_value_type,
  .print = (void (*) (const_pointer,ostream_pointer)) yaooc_json_null_print,
};


DEFINE_TYPE_INFO(yaooc_json_null,Y,N,N,N,N,N,N,Y,yaooc_json_value);
/* Private items for yaooc_json_bool */

/* Protected items for yaooc_json_bool */


/* Typeinfo for yaooc_json_bool */
void yaooc_json_bool_default_ctor(pointer p)
{
  yaooc_json_bool_pointer this=p;
  yaooc_json_value_default_ctor(p);
  this->type_=JSON_BOOL;
  this->bool_=false;
}
/*
void yaooc_json_bool_copy_ctor(pointer d,const_pointer s)
{
  yaooc_json_bool_pointer dst=d;
  yaooc_json_bool_const_pointer src=s;
  dst->bool_=src->bool_;
}
*/
/* Constructors for yaooc_json_bool */
void yaooc_json_bool_ctor_bool(pointer p,va_list args)
{
  yaooc_json_bool_pointer this=p;
  this->type_=JSON_BOOL;
  this->bool_=va_arg(args,int);
}

/* Class table methods for yaooc_json_bool */
void yaooc_json_bool_virtual_dtor(pointer p)
{
}

void yaooc_json_bool_virtual_copy_ctor(pointer p,const_pointer s)
{
  yaooc_json_bool_pointer this=p;
  yaooc_json_bool_const_pointer src=s;
  this->type_=JSON_BOOL;
  this->bool_=src->bool_;
}

void yaooc_json_bool_virtual_assign(pointer p,const_pointer s)
{
  yaooc_json_bool_pointer this=p;
  yaooc_json_bool_const_pointer src=s;
  if(this->type_==JSON_UNDEFINED || this->type_==JSON_BOOL) {
    this->class_table_=&yaooc_json_bool_class_table;
    this->type_=JSON_BOOL;
    this->bool_=src->bool_;
  } else {
		THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,
					"Attempt to assign JSON_BOOL to %s",yaooc_json_type_strings[this->type_]));
  }
}

bool yaooc_json_bool_virtual_less_than_compare(const_pointer p,const_pointer p2)
{
  return ((yaooc_json_bool_const_pointer)p)->bool_ < ((yaooc_json_bool_const_pointer)p2)->bool_;
}

void yaooc_json_bool_print(const_pointer p,ostream_pointer s)
{
  yaooc_json_bool_const_pointer this=p;
	yaooc_ostream_pointer strm=s;
  M(strm,printf,"%s",(this->bool_ ? "true" : "false"));
}

void yaooc_json_bool_set(pointer p,bool value)
{
  yaooc_json_bool_pointer this=p;
  this->bool_=value;
}

bool yaooc_json_bool_get(const_pointer p)
{
  yaooc_json_bool_const_pointer this=p;
  return this->bool_;
}


/* Class table for yaooc_json_bool */
yaooc_json_bool_class_table_t yaooc_json_bool_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_json_value_class_table,
  .type_name_ = (const char*) "yaooc_json_bool_t",
  .swap = (void (*) (pointer p,pointer)) yaooc_json_bool_swap,
  .virtual_dtor = (void (*) (pointer p)) yaooc_json_bool_virtual_dtor,
  .virtual_copy_ctor = (void (*) (pointer,const_pointer)) yaooc_json_bool_virtual_copy_ctor,
  .virtual_assign = (void (*) (pointer,const_pointer)) yaooc_json_bool_virtual_assign,
  .virtual_less_than_compare = (bool (*) (const_pointer,const_pointer)) yaooc_json_bool_virtual_less_than_compare,
  .type = (yaooc_json_type_t (*) (const_pointer)) yaooc_json_value_type,
  .print = (void (*) (const_pointer,ostream_pointer)) yaooc_json_bool_print,
  .set = (void (*) (pointer p,bool)) yaooc_json_bool_set,
  .get = (bool (*) (const_pointer p)) yaooc_json_bool_get,
};


DEFINE_TYPE_INFO(yaooc_json_bool,Y,N,N,N,N,N,N,Y,yaooc_json_value);
/* Private items for yaooc_json_integer */

/* Protected items for yaooc_json_integer */


/* Typeinfo for yaooc_json_integer */
void yaooc_json_integer_default_ctor(pointer p)
{
  yaooc_json_integer_pointer this=p;
  this->type_=JSON_INTEGER;
  this->int_=0;
}
/*
void yaooc_json_integer_copy_ctor(pointer d,const_pointer s)
{
  yaooc_json_integer_pointer dst=d;
  yaooc_json_integer_const_pointer src=s;
}
*/
/* Constructors for yaooc_json_integer */
void yaooc_json_integer_ctor_int(pointer p,va_list args)
{
  yaooc_json_integer_pointer this=p;
  this->type_=JSON_INTEGER;
  this->int_ = va_arg(args,int);
}

/* Class table methods for yaooc_json_integer */
void yaooc_json_integer_virtual_dtor(pointer p)
{
}

void yaooc_json_integer_virtual_copy_ctor(pointer p,const_pointer s)
{
  yaooc_json_integer_pointer this=p;
  this->type_=JSON_INTEGER;
  this->int_=((yaooc_json_integer_const_pointer)s)->int_;
}

void yaooc_json_integer_virtual_assign(pointer p,const_pointer s)
{
  yaooc_json_integer_pointer this=p;
//  yaooc_json_integer_const_pointer src=s;
  if(this->type_==JSON_UNDEFINED || this->type_==JSON_INTEGER) {
    this->class_table_=&yaooc_json_integer_class_table;
    this->type_=JSON_INTEGER;
    this->int_=((yaooc_json_integer_const_pointer)s)->int_;
  } else {
		THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,
					"Attempt to assign JSON_INTEGER to %s",yaooc_json_type_strings[this->type_]));
  }
}

bool yaooc_json_integer_virtual_less_than_compare(const_pointer p,const_pointer o)
{
  return ((yaooc_json_integer_const_pointer)p)->int_ < ((yaooc_json_integer_const_pointer)o)->int_;
}

void yaooc_json_integer_print(const_pointer p,ostream_pointer s)
{
  yaooc_json_integer_const_pointer this=p;
	yaooc_ostream_pointer strm=s;
	M(strm,printf,"%" PRId64,this->int_);
}

void yaooc_json_integer_set(pointer p,int64_t value)
{
  yaooc_json_integer_pointer this=p;
  this->int_=value;
}

int64_t yaooc_json_integer_get(const_pointer p)
{
  yaooc_json_integer_const_pointer this=p;
  return this->int_;
}


/* Class table for yaooc_json_integer */
yaooc_json_integer_class_table_t yaooc_json_integer_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_json_value_class_table,
  .type_name_ = (const char*) "yaooc_json_integer_t",
  .swap = (void (*) (pointer p,pointer)) yaooc_json_integer_swap,
  .virtual_dtor = (void (*) (pointer p)) yaooc_json_integer_virtual_dtor,
  .virtual_copy_ctor = (void (*) (pointer,const_pointer)) yaooc_json_integer_virtual_copy_ctor,
  .virtual_assign = (void (*) (pointer,const_pointer)) yaooc_json_integer_virtual_assign,
  .virtual_less_than_compare = (bool (*) (const_pointer,const_pointer)) yaooc_json_integer_virtual_less_than_compare,
  .type = (yaooc_json_type_t (*) (const_pointer)) yaooc_json_value_type,
  .print = (void (*) (const_pointer,ostream_pointer)) yaooc_json_integer_print,
  .set = (void (*) (pointer p,int64_t)) yaooc_json_integer_set,
  .get = (int64_t (*) (const_pointer p)) yaooc_json_integer_get,
};


DEFINE_TYPE_INFO(yaooc_json_integer,Y,N,N,N,N,N,N,Y,yaooc_json_value);
/* Private items for yaooc_json_real */

/* Protected items for yaooc_json_real */


/* Typeinfo for yaooc_json_real */
void yaooc_json_real_default_ctor(pointer p)
{
  yaooc_json_real_pointer this=p;
  this->type_=JSON_REAL;
  this->real_=0;
}
/*
void yaooc_json_real_copy_ctor(pointer d,const_pointer s)
{
  yaooc_json_real_pointer dst=d;
  yaooc_json_real_const_pointer src=s;
}
*/
/* Constructors for yaooc_json_real */
void yaooc_json_real_ctor_real(pointer p,va_list args)
{
  yaooc_json_real_pointer this=p;
  this->type_=JSON_REAL;
  this->real_ = va_arg(args,double);
}

/* Class table methods for yaooc_json_real */
void yaooc_json_real_virtual_dtor(pointer p)
{
}

void yaooc_json_real_virtual_copy_ctor(pointer p,const_pointer s)
{
  yaooc_json_real_pointer this=p;
  this->type_=JSON_REAL;
  this->real_=((yaooc_json_real_const_pointer)s)->real_;
}

void yaooc_json_real_virtual_assign(pointer p,const_pointer s)
{
  yaooc_json_real_pointer this=p;
  if(this->type_==JSON_UNDEFINED || this->type_==JSON_REAL) {
    this->class_table_=&yaooc_json_real_class_table;
    this->type_=JSON_REAL;
    this->real_=((yaooc_json_real_const_pointer)s)->real_;
  } else {
		THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,
					"Attempt to assign JSON_REAL to %s",yaooc_json_type_strings[this->type_]));
  }
}

bool yaooc_json_real_virtual_less_than_compare(const_pointer p,const_pointer o)
{
  return ((yaooc_json_real_const_pointer)p)->real_ < ((yaooc_json_real_const_pointer)o)->real_;
}

void yaooc_json_real_print(const_pointer p,ostream_pointer s)
{
  yaooc_json_real_const_pointer this=p;
	yaooc_ostream_pointer strm=s;
	M(strm,printf,"%lg",this->real_);
}

void yaooc_json_real_set(pointer p,double value)
{
  yaooc_json_real_pointer this=p;
  this->real_=value;
}

double yaooc_json_real_get(const_pointer p)
{
  return ((yaooc_json_real_const_pointer)p)->real_;
}


/* Class table for yaooc_json_real */
yaooc_json_real_class_table_t yaooc_json_real_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_json_value_class_table,
  .type_name_ = (const char*) "yaooc_json_real_t",
  .swap = (void (*) (pointer p,pointer)) yaooc_json_real_swap,
  .virtual_dtor = (void (*) (pointer p)) yaooc_json_real_virtual_dtor,
  .virtual_copy_ctor = (void (*) (pointer,const_pointer)) yaooc_json_real_virtual_copy_ctor,
  .virtual_assign = (void (*) (pointer,const_pointer)) yaooc_json_real_virtual_assign,
  .virtual_less_than_compare = (bool (*) (const_pointer,const_pointer)) yaooc_json_real_virtual_less_than_compare,
  .type = (yaooc_json_type_t (*) (const_pointer)) yaooc_json_value_type,
  .print = (void (*) (const_pointer,ostream_pointer)) yaooc_json_real_print,
  .set = (void (*) (pointer p,double)) yaooc_json_real_set,
  .get = (double (*) (const_pointer p)) yaooc_json_real_get,
};


DEFINE_TYPE_INFO(yaooc_json_real,Y,N,N,N,N,N,N,Y,yaooc_json_value);
/* Private items for yaooc_json_string */

/* Protected items for yaooc_json_string */


/* Typeinfo for yaooc_json_string */
void yaooc_json_string_default_ctor(pointer p)
{
  yaooc_json_string_pointer this=p;
  this->type_=JSON_STRING;
  this->string_=STRDUP("");
}
/*
void yaooc_json_string_copy_ctor(pointer d,const_pointer s)
{
  yaooc_json_string_pointer dst=d;
  yaooc_json_string_const_pointer src=s;
}
*/
/* Constructors for yaooc_json_string */
void yaooc_json_string_ctor_ccs(pointer p,va_list args)
{
  yaooc_json_string_pointer this=p;
  const char* str = va_arg(args,const char*);
  this->type_=JSON_STRING;
  this->string_=STRDUP(str == NULL ? "" : str);
}
void yaooc_json_string_ctor_ccs_size(pointer p,va_list args)
{
  yaooc_json_string_pointer this=p;
  const char* str = va_arg(args,const char*);
  size_t n = va_arg(args,size_t);
  this->type_=JSON_STRING;
  if(str && n>0) {
    if(n>strlen(str)) n=strlen(str);
    this->string_=MALLOC(n+1);
    strncpy(this->string_,str,n);
    this->string_[n]=0;
  } else
    this->string_=STRDUP("");
}

/* Class table methods for yaooc_json_string */
void yaooc_json_string_virtual_dtor(pointer p)
{
  yaooc_json_string_pointer this=p;
  FREE(this->string_);
}

void yaooc_json_string_virtual_copy_ctor(pointer p,const_pointer s)
{
  yaooc_json_string_pointer this=p;
  this->type_=JSON_STRING;
  this->string_=STRDUP(((yaooc_json_string_const_pointer)s)->string_);
}

void yaooc_json_string_virtual_assign(pointer p,const_pointer s)
{
  yaooc_json_string_pointer this=p;
  if(this->type_==JSON_UNDEFINED) {
    this->class_table_=&yaooc_json_string_class_table;
    yaooc_json_string_default_ctor(this);
  }
  if(this->type_==JSON_STRING) {
    FREE(this->string_);
    this->string_=STRDUP(((yaooc_json_string_const_pointer)s)->string_);
  } else {
		THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,
					"Attempt to assign JSON_STRING to %s",yaooc_json_type_strings[this->type_]));
  }
}

bool yaooc_json_string_virtual_less_than_compare(const_pointer p,const_pointer o)
{
  return strcmp(((yaooc_json_string_const_pointer)p)->string_,((yaooc_json_string_const_pointer)o)->string_)<0;
}

void yaooc_json_string_print(const_pointer p,ostream_pointer s)
{
  yaooc_json_string_const_pointer this=p;
	yaooc_ostream_pointer strm=s;
	M(strm,printf,"\"%s\"",this->string_);
}

void yaooc_json_string_set(pointer p,const char* value)
{
  yaooc_json_string_pointer this=p;
  FREE(this->string_);
  this->string_=STRDUP(value);
}

const char* yaooc_json_string_get(const_pointer p)
{
  return ((yaooc_json_string_const_pointer)p)->string_;
}

size_t yaooc_json_string_size(const_pointer p)
{
  return strlen(((yaooc_json_string_const_pointer)p)->string_);
}

void yaooc_json_string_clear(pointer p)
{
  yaooc_json_string_pointer this=p;
  FREE(this->string_);
  this->string_=STRDUP("");
}


/* Class table for yaooc_json_string */
yaooc_json_string_class_table_t yaooc_json_string_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_json_value_class_table,
  .type_name_ = (const char*) "yaooc_json_string_t",
  .swap = (void (*) (pointer p,pointer)) yaooc_json_string_swap,
  .virtual_dtor = (void (*) (pointer p)) yaooc_json_string_virtual_dtor,
  .virtual_copy_ctor = (void (*) (pointer,const_pointer)) yaooc_json_string_virtual_copy_ctor,
  .virtual_assign = (void (*) (pointer,const_pointer)) yaooc_json_string_virtual_assign,
  .virtual_less_than_compare = (bool (*) (const_pointer,const_pointer)) yaooc_json_string_virtual_less_than_compare,
  .type = (yaooc_json_type_t (*) (const_pointer)) yaooc_json_value_type,
  .print = (void (*) (const_pointer,ostream_pointer)) yaooc_json_string_print,
  .set = (void (*) (pointer p,const char*)) yaooc_json_string_set,
  .get = (const char* (*) (const_pointer p)) yaooc_json_string_get,
  .size = (size_t (*) (const_pointer)) yaooc_json_string_size,
  .clear = (void (*) (pointer p)) yaooc_json_string_clear,
};


DEFINE_TYPE_INFO(yaooc_json_string,Y,N,N,N,N,N,N,Y,yaooc_json_value);


VECTOR_IMPLEMENTATION(yaooc_json_value,yaooc_json_value_array);

/* Private items for yaooc_json_array */

/* Protected items for yaooc_json_array */


/* Typeinfo for yaooc_json_array */
void yaooc_json_array_default_ctor(pointer p)
{
  yaooc_json_array_pointer this=p;
  this->type_=JSON_ARRAY;
  this->array_=new(yaooc_json_value_array);
}
/*
void yaooc_json_array_copy_ctor(pointer d,const_pointer s)
{
  yaooc_json_array_pointer dst=d;
  yaooc_json_array_const_pointer src=s;
}
*/
/* Constructors for yaooc_json_array */

/* Class table methods for yaooc_json_array */
void yaooc_json_array_virtual_dtor(pointer p)
{
  yaooc_json_array_pointer this=p;
  delete(this->array_);
}

void yaooc_json_array_virtual_copy_ctor(pointer p,const_pointer s)
{
  yaooc_json_array_pointer this=p;
  yaooc_json_array_default_ctor(p);
  assign(this->array_,((yaooc_json_array_pointer)s)->array_);
}

void yaooc_json_array_virtual_assign(pointer p,const_pointer s)
{
  yaooc_json_array_pointer this=p;
  if(this->type_==JSON_UNDEFINED) {
    this->class_table_=&yaooc_json_array_class_table;
    yaooc_json_array_default_ctor(this);
  }
  if(this->type_==JSON_ARRAY) {
    assign(this->array_,((yaooc_json_array_pointer)s)->array_);
  } else {
		THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,
					"Attempt to assign JSON_ARRAY to %s",yaooc_json_type_strings[this->type_]));
  }
}

bool yaooc_json_array_virtual_less_than_compare(const_pointer p,const_pointer o)
{
  return false;
}

void yaooc_json_array_print(const_pointer p,ostream_pointer s)
{
  yaooc_json_array_const_pointer this=p;
	yaooc_ostream_pointer strm=s;
	yaooc_json_array_const_iterator ia;
	M(strm,printf,"[");
	if(M(this,size)>0) {
		ia=M(this,begin);
		M(ia,print,s);
		for(ia++;ia!=M(this,end);ia++) {
			M(strm,printf,",");
			M(ia,print,s);
		}
	}
	M(strm,printf,"]");
}

yaooc_json_array_iterator yaooc_json_array_insert(pointer p,pointer value)
{
  yaooc_json_array_pointer this=p;
  const_iterator pos=M(this->array_,end);
  return M(this->array_,insert,pos,value);
}

void yaooc_json_array_erase(pointer p,pointer value)
{
  yaooc_json_array_pointer this=p;
  M(this->array_,erase_value,value);
}

void yaooc_json_array_clear(pointer p)
{
  yaooc_json_array_pointer this=p;
  M(this->array_,clear);
}

size_t yaooc_json_array_size(const_pointer p)
{
  yaooc_json_array_const_pointer this=p;
  return M(this->array_,size);
}

yaooc_json_array_iterator yaooc_json_array_at(const_pointer p,size_t i)
{
  yaooc_json_array_const_pointer this=p;
  return M(this->array_,at,i);
}

yaooc_json_array_iterator yaooc_json_array_begin(const_pointer p)
{
  yaooc_json_array_const_pointer this=p;
  return M(this->array_,begin);
}

yaooc_json_array_iterator yaooc_json_array_end(const_pointer p)
{
  yaooc_json_array_const_pointer this=p;
  return M(this->array_,end);
}


/* Class table for yaooc_json_array */
yaooc_json_array_class_table_t yaooc_json_array_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_json_value_class_table,
  .type_name_ = (const char*) "yaooc_json_array_t",
  .swap = (void (*) (pointer p,pointer)) yaooc_json_array_swap,
  .virtual_dtor = (void (*) (pointer p)) yaooc_json_array_virtual_dtor,
  .virtual_copy_ctor = (void (*) (pointer,const_pointer)) yaooc_json_array_virtual_copy_ctor,
  .virtual_assign = (void (*) (pointer,const_pointer)) yaooc_json_array_virtual_assign,
  .virtual_less_than_compare = (bool (*) (const_pointer,const_pointer)) yaooc_json_array_virtual_less_than_compare,
  .type = (yaooc_json_type_t (*) (const_pointer)) yaooc_json_value_type,
  .print = (void (*) (const_pointer,ostream_pointer)) yaooc_json_array_print,
  .insert = (yaooc_json_array_iterator (*) (pointer p,pointer)) yaooc_json_array_insert,
  .erase = (void (*) (pointer p,pointer)) yaooc_json_array_erase,
  .clear = (void (*) (pointer p)) yaooc_json_array_clear,
  .size = (size_t (*) (const_pointer p)) yaooc_json_array_size,
  .at = (yaooc_json_array_iterator (*) (const_pointer p,size_t)) yaooc_json_array_at,
  .begin = (yaooc_json_array_iterator (*) (const_pointer p)) yaooc_json_array_begin,
  .end = (yaooc_json_array_iterator (*) (const_pointer p)) yaooc_json_array_end,
};


DEFINE_TYPE_INFO(yaooc_json_array,Y,N,N,N,N,N,N,Y,yaooc_json_value);


MINI_MAP_IMPLEMENTATION(yaooc_json_string,yaooc_json_value,yaooc_json_string_value_map);


/* Private items for yaooc_json_object */

/* Protected items for yaooc_json_object */


/* Typeinfo for yaooc_json_object */
void yaooc_json_object_default_ctor(pointer p)
{
  yaooc_json_object_pointer this=p;
  this->type_=JSON_OBJECT;
  this->object_=new(yaooc_json_string_value_map);
}
/*
void yaooc_json_object_copy_ctor(pointer d,const_pointer s)
{
  yaooc_json_object_pointer dst=d;
  yaooc_json_object_const_pointer src=s;
}
*/
/* Constructors for yaooc_json_object */

/* Class table methods for yaooc_json_object */
void yaooc_json_object_virtual_dtor(pointer p)
{
  yaooc_json_object_pointer this=p;
  delete(this->object_);
}

void yaooc_json_object_virtual_copy_ctor(pointer p,const_pointer s)
{
  yaooc_json_object_pointer this=p;
  yaooc_json_object_default_ctor(p);
  assign(this->object_,((yaooc_json_object_const_pointer)s)->object_);
}

void yaooc_json_object_virtual_assign(pointer p,const_pointer s)
{
  yaooc_json_object_pointer this=p;
  if(this->type_==JSON_UNDEFINED) {
    this->class_table_=&yaooc_json_object_class_table;
    yaooc_json_object_default_ctor(this);
  }
  if(this->type_==JSON_OBJECT) {
    assign(this->object_,((yaooc_json_object_const_pointer)s)->object_);
  } else {
		THROW(new_ctor(yaooc_json_exception,yaooc_json_exception_ctor_v,
					"Attempt to assign JSON_OBJECT to %s",yaooc_json_type_strings[this->type_]));
  }
}

bool yaooc_json_object_virtual_less_than_compare(const_pointer p,const_pointer o)
{
  return false;
}

void yaooc_json_object_print(const_pointer p,ostream_pointer s)
{
  yaooc_json_object_const_pointer this=p;
	yaooc_ostream_pointer strm=s;
	M(strm,printf,"{");
	yaooc_json_object_const_iterator io;
	if(M(this,size)>0) {
		io=M(this->object_,begin);
		M(&io->first,print,s);
		M(strm,printf,":");
		M(&io->second,print,s);
		for(io++;io!=M(this->object_,end);io++) {
			M(strm,printf,",");
			M(&io->first,print,s);
			M(strm,printf,":");
			M(&io->second,print,s);
		}
  }
	M(strm,printf,"}");
}

yaooc_json_object_iterator yaooc_json_object_insert(pointer p,const_pointer str,const_pointer val)
{
  yaooc_json_object_pointer this=p;
  return M(this->object_,insert,str,val);
}

void yaooc_json_object_erase(pointer p,const_pointer str)
{
  yaooc_json_object_pointer this=p;
  M(this->object_,erase_key,str);
}

void yaooc_json_object_clear(pointer p)
{
  yaooc_json_object_pointer this=p;
  M(this->object_,clear);
}

size_t yaooc_json_object_size(const_pointer p)
{
  yaooc_json_object_const_pointer this=p;
  return M(this->object_,size);
}

yaooc_json_value_pointer yaooc_json_object_at(const_pointer p,const_pointer str)
{
  yaooc_json_object_const_pointer this=p;
  return M(this->object_,at,str);
}

yaooc_json_object_iterator yaooc_json_object_begin(const_pointer p)
{
  yaooc_json_object_const_pointer this=p;
  return M(this->object_,begin);
}

yaooc_json_object_iterator yaooc_json_object_end(const_pointer p)
{
  yaooc_json_object_const_pointer this=p;
  return M(this->object_,end);
}


/* Class table for yaooc_json_object */
yaooc_json_object_class_table_t yaooc_json_object_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_json_value_class_table,
  .type_name_ = (const char*) "yaooc_json_object_t",
  .swap = (void (*) (pointer p,pointer)) yaooc_json_object_swap,
  .virtual_dtor = (void (*) (pointer p)) yaooc_json_object_virtual_dtor,
  .virtual_copy_ctor = (void (*) (pointer,const_pointer)) yaooc_json_object_virtual_copy_ctor,
  .virtual_assign = (void (*) (pointer,const_pointer)) yaooc_json_object_virtual_assign,
  .virtual_less_than_compare = (bool (*) (const_pointer,const_pointer)) yaooc_json_object_virtual_less_than_compare,
  .type = (yaooc_json_type_t (*) (const_pointer)) yaooc_json_value_type,
  .print = (void (*) (const_pointer,ostream_pointer)) yaooc_json_object_print,
  .insert = (yaooc_json_object_iterator (*) (pointer p,const_pointer,const_pointer)) yaooc_json_object_insert,
  .erase = (void (*) (pointer p,const_pointer)) yaooc_json_object_erase,
  .clear = (void (*) (pointer p)) yaooc_json_object_clear,
  .size = (size_t (*) (const_pointer p)) yaooc_json_object_size,
  .at = (yaooc_json_value_pointer (*) (const_pointer p,const_pointer)) yaooc_json_object_at,
  .begin = (yaooc_json_object_iterator (*) (const_pointer p)) yaooc_json_object_begin,
  .end = (yaooc_json_object_iterator (*) (const_pointer p)) yaooc_json_object_end,
};


DEFINE_TYPE_INFO(yaooc_json_object,Y,N,N,N,N,N,N,Y,yaooc_json_value);
/*  End YAOOC PreProcessor generated content */
