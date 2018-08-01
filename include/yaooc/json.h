/*
		Copyright (C) 2016-2018  by Terry N Bezue

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

#ifndef __JSON_INCLUDED__
#define __JSON_INCLUDED__

#include <yaooc/exception.h>
#include <yaooc/stream.h>
#include <yaooc/vector.h>
#include <yaooc/map.h>

typedef enum { JSON_UNDEFINED=0, JSON_NULL, JSON_BOOL, JSON_INTEGER, JSON_REAL, JSON_STRING,
        JSON_ARRAY, JSON_OBJECT } yaooc_json_type_t;

yaooc_class_forward(yaooc_json_value_array)
yaooc_class_forward(yaooc_json_string_value_map)

typedef union {
  bool    bool_;
  int64_t int_;
  double  real_;
  char*   string_;
  yaooc_json_value_array_t* array_;
  yaooc_json_string_value_map_t* object_;
} json_data_t;

/*  Begin YAOOC PreProcessor generated content */

/*
  Class definition for yaooc_json_exception
*/
yaooc_class_table(yaooc_json_exception)
{
  yaooc_exception_class_table_t;
};

yaooc_class_instance(yaooc_json_exception)
{
  yaooc_exception_class_instance_t;
  char* exception_str_;
};

yaooc_class(yaooc_json_exception);
/* Prototypes for yaooc_json_exception type info */
void yaooc_json_exception_default_ctor(pointer);
void yaooc_json_exception_dtor(pointer);
void yaooc_json_exception_copy_ctor(pointer,const_pointer);
void yaooc_json_exception_assign(pointer,const_pointer);

/* Constructors for yaooc_json_exception */
void yaooc_json_exception_ctor_ccs(pointer,va_list);

/* Prototypes for yaooc_json_exception class table*/
const char* yaooc_json_exception_isa(const_pointer);
#define yaooc_json_exception_is_descendant yaooc_exception_is_descendant
#define yaooc_json_exception_swap yaooc_exception_swap
const char* yaooc_json_exception_what(const_pointer);

/* Prototypes for yaooc_json_exception class instance*/

/* Prototypes for yaooc_json_exception class protected items*/


/*
  Class definition for yaooc_json_value
*/
yaooc_class_table(yaooc_json_value)
{
  yaooc_object_class_table_t;
  void (*virtual_dtor)(pointer);
  void (*virtual_copy_ctor)(pointer,const_pointer);
  void (*virtual_assign)(pointer,const_pointer);
  bool (*virtual_less_than_compare)(const_pointer,const_pointer);
  yaooc_json_type_t (*type)(const_pointer);
  void (*print)(const_pointer,ostream_pointer);
};

yaooc_class_instance(yaooc_json_value)
{
  yaooc_object_class_instance_t;
  yaooc_json_type_t type_;
  json_data_t;
};

yaooc_class(yaooc_json_value);
/* Prototypes for yaooc_json_value type info */
void yaooc_json_value_default_ctor(pointer);
void yaooc_json_value_dtor(pointer);
void yaooc_json_value_copy_ctor(pointer,const_pointer);
void yaooc_json_value_assign(pointer,const_pointer);
bool yaooc_json_value_less_than_compare(const_pointer,const_pointer);

/* Constructors for yaooc_json_value */

/* Prototypes for yaooc_json_value class table*/
const char* yaooc_json_value_isa(const_pointer);
#define yaooc_json_value_is_descendant yaooc_object_is_descendant
#define yaooc_json_value_swap yaooc_object_swap
void yaooc_json_value_virtual_dtor(pointer);
void yaooc_json_value_virtual_copy_ctor(pointer,const_pointer);
void yaooc_json_value_virtual_assign(pointer,const_pointer);
bool yaooc_json_value_virtual_less_than_compare(const_pointer,const_pointer);
yaooc_json_type_t yaooc_json_value_type(const_pointer);
void yaooc_json_value_print(const_pointer,ostream_pointer);

/* Prototypes for yaooc_json_value class instance*/

/* Prototypes for yaooc_json_value class protected items*/


