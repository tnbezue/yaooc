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

#ifndef __YAOOC_POD_ARRAY_INCLUDED__
#define __YAOOC_POD_ARRAY_INCLUDED__

#include <yaooc/object.h>
/*
  Used for POD types or structs made of POD types.  Intended for internal YAOOC usage.
  It has the advantage of not having to check if items contained has defuault constructors,
  destructor, etc.
*/
/*  Begin YAOOC PreProcessor generated content */

/*
  Class definition for yaooc_pod_array
*/
class_table(yaooc_pod_array)
{
  yaooc_object_class_table_t;
  bool (*increase_capacity)(pointer,size_t); //const size_t extra_capacity_;
  size_t (*size_needed)(const_pointer,size_t);
  size_t (*size)(const_pointer);
  size_t (*capacity)(const_pointer);
  bool (*empty)(const_pointer);
  iterator (*begin)(const_pointer);
  iterator (*end)(const_pointer);
};
class_instance(yaooc_pod_array)
{
  yaooc_object_class_instance_t;
  char* array_;
  const type_info_t* type_info_;
  size_t size_;
  size_t capacity_;
};

class(yaooc_pod_array);


/* Prototypes for yaooc_pod_array type info */
void yaooc_pod_array_default_ctor(pointer);
void yaooc_pod_array_dtor(pointer);
void yaooc_pod_array_copy_ctor(pointer,const_pointer);
void yaooc_pod_array_assign(pointer,const_pointer);

/* Constructors for yaooc_pod_array */
void yaooc_pod_array_ctor_ti(pointer,va_list);

/* Prototypes for yaooc_pod_array class table*/
const char* yaooc_pod_array_isa(const_pointer);
#define yaooc_pod_array_is_descendant yaooc_object_is_descendant
void yaooc_pod_array_swap(pointer,pointer);
char* yaooc_pod_array_to_s(const_pointer);
bool yaooc_pod_array_increase_capacity(pointer,size_t);
size_t yaooc_pod_array_size_needed(const_pointer,size_t);
size_t yaooc_pod_array_size(const_pointer);
size_t yaooc_pod_array_capacity(const_pointer);
bool yaooc_pod_array_empty(const_pointer);
iterator yaooc_pod_array_begin(const_pointer);
iterator yaooc_pod_array_end(const_pointer);

/* Prototypes for yaooc_pod_array class instance*/

/* Prototypes for yaooc_pod_array class protected items*/
iterator yaooc_pod_array_insert_space(pointer,const_iterator,size_t);
iterator yaooc_pod_array_erase_space(pointer,const_iterator,size_t);
iterator yaooc_pod_array_replace_space(pointer,const_iterator,const_iterator,size_t);
iterator yaooc_pod_array_find(pointer,const_pointer);
iterator yaooc_pod_array_insert(pointer,const_iterator,const_pointer);
iterator yaooc_pod_array_insertn(pointer,const_iterator,size_t,const_pointer);
iterator yaooc_pod_array_insert_range(pointer,const_iterator,const_iterator,const_iterator);
iterator yaooc_pod_array_erase(pointer,const_iterator);
iterator yaooc_pod_array_erase_range(pointer,const_iterator,const_iterator);
size_t yaooc_pod_array_erase_value(pointer,const_pointer);
iterator yaooc_pod_array_at(const_pointer,size_t);
void yaooc_pod_array_shrink_to_fit(pointer);
void yaooc_pod_array_reserve(pointer,size_t);
void yaooc_pod_array_clear(pointer);

#define FOR_EACH(ITER,ARRAY) for(ITER=M(ARRAY,begin);ITER!=M(ARRAY,end);ITER++)

#define TYPE_INFO(p) (((yaooc_pod_array_const_pointer)p)->type_info_)
#define TYPE_SIZE(p) (TYPE_INFO(p)->type_size_)
#define SIZE(p)  (((yaooc_pod_array_const_pointer)p)->size_)
#define CAPACITY(p)  (((yaooc_pod_array_const_pointer)p)->capacity_)
#define BEGIN(p) (((yaooc_pod_array_pointer)p)->array_)
#define AT(p,i) (BEGIN(p)+((i)*TYPE_SIZE(p)))
#define END(p)  AT(p,SIZE(p))
#define INDEX(p,pos) (((yaooc_private_const_iterator)(pos)-BEGIN(p))/TYPE_SIZE(p))

