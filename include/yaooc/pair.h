/*
		Copyright (C) 2016-2019  by Terry N Bezue

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

#ifndef __YAOOC_PAIR_INCLUDED__
#define __YAOOC_PAIR_INCLUDED__

#include <yaooc/new.h>
#include <string.h>
/*
	Pair definition

	Requirements:
			K_t and V_t are valid types.
			K_ti and V_ti are type information for K_t and V_t respectively

*/

void __pair_to_stream(const type_info_t*,const_pointer,const type_info_t*,const_pointer,pointer);
void __pair_from_stream(const type_info_t*,pointer,const type_info_t*,pointer,pointer);

#define PAIR_DEFINITION(K,V,NAME) \
typedef struct {\
	const K ## _t first; \
	V ## _t second; \
} NAME ## _t ;\
typedef NAME ## _t* NAME ## _pointer; \
typedef const NAME ## _t* NAME ## _const_pointer; \
void  NAME ## _default_ctor(pointer); \
void  NAME ## _dtor(pointer); \
void  NAME ## _copy_ctor(pointer,const_pointer); \
void  NAME ## _assign(pointer,const_pointer); \
bool  K ## _ ## V ## _less_than_compare(const_pointer,const_pointer);\
void make_ ## NAME (NAME ## _t*,const K ## _t*,const V ## _t*);\
extern const type_info_t* const NAME ## _ti;

#define PAIR_IMPLEMENTATION(K,V,NAME) \
void  NAME ## _default_ctor(pointer p) \
{ \
	NAME ## _t * this=p; \
	newp((pointer)(&this->first),K); \
	newp(&this->second,V); \
} \
void NAME ## _dtor(pointer p) \
{ \
	NAME ## _t * this=p; \
	__deletep_array((pointer)&this->first,K ## _ti,1); \
	__deletep_array(&this->second,V ## _ti,1); \
} \
void NAME ## _assign(pointer d,const_pointer s) \
{ \
	NAME ## _t* dst=d; \
	const NAME ## _t* src=s; \
	__assign_static((pointer)&dst->first,&src->first,K ## _ti); \
	__assign_static(&dst->second,&src->second,V ## _ti); \
} \
void NAME ## _copy_ctor(pointer d,const_pointer s) \
{ \
	NAME ## _default_ctor(d); \
	NAME ## _assign(d,s); \
} \
bool NAME ## _less_than_compare(const_pointer v1,const_pointer v2) \
{ \
	return __op_lt_static(&((const NAME ## _t*)v1)->first,&((const NAME ## _t*)v2)->first,K ## _ti); \
} \
void NAME ## _to_stream(const_pointer p,pointer s) \
{ \
	const NAME ## _t * this=p; \
	__pair_to_stream(K ## _ti,&this->first,V ## _ti,&this->second,s); \
} \
void NAME ## _from_stream(pointer p,pointer s) \
{ \
	NAME ## _t * this=p; \
	__pair_from_stream(K ## _ti,(pointer)&this->first,V ## _ti,(pointer)&this->second,s); \
} \
DEFINE_TYPE_INFO(NAME,Y,Y,Y,Y,Y,Y,Y,N,NULL) \
void make_ ## NAME (NAME ## _t*this,const K ## _t* k,const V ## _t* v) \
{ \
  memcpy((pointer)&this->first,k,sizeof(K ## _t)); \
  if(v != NULL) memcpy((pointer)&this->second,v,sizeof(V ## _t)); \
}

#endif
