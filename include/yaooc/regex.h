#ifndef __REGEX_INCLUDED__
#define __REGEX_INCLUDED__

#define PCRE2_CODE_UNIT_WIDTH 8
#include <yaooc/object.h>
#include <yaooc/string.h>
#include <pcre2.h>

class_table(yaooc_matchdata) {
  yaooc_object_class_members_t;
  char* (*at)(pointer,uint32_t);
  yaooc_string_const_pointer (*subject)(const_pointer);
  bool (*good)(const_pointer);
  bool (*bad)(const_pointer);
  uint32_t (*size)(const_pointer);
};

class_instance(yaooc_matchdata) {
  yaooc_object_instance_members_t;
  yaooc_string_pointer subject_;
  pcre2_match_data * match_data_;
  uint32_t match_flags_;
};

class(yaooc_matchdata);
ISA_DEFINITION(yaooc_matchdata,yaooc_object)

/* Type info */
void yaooc_matchdata_default_ctor(pointer);
void yaooc_matchdata_dtor(pointer);
void yaooc_matchdata_copy_ctor(pointer,const_pointer);
void yaooc_matchdata_assign(pointer,const_pointer);


/* Class member functions */
ISA_DEFINITION(yaooc_matchdata,yaooc_object)
char* yaooc_matchdata_at(pointer,uint32_t);
yaooc_string_const_pointer yaooc_matchdata_subject(const_pointer);
bool yaooc_matchdata_good(const_pointer);
bool yaooc_matchdata_bad(const_pointer);
uint32_t yaooc_matchdata_size(const_pointer);

/* Protected members */

#define YAOOC_MATCHDATA_CLASS_MEMBERS \
  { \
    yaooc_matchdata_isa, \
    yaooc_matchdata_is_descendent, \
    yaooc_object_swap \
  }, \
  (char* (*)(pointer,uint32_t)) yaooc_matchdata_at,\
  (yaooc_string_const_pointer (*)(const_pointer)) yaooc_matchdata_subject,\
  (bool (*)(const_pointer)) yaooc_matchdata_good,\
  (bool (*)(const_pointer)) yaooc_matchdata_bad,\
  (uint32_t (*)(const_pointer)) yaooc_matchdata_size,\

class_table(yaooc_regex) {
  yaooc_object_class_members_t;
  void (*set_pattern)(pointer,const char *,int);
  yaooc_string_const_pointer (*get_pattern)(const_pointer);
  int (*get_flags)(const_pointer);
  yaooc_matchdata_pointer (*match)(pointer,const char *,int);
  bool (*match_next)(pointer,pointer);
  bool (*good)(const_pointer);
  bool (*bad)(const_pointer);
};

class_instance(yaooc_regex) {
  yaooc_object_instance_members_t;
  pcre2_code * re_;
  int compile_flags_;
  yaooc_string_pointer pattern_;
};

class(yaooc_regex);

/* Type info */
void yaooc_regex_default_ctor(pointer);
void yaooc_regex_dtor(pointer);
void yaooc_regex_copy_ctor(pointer,const_pointer);
void yaooc_regex_assign(pointer,const_pointer);

/* Constructors */
void yaooc_regex_ctor_pat_flags(pointer,va_list);

/* Class member functions */
ISA_DEFINITION(yaooc_regex,yaooc_object)
void yaooc_regex_set_pattern(pointer,const char *,int);
yaooc_string_const_pointer yaooc_regex_get_pattern(const_pointer);
int yaooc_regex_get_flags(const_pointer);
yaooc_matchdata_pointer yaooc_regex_match(pointer,const char *,uint32_t);
bool yaooc_regex_match_next(pointer,pointer);
bool yaooc_regex_good(const_pointer);
bool yaooc_regex_bad(const_pointer);

/* Protected members */

#define YAOOC_REGEX_CLASS_MEMBERS \
  { \
    yaooc_regex_isa, \
    yaooc_regex_is_descendent, \
    yaooc_object_swap \
  }, \
  (void (*)(pointer,const char *,int)) yaooc_regex_set_pattern,\
  (yaooc_string_const_pointer (*)(const_pointer)) yaooc_regex_get_pattern,\
  (int (*)(const_pointer)) yaooc_regex_get_flags,\
  (yaooc_matchdata_pointer (*)(pointer,const char *,int)) yaooc_regex_match,\
  (bool (*)(pointer,pointer)) yaooc_regex_match_next,\
  (bool (*)(const_pointer)) yaooc_regex_good,\
  (bool (*)(const_pointer)) yaooc_regex_bad,\


#endif
