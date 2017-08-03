#ifndef __YAOOC_OBJECT_INCLUDED__
#define __YAOOC_OBJECT_INCLUDED__

#include <yaooc/new.h>
#include <stdio.h>
#include <stddef.h>

class_table(yaooc_object)
{
	const char*(*isa)(const_pointer);
	bool(*is_descendent)(const_pointer,const char*);
	void (*swap)(pointer,pointer);
};

class_instance(yaooc_object)
{
};

class(yaooc_object);

#define YAOOC_OBJECT_CLASS_MEMBERS \
	yaooc_object_isa, \
	yaooc_object_is_descendent, \
	yaooc_object_swap

void yaooc_object_default_ctor(pointer p);
void yaooc_object_dtor(pointer p);
void yaooc_object_assign(pointer d,const_pointer s);
void yaooc_object_copy_ctor(pointer d,const_pointer s);

const char* yaooc_object_isa(const_pointer);
bool yaooc_object_is_descendent(const_pointer,const char*);
void yaooc_object_swap(pointer,pointer);


/*
  The ISA macro will define the class isa and is_decendant methods
*/
#define ISA_DEFINITION(C,P) \
const char* C ## _isa(const_pointer); \
bool  C ## _is_descendent(const_pointer,const char*);

#define ISA_IMPLEMENTATION(C,P) \
const char* C ## _isa(const_pointer p ) { return # C "_t" ; } \
bool  C ## _is_descendent(const_pointer p,const char* s) \
{ return strcmp(# C "_t",s) == 0 || P ## _is_descendent(p,s); }

#endif
