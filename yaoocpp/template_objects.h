#ifndef __TEMPLATE_OBJECTS_INCLUDED__
#define __TEMPLATE_OBJECTS_INCLUDED__

#include <yaooc/vector.h>
#include <yaooc/string.h>
#include <yaooc/memory.h>

//SHARED_PTR_DEFINITION(yaooc_string)

/*
  Item defintion is base for all elements in definition file
*/
class_table(item_definition)
{
  yaooc_object_class_members_t;
  void (*virtual_dtor)(pointer);
  void (*virtual_copy_ctor)(pointer,const_pointer);
  void (*virtual_assign)(pointer,const_pointer);
  void (*print_to_header_class)(const_pointer,FILE* out);
  void (*print_to_header_prototype)(const_pointer,FILE* out);
  void (*print_to_header_define)(const_pointer,FILE* out);
  void (*print_to_source)(const_pointer,FILE* out);
  void(*dump)(const_pointer,FILE* out,int);
};

class_instance(item_definition)
{
};

class(item_definition);
ISA_DEFINITION(item_definition,yaooc_object)

void item_definition_default_ctor(pointer);
void item_definition_dtor(pointer);
void item_definition_copy_ctor(pointer,const_pointer);
void item_definition_assign(pointer,const_pointer);
/*void item_definition_print_to_header_class_table(const_pointer,FILE*);
void item_definition_print_to_header_instance(const_pointer,FILE*);
void item_definition_print_to_header_prototype(const_pointer,FILE*);
void item_definition_print_to_header_define(const_pointer,FILE*);
void item_definition_print_to_source(const_pointer,FILE*);
void item_definition_dump(const_pointer,FILE*,int);*/

#define ITEM_DEFINITION_CLASS_MEMBERS \
  { \
    item_definition_isa, \
    item_definition_is_descendent, \
    yaooc_object_swap \
  }, \
    NULL, \
    NULL, \
    NULL, \
    NULL, \
    NULL, \
    NULL, \
    NULL, \
    NULL

SHARED_PTR_DEFINITION(item_definition)
VECTOR_DEFINITION(item_definition_shared_ptr)

/*
  A variable, argument, or function type definition
*/
class_table(type_definition)
{
  item_definition_class_members_t;
  void (*set)(pointer,const char*);
};

class_instance(type_definition)
{
  yaooc_string_t type_string_;
};

class(type_definition);

ISA_DEFINITION(type_definition,item_definition)
void type_definition_default_ctor(pointer);
void type_definition_virtual_dtor(pointer);
void type_definition_virtual_copy_ctor(pointer,const_pointer);
void type_definition_virtual_assign(pointer,const_pointer);
void type_definition_print_to_header(const_pointer,FILE*);
/*void type_definition_print_to_header_instance(const_pointer,FILE*);
void type_definition_print_to_header_prototype(const_pointer,FILE*);
void type_definition_print_to_header_define(const_pointer,FILE*);*/
void type_definition_print_to_source(const_pointer,FILE*);
void type_definition_dump(const_pointer,FILE*,int);
void type_definition_set(pointer,const char*);

#define TYPE_DEFINITION_CLASS_MEMBERS \
  { \
    { \
      type_definition_isa, \
      type_definition_is_descendent, \
      yaooc_object_swap \
    }, \
      type_definition_virtual_dtor, \
      type_definition_virtual_copy_ctor, \
      type_definition_virtual_assign, \
      type_definition_print_to_header, \
      type_definition_print_to_header, \
      type_definition_print_to_header, \
      type_definition_print_to_source, \
      type_definition_dump \
  }, \
  type_definition_set

/*
  Arg definition
*/
class_table(arg_definition)
{
  item_definition_class_members_t;
  type_definition_const_pointer (*type)(const_pointer);
  void (*set)(pointer,const char*,const char*); /* type_definition_const_pointer,yaooc_string_shared_ptr_const_pointer */
};

class_instance(arg_definition)
{
  type_definition_pointer type_;
  yaooc_string_t name_;
};

class(arg_definition);
ISA_DEFINITION(arg_definition,item_definition)
void arg_definition_default_ctor(pointer);
void arg_definition_virtual_dtor(pointer);
void arg_definition_virtual_copy_ctor(pointer,const_pointer);
void arg_definition_virtual_assign(pointer,const_pointer);
void arg_definition_print_to_header_class(const_pointer,FILE*);
void arg_definition_print_to_header_prototype(const_pointer,FILE*);
void arg_definition_print_to_source(const_pointer,FILE*);
void arg_definition_dump(const_pointer,FILE*,int);
type_definition_const_pointer arg_definition_type(const_pointer);
void arg_definition_set(pointer,const char*,const char*);
void arg_definition_ctor_type_name(pointer,va_list);

