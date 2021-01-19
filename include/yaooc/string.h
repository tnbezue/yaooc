#ifndef __STRING_INCLUDED__
#define __STRING_INCLUDED__
#include <yaooc/new.h>
#include <yaooc/array_container.h>
typedef char* yaooc_string_iterator;
typedef const char* yaooc_string_const_iterator;

#include <yaooc/vector.h>

yaooc_class_forward(yaooc_regex);
yaooc_class_forward(yaooc_string_vector);
void yaooc_string_sub_(pointer,const char* pat,const char* repl_str);
void yaooc_string_sub_re_(pointer,yaooc_regex_const_pointer re,const char* repl_str);
void yaooc_string_gsub_(pointer,const char* pat,const char* str);
void yaooc_string_gsub_re_(pointer,yaooc_regex_const_pointer re,const char* pat);
bool yaooc_string_match(const_pointer,const char* pat);
bool yaooc_string_match_re(const_pointer,yaooc_regex_const_pointer re);
yaooc_string_vector_pointer yaooc_string_split(const_pointer,const char* str,size_t max);
yaooc_string_vector_pointer yaooc_string_split_re(const_pointer,yaooc_regex_const_pointer re,size_t max);


yaooc_class_table(yaooc_string) {
  yaooc_array_container_class_table_t;
char* (*at)(pointer,size_t);
void (*reserve)(pointer,size_t);
void (*insert)(pointer,size_t,const char*);
void (*insertn)(pointer,size_t,const char*,size_t);
void (*insert_chr)(pointer,size_t,char);
void (*insertn_chr)(pointer,size_t,size_t,char);
void (*set)(pointer,const char*);
void (*setn)(pointer,const char*,size_t);
void (*erase)(pointer,size_t);
void (*erasen)(pointer,size_t,size_t);
void (*replace)(pointer,size_t,size_t,const char*);
void (*replacen)(pointer,size_t,size_t,const char*,size_t);
void (*resize)(pointer,size_t);
void (*resize_value)(pointer,size_t,char);
void (*shrink_to_fit)(pointer);
void (*append)(pointer,const char*);
void (*appendn)(pointer,const char*,size_t);
yaooc_string_pointer (*substr)(const_pointer,size_t,size_t);
yaooc_string_pointer (*upcase)(const_pointer);
void (*upcase_)(pointer);
yaooc_string_pointer (*downcase)(const_pointer);
void (*downcase_)(pointer);
yaooc_string_pointer (*ltrim)(const_pointer);
void (*ltrim_)(pointer);
yaooc_string_pointer (*rtrim)(const_pointer);
void (*rtrim_)(pointer);
yaooc_string_pointer (*trim)(const_pointer);
void (*trim_)(pointer);
yaooc_string_pointer (*sub)(const_pointer,const char*,const char*);
void (*sub_)(pointer,const char*,const char*);
yaooc_string_pointer (*sub_re)(const_pointer,yaooc_regex_const_pointer,const char*);
void (*sub_re_)(pointer,yaooc_regex_const_pointer,const char*);
yaooc_string_pointer (*gsub)(const_pointer,const char*,const char*);
void (*gsub_)(pointer,const char*,const char*);
yaooc_string_pointer (*gsub_re)(const_pointer,yaooc_regex_const_pointer,const char*);
void (*gsub_re_)(pointer,yaooc_regex_const_pointer,const char*);
bool (*match)(const_pointer,const char*);
bool (*match_re)(const_pointer,yaooc_regex_const_pointer);
bool (*starts_with)(const_pointer,const char*);
bool (*ends_with)(const_pointer,const char*);
void (*clear)(pointer);
size_t (*findstr)(pointer,const char*,size_t);
size_t (*rfindstr)(pointer,const char*,size_t);
size_t (*findchr)(pointer,char,size_t);
size_t (*rfindchr)(pointer,char,size_t);
yaooc_string_vector_pointer (*split)(const_pointer,const char*,size_t);
yaooc_string_vector_pointer (*split_re)(const_pointer,yaooc_regex_const_pointer,size_t);
const char* (*c_str)(const_pointer);
};
#define yaooc_string_parent_class_table ((yaooc_array_container_class_table_t*)(yaooc_string_class_table.parent_class_table_))

yaooc_class_instance(yaooc_string) {
  yaooc_array_container_class_instance_t;
};

