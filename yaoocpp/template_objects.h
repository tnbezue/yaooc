#ifndef __TEMPLATE_OBJECTS_INCLUDED__
#define __TEMPLATE_OBJECTS_INCLUDED__

#include <yaooc/string.h>
#include <yaooc/vector.h>
#include <yaooc/stream.h>
#include <yaooc/memory.h>

yaooc_struct_forward(yaoocpp_argument);
VECTOR_DEFINITION(yaoocpp_argument,yaoocpp_argument_vector);

/*
  Struct Definition for yaoocpp_argument
*/
yaooc_struct(yaoocpp_argument) {
  yaooc_string_t type_;
  yaooc_string_t name_;
  yaooc_string_t array_size_;
  bool is_array_;
};

/* Protected prototypes for yaoocpp_argument */
void yaoocpp_argument_print_type(const_pointer,ostream_pointer);
void yaoocpp_argument_print_type_name(const_pointer,ostream_pointer);

/* Type Info Prototypes for yaoocpp_argument */
void yaoocpp_argument_default_ctor(pointer);
void yaoocpp_argument_dtor(pointer);
void yaoocpp_argument_copy_ctor(pointer,const_pointer);
void yaoocpp_argument_assign(pointer,const_pointer);
int yaoocpp_argument_rich_compare(const_pointer,const_pointer);

/* Constructor prototypes for yaoocpp_argument */

/*
  Class Definition for yaoocpp_element
*/
typedef enum { INITIAL = 0 , INHERITED = 1, OVERRIDDEN = 2 } element_state_t;
yaooc_class_table(yaoocpp_element) {
  yaooc_object_class_table_t;
  void (*print_class_table_definition)(const_pointer,ostream_pointer);
  void (*print_class_instance_definition)(const_pointer,ostream_pointer);
  void (*print_prototype)(const_pointer,ostream_pointer,const char*,const char*);
  void (*print_implementation)(const_pointer,ostream_pointer,const char*,const char*);
  void (*print_class_table_implementation)(const_pointer,ostream_pointer,const char*);
};

yaooc_class_instance(yaoocpp_element) {
  yaooc_string_t name_;
  element_state_t state_;
};

yaooc_class(yaoocpp_element);

/* Type Info Prototypes for yaoocpp_element */
void yaoocpp_element_default_ctor(pointer);
void yaoocpp_element_dtor(pointer);
void yaoocpp_element_copy_ctor(pointer,const_pointer);
void yaoocpp_element_assign(pointer,const_pointer);

/* Constructors prototypes for yaoocpp_element */

/* Table prototypes for yaoocpp_element */
const char* yaoocpp_element_isa(const_pointer);
#define yaoocpp_element_swap yaooc_object_swap
#define yaoocpp_element_print_class_table_definition NULL
#define yaoocpp_element_print_class_instance_definition NULL
#define yaoocpp_element_print_prototype NULL
#define yaoocpp_element_print_implementation NULL
#define yaoocpp_element_print_class_table_implementation NULL

/* Protected prototypes for yaoocpp_element */

DYNAMIC_POINTER_DEFINITION(yaoocpp_element,yaoocpp_element_pointer);
VECTOR_DEFINITION(yaoocpp_element_pointer,yaoocpp_element_pointer_vector);


/*
  Class Definition for yaoocpp_type
*/
yaooc_class_table(yaoocpp_type) {
  yaoocpp_element_class_table_t;
};

yaooc_class_instance(yaoocpp_type) {
  yaoocpp_element_class_instance_t;
};

yaooc_class(yaoocpp_type);

/* Type Info Prototypes for yaoocpp_type */

/* Constructors prototypes for yaoocpp_type */

/* Table prototypes for yaoocpp_type */
const char* yaoocpp_type_isa(const_pointer);
#define yaoocpp_type_swap yaoocpp_element_swap
void yaoocpp_type_print_class_table_definition(const_pointer,ostream_pointer);
#define yaoocpp_type_print_class_instance_definition yaoocpp_type_print_class_table_definition
#define yaoocpp_type_print_prototype NULL
#define yaoocpp_type_print_implementation NULL
#define yaoocpp_type_print_class_table_implementation NULL