#define YAOOC_POD_ARRAY_DEFINITION(T,N) \
typedef T ## _t* N ## _iterator; \
typedef const T ## _t* N ## _const_iterator; \
class_table(N) { \
  yaooc_pod_array_class_table_t; \
  N ## _iterator(*insert)(N ## _pointer,const_iterator,T ## _t); \
  N ## _iterator(*insertn)(N ## _pointer,const_iterator,size_t,T ## _t); \
  N ## _iterator(*insert_range)(N ## _pointer,const_iterator,const_iterator); \
  N ## _iterator(*insert_back)(N ## _pointer,T ## _t); \
  N ## _iterator(*insert_front)(N ## _pointer,T ## _t); \
  N ## _iterator(*find)(N ## _pointer,T ## _t); \
  N ## _iterator(*erase)(N ## _pointer,const_iterator); \
  N ## _iterator(*erase_range)(N ## _pointer,const_iterator,const_iterator); \
  size_t (*erase_value)(N ## _pointer,T ## _t); \
  N ## _iterator(*erase_front)(N ## _pointer); \
  N ## _iterator(*erase_back)(N ## _pointer); \
  void (*clear)(pointer); \
}; \
class_instance(N) { \
  yaooc_pod_array_class_instance_t; \
}; \
class(N); \
N ## _iterator N ## _insert(N ## _t*,const_iterator,T ## _t); \
N ## _iterator N ## _insertn(N ## _t*,const_iterator,size_t,T ## _t); \
N ## _iterator N ## _insert_range(N ## _t*,const_iterator,const_iterator); \
N ## _iterator N ## _insert_back(N ## _t*,T ## _t); \
N ## _iterator N ## _insert_front(N ## _t*,T ## _t); \
N ## _iterator N ## _erase_front(N ## _t*); \
N ## _iterator N ## _erase_back(N ## _t*);

#define YAOOC_POD_ARRAY_IMPLEMENTATION(T,N) \
void N ## _default_ctor(pointer p) \
{\
  call_constructor(p,yaooc_pod_array_ctor_ti,T ## _ti); \
}\
N ## _iterator N ## _insert(N ## _t* this,const_iterator pos,T ## _t value) \
{ \
  return yaooc_pod_array_insert(this,pos,&value); \
}\
N ## _iterator N ## _insertn(N ## _t* this,const_iterator pos,size_t n,T ## _t value) \
{ \
  return yaooc_pod_array_insertn(this,pos,n,&value); \
}\
N ## _iterator N ## _insert_front(N ## _t* this,T ## _t value) \
{ \
  return yaooc_pod_array_insert(this,BEGIN(this),&value); \
} \
N ## _iterator N ## _insert_back(N ## _t* this,T ## _t value) \
{ \
  return yaooc_pod_array_insert(this,END(this),&value); \
} \
N ## _iterator N ## _erase_front(N ## _t* this)\
{\
  return yaooc_pod_array_erase(this,BEGIN(this)); \
}\
N ## _iterator N ## _erase_back(N ## _t* this)\
{\
  return yaooc_pod_array_erase(this,END(this)); \
}\
size_t N ## _erase_value(N ## _t* this,T ## _t value)\
{\
  return yaooc_pod_array_erase_value(this,&value); \
}\
N ## _iterator N ## _find(N ## _pointer this,T ## _t value) \
{\
  return yaooc_pod_array_find(this,&value); \
} \
N ## _class_table_t N ## _class_table= {\
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table, \
  .isa = (const char* (*) (const_pointer p)) yaooc_pod_array_isa, \
  .is_descendant = (bool (*) (const_pointer p,const char*)) yaooc_pod_array_is_descendant, \
  .swap = (void (*) (pointer p,pointer)) yaooc_pod_array_swap, \
  .increase_capacity =(bool(*)(pointer,size_t)) yaooc_pod_array_increase_capacity, \
  .size_needed = (size_t (*)(const_pointer,size_t)) yaooc_pod_array_size_needed, \
  .size = (size_t (*) (const_pointer p)) yaooc_pod_array_size, \
  .capacity = (size_t (*) (const_pointer p)) yaooc_pod_array_capacity, \
  .empty = (bool (*) (const_pointer p)) yaooc_pod_array_empty, \
  .begin = (iterator (*) (const_pointer p)) yaooc_pod_array_begin, \
  .end = (iterator (*) (const_pointer p)) yaooc_pod_array_end, \
  .insert=N ## _insert, \
  .insertn=N ## _insertn, \
  .insert_range=(N ## _iterator(*)(N ## _t*,const_iterator,const_iterator))yaooc_pod_array_insert_range, \
  .insert_back=N ## _insert_back, \
  .find=N ## _find, \
  .erase=(N ## _iterator(*)(N ## _pointer,const_iterator))yaooc_pod_array_erase,\
  .erase_range=(N ## _iterator(*)(N ## _pointer,const_iterator,const_iterator))yaooc_pod_array_erase_range,\
  .erase_value=N ## _erase_value, \
  .erase_front=N ## _erase_front, \
  .erase_back=N ## _erase_back, \
  .clear = yaooc_pod_array_clear, \
}; \
DEFINE_TYPE_INFO(N ,N ## _default_ctor,NULL,NULL,NULL,NULL,NULL,NULL,&N ## _class_table,yaooc_pod_array)

#define YAOOC_POD_ARRAY(T,N) \
YAOOC_POD_ARRAY_DEFINITION(T,N) \
YAOOC_POD_ARRAY_IMPLEMENTATION(T,N)


#endif
