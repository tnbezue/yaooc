#ifndef __YAOOC_SIMPLE_ARRAY_INCLUDED__
#define __YAOOC_SIMPLE_ARRAY_INCLUDED__

#include <yaooc/new.h>
#include <string.h>
/*
  Used for POD types or structs made of POD types.  Intended for internal YAOOC usage.
*/
#define YAOOC_SIMPLE_ARRAY_DEFINITION(T) \
class_(T ## _simple_array) { \
  T ## _t* array_; \
  yaooc_size_type size_; \
  yaooc_size_type capacity_; \
}; \
typedef T ## _t* T ## _simple_array_iterator; \
typedef const T ## _t* T ## _simple_array_const_iterator; \
T ## _simple_array_iterator T ## _simple_array_insert(T ## _simple_array_t*,yaooc_size_type,T ## _t); \
void T ## _simple_array_erase(T ## _simple_array_t*,yaooc_size_type); \
T ## _simple_array_iterator T ## _simple_array_find(T ## _simple_array_t*,T ## _t);

#define YAOOC_SIMPLE_ARRAY_IMPLEMENTATION(T) \
void T ## _simple_array_default_ctor(pointer p) \
{\
  T ## _simple_array_t* this=p; \
  this->size_=0;\
  this->capacity_=16; \
  this->array_=(T ## _t*)MALLOC(16*sizeof(T ## _t)); \
}\
void T ## _simple_array_dtor(pointer p) { \
  T ## _simple_array_t* this=p; \
  if(this->array_) FREE(this->array_); \
}\
T ## _simple_array_iterator T ## _simple_array_insert(T ## _simple_array_t* this,yaooc_size_type pos,T ## _t value) \
{ \
  if(this->size_>=this->capacity_) { \
    this->capacity_<<= 1; \
    this->array_=(T ## _t*)REALLOC(this->array_,this->capacity_*sizeof(T ## _t)); \
  } \
  memmove(this->array_+pos+1,this->array_+pos,(this->size_-pos)*sizeof(T ## _t)); \
  this->array_[pos]=value;\
  this->size_++; \
  return this->array_+pos; \
}\
void T ## _simple_array_erase(T ## _simple_array_t* this,yaooc_size_type pos)\
{\
  memmove(this->array_+pos,this->array_+pos+1,(this->size_-pos)*sizeof(T ## _t));\
  this->size_--; \
}\
DEFINE_TYPE_INFO(T ## _simple_array,T ## _simple_array_default_ctor,T ## _simple_array_dtor, \
      NULL,NULL,NULL,NULL,NULL)

#define YAOOC_SIMPLE_ARRAY_FIND_POD(T) \
T ## _simple_array_iterator T ## _simple_array_find(T ## _simple_array_t* this,T ## _t value) \
{\
  T ## _simple_array_iterator i; \
  SA_ITERATE(i,this) {\
    if(*i==value) \
      break; \
  }\
  return i; \
}

#define YAOOC_SIMPLE_ARRAY_FIND_NON_POD(T) \
T ## _simple_array_iterator T ## _simple_array_find(T ## _simple_array_t* this,T ## _t value) \
{\
  T ## _simple_array_iterator i; \
  SA_ITERATE(i,this) {\
    if(memcmp(i,&value,sizeof(T ## _t))==0) \
      break; \
  }\
  return i; \
}

#define YAOOC_SIMPLE_ARRAY(T) \
YAOOC_SIMPLE_ARRAY_DEFINITION(T) \
YAOOC_SIMPLE_ARRAY_IMPLEMENTATION(T)

#define SA_CLEAR(sa) sa->size_=0
#define SA_BEGIN(sa) sa->array_
#define SA_END(sa) sa->array_+sa->size_
#define SA_ITERATE(i,sa) for(i=SA_BEGIN(sa);i!=SA_END(sa);i++)

#endif
