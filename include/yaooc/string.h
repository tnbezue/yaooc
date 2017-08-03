#ifndef __STRING_INCLUDED__
#define __STRING_INCLUDED__

#include <yaooc/container.h>
#include <string.h>

class_instance(yaooc_string)
{
	yaooc_container_instance_members_t;
};

typedef char* yaooc_string_iterator;
typedef char const * yaooc_string_const_iterator;

class_table(yaooc_string) {
  yaooc_container_class_members_t;
	const size_t		npos;		// static variable
  void (*insert)(pointer,size_t,const char*);
  void (*insertn)(pointer,size_t,const char*,size_t);
  void (*insert_chr)(pointer,size_t,char);
  void (*insertn_chr)(pointer,size_t,char,size_t);
  void (*set)(pointer,const char*);
  void (*setn)(pointer,const char*,size_t);
  void (*append) (pointer,const char*);
  void (*appendn) (pointer,const char*,size_t);
  void (*erase)(pointer,size_t,size_t);
  void (*replace)(pointer,size_t,size_t,const char*);
  void (*replacen)(pointer,size_t,size_t,const char*,size_t);
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
  void (*squeeze)(pointer,const char*);
  void	(*shrink_to_fit)(pointer);
  void (*resize)(pointer,size_t,char);
  size_t (*findstr)(const_pointer,const char*,size_t);
  size_t (*rfindstr)(const_pointer,const char*,size_t);
  size_t (*findchr)(const_pointer,char,size_t);
  size_t (*rfindchr)(const_pointer,char,size_t);
  yaooc_string_iterator (*at)(pointer,size_t);
  yaooc_string_const_iterator (*cat)(const_pointer,size_t);
  const char* (*c_str)(const_pointer);
  yaooc_string_iterator (*begin) (pointer);
  yaooc_string_iterator (*end) (pointer);
  yaooc_string_const_iterator (*cbegin) (const_pointer);
  yaooc_string_const_iterator (*cend) (const_pointer);
};

class(yaooc_string);
ISA_DEFINITION(yaooc_string,yaooc_container)

// Constructors
void yaooc_string_ctor_ccs(pointer,va_list); // string(const char*)
void yaooc_string_ctor_chr_n(pointer,va_list); // string(char c, int)
void yaooc_string_ctor_ccs_n(pointer,va_list); // string(const char *, int)

extern yaooc_string_class_members_t yaooc_string_class_members;

void yaooc_string_default_ctor(pointer p);
//void yaooc_string_dtor(pointer p);
void yaooc_string_assign(pointer d,const_pointer s);
void yaooc_string_copy_ctor(pointer d,const_pointer s);
bool yaooc_string_lt_compare(const_pointer v1,const const_pointer v2);

void yaooc_string_insert_chr(pointer,size_t,char);
void yaooc_string_insertn_chr(pointer,size_t,char,size_t);
void yaooc_string_set(pointer,const char*);
void yaooc_string_setn(pointer,const char*,size_t);
void yaooc_string_appendn(pointer this,const char* s,size_t n);
void yaooc_string_append(pointer this,const char* s);
void yaooc_string_insert(pointer this,size_t spos, const char* s);
void yaooc_string_insertn(pointer this,size_t spos, const char* s,size_t n);
#define yaooc_string_reserve yaooc_container_reserve
void yaooc_string_erase(pointer this,size_t spos, size_t n);
void yaooc_string_replace(pointer ,size_t , size_t,const char*);
void yaooc_string_replacen(pointer ,size_t , size_t,const char*, size_t );
yaooc_string_pointer yaooc_string_upcase(const_pointer this);
void yaooc_string_upcase_(pointer this);
yaooc_string_pointer yaooc_string_downcase(const_pointer this);
void yaooc_string_downcase_(pointer this);
yaooc_string_pointer yaooc_string_substr(const_pointer this,size_t pos,size_t n);
yaooc_string_pointer yaooc_string_ltrim(const_pointer);
void yaooc_string_ltrim_(pointer);
yaooc_string_pointer yaooc_string_rtrim(const_pointer);
void yaooc_string_rtrim_(pointer);
yaooc_string_pointer yaooc_string_trim(const_pointer);
void yaooc_string_trim_(pointer);
void yaooc_string_squeeze(pointer,const char*);
void yaooc_string_shrink_to_fit(pointer);
void yaooc_string_resize(pointer,size_t,char);
size_t yaooc_string_findstr(const_pointer this,const char* s,size_t spos);
size_t yaooc_string_rfindstr(const_pointer this,const char* s,size_t spos);
size_t yaooc_string_findchr(const_pointer this,char c,size_t spos);
size_t yaooc_string_rfindchr(const_pointer this,char c,size_t spos);
#define yaooc_string_at yaooc_container_at
#define yaooc_string_cat yaooc_container_cat
//const char* yaooc_string_c_str(const_pointer this);
#define yaooc_string_capacity yaooc_container_capacity
#define yaooc_string_size yaooc_container_size
#define yaooc_string_empty yaooc_container_empty
#define yaooc_string_begin (yaooc_string_iterator (*) (pointer))yaooc_container_begin
#define yaooc_string_end (yaooc_string_iterator (*) (pointer))yaooc_container_end

#define yaooc_string_npos yaooc_string_class_members.npos

void yaooc_string_clear(pointer);


#define YAOOC_CONTAINER_CLASS_MEMBERS_FOR_STRING \
  { \
    yaooc_string_isa, \
    yaooc_string_is_descendent, \
    yaooc_container_swap \
  }, \
  yaooc_container_empty, \
  yaooc_container_size, \
  yaooc_container_capacity, \
  yaooc_container_reserve, \
  yaooc_string_clear

#define YAOOC_STRING_CLASS_MEMBERS \
  { \
    YAOOC_CONTAINER_CLASS_MEMBERS_FOR_STRING \
  }, \
	-1, \
  yaooc_string_insert, \
  yaooc_string_insertn, \
  yaooc_string_insert_chr, \
  yaooc_string_insertn_chr, \
  yaooc_string_set, \
  yaooc_string_setn, \
	yaooc_string_append, \
	yaooc_string_appendn, \
	yaooc_string_erase, \
	yaooc_string_replace, \
	yaooc_string_replacen, \
	yaooc_string_substr, \
	yaooc_string_upcase, \
	yaooc_string_upcase_, \
	yaooc_string_downcase, \
	yaooc_string_downcase_, \
	yaooc_string_ltrim, \
	yaooc_string_ltrim_, \
	yaooc_string_rtrim, \
	yaooc_string_rtrim_, \
	yaooc_string_trim, \
	yaooc_string_trim_, \
	yaooc_string_squeeze, \
	yaooc_string_shrink_to_fit, \
	yaooc_string_resize, \
	yaooc_string_findstr, \
	yaooc_string_rfindstr, \
	yaooc_string_findchr, \
	yaooc_string_rfindchr, \
	(yaooc_string_iterator (*)(pointer,size_t))yaooc_string_at, \
	(yaooc_string_const_iterator (*)(const_pointer,size_t))yaooc_string_at, \
	(yaooc_string_const_iterator (*) (const_pointer))yaooc_string_begin, \
  yaooc_string_begin, \
  yaooc_string_end, \
  (yaooc_string_const_iterator (*) (const_pointer))yaooc_string_begin, \
  (yaooc_string_const_iterator (*) (const_pointer))yaooc_string_end

/*
  Quick way to create a string
*/
#define make_yaooc_string(s) new_ctor(yaooc_string,yaooc_string_ctor_ccs,s)

#endif
