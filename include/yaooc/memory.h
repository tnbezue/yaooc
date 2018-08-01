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

#ifndef __YAOOC_MEMORY_INCLUDED__
#define __YAOOC_MEMORY_INCLUDED__

#include <yaooc/object.h>

/*
 * Pointer that as a POD type.  Can only used for pointers that point to objects
 * that were dynamically allocated (i.e., new, new_ctor, etc)
 */
void dynamic_pointer_default_ctor(pointer);
void dynamic_pointer_dtor(pointer);
void dynamic_pointer_copy_ctor(pointer,const_pointer);
void dynamic_pointer_assign(pointer,const_pointer);
bool dynamic_pointer_less_than_compare(const_pointer,const_pointer);


#define DYNAMIC_POINTER_DEFINITION(T,N) \
typedef T ## _t* N ## _t; \
typedef N ## _t* N ## _pointer; \
typedef const N ## _t* N ## _const_pointer; \
extern const type_info_t* const N ## _ti;

#define DYNAMIC_POINTER_IMPLEMENTATION(T,N) \
__DEFINE_TYPE_INFO__(N,dynamic_pointer_default_ctor,dynamic_pointer_dtor,dynamic_pointer_copy_ctor,dynamic_pointer_assign,dynamic_pointer_less_than_compare,NULL,NULL,NULL,NULL)

#if 0

void N ## _default_ctor(pointer p) \
{ \
  *(pointer_t*)p = NULL; \
} \
void N ## _dtor(pointer p) \
{ \
  if(*(pointer_t*)p) { \
    delete (*(pointer_t*)p); \
    *(pointer_t*)p=NULL; \
  } \
} \
void dynamic_pointer_copy_ctor(pointer d,const_pointer s) \
{ \
  if(*(pointer_t*)s) \
    *(pointer_t*)d=new_copy(*(pointer_t*)s); \
  else \
    *(pointer_t*)d=NULL; \
} \
void dynamic_pointer_assign(pointer d,const_pointer s) \
{ \
  pointer_dtor(*(pointer_t*)d); \
  pointer_copy_ctor(d,s); \
} \
bool dynamic_pointer_less_than_compare(const_pointer p1,const_pointer p2) \
{ \
  return op_lt(*(pointer_t*)p1,*(pointer_t*)p2); \
}\

#endif

/*  Begin YAOOC PreProcessor generated content */

/*
  Class definition for yaooc_unique_ptr
*/

yaooc_class_table(yaooc_unique_ptr)
{
  yaooc_object_class_table_t;
  pointer (*get)(const_pointer);
  pointer (*release)(pointer);
  void (*reset)(pointer,pointer);
};

yaooc_class_instance(yaooc_unique_ptr)
{
  void* ptr_;
};

yaooc_class(yaooc_unique_ptr);

/* Prototypes for type info */
void yaooc_unique_ptr_default_ctor(pointer);
void yaooc_unique_ptr_dtor(pointer);
void yaooc_unique_ptr_copy_ctor(pointer,const_pointer);
void yaooc_unique_ptr_assign(pointer,const_pointer);
bool yaooc_unique_ptr_less_than_compare(const_pointer,const_pointer);

/* Prototypes for Constructors */
void yaooc_unique_ptr_ctor_ptr(pointer,va_list);

/* Prototypes for class table members */
const char* yaooc_unique_ptr_isa(const_pointer);
#define yaooc_unique_ptr_is_descendant yaooc_object_is_descendant
void yaooc_unique_ptr_swap(pointer,pointer);
pointer yaooc_unique_ptr_get(const_pointer);
pointer yaooc_unique_ptr_release(pointer);
void yaooc_unique_ptr_reset(pointer,pointer);

/* Prototypes for class instance members */

/* Prototypes for class protected members */