yaooc_class(yaooc_string);
void yaooc_string_default_ctor(pointer);
void yaooc_string_copy_ctor(pointer,const_pointer);
void yaooc_string_assign(pointer,const_pointer);
int yaooc_string_rich_compare(const_pointer,const_pointer);
void yaooc_string_to_stream(const_pointer,ostream_pointer);
void yaooc_string_from_stream(pointer,ostream_pointer);
void yaooc_string_ctor_ccs(pointer,va_list);
void yaooc_string_ctor_ccs_n(pointer,va_list);
void yaooc_string_ctor_chr_n(pointer,va_list);
#define yaooc_string_swap yaooc_array_container_swap
#define yaooc_string_increase_capacity yaooc_array_container_increase_capacity
 size_t yaooc_string_size_needed(const_pointer,size_t);
#define yaooc_string_size yaooc_array_container_size
#define yaooc_string_capacity yaooc_array_container_capacity
#define yaooc_string_empty yaooc_array_container_empty
#define yaooc_string_begin yaooc_array_container_begin
#define yaooc_string_end yaooc_array_container_end
#define yaooc_string_cbegin yaooc_array_container_cbegin
#define yaooc_string_cend yaooc_array_container_cend
 char* yaooc_string_at(pointer,size_t);
#define yaooc_string_reserve yaooc_array_container_reserve
 void yaooc_string_insert(pointer,size_t,const char*);
 void yaooc_string_insertn(pointer,size_t,const char*,size_t);
 void yaooc_string_insert_chr(pointer,size_t,char);
 void yaooc_string_insertn_chr(pointer,size_t,size_t,char);
 void yaooc_string_set(pointer,const char*);
 void yaooc_string_setn(pointer,const char*,size_t);
 void yaooc_string_erase(pointer,size_t);
 void yaooc_string_erasen(pointer,size_t,size_t);
 void yaooc_string_replace(pointer,size_t,size_t,const char*);
 void yaooc_string_replacen(pointer,size_t,size_t,const char*,size_t);
 void yaooc_string_resize(pointer,size_t);
 void yaooc_string_resize_value(pointer,size_t,char);
#define yaooc_string_shrink_to_fit yaooc_array_container_shrink_to_fit
 void yaooc_string_append(pointer,const char*);
 void yaooc_string_appendn(pointer,const char*,size_t);
 yaooc_string_pointer yaooc_string_substr(const_pointer,size_t,size_t);
 yaooc_string_pointer yaooc_string_upcase(const_pointer);
 void yaooc_string_upcase_(pointer);
 yaooc_string_pointer yaooc_string_downcase(const_pointer);
 void yaooc_string_downcase_(pointer);
 yaooc_string_pointer yaooc_string_ltrim(const_pointer);
 void yaooc_string_ltrim_(pointer);
 yaooc_string_pointer yaooc_string_rtrim(const_pointer);
 void yaooc_string_rtrim_(pointer);
 yaooc_string_pointer yaooc_string_trim(const_pointer);
 void yaooc_string_trim_(pointer);
 yaooc_string_pointer yaooc_string_sub(const_pointer,const char*,const char*);
#define yaooc_string_sub_ yaooc_string_sub_
 yaooc_string_pointer yaooc_string_sub_re(const_pointer,yaooc_regex_const_pointer,const char*);
#define yaooc_string_sub_re_ yaooc_string_sub_re_
 yaooc_string_pointer yaooc_string_gsub(const_pointer,const char*,const char*);
#define yaooc_string_gsub_ yaooc_string_gsub_
 yaooc_string_pointer yaooc_string_gsub_re(const_pointer,yaooc_regex_const_pointer,const char*);
#define yaooc_string_gsub_re_ yaooc_string_gsub_re_
#define yaooc_string_match yaooc_string_match
#define yaooc_string_match_re yaooc_string_match_re
 bool yaooc_string_starts_with(const_pointer,const char*);
 bool yaooc_string_ends_with(const_pointer,const char*);
 void yaooc_string_clear(pointer);
 size_t yaooc_string_findstr(pointer,const char*,size_t);
 size_t yaooc_string_rfindstr(pointer,const char*,size_t);
 size_t yaooc_string_findchr(pointer,char,size_t);
 size_t yaooc_string_rfindchr(pointer,char,size_t);
#define yaooc_string_split yaooc_string_split
#define yaooc_string_split_re yaooc_string_split_re
#define yaooc_string_c_str yaooc_array_container_begin
extern  const size_t yaooc_string_npos;
VECTOR_DEFINITION(yaooc_string,yaooc_string_vector);
#define YAOOC_STRING_STATIC_DEFAULT_CTOR { .class_table_ = &yaooc_string_class_table, \
    .array_=NULL,.type_info_=(const type_info_t*)&__char_ti,.size_=0,.capacity_=0 }


#endif
