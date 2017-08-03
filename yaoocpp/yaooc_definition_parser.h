#ifndef __yaooc_definition_PARSER_INCLUDED__
#define __yaooc_definition_PARSER_INCLUDED__

#include <yaooc/base_parser.h>
#include "template_objects.h"

class_table(yaooc_definition_parser) {
  yaooc_base_parser_class_members_t;
  bool (*constructors)(pointer,class_definition_pointer);
  bool (*destructor)(pointer,class_definition_pointer);
  bool (*operators)(pointer,class_definition_pointer);
  bool (*member_definition)(pointer,member_definition_pointer,yaooc_string_pointer);
  class_definition_pointer (*class_definition)(pointer);
  item_definition_shared_ptr_vector_pointer (*parse)(pointer,const char*);
  item_definition_shared_ptr_vector_pointer (*parse_file)(pointer,const char*);
};

class_instance(yaooc_definition_parser) {
  yaooc_base_parser_instance_members_t;
};

class(yaooc_definition_parser);
ISA_DEFINITION(yaooc_definition_parser,yaooc_base_parser)
bool yaooc_definition_parser_constructors(pointer,class_definition_pointer);
bool yaooc_definition_parser_destructor(pointer,class_definition_pointer);
bool yaooc_definition_parser_operators(pointer,class_definition_pointer);
bool yaooc_definition_parser_member_definition(pointer,member_definition_pointer,yaooc_string_pointer);
item_definition_shared_ptr_vector_pointer yaooc_definition_parser_parse(pointer,const char*);
item_definition_shared_ptr_vector_pointer yaooc_definition_parser_parse_file(pointer,const char*);
class_definition_pointer yaooc_definition_parser_class_definition(pointer);

#define YAOOC_DEFINITION_PARSER_CLASS_MEMBERS \
  { \
    { \
      yaooc_definition_parser_isa, \
      yaooc_definition_parser_is_descendent, \
      yaooc_base_parser_swap \
    }, \
    YAOOC_BASE_PARSER_NEW_MEMBERS \
  }, \
  yaooc_definition_parser_constructors, \
  yaooc_definition_parser_destructor, \
  yaooc_definition_parser_operators, \
  yaooc_definition_parser_member_definition, \
  yaooc_definition_parser_class_definition, \
  yaooc_definition_parser_parse, \
  yaooc_definition_parser_parse_file

#endif
