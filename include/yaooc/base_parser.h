#ifndef __BASE_PARSER_INCLUDED__
#define __BASE_PARSER_INCLUDED__

#include <yaooc/string.h>
#include <yaooc/stack.h>

typedef struct {
  const char* pos_;
  uint32_t    line_no_;
} parser_position_t;
extern const type_info_t* const parser_position_ti;
typedef parser_position_t* parser_position_pointer;
typedef const parser_position_t* parser_position_const_pointer;

STACK_DEFINITION(parser_position)
class_table(yaooc_terminal)
{
  char* (*get_text)(pointer);
  char* (*get_raw_text)(pointer);
  bool (*has_value) (const_pointer);
};

class_instance(yaooc_terminal)
{
  const char* beg_;
  const char* end_;
};

class(yaooc_terminal);

#define YAOOC_TERMINAL_CLASS_MEMBERS \
yaooc_terminal_get_text,\
yaooc_terminal_get_raw_text,\
yaooc_terminal_has_value

typedef bool yaooc_static_terminal_t;

typedef enum { CRLF=1,C_COMMENT=2,CPP_COMMENT=4,SHELL_COMMENT=8} whitespace_t;
class_table(yaooc_base_parser)
{
  yaooc_object_class_members_t;
  void (*set_parse_string)(pointer p,const char*);
  char (*current_chr)(pointer p);
  void (*next_chr)(pointer p);
  void (*next_n_chr)(pointer p,uint32_t);
  void (*rule_start)(pointer p);
  void (*rule_success)(pointer p);
  void (*rule_fail)(pointer p);
  yaooc_static_terminal_t (*eos)(pointer);
  yaooc_terminal_t (*string_until_chr_before_chr)(pointer,char,char);
  yaooc_terminal_t (*string_until_chr)(pointer,char);
  yaooc_terminal_t (*string_until_eol)(pointer);
  yaooc_terminal_t (*shell_comment)(pointer);
  yaooc_terminal_t (*c_comment)(pointer);
  yaooc_terminal_t (*cpp_comment)(pointer);
  void (*set_whitespace_types)(pointer,uint32_t);
  void (*set_crlf_as_whitespace)(pointer,bool);
  void (*set_c_comment_as_whitespace)(pointer,bool);
  void (*set_cpp_comment_as_whitespace)(pointer,bool);
  void (*set_shell_comment_as_whitespace)(pointer,bool);
  uint32_t (*get_whitespace_types)(pointer);
  bool (*is_crlf_whitespace)(pointer);
  bool (*is_c_comment_whitespace)(pointer);
  bool (*is_cpp_comment_whitespace)(pointer);
  bool (*is_shell_comment_whitespace)(pointer);
  int (*whitespace)(pointer);
  yaooc_static_terminal_t (*chr)(pointer,char);
  int (*chr_choices)(pointer,const char*);
  yaooc_static_terminal_t (*str)(pointer,const char*);
  int (*str_choices)(pointer,...);
  yaooc_terminal_t (*digits)(pointer);
  yaooc_terminal_t (*hexdigits)(pointer);
  yaooc_terminal_t (*integer)(pointer);
  yaooc_terminal_t (*hexinteger)(pointer);
  yaooc_terminal_t (*real)(pointer);
  yaooc_terminal_t (*ident)(pointer);
  yaooc_terminal_t (*regex)(pointer,const char*,uint32_t,uint32_t);
  yaooc_terminal_t (*quoted_string)(pointer,char);
  yaooc_terminal_t (*single_quoted_string)(pointer);
  yaooc_terminal_t (*double_quoted_string)(pointer);
  yaooc_terminal_t (*bare_string)(pointer);
  yaooc_terminal_t (*string_until_matching_chr)(pointer,char,char);
};

class_instance(yaooc_base_parser)
{
  yaooc_object_instance_members_t;
  const char* string_to_parse_;
  const char* current_pos_;
  parser_position_stack_pointer stack_;
  uint32_t line_no_;
  uint32_t included_in_whitespace_;
  int parser_error_;
};

class(yaooc_base_parser);

