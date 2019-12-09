#ifndef __JSON_INCLUDED__
#define __JSON_INCLUDED__

#include <yaooc/object.h>

#include <yaooc/exception.h>

#include <yaooc/stream.h>
#include <yaooc/vector.h>
#include <yaooc/map.h>
typedef enum { JSON_UNDEFINED=0, JSON_NULL, JSON_BOOL, JSON_INTEGER, JSON_REAL, JSON_STRING,
        JSON_ARRAY, JSON_OBJECT } yaooc_json_type_t;

yaooc_class_forward(yaooc_json_value_array);

yaooc_class_forward(yaooc_json_string_value_map);

typedef union {
  bool bool_;
  int64_t int_;
  double real_;
  char* string_;
  yaooc_json_value_array_t* array_;
  yaooc_json_string_value_map_t* object_;
} json_data_t;

yaooc_class_table(yaooc_json_exception) {
  yaooc_exception_class_table_t;
};
#define yaooc_json_exception_parent_class_table ((yaooc_exception_class_table_t*)(yaooc_json_exception_class_table.parent_class_table_))

yaooc_class_instance(yaooc_json_exception) {
  yaooc_exception_class_instance_t;
};

yaooc_class(yaooc_json_exception);
#define yaooc_json_exception_ctor_v yaooc_exception_ctor_v
#define yaooc_json_exception_swap yaooc_exception_swap
#define yaooc_json_exception_what yaooc_exception_what
yaooc_class_table(yaooc_json_value) {
  yaooc_object_class_table_t;
void (*virtual_dtor)(pointer);
void (*virtual_assign)(pointer,const_pointer);
int (*virtual_rich_compare)(const_pointer,const_pointer);
};
#define yaooc_json_value_parent_class_table ((yaooc_object_class_table_t*)(yaooc_json_value_class_table.parent_class_table_))

yaooc_class_instance(yaooc_json_value) {
json_data_t ;
yaooc_json_type_t type_;
};

yaooc_class(yaooc_json_value);
void yaooc_json_value_default_ctor(pointer);
void yaooc_json_value_dtor(pointer);
void yaooc_json_value_copy_ctor(pointer,const_pointer);
void yaooc_json_value_assign(pointer,const_pointer);
int yaooc_json_value_rich_compare(const_pointer,const_pointer);
#define yaooc_json_value_swap yaooc_object_swap
 void yaooc_json_value_virtual_dtor(pointer);
 void yaooc_json_value_virtual_assign(pointer,const_pointer);
 int yaooc_json_value_virtual_rich_compare(const_pointer,const_pointer);
yaooc_class_table(yaooc_json_null) {
  yaooc_json_value_class_table_t;
};
#define yaooc_json_null_parent_class_table ((yaooc_json_value_class_table_t*)(yaooc_json_null_class_table.parent_class_table_))

yaooc_class_instance(yaooc_json_null) {
  yaooc_json_value_class_instance_t;
};

yaooc_class(yaooc_json_null);
void yaooc_json_null_default_ctor(pointer);
void yaooc_json_null_assign(pointer,const_pointer);
int yaooc_json_null_rich_compare(const_pointer,const_pointer);
#define yaooc_json_null_swap yaooc_json_value_swap
 void yaooc_json_null_virtual_dtor(pointer);
 void yaooc_json_null_virtual_assign(pointer,const_pointer);
 int yaooc_json_null_virtual_rich_compare(const_pointer,const_pointer);
yaooc_class_table(yaooc_json_bool) {
  yaooc_json_value_class_table_t;
};
#define yaooc_json_bool_parent_class_table ((yaooc_json_value_class_table_t*)(yaooc_json_bool_class_table.parent_class_table_))

yaooc_class_instance(yaooc_json_bool) {
  yaooc_json_value_class_instance_t;
};

yaooc_class(yaooc_json_bool);
void yaooc_json_bool_default_ctor(pointer);
void yaooc_json_bool_assign(pointer,const_pointer);
int yaooc_json_bool_rich_compare(const_pointer,const_pointer);
void yaooc_json_bool_ctor_bool(pointer,va_list);
#define yaooc_json_bool_swap yaooc_json_value_swap
 void yaooc_json_bool_virtual_dtor(pointer);
 void yaooc_json_bool_virtual_assign(pointer,const_pointer);
 int yaooc_json_bool_virtual_rich_compare(const_pointer,const_pointer);
yaooc_class_table(yaooc_json_integer) {
  yaooc_json_value_class_table_t;
};
#define yaooc_json_integer_parent_class_table ((yaooc_json_value_class_table_t*)(yaooc_json_integer_class_table.parent_class_table_))

