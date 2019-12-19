#ifndef __REGEX_INCLUDED__
#define __REGEX_INCLUDED__

#include <yaooc/object.h>
#include <yaooc/exception.h>
#include <yaooc/string.h>

#ifdef __YAOOC_USE_TRE
#include <tre/regex.h>
#else
#include <regex.h>
#endif



















yaooc_struct_forward(yaooc_regex_pattern_info);
bool yaooc_regex_parse_pattern(const char*,yaooc_regex_pattern_info_t*);

int yaooc_regex_regexec(const regex_t* re,const char* subject,int ofs,size_t n_ov,regmatch_t* ov,int eflags);

yaooc_struct(yaooc_regex_pattern_info) {
char* pattern_;
int flags_;
};
void yaooc_regex_pattern_info_default_ctor(pointer);
void yaooc_regex_pattern_info_dtor(pointer);
void yaooc_regex_pattern_info_copy_ctor(pointer,const_pointer);
void yaooc_regex_pattern_info_assign(pointer,const_pointer);
yaooc_class_table(yaooc_regex_exception) {
  yaooc_exception_class_table_t;
};
#define yaooc_regex_exception_parent_class_table ((yaooc_exception_class_table_t*)(yaooc_regex_exception_class_table.parent_class_table_))

yaooc_class_instance(yaooc_regex_exception) {
  yaooc_exception_class_instance_t;
};

yaooc_class(yaooc_regex_exception);
#define yaooc_regex_exception_ctor_v yaooc_exception_ctor_v
#define yaooc_regex_exception_swap yaooc_exception_swap
#define yaooc_regex_exception_what yaooc_exception_what
#define yaooc_regex_exception_error_code yaooc_exception_error_code
yaooc_class_table(yaooc_matchdata) {
  yaooc_object_class_table_t;
yaooc_string_pointer (*at)(const_pointer,size_t);
yaooc_string_pointer (*exec)(pointer,const char*);
const char* (*subject)(const_pointer);
bool (*good)(const_pointer);
size_t (*size)(const_pointer);
};
#define yaooc_matchdata_parent_class_table ((yaooc_object_class_table_t*)(yaooc_matchdata_class_table.parent_class_table_))

yaooc_class_instance(yaooc_matchdata) {
regmatch_t* ovector_;
char* subject_;
int match_result_;
int n_captures_;
};

yaooc_class(yaooc_matchdata);
void yaooc_matchdata_default_ctor(pointer);
void yaooc_matchdata_dtor(pointer);
void yaooc_matchdata_copy_ctor(pointer,const_pointer);
void yaooc_matchdata_assign(pointer,const_pointer);
 void yaooc_matchdata_swap(pointer,pointer);
 yaooc_string_pointer yaooc_matchdata_at(const_pointer,size_t);
 yaooc_string_pointer yaooc_matchdata_exec(pointer,const char*);
 const char* yaooc_matchdata_subject(const_pointer);
 bool yaooc_matchdata_good(const_pointer);
 size_t yaooc_matchdata_size(const_pointer);
yaooc_class_table(yaooc_regex) {
  yaooc_object_class_table_t;
void (*set_pattern_flags)(pointer,const char*,int);
const char* (*get_pattern)(const_pointer);
int (*get_flags)(const_pointer);
yaooc_matchdata_pointer (*match)(pointer,const char*,int);
bool (*match_next)(pointer,yaooc_matchdata_pointer);
bool (*good)(const_pointer);
};
#define yaooc_regex_parent_class_table ((yaooc_object_class_table_t*)(yaooc_regex_class_table.parent_class_table_))

yaooc_class_instance(yaooc_regex) {
regex_t* re_;
char* pattern_;
int compile_flags_;
int compile_result_;
};

yaooc_class(yaooc_regex);
void yaooc_regex_default_ctor(pointer);
void yaooc_regex_dtor(pointer);
void yaooc_regex_copy_ctor(pointer,const_pointer);
void yaooc_regex_assign(pointer,const_pointer);
void yaooc_regex_ctor_ccs_int(pointer,va_list);
void yaooc_regex_ctor_ccs(pointer,va_list);
#define yaooc_regex_swap yaooc_object_swap
 void yaooc_regex_set_pattern_flags(pointer,const char*,int);
 const char* yaooc_regex_get_pattern(const_pointer);
 int yaooc_regex_get_flags(const_pointer);
 yaooc_matchdata_pointer yaooc_regex_match(pointer,const char*,int);
 bool yaooc_regex_match_next(pointer,yaooc_matchdata_pointer);
 bool yaooc_regex_good(const_pointer);

#endif
