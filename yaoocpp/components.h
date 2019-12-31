#ifndef __COMPONENTS_INCLUDED__
#define __COMPONENTS_INCLUDED__

#include <yaooc/object.h>
#include <yaooc/vector.h>
#include <yaooc/string.h>
#include <yaooc/memory.h>
#include <yaooc/stream.h>
#include <yaooc/algorithm.h>
#include <yaooc/garbage_bag.h>
#include <yaooc/regex.h>
#include <string.h>
#include <ctype.h>

yaooc_class_table(yaoocpp_item) {
  yaooc_object_class_table_t;
void (*set_line_no)(pointer,int);
};
#define yaoocpp_item_parent_class_table ((yaooc_object_class_table_t*)(yaoocpp_item_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_item) {
yaooc_string_t name_;
int line_no_;
};

yaooc_class(yaoocpp_item);
void yaoocpp_item_default_ctor(pointer);
void yaoocpp_item_dtor(pointer);
void yaoocpp_item_copy_ctor(pointer,const_pointer);
void yaoocpp_item_assign(pointer,const_pointer);
int yaoocpp_item_rich_compare(const_pointer,const_pointer);
#define yaoocpp_item_swap yaooc_object_swap
 void yaoocpp_item_set_line_no(pointer,int);
VECTOR_DEFINITION(yaooc_dynamic_pointer,yaoocpp_item_pointer_vector);

yaooc_class_table(yaoocpp_argument) {
  yaoocpp_item_class_table_t;
};
#define yaoocpp_argument_parent_class_table ((yaoocpp_item_class_table_t*)(yaoocpp_argument_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_argument) {
  yaoocpp_item_class_instance_t;
yaooc_string_t type_;
yaooc_string_t array_def_;
};

yaooc_class(yaoocpp_argument);
void yaoocpp_argument_default_ctor(pointer);
void yaoocpp_argument_dtor(pointer);
void yaoocpp_argument_copy_ctor(pointer,const_pointer);
void yaoocpp_argument_assign(pointer,const_pointer);
#define yaoocpp_argument_swap yaoocpp_item_swap
#define yaoocpp_argument_set_line_no yaoocpp_item_set_line_no
typedef enum { DEFAULT, DELETE, IMPLEMENTED_AS,IMPLEMENTATION_TEXT } yaoocpp_implementation_form_t;

typedef enum { INITIAL = 0 , INHERITED = 1, OVERRIDDEN = 2 } yaoocpp_member_item_generation_t;

yaooc_class_table(yaoocpp_member_item) {
  yaoocpp_argument_class_table_t;
void (*print_instance_prototype)(const_pointer,ostream_pointer,const char*,const char*);
void (*print_table_definition)(const_pointer,ostream_pointer,const char*,const char*);
void (*print_table_implementation)(const_pointer,ostream_pointer,const char*,const char*);
void (*print_adjunct_prototype)(const_pointer,ostream_pointer,const char*,const char*);
void (*print_adjunct_implementation)(const_pointer,ostream_pointer,const char*,const char*);
void (*print_private_prototype)(const_pointer,ostream_pointer,const char*,const char*);
void (*print_private_implementation)(const_pointer,ostream_pointer,const char*,const char*);
void (*print_class_table_entry)(const_pointer,ostream_pointer,const char*,const char*);
void (*print_yaooh_definition)(const_pointer,ostream_pointer,bool);
};
#define yaoocpp_member_item_parent_class_table ((yaoocpp_argument_class_table_t*)(yaoocpp_member_item_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_member_item) {
  yaoocpp_argument_class_instance_t;
yaoocpp_member_item_generation_t generation_;
};

yaooc_class(yaoocpp_member_item);
void yaoocpp_member_item_default_ctor(pointer);
void yaoocpp_member_item_copy_ctor(pointer,const_pointer);
void yaoocpp_member_item_assign(pointer,const_pointer);
#define yaoocpp_member_item_swap yaoocpp_argument_swap
#define yaoocpp_member_item_set_line_no yaoocpp_argument_set_line_no
 void yaoocpp_member_item_print_instance_prototype(const_pointer,ostream_pointer,const char*,const char*);
 void yaoocpp_member_item_print_table_definition(const_pointer,ostream_pointer,const char*,const char*);
 void yaoocpp_member_item_print_table_implementation(const_pointer,ostream_pointer,const char*,const char*);
 void yaoocpp_member_item_print_adjunct_prototype(const_pointer,ostream_pointer,const char*,const char*);
 void yaoocpp_member_item_print_adjunct_implementation(const_pointer,ostream_pointer,const char*,const char*);
 void yaoocpp_member_item_print_private_prototype(const_pointer,ostream_pointer,const char*,const char*);
 void yaoocpp_member_item_print_private_implementation(const_pointer,ostream_pointer,const char*,const char*);
 void yaoocpp_member_item_print_class_table_entry(const_pointer,ostream_pointer,const char*,const char*);
 void yaoocpp_member_item_print_yaooh_definition(const_pointer,ostream_pointer,bool);
