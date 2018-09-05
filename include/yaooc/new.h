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

#ifndef __YAOOC_NEW_INCLUDED__
#define __YAOOC_NEW_INCLUDED__

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <inttypes.h>
#include <yaooc/types.h>
#ifdef __YAOOC_USE_GC__
#define GC_THREADS
#include <pthread.h>
#include <gc.h>
#define MALLOC(obj) GC_MALLOC(obj)
#define REALLOC(obj,n) GC_REALLOC(obj,n)
#define FREE(obj) obj=NULL
#define STRDUP(str) GC_strdup(str)
#else
#define MALLOC(obj) malloc(obj)
#define REALLOC(obj,n) realloc(obj,n)
#define FREE(obj) { free(obj); obj=NULL; }
#define STRDUP(str) strdup(str)
#define GC_INIT()
#endif

#include <yaooc/yaooc_debug.h>
#include <yaooc/macros.h>
/*
	New

	C++ allows new to be overloaded in various ways.  In YAOOC, must define separate functions
	for each case.
*/
/*
	Basic new -- arguments are pointer to type info structure and number of elements to allocate.
	The default constructor is used to initilize objects.
*/
#define new(T) __new_array(T ## _ti,1)
#define new_array(T,N) __new_array(T ## _ti,N)
pointer __new_array(const type_info_t*,size_t);
/*
	Placement new -- arguments are pointer to preallocated memory, pointer to type info structure, and number
	of elements.  The default constructor is used to initialize objects.
*/
#define newp(P,T) __newp_array(P,T ## _ti,1)
#define newp_array(P,T,N) __newp_array(P,T ## _ti,N)
pointer __newp_array(pointer,const type_info_t*,size_t);

/*
	Copy new -- arguments are const pointer to object to copy and number of elements.
	Each element is a duplicate of the object to copy.
*/
#define new_copy(CP) __new_array_copy(CP,1)
#define new_array_copy(CP,N) __new_array_copy(CP,N)
pointer __new_array_copy(const_pointer src,size_t);

/*
	Copy placement new (placement version of above)-- arguments are pointer to preallocated memory, const pointer
	to object to copy, and number of elements.
*/
#define newp_copy(P,CP) __newp_array_copy(P,CP,1)
#define newp_array_copy(P,CP,N) __newp_array_copy(P,CP,N)
pointer __newp_array_copy(pointer,const_pointer,size_t);

/*
	Copy static new -- arguments are type info pointer, const pointer to object to be copied, and number of
	elements.

	Note:  Above copy new's dynamically determine the type being copied.
  However, there are times when this can not be used (i.e., when object is in a container).  Therefore,
	the type info has to be supplied.
*/
#define new_copy_static(T,CP)  		__new_array_copy_static(T ## _ti,CP,1)
#define new_array_copy_static(T,CP,N) 		__new_array_copy_static(T ## _ti,CP,N)
pointer __new_array_copy_static(const type_info_t*,const_pointer,size_t);

/*
	Placement version of above
*/
#define newp_copy_static(P,T,CP) __newp_array_copy_static(P,T ## _ti,CP,1)
#define newp_array_copy_static(P,T,CP,N) __newp_array_copy_static(P,T ## _ti,CP,N)
pointer __newp_array_copy_static(pointer,const type_info_t*,const_pointer,size_t);

/*
	New ctor -- arguments are type info pointer, number of elements, constructor, and arguments to constructor
*/
#define new_ctor(T,CON,...)  				__new_array_ctor(T ## _ti,1,CON, __VA_ARGS__)
#define new_array_ctor(T,N,CON,...)  				__new_array_ctor(T ## _ti,N,CON, __VA_ARGS__)
pointer __new_array_ctor(const type_info_t*,size_t, constructor,...);

/*
	new ctor placement.  Placement version of above
*/
#define newp_ctor(P,T,CON,...)  		__newp_array_ctor(P,T ## _ti,1,CON,## __VA_ARGS__)
#define newp_array_ctor(P,T,N,CON,...)  		__newp_array_ctor(P,T ## _ti,N,CON,## __VA_ARGS__)


pointer __newp_array_ctor(pointer,const type_info_t*,size_t,constructor,...);
pointer __new_array_copy_range_static(const type_info_t* ti,const_pointer src,size_t);
pointer __new_array_copy_range(const_pointer,size_t);
pointer __newp_array_copy_range(pointer,const_pointer,size_t);

/*
  Copy construct range of elements
*/
pointer __newp_array_copy_range_static(pointer,const type_info_t*,const_pointer,size_t);

