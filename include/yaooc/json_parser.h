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

#ifndef __JSON_PARSER_INCLUDED__
#define __JSON_PARSER_INCLUDED__

#include <yaooc/base_parser.h>
#include <yaooc/json.h>


/*  Begin YAOOC PreProcessor generated content */


/*
  Class definition for yaooc_json_parser
*/
yaooc_class_table(yaooc_json_parser)
{
  yaooc_base_parser_class_table_t;
  yaooc_json_value_pointer (*parse_json_null)(pointer);
  yaooc_json_value_pointer (*parse_json_bool)(pointer);
  yaooc_json_value_pointer (*parse_json_integer)(pointer);
  yaooc_json_value_pointer (*parse_json_real)(pointer);
  yaooc_json_value_pointer (*parse_json_string)(pointer);
  yaooc_json_value_pointer (*parse_json_array)(pointer);
  yaooc_json_value_pointer (*parse_json_object)(pointer);
  yaooc_json_value_pointer (*parse_json_value)(pointer);
  yaooc_json_value_pointer (*parse_string)(pointer,const char*);
  yaooc_json_value_pointer (*parse_file)(pointer,const char*);
};

yaooc_class_instance(yaooc_json_parser)
{
  yaooc_base_parser_class_instance_t;
};

yaooc_class(yaooc_json_parser);
/* Prototypes for yaooc_json_parser type info */

/* Constructors for yaooc_json_parser */

/* Prototypes for yaooc_json_parser class table*/
#define yaooc_json_parser_swap yaooc_base_parser_swap
#define yaooc_json_parser_set_parse_string yaooc_base_parser_set_parse_string
#define yaooc_json_parser_rule_start yaooc_base_parser_rule_start
#define yaooc_json_parser_rule_success yaooc_base_parser_rule_success
#define yaooc_json_parser_rule_fail yaooc_base_parser_rule_fail
#define yaooc_json_parser_eos yaooc_base_parser_eos
#define yaooc_json_parser_string_until_chrs yaooc_base_parser_string_until_chrs
#define yaooc_json_parser_string_while_chrs yaooc_base_parser_string_while_chrs
#define yaooc_json_parser_string_until_eol yaooc_base_parser_string_until_eol
#define yaooc_json_parser_shell_comment yaooc_base_parser_shell_comment
#define yaooc_json_parser_c_comment yaooc_base_parser_c_comment
#define yaooc_json_parser_cpp_comment yaooc_base_parser_cpp_comment
#define yaooc_json_parser_custom_whitespace yaooc_base_parser_custom_whitespace
#define yaooc_json_parser_set_whitespace_types yaooc_base_parser_set_whitespace_types
#define yaooc_json_parser_get_whitespace_types yaooc_base_parser_get_whitespace_types
#define yaooc_json_parser_whitespace yaooc_base_parser_whitespace
#define yaooc_json_parser_chr yaooc_base_parser_chr
#define yaooc_json_parser_chr_choices yaooc_base_parser_chr_choices
#define yaooc_json_parser_str yaooc_base_parser_str
#define yaooc_json_parser_str_choices yaooc_base_parser_str_choices
#define yaooc_json_parser_digits yaooc_base_parser_digits
#define yaooc_json_parser_hexdigits yaooc_base_parser_hexdigits
#define yaooc_json_parser_integer yaooc_base_parser_integer
#define yaooc_json_parser_hexinteger yaooc_base_parser_hexinteger
#define yaooc_json_parser_real yaooc_base_parser_real
#define yaooc_json_parser_ident yaooc_base_parser_ident
#define yaooc_json_parser_regex yaooc_base_parser_regex
#define yaooc_json_parser_quoted_string yaooc_base_parser_quoted_string
#define yaooc_json_parser_single_quoted_string yaooc_base_parser_single_quoted_string
#define yaooc_json_parser_double_quoted_string yaooc_base_parser_double_quoted_string
#define yaooc_json_parser_bare_string yaooc_base_parser_bare_string
#define yaooc_json_parser_string_until_matching_chr yaooc_base_parser_string_until_matching_chr
yaooc_json_value_pointer yaooc_json_parser_parse_json_null(pointer);
yaooc_json_value_pointer yaooc_json_parser_parse_json_bool(pointer);
yaooc_json_value_pointer yaooc_json_parser_parse_json_integer(pointer);
yaooc_json_value_pointer yaooc_json_parser_parse_json_real(pointer);
yaooc_json_value_pointer yaooc_json_parser_parse_json_string(pointer);
yaooc_json_value_pointer yaooc_json_parser_parse_json_array(pointer);
yaooc_json_value_pointer yaooc_json_parser_parse_json_object(pointer);
yaooc_json_value_pointer yaooc_json_parser_parse_json_value(pointer);
yaooc_json_value_pointer yaooc_json_parser_parse_string(pointer,const char*);
yaooc_json_value_pointer yaooc_json_parser_parse_file(pointer,const char*);

/* Prototypes for yaooc_json_parser class instance*/

/* Prototypes for yaooc_json_parser class protected items*/

/*  End YAOOC PreProcessor generated content */

#endif
