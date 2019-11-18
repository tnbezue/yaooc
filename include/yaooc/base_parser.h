#ifndef __BASE_PARSER_INCLUDED__
#define __BASE_PARSER_INCLUDED__


#include <yaooc/object.h>


#include <yaooc/stack.h>
#ifdef __YAOOC_USE_TRE__
#include <tre/regex.h>
#else
#include <regex.h>
#endif

yaooc_struct_forward(parser_position);

#define yaooc_base_parser_current_pos(p) ((yaooc_base_parser_pointer)p)->current_pos_
#define yaooc_base_parser_peek(p) *(((yaooc_base_parser_pointer)p)->current_pos_)
#define yaooc_base_parser_skip(p,n) { int __nn__=n; for(;__nn__>0;__nn__--) yaooc_base_parser_next_chr(p); }

STACK_DEFINITION(parser_position,parser_position_stack);

#define yaooc_default_token(p) \
     (yaooc_token_t){ .beg_=((yaooc_base_parser_pointer)p)->current_pos_, .end_=NULL }

enum { PARSE_SUCCESS = 0, PARSE_FAILED };

#define RULE_START(p) M((yaooc_base_parser_pointer)this,rule_start)
#define RULE_FAIL(p) M((yaooc_base_parser_pointer)this,rule_fail)
#define RULE_SUCCESS(p) M((yaooc_base_parser_pointer)this,rule_success)

#define YAOOC_PARSER_OPTIONAL(rule) ((rule),true)
#define YAOOC_PARSER_TRY_RULE(p,rule) (RULE_START(p), (rule) ? RULE_SUCCESS(p) : RULE_FAIL(p))
#define yaooc_token_len(t) (((t).end_ > (t).beg_ ) ? (t).end_ - (t).beg_ : 0 )


yaooc_min_struct(parser_position) {
  const char* pos_;
  size_t line_no_;
};
yaooc_min_struct(yaooc_token) {
  const char* beg_;
  const char* end_;
};
char* yaooc_token_raw_text(const_pointer);
char* yaooc_token_text(const_pointer);
yaooc_class_table(yaooc_base_parser) {
  yaooc_object_class_table_t;
  void (*set_parse_string)(pointer,const char*);
  void (*rule_start)(pointer);
  bool (*rule_success)(pointer);
  bool (*rule_fail)(pointer);
  bool (*eos)(pointer);
  bool (*chr)(pointer,char,yaooc_token_t*);
  int (*chr_choices)(pointer,const char*,yaooc_token_t*);
  bool (*str)(pointer,const char*,yaooc_token_t*);
  int (*str_choices)(pointer,yaooc_token_t*,...);
  bool (*digits)(pointer,yaooc_token_t*);
  bool (*hexdigits)(pointer,yaooc_token_t*);
  bool (*integer)(pointer,yaooc_token_t*);
  bool (*hexinteger)(pointer,yaooc_token_t*);
  bool (*real)(pointer,yaooc_token_t*);
  bool (*ident)(pointer,yaooc_token_t*);
  bool (*regex)(pointer,regex_t*,uint32_t,size_t,regmatch_t*,yaooc_token_t*);
  bool (*quoted_string)(pointer,char,yaooc_token_t*);
  bool (*single_quoted_string)(pointer,yaooc_token_t*);
  bool (*double_quoted_string)(pointer,yaooc_token_t*);
  bool (*bare_string)(pointer,yaooc_token_t*);
  bool (*string_until_chrs)(pointer,const char*,yaooc_token_t*);
  bool (*string_while_chrs)(pointer,const char*,yaooc_token_t*);
  bool (*string_until_eol)(pointer,yaooc_token_t*);
  bool (*whitespace)(pointer,yaooc_token_t*);
  bool (*string_within_matching_chr)(pointer,char,char,yaooc_token_t*);
  bool (*result)(const_pointer);
};
#define yaooc_base_parser_parent_class_table ((yaooc_object_class_table_t*)(yaooc_base_parser_class_table.parent_class_table_))

yaooc_class_instance(yaooc_base_parser) {
  parser_position_stack_t* stack_;
  const char* parse_string_;
  const char* current_pos_;
  unsigned int line_no_;
};

yaooc_class(yaooc_base_parser);

void yaooc_base_parser_default_ctor(pointer);
void yaooc_base_parser_dtor(pointer);
#define yaooc_base_parser_swap yaooc_object_swap
void yaooc_base_parser_set_parse_string(pointer,const char*);
void yaooc_base_parser_rule_start(pointer);
bool yaooc_base_parser_rule_success(pointer);
bool yaooc_base_parser_rule_fail(pointer);
bool yaooc_base_parser_eos(pointer);
bool yaooc_base_parser_chr(pointer,char,yaooc_token_t*);
int yaooc_base_parser_chr_choices(pointer,const char*,yaooc_token_t*);
bool yaooc_base_parser_str(pointer,const char*,yaooc_token_t*);
int yaooc_base_parser_str_choices(pointer,yaooc_token_t*,...);
bool yaooc_base_parser_digits(pointer,yaooc_token_t*);
bool yaooc_base_parser_hexdigits(pointer,yaooc_token_t*);
bool yaooc_base_parser_integer(pointer,yaooc_token_t*);
bool yaooc_base_parser_hexinteger(pointer,yaooc_token_t*);
bool yaooc_base_parser_real(pointer,yaooc_token_t*);
bool yaooc_base_parser_ident(pointer,yaooc_token_t*);
bool yaooc_base_parser_regex(pointer,regex_t*,uint32_t,size_t,regmatch_t*,yaooc_token_t*);
bool yaooc_base_parser_quoted_string(pointer,char,yaooc_token_t*);
bool yaooc_base_parser_single_quoted_string(pointer,yaooc_token_t*);
bool yaooc_base_parser_double_quoted_string(pointer,yaooc_token_t*);
bool yaooc_base_parser_bare_string(pointer,yaooc_token_t*);
bool yaooc_base_parser_string_until_chrs(pointer,const char*,yaooc_token_t*);
bool yaooc_base_parser_string_while_chrs(pointer,const char*,yaooc_token_t*);
bool yaooc_base_parser_string_until_eol(pointer,yaooc_token_t*);
bool yaooc_base_parser_whitespace(pointer,yaooc_token_t*);
bool yaooc_base_parser_string_within_matching_chr(pointer,char,char,yaooc_token_t*);
bool yaooc_base_parser_result(const_pointer);
int yaooc_base_parser_next_chr(pointer);
int yaooc_base_parser_prev_chr(pointer);
bool yaooc_base_parser_space(pointer,yaooc_token_t*);
bool yaooc_base_parser_crlf(pointer,yaooc_token_t*);
bool yaooc_base_parser_shell_comment(pointer,yaooc_token_t*);
bool yaooc_base_parser_c_comment(pointer,yaooc_token_t*);
bool yaooc_base_parser_cpp_comment(pointer,yaooc_token_t*);

#endif
