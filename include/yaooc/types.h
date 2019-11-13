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
#include <inttypes.h>
#include <sys/types.h>
#include <stdint.h>

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
	The below "iterators" are used where iterators involve mathmatical operations.
*/
typedef char* const yaooc_private_pointer;
typedef const char* const yaooc_private_const_pointer;
typedef char* yaooc_private_iterator;
typedef const char* yaooc_private_const_iterator;

/*
	Although yaooc_ifstream_pointer are yaooc_istringstream_pointer decendent from yaooc_istream_pointer
	is passed as an argument, this will generate waring messgage.  Therefore, a generic stream pointer (void*) is used.
	Using the stream pointers defined below serves as a reminder a stream is expected as a argument.
*/
typedef pointer ostream_pointer;
typedef pointer istream_pointer;
typedef const_pointer ostream_const_pointer;
typedef const_pointer istream_const_pointer;

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
	Return < 0 for less than, = 0 for equal, or > 0 for greater than
*/
typedef int(*rich_compare)(const_pointer,const_pointer);

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
	For objects with class tables, it must be first in structure.
*/
typedef struct class_table_s class_table_t;
struct class_table_s {
  const class_table_t* class_table;
};
typedef class_table_t* class_table_pointer;
typedef const class_table_t* class_table_const_pointer;
typedef struct {
	class_table_t;
} base_object_t;
#define copy_class_table(p,ct) ((base_object_t*)(p))->class_table=ct

/*
	Objects allocated by new must define a type_info_t structure.
  The minimum requirement is the type size (min_type_info)

	The pod_type_info_s structure  is for Plain Old Data (POD).
    -- Has rich compare
    -- Has to/from stream
    -- Does not have a parent
    -- Used for POD types (int, double, etc) and structures made of POD types

	The type_info_s structure is used for full class definitions.
    -- pod_type pluse
    -- Can have constructor
    -- Can have destructor
    -- Can have copy constructor
    -- Can have assignment
    -- Can have parent
*/
#ifdef _WIN64
#define __WORDSIZE 64
#else
#ifdef _WIN32
#define __WORDSIZE 32
#endif
#endif
typedef struct min_type_info_s min_type_info_t;
struct min_type_info_s {
#if __WORDSIZE == 64
  uint16_t min_flag_; // Indicates type info structure contains only size
  uint16_t pod_flag_; // Indicates type info structure contains POD
	uint32_t type_size_; // object size
#else
  uint8_t min_flag_; // Indicates type info structure contains only size
  uint8_t pod_flag_; // Indicates type info structure contains POD
	uint16_t type_size_; // object size
#endif
};

typedef struct pod_type_info_s pod_type_info_t;
struct pod_type_info_s {
  min_type_info_t;
	rich_compare rich_compare_;
	to_stream to_stream_;
	from_stream from_stream_;
};

/*
	Pod types will have the MSB set in the size entry.
*/
#define is_min_type(ti) (((min_type_info_t*)ti)->min_flag_ == 1)
#define is_pod_type(ti) (((min_type_info_t*)ti)->pod_flag_ == 1)
#define is_min_pod_type(ti) (is_min_type(ti) || is_pod_type(ti))
/*
	never directly use type info size entry, use yaooc_sizeof to get correct size
*/
#define yaooc_sizeof(ti) ((size_t)(((min_type_info_t*)ti)->type_size_))
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
	char ptr_[1];
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
POD_DEFINITION(unsigned char,uchar)
POD_DEFINITION(short,short)
POD_DEFINITION(unsigned short,ushort)
POD_DEFINITION(int,int)
POD_DEFINITION(unsigned int,uint)
#if __WORDSIZE == 64
POD_DEFINITION(long,long)
POD_DEFINITION(unsigned long,ulong)
#else
POD_DEFINITION(long long,long)
POD_DEFINITION(unsigned long long,ulong)
#endif
typedef double * double_pointer;
typedef const double* double_const_pointer;
void double_to_stream(const_pointer,pointer);
void double_from_stream(pointer,pointer);
extern const pod_type_info_t __double_ti;
extern const type_info_t* const double_ti;
//POD_DEFINITION(double,double)
//POD_DEFINITION(pointer,pointer)
//POD_DEFINITION(const_pointer,const_pointer)
extern const pod_type_info_t __pointer_ti;
extern const type_info_t* const pointer_ti;

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

#define PRISHORT PRId16
#define PRIUSHORT PRIu16
#define PRIINT PRId32
#define PRIUINT PRIu32
#if __WORDSIZE == 64
#define PRILONG PRId64
#define PRIULONG PRIu64
#else
#define PRILONG PRId32
#define PRIULONG PRIu32
#endif
#define PRILONGLONG PRId64
#define PRIULONGLONG PRIu64
#endif
