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

#ifndef __TEMPLATE_OBJECTS_INCLUDED__
#define __TEMPLATE_OBJECTS_INCLUDED__

#include <stdio.h>
#include <yaooc/object.h>
#include <yaooc/memory.h>
#include <yaooc/string.h>
#include <yaooc/vector.h>
#include <yaooc/fstream.h>

class_forward(yaoocpp_item);
DYNAMIC_POINTER_DEFINITION(yaoocpp_item,yaoocpp_item_ptr);
VECTOR_DEFINITION(yaoocpp_item_ptr,yaoocpp_item_ptr_vector);

#define DEFINED_IN_CURRENT_CLASS 1
#define DEFINED_IN_PARENT_CLASS (1<<1)
#define OVERRIDEN_IN_CURRENT_CLASS (1<<2)

/*  Begin YAOOC PreProcessor generated content */


/*
  Class definition for yaoocpp_item
*/
class_table(yaoocpp_item)
{
  yaooc_object_class_table_t;
  void (*virtual_dtor)(pointer);
  bool (*virtual_less_than_compare)(const_pointer,const_pointer);
  void (*dump)(const_pointer,yaooc_ofstream_pointer);
  void (*print_prototype)(const_pointer,yaooc_ofstream_pointer);
  void (*print_implementation)(const_pointer,yaooc_ofstream_pointer);
  void (*print_class_prototype)(const_pointer,yaooc_ofstream_pointer);
  void (*print_class_implementation)(const_pointer,yaooc_ofstream_pointer);
};

class_instance(yaoocpp_item)
{
  yaooc_object_class_instance_t;
  unsigned int flags_;
};

class(yaoocpp_item);
/* Prototypes for yaoocpp_item type info */
void yaoocpp_item_default_ctor(pointer);
void yaoocpp_item_dtor(pointer);
void yaoocpp_item_copy_ctor(pointer,const_pointer);
void yaoocpp_item_assign(pointer,const_pointer);
bool yaoocpp_item_less_than_compare(const_pointer,const_pointer);

/* Constructors for yaoocpp_item */

/* Prototypes for yaoocpp_item class table*/
const char* yaoocpp_item_isa(const_pointer);
#define yaoocpp_item_is_descendant yaooc_object_is_descendant
#define yaoocpp_item_swap yaooc_object_swap

/* Prototypes for yaoocpp_item class instance*/

/* Prototypes for yaoocpp_item class protected items*/


/*
  Class definition for yaoocpp_argument
*/
class_table(yaoocpp_argument)
{
  yaoocpp_item_class_table_t;
  const char* (*type) (const_pointer);
  const char* (*name) (const_pointer);
};

class_instance(yaoocpp_argument)
{
  yaoocpp_item_class_instance_t;
  yaooc_string_t* name_;
  yaooc_string_t* type_;
};

class(yaoocpp_argument);
/* Prototypes for yaoocpp_argument type info */
void yaoocpp_argument_default_ctor(pointer);
void yaoocpp_argument_copy_ctor(pointer,const_pointer);
void yaoocpp_argument_assign(pointer,const_pointer);

/* Constructors for yaoocpp_argument */

/* Prototypes for yaoocpp_argument class table*/
const char* yaoocpp_argument_isa(const_pointer);
#define yaoocpp_argument_is_descendant yaoocpp_item_is_descendant
#define yaoocpp_argument_swap yaoocpp_item_swap
void yaoocpp_argument_virtual_dtor(pointer);
bool yaoocpp_argument_virtual_less_than_compare(const_pointer,const_pointer);
void yaoocpp_argument_dump(const_pointer,yaooc_ofstream_pointer);
const char* yaoocpp_argument_type(const_pointer);
const char* yaoocpp_argument_name(const_pointer);

/* Prototypes for yaoocpp_argument class instance*/

/* Prototypes for yaoocpp_argument class protected items*/


/*
  Class definition for yaoocpp_variable
*/
class_table(yaoocpp_variable)
{
  yaoocpp_argument_class_table_t;
  const char* (*default_value)(const_pointer);
};

class_instance(yaoocpp_variable)
{
  yaoocpp_argument_class_instance_t;
  yaooc_string_t* default_value_;
};

class(yaoocpp_variable);
/* Prototypes for yaoocpp_variable type info */
void yaoocpp_variable_default_ctor(pointer);
void yaoocpp_variable_copy_ctor(pointer,const_pointer);
void yaoocpp_variable_assign(pointer,const_pointer);

/* Constructors for yaoocpp_variable */

/* Prototypes for yaoocpp_variable class table*/
const char* yaoocpp_variable_isa(const_pointer);
#define yaoocpp_variable_is_descendant yaoocpp_argument_is_descendant
#define yaoocpp_variable_swap yaoocpp_argument_swap
void yaoocpp_variable_virtual_dtor(pointer);
bool yaoocpp_variable_virtual_less_than_compare(const_pointer,const_pointer);
void yaoocpp_variable_dump(const_pointer,yaooc_ofstream_pointer);
const char* yaoocpp_variable_default_value(const_pointer);

/* Prototypes for yaoocpp_variable class instance*/

/* Prototypes for yaoocpp_variable class protected items*/