#define ARG_DEFINITION_CLASS_MEMBERS \
  { \
    { \
      arg_definition_isa, \
      arg_definition_is_descendent, \
      yaooc_object_swap \
    }, \
    arg_definition_virtual_dtor, \
    arg_definition_virtual_copy_ctor, \
    arg_definition_virtual_assign, \
    arg_definition_print_to_header_class, \
    arg_definition_print_to_header_prototype, \
    NULL, /* Won't need in define */ \
    arg_definition_print_to_source, \
    arg_definition_dump \
  }, \
  arg_definition_type, \
  arg_definition_set


/*
  Variable definition -- decendent of argument.  Variable adds default value and printed different
  in header and source
*/
class_table(variable_definition)
{
  item_definition_class_members_t;
  void (*set)(pointer,const char*,const char*,const char*); /* type_definition_const_pointer,yaooc_string_shared_ptr_const_pointer */
};

class_instance(variable_definition)
{
  arg_definition_instance_members_t;
  yaooc_string_t default_value_;
};

class(variable_definition);
ISA_DEFINITION(variable_definition,arg_definition)
void variable_definition_default_ctor(pointer);
void variable_definition_virtual_dtor(pointer);
void variable_definition_virtual_copy_ctor(pointer,const_pointer);
void variable_definition_virtual_assign(pointer,const_pointer);
void variable_definition_print_to_header_class(const_pointer,FILE*);
/*void variable_definition_print_to_header_instance(const_pointer,FILE*);*/
void variable_definition_print_to_header_prototype(const_pointer,FILE*);
void variable_definition_print_to_header_define(const_pointer,FILE*);
void variable_definition_print_to_source(const_pointer,FILE*);
void variable_definition_dump(const_pointer,FILE*,int);
void variable_definition_set(pointer,const char*,const char*,const char*);
void variable_definition_ctor_type_name_default_value(pointer,va_list);

#define VARIABLE_DEFINITION_CLASS_MEMBERS \
  { \
    { \
      variable_definition_isa, \
      variable_definition_is_descendent, \
      yaooc_object_swap \
    }, \
      variable_definition_virtual_dtor, \
      variable_definition_virtual_copy_ctor, \
      variable_definition_virtual_assign, \
      variable_definition_print_to_header_class, \
      variable_definition_print_to_header_prototype, \
      variable_definition_print_to_header_define, \
      variable_definition_print_to_source, \
      variable_definition_dump \
  }, \
  variable_definition_set

/*
  Constructor definition (other than default and copy) -- descendent of
*/
//VECTOR_DEFINITION(arg_definition)

class_table(constructor_definition)
{
  item_definition_class_members_t;
  void (*add_arg)(pointer,const_pointer);
};

class_instance(constructor_definition)
{
  yaooc_string_t prefix_;
  yaooc_string_t name_;
  item_definition_shared_ptr_vector_pointer args_;
};

class(constructor_definition);
ISA_DEFINITION(constructor_definition,item_definition)
void constructor_definition_default_ctor(pointer);
void constructor_definition_virtual_dtor(pointer);
void constructor_definition_virtual_copy_ctor(pointer,const_pointer);
void constructor_definition_virtual_assign(pointer,const_pointer);
void constructor_definition_print_to_header_class(const_pointer,FILE*);
void constructor_definition_print_to_header_instance(const_pointer,FILE*);
void constructor_definition_print_to_header_prototype(const_pointer,FILE*);
void constructor_definition_print_to_header_define(const_pointer,FILE*);
void constructor_definition_print_to_source(const_pointer,FILE*);
void constructor_definition_dump(const_pointer,FILE*,int);
void constructor_definition_add_arg(pointer,const_pointer);

#define CONSTRUCTOR_DEFINITION_CLASS_MEMBERS \
  { \
    { \
      constructor_definition_isa, \
      constructor_definition_is_descendent, \
      yaooc_object_swap \
    }, \
      constructor_definition_virtual_dtor, \
      constructor_definition_virtual_copy_ctor, \
      constructor_definition_virtual_assign, \
      constructor_definition_print_to_header_class, \
      constructor_definition_print_to_header_prototype, \
      constructor_definition_print_to_header_define, \
      constructor_definition_print_to_source, \
      constructor_definition_dump \
  }, \
  constructor_definition_add_arg

/*
  A method definition -- a descendent of constructor
*/
class_table(method_definition)
{
  constructor_definition_class_members_t;
};

class_instance(method_definition)
{
  constructor_definition_instance_members_t;
  type_definition_pointer return_type_;
  yaooc_string_t implementation_function_;
  bool is_const_;
};