/*
  Unique pointer for a specific type.  New type will be type with "unique_ptr" appended
  For methods that return a pointer, it's a pointer of specified type
*/
#define UNIQUE_PTR_DEFINITION(T,NAME) \
yaooc_class_table(NAME) \
{ \
  yaooc_object_class_table_t; \
  T ## _pointer (*get)(NAME ## _const_pointer); \
  void (*reset)(NAME ## _pointer,T ## _pointer); \
  T ## _pointer (*release)(NAME ## _pointer); \
}; \
yaooc_class_instance(NAME) \
{ \
  T ## _t* ptr_; \
}; \
yaooc_class(NAME); \
void NAME ## _ctor_ptr(pointer,va_list);

#define UNIQUE_PTR_IMPLEMENTATION(T,NAME) \
void NAME ## _ctor_ptr(pointer p,va_list args) \
{ call_constructor(p,yaooc_unique_ptr_ctor_ptr,va_arg(args,pointer)); } \
const char* NAME ## _isa(const_pointer p) { return # NAME "_t"; } \
NAME ## _class_table_t NAME ## _class_table = \
{ \
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table, \
  .isa = (const char*(*) (const_pointer)) NAME ## _isa, \
  .is_descendant = (bool(*) (const_pointer,const char*)) yaooc_object_is_descendant, \
  .swap = (void(*) (pointer,pointer)) yaooc_unique_ptr_swap, \
  .get = (T ## _pointer (*)(NAME ## _const_pointer))yaooc_unique_ptr_get, \
  .reset = (void (*) (NAME ## _pointer,T ## _pointer)) yaooc_unique_ptr_reset, \
  .release = (T ## _pointer (*)(NAME ## _pointer))yaooc_unique_ptr_release \
}; \
DEFINE_TYPE_INFO(NAME,N,N,N,N,N,N,N,Y,yaooc_unique_ptr)

/*
  Shared pointer
*/

typedef struct yaooc_counter_s yaooc_counter_t;

yaooc_class_table(yaooc_shared_ptr)
{
  yaooc_object_class_table_t;
  pointer (*get)(const_pointer);
  pointer (*release)(pointer);
  void (*reset)(pointer,pointer);
  size_t (*count)(const_pointer);
};

yaooc_class_instance(yaooc_shared_ptr)
{
  yaooc_counter_t* counter_;
};

yaooc_class(yaooc_shared_ptr);

/* Prototypes for type info */
void yaooc_shared_ptr_default_ctor(pointer);
void yaooc_shared_ptr_dtor(pointer);
void yaooc_shared_ptr_copy_ctor(pointer,const_pointer);
void yaooc_shared_ptr_assign(pointer,const_pointer);
bool yaooc_shared_ptr_less_than_compare(const_pointer,const_pointer);

/* Prototypes for Constructors */
void yaooc_shared_ptr_ctor_ptr(pointer,va_list);

/* Prototypes for class table members */
const char* yaooc_shared_ptr_isa(const_pointer);
#define yaooc_shared_ptr_is_descendant yaooc_object_is_descendant
void yaooc_shared_ptr_swap(pointer,pointer);
pointer yaooc_shared_ptr_get(const_pointer);
pointer yaooc_shared_ptr_release(pointer);
void yaooc_shared_ptr_reset(pointer,pointer);
size_t yaooc_shared_ptr_count(const_pointer);

/* Prototypes for class instance members */

/* Prototypes for class protected members */

/*
  The following template implements same as above.  The values of get are
  of the correct pointer type.
*/
#define SHARED_PTR_DEFINITION(T,NAME) \
yaooc_class_table(NAME) \
{ \
  yaooc_object_class_table_t; \
	T ## _pointer (*get)(NAME ## _const_pointer); \
	T ## _pointer	(*release)(NAME ## _pointer); \
  void  (*reset)(NAME ## _pointer,T ## _pointer); \
  size_t (*count)(NAME ## _const_pointer); \
}; \
yaooc_class_instance(NAME) { \
	yaooc_counter_t* counter_; \
}; \
yaooc_class(NAME); \
void NAME ## _ctor_ptr(pointer this,va_list args); \
const char* NAME ## _isa(const_pointer);

#define SHARED_PTR_IMPLEMENTATION(T,NAME) \
void NAME ## _ctor_ptr(pointer this,va_list args) \
	{ call_constructor(this,yaooc_shared_ptr_ctor_ptr,va_arg(args,pointer)); } \
const char* NAME ## _isa(const_pointer p) { return # NAME "_t"; } \
NAME ## _class_table_t NAME ## _class_table = {\
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table, \
  .isa = (const char* (*) (const_pointer)) NAME ## _isa, \
  .is_descendant = (bool (*) (const_pointer,const char*)) yaooc_object_is_descendant, \
  .swap = (void (*) (pointer,pointer)) yaooc_shared_ptr_swap, \
  .get = (T ## _pointer (*) (NAME ## _const_pointer)) yaooc_shared_ptr_get, \
  .release = (T ## _pointer (*) (NAME ## _pointer)) yaooc_shared_ptr_release, \
  .reset = (void (*) (NAME ## _pointer,T ## _pointer)) yaooc_shared_ptr_reset, \
  .count = (size_t (*) (NAME ## _const_pointer)) yaooc_shared_ptr_count, \
};\
DEFINE_TYPE_INFO(NAME,N,N,N,N,N,N,N,Y,yaooc_shared_ptr)

#endif
