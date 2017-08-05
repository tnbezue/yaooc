#ifndef __NEW_INCLUDED__
#define __NEW_INCLUDED__

#include <stdarg.h>
#include <stddef.h>
#include <stdlib.h>
#include <inttypes.h>
#ifdef __YAOOC_USE_GC__
#include <gc.h>
#define MALLOC(obj) GC_MALLOC_ATOMIC(obj)
#define REALLOC(obj,n) GC_REALLOC(obj,n)
#define FREE(obj)
#define STRDUP(str) GC_strdup(str)
#else
#define MALLOC(obj) malloc(obj)
#define REALLOC(obj,n) realloc(obj,n)
#define FREE(obj) free(obj)
#define STRDUP(str) strdup(str)
#define GC_INIT()
#endif

#include <yaooc/yaooc_debug.h>

/* bool type */
#ifndef __bool_true_false_are_defined
#define __bool_true_false_are_defined	1
typedef unsigned char bool;
#define false 0
#define true 1
#endif

typedef unsigned int yaooc_size_type;
/*
	Generic pointer.  Objects should define a more appropriate pointer.
	For example, yaooc_string class uses yaooc_string_pointer and yaooc_string_const_pointer to point to
	string objects.
*/
typedef void* pointer;
typedef const void* const_pointer;
typedef pointer pointer_t;
/*
	Generic iterator
*/
/*
	A place holder.  An appropriate iterator needs to be defined
	For example, yaooc_string class uses:
		typedef char* yaooc_string_iterator;
		typedef const char* yaooc_string_const_iterator;
*/
typedef void* iterator;
typedef const void* const_iterator;

/*
	The yaooc_iterator to be used privately by yaooc classes/methods.
	Some compilers don't allow adding integer values to above iterators (void*).
	The below "iterators" are used where addition to iterators is needed.
*/
typedef char* const yaooc_private_pointer;
typedef const char* const yaooc_private_const_pointer;
typedef char* yaooc_private_iterator;
typedef const char* yaooc_private_const_iterator;

/*
	C++ requires an object to have default constructor, destructor, copy constructor,
	operator =.  C++ automatically generates if not present.
  YAOOC requires the same.  If not defined, default actions (describe later) will be executed
  Operator < required if object will be used in a unique or sorted container.
*/
/*
	Default constructor.  Same as C++.  Called after memory for object has been allocated.  Pointer argument
	is pointer to allocated memory.  If default constructor not defined, memory allocated is left unaltered.
  No actions performed.
*/
typedef void(*default_constructor)(pointer);
/*
	Destructor.  Same as C++.  Called before memory for object is released.  Pointer argument is pointer
	to object to be deleted.
  If destructor not defined, then no actions will be peformed.
  As in C++, the parent class destructor is called; then grandparent; etc until base class is reached.
  Note: The destructor is registered with the garbage collector and is automatically called when
  object is collected.  User can explicitly use destory to invoke the destructor.
*/
typedef void(*destructor)(pointer);

/*
	In C++, if copy constructor not defined, the parent copy constructor is used.  If parent copy constructor
	not defined, the parent's parent is used (and so on).  If no copy constructor found, member by member assignment
	is performed
	For YAOOC, If copy constructor is not defined (NULL), the parent, then parent parent (and so on) until a
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
  Calls a contructor.  Meant to be used in contructors to call parent constructor. However, it
  can be used anywhere
*/
void call_constructor(pointer,constructor,...);

/*
	For objects with class tables, it must be first in list.
*/
typedef struct {
} class_table_t;
typedef struct {
	const class_table_t* class_table;
} base_object_t;
#define copy_class_table(p,ct) ((base_object_t*)(p))->class_table=ct

/*
	Objects allocated by new must define a type_info_t structure.
  type_size must be defined and not zero, others may be NULL
*/
typedef struct type_info_s type_info_t;
struct type_info_s {
	yaooc_size_type type_size_;											// object size
	default_constructor  default_ctor_;
	destructor dtor_;
	copy_constructor copy_ctor_;
	assignment assign_;
	less_than_compare less_than_compare_;
	const class_table_t* class_table_;  // pointer to class table
	const type_info_t *parent_;   // parent type info
};