/* Protected prototypes for yaoocpp_type */

/*
  Class Definition for yaoocpp_variable
*/
yaooc_class_table(yaoocpp_variable) {
  yaoocpp_element_class_table_t;
};

yaooc_class_instance(yaoocpp_variable) {
  yaoocpp_element_class_instance_t;
  yaooc_string_t type_;
  yaooc_string_t default_value_;
  yaooc_string_t array_size_;
  bool is_array_;
};

yaooc_class(yaoocpp_variable);

/* Type Info Prototypes for yaoocpp_variable */
void yaoocpp_variable_default_ctor(pointer);
void yaoocpp_variable_dtor(pointer);
void yaoocpp_variable_copy_ctor(pointer,const_pointer);
void yaoocpp_variable_assign(pointer,const_pointer);

/* Constructors prototypes for yaoocpp_variable */

/* Table prototypes for yaoocpp_variable */
const char* yaoocpp_variable_isa(const_pointer);
#define yaoocpp_variable_swap yaoocpp_element_swap
void yaoocpp_variable_print_class_table_definition(const_pointer,ostream_pointer);
#define yaoocpp_variable_print_class_instance_definition yaoocpp_variable_print_class_table_definition
void yaoocpp_variable_print_prototype(const_pointer,ostream_pointer,const char*,const char*);
void yaoocpp_variable_print_implementation(const_pointer,ostream_pointer,const char*,const char*);
void yaoocpp_variable_print_class_table_implementation(const_pointer,ostream_pointer,const char*);

/* Protected prototypes for yaoocpp_variable */

#if 0
/*
  Class Definition for yaoocpp_raw_struct_union
*/
yaooc_class_table(yaoocpp_raw_struct_union) {
  yaoocpp_element_class_table_t;
};
#define yaoocpp_raw_struct_union_parent_class_table ((yaoocpp_element_class_table_t*)(yaoocpp_raw_struct_union_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_raw_struct_union) {
  yaoocpp_element_class_instance_t;
  yaooc_string_t raw_string_;
};

yaooc_class(yaoocpp_raw_struct_union);

/* Type Info Prototypes for yaoocpp_raw_struct_union */
void yaoocpp_raw_struct_union_default_ctor(pointer);
void yaoocpp_raw_struct_union_dtor(pointer);
void yaoocpp_raw_struct_union_copy_ctor(pointer,const_pointer);
void yaoocpp_raw_struct_union_assign(pointer,const_pointer);

/* Constructors prototypes for yaoocpp_raw_struct_union */

/* Table prototypes for yaoocpp_raw_struct_union */
#define yaoocpp_raw_struct_union_isa yaoocpp_element_isa
#define yaoocpp_raw_struct_union_swap yaoocpp_element_swap
void yaoocpp_raw_struct_union_print_class_table_definition(const_pointer, ostream_pointer);
void yaoocpp_raw_struct_union_print_class_instance_definition(const_pointer, ostream_pointer);
void yaoocpp_raw_struct_union_print_prototype(const_pointer, ostream_pointer, const char*, const char*);
void yaoocpp_raw_struct_union_print_implementation(const_pointer, ostream_pointer, const char*, const char*);
void yaoocpp_raw_struct_union_print_class_table_implementation(const_pointer, ostream_pointer, const char*);

/* Protected prototypes for yaoocpp_raw_struct_union */
#endif
/*
  Class Definition for yaoocpp_constructor
*/
yaooc_class_table(yaoocpp_constructor) {
  yaoocpp_element_class_table_t;
};

yaooc_class_instance(yaoocpp_constructor) {
  yaoocpp_element_class_instance_t;
  yaoocpp_argument_vector_t arguments_;
  yaooc_string_t implementation_method_;
  yaooc_string_t implementation_;
};

yaooc_class(yaoocpp_constructor);

/* Type Info Prototypes for yaoocpp_constructor */
void yaoocpp_constructor_default_ctor(pointer);
void yaoocpp_constructor_dtor(pointer);
void yaoocpp_constructor_copy_ctor(pointer,const_pointer);
void yaoocpp_constructor_assign(pointer,const_pointer);