/*
	YAOOC extension.  "renew" is to "new" as "realloc" is to "malloc".

	If size specified if greater than current size, new objects are added.
	If size specified is less than current size, destructor is called for objects beyond new size
	If size is same, nothing happens
*/
pointer renew_array(pointer,size_t); // new objects initilized with default constructor
pointer renew_array_copy(pointer,size_t,const_pointer); // new objets copied from const_pointer
pointer renew_array_ctor(pointer,size_t,constructor,...); // new objects initialized using constructor

/*
#define renew(P,N) renew_array(P,N)
#define renew_copy(P,N,CP) renew_array_copy(P,N,CP)
#define renew_ctor(P,N,CTOR,...) renew_array_ctor(P,N,CTOR,__VA_ARGS__)
*/
#define get_memory_header(ptr) ( ptr ? ((memory_header_t*)((char*)(ptr) - offsetof(memory_header_t,ptr_))) : NULL)
#define get_type_info(ptr) ( ptr ? (get_memory_header(ptr)->type_info_) : NULL)
#define get_n_elem(ptr) ( ptr ? (get_memory_header(ptr)->n_elem_) : 0 )
default_constructor get_default_ctor(const type_info_t*);
bool has_destructor(const type_info_t*);
copy_constructor get_copy_ctor(const type_info_t*);
assignment get_assignment(const type_info_t*);
less_than_compare get_lt_cmp(const type_info_t*);
to_stream get_to_stream(const type_info_t*);
from_stream get_from_stream(const type_info_t*);

/*
	Deletes an array of objects by calling destructor if defined
	In YAOOC, all allocations are treated as an array so either "delete" or "delete_array" can be used
  Note: Garbage collector will call destructor if user does not explicitly call it.
*/
#define delete(P) delete_array(P)
void delete_array(pointer);

/*
	Placement delete.
  Note: Static objects are not subject to garbage collection so user MUST call deletep if resources
  other than memory have to be deleted.
*/
#define deletep(P,T) __deletep_array(P,T ## _ti,1)
#define deletep_array(P,T,N) __deletep_array(P,T ## _ti,N)
void __deletep_array(pointer,const type_info_t*,size_t);

void __delete_list(pointer,...);
#define DELETE(p,...) __delete_list(p, ## __VA_ARGS__ , NULL)
#define delete_list(p,...) __delete_list(p, ## __VA_ARGS__ , NULL)
/*
  Calls a contructor.  Meant to be used in contructors other than default or copy constructor.
*/
void call_constructor(pointer,constructor,...);

/*
  Calls the specified class method.
*/
#define __M(ptr,method,...) (ptr)->class_table_->method(ptr, ## __VA_ARGS__)
#define M(ptr,...) __M(ptr, __VA_ARGS__)


pointer __assign_static(pointer,const_pointer,const type_info_t*);
#define assign_static(P,CP,T)  __assign_static(P,CP,T ## _ti)
#define assign(DST,SRC) __assign_static(DST,SRC,get_type_info(SRC))

bool op_eq(const_pointer,const_pointer);
bool op_ne(const_pointer,const_pointer);
bool op_gt(const_pointer,const_pointer);
bool op_ge(const_pointer,const_pointer);
bool op_lt(const_pointer,const_pointer);
bool op_le(const_pointer,const_pointer);

bool __op_eq_static(const_pointer,const_pointer,const type_info_t*);
bool __op_ne_static(const_pointer,const_pointer,const type_info_t*);
bool __op_gt_static(const_pointer,const_pointer,const type_info_t*);
bool __op_ge_static(const_pointer,const_pointer,const type_info_t*);
bool __op_lt_static(const_pointer,const_pointer,const type_info_t*);
bool __op_le_static(const_pointer,const_pointer,const type_info_t*);

#define op_eq_static(P,CP,T) __op_eq_static(P,CP,T ## _ti)
#define op_ne_static(P,CP,T) __op_ne_static(P,CP,T ## _ti)
#define op_gt_static(P,CP,T) __op_gt_static(P,CP,T ## _ti)
#define op_ge_static(P,CP,T) __op_ge_static(P,CP,T ## _ti)
#define op_lt_static(P,CP,T) __op_lt_static(P,CP,T ## _ti)
#define op_le_static(P,CP,T) __op_le_static(P,CP,T ## _ti)

char* yaooc_strdup(const char*);
char* yaooc_upcase(const char*);
char* yaooc_downcase(const char*);

#endif
