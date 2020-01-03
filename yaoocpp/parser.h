#ifndef __PARSER_INCLUDED__
#define __PARSER_INCLUDED__
#include <yaooc/new.h>
#include <yaooc/base_parser.h>
#include <yaooc/exception.h>
#include <yaooc/string.h>
#include "components.h"


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <regex.h>
#include <yaooc/fstream.h>
#include <yaooc/regex.h>
#include <yaooc/garbage_bag.h>
#include <yaooc/algorithm.h>

yaooc_class_table(yaoocpp_parser) {
  yaooc_base_parser_class_table_t;
void (*parse_file)(pointer,const char*);
};
#define yaoocpp_parser_parent_class_table ((yaooc_base_parser_class_table_t*)(yaoocpp_parser_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_parser) {
  yaooc_base_parser_class_instance_t;
yaoocpp_item_pointer_vector_t sections_;
yaoocpp_item_pointer_vector_t mixins_;
};

yaooc_class(yaoocpp_parser);
void yaoocpp_parser_default_ctor(pointer);
void yaoocpp_parser_dtor(pointer);
void yaoocpp_parser_copy_ctor(pointer,const_pointer);
void yaoocpp_parser_assign(pointer,const_pointer);
#define yaoocpp_parser_swap yaooc_base_parser_swap
#define yaoocpp_parser_set_parse_string yaooc_base_parser_set_parse_string
#define yaoocpp_parser_rule_start yaooc_base_parser_rule_start
#define yaoocpp_parser_rule_success yaooc_base_parser_rule_success
#define yaoocpp_parser_rule_fail yaooc_base_parser_rule_fail
#define yaoocpp_parser_eos yaooc_base_parser_eos
#define yaoocpp_parser_chr yaooc_base_parser_chr
#define yaoocpp_parser_chr_choices yaooc_base_parser_chr_choices
#define yaoocpp_parser_str yaooc_base_parser_str
#define yaoocpp_parser_str_choices yaooc_base_parser_str_choices
#define yaoocpp_parser_digits yaooc_base_parser_digits
#define yaoocpp_parser_hexdigits yaooc_base_parser_hexdigits
#define yaoocpp_parser_integer yaooc_base_parser_integer
#define yaoocpp_parser_hexinteger yaooc_base_parser_hexinteger
#define yaoocpp_parser_real yaooc_base_parser_real
#define yaoocpp_parser_ident yaooc_base_parser_ident
#define yaoocpp_parser_regex yaooc_base_parser_regex
#define yaoocpp_parser_quoted_string yaooc_base_parser_quoted_string
#define yaoocpp_parser_single_quoted_string yaooc_base_parser_single_quoted_string
#define yaoocpp_parser_double_quoted_string yaooc_base_parser_double_quoted_string
#define yaoocpp_parser_bare_string yaooc_base_parser_bare_string
#define yaoocpp_parser_string_until_chrs yaooc_base_parser_string_until_chrs
#define yaoocpp_parser_string_while_chrs yaooc_base_parser_string_while_chrs
#define yaoocpp_parser_string_until_eol yaooc_base_parser_string_until_eol
#define yaoocpp_parser_whitespace yaooc_base_parser_whitespace
#define yaoocpp_parser_string_within_matching_chr yaooc_base_parser_string_within_matching_chr
#define yaoocpp_parser_result yaooc_base_parser_result
 void yaoocpp_parser_parse_file(pointer,const char*);
 bool yaoocpp_parser_line_directive(pointer,yaoocpp_section_t**);
 bool yaoocpp_parser_header_prefix(pointer);
 bool yaoocpp_parser_header(pointer,yaoocpp_section_t**);
 bool yaoocpp_parser_source(pointer,yaoocpp_section_t**);
 bool yaoocpp_parser_class_forward(pointer,yaoocpp_section_t**);
 bool yaoocpp_parser_class_definition(pointer,yaoocpp_section_t**);
 bool yaoocpp_parser_sub_section(pointer,yaoocpp_item_pointer_vector_t*,bool);
 bool yaoocpp_parser_variable(pointer,yaoocpp_variable_t**,bool);
 bool yaoocpp_parser_method(pointer,yaoocpp_method_t**);
 bool yaoocpp_parser_get_parent_name(pointer,char**);
 bool yaoocpp_parser_set_parent(pointer,const char*,const yaoocpp_struct_t**);
 bool yaoocpp_parser_type_info(pointer,yaoocpp_struct_t*);
 bool yaoocpp_parser_constructor_initializers(pointer,yaoocpp_item_pointer_vector_t*);
 bool yaoocpp_parser_default_constructor(pointer,yaoocpp_struct_t*,bool);
 bool yaoocpp_parser_destructor(pointer,yaoocpp_struct_t*);
 bool yaoocpp_parser_copy_constructor(pointer,yaoocpp_struct_t*,bool);
 bool yaoocpp_parser_assignment(pointer,yaoocpp_struct_t*);
 bool yaoocpp_parser_rich_compare(pointer,yaoocpp_struct_t*);
 bool yaoocpp_parser_to_stream(pointer,yaoocpp_struct_t*);
 bool yaoocpp_parser_from_stream(pointer,yaoocpp_struct_t*);
 bool yaoocpp_parser_include(pointer,yaoocpp_struct_t*);
 bool yaoocpp_parser_va_argument(pointer,yaoocpp_argument_t**);
 bool yaoocpp_parser_argument(pointer,yaoocpp_argument_t**);
 bool yaoocpp_parser_arguments(pointer,yaoocpp_item_pointer_vector_t*);
 bool yaoocpp_parser_constructor(pointer,yaoocpp_struct_t*);
 bool yaoocpp_parser_mixin(pointer,yaoocpp_mixin_t**);
yaooc_class_table(yaoocpp_parser_exception) {
  yaooc_exception_class_table_t;
};
#define yaoocpp_parser_exception_parent_class_table ((yaooc_exception_class_table_t*)(yaoocpp_parser_exception_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_parser_exception) {
  yaooc_exception_class_instance_t;
};

yaooc_class(yaoocpp_parser_exception);
#define yaoocpp_parser_exception_ctor_v yaooc_exception_ctor_v
#define yaoocpp_parser_exception_swap yaooc_exception_swap
#define yaoocpp_parser_exception_what yaooc_exception_what
#define yaoocpp_parser_exception_error_code yaooc_exception_error_code

#endif