/*
  Class definition for yaoocpp_constructor
*/
class_table(yaoocpp_constructor)
{
  yaoocpp_item_class_table_t;
};

class_instance(yaoocpp_constructor)
{
  yaoocpp_item_class_instance_t;
  yaooc_string_t* name_;
  yaoocpp_item_ptr_vector_t* arguments_;
  yaooc_string_t* implementation_method_;
  yaooc_string_t* prefix_;
};

class(yaoocpp_constructor);
/* Prototypes for yaoocpp_constructor type info */
void yaoocpp_constructor_default_ctor(pointer);
void yaoocpp_constructor_copy_ctor(pointer,const_pointer);
void yaoocpp_constructor_assign(pointer,const_pointer);

/* Constructors for yaoocpp_constructor */

/* Prototypes for yaoocpp_constructor class table*/
const char* yaoocpp_constructor_isa(const_pointer);
#define yaoocpp_constructor_is_descendant yaoocpp_item_is_descendant
#define yaoocpp_constructor_swap yaoocpp_item_swap
void yaoocpp_constructor_virtual_dtor(pointer);
bool yaoocpp_constructor_virtual_less_than_compare(const_pointer,const_pointer);
void yaoocpp_constructor_dump(const_pointer,yaooc_ofstream_pointer);
void yaoocpp_constructor_print_prototype(const_pointer,yaooc_ofstream_pointer);
void yaoocpp_constructor_print_definition(const_pointer,yaooc_ofstream_pointer);

/* Prototypes for yaoocpp_constructor class instance*/

/* Prototypes for yaoocpp_constructor class protected items*/


/*
  Class definition for yaoocpp_method
*/
class_table(yaoocpp_method)
{
  yaoocpp_constructor_class_table_t;
};

class_instance(yaoocpp_method)
{
  yaoocpp_constructor_class_instance_t;
  yaooc_string_t* type_;
  bool is_const_;
};

class(yaoocpp_method);
/* Prototypes for yaoocpp_method type info */
void yaoocpp_method_default_ctor(pointer);
void yaoocpp_method_copy_ctor(pointer,const_pointer);
void yaoocpp_method_assign(pointer,const_pointer);

/* Constructors for yaoocpp_method */

/* Prototypes for yaoocpp_method class table*/
const char* yaoocpp_method_isa(const_pointer);
#define yaoocpp_method_is_descendant yaoocpp_constructor_is_descendant
#define yaoocpp_method_swap yaoocpp_constructor_swap
void yaoocpp_method_virtual_dtor(pointer);
bool yaoocpp_method_virtual_less_than_compare(const_pointer,const_pointer);
void yaoocpp_method_dump(const_pointer,yaooc_ofstream_pointer);
void yaoocpp_method_print_prototype(const_pointer,yaooc_ofstream_pointer);
void yaoocpp_method_print_definition(const_pointer,yaooc_ofstream_pointer);

/* Prototypes for yaoocpp_method class instance*/

/* Prototypes for yaoocpp_method class protected items*/


/*
  Class definition for yaoocpp_class
*/
class_table(yaoocpp_class)
{
  yaoocpp_item_class_table_t;
  void (*print_to_header)(const_pointer,yaooc_ofstream_pointer);
  void (*print_to_source)(const_pointer,yaooc_ofstream_pointer);
};

class_instance(yaoocpp_class)
{
  yaoocpp_item_class_instance_t;
  yaoocpp_class_t* parent_;
  yaooc_string_t* name_;
  yaoocpp_item_ptr_vector_t* constructors_;
  yaoocpp_item_ptr_vector_t* table_;
  yaoocpp_item_ptr_vector_t* instance_;
  yaoocpp_item_ptr_vector_t* private_;
  yaoocpp_item_ptr_vector_t* protected_;
  bool has_default_ctor_;
  bool has_dtor_;
  bool has_copy_ctor_;
  bool has_assign_;
  bool has_lt_cmp_;
	bool has_to_stream_;
	bool has_from_stream_;
  bool defined_in_top_level_file_;
};

class(yaoocpp_class);
/* Prototypes for yaoocpp_class type info */
void yaoocpp_class_default_ctor(pointer);
void yaoocpp_class_copy_ctor(pointer,const_pointer);
void yaoocpp_class_assign(pointer,const_pointer);

/* Constructors for yaoocpp_class */

/* Prototypes for yaoocpp_class class table*/
const char* yaoocpp_class_isa(const_pointer);
#define yaoocpp_class_is_descendant yaoocpp_item_is_descendant
#define yaoocpp_class_swap yaoocpp_item_swap
void yaoocpp_class_virtual_dtor(pointer);
bool yaoocpp_class_virtual_less_than_compare(const_pointer,const_pointer);
void yaoocpp_class_dump(const_pointer,yaooc_ofstream_pointer);
void yaoocpp_class_print_to_header(const_pointer,yaooc_ofstream_pointer);
void yaoocpp_class_print_to_source(const_pointer,yaooc_ofstream_pointer);

/* Prototypes for yaoocpp_class class instance*/

/* Prototypes for yaoocpp_class class protected items*/

/*  End YAOOC PreProcessor generated content */

#endif
