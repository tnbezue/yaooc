/*
		Copyright (C) 2016-2019  by Terry N Bezue

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

#ifndef __BASE_PARSER_INCLUDED__
#define __BASE_PARSER_INCLUDED__

/* Begin YAOOCPP output */

#include <yaooc/object.h>


#include <yaooc/stack.h>
#include <yaooc/stack.h>

yaooc_struct_forward(parser_position);

# define yaooc_base_parser_current_pos(p) ((yaooc_base_parser_pointer)p)->current_pos_
# define yaooc_base_parser_peek(p) *(((yaooc_base_parser_pointer)p)->current_pos_)
# define yaooc_base_parser_skip(p,n) { int __nn__=n; for(;__nn__>0;__nn__--) yaooc_base_parser_next_chr(p); }

STACK_DEFINITION(parser_position,parser_position_stack)

#define default_terminal(p) \
     (yaooc_terminal_t){ .beg_=((yaooc_base_parser_pointer)p)->current_pos_, .end_=NULL }

enum { CRLF=1,C_COMMENT=2,CPP_COMMENT=4,SHELL_COMMENT=8,CUSTOM_WHITESPACE=16};
enum { PARSE_SUCCESS = 0, PARSE_FAILED };

#define RULE_START(p) M((yaooc_base_parser_pointer)this,rule_start)
#define RULE_FAIL(p) M((yaooc_base_parser_pointer)this,rule_fail)
#define RULE_SUCCESS(p) M((yaooc_base_parser_pointer)this,rule_success)

//#define NEXT_CHR (yaooc_base_parser_current_char_=*this->current_pos_++,yaooc_base_parser_current_char_)
#define OPTIONAL(rule) ((rule),true)
#define TRY_RULE(p,rule) (RULE_START(p), (rule) ? RULE_SUCCESS(p) : RULE_FAIL(p))

/*
  Struct Definition for parser_position
*/
yaooc_min_struct(parser_position) {
  const char* pos_;
  size_t line_no_;
};

/* Protected prototypes for parser_position */

/* Type Info Prototypes for parser_position */
#define parser_position_default_ctor yaooc_do_nothing_default_ctor
#define parser_position_dtor yaooc_do_nothing_dtor
#define parser_position_copy_ctor yaooc_do_nothing_copy_ctor
#define parser_position_assign yaooc_do_nothing_assign

/* Constructor prototypes for parser_position */

/*
  Struct Definition for yaooc_terminal
*/
yaooc_min_struct(yaooc_terminal) {
  const char* beg_;
  const char* end_;
};

/* Protected prototypes for yaooc_terminal */
char* yaooc_terminal_text(const_pointer);
char* yaooc_terminal_raw_text(const_pointer);

/* Type Info Prototypes for yaooc_terminal */
#define yaooc_terminal_default_ctor yaooc_do_nothing_default_ctor
#define yaooc_terminal_dtor yaooc_do_nothing_dtor
#define yaooc_terminal_copy_ctor yaooc_do_nothing_copy_ctor
#define yaooc_terminal_assign yaooc_do_nothing_assign

/* Constructor prototypes for yaooc_terminal */

/*
  Class Definition for yaooc_base_parser
*/
yaooc_class_table(yaooc_base_parser) {
  yaooc_object_class_table_t;
  void (*set_parse_string)(pointer, const char*);
  void (*rule_start)(pointer);
  bool (*rule_success)(pointer);
  bool (*rule_fail)(pointer);
  bool (*eos)(pointer);
  bool (*string_until_chrs)(pointer, const char*, yaooc_terminal_t*);
  bool (*string_while_chrs)(pointer, const char*, yaooc_terminal_t*);
  bool (*string_until_eol)(pointer, yaooc_terminal_t*);
#if 0
  bool (*shell_comment)(pointer, yaooc_terminal_t*);
  bool (*c_comment)(pointer, yaooc_terminal_t*);
  bool (*cpp_comment)(pointer, yaooc_terminal_t*);
  bool (*custom_whitespace)(pointer, yaooc_terminal_t*);
  void (*set_whitespace_types)(pointer, uint32_t);
  uint32_t (*get_whitespace_types)(pointer);
#endif
  bool (*whitespace)(pointer,yaooc_terminal_t*);
  bool (*chr)(pointer, char,yaooc_terminal_t*);
  int (*chr_choices)(pointer, const char*);
  bool (*str)(pointer, const char*,yaooc_terminal_t*);
  int (*str_choices)(pointer, ...);
  bool (*digits)(pointer, yaooc_terminal_t*);
  bool (*hexdigits)(pointer, yaooc_terminal_t*);
  bool (*integer)(pointer, yaooc_terminal_t*);
  bool (*hexinteger)(pointer, yaooc_terminal_t*);
  bool (*real)(pointer, yaooc_terminal_t*);
  bool (*ident)(pointer, yaooc_terminal_t*);
  bool (*regex)(pointer, const char*, uint32_t, uint32_t, yaooc_terminal_t*);
  bool (*quoted_string)(pointer, char, yaooc_terminal_t*);
  bool (*single_quoted_string)(pointer, yaooc_terminal_t*);
  bool (*double_quoted_string)(pointer, yaooc_terminal_t*);
  bool (*bare_string)(pointer, yaooc_terminal_t*);
  bool (*string_until_matching_chr)(pointer, char, char, yaooc_terminal_t*);
  bool (*result)(const_pointer);
};
#define yaooc_base_parser_parent_class_table ((yaooc_object_class_table_t*)(yaooc_base_parser_class_table.parent_class_table_))