/*
	New

	C++ allows new to be overloaded in various ways.  In YAOOC, must define separate functions
	for each case.
*/
/*
	Basic new -- arguments are pointer to type info structure and number of elements to allocate.
	The default constructor is used to initilize objects.
*/
#define new(T) real_new_array(T ## _ti,1)
#define new_array(T,N) real_new_array(T ## _ti,N)
pointer real_new_array(const type_info_t*,yaooc_size_type);
/*
	Placement new -- arguments are pointer to preallocated memory, pointer to type info structure, and number
	of elements.  The default constructor is used to initialize objects.
*/
#define newp(P,T) real_newp_array(P,T ## _ti,1)
#define newp_array(P,T,N) real_newp_array(P,T ## _ti,N)
pointer real_newp_array(pointer,const type_info_t*,yaooc_size_type);

/*
	Copy new -- arguments are const pointer to object to copy and number of elements.
	Each element is a duplicate of the object to copy.
*/
#define new_copy(CP) real_new_array_copy(CP,1)
#define new_array_copy(CP,N) real_new_array_copy(CP,N)
pointer real_new_array_copy(const_pointer src,yaooc_size_type);

/*
	Copy placement new (placement version of above)-- arguments are pointer to preallocated memory, const pointer
	to object to copy, and number of elements.
*/
#define newp_copy(P,CP) real_newp_array_copy(P,CP,N)
#define newp_array_copy(P,CP,N) real_newp_array_copy(P,CP,N)
pointer real_newp_array_copy(pointer,const_pointer,yaooc_size_type);

/*
	Copy static new -- arguments are type info pointer, const pointer to object to be copied, and number of
	elements.

	Note:  Above copy new's dynamically determine the type being copied.
  However, there are times when this can not be used (i.e., when object is in a container).  Therefore,
	the type info has to be supplied.
*/
#define new_copy_static(T,CP)  		real_new_array_copy_static(T ## _ti,CP,1)
#define new_array_copy_static(T,CP,N) 		real_new_array_copy_static(T ## _ti,CP,N)
pointer real_new_array_copy_static(const type_info_t*,const_pointer,yaooc_size_type);

/*
	Placement version of abover
*/
#define newp_copy_static(P,T,CP) real_newp_array_copy_static(P,T ## _ti,CP,1)
#define newp_array_copy_static(P,T,CP,N) real_newp_array_copy_static(P,T ## _ti,CP,N)
pointer real_newp_array_copy_static(pointer,const type_info_t*,const_pointer,yaooc_size_type);

/*
	New ctor -- arguments are type info pointer, number of elements, constructor, and arguments to constructor
*/
#define new_ctor(T,CON,...)  				real_new_array_ctor(T ## _ti,1,CON, __VA_ARGS__)
#define new_array_ctor(T,N,CON,...)  				real_new_array_ctor(T ## _ti,N,CON, __VA_ARGS__)
pointer real_new_array_ctor(const type_info_t*,yaooc_size_type, constructor,...);

/*
	new ctor placement.  Placement version of above
*/
#define newp_ctor(P,T,CON,...)  		real_newp_array_ctor(P,T ## _ti,1,CON,## __VA_ARGS__)
#define newp_array_ctor(P,T,N,CON,...)  		real_newp_array_ctor(P,T ## _ti,N,CON,## __VA_ARGS__)
pointer real_newp_array_ctor(pointer,const type_info_t*,yaooc_size_type,constructor,...);

/*
	YAOOC extension.  "renew" is to "new" as "realloc" is to "malloc".

	If size specified if greater than current size, new objects are added.
	If size specified is less than current size, destructor is called for objects beyond new size
	If size is same, nothing happens
*/
pointer renew_array(pointer,yaooc_size_type); // new objects initilized with default constructor
pointer renew_array_copy(pointer,yaooc_size_type,const_pointer); // new objets copied from const_pointer
pointer renew_array_ctor(pointer,yaooc_size_type,constructor,...); // new objects initialized using constructor

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
#define deletep(P,T) real_deletep_array(P,T ## _ti,1)
#define deletep_array(P,T,N) real_deletep_array(P,T ## _ti,N)
void real_deletep_array(pointer,const type_info_t*,yaooc_size_type);

void delete_list(pointer,...);
#define DELETE(p,...) delete_list(p, ## __VA_ARGS__ , NULL)

/*
  Calls method for the specified object.
*/
#define REAL_M(ptr,method,...) (ptr)->class_table_->method(ptr, ## __VA_ARGS__)
#define M(ptr,...) REAL_M(ptr,__VA_ARGS__)