yaooc_class_table(yaoocpp_variable) {
  yaoocpp_member_item_class_table_t;
};
#define yaoocpp_variable_parent_class_table ((yaoocpp_member_item_class_table_t*)(yaoocpp_variable_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_variable) {
  yaoocpp_member_item_class_instance_t;
yaooc_string_t value_;
};

yaooc_class(yaoocpp_variable);
void yaoocpp_variable_default_ctor(pointer);
void yaoocpp_variable_dtor(pointer);
void yaoocpp_variable_copy_ctor(pointer,const_pointer);
void yaoocpp_variable_assign(pointer,const_pointer);
#define yaoocpp_variable_swap yaoocpp_member_item_swap
#define yaoocpp_variable_set_line_no yaoocpp_member_item_set_line_no
 void yaoocpp_variable_print_instance_prototype(const_pointer,ostream_pointer,const char*,const char*);
 void yaoocpp_variable_print_table_definition(const_pointer,ostream_pointer,const char*,const char*);
 void yaoocpp_variable_print_table_implementation(const_pointer,ostream_pointer,const char*,const char*);
 void yaoocpp_variable_print_adjunct_prototype(const_pointer,ostream_pointer,const char*,const char*);
 void yaoocpp_variable_print_adjunct_implementation(const_pointer,ostream_pointer,const char*,const char*);
 void yaoocpp_variable_print_private_prototype(const_pointer,ostream_pointer,const char*,const char*);
 void yaoocpp_variable_print_private_implementation(const_pointer,ostream_pointer,const char*,const char*);
 void yaoocpp_variable_print_class_table_entry(const_pointer,ostream_pointer,const char*,const char*);
 void yaoocpp_variable_print_yaooh_definition(const_pointer,ostream_pointer,bool);
 void yaoocpp_variable_print(const_pointer,ostream_pointer,const char*,const char*,const char*,bool);
yaooc_class_table(yaoocpp_method) {
  yaoocpp_member_item_class_table_t;
size_t (*argument_count)(const_pointer);
void (*set_implementation)(pointer,const char*,size_t);
void (*set_implemented_as)(pointer,const char*,size_t);
bool (*is_implemented)(const_pointer);
};
#define yaoocpp_method_parent_class_table ((yaoocpp_member_item_class_table_t*)(yaoocpp_method_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_method) {
  yaoocpp_member_item_class_instance_t;
bool is_const_;
yaoocpp_item_pointer_vector_t arguments_;
yaooc_string_t implementation_;
yaoocpp_implementation_form_t form_;
};

yaooc_class(yaoocpp_method);
void yaoocpp_method_default_ctor(pointer);
void yaoocpp_method_dtor(pointer);
void yaoocpp_method_copy_ctor(pointer,const_pointer);
void yaoocpp_method_assign(pointer,const_pointer);
#define yaoocpp_method_swap yaoocpp_member_item_swap
#define yaoocpp_method_set_line_no yaoocpp_member_item_set_line_no
#define yaoocpp_method_print_instance_prototype yaoocpp_member_item_print_instance_prototype
 void yaoocpp_method_print_table_definition(const_pointer,ostream_pointer,const char*,const char*);
 void yaoocpp_method_print_table_implementation(const_pointer,ostream_pointer,const char*,const char*);
 void yaoocpp_method_print_adjunct_prototype(const_pointer,ostream_pointer,const char*,const char*);
 void yaoocpp_method_print_adjunct_implementation(const_pointer,ostream_pointer,const char*,const char*);
 void yaoocpp_method_print_private_prototype(const_pointer,ostream_pointer,const char*,const char*);
 void yaoocpp_method_print_private_implementation(const_pointer,ostream_pointer,const char*,const char*);
 void yaoocpp_method_print_class_table_entry(const_pointer,ostream_pointer,const char*,const char*);
 void yaoocpp_method_print_yaooh_definition(const_pointer,ostream_pointer,bool);
 size_t yaoocpp_method_argument_count(const_pointer);
 void yaoocpp_method_set_implementation(pointer,const char*,size_t);
 void yaoocpp_method_set_implemented_as(pointer,const char*,size_t);
 bool yaoocpp_method_is_implemented(const_pointer);
 void yaoocpp_method_print_args_type(const_pointer,ostream_pointer);
 void yaoocpp_method_print_args_type_name(const_pointer,ostream_pointer);
yaooc_class_table(yaoocpp_constructor_initializer) {
  yaoocpp_item_class_table_t;
};
#define yaoocpp_constructor_initializer_parent_class_table ((yaoocpp_item_class_table_t*)(yaoocpp_constructor_initializer_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_constructor_initializer) {
  yaoocpp_item_class_instance_t;
yaooc_string_t value_;
};