yaooc_class_instance(yaooc_json_integer) {
  yaooc_json_value_class_instance_t;
};

yaooc_class(yaooc_json_integer);
void yaooc_json_integer_default_ctor(pointer);
void yaooc_json_integer_assign(pointer,const_pointer);
int yaooc_json_integer_rich_compare(const_pointer,const_pointer);
void yaooc_json_integer_ctor_int(pointer,va_list);
#define yaooc_json_integer_swap yaooc_json_value_swap
 void yaooc_json_integer_virtual_dtor(pointer);
 void yaooc_json_integer_virtual_assign(pointer,const_pointer);
 int yaooc_json_integer_virtual_rich_compare(const_pointer,const_pointer);
yaooc_class_table(yaooc_json_real) {
  yaooc_json_value_class_table_t;
};
#define yaooc_json_real_parent_class_table ((yaooc_json_value_class_table_t*)(yaooc_json_real_class_table.parent_class_table_))

yaooc_class_instance(yaooc_json_real) {
  yaooc_json_value_class_instance_t;
};

yaooc_class(yaooc_json_real);
void yaooc_json_real_default_ctor(pointer);
void yaooc_json_real_assign(pointer,const_pointer);
int yaooc_json_real_rich_compare(const_pointer,const_pointer);
void yaooc_json_real_ctor_int(pointer,va_list);
#define yaooc_json_real_swap yaooc_json_value_swap
 void yaooc_json_real_virtual_dtor(pointer);
 void yaooc_json_real_virtual_assign(pointer,const_pointer);
 int yaooc_json_real_virtual_rich_compare(const_pointer,const_pointer);
yaooc_class_table(yaooc_json_string) {
  yaooc_json_value_class_table_t;
};
#define yaooc_json_string_parent_class_table ((yaooc_json_value_class_table_t*)(yaooc_json_string_class_table.parent_class_table_))

yaooc_class_instance(yaooc_json_string) {
  yaooc_json_value_class_instance_t;
};

yaooc_class(yaooc_json_string);
void yaooc_json_string_default_ctor(pointer);
void yaooc_json_string_dtor(pointer);
void yaooc_json_string_assign(pointer,const_pointer);
int yaooc_json_string_rich_compare(const_pointer,const_pointer);
void yaooc_json_string_ctor_ccs(pointer,va_list);
#define yaooc_json_string_swap yaooc_json_value_swap
 void yaooc_json_string_virtual_dtor(pointer);
 void yaooc_json_string_virtual_assign(pointer,const_pointer);
 int yaooc_json_string_virtual_rich_compare(const_pointer,const_pointer);
VECTOR_DEFINITION(yaooc_json_value,yaooc_json_value_array);

yaooc_class_table(yaooc_json_array) {
  yaooc_json_value_class_table_t;
};
#define yaooc_json_array_parent_class_table ((yaooc_json_value_class_table_t*)(yaooc_json_array_class_table.parent_class_table_))

yaooc_class_instance(yaooc_json_array) {
  yaooc_json_value_class_instance_t;
};

yaooc_class(yaooc_json_array);
void yaooc_json_array_default_ctor(pointer);
void yaooc_json_array_dtor(pointer);
void yaooc_json_array_assign(pointer,const_pointer);
int yaooc_json_array_rich_compare(const_pointer,const_pointer);
#define yaooc_json_array_swap yaooc_json_value_swap
 void yaooc_json_array_virtual_dtor(pointer);
 void yaooc_json_array_virtual_assign(pointer,const_pointer);
 int yaooc_json_array_virtual_rich_compare(const_pointer,const_pointer);
MINI_MAP_DEFINITION(yaooc_json_string,yaooc_json_value,yaooc_json_string_value_map);

yaooc_class_table(yaooc_json_object) {
  yaooc_json_value_class_table_t;
};
#define yaooc_json_object_parent_class_table ((yaooc_json_value_class_table_t*)(yaooc_json_object_class_table.parent_class_table_))

yaooc_class_instance(yaooc_json_object) {
  yaooc_json_value_class_instance_t;
};

yaooc_class(yaooc_json_object);
void yaooc_json_object_default_ctor(pointer);
void yaooc_json_object_dtor(pointer);
void yaooc_json_object_assign(pointer,const_pointer);
int yaooc_json_object_rich_compare(const_pointer,const_pointer);
#define yaooc_json_object_swap yaooc_json_value_swap
 void yaooc_json_object_virtual_dtor(pointer);
 void yaooc_json_object_virtual_assign(pointer,const_pointer);
 int yaooc_json_object_virtual_rich_compare(const_pointer,const_pointer);

#endif
