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
yaooc_class_table(yaooc_pod_array)
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
yaooc_class_instance(yaooc_pod_array)
{
  yaooc_object_class_instance_t;
  char* array_;
  const type_info_t* type_info_;
  size_t size_;
  size_t capacity_;
};

yaooc_class(yaooc_pod_array);


/* Prototypes for yaooc_pod_array type info */
void yaooc_pod_array_default_ctor(pointer);
void yaooc_pod_array_dtor(pointer);
void yaooc_pod_array_copy_ctor(pointer,const_pointer);
void yaooc_pod_array_assign(pointer,const_pointer);

/* Constructors for yaooc_pod_array */
void yaooc_pod_array_ctor_ti(pointer,va_list);

/* Prototypes for yaooc_pod_array class table*/
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

#define YAOOC_POD_ARRAY_DEFINITION(T,NAME) \
typedef T ## _t* NAME ## _iterator; \
typedef const T ## _t* NAME ## _const_iterator; \
yaooc_class_table(NAME) { \
  yaooc_pod_array_class_table_t; \
  NAME ## _iterator(*insert)(NAME ## _pointer,const_iterator,T ## _t); \
  NAME ## _iterator(*insertn)(NAME ## _pointer,const_iterator,size_t,T ## _t); \
  NAME ## _iterator(*insert_range)(NAME ## _pointer,const_iterator,const_iterator); \
  NAME ## _iterator(*insert_back)(NAME ## _pointer,T ## _t); \
  NAME ## _iterator(*insert_front)(NAME ## _pointer,T ## _t); \
  NAME ## _iterator(*find)(NAME ## _pointer,T ## _t); \
  NAME ## _iterator(*erase)(NAME ## _pointer,const_iterator); \
  NAME ## _iterator(*erase_range)(NAME ## _pointer,const_iterator,const_iterator); \
  size_t (*erase_value)(NAME ## _pointer,T ## _t); \
  NAME ## _iterator(*erase_front)(NAME ## _pointer); \
  NAME ## _iterator(*erase_back)(NAME ## _pointer); \
  void (*clear)(pointer); \
}; \
yaooc_class_instance(NAME) { \
  yaooc_pod_array_class_instance_t; \
}; \
yaooc_class(NAME); \
NAME ## _iterator NAME ## _insert(NAME ## _t*,const_iterator,T ## _t); \
NAME ## _iterator NAME ## _insertn(NAME ## _t*,const_iterator,size_t,T ## _t); \
NAME ## _iterator NAME ## _insert_range(NAME ## _t*,const_iterator,const_iterator); \
NAME ## _iterator NAME ## _insert_back(NAME ## _t*,T ## _t); \
NAME ## _iterator NAME ## _insert_front(NAME ## _t*,T ## _t); \
NAME ## _iterator NAME ## _erase_front(NAME ## _t*); \
NAME ## _iterator NAME ## _erase_back(NAME ## _t*);

#define YAOOC_POD_ARRAY_IMPLEMENTATION(T,NAME) \
void NAME ## _default_ctor(pointer p) \
{\
  call_constructor(p,yaooc_pod_array_ctor_ti,T ## _ti); \
}\
NAME ## _iterator NAME ## _insert(NAME ## _t* this,const_iterator pos,T ## _t value) \
{ \
  return yaooc_pod_array_insert(this,pos,&value); \
}\
NAME ## _iterator NAME ## _insertn(NAME ## _t* this,const_iterator pos,size_t n,T ## _t value) \
{ \
  return yaooc_pod_array_insertn(this,pos,n,&value); \
}\
NAME ## _iterator NAME ## _insert_front(NAME ## _t* this,T ## _t value) \
{ \
  return yaooc_pod_array_insert(this,BEGIN(this),&value); \
} \
NAME ## _iterator NAME ## _insert_back(NAME ## _t* this,T ## _t value) \
{ \
  return yaooc_pod_array_insert(this,END(this),&value); \
} \
NAME ## _iterator NAME ## _erase_front(NAME ## _t* this)\
{\
  return yaooc_pod_array_erase(this,BEGIN(this)); \
}\
NAME ## _iterator NAME ## _erase_back(NAME ## _t* this)\
{\
  return yaooc_pod_array_erase(this,END(this)); \
}\
size_t NAME ## _erase_value(NAME ## _t* this,T ## _t value)\
{\
  return yaooc_pod_array_erase_value(this,&value); \
}\
NAME ## _iterator NAME ## _find(NAME ## _pointer this,T ## _t value) \
{\
  return yaooc_pod_array_find(this,&value); \
} \
NAME ## _class_table_t NAME ## _class_table= {\
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table, \
  .type_name_ = (const char*) #NAME "_t", \
  .swap = (void (*) (pointer p,pointer)) yaooc_pod_array_swap, \
  .increase_capacity =(bool(*)(pointer,size_t)) yaooc_pod_array_increase_capacity, \
  .size_needed = (size_t (*)(const_pointer,size_t)) yaooc_pod_array_size_needed, \
  .size = (size_t (*) (const_pointer p)) yaooc_pod_array_size, \
  .capacity = (size_t (*) (const_pointer p)) yaooc_pod_array_capacity, \
  .empty = (bool (*) (const_pointer p)) yaooc_pod_array_empty, \
  .begin = (iterator (*) (const_pointer p)) yaooc_pod_array_begin, \
  .end = (iterator (*) (const_pointer p)) yaooc_pod_array_end, \
  .insert=NAME ## _insert, \
  .insertn=NAME ## _insertn, \
  .insert_range=(NAME ## _iterator(*)(NAME ## _t*,const_iterator,const_iterator))yaooc_pod_array_insert_range, \
  .insert_back=NAME ## _insert_back, \
  .find=NAME ## _find, \
  .erase=(NAME ## _iterator(*)(NAME ## _pointer,const_iterator))yaooc_pod_array_erase,\
  .erase_range=(NAME ## _iterator(*)(NAME ## _pointer,const_iterator,const_iterator))yaooc_pod_array_erase_range,\
  .erase_value=NAME ## _erase_value, \
  .erase_front=NAME ## _erase_front, \
  .erase_back=NAME ## _erase_back, \
  .clear = yaooc_pod_array_clear, \
}; \
DEFINE_TYPE_INFO(NAME,Y,N,N,N,N,N,N,Y,yaooc_pod_array)

#define YAOOC_POD_ARRAY(T,NAME) \
YAOOC_POD_ARRAY_DEFINITION(T,NAME) \
YAOOC_POD_ARRAY_IMPLEMENTATION(T,NAME)


#endif