yaooc_class(yaoocpp_constructor_initializer);
void yaoocpp_constructor_initializer_default_ctor(pointer);
void yaoocpp_constructor_initializer_dtor(pointer);
void yaoocpp_constructor_initializer_copy_ctor(pointer,const_pointer);
void yaoocpp_constructor_initializer_assign(pointer,const_pointer);
void yaoocpp_constructor_initializer_ctor_id_value(pointer,va_list);
#define yaoocpp_constructor_initializer_swap yaoocpp_item_swap
#define yaoocpp_constructor_initializer_set_line_no yaoocpp_item_set_line_no
yaooc_class_table(yaoocpp_type_info) {
  yaoocpp_item_class_table_t;
void (*print_prototype)(const_pointer,ostream_pointer);
void (*set_implementation)(pointer,const char*,size_t);
void (*set_implemented_as)(pointer,const char*,size_t);
bool (*is_implemented)(const_pointer);
};
#define yaoocpp_type_info_parent_class_table ((yaoocpp_item_class_table_t*)(yaoocpp_type_info_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_type_info) {
  yaoocpp_item_class_instance_t;
yaooc_string_t mixin_text_;
yaooc_string_t implementation_;
yaoocpp_implementation_form_t form_;
};

yaooc_class(yaoocpp_type_info);
void yaoocpp_type_info_default_ctor(pointer);
void yaoocpp_type_info_dtor(pointer);
void yaoocpp_type_info_copy_ctor(pointer,const_pointer);
void yaoocpp_type_info_assign(pointer,const_pointer);
#define yaoocpp_type_info_swap yaoocpp_item_swap
#define yaoocpp_type_info_set_line_no yaoocpp_item_set_line_no
 void yaoocpp_type_info_print_prototype(const_pointer,ostream_pointer);
 void yaoocpp_type_info_set_implementation(pointer,const char*,size_t);
 void yaoocpp_type_info_set_implemented_as(pointer,const char*,size_t);
 bool yaoocpp_type_info_is_implemented(const_pointer);
 void yaoocpp_type_info_print_entry(const_pointer,ostream_pointer,const char*);
yaooc_class_table(yaoocpp_constructor_base) {
  yaoocpp_type_info_class_table_t;
};
#define yaoocpp_constructor_base_parent_class_table ((yaoocpp_type_info_class_table_t*)(yaoocpp_constructor_base_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_constructor_base) {
  yaoocpp_type_info_class_instance_t;
yaoocpp_item_pointer_vector_t initializers_;
yaooc_string_t initializer_text_;
};

yaooc_class(yaoocpp_constructor_base);
void yaoocpp_constructor_base_default_ctor(pointer);
void yaoocpp_constructor_base_dtor(pointer);
void yaoocpp_constructor_base_copy_ctor(pointer,const_pointer);
void yaoocpp_constructor_base_assign(pointer,const_pointer);
#define yaoocpp_constructor_base_swap yaoocpp_type_info_swap
#define yaoocpp_constructor_base_set_line_no yaoocpp_type_info_set_line_no
 void yaoocpp_constructor_base_print_prototype(const_pointer,ostream_pointer);
#define yaoocpp_constructor_base_set_implementation yaoocpp_type_info_set_implementation
#define yaoocpp_constructor_base_set_implemented_as yaoocpp_type_info_set_implemented_as
#define yaoocpp_constructor_base_is_implemented yaoocpp_type_info_is_implemented
 void yaoocpp_constructor_base_gen_initializers_text(pointer,const char*,const char*,yaoocpp_item_pointer_vector_const_pointer,bool);
yaooc_class_forward(yaoocpp_mixin);

yaooc_class_table(yaoocpp_default_constructor) {
  yaoocpp_constructor_base_class_table_t;
};
#define yaoocpp_default_constructor_parent_class_table ((yaoocpp_constructor_base_class_table_t*)(yaoocpp_default_constructor_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_default_constructor) {
  yaoocpp_constructor_base_class_instance_t;
};

yaooc_class(yaoocpp_default_constructor);
#define yaoocpp_default_constructor_swap yaoocpp_constructor_base_swap
#define yaoocpp_default_constructor_set_line_no yaoocpp_constructor_base_set_line_no
#define yaoocpp_default_constructor_print_prototype yaoocpp_constructor_base_print_prototype
#define yaoocpp_default_constructor_set_implementation yaoocpp_constructor_base_set_implementation
#define yaoocpp_default_constructor_set_implemented_as yaoocpp_constructor_base_set_implemented_as
#define yaoocpp_default_constructor_is_implemented yaoocpp_constructor_base_is_implemented
 void yaoocpp_default_constructor_resolve(pointer,const char*,const char*,yaoocpp_item_pointer_vector_const_pointer);
 void yaoocpp_default_constructor_create(pointer,const char*,const char*,yaoocpp_item_pointer_vector_const_pointer);
 void yaoocpp_default_constructor_add_mixin_text(pointer,yaoocpp_mixin_const_pointer,const char*,const char*);
 void yaoocpp_default_constructor_print_implementation(const_pointer,ostream_pointer,const char*);
 void yaoocpp_default_constructor_print_type_info_entry(const_pointer,ostream_pointer);
 void yaoocpp_default_constructor_print_yaooh_definition(const_pointer,ostream_pointer,bool);