yaooc_class_instance(yaooc_base_parser) {
  yaooc_object_class_instance_t;
  parser_position_stack_t* stack_;
  const char* current_pos_;
  unsigned int line_no_;
//  unsigned int whitespace_types_;
};

yaooc_class(yaooc_base_parser);

/* Type Info Prototypes for yaooc_base_parser */
void yaooc_base_parser_default_ctor(pointer);
void yaooc_base_parser_dtor(pointer);
void yaooc_base_parser_copy_ctor(pointer,const_pointer);
void yaooc_base_parser_assign(pointer,const_pointer);

/* Constructors prototypes for yaooc_base_parser */

/* Table prototypes for yaooc_base_parser */
void yaooc_base_parser_swap(pointer, pointer);
void yaooc_base_parser_set_parse_string(pointer, const char*);
void yaooc_base_parser_rule_start(pointer);
bool yaooc_base_parser_rule_success(pointer);
bool yaooc_base_parser_rule_fail(pointer);
bool yaooc_base_parser_eos(pointer);
bool yaooc_base_parser_string_until_chrs(pointer, const char*, yaooc_terminal_t*);
bool yaooc_base_parser_string_while_chrs(pointer, const char*, yaooc_terminal_t*);
bool yaooc_base_parser_string_until_eol(pointer, yaooc_terminal_t*);
bool yaooc_base_parser_whitespace(pointer,yaooc_terminal_t*);
bool yaooc_base_parser_chr(pointer, char, yaooc_terminal_t*);
int yaooc_base_parser_chr_choices(pointer, const char*);
bool yaooc_base_parser_str(pointer, const char*, yaooc_terminal_t*);
int yaooc_base_parser_str_choices(pointer, ...);
bool yaooc_base_parser_digits(pointer, yaooc_terminal_t*);
bool yaooc_base_parser_hexdigits(pointer, yaooc_terminal_t*);
bool yaooc_base_parser_integer(pointer, yaooc_terminal_t*);
bool yaooc_base_parser_hexinteger(pointer, yaooc_terminal_t*);
bool yaooc_base_parser_real(pointer, yaooc_terminal_t*);
bool yaooc_base_parser_ident(pointer, yaooc_terminal_t*);
bool yaooc_base_parser_regex(pointer, const char*, uint32_t, uint32_t, yaooc_terminal_t*);
bool yaooc_base_parser_quoted_string(pointer, char, yaooc_terminal_t*);
bool yaooc_base_parser_single_quoted_string(pointer, yaooc_terminal_t*);
bool yaooc_base_parser_double_quoted_string(pointer, yaooc_terminal_t*);
bool yaooc_base_parser_bare_string(pointer, yaooc_terminal_t*);
bool yaooc_base_parser_string_until_matching_chr(pointer, char, char, yaooc_terminal_t*);
bool yaooc_base_parser_result(const_pointer);

/* Protected prototypes for yaooc_base_parser */
int yaooc_base_parser_next_chr(pointer);
bool yaooc_base_parser_space(pointer, yaooc_terminal_t*);
bool yaooc_base_parser_crlf(pointer, yaooc_terminal_t*);
bool yaooc_base_parser_shell_comment(pointer, yaooc_terminal_t*);
bool yaooc_base_parser_c_comment(pointer, yaooc_terminal_t*);
bool yaooc_base_parser_cpp_comment(pointer, yaooc_terminal_t*);

/* End YAOOCPP output */


#endif
