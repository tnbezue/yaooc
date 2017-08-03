#ifndef __MEMORY_INCLUDED__
#define __MEMORY_INCLUDED__

#include <yaooc/object.h>

class_table(yaooc_unique_ptr)
{
  yaooc_object_class_members_t;
  pointer (*get)(pointer);
  const_pointer(*cget)(const_pointer);
  void (*set)(pointer,pointer);
  pointer (*release)(pointer);
};

class_instance(yaooc_unique_ptr)
{
  pointer ptr_;
};

class(yaooc_unique_ptr);

void yaooc_unique_ptr_default_ctor(pointer);
void yaooc_unique_ptr_dtor(pointer);
void yaooc_unique_ptr_copy_ctor(pointer,const_pointer);
void yaooc_unique_ptr_assign(pointer,const_pointer);
bool yaooc_unique_ptr_less_than_compare(const_pointer,const_pointer);

ISA_DEFINITION(yaooc_unique_ptr,yaooc_object)
void yaooc_unique_ptr_swap(pointer,pointer);
pointer yaooc_unique_ptr_get(pointer);
void yaooc_unique_ptr_set(pointer,pointer);
pointer yaooc_unique_ptr_release(pointer);
void yaooc_unique_ptr_ctor_ptr(pointer,va_list);

#define UNIQUE_PTR_DEFINITION(T) \
class_table(T ## _unique_ptr) \
{ \
  yaooc_object_class_members_t; \
  T ## _pointer (*get)(pointer); \
  T ## _const_pointer (*cget)(const_pointer); \
  void (*set)(pointer,pointer); \
  T ## _pointer (*release)(pointer); \
}; \
class_instance(T ## _unique_ptr) \
{ \
  yaooc_unique_ptr_instance_members_t; \
}; \
class(T ## _unique_ptr); \
ISA_DEFINITION(T ## _unique_ptr,yaooc_unique_ptr) \
void T ## _unique_ptr_ctor_ptr(pointer,va_list);

#define UNIQUE_PTR_IMPLEMENTATION(T) \
ISA_IMPLEMENTATION(T ## _unique_ptr,yaooc_unique_ptr) \
void T ## _unique_ptr_ctor_ptr(pointer p,va_list args) \
{ call_constructor(p,yaooc_unique_ptr_ctor_ptr,va_arg(args,pointer)); } \
T ## _unique_ptr_class_members_t T ## _unique_ptr_class_members = \
{ \
  { \
    T ## _unique_ptr_isa, \
    T ## _unique_ptr_is_descendent, \
    yaooc_unique_ptr_swap \
  }, \
  (T ## _pointer (*)(pointer))yaooc_unique_ptr_get, \
  (T ## _const_pointer (*)(const_pointer))yaooc_unique_ptr_get, \
  yaooc_unique_ptr_set, \
  (T ## _pointer (*)(pointer))yaooc_unique_ptr_release \
}; \
DEFINE_TYPE_INFO(T ## _unique_ptr,NULL,NULL,NULL,NULL,NULL, \
      &T ## _unique_ptr_class_members,yaooc_unique_ptr)


typedef struct yaooc_counter_s yaooc_counter_t;

class_table(yaooc_shared_ptr)
{
  yaooc_object_class_members_t;
	pointer (*get)(pointer);
  const_pointer (*cget)(const_pointer);
	bool 	(*unique)(const_pointer);
	void	(*release)(pointer);
  void (*reset)(pointer,pointer);
  unsigned int (*count)(const_pointer);
};

class_instance(yaooc_shared_ptr)
{
  yaooc_counter_t* counter_;
};
class(yaooc_shared_ptr);
ISA_DEFINITION(yaooc_shared_ptr,yaooc_object)

/* type info requirements */
void yaooc_shared_ptr_default_ctor(pointer);
void yaooc_shared_ptr_dtor(pointer);
void yaooc_shared_ptr_copy_ctor(pointer dst,const_pointer src);
void yaooc_shared_ptr_assign(pointer dst,const_pointer src);
bool yaooc_shared_ptr_less_than_compare(const_pointer,const_pointer);

/* constructors */
void yaooc_shared_ptr_ctor_ptr(pointer,va_list); // shared_ptr(void* ptr)

// class methods
void yaooc_shared_ptr_acquire(pointer,yaooc_counter_t*);
void yaooc_shared_ptr_release(pointer p);
void yaooc_shared_ptr_reset(pointer,pointer);
void* yaooc_shared_ptr_get(pointer this);
bool yaooc_shared_ptr_unique(const_pointer this);
void yaooc_shared_ptr_swap(pointer,pointer);
unsigned int yaooc_shared_ptr_count(const_pointer);

/*
  The following template implements same as above.  The values of get (and cget) are
  of the correct pointer type.
*/
#define SHARED_PTR_DEFINITION(T) \
class_table(T ## _shared_ptr) \
{ \
  yaooc_object_class_members_t;\
	T ## _t* (*get)(pointer); \
	const T ## _t* (*cget)(const_pointer); \
	bool 	(*unique)(const_pointer); \
	void	(*release)(pointer); \
  void  (*reset)(pointer,pointer); \
  unsigned int (*count)(const_pointer); \
}; \
class_instance(T ## _shared_ptr) { \
	yaooc_counter_t* counter_; \
}; \
class(T ## _shared_ptr); \
void T ## _shared_ptr_ctor_ptr(pointer this,va_list args); \
ISA_DEFINITION(T ## _shared_ptr,yaooc_shared_ptr)

#define SHARED_PTR_IMPLEMENTATION(T) \
void T ## _shared_ptr_ctor_ptr(pointer this,va_list args) \
	{ call_constructor(this,yaooc_shared_ptr_ctor_ptr,va_arg(args,pointer)); } \
ISA_IMPLEMENTATION(T ## _shared_ptr,yaooc_shared_ptr) \
T ## _shared_ptr_class_members_t T ## _shared_ptr_class_members = \
{ \
  { \
    T ## _shared_ptr_isa, \
    T ## _shared_ptr_is_descendent, \
    yaooc_shared_ptr_swap \
  }, \
	(T ## _t* (*)(pointer)) yaooc_shared_ptr_get, \
	(const T ## _t* (*)(const_pointer)) yaooc_shared_ptr_get, \
	yaooc_shared_ptr_unique, \
	yaooc_shared_ptr_release, \
  yaooc_shared_ptr_reset, \
  yaooc_shared_ptr_count \
};\
DEFINE_TYPE_INFO(T ## _shared_ptr,yaooc_shared_ptr_default_ctor,NULL,NULL,NULL,NULL, \
        &T ## _shared_ptr_class_members,yaooc_shared_ptr)

#endif