/* Constructors prototypes for yaoocpp_constructor */

/* Table prototypes for yaoocpp_constructor */
const char* yaoocpp_constructor_isa(const_pointer);
#define yaoocpp_constructor_swap yaoocpp_element_swap
#define yaoocpp_constructor_print_class_table_definition NULL
#define yaoocpp_constructor_print_class_instance_definition NULL
void yaoocpp_constructor_print_prototype(const_pointer,ostream_pointer,const char*,const char*);
void yaoocpp_constructor_print_implementation(const_pointer,ostream_pointer,const char*,const char*);
#define yaoocpp_constructor_print_class_table_implementation NULL

/* Protected prototypes for yaoocpp_constructor */

/*
  Class Definition for yaoocpp_method
*/
yaooc_class_table(yaoocpp_method) {
  yaoocpp_constructor_class_table_t;
};

yaooc_class_instance(yaoocpp_method) {
  yaoocpp_constructor_class_instance_t;
  yaooc_string_t return_type_;
  bool is_const_;
};

yaooc_class(yaoocpp_method);

/* Type Info Prototypes for yaoocpp_method */
void yaoocpp_method_default_ctor(pointer);
void yaoocpp_method_dtor(pointer);
void yaoocpp_method_copy_ctor(pointer,const_pointer);
void yaoocpp_method_assign(pointer,const_pointer);

/* Constructors prototypes for yaoocpp_method */

/* Table prototypes for yaoocpp_method */
const char* yaoocpp_method_isa(const_pointer);
#define yaoocpp_method_swap yaoocpp_constructor_swap
void yaoocpp_method_print_class_table_definition(const_pointer,ostream_pointer);
#define yaoocpp_method_print_class_instance_definition yaoocpp_method_print_class_table_definition
void yaoocpp_method_print_prototype(const_pointer,ostream_pointer,const char*,const char*);
void yaoocpp_method_print_implementation(const_pointer,ostream_pointer,const char*,const char*);
void yaoocpp_method_print_class_table_implementation(const_pointer,ostream_pointer,const char*);

/* Protected prototypes for yaoocpp_method */

/*
  Class Definition for yaoocpp_container
*/
yaooc_class_table(yaoocpp_container) {
  yaooc_object_class_table_t;
  void (*inherit) (pointer);
  bool (*is_min_pod) (const_pointer);
  bool (*is_pod) (const_pointer);
  void (*print_to_header)(const_pointer,ostream_pointer);
  void (*print_to_source)(const_pointer,ostream_pointer);
};

yaooc_class_instance(yaoocpp_container) {
  yaooc_string_t name_;
  const yaoocpp_container_t* parent_;
  yaoocpp_element_pointer_vector_t constructors_;
  yaoocpp_element_pointer_vector_t instance_;
  yaoocpp_element_pointer_vector_t private_;
  yaoocpp_element_pointer_vector_t protected_;
  yaoocpp_element_pointer_vector_t static_;
  yaooc_string_t default_ctor_implementation_;
  yaooc_string_t dtor_implementation_;
  yaooc_string_t copy_ctor_implementation_;
  yaooc_string_t assign_implementation_;
  yaooc_string_t rich_cmp_implementation_;
  yaooc_string_t to_stream_implementation_;
  yaooc_string_t from_stream_implementation_;
  bool defined_in_top_level_file_;
};

yaooc_class(yaoocpp_container);

/* Type Info Prototypes for yaoocpp_container */
void yaoocpp_container_default_ctor(pointer);
void yaoocpp_container_dtor(pointer);
void yaoocpp_container_copy_ctor(pointer,const_pointer);
void yaoocpp_container_assign(pointer,const_pointer);
int yaoocpp_container_rich_compare(const_pointer,const_pointer);

/* Constructors prototypes for yaoocpp_container */