yaooc_class_table(yaoocpp_destructor) {
  yaoocpp_type_info_class_table_t;
};
#define yaoocpp_destructor_parent_class_table ((yaoocpp_type_info_class_table_t*)(yaoocpp_destructor_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_destructor) {
  yaoocpp_type_info_class_instance_t;
};

yaooc_class(yaoocpp_destructor);
#define yaoocpp_destructor_swap yaoocpp_type_info_swap
#define yaoocpp_destructor_set_line_no yaoocpp_type_info_set_line_no
 void yaoocpp_destructor_print_prototype(const_pointer,ostream_pointer);
#define yaoocpp_destructor_set_implementation yaoocpp_type_info_set_implementation
#define yaoocpp_destructor_set_implemented_as yaoocpp_type_info_set_implemented_as
#define yaoocpp_destructor_is_implemented yaoocpp_type_info_is_implemented
 void yaoocpp_destructor_resolve(pointer,const char*,const char*,yaoocpp_item_pointer_vector_const_pointer);
 void yaoocpp_destructor_create(pointer,const char*,const char*,yaoocpp_item_pointer_vector_const_pointer);
 void yaoocpp_destructor_add_mixin_text(pointer,yaoocpp_mixin_const_pointer,const char*,const char*);
 void yaoocpp_destructor_print_implementation(const_pointer,ostream_pointer,const char*);
 void yaoocpp_destructor_print_type_info_entry(const_pointer,ostream_pointer);
 void yaoocpp_destructor_print_yaooh_definition(const_pointer,ostream_pointer,bool);
yaooc_class_table(yaoocpp_copy_constructor) {
  yaoocpp_constructor_base_class_table_t;
void (*set_source_name)(pointer,const char*,size_t);
};
#define yaoocpp_copy_constructor_parent_class_table ((yaoocpp_constructor_base_class_table_t*)(yaoocpp_copy_constructor_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_copy_constructor) {
  yaoocpp_constructor_base_class_instance_t;
yaooc_string_t src_name_;
};

yaooc_class(yaoocpp_copy_constructor);
void yaoocpp_copy_constructor_default_ctor(pointer);
void yaoocpp_copy_constructor_dtor(pointer);
void yaoocpp_copy_constructor_copy_ctor(pointer,const_pointer);
void yaoocpp_copy_constructor_assign(pointer,const_pointer);
#define yaoocpp_copy_constructor_swap yaoocpp_constructor_base_swap
#define yaoocpp_copy_constructor_set_line_no yaoocpp_constructor_base_set_line_no
 void yaoocpp_copy_constructor_print_prototype(const_pointer,ostream_pointer);
#define yaoocpp_copy_constructor_set_implementation yaoocpp_constructor_base_set_implementation
#define yaoocpp_copy_constructor_set_implemented_as yaoocpp_constructor_base_set_implemented_as
#define yaoocpp_copy_constructor_is_implemented yaoocpp_constructor_base_is_implemented
 void yaoocpp_copy_constructor_set_source_name(pointer,const char*,size_t);
 void yaoocpp_copy_constructor_resolve(pointer,const char*,const char*,yaoocpp_item_pointer_vector_const_pointer);
 void yaoocpp_copy_constructor_create(pointer,const char*,const char*,yaoocpp_item_pointer_vector_const_pointer);
 void yaoocpp_copy_constructor_add_mixin_text(pointer,yaoocpp_mixin_const_pointer,const char*,const char*);
 void yaoocpp_copy_constructor_print_implementation(const_pointer,ostream_pointer,const char*);
 void yaoocpp_copy_constructor_print_type_info_entry(const_pointer,ostream_pointer);
 void yaoocpp_copy_constructor_print_yaooh_definition(const_pointer,ostream_pointer,bool);
yaooc_class_table(yaoocpp_assignment) {
  yaoocpp_copy_constructor_class_table_t;
};
#define yaoocpp_assignment_parent_class_table ((yaoocpp_copy_constructor_class_table_t*)(yaoocpp_assignment_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_assignment) {
  yaoocpp_copy_constructor_class_instance_t;
};

yaooc_class(yaoocpp_assignment);
#define yaoocpp_assignment_swap yaoocpp_copy_constructor_swap
#define yaoocpp_assignment_set_line_no yaoocpp_copy_constructor_set_line_no
 void yaoocpp_assignment_print_prototype(const_pointer,ostream_pointer);
#define yaoocpp_assignment_set_implementation yaoocpp_copy_constructor_set_implementation
#define yaoocpp_assignment_set_implemented_as yaoocpp_copy_constructor_set_implemented_as
#define yaoocpp_assignment_is_implemented yaoocpp_copy_constructor_is_implemented
#define yaoocpp_assignment_set_source_name yaoocpp_copy_constructor_set_source_name
 void yaoocpp_assignment_resolve(pointer,const char*,const char*,yaoocpp_item_pointer_vector_const_pointer);
 void yaoocpp_assignment_create(pointer,const char*,const char*,yaoocpp_item_pointer_vector_const_pointer);
 void yaoocpp_assignment_add_mixin_text(pointer,yaoocpp_mixin_const_pointer,const char*,const char*);
 void yaoocpp_assignment_print_implementation(const_pointer,ostream_pointer,const char*);
 void yaoocpp_assignment_print_type_info_entry(const_pointer,ostream_pointer);
 void yaoocpp_assignment_print_yaooh_definition(const_pointer,ostream_pointer,bool);