/*
  Class definition for yaooc_json_null
*/
yaooc_class_table(yaooc_json_null)
{
  yaooc_json_value_class_table_t;
};

yaooc_class_instance(yaooc_json_null)
{
  yaooc_json_value_class_instance_t;
};

yaooc_class(yaooc_json_null);
/* Prototypes for yaooc_json_null type info */
void yaooc_json_null_default_ctor(pointer);
void yaooc_json_null_copy_ctor(pointer,const_pointer);

/* Constructors for yaooc_json_null */

/* Prototypes for yaooc_json_null class table*/
const char* yaooc_json_null_isa(const_pointer);
#define yaooc_json_null_is_descendant yaooc_json_value_is_descendant
#define yaooc_json_null_swap yaooc_json_value_swap
void yaooc_json_null_virtual_dtor(pointer);
void yaooc_json_null_virtual_copy_ctor(pointer,const_pointer);
void yaooc_json_null_virtual_assign(pointer,const_pointer);
bool yaooc_json_null_virtual_less_than_compare(const_pointer,const_pointer);
void yaooc_json_null_print(const_pointer,ostream_pointer);

/* Prototypes for yaooc_json_null class instance*/

/* Prototypes for yaooc_json_null class protected items*/


/*
  Class definition for yaooc_json_bool
*/
yaooc_class_table(yaooc_json_bool)
{
  yaooc_json_value_class_table_t;
  void (*set)(pointer,bool);
  bool (*get)(const_pointer);
};

yaooc_class_instance(yaooc_json_bool)
{
  yaooc_json_value_class_instance_t;
};

yaooc_class(yaooc_json_bool);
/* Prototypes for yaooc_json_bool type info */
void yaooc_json_bool_default_ctor(pointer);
void yaooc_json_bool_copy_ctor(pointer,const_pointer);

/* Constructors for yaooc_json_bool */
void yaooc_json_bool_ctor_bool(pointer,va_list);

/* Prototypes for yaooc_json_bool class table*/
const char* yaooc_json_bool_isa(const_pointer);
#define yaooc_json_bool_is_descendant yaooc_json_value_is_descendant
#define yaooc_json_bool_swap yaooc_json_value_swap
void yaooc_json_bool_virtual_dtor(pointer);
void yaooc_json_bool_virtual_copy_ctor(pointer,const_pointer);
void yaooc_json_bool_virtual_assign(pointer,const_pointer);
bool yaooc_json_bool_virtual_less_than_compare(const_pointer,const_pointer);
void yaooc_json_bool_print(const_pointer,ostream_pointer);
void yaooc_json_bool_set(pointer,bool);
bool yaooc_json_bool_get(const_pointer);

/* Prototypes for yaooc_json_bool class instance*/

/* Prototypes for yaooc_json_bool class protected items*/


/*
  Class definition for yaooc_json_integer
*/
yaooc_class_table(yaooc_json_integer)
{
  yaooc_json_value_class_table_t;
  void (*set)(pointer,int64_t);
  int64_t (*get)(const_pointer);
};

yaooc_class_instance(yaooc_json_integer)
{
  yaooc_json_value_class_instance_t;
};

yaooc_class(yaooc_json_integer);
/* Prototypes for yaooc_json_integer type info */
void yaooc_json_integer_default_ctor(pointer);
void yaooc_json_integer_copy_ctor(pointer,const_pointer);

/* Constructors for yaooc_json_integer */
void yaooc_json_integer_ctor_int(pointer,va_list);

/* Prototypes for yaooc_json_integer class table*/
const char* yaooc_json_integer_isa(const_pointer);
#define yaooc_json_integer_is_descendant yaooc_json_value_is_descendant
#define yaooc_json_integer_swap yaooc_json_value_swap
void yaooc_json_integer_virtual_dtor(pointer);
void yaooc_json_integer_virtual_copy_ctor(pointer,const_pointer);
void yaooc_json_integer_virtual_assign(pointer,const_pointer);
bool yaooc_json_integer_virtual_less_than_compare(const_pointer,const_pointer);
void yaooc_json_integer_print(const_pointer,ostream_pointer);
void yaooc_json_integer_set(pointer,int64_t);
int64_t yaooc_json_integer_get(const_pointer);

