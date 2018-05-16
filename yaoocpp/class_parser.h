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

#ifndef __CLASS_PARSER_INCLUDED__
#define __CLASS_PARSER_INCLUDED__

#include <yaooc/string.h>
#include <yaooc/base_parser.h>
#include "template_objects.h"

/*  Begin YAOOC PreProcessor generated content */


/*
  Class definition for yaoocpp_class_parser
*/
class_table(yaoocpp_class_parser)
{
  yaooc_base_parser_class_table_t;
  bool (*parse_file)(pointer,const char*);
};

class_instance(yaoocpp_class_parser)
{
  yaooc_base_parser_class_instance_t;
  yaoocpp_item_ptr_vector_t* classes_;
  yaooc_string_t* file_;
  bool is_top_level_file_;
};

class(yaoocpp_class_parser);
/* Prototypes for yaoocpp_class_parser type info */

/* Constructors for yaoocpp_class_parser */

/* Prototypes for yaoocpp_class_parser class table*/
#define yaoocpp_class_parser_isa yaooc_base_parser_isa
#define yaoocpp_class_parser_is_descendant yaooc_base_parser_is_descendant
#define yaoocpp_class_parser_swap yaooc_base_parser_swap
#define yaoocpp_class_parser_set_parse_string yaooc_base_parser_set_parse_string
#define yaoocpp_class_parser_rule_start yaooc_base_parser_rule_start
#define yaoocpp_class_parser_rule_success yaooc_base_parser_rule_success
#define yaoocpp_class_parser_rule_fail yaooc_base_parser_rule_fail
#define yaoocpp_class_parser_eos yaooc_base_parser_eos
#define yaoocpp_class_parser_string_until_chrs yaooc_base_parser_string_until_chrs
#define yaoocpp_class_parser_string_while_chrs yaooc_base_parser_string_while_chrs
#define yaoocpp_class_parser_string_until_eol yaooc_base_parser_string_until_eol
#define yaoocpp_class_parser_shell_comment yaooc_base_parser_shell_comment
#define yaoocpp_class_parser_c_comment yaooc_base_parser_c_comment
#define yaoocpp_class_parser_cpp_comment yaooc_base_parser_cpp_comment
yaooc_terminal_t yaoocpp_class_parser_custom_whitespace(pointer);
#define yaoocpp_class_parser_set_whitespace_types yaooc_base_parser_set_whitespace_types
#define yaoocpp_class_parser_get_whitespace_types yaooc_base_parser_get_whitespace_types
#define yaoocpp_class_parser_whitespace yaooc_base_parser_whitespace
#define yaoocpp_class_parser_chr yaooc_base_parser_chr
#define yaoocpp_class_parser_chr_choices yaooc_base_parser_chr_choices
#define yaoocpp_class_parser_str yaooc_base_parser_str
#define yaoocpp_class_parser_str_choices yaooc_base_parser_str_choices
#define yaoocpp_class_parser_digits yaooc_base_parser_digits
#define yaoocpp_class_parser_hexdigits yaooc_base_parser_hexdigits
#define yaoocpp_class_parser_integer yaooc_base_parser_integer
#define yaoocpp_class_parser_hexinteger yaooc_base_parser_hexinteger
#define yaoocpp_class_parser_real yaooc_base_parser_real
#define yaoocpp_class_parser_ident yaooc_base_parser_ident
#define yaoocpp_class_parser_regex yaooc_base_parser_regex
#define yaoocpp_class_parser_quoted_string yaooc_base_parser_quoted_string
#define yaoocpp_class_parser_single_quoted_string yaooc_base_parser_single_quoted_string
#define yaoocpp_class_parser_double_quoted_string yaooc_base_parser_double_quoted_string
#define yaoocpp_class_parser_bare_string yaooc_base_parser_bare_string
#define yaoocpp_class_parser_string_until_matching_chr yaooc_base_parser_string_until_matching_chr
//bool yaoocpp_class_parser_constructor(pointer);
bool yaoocpp_class_parser_operator(pointer);
bool yaoocpp_class_parser_parse_file(pointer,const char*);

/* Prototypes for yaoocpp_class_parser class instance*/

/* Prototypes for yaoocpp_class_parser class protected items*/

/*  End YAOOC PreProcessor generated content */

#endif