default_constructor get_default_ctor(const type_info_t* ti);
copy_constructor get_copy_ctor(const type_info_t* ti);
assignment get_assignment(const type_info_t* ti);
pointer assign(pointer dst,const_pointer src); // operator =
#define assign_static(P,CP,T)  real_assign_static(P,CP,T ## _ti)
pointer real_assign_static(pointer,const_pointer,const type_info_t*);

less_than_compare get_lt_cmp(const type_info_t*);
bool __lt_cmp__(const_pointer v1,const_pointer v2,less_than_compare lt_cmp_func);

bool op_eq(const_pointer,const_pointer);
bool op_ne(const_pointer,const_pointer);
bool op_gt(const_pointer,const_pointer);
bool op_ge(const_pointer,const_pointer);
bool op_lt(const_pointer,const_pointer);
bool op_le(const_pointer,const_pointer);

bool op_eq_static(const_pointer,const_pointer,const type_info_t*);
bool op_ne_static(const_pointer,const_pointer,const type_info_t*);
bool op_gt_static(const_pointer,const_pointer,const type_info_t*);
bool op_ge_static(const_pointer,const_pointer,const type_info_t*);
bool op_lt_static(const_pointer,const_pointer,const type_info_t*);
bool op_le_static(const_pointer,const_pointer,const type_info_t*);

/*
	Make it look more like C++
*/
#define class_forward(name) \
typedef struct name ## _s name ## _t; \
typedef struct name ## _s * name ## _pointer; \
typedef const struct name ## _s * name ## _const_pointer; \
extern type_info_t __ ## name ## _ti; \
extern const type_info_t* const name ## _ti;

#define class_table(name) \
typedef struct name ## _s name ## _t; \
typedef struct name ## _s * name ## _pointer; \
typedef const struct name ## _s * name ## _const_pointer; \
typedef struct name ## _class_members_s name ## _class_members_t; \
struct name ## _class_members_s

#define class_instance(name) \
typedef struct name ## _s name ## _t; \
typedef struct name ## _s * name ## _pointer; \
typedef const struct name ## _s * name ## _const_pointer; \
typedef struct name ## _instance_members_s name ## _instance_members_t; \
struct name ## _instance_members_s

#define class(name) \
typedef struct name ## _s name ## _t; \
typedef struct name ## _s * name ## _pointer; \
typedef const struct name ## _s * name ## _const_pointer; \
typedef struct name ## _class_members_s name ## _class_members_t; \
typedef struct name ## _instance_members_s name ## _instance_members_t; \
extern name ## _class_members_t name ## _class_members; \
extern type_info_t __ ## name ## _ti; \
extern const type_info_t* const name ## _ti; \
struct name ## _s \
{ \
	name ## _class_members_t* class_table_; \
	name ## _instance_members_t; \
}

#define class_(name) \
typedef struct name ## _s name ## _t; \
typedef struct name ## _s * name ## _pointer; \
typedef const struct name ## _s * name ## _const_pointer; \
extern type_info_t __ ## name ## _ti; \
extern const type_info_t* const name ## _ti; \
struct name ## _s

#define ALIAS_DEFINITION(NEW_TYPE,EXISTING_TYPE) \
typedef EXISTING_TYPE ## _t NEW_TYPE ## _t; \
typedef EXISTING_TYPE ## _pointer NEW_TYPE ## _pointer; \
typedef EXISTING_TYPE ## _const_pointer NEW_TYPE ## _const_pointer; \
extern const type_info_t* const NEW_TYPE ## _ti;

#define ALIAS_IMPLEMENTATION(NEW_TYPE,EXISTING_TYPE) \
const type_info_t* const NEW_TYPE ## _ti=&__ ## EXISTING_TYPE ## _ti;

#define ALIAS(NEW_TYPE,EXISTING_TYPE) \
ALIAS_DEFINITION(NEW_TYPE,EXISTING_TYPE) \
ALIAS_IMPLEMENTATION(NEW_TYPE,EXISTING_TYPE)

#define __NULL_ti (*(char*)NULL)

#define DEFINE_TYPE_INFO(T,DEF_CTOR,DTOR,COPY_CTOR,ASSIGN,LT_COMPARE,CLASS_TABLE,PARENT) \
type_info_t __ ## T ## _ti ={ \
	sizeof(T ## _t),\
	DEF_CTOR, \
	DTOR, \
	COPY_CTOR, \
  ASSIGN, \
	LT_COMPARE, \
	(const class_table_t*)CLASS_TABLE, \
	(const type_info_t*)&__ ## PARENT ## _ti \
}; \
const type_info_t* const T ## _ti = &__ ## T ## _ti;