/* Prototypes for yaooc_json_integer class instance*/

/* Prototypes for yaooc_json_integer class protected items*/


/*
  Class definition for yaooc_json_real
*/
yaooc_class_table(yaooc_json_real)
{
  yaooc_json_value_class_table_t;
  void (*set)(pointer,double);
  double (*get)(const_pointer);
};

yaooc_class_instance(yaooc_json_real)
{
  yaooc_json_value_class_instance_t;
};

yaooc_class(yaooc_json_real);
/* Prototypes for yaooc_json_real type info */
void yaooc_json_real_default_ctor(pointer);
void yaooc_json_real_copy_ctor(pointer,const_pointer);

/* Constructors for yaooc_json_real */
void yaooc_json_real_ctor_real(pointer,va_list);

/* Prototypes for yaooc_json_real class table*/
const char* yaooc_json_real_isa(const_pointer);
#define yaooc_json_real_is_descendant yaooc_json_value_is_descendant
#define yaooc_json_real_swap yaooc_json_value_swap
void yaooc_json_real_virtual_dtor(pointer);
void yaooc_json_real_virtual_copy_ctor(pointer,const_pointer);
void yaooc_json_real_virtual_assign(pointer,const_pointer);
bool yaooc_json_real_virtual_less_than_compare(const_pointer,const_pointer);
void yaooc_json_real_print(const_pointer,ostream_pointer);
void yaooc_json_real_set(pointer,double);
double yaooc_json_real_get(const_pointer);

/* Prototypes for yaooc_json_real class instance*/

/* Prototypes for yaooc_json_real class protected items*/


/*
  Class definition for yaooc_json_string
*/
yaooc_class_table(yaooc_json_string)
{
  yaooc_json_value_class_table_t;
  void (*set)(pointer,const char*);
  const char* (*get)(const_pointer);
  size_t (*size)(const_pointer);
  void (*clear)(pointer);
};

yaooc_class_instance(yaooc_json_string)
{
  yaooc_json_value_class_instance_t;
};

yaooc_class(yaooc_json_string);
/* Prototypes for yaooc_json_string type info */
void yaooc_json_string_default_ctor(pointer);
void yaooc_json_string_copy_ctor(pointer,const_pointer);

/* Constructors for yaooc_json_string */
void yaooc_json_string_ctor_ccs(pointer,va_list);
void yaooc_json_string_ctor_ccs_size(pointer,va_list);

/* Prototypes for yaooc_json_string class table*/
const char* yaooc_json_string_isa(const_pointer);
#define yaooc_json_string_is_descendant yaooc_json_value_is_descendant
#define yaooc_json_string_swap yaooc_json_value_swap
void yaooc_json_string_virtual_dtor(pointer);
void yaooc_json_string_virtual_copy_ctor(pointer,const_pointer);
void yaooc_json_string_virtual_assign(pointer,const_pointer);
bool yaooc_json_string_virtual_less_than_compare(const_pointer,const_pointer);
void yaooc_json_string_print(const_pointer,ostream_pointer);
void yaooc_json_string_set(pointer,const char*);
const char* yaooc_json_string_get(const_pointer);
size_t yaooc_json_string_size(const_pointer);
void yaooc_json_string_clear(pointer);

/* Prototypes for yaooc_json_string class instance*/

/* Prototypes for yaooc_json_string class protected items*/

VECTOR_DEFINITION(yaooc_json_value,yaooc_json_value_array)
typedef yaooc_json_value_array_iterator yaooc_json_array_iterator;
typedef yaooc_json_value_array_const_iterator yaooc_json_array_const_iterator;

/*
  Class definition for yaooc_json_array
*/
yaooc_class_table(yaooc_json_array)
{
  yaooc_json_value_class_table_t;
  yaooc_json_array_iterator (*insert)(pointer,pointer);
  void (*erase)(pointer,pointer);
  void (*clear)(pointer);
  size_t (*size)(const_pointer);
  yaooc_json_array_iterator (*at)(const_pointer,size_t);
  yaooc_json_array_iterator (*begin)(const_pointer);
  yaooc_json_array_iterator (*end)(const_pointer);
};