yaooc_class_table(yaoocpp_rich_compare) {
  yaoocpp_type_info_class_table_t;
void (*set_lhs_name)(pointer,const char*,size_t);
void (*set_rhs_name)(pointer,const char*,size_t);
};
#define yaoocpp_rich_compare_parent_class_table ((yaoocpp_type_info_class_table_t*)(yaoocpp_rich_compare_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_rich_compare) {
  yaoocpp_type_info_class_instance_t;
yaooc_string_t lhs_name_;
yaooc_string_t rhs_name_;
};

yaooc_class(yaoocpp_rich_compare);
void yaoocpp_rich_compare_default_ctor(pointer);
void yaoocpp_rich_compare_dtor(pointer);
void yaoocpp_rich_compare_copy_ctor(pointer,const_pointer);
void yaoocpp_rich_compare_assign(pointer,const_pointer);
#define yaoocpp_rich_compare_swap yaoocpp_type_info_swap
#define yaoocpp_rich_compare_set_line_no yaoocpp_type_info_set_line_no
 void yaoocpp_rich_compare_print_prototype(const_pointer,ostream_pointer);
#define yaoocpp_rich_compare_set_implementation yaoocpp_type_info_set_implementation
#define yaoocpp_rich_compare_set_implemented_as yaoocpp_type_info_set_implemented_as
#define yaoocpp_rich_compare_is_implemented yaoocpp_type_info_is_implemented
 void yaoocpp_rich_compare_set_lhs_name(pointer,const char*,size_t);
 void yaoocpp_rich_compare_set_rhs_name(pointer,const char*,size_t);
 void yaoocpp_rich_compare_resolve(pointer,const char*,const char*,yaoocpp_item_pointer_vector_const_pointer);
 void yaoocpp_rich_compare_print_implementation(const_pointer,ostream_pointer,const char*);
 void yaoocpp_rich_compare_print_type_info_entry(const_pointer,ostream_pointer);
 void yaoocpp_rich_compare_print_yaooh_definition(const_pointer,ostream_pointer,bool);
 void yaoocpp_rich_compare_add_mixin_text(pointer,yaoocpp_mixin_const_pointer,const char*,const char*);
yaooc_class_table(yaoocpp_to_stream) {
  yaoocpp_type_info_class_table_t;
void (*set_stream_name)(pointer,const char*,size_t);
};
#define yaoocpp_to_stream_parent_class_table ((yaoocpp_type_info_class_table_t*)(yaoocpp_to_stream_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_to_stream) {
  yaoocpp_type_info_class_instance_t;
yaooc_string_t strm_name_;
};

yaooc_class(yaoocpp_to_stream);
void yaoocpp_to_stream_default_ctor(pointer);
void yaoocpp_to_stream_dtor(pointer);
void yaoocpp_to_stream_copy_ctor(pointer,const_pointer);
void yaoocpp_to_stream_assign(pointer,const_pointer);
#define yaoocpp_to_stream_swap yaoocpp_type_info_swap
#define yaoocpp_to_stream_set_line_no yaoocpp_type_info_set_line_no
 void yaoocpp_to_stream_print_prototype(const_pointer,ostream_pointer);
#define yaoocpp_to_stream_set_implementation yaoocpp_type_info_set_implementation
#define yaoocpp_to_stream_set_implemented_as yaoocpp_type_info_set_implemented_as
#define yaoocpp_to_stream_is_implemented yaoocpp_type_info_is_implemented
 void yaoocpp_to_stream_set_stream_name(pointer,const char*,size_t);
 void yaoocpp_to_stream_resolve(pointer,const char*,const char*,yaoocpp_item_pointer_vector_const_pointer);
 void yaoocpp_to_stream_print_implementation(const_pointer,ostream_pointer,const char*);
 void yaoocpp_to_stream_print_type_info_entry(const_pointer,ostream_pointer);
 void yaoocpp_to_stream_print_yaooh_definition(const_pointer,ostream_pointer,bool);
 void yaoocpp_to_stream_add_mixin_text(pointer,yaoocpp_mixin_const_pointer,const char*,const char*);
yaooc_class_table(yaoocpp_from_stream) {
  yaoocpp_to_stream_class_table_t;
};
#define yaoocpp_from_stream_parent_class_table ((yaoocpp_to_stream_class_table_t*)(yaoocpp_from_stream_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_from_stream) {
  yaoocpp_to_stream_class_instance_t;
};

yaooc_class(yaoocpp_from_stream);
#define yaoocpp_from_stream_swap yaoocpp_to_stream_swap
#define yaoocpp_from_stream_set_line_no yaoocpp_to_stream_set_line_no
 void yaoocpp_from_stream_print_prototype(const_pointer,ostream_pointer);