class(method_definition);
ISA_DEFINITION(method_definition,constructor_definition)
void method_definition_default_ctor(pointer);
void method_definition_virtual_dtor(pointer);
void method_definition_virtual_copy_ctor(pointer,const_pointer);
void method_definition_virtual_assign(pointer,const_pointer);
void method_definition_print_to_header_class(const_pointer,FILE*);
void method_definition_print_to_header_prototype(const_pointer,FILE*);
void method_definition_print_to_header_define(const_pointer,FILE*);
void method_definition_print_to_source(const_pointer,FILE*);
void method_definition_dump(const_pointer,FILE*,int);
void method_definition_add_arg(pointer,const_pointer);
#define METHOD_DEFINITION_CLASS_MEMBERS \
  { \
    { \
      { \
        method_definition_isa, \
        method_definition_is_descendent, \
        yaooc_object_swap \
      }, \
        method_definition_virtual_dtor, \
        method_definition_virtual_copy_ctor, \
        method_definition_virtual_assign, \
        method_definition_print_to_header_class, \
        method_definition_print_to_header_prototype, \
        method_definition_print_to_header_define, \
        method_definition_print_to_source, \
        method_definition_dump \
    }, \
    constructor_definition_add_arg \
  }


/*
  A member (table, private, protected) definition
*/
class_table(member_definition)
{
  item_definition_class_members_t;
  void(*add_item)(pointer,const_pointer);
};

class_instance(member_definition)
{
  item_definition_shared_ptr_vector_pointer items_;
  bool print_variable_members_;
};

class(member_definition);
ISA_DEFINITION(member_definition,item_definition)
void member_definition_default_ctor(pointer);
void member_definition_virtual_dtor(pointer);
void member_definition_virtual_copy_ctor(pointer,const_pointer);
void member_definition_virtual_assign(pointer,const_pointer);
void member_definition_print_to_header_class(const_pointer,FILE*);
/*void member_definition_print_to_header_instance(const_pointer,FILE*);*/
void member_definition_print_to_header_prototype(const_pointer,FILE*);
void member_definition_print_to_header_define(const_pointer,FILE*);
void member_definition_print_to_source(const_pointer,FILE*);
void member_definition_dump(const_pointer,FILE*,int);
void member_definition_add_item(pointer,const_pointer);
#define MEMBER_DEFINITION_CLASS_MEMBERS \
  { \
    { \
      member_definition_isa, \
      member_definition_is_descendent, \
      yaooc_object_swap \
    }, \
      member_definition_virtual_dtor, \
      member_definition_virtual_copy_ctor, \
      member_definition_virtual_assign, \
      member_definition_print_to_header_class, \
      member_definition_print_to_header_prototype, \
      member_definition_print_to_header_define, \
      member_definition_print_to_source, \
      member_definition_dump \
  }, \
  member_definition_add_item


/*
  Class definition

VECTOR_DEFINITION(method_definition)
*/
class_table(class_definition)
{
  item_definition_class_members_t;
  void (*add_constructor)(pointer,const_pointer);
};

class_instance(class_definition)
{
  yaooc_string_t name_;
  yaooc_string_t parent_name_;
/*  item_definition_shared_ptr_vector_pointer constructors_;*/
  member_definition_pointer constructors_;
  member_definition_pointer table_;
  member_definition_pointer private_;
  member_definition_pointer protected_;
  member_definition_pointer instance_;
  bool has_default_ctor_;
  bool has_dtor_;
  bool has_copy_ctor_;
  bool has_assignment_;
  bool has_lt_compare_;
};

class(class_definition);
ISA_DEFINITION(class_definition,item_definition)
void class_definition_default_ctor(pointer);
void class_definition_virtual_dtor(pointer);
void class_definition_virtual_copy_ctor(pointer,const_pointer);
void class_definition_virtual_assign(pointer,const_pointer);
void class_definition_print_to_header_class(const_pointer,FILE*);
void class_definition_print_to_header_prototype(const_pointer,FILE*);
void class_definition_print_to_header_define(const_pointer,FILE*);
void class_definition_print_to_source(const_pointer,FILE*);
void class_definition_dump(const_pointer,FILE*,int);
void class_definition_add_constructor(pointer,const_pointer);

#define CLASS_DEFINITION_CLASS_MEMBERS \
  { \
    { \
      class_definition_isa, \
      class_definition_is_descendent, \
      yaooc_object_swap \
    }, \
      class_definition_virtual_dtor, \
      class_definition_virtual_copy_ctor, \
      class_definition_virtual_assign, \
      class_definition_print_to_header_class, \
      class_definition_print_to_header_prototype, \
      class_definition_print_to_header_define, \
      class_definition_print_to_source, \
      class_definition_dump \
  }, \
  class_definition_add_constructor

#endif