yaooc_class_instance(yaooc_json_array)
{
  yaooc_json_value_class_instance_t;
};

yaooc_class(yaooc_json_array);
/* Prototypes for yaooc_json_array type info */
void yaooc_json_array_default_ctor(pointer);
void yaooc_json_array_copy_ctor(pointer,const_pointer);

/* Constructors for yaooc_json_array */

/* Prototypes for yaooc_json_array class table*/
const char* yaooc_json_array_isa(const_pointer);
#define yaooc_json_array_is_descendant yaooc_json_value_is_descendant
#define yaooc_json_array_swap yaooc_json_value_swap
void yaooc_json_array_virtual_dtor(pointer);
void yaooc_json_array_virtual_copy_ctor(pointer,const_pointer);
void yaooc_json_array_virtual_assign(pointer,const_pointer);
bool yaooc_json_array_virtual_less_than_compare(const_pointer,const_pointer);
void yaooc_json_array_print(const_pointer,ostream_pointer);
yaooc_json_array_iterator yaooc_json_array_insert(pointer,pointer);
void yaooc_json_array_erase(pointer,pointer);
void yaooc_json_array_clear(pointer);
size_t yaooc_json_array_size(const_pointer);
yaooc_json_array_iterator yaooc_json_array_at(const_pointer,size_t);
yaooc_json_array_iterator yaooc_json_array_begin(const_pointer);
yaooc_json_array_iterator yaooc_json_array_end(const_pointer);

/* Prototypes for yaooc_json_array class instance*/

/* Prototypes for yaooc_json_array class protected items*/

MINI_MAP_DEFINITION(yaooc_json_string,yaooc_json_value,yaooc_json_string_value_map)
typedef yaooc_json_string_value_map_iterator yaooc_json_object_iterator;
typedef yaooc_json_string_value_map_const_iterator yaooc_json_object_const_iterator;

/*
  Class definition for yaooc_json_object
*/
yaooc_class_table(yaooc_json_object)
{
  yaooc_json_value_class_table_t;
  yaooc_json_object_iterator (*insert)(pointer,const_pointer,const_pointer);
  void (*erase)(pointer,const_pointer);
  void (*clear)(pointer);
  size_t (*size)(const_pointer);
  yaooc_json_value_pointer (*at)(const_pointer,const_pointer);
  yaooc_json_object_iterator (*begin)(const_pointer);
  yaooc_json_object_iterator (*end)(const_pointer);
};

yaooc_class_instance(yaooc_json_object)
{
  yaooc_json_value_class_instance_t;
};

yaooc_class(yaooc_json_object);
/* Prototypes for yaooc_json_object type info */
void yaooc_json_object_default_ctor(pointer);
void yaooc_json_object_copy_ctor(pointer,const_pointer);

/* Constructors for yaooc_json_object */

/* Prototypes for yaooc_json_object class table*/
const char* yaooc_json_object_isa(const_pointer);
#define yaooc_json_object_is_descendant yaooc_json_value_is_descendant
#define yaooc_json_object_swap yaooc_json_value_swap
void yaooc_json_object_virtual_dtor(pointer);
void yaooc_json_object_virtual_copy_ctor(pointer,const_pointer);
void yaooc_json_object_virtual_assign(pointer,const_pointer);
bool yaooc_json_object_virtual_less_than_compare(const_pointer,const_pointer);
void yaooc_json_object_print(const_pointer,ostream_pointer);
yaooc_json_object_iterator yaooc_json_object_insert(pointer,const_pointer,const_pointer);
void yaooc_json_object_erase(pointer,const_pointer);
void yaooc_json_object_clear(pointer);
size_t yaooc_json_object_size(const_pointer);
yaooc_json_value_pointer yaooc_json_object_at(const_pointer,const_pointer);
yaooc_json_object_iterator yaooc_json_object_begin(const_pointer);
yaooc_json_object_iterator yaooc_json_object_end(const_pointer);

/* Prototypes for yaooc_json_object class instance*/

/* Prototypes for yaooc_json_object class protected items*/

/*  End YAOOC PreProcessor generated content */

#endif