#define yaoocpp_from_stream_set_implementation yaoocpp_to_stream_set_implementation
#define yaoocpp_from_stream_set_implemented_as yaoocpp_to_stream_set_implemented_as
#define yaoocpp_from_stream_is_implemented yaoocpp_to_stream_is_implemented
#define yaoocpp_from_stream_set_stream_name yaoocpp_to_stream_set_stream_name
 void yaoocpp_from_stream_resolve(pointer,const char*,const char*,yaoocpp_item_pointer_vector_const_pointer);
 void yaoocpp_from_stream_print_implementation(const_pointer,ostream_pointer,const char*);
 void yaoocpp_from_stream_print_type_info_entry(const_pointer,ostream_pointer);
 void yaoocpp_from_stream_print_yaooh_definition(const_pointer,ostream_pointer,bool);
 void yaoocpp_from_stream_add_mixin_text(pointer,yaoocpp_mixin_const_pointer,const char*,const char*);
yaooc_class_table(yaoocpp_constructor) {
  yaoocpp_constructor_base_class_table_t;
void (*print_implementation)(const_pointer,ostream_pointer,const char*);
size_t (*argument_count)(const_pointer);
};
#define yaoocpp_constructor_parent_class_table ((yaoocpp_constructor_base_class_table_t*)(yaoocpp_constructor_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_constructor) {
  yaoocpp_constructor_base_class_instance_t;
yaoocpp_item_pointer_vector_t arguments_;
};

yaooc_class(yaoocpp_constructor);
void yaoocpp_constructor_default_ctor(pointer);
void yaoocpp_constructor_dtor(pointer);
void yaoocpp_constructor_copy_ctor(pointer,const_pointer);
void yaoocpp_constructor_assign(pointer,const_pointer);
#define yaoocpp_constructor_swap yaoocpp_constructor_base_swap
#define yaoocpp_constructor_set_line_no yaoocpp_constructor_base_set_line_no
 void yaoocpp_constructor_print_prototype(const_pointer,ostream_pointer);
#define yaoocpp_constructor_set_implementation yaoocpp_constructor_base_set_implementation
#define yaoocpp_constructor_set_implemented_as yaoocpp_constructor_base_set_implemented_as
#define yaoocpp_constructor_is_implemented yaoocpp_constructor_base_is_implemented
 void yaoocpp_constructor_print_implementation(const_pointer,ostream_pointer,const char*);
 size_t yaoocpp_constructor_argument_count(const_pointer);
 void yaoocpp_constructor_resolve(pointer,const char*,const char*,yaoocpp_item_pointer_vector_const_pointer);
 void yaoocpp_constructor_print_yaooh_definition(const_pointer,ostream_pointer,bool);
 void yaoocpp_constructor_print_args_type(const_pointer,ostream_pointer);
 void yaoocpp_constructor_print_args_type_name(const_pointer,ostream_pointer);
yaooc_class_table(yaoocpp_section) {
  yaoocpp_item_class_table_t;
void (*print_to_header)(const_pointer,ostream_pointer);
void (*print_to_source)(const_pointer,ostream_pointer);
void (*print_to_yaooh)(const_pointer,ostream_pointer);
void (*resolve)(pointer,const char*,const char*,yaoocpp_item_pointer_vector_const_pointer);
void (*add_mixins)(pointer,yaoocpp_item_pointer_vector_const_pointer);
};
#define yaoocpp_section_parent_class_table ((yaoocpp_item_class_table_t*)(yaoocpp_section_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_section) {
  yaoocpp_item_class_instance_t;
bool defined_in_top_level_file_;
};

yaooc_class(yaoocpp_section);
void yaoocpp_section_default_ctor(pointer);
void yaoocpp_section_dtor(pointer);
void yaoocpp_section_copy_ctor(pointer,const_pointer);
void yaoocpp_section_assign(pointer,const_pointer);
#define yaoocpp_section_swap yaoocpp_item_swap
#define yaoocpp_section_set_line_no yaoocpp_item_set_line_no
 void yaoocpp_section_print_to_header(const_pointer,ostream_pointer);
 void yaoocpp_section_print_to_source(const_pointer,ostream_pointer);
 void yaoocpp_section_print_to_yaooh(const_pointer,ostream_pointer);
 void yaoocpp_section_resolve(pointer,const char*,const char*,yaoocpp_item_pointer_vector_const_pointer);
 void yaoocpp_section_add_mixins(pointer,yaoocpp_item_pointer_vector_const_pointer);
yaooc_class_table(yaoocpp_header) {
  yaoocpp_section_class_table_t;
};
#define yaoocpp_header_parent_class_table ((yaoocpp_section_class_table_t*)(yaoocpp_header_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_header) {
  yaoocpp_section_class_instance_t;
yaooc_string_t content_;
};

yaooc_class(yaoocpp_header);
void yaoocpp_header_default_ctor(pointer);
void yaoocpp_header_dtor(pointer);
void yaoocpp_header_copy_ctor(pointer,const_pointer);
void yaoocpp_header_assign(pointer,const_pointer);
#define yaoocpp_header_swap yaoocpp_section_swap
#define yaoocpp_header_set_line_no yaoocpp_section_set_line_no
 void yaoocpp_header_print_to_header(const_pointer,ostream_pointer);
