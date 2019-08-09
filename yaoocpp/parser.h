#ifndef __PARSER_INCLUDED__
#define __PARSER_INCLUDED__

/* Begin YAOOCPP output */

#include <yaooc/base_parser.h>
#include <yaooc/exception.h>


#include "template_objects.h"

/*
  Class Definition for yaoocpp_parser_exception
*/
yaooc_class_table(yaoocpp_parser_exception) {
  yaooc_exception_class_table_t;
};
#define yaoocpp_parser_exception_parent_class_table ((yaooc_exception_class_table_t*)(yaoocpp_parser_exception_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_parser_exception) {
  yaooc_exception_class_instance_t;
};

yaooc_class(yaoocpp_parser_exception);

/* Type Info Prototypes for yaoocpp_parser_exception */
#define yaoocpp_parser_exception_default_ctor yaooc_exception_default_ctor
#define yaoocpp_parser_exception_dtor yaooc_exception_dtor
#define yaoocpp_parser_exception_copy_ctor yaooc_exception_copy_ctor
#define yaoocpp_parser_exception_assign yaooc_exception_assign

/* Constructors prototypes for yaoocpp_parser_exception */
#define yaoocpp_parser_exception_ctor_v yaooc_exception_ctor_v

/* Table prototypes for yaoocpp_parser_exception */
#define yaoocpp_parser_exception_swap yaooc_exception_swap
#define yaoocpp_parser_exception_what yaooc_exception_what

/* Protected prototypes for yaoocpp_parser_exception */

/*
  Class Definition for yaoocpp_parser
*/
yaooc_class_table(yaoocpp_parser) {
  yaooc_base_parser_class_table_t;
  void (*parse_file)(pointer, const char*);
};

#define yaoocpp_parser_parent_class_table ((yaooc_base_parser_class_table_t*)(yaoocpp_parser_class_table.parent_class_table_))

yaooc_class_instance(yaoocpp_parser) {
  yaooc_base_parser_class_instance_t;
  yaoocpp_container_pointer_vector_t* classes_;
  yaooc_string_t header_text_;
  yaooc_string_t source_text_;
  yaooc_string_vector_t include_files_;
  yaoocpp_container_t* current_class_;
};

yaooc_class(yaoocpp_parser);

/* Type Info Prototypes for yaoocpp_parser */
void yaoocpp_parser_default_ctor(pointer);
void yaoocpp_parser_dtor(pointer);
#define yaoocpp_parser_copy_ctor yaooc_base_parser_copy_ctor
#define yaoocpp_parser_assign yaooc_base_parser_assign

/* Constructors prototypes for yaoocpp_parser */

/* Table prototypes for yaoocpp_parser */
#define yaoocpp_parser_swap yaooc_base_parser_swap
#define yaoocpp_parser_set_parse_string yaooc_base_parser_set_parse_string
#define yaoocpp_parser_rule_start yaooc_base_parser_rule_start
#define yaoocpp_parser_rule_success yaooc_base_parser_rule_success
#define yaoocpp_parser_rule_fail yaooc_base_parser_rule_fail
#define yaoocpp_parser_eos yaooc_base_parser_eos
#define yaoocpp_parser_string_until_chrs yaooc_base_parser_string_until_chrs
#define yaoocpp_parser_string_while_chrs yaooc_base_parser_string_while_chrs
#define yaoocpp_parser_string_until_eol yaooc_base_parser_string_until_eol
bool yaoocpp_parser_whitespace(pointer,yaooc_terminal_t*);
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
void yaoocpp_parser_parse_file(pointer, const char*);

/* Protected prototypes for yaoocpp_parser */

/* End YAOOCPP output */


#endif
