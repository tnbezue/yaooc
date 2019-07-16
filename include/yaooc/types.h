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

#ifndef __YAOOC_TYPES_INCLUDED__
#define __YAOOC_TYPES_INCLUDED__

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include <sys/types.h>

/* bool type */
#ifndef __bool_true_false_are_defined
#define __bool_true_false_are_defined	1
typedef unsigned char bool;
#define false 0
#define true 1
#endif

/*
	Generic pointer.
  The pointer type is used to point to a single object.  Objects should define a more appropriate pointer.
	For example, yaooc_string class uses yaooc_string_pointer and yaooc_string_const_pointer to point to
	string objects.
*/
typedef void* const pointer;
typedef const void* const const_pointer;

/*
	Generic iterator. Objects should define a more appropriate iterator.
	For example, yaooc_string class uses:
		typedef char* yaooc_string_iterator;
		typedef const char* yaooc_string_const_iterator;
*/
typedef void* iterator;
typedef const void* const_iterator;

/*
	The yaooc_iterator to be used privately by yaooc classes/methods.
	Some compilers don't allow adding integer values to above iterators (void*).
	The below "iterators" are used where iterators are involved mathmatical operations.
*/
typedef char* const yaooc_private_pointer;
typedef const char* const yaooc_private_const_pointer;
typedef char* yaooc_private_iterator;
typedef const char* yaooc_private_const_iterator;

/*
	Default constructor.  Same as C++.  Called after memory for object has been allocated.  Pointer argument
	is pointer to allocated memory.  If default constructor not defined (NULL),
  the defuault constructor of the parent is used.  If the parent default
  constructor is not defined, then grandparent, and so on.
  If no default constructor found, then memory allocated is left unaltered.
  No actions performed.
*/
typedef void(*default_constructor)(pointer);

/*
	Destructor.  Same as C++.  Called before memory for object is released.  Pointer argument is pointer
	to object to be deleted.
  If destructor not defined, then no actions will be peformed.
  As in C++, the parent class destructor is called; then grandparent; etc until base class is reached.
  Note: The destructor is registered with the garbage collector and is automatically called when
  object is collected.  User can explicitly use delete to invoke the destructor.
*/
typedef void(*destructor)(pointer);

/*
	In C++, if copy constructor not defined, the parent copy constructor is used.  If parent copy constructor
	not defined, the parent's parent is used (and so on).  If no copy constructor found, member by member assignment
	is performed
	For YAOOC, If copy constructor is not defined (NULL), the parent, then grandparent (and so on) until a
	copy constructor found.  If none found, the object is copied to new object using memcpy. For POD types and
  classes composed of POD types, using an undefined copy constructor is sufficient (prehaps perfered).
  For non-POD types, using an undefined copy constructor may have unexpected consequences.
*/
typedef void(*copy_constructor)(pointer,const_pointer);

/*
	Assignment operator has same restrictions as copy constructor.
*/
typedef void(*assignment)(pointer,const_pointer);

/*
	Less than comparison function required if object is used in a container.  If not defined,
  comparisons will return false -- thus all object of this type will be considered equal.
*/
typedef bool(*less_than_compare)(const_pointer,const_pointer);

/*
	Any number of non default constructors may be defined.  Arguments to these constructors are a pointer
	to the newly created object and a va_list.  See yaooc_string for examples.
*/
typedef void(*constructor)(pointer,va_list);

/*
	How to write to stream
*/
typedef void (*to_stream)(const_pointer,pointer);

/*
	How to read from a stream
*/
typedef void (*from_stream)(pointer,pointer);

/*
	For objects with class tables, it must be first in list.
*/
typedef struct {
} class_table_t;
typedef class_table_t* class_table_pointer;
typedef const class_table_t* class_table_const_pointer;
typedef struct {
	const class_table_t* class_table;
} base_object_t;
#define copy_class_table(p,ct) ((base_object_t*)(p))->class_table=ct