#define yaoocpp_header_print_to_source yaoocpp_section_print_to_source
#define yaoocpp_header_print_to_yaooh yaoocpp_section_print_to_yaooh
#define yaoocpp_header_resolve yaoocpp_section_resolve
#define yaoocpp_header_add_mixins yaoocpp_section_add_mixins
yaooc_class_table(yaoocpp_source) {
  yaoocpp_header_class_table_t;
};
#define yaoocpp_source_parent_class_table ((yaoocpp_header_class_table_t*)(yaoocpp_source_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_source) {
  yaoocpp_header_class_instance_t;
};

yaooc_class(yaoocpp_source);
#define yaoocpp_source_swap yaoocpp_header_swap
#define yaoocpp_source_set_line_no yaoocpp_header_set_line_no
 void yaoocpp_source_print_to_header(const_pointer,ostream_pointer);
 void yaoocpp_source_print_to_source(const_pointer,ostream_pointer);
#define yaoocpp_source_print_to_yaooh yaoocpp_header_print_to_yaooh
#define yaoocpp_source_resolve yaoocpp_header_resolve
#define yaoocpp_source_add_mixins yaoocpp_header_add_mixins
yaooc_class_table(yaoocpp_struct) {
  yaoocpp_section_class_table_t;
void (*inherit)(pointer);
void (*resolve_outstanding_components)(pointer);
yaoocpp_item_pointer_vector_t* (*get_new_instance_variables)(const_pointer);
bool (*is_pod)(const_pointer);
bool (*is_min_pod)(const_pointer);
};
#define yaoocpp_struct_parent_class_table ((yaoocpp_section_class_table_t*)(yaoocpp_struct_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_struct) {
  yaoocpp_section_class_instance_t;
const yaoocpp_struct_t* parent_;
yaoocpp_default_constructor_t default_ctor_;
yaoocpp_destructor_t dtor_;
yaoocpp_copy_constructor_t copy_ctor_;
yaoocpp_assignment_t assign_;
yaoocpp_rich_compare_t rich_compare_;
yaoocpp_to_stream_t to_stream_;
yaoocpp_from_stream_t from_stream_;
yaoocpp_item_pointer_vector_t constructors_;
yaoocpp_item_pointer_vector_t instance_;
yaoocpp_item_pointer_vector_t adjunct_;
yaoocpp_item_pointer_vector_t private_;
yaooc_string_vector_t mixins_;
};

yaooc_class(yaoocpp_struct);
void yaoocpp_struct_default_ctor(pointer);
void yaoocpp_struct_dtor(pointer);
void yaoocpp_struct_copy_ctor(pointer,const_pointer);
void yaoocpp_struct_assign(pointer,const_pointer);
#define yaoocpp_struct_swap yaoocpp_section_swap
#define yaoocpp_struct_set_line_no yaoocpp_section_set_line_no
 void yaoocpp_struct_print_to_header(const_pointer,ostream_pointer);
 void yaoocpp_struct_print_to_source(const_pointer,ostream_pointer);
 void yaoocpp_struct_print_to_yaooh(const_pointer,ostream_pointer);
#define yaoocpp_struct_resolve yaoocpp_section_resolve
 void yaoocpp_struct_add_mixins(pointer,yaoocpp_item_pointer_vector_const_pointer);
 void yaoocpp_struct_inherit(pointer);
 void yaoocpp_struct_resolve_outstanding_components(pointer);
 yaoocpp_item_pointer_vector_t* yaoocpp_struct_get_new_instance_variables(const_pointer);
 bool yaoocpp_struct_is_pod(const_pointer);
 bool yaoocpp_struct_is_min_pod(const_pointer);
 void yaoocpp_struct_print_struct_definition(const_pointer,ostream_pointer);
 void yaoocpp_struct_print_type_info_definition(const_pointer,ostream_pointer);
 void yaoocpp_struct_print_type_info_implementation(const_pointer,ostream_pointer);
 void yaoocpp_struct_print_constructor_prototypes(const_pointer,ostream_pointer);
 void yaoocpp_struct_print_constructor_implementation(const_pointer,ostream_pointer);
 void yaoocpp_struct_print_adjunct_prototypes(const_pointer,ostream_pointer);
 void yaoocpp_struct_print_adjunct_implementation(const_pointer,ostream_pointer);
 void yaoocpp_struct_print_private_variable_implementation(const_pointer,ostream_pointer);
 void yaoocpp_struct_print_private_method_prototypes(const_pointer,ostream_pointer);
 void yaoocpp_struct_print_private_method_implementation(const_pointer,ostream_pointer);
 void yaoocpp_struct_add_mixin_members(pointer,yaoocpp_item_pointer_vector_pointer,yaoocpp_item_pointer_vector_const_pointer,bool);
 void yaoocpp_struct_print_type_info_declaration(const_pointer,ostream_pointer);