/* Table prototypes for yaoocpp_container */
const char* yaoocpp_container_isa(const_pointer);
#define yaoocpp_container_swap yaooc_object_swap
void yaoocpp_container_inherit(pointer);
bool yaoocpp_container_is_min_pod(const_pointer);
#define yaoocpp_container_is_pod yaoocpp_container_is_min_pod
#define yaoocpp_container_print_to_header NULL
#define yaoocpp_container_print_to_source NULL

/* Protected prototypes for yaoocpp_container */

DYNAMIC_POINTER_DEFINITION(yaoocpp_container,yaoocpp_container_pointer);
VECTOR_DEFINITION(yaoocpp_container_pointer,yaoocpp_container_pointer_vector);

/*
  Class Definition for yaoocpp_struct
*/
yaooc_class_table(yaoocpp_struct) {
  yaoocpp_container_class_table_t;
};

yaooc_class_instance(yaoocpp_struct) {
  yaoocpp_container_class_instance_t;
};

yaooc_class(yaoocpp_struct);

/* Type Info Prototypes for yaoocpp_struct */

/* Constructors prototypes for yaoocpp_struct */

/* Table prototypes for yaoocpp_struct */
const char* yaoocpp_struct_isa(const_pointer);
#define yaoocpp_struct_swap yaoocpp_container_swap
#define yaoocpp_struct_inherit yaoocpp_container_inherit
bool yaoocpp_struct_is_min_pod(const_pointer);
bool yaoocpp_struct_is_pod(const_pointer);
void yaoocpp_struct_print_to_header(const_pointer,ostream_pointer);
void yaoocpp_struct_print_to_source(const_pointer,ostream_pointer);

/* Protected prototypes for yaoocpp_struct */

/*
  Class Definition for yaoocpp_container_with_class_table
*/
yaooc_class_table(yaoocpp_container_with_class_table) {
  yaoocpp_container_class_table_t;
};

yaooc_class_instance(yaoocpp_container_with_class_table) {
  yaoocpp_container_class_instance_t;
  yaoocpp_element_pointer_vector_t table_;
};

yaooc_class(yaoocpp_container_with_class_table);

/* Type Info Prototypes for yaoocpp_container_with_class_table */
void yaoocpp_container_with_class_table_default_ctor(pointer);
void yaoocpp_container_with_class_table_dtor(pointer);
void yaoocpp_container_with_class_table_copy_ctor(pointer,const_pointer);
void yaoocpp_container_with_class_table_assign(pointer,const_pointer);

/* Constructors prototypes for yaoocpp_container_with_class_table */

/* Table prototypes for yaoocpp_container_with_class_table */
const char* yaoocpp_container_with_class_table_isa(const_pointer);
#define yaoocpp_container_with_class_table_swap yaoocpp_container_swap
void yaoocpp_container_with_class_table_inherit(pointer);
#define yaoocpp_container_with_class_table_is_min_pod yaoocpp_container_is_min_pod
#define yaoocpp_container_with_class_table_is_pod yaoocpp_container_is_pod
void yaoocpp_container_with_class_table_print_to_header(const_pointer, ostream_pointer);
void yaoocpp_container_with_class_table_print_to_source(const_pointer, ostream_pointer);

/* Protected prototypes for yaoocpp_container_with_class_table */
 #if 0
/*
  Class Definition for yaoocpp_union
*/
yaooc_class_table(yaoocpp_union) {
  yaoocpp_container_class_table_t;
};

yaooc_class_instance(yaoocpp_union) {
  yaoocpp_container_class_instance_t;
};

yaooc_class(yaoocpp_union);

/* Type Info Prototypes for yaoocpp_union */

/* Constructors prototypes for yaoocpp_union */

/* Table prototypes for yaoocpp_union */
const char* yaoocpp_union_isa(const_pointer);
#define yaoocpp_union_swap yaoocpp_container_swap
void yaoocpp_union_print_to_header(const_pointer,ostream_pointer);
void yaoocpp_union_print_to_source(const_pointer,ostream_pointer);

/* Protected prototypes for yaoocpp_union */
#define yaoocpp_union_inherit yaoocpp_container_inherit

