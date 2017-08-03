#ifndef __YAOOC_PAIR_INCLUDED__
#define __YAOOC_PAIR_INCLUDED__

#include <yaooc/new.h>

/*
	Pair definition

	Requirements:
			K_t and V_t are valid types.
			K_ti and V_ti are type information for K_t and V_t respectively

			Example: Given PAIR_DEFINITION(yaooc_string,int32) will create
      yaooc_string_int32_pair_t
*/

#define PAIR_DEFINITION(K,V) \
typedef struct {\
	K ## _t first; \
	V ## _t second; \
} K ## _ ## V ## _pair_t ;\
void  K ## _ ## V ## _pair_default_ctor(pointer); \
void  K ## _ ## V ## _pair_dtor(pointer); \
void  K ## _ ## V ## _pair_copy_ctor(pointer,const_pointer); \
void  K ## _ ## V ## _pair_assign(pointer,const_pointer); \
bool  K ## _ ## V ## _less_than_compare(const_pointer,const_pointer);\
K ## _ ## V ## _pair_t* make_ ## K ## _ ## V ## _pair(const_pointer k,const_pointer p);\
extern const type_info_t* const K ## _ ## V ## _pair_ti;

#define PAIR_IMPLEMENTATION(K,V) \
K ## _ ## V ## _pair_t* make_ ## K ## _ ## V ## _pair(const_pointer k,const_pointer v) \
{ \
  K ## _ ## V ## _pair_t* pair= new(K ## _ ## V ## _pair); \
  real_assign_static(&pair->first,k,K ## _ti); \
  real_assign_static(&pair->second,v,V ## _ti); \
  return pair; \
} \
void  K ## _ ## V ## _pair_default_ctor(pointer p) \
{ \
	K ## _ ## V ## _pair_t * this=p; \
	newp(&this->first,K); \
	newp(&this->second,V); \
} \
void K ## _ ## V ## _pair_dtor(pointer p) \
{ \
	K ## _ ## V ## _pair_t * this=p; \
	real_deletep_array(&this->first,K ## _ti,1); \
	real_deletep_array(&this->second,V ## _ti,1); \
} \
void K ## _ ## V ## _pair_assign(pointer d,const_pointer s) \
{ \
	K ## _ ## V ## _pair_t* dst=d; \
	const K ## _ ## V ## _pair_t* src=s; \
	real_assign_static(&dst->first,&src->first,K ## _ti); \
	real_assign_static(&dst->second,&src->second,V ## _ti); \
} \
void K ## _ ## V ## _pair_copy_ctor(pointer d,const_pointer s) \
{ \
	K ## _ ## V ## _pair_default_ctor(d); \
	K ## _ ## V ## _pair_assign(d,s); \
} \
bool K ## _ ## V ## _pair_less_than_compare(const_pointer v1,const_pointer v2) \
{ \
	return op_lt_static(&((const K ## _ ## V ## _pair_t*)v1)->first,&((const K ## _ ## V ## _pair_t*)v2)->first,K ## _ti); \
} \
DEFINE_TYPE_INFO(K ## _ ## V ## _pair,K ## _ ## V ## _pair_default_ctor,\
    K ## _ ## V ## _pair_dtor,K ## _ ## V ## _pair_copy_ctor,K ## _ ## V ## _pair_assign,\
    K ## _ ## V ## _pair_less_than_compare,NULL,NULL)

#endif