typedef enum { DEFAULT_CTOR=0, DTOR, COPY_CTOR, ASSIGN, RICH_COMPARE, TO_STREAM, FROM_STREAM } type_info_item_t;

yaooc_class_table(yaoocpp_class) {
  yaoocpp_struct_class_table_t;
};
#define yaoocpp_class_parent_class_table ((yaoocpp_struct_class_table_t*)(yaoocpp_class_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_class) {
  yaoocpp_struct_class_instance_t;
yaoocpp_item_pointer_vector_t table_;
};

yaooc_class(yaoocpp_class);
void yaoocpp_class_default_ctor(pointer);
void yaoocpp_class_dtor(pointer);
void yaoocpp_class_copy_ctor(pointer,const_pointer);
void yaoocpp_class_assign(pointer,const_pointer);
#define yaoocpp_class_swap yaoocpp_struct_swap
#define yaoocpp_class_set_line_no yaoocpp_struct_set_line_no
 void yaoocpp_class_print_to_header(const_pointer,ostream_pointer);
 void yaoocpp_class_print_to_source(const_pointer,ostream_pointer);
 void yaoocpp_class_print_to_yaooh(const_pointer,ostream_pointer);
#define yaoocpp_class_resolve yaoocpp_struct_resolve
 void yaoocpp_class_add_mixins(pointer,yaoocpp_item_pointer_vector_const_pointer);
 void yaoocpp_class_inherit(pointer);
#define yaoocpp_class_resolve_outstanding_components yaoocpp_struct_resolve_outstanding_components
#define yaoocpp_class_get_new_instance_variables yaoocpp_struct_get_new_instance_variables
#define yaoocpp_class_is_pod yaoocpp_struct_is_pod
#define yaoocpp_class_is_min_pod yaoocpp_struct_is_min_pod
 void yaoocpp_class_print_class_definition(const_pointer,ostream_pointer);
 void yaoocpp_class_print_class_table_prototypes(const_pointer,ostream_pointer);
 void yaoocpp_class_print_table_method_implementation(const_pointer,ostream_pointer);
 void yaoocpp_class_print_class_table_implementation(const_pointer,ostream_pointer);
 void yaoocpp_class_print_type_info_declaration(const_pointer,ostream_pointer);
yaooc_class_table(yaoocpp_union) {
  yaoocpp_class_class_table_t;
void (*print_class_definition)(const_pointer,ostream_pointer);
};
#define yaoocpp_union_parent_class_table ((yaoocpp_class_class_table_t*)(yaoocpp_union_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_union) {
  yaoocpp_class_class_instance_t;
};

yaooc_class(yaoocpp_union);
#define yaoocpp_union_swap yaoocpp_class_swap
#define yaoocpp_union_set_line_no yaoocpp_class_set_line_no
 void yaoocpp_union_print_to_header(const_pointer,ostream_pointer);
#define yaoocpp_union_print_to_source yaoocpp_class_print_to_source
#define yaoocpp_union_print_to_yaooh yaoocpp_class_print_to_yaooh
#define yaoocpp_union_resolve yaoocpp_class_resolve
#define yaoocpp_union_add_mixins yaoocpp_class_add_mixins
#define yaoocpp_union_inherit yaoocpp_class_inherit
#define yaoocpp_union_resolve_outstanding_components yaoocpp_class_resolve_outstanding_components
#define yaoocpp_union_get_new_instance_variables yaoocpp_class_get_new_instance_variables
#define yaoocpp_union_is_pod yaoocpp_class_is_pod
#define yaoocpp_union_is_min_pod yaoocpp_class_is_min_pod
 void yaoocpp_union_print_class_definition(const_pointer,ostream_pointer);
yaooc_class_table(yaoocpp_mixin) {
  yaoocpp_class_class_table_t;
};
#define yaoocpp_mixin_parent_class_table ((yaoocpp_class_class_table_t*)(yaoocpp_mixin_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_mixin) {
  yaoocpp_class_class_instance_t;
};

yaooc_class(yaoocpp_mixin);
#define yaoocpp_mixin_swap yaoocpp_class_swap
#define yaoocpp_mixin_set_line_no yaoocpp_class_set_line_no
 void yaoocpp_mixin_print_to_header(const_pointer,ostream_pointer);
 void yaoocpp_mixin_print_to_source(const_pointer,ostream_pointer);
 void yaoocpp_mixin_print_to_yaooh(const_pointer,ostream_pointer);
#define yaoocpp_mixin_resolve yaoocpp_class_resolve
#define yaoocpp_mixin_add_mixins yaoocpp_class_add_mixins
#define yaoocpp_mixin_inherit yaoocpp_class_inherit
#define yaoocpp_mixin_resolve_outstanding_components yaoocpp_class_resolve_outstanding_components
#define yaoocpp_mixin_get_new_instance_variables yaoocpp_class_get_new_instance_variables
#define yaoocpp_mixin_is_pod yaoocpp_class_is_pod
#define yaoocpp_mixin_is_min_pod yaoocpp_class_is_min_pod

#endif