/*
	Objects allocated by new must define a type_info_t structure.
  type_size must be defined and not zero, others may be NULL

	The first structure (pod_type_info_s) is for Plain Old Data (POD).
		-- Does not have a default constructor nor destructor
		-- copy and assign is done by coping (memcpy)
		-- No class table
		-- No parent

	The second structure is for non POD types.
*/
typedef struct pod_type_info_s pod_type_info_t;
struct pod_type_info_s {
	size_t type_size_; // object size
	less_than_compare less_than_compare_;
	to_stream to_stream_;
	from_stream from_stream_;
};

/*
	Pod types will have the MSB set in the size entry.
*/
#define POD_FLAG (((__SIZE_TYPE__)1) << ((sizeof(__SIZE_TYPE__)*8)-1))
#define is_pod(ti) ((((pod_type_info_t*)ti)->type_size_) & POD_FLAG)
/*
	never directly use type info size entry, use yaooc_sizeof to get correct size
*/
#define yaooc_sizeof(ti) ((((pod_type_info_t*)ti)->type_size_) & ~POD_FLAG)
typedef struct type_info_s type_info_t;
struct type_info_s {
	pod_type_info_t;
	default_constructor  default_ctor_;
	destructor dtor_;
	copy_constructor copy_ctor_;
	assignment assign_;
	const class_table_t* class_table_;  // pointer to class table
	const type_info_t *parent_;   // pointer to parent type info
};

typedef struct memory_header_s memory_header_t;
struct memory_header_s {
	const type_info_t* type_info_;
	size_t	n_elem_;			// number of elements allocated
	char ptr_[0];
};

/*
	For types that already use _t as postfix (i.e. int32_t)
*/

#define PARTIAL_ALIAS_DEFINITION(NEW_TYPE,EXISTING_TYPE) \
typedef EXISTING_TYPE ## _pointer NEW_TYPE ## _pointer; \
typedef EXISTING_TYPE ## _const_pointer NEW_TYPE ## _const_pointer; \
extern const type_info_t* const NEW_TYPE ## _ti;

#define ALIAS_DEFINITION(NEW_TYPE,EXISTING_TYPE) \
typedef EXISTING_TYPE ## _t NEW_TYPE ## _t; \
PARTIAL_ALIAS_DEFINITION(NEW_TYPE,EXISTING_TYPE)

#define ALIAS_IMPLEMENTATION(NEW_TYPE,EXISTING_TYPE) \
const type_info_t* const NEW_TYPE ## _ti=&__ ## EXISTING_TYPE ## _ti;

#define ALIAS(NEW_TYPE,EXISTING_TYPE) \
ALIAS_DEFINITION(NEW_TYPE,EXISTING_TYPE) \
ALIAS_IMPLEMENTATION(NEW_TYPE,EXISTING_TYPE)


/*
  POD types
*/
#define POD_DEFINITION(T,N) \
typedef T N ## _t; \
typedef N ## _t* const N ## _pointer; \
typedef const N ## _t* const N ##_const_pointer; \
void N ## _to_stream(const_pointer,pointer); \
void N ## _from_stream(pointer,pointer); \
extern const pod_type_info_t __ ## N ## _ti; \
extern const type_info_t* const N ## _ti;

POD_DEFINITION(char,char)
POD_DEFINITION(unsigned char,uchar);
POD_DEFINITION(short,short);
POD_DEFINITION(unsigned short,ushort);
POD_DEFINITION(int,int)
POD_DEFINITION(unsigned int,uint)
POD_DEFINITION(long long,long);
POD_DEFINITION(unsigned long long,ulong);
POD_DEFINITION(double,double)
POD_DEFINITION(pointer,pointer)
POD_DEFINITION(const_pointer,const_pointer)
POD_DEFINITION(char*,yaooc_ccs)

/*
	type info for POD types
*/
#define POD_TYPE_INFO_DEFINITION(T) \
typedef T ## _t* T ## _pointer; \
typedef const T ## _t* T ## _const_pointer; \
extern const type_info_t* const T ## _ti;

typedef size_t* size_pointer;
typedef const size_t* size_const_pointer;
extern const type_info_t* const size_ti;
void size_to_stream(const_pointer,pointer);
void size_from_stream(pointer,pointer);

#endif
