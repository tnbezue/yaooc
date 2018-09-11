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

#ifndef __STRING_INCLUDED__
#define __STRING_INCLUDED__

#include <yaooc/vector.h>

typedef char* yaooc_string_iterator;
typedef const char* yaooc_string_const_iterator;
yaooc_class_forward(yaooc_regex);
yaooc_class_forward(yaooc_string_vector);

/*  Begin YAOOC PreProcessor generated content */

/*
  Class definition for yaooc_string
*/
yaooc_class_table(yaooc_string)
{
  yaooc_pod_array_class_table_t;
  yaooc_string_iterator (*at)(const_pointer,size_t);
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
	yaooc_string_pointer (*gsub)(const_pointer,const char*,const char*);
	void (*gsub_)(pointer,const char*,const char*);
	bool (*match)(const_pointer,const char*);
  bool (*starts_with)(const_pointer,const char*);
  bool (*ends_with)(const_pointer,const char*);
  void (*clear)(pointer);
  size_t (*findstr)(pointer,const char*,size_t);
  size_t (*rfindstr)(pointer,const char*,size_t);
  size_t (*findchr)(pointer,char,size_t);
  size_t (*rfindchr)(pointer,char,size_t);
  yaooc_string_vector_pointer(*split)(const_pointer,const char*,size_t);
  const char* (*c_str)(const_pointer);
};

yaooc_class_instance(yaooc_string)
{
  yaooc_pod_array_class_instance_t;
};

yaooc_class(yaooc_string);
/* Prototypes for yaooc_string type info */
void yaooc_string_default_ctor(pointer);
void yaooc_string_dtor(pointer);
void yaooc_string_copy_ctor(pointer,const_pointer);
void yaooc_string_assign(pointer,const_pointer);
bool yaooc_string_less_than_compare(const_pointer,const_pointer);

/* Constructors for yaooc_string */
void yaooc_string_ctor_ccs(pointer,va_list);
void yaooc_string_ctor_ccs_n(pointer,va_list);
void yaooc_string_ctor_n_chr(pointer,va_list);

/* Prototypes for yaooc_string class table*/
#define yaooc_string_swap yaooc_pod_array_swap
bool yaooc_string_increase_capacity(pointer,size_t);
size_t yaooc_string_size_needed(const_pointer,size_t);
#define yaooc_string_size yaooc_pod_array_size
#define yaooc_string_capacity yaooc_pod_array_capacity
#define yaooc_string_empty yaooc_pod_array_empty
#define yaooc_string_begin yaooc_pod_array_begin
#define yaooc_string_end yaooc_pod_array_end
#define yaooc_string_at yaooc_pod_array_at
#define yaooc_string_reserve yaooc_pod_array_reserve
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
#define yaooc_string_shrink_to_fit yaooc_pod_array_shrink_to_fit
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
void yaooc_string_sub_(pointer,const char*,const char*);
yaooc_string_pointer yaooc_string_gsub(const_pointer,const char*,const char*);
void yaooc_string_gsub_(pointer,const char*,const char*);
bool yaooc_string_match(const_pointer,const char*);
bool yaooc_string_starts_with(const_pointer,const char*);
bool yaooc_string_ends_with(const_pointer,const char*);
size_t yaooc_string_findstr(pointer,const char*,size_t);
size_t yaooc_string_rfindstr(pointer,const char*,size_t);
size_t yaooc_string_findchr(pointer,char,size_t);
size_t yaooc_string_rfindchr(pointer,char,size_t);
yaooc_string_vector_pointer yaooc_string_split(const_pointer,const char*,size_t);
//yaooc_string_vector_pointer yaooc_string_split_re(const_pointer,const char*,size_t);
#define yaooc_string_c_str yaooc_pod_array_begin


/* Prototypes for yaooc_string class instance*/

/* Prototypes for yaooc_string class protected items*/
extern const size_t yaooc_string_npos;

/*  End YAOOC PreProcessor generated content */

#define YAOOC_STRING_STATIC_DEFAULT_CTOR { .class_table_ = &yaooc_string_class_table, .array_=NULL, \
		.type_info_=&__char_ti,.size_=0,.capacity_=0 }

VECTOR_DEFINITION(yaooc_string,yaooc_string_vector)

#endif
