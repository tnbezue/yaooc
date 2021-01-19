#ifndef __JSON_PARSER_INCLUDED__
#define __JSON_PARSER_INCLUDED__
#include <yaooc/new.h>
#include <yaooc/base_parser.h>
#include <yaooc/exception.h>
#include <yaooc/json.h>

typedef struct {
  yaooc_json_string_t* key;
  yaooc_json_value_t* value;
} yaooc_json_pair_t;


yaooc_class_table(yaooc_json_parser_exception) {
  yaooc_exception_class_table_t;
};
#define yaooc_json_parser_exception_parent_class_table ((yaooc_exception_class_table_t*)(yaooc_json_parser_exception_class_table.parent_class_table_))

yaooc_class_instance(yaooc_json_parser_exception) {
  yaooc_exception_class_instance_t;
};

yaooc_class(yaooc_json_parser_exception);
#define yaooc_json_parser_exception_ctor_v yaooc_exception_ctor_v
#define yaooc_json_parser_exception_swap yaooc_exception_swap
#define yaooc_json_parser_exception_what yaooc_exception_what
#define yaooc_json_parser_exception_error_code yaooc_exception_error_code
yaooc_class_table(yaooc_json_parser) {
  yaooc_base_parser_class_table_t;
bool (*parse_json_null)(pointer,yaooc_json_value_t**);
bool (*parse_json_bool)(pointer,yaooc_json_value_t**);
bool (*parse_json_integer)(pointer,yaooc_json_value_t**);
bool (*parse_json_real)(pointer,yaooc_json_value_t**);
bool (*parse_json_string)(pointer,yaooc_json_value_t**);
bool (*parse_json_array)(pointer,yaooc_json_value_t**);
bool (*parse_json_object)(pointer,yaooc_json_value_t**);
bool (*parse_json_value)(pointer,yaooc_json_value_t**);
bool (*parse_string)(pointer,const char*,yaooc_json_value_t**);
bool (*parse_file)(pointer,const char*,yaooc_json_value_t**);
};
#define yaooc_json_parser_parent_class_table ((yaooc_base_parser_class_table_t*)(yaooc_json_parser_class_table.parent_class_table_))

yaooc_class_instance(yaooc_json_parser) {
  yaooc_base_parser_class_instance_t;
};

yaooc_class(yaooc_json_parser);
#define yaooc_json_parser_swap yaooc_base_parser_swap
#define yaooc_json_parser_set_parse_string yaooc_base_parser_set_parse_string
#define yaooc_json_parser_rule_start yaooc_base_parser_rule_start
#define yaooc_json_parser_rule_success yaooc_base_parser_rule_success
#define yaooc_json_parser_rule_fail yaooc_base_parser_rule_fail
#define yaooc_json_parser_eos yaooc_base_parser_eos
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
#define yaooc_json_parser_string_until_chrs yaooc_base_parser_string_until_chrs
#define yaooc_json_parser_string_while_chrs yaooc_base_parser_string_while_chrs
#define yaooc_json_parser_string_until_eol yaooc_base_parser_string_until_eol
 bool yaooc_json_parser_whitespace(pointer,yaooc_token_t*);
#define yaooc_json_parser_string_within_matching_chr yaooc_base_parser_string_within_matching_chr
#define yaooc_json_parser_result yaooc_base_parser_result
 bool yaooc_json_parser_parse_json_null(pointer,yaooc_json_value_t**);
 bool yaooc_json_parser_parse_json_bool(pointer,yaooc_json_value_t**);
 bool yaooc_json_parser_parse_json_integer(pointer,yaooc_json_value_t**);
 bool yaooc_json_parser_parse_json_real(pointer,yaooc_json_value_t**);
 bool yaooc_json_parser_parse_json_string(pointer,yaooc_json_value_t**);
 bool yaooc_json_parser_parse_json_array(pointer,yaooc_json_value_t**);
 bool yaooc_json_parser_parse_json_object(pointer,yaooc_json_value_t**);
 bool yaooc_json_parser_parse_json_value(pointer,yaooc_json_value_t**);
 bool yaooc_json_parser_parse_string(pointer,const char*,yaooc_json_value_t**);
 bool yaooc_json_parser_parse_file(pointer,const char*,yaooc_json_value_t**);
 bool yaooc_json_parser_parse_json_pair(pointer,yaooc_json_pair_t*);

#endif
