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

#ifndef __YAOOC_PAIR_INCLUDED__
#define __YAOOC_PAIR_INCLUDED__

#include <yaooc/new.h>

/*
	Pair definition

	Requirements:
			K_t and V_t are valid types.
			K_ti and V_ti are type information for K_t and V_t respectively

*/

void __pair_to_stream(const type_info_t*,const_pointer,const type_info_t*,const_pointer,pointer);
void __pair_from_stream(const type_info_t*,pointer,const type_info_t*,pointer,pointer);

#define PAIR_DEFINITION(K,V,N) \
typedef struct {\
	const K ## _t first; \
	V ## _t second; \
} N ## _t ;\
typedef N ## _t* N ## _pointer; \
typedef const N ## _t* N ## _const_pointer; \
void  N ## _default_ctor(pointer); \
void  N ## _dtor(pointer); \
void  N ## _copy_ctor(pointer,const_pointer); \
void  N ## _assign(pointer,const_pointer); \
bool  K ## _ ## V ## _less_than_compare(const_pointer,const_pointer);\
void make_ ## N (N ## _t*,const K ## _t*,const V ## _t*);\
extern const type_info_t* const N ## _ti;

#define PAIR_IMPLEMENTATION(K,V,N) \
void  N ## _default_ctor(pointer p) \
{ \
	N ## _t * this=p; \
	newp((pointer)&this->first,K); \
	newp(&this->second,V); \
} \
void N ## _dtor(pointer p) \
{ \
	N ## _t * this=p; \
	__deletep_array((pointer)&this->first,K ## _ti,1); \
	__deletep_array(&this->second,V ## _ti,1); \
} \
void N ## _assign(pointer d,const_pointer s) \
{ \
	N ## _t* dst=d; \
	const N ## _t* src=s; \
	__assign_static((pointer)&dst->first,&src->first,K ## _ti); \
	__assign_static(&dst->second,&src->second,V ## _ti); \
} \
void N ## _copy_ctor(pointer d,const_pointer s) \
{ \
	N ## _default_ctor(d); \
	N ## _assign(d,s); \
} \
bool N ## _less_than_compare(const_pointer v1,const_pointer v2) \
{ \
	return __op_lt_static(&((const N ## _t*)v1)->first,&((const N ## _t*)v2)->first,K ## _ti); \
} \
void N ## _to_stream(const_pointer p,pointer s) \
{ \
	const N ## _t * this=p; \
	__pair_to_stream(K ## _ti,&this->first,V ## _ti,&this->second,s); \
} \
void N ## _from_stream(pointer p,pointer s) \
{ \
	N ## _t * this=p; \
	__pair_from_stream(K ## _ti,(pointer)&this->first,V ## _ti,(pointer)&this->second,s); \
} \
DEFINE_TYPE_INFO(N,N ## _default_ctor,N ## _dtor,N ## _copy_ctor,N ## _assign,\
    N ## _less_than_compare, N ## _to_stream,N ## _from_stream,NULL,NULL) \
void make_ ## N (N ## _t*this,const K ## _t* k,const V ## _t* v) \
{ \
  memcpy((pointer)&this->first,k,sizeof(K ## _t)); \
  if(v != NULL) memcpy((pointer)&this->second,v,sizeof(V ## _t)); \
}

#endif
