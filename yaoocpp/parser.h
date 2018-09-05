#ifndef __PARSER_INCLUDED__
#define __PARSER_INCLUDED__

#include "template_objects.h"
#include <yaooc/base_parser.h>

/*
  Class Definition for yaoocpp_parser_exception
*/
yaooc_class_table(yaoocpp_parser_exception) {
  yaooc_exception_class_table_t;
};

yaooc_class_instance(yaoocpp_parser_exception) {
  yaooc_exception_class_instance_t;
};

yaooc_class(yaoocpp_parser_exception);

/* Type Info Prototypes for yaoocpp_parser_exception */

/* Constructors prototypes for yaoocpp_parser_exception */
#define yaoocpp_parser_exception_ctor_v yaooc_exception_ctor_v

/* Table prototypes for yaoocpp_parser_exception */
const char* yaoocpp_parser_exception_isa(const_pointer);
#define yaoocpp_parser_exception_is_descendant yaooc_exception_is_descendant
#define yaoocpp_parser_exception_swap yaooc_exception_swap
#define yaoocpp_parser_exception_what yaooc_exception_what

/* Protected prototypes for yaoocpp_parser_exception */

/*
  Struct Definition for name_parent
*/
yaooc_struct(name_parent) {
  char* name_;
  const yaoocpp_container_t* parent_;
};

/* Protected prototypes for name_parent */

/* Type Info Prototypes for name_parent */
void name_parent_default_ctor(pointer);
void name_parent_dtor(pointer);

/* Constructor prototypes for name_parent */

/*
  Class Definition for yaoocpp_parser
*/
yaooc_class_table(yaoocpp_parser) {
  yaooc_base_parser_class_table_t;
  void (*parse_file)(pointer,const char*);
};

yaooc_class_instance(yaoocpp_parser) {
  yaooc_base_parser_class_instance_t;
  yaoocpp_container_pointer_vector_t* classes_;
  char* buffer_;
  const char* file_;
//	const char* header_text_;
//	const char* source_text_;
  bool is_top_level_file_;
};

yaooc_class(yaoocpp_parser);

/* Type Info Prototypes for yaoocpp_parser */
void yaoocpp_parser_default_ctor(pointer);
void yaoocpp_parser_dtor(pointer);

/* Constructors prototypes for yaoocpp_parser */

/* Table prototypes for yaoocpp_parser */
const char* yaoocpp_parser_isa(const_pointer);
#define yaoocpp_parser_is_descendant yaooc_base_parser_is_descendant
#define yaoocpp_parser_swap yaooc_base_parser_swap
#define yaoocpp_parser_set_parse_string yaooc_base_parser_set_parse_string
#define yaoocpp_parser_rule_start yaooc_base_parser_rule_start
#define yaoocpp_parser_rule_success yaooc_base_parser_rule_success
#define yaoocpp_parser_rule_fail yaooc_base_parser_rule_fail
#define yaoocpp_parser_eos yaooc_base_parser_eos
#define yaoocpp_parser_string_until_chrs yaooc_base_parser_string_until_chrs
#define yaoocpp_parser_string_while_chrs yaooc_base_parser_string_while_chrs
#define yaoocpp_parser_string_until_eol yaooc_base_parser_string_until_eol
#define yaoocpp_parser_shell_comment yaooc_base_parser_shell_comment
#define yaoocpp_parser_c_comment yaooc_base_parser_c_comment
#define yaoocpp_parser_cpp_comment yaooc_base_parser_cpp_comment
yaooc_terminal_t yaoocpp_parser_custom_whitespace(pointer);
#define yaoocpp_parser_set_whitespace_types yaooc_base_parser_set_whitespace_types
#define yaoocpp_parser_get_whitespace_types yaooc_base_parser_get_whitespace_types
#define yaoocpp_parser_whitespace yaooc_base_parser_whitespace
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
#define yaoocpp_parser_string_until_matching_chr yaooc_base_parser_string_until_matching_chr
#define yaoocpp_parser_result yaooc_base_parser_result
void yaoocpp_parser_parse_file(pointer,const char*);

/* Protected prototypes for yaoocpp_parser */


#endif
