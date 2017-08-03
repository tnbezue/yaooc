#ifndef __JSON_PARSER_INCLUDED__
#define __JSON_PARSER_INCLUDED__

#include <yaooc/string.h>
#include <yaooc/base_parser.h>
#include <yaooc/json.h>

class_(json_pair)
{
  json_string_pointer key;
  json_value_pointer value;
};

class_table(json_parser) {
  yaooc_base_parser_class_members_t;
  json_value_pointer (*jnull)(pointer);
  json_value_pointer (*jbool)(pointer);
  json_value_pointer (*jinteger)(pointer);
  json_value_pointer (*jreal)(pointer);
  json_value_pointer (*jstring)(pointer);
  json_value_pointer (*jarray)(pointer);
  json_pair_pointer (*jpair)(pointer);
  json_value_pointer (*jobject)(pointer);
  json_value_pointer (*jvalue)(pointer);
  json_value_pointer (*parse_string)(pointer,const char *);
  json_value_pointer (*parse_file)(pointer,const char *);
};

class_instance(json_parser) {
  yaooc_base_parser_instance_members_t;
};

class(json_parser);

/* Type info */
void json_parser_default_ctor(pointer);


/* Class member functions */
json_value_pointer json_parser_jnull(pointer);
json_value_pointer json_parser_jbool(pointer);
json_value_pointer json_parser_jinteger(pointer);
json_value_pointer json_parser_jreal(pointer);
json_value_pointer json_parser_jstring(pointer);
json_value_pointer json_parser_jarray(pointer);
json_pair_pointer json_parser_jpair(pointer);
json_value_pointer json_parser_jobject(pointer);
json_value_pointer json_parser_jvalue(pointer);
json_value_pointer json_parser_parse_string(pointer,const char *);
json_value_pointer json_parser_parse_file(pointer,const char *);

/* Protected members */
void json_parser_swap(pointer,pointer);

#define JSON_PARSER_CLASS_MEMBERS \
  { YAOOC_BASE_PARSER_CLASS_MEMBERS }, \
  (json_value_pointer (*)(pointer)) json_parser_jnull,\
  (json_value_pointer (*)(pointer)) json_parser_jbool,\
  (json_value_pointer (*)(pointer)) json_parser_jinteger,\
  (json_value_pointer (*)(pointer)) json_parser_jreal,\
  (json_value_pointer (*)(pointer)) json_parser_jstring,\
  (json_value_pointer (*)(pointer)) json_parser_jarray,\
  (json_pair_pointer (*)(pointer)) json_parser_jpair,\
  (json_value_pointer (*)(pointer)) json_parser_jobject,\
  (json_value_pointer (*)(pointer)) json_parser_jvalue,\
  (json_value_pointer (*)(pointer,const char *)) json_parser_parse_string,\
  (json_value_pointer (*)(pointer,const char *)) json_parser_parse_file,\


#endif