/*
	Define type info for object without contructor, destructor, assign, copy ctor, or lt_compare
*/
#define SIMPLE_TYPE_INFO(T) DEFINE_TYPE_INFO(T,NULL,NULL,NULL,NULL,NULL,NULL,NULL)

/*
	Define type info using standard naming convention for object with
	contructor, destructor,  copy ctor, less_than_compare.  No class table and no parent.
*/
#define STANDARD_TYPE_INFO(T) \
	DEFINE_TYPE_INFO(T,T ## _default_ctor,T ## _dtor,T ## _copy_ctor,T ## _assign,T ## _less_than_compare,NULL,NULL)

/*
	Define type info using standard naming convention for object with
	contructor, destructor,  copy ctor, lt_compare, and parent.  No class table.
*/
#define STANDARD_TYPE_INFO_P(T,P) \
	DEFINE_TYPE_INFO(T,T ## _default_ctor,T ## _dtor,T ## _copy_ctor,T ## _assign,T ## _less_than_compare,NULL,P)

/*
	Define type info using standard naming convention for object with
	contructor, destructor, copy ctor, lt_compare, and class table. No parent
*/
#define STANDARD_TYPE_INFO_CT(T) \
	DEFINE_TYPE_INFO(T,T ## _default_ctor,T ## _dtor,T ## _copy_ctor,T ## _assign,T ## _less_than_compare,& T ## _class_members,NULL)

/*
	Define type info using standard naming convention for object with
	contructor, destructor, assign, copy ctor, lt_compare, class table, and parent.
*/
#define STANDARD_TYPE_INFO_CT_P(T,P) \
	DEFINE_TYPE_INFO(T,T ## _default_ctor,T ## _dtor,T ## _copy_ctor,T ## _assign,T ## _less_than_compare,&T ## _class_members,P)

/*
  Utility functions
*/

#define SWAP(T,x,y) { T __temp__=x; x=y; y=__temp__; }

void swap_object(void *,void*,yaooc_size_type); /* Careful using this */
char* yaooc_strdup(const char*);

/*
  If object does not have a destructor (or will not have to use the destructor if one exists)
  then it can be created on the stack and not have to call delete
*/
#define STACK_PTR(T,P) char P ## _stack[sizeof(T ## _t)]; T ## _pointer P=real_newp_array(P ## _stack,T ## _ti,1)
#define STACK_PTR_CTOR(T,P,CTOR,...) char P ## _stack[sizeof(T ## _t)]; T ## _pointer P=real_newp_array_ctor(P ## _stack,T ## _ti,1,CTOR,## __VA_ARGS__)

/*
	type info for POD types
*/
#define POD_TYPE_INFO_DEFINITION(T) \
typedef T ## _t* T ## _pointer; \
typedef const T ## _t* T ## _const_pointer; \
extern const type_info_t* const T ## _ti;

/*
  Typedefs so that POD types adhere to naming convention
*/
typedef char char_t;
typedef unsigned char uchar;
typedef uchar uchar_t;
typedef short int short_t;
typedef unsigned short int ushort_t;
typedef int int_t;
typedef unsigned int uint_t;
typedef unsigned long ulong_t;
typedef unsigned long long ulong_long_t;
typedef long int long_t;
typedef long long int long_long_t;
typedef double double_t;
extern const type_info_t* const char_ti;
extern const type_info_t* const int8_ti;
extern const type_info_t* const uchar_ti;
extern const type_info_t* const uint8_ti;
extern const type_info_t* const short_ti;
extern const type_info_t* const int16_ti;
extern const type_info_t* const ushort_ti;
extern const type_info_t* const uint16_ti;
extern const type_info_t* const int_ti;
extern const type_info_t* const int32_ti;
extern const type_info_t* const uint_ti;
extern const type_info_t* const uint32_ti;
extern const type_info_t* const long_ti;
extern const type_info_t* const ulong_ti;
extern const type_info_t* const long_long_ti;
extern const type_info_t* const ulong_long_ti;
extern const type_info_t* const int64_ti;
extern const type_info_t* const uint64_ti;
extern const type_info_t* const double_ti;

#endif