ISA_DEFINITION(yaooc_base_parser,yaooc_object)
void yaooc_base_parser_swap(pointer,pointer);
void yaooc_base_parser_default_ctor(pointer p);
void yaooc_base_parser_dtor(pointer p);
void yaooc_base_parser_assign(pointer d,const_pointer s);
void yaooc_base_parser_copy_ctor(pointer d,const_pointer s);
void yaooc_base_parser_set_parse_string(pointer,const char*);
char yaooc_base_parser_current_chr(pointer p);
void yaooc_base_parser_next_chr(pointer p);
void yaooc_base_parser_next_n_chr(pointer p,uint32_t);
void yaooc_base_parser_rule_start(pointer p);
void yaooc_base_parser_rule_success(pointer p);
void yaooc_base_parser_rule_fail(pointer p);
yaooc_terminal_t yaooc_base_parser_string_until_chr_before_chr(pointer,char,char);
yaooc_terminal_t yaooc_base_parser_string_until_chr(pointer,char);
yaooc_terminal_t yaooc_base_parser_string_until_eol(pointer);
yaooc_terminal_t yaooc_base_parser_shell_comment(pointer);
yaooc_terminal_t yaooc_base_parser_c_comment(pointer);
yaooc_terminal_t yaooc_base_parser_cpp_comment(pointer);
void yaooc_base_parser_set_whitespace_types(pointer,uint32_t);
void yaooc_base_parser_set_crlf_as_whitespace(pointer,bool);
void yaooc_base_parser_set_c_comment_as_whitespace(pointer,bool);
void yaooc_base_parser_set_cpp_comment_as_whitespace(pointer,bool);
void yaooc_base_parser_set_shell_comment_as_whitespace(pointer,bool);
uint32_t yaooc_base_parser_get_whitespace_types(pointer);
bool yaooc_base_parser_is_crlf_whitespace(pointer);
bool yaooc_base_parser_is_c_comment_whitespace(pointer);
bool yaooc_base_parser_is_cpp_comment_whitespace(pointer);
bool yaooc_base_parser_is_shell_comment_whitespace(pointer);
int yaooc_base_parser_whitespace(pointer);
yaooc_static_terminal_t yaooc_base_parser_eos(pointer);
yaooc_static_terminal_t yaooc_base_parser_chr(pointer,char);
yaooc_terminal_t yaooc_base_parser_digits(pointer);
yaooc_terminal_t yaooc_base_parser_hexdigits(pointer);
yaooc_terminal_t yaooc_base_parser_integer(pointer);
yaooc_terminal_t yaooc_base_parser_hexinteger(pointer);
yaooc_terminal_t yaooc_base_parser_real(pointer);
yaooc_terminal_t yaooc_base_parser_ident(pointer);
yaooc_terminal_t yaooc_base_parser_regex(pointer,const char*,uint32_t,uint32_t);
yaooc_terminal_t yaooc_base_parser_quoted_string(pointer,char);
yaooc_terminal_t yaooc_base_parser_single_quoted_string(pointer);
yaooc_terminal_t yaooc_base_parser_double_quoted_string(pointer);
yaooc_terminal_t yaooc_base_parser_bare_string(pointer);
yaooc_terminal_t yaooc_base_parser_string_until_matching_chr(pointer,char,char);
int yaooc_base_parser_chr_choices(pointer,const char*);
yaooc_static_terminal_t yaooc_base_parser_str(pointer,const char*);
int yaooc_base_parser_str_choices(pointer,...);

#define YAOOC_BASE_PARSER_OBJECT_CLASS_MEMBERS \
	yaooc_base_parser_isa, \
	yaooc_base_parser_is_descendent, \
	yaooc_base_parser_swap \

#define YAOOC_BASE_PARSER_NEW_MEMBERS \
  yaooc_base_parser_set_parse_string, \
  yaooc_base_parser_current_chr, \
  yaooc_base_parser_next_chr, \
  yaooc_base_parser_next_n_chr, \
  yaooc_base_parser_rule_start, \
  yaooc_base_parser_rule_success, \
  yaooc_base_parser_rule_fail, \
  yaooc_base_parser_eos, \
  yaooc_base_parser_string_until_chr_before_chr, \
  yaooc_base_parser_string_until_chr, \
  yaooc_base_parser_string_until_eol, \
  yaooc_base_parser_shell_comment, \
  yaooc_base_parser_c_comment, \
  yaooc_base_parser_cpp_comment, \
  yaooc_base_parser_set_whitespace_types, \
  yaooc_base_parser_set_crlf_as_whitespace, \
  yaooc_base_parser_set_c_comment_as_whitespace, \
  yaooc_base_parser_set_cpp_comment_as_whitespace, \
  yaooc_base_parser_set_shell_comment_as_whitespace, \
  yaooc_base_parser_get_whitespace_types, \
  yaooc_base_parser_is_crlf_whitespace, \
  yaooc_base_parser_is_c_comment_whitespace, \
  yaooc_base_parser_is_cpp_comment_whitespace, \
  yaooc_base_parser_is_shell_comment_whitespace, \
  yaooc_base_parser_whitespace, \
  yaooc_base_parser_chr, \
  yaooc_base_parser_chr_choices, \
  yaooc_base_parser_str, \
  yaooc_base_parser_str_choices, \
  yaooc_base_parser_digits ,\
  yaooc_base_parser_hexdigits ,\
  yaooc_base_parser_integer ,\
  yaooc_base_parser_hexinteger ,\
  yaooc_base_parser_real ,\
  yaooc_base_parser_ident ,\
  yaooc_base_parser_regex ,\
  yaooc_base_parser_quoted_string,\
  yaooc_base_parser_single_quoted_string,\
  yaooc_base_parser_double_quoted_string,\
  yaooc_base_parser_bare_string, \
  yaooc_base_parser_string_until_matching_chr

#define YAOOC_BASE_PARSER_CLASS_MEMBERS \
  { YAOOC_BASE_PARSER_OBJECT_CLASS_MEMBERS }, \
  YAOOC_BASE_PARSER_NEW_MEMBERS

char* yaooc_terminal_get_raw_text(pointer);
char* yaooc_terminal_get_text(pointer);
bool yaooc_terminal_has_value(const_pointer);

#endif
