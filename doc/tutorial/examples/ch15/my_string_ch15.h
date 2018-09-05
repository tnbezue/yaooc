#ifndef __MY_STRING_V5_INCLUDED__
#define __MY_STRING_V5_INCLUDED__

/* Begin YAOOCPP output */

#include <yaooc/object.h>
#include <yaooc/exception.h>

/*
  Class definition for my_string
*/
yaooc_class_table(my_string)
{
  yaooc_object_class_table_t;
  const size_t my_string_n_pos;
  const char* (*get)(const_pointer);
  const char* (*c_str)(const_pointer);
  void (*set)(pointer,const char*);
  my_string_pointer (*substr)(pointer,size_t,size_t);
  void (*insert)(pointer,size_t,const char*);
  void (*insertn)(pointer,size_t,const char*,size_t);
  void (*erase)(pointer,size_t,size_t);
  void (*append)(pointer,const char*);
  void (*appendn)(pointer,const char*,size_t);
  const char* (*find)(const_pointer,const char*);
  const char* (*rfind)(const_pointer,const char*);
  const char* (*find_chr)(const_pointer,char);
  const char* (*rfind_chr)(const_pointer,char);
  char* (*at)(pointer,size_t);
  size_t (*size)(const_pointer);
  size_t (*length)(const_pointer);
  char* (*begin)(const_pointer);
  char* (*end)(const_pointer);
};
#define my_string_parent_class_table ((yaooc_object_class_table_t*)(my_string_class_table.parent_class_table_))

yaooc_class_instance(my_string)
{
  yaooc_object_class_instance_t;
  char* str;
};

yaooc_class(my_string);

/* Prototypes for my_string type info */
void my_string_default_ctor(pointer);
void my_string_dtor(pointer);
void my_string_copy_ctor(pointer,const_pointer);
void my_string_assign(pointer,const_pointer);
bool my_string_less_than_compare(const_pointer,const_pointer);
void my_string_to_stream(const_pointer,pointer);
void my_string_from_stream(pointer,pointer);

/* Prototypes for my_string constructors */
void my_string_ctor_ccs_n(pointer,va_list);
void my_string_ctor_ccs(pointer,va_list);
void my_string_ctor_chr_n(pointer,va_list);

/* Prototypes for my_string class table */
const char* my_string_isa(const_pointer);
#define my_string_is_descendant yaooc_object_is_descendant
void my_string_swap(pointer,pointer);
const char* my_string_get(const_pointer);
#define my_string_c_str my_string_get
void my_string_set(pointer,const char*);
my_string_pointer my_string_substr(pointer,size_t,size_t);
void my_string_insert(pointer,size_t,const char*);
void my_string_insertn(pointer,size_t,const char*,size_t);
void my_string_erase(pointer,size_t,size_t);
void my_string_append(pointer,const char*);
void my_string_appendn(pointer,const char*,size_t);
const char* my_string_find(const_pointer,const char*);
const char* my_string_rfind(const_pointer,const char*);
const char* my_string_find_chr(const_pointer,char);
const char* my_string_rfind_chr(const_pointer,char);
char* my_string_at(pointer,size_t);
size_t my_string_size(const_pointer);
#define my_string_length my_string_size
#define my_string_begin my_string_get
char* my_string_end(const_pointer);

/* Prototypes for my_string protected members */
void my_string_insert_space(pointer,size_t,size_t);
void my_string_erase_space(pointer,size_t,size_t);

/*
  Class Definition for my_string_exception
*/
yaooc_class_table(my_string_exception) {
  yaooc_exception_class_table_t;
};
#define my_string_exception_parent_class_table ((yaooc_exception_class_table_t*)(my_string_exception_class_table.parent_class_table_))

yaooc_class_instance(my_string_exception) {
  yaooc_exception_class_instance_t;
};

yaooc_class(my_string_exception);

/* Type Info Prototypes for my_string_exception */
#define my_string_exception_default_ctor yaooc_exception_default_ctor
#define my_string_exception_dtor yaooc_exception_dtor
#define my_string_exception_copy_ctor yaooc_exception_copy_ctor
#define my_string_exception_assign yaooc_exception_assign