/*
  Class Definition for yaoocpp_class
*/
yaooc_class_table(yaoocpp_class) {
  yaoocpp_container_class_table_t;
};

yaooc_class_instance(yaoocpp_class) {
  yaoocpp_container_class_instance_t;
  yaoocpp_element_pointer_vector_t table_;
};

yaooc_class(yaoocpp_class);

/* Type Info Prototypes for yaoocpp_class */
void yaoocpp_class_default_ctor(pointer);
void yaoocpp_class_dtor(pointer);
void yaoocpp_class_copy_ctor(pointer,const_pointer);
void yaoocpp_class_assign(pointer,const_pointer);
int yaoocpp_class_rich_compare(const_pointer,const_pointer);

/* Constructors prototypes for yaoocpp_class */

/* Table prototypes for yaoocpp_class */
const char* yaoocpp_class_isa(const_pointer);
#define yaoocpp_class_swap yaoocpp_container_swap
void yaoocpp_class_print_to_header(const_pointer,ostream_pointer);
void yaoocpp_class_print_to_source(const_pointer,ostream_pointer);

/* Protected prototypes for yaoocpp_class */
extern void yaoocpp_class_inherit(pointer);
#endif
/*
  Class Definition for yaoocpp_class
*/
yaooc_class_table(yaoocpp_class) {
  yaoocpp_container_with_class_table_class_table_t;
};

yaooc_class_instance(yaoocpp_class) {
  yaoocpp_container_with_class_table_class_instance_t;
};

yaooc_class(yaoocpp_class);

/* Type Info Prototypes for yaoocpp_class */
#define yaoocpp_class_default_ctor yaoocpp_container_with_class_table_default_ctor
#define yaoocpp_class_dtor yaoocpp_container_with_class_table_dtor
#define yaoocpp_class_copy_ctor yaoocpp_container_with_class_table_copy_ctor
#define yaoocpp_class_assign yaoocpp_container_with_class_table_assign

/* Constructors prototypes for yaoocpp_class */

/* Table prototypes for yaoocpp_class */
const char* yaoocpp_class_isa(const_pointer);
#define yaoocpp_class_swap yaoocpp_container_with_class_table_swap
#define yaoocpp_class_inherit yaoocpp_container_with_class_table_inherit
#define yaoocpp_class_is_min_pod yaoocpp_container_with_class_table_is_min_pod
#define yaoocpp_class_is_pod yaoocpp_container_with_class_table_is_pod
void yaoocpp_class_print_to_header(const_pointer, ostream_pointer);
void yaoocpp_class_print_to_source(const_pointer, ostream_pointer);

/* Protected prototypes for yaoocpp_class */

/*
  Class Definition for yaoocpp_union
*/
yaooc_class_table(yaoocpp_union) {
  yaoocpp_container_with_class_table_class_table_t;
};

yaooc_class_instance(yaoocpp_union) {
  yaoocpp_container_with_class_table_class_instance_t;
};

yaooc_class(yaoocpp_union);

/* Type Info Prototypes for yaoocpp_union */
#define yaoocpp_union_default_ctor yaoocpp_container_with_class_table_default_ctor
#define yaoocpp_union_dtor yaoocpp_container_with_class_table_dtor
#define yaoocpp_union_copy_ctor yaoocpp_container_with_class_table_copy_ctor
#define yaoocpp_union_assign yaoocpp_container_with_class_table_assign

/* Constructors prototypes for yaoocpp_union */

/* Table prototypes for yaoocpp_union */
const char* yaoocpp_union_isa(const_pointer);
#define yaoocpp_union_swap yaoocpp_container_with_class_table_swap
#define yaoocpp_union_inherit yaoocpp_container_with_class_table_inherit
#define yaoocpp_union_is_min_pod yaoocpp_container_with_class_table_is_min_pod
#define yaoocpp_union_is_pod yaoocpp_container_with_class_table_is_pod
void yaoocpp_union_print_to_header(const_pointer, ostream_pointer);
void yaoocpp_union_print_to_source(const_pointer, ostream_pointer);

/* Protected prototypes for yaoocpp_union */

/* End YAOOCPP output */


#endif
