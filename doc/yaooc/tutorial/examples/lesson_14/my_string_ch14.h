#ifndef __MY_STRING_CH14_INCLUDED__
#define __MY_STRING_CH14_INCLUDED__

/* Begin YAOOCPP output */

#include <yaooc/object.h>
#include <string.h>
#include <yaooc/stream.h>

/*
  Class Definition for my_string
*/
yaooc_class_table(my_string) {
  yaooc_object_class_table_t;
  const size_t n_pos;
  const char* (*get)(const_pointer);
  const char* (*c_str)(const_pointer);
  void (*set)(pointer, const char*);
  my_string_pointer (*substr)(pointer, size_t, size_t);
  void (*insert)(pointer, size_t, const char*);
  void (*insertn)(pointer, size_t, const char*, size_t);
  void (*erase)(pointer, size_t, size_t);
  void (*append)(pointer, const char*);
  void (*appendn)(pointer, const char*, size_t);
  const char* (*find)(const_pointer, const char*);
  const char* (*rfind)(const_pointer, const char*);
  const char* (*find_chr)(const_pointer, char);
  const char* (*rfind_chr)(const_pointer, char);
  char* (*at)(pointer, size_t);
  size_t (*size)(const_pointer);
  size_t (*length)(const_pointer);
  char* (*begin)(const_pointer);
  char* (*end)(const_pointer);
};
#define my_string_parent_class_table ((yaooc_object_class_table_t*)(my_string_class_table.parent_class_table_))

yaooc_class_instance(my_string) {
//  yaooc_object_class_instance_t;
  char* str;
};

yaooc_class(my_string);

/* Type Info Prototypes for my_string */
void my_string_default_ctor(pointer);
void my_string_dtor(pointer);
void my_string_copy_ctor(pointer,const_pointer);
void my_string_assign(pointer,const_pointer);
int my_string_rich_compare(const_pointer,const_pointer);
void my_string_to_stream(const_pointer,ostream_pointer);
void my_string_from_stream(pointer,istream_pointer);

/* Constructors prototypes for my_string */
void my_string_ctor_ccs_size(pointer,va_list);
void my_string_ctor_ccs(pointer,va_list);
void my_string_ctor_chr_size(pointer,va_list);

/* Table prototypes for my_string */
void my_string_swap(pointer, pointer);
const char* my_string_get(const_pointer);
#define my_string_c_str my_string_get
void my_string_set(pointer, const char*);
my_string_pointer my_string_substr(pointer, size_t, size_t);
void my_string_insert(pointer, size_t, const char*);
void my_string_insertn(pointer, size_t, const char*, size_t);
void my_string_erase(pointer, size_t, size_t);
void my_string_append(pointer, const char*);
void my_string_appendn(pointer, const char*, size_t);
const char* my_string_find(const_pointer, const char*);
const char* my_string_rfind(const_pointer, const char*);
const char* my_string_find_chr(const_pointer, char);
const char* my_string_rfind_chr(const_pointer, char);
char* my_string_at(pointer, size_t);
size_t my_string_size(const_pointer);
#define my_string_length my_string_size
#define my_string_begin my_string_get
char* my_string_end(const_pointer);

/* Protected prototypes for my_string */
extern void my_string_insert_space(pointer, size_t, size_t);
extern void my_string_erase_space(pointer, size_t, size_t);

/* End YAOOCPP output */


#endif