/* Constructors prototypes for my_string_exception */
#define my_string_exception_ctor_v yaooc_exception_ctor_v

/* Table prototypes for my_string_exception */
const char* my_string_exception_isa(const_pointer);
#define my_string_exception_is_descendant yaooc_exception_is_descendant
#define my_string_exception_swap yaooc_exception_swap
#define my_string_exception_what yaooc_exception_what

/* Protected prototypes for my_string_exception */

/*
  Class Definition for my_string_insert_exception
*/
yaooc_class_table(my_string_insert_exception) {
  my_string_exception_class_table_t;
};
#define my_string_insert_exception_parent_class_table ((my_string_exception_class_table_t*)(my_string_insert_exception_class_table.parent_class_table_))

yaooc_class_instance(my_string_insert_exception) {
  my_string_exception_class_instance_t;
};

yaooc_class(my_string_insert_exception);

/* Type Info Prototypes for my_string_insert_exception */
#define my_string_insert_exception_default_ctor my_string_exception_default_ctor
#define my_string_insert_exception_dtor my_string_exception_dtor
#define my_string_insert_exception_copy_ctor my_string_exception_copy_ctor
#define my_string_insert_exception_assign my_string_exception_assign

/* Constructors prototypes for my_string_insert_exception */
#define my_string_insert_exception_ctor_v yaooc_exception_ctor_v

/* Table prototypes for my_string_insert_exception */
const char* my_string_insert_exception_isa(const_pointer);
#define my_string_insert_exception_is_descendant my_string_exception_is_descendant
#define my_string_insert_exception_swap my_string_exception_swap
#define my_string_insert_exception_what my_string_exception_what

/* Protected prototypes for my_string_insert_exception */

/*
  Class Definition for my_string_erase_exception
*/
yaooc_class_table(my_string_erase_exception) {
  my_string_exception_class_table_t;
};
#define my_string_erase_exception_parent_class_table ((my_string_exception_class_table_t*)(my_string_erase_exception_class_table.parent_class_table_))

yaooc_class_instance(my_string_erase_exception) {
  my_string_exception_class_instance_t;
};

yaooc_class(my_string_erase_exception);

/* Type Info Prototypes for my_string_erase_exception */
#define my_string_erase_exception_default_ctor my_string_exception_default_ctor
#define my_string_erase_exception_dtor my_string_exception_dtor
#define my_string_erase_exception_copy_ctor my_string_exception_copy_ctor
#define my_string_erase_exception_assign my_string_exception_assign

/* Constructors prototypes for my_string_erase_exception */
#define my_string_erase_exception_ctor_v yaooc_exception_ctor_v

/* Table prototypes for my_string_erase_exception */
const char* my_string_erase_exception_isa(const_pointer);
#define my_string_erase_exception_is_descendant my_string_exception_is_descendant
#define my_string_erase_exception_swap my_string_exception_swap
#define my_string_erase_exception_what my_string_exception_what

/* Protected prototypes for my_string_erase_exception */

/*
  Class Definition for my_string_at_exception
*/
yaooc_class_table(my_string_at_exception) {
  my_string_exception_class_table_t;
};
#define my_string_at_exception_parent_class_table ((my_string_exception_class_table_t*)(my_string_at_exception_class_table.parent_class_table_))

yaooc_class_instance(my_string_at_exception) {
  my_string_exception_class_instance_t;
};

yaooc_class(my_string_at_exception);

/* Type Info Prototypes for my_string_at_exception */
#define my_string_at_exception_default_ctor my_string_exception_default_ctor
#define my_string_at_exception_dtor my_string_exception_dtor
#define my_string_at_exception_copy_ctor my_string_exception_copy_ctor
#define my_string_at_exception_assign my_string_exception_assign

/* Constructors prototypes for my_string_at_exception */
#define my_string_at_exception_ctor_v yaooc_exception_ctor_v

/* Table prototypes for my_string_at_exception */
const char* my_string_at_exception_isa(const_pointer);
#define my_string_at_exception_is_descendant my_string_exception_is_descendant
#define my_string_at_exception_swap my_string_exception_swap
#define my_string_at_exception_what my_string_exception_what

/* Protected prototypes for my_string_at_exception */

/*  End YAOOC PreProcessor generated content */

#endif
