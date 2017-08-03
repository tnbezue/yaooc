#include "template_objects.h"
#include <yaooc/garbage_bag.h>
#include <string.h>
const type_info_t* const get_type_info(const_pointer ptr);

//SHARED_PTR_IMPLEMENTATION(yaooc_string)

static const char* indent_space=" ";

#define INDENT(l) l*2,l*2,indent_space

ISA_IMPLEMENTATION(item_definition,yaooc_object)

void item_definition_default_ctor(pointer p)
{
}

void item_definition_dtor(pointer p)
{
  M((item_definition_pointer)p,virtual_dtor);
}

void item_definition_copy_ctor(pointer d,const_pointer s)
{
  M((item_definition_pointer)d,virtual_copy_ctor,s);
}

void item_definition_assign(pointer d,const_pointer s)
{
  if(get_type_info(d) != get_type_info(s)) {
    puts("Could not assign\n");
    exit(0);
  }
  M((item_definition_pointer)d,virtual_assign,s);
}
/*
void item_definition_print_to_header(const_pointer p,FILE* out)
{
  fprintf(out,"**** NOT IMPLEMENTED ****");
}

void item_definition_print_to_source(const_pointer p,FILE* out)
{
  fprintf(out,"**** NOT IMPLEMENTED ****");
}

void item_definition_dump(const_pointer p,FILE* out,int level)
{
  fprintf(out,"**** NOT IMPLEMENTED ****");
}
*/
item_definition_class_members_t item_definition_class_members = { ITEM_DEFINITION_CLASS_MEMBERS };

DEFINE_TYPE_INFO(item_definition,item_definition_default_ctor,item_definition_dtor,
      item_definition_copy_ctor,item_definition_assign,NULL,&item_definition_class_members,yaooc_object)


SHARED_PTR_IMPLEMENTATION(item_definition)
/*
  Type definition
*/
ISA_IMPLEMENTATION(type_definition,item_definition)

void type_definition_default_ctor(pointer p)
{
  newp(&((type_definition_pointer)p)->type_string_,yaooc_string);
}

void type_definition_virtual_dtor(pointer p)
{
  deletep(&((type_definition_pointer)p)->type_string_,yaooc_string);
}

void type_definition_virtual_copy_ctor(pointer d,const_pointer s)
{
  type_definition_default_ctor(d);
  type_definition_virtual_assign(d,s);
}

void type_definition_virtual_assign(pointer d,const_pointer s)
{
  assign_static(&((type_definition_pointer)d)->type_string_,
        &((type_definition_const_pointer)s)->type_string_,yaooc_string);
}

void type_definition_print_to_header(const_pointer p,FILE* out)
{
  fprintf(out,"%s",M(&((type_definition_const_pointer)p)->type_string_,c_str));
}

void type_definition_print_to_source(const_pointer p,FILE* out)
{
  fprintf(out,"%s",M(&((type_definition_pointer)p)->type_string_,c_str));
}

void type_definition_dump(const_pointer p,FILE* out,int level)
{
  fprintf(out,"%*.*sType: %s",INDENT(level),M(&((type_definition_pointer)p)->type_string_,c_str));
}

/*
  Value (v) is of type yaooc_string_shared_ptr_const_pointer
*/
void type_definition_set(pointer p,const char* v)
{
  M(&((type_definition_pointer)p)->type_string_,set,v);
}

type_definition_class_members_t type_definition_class_members = { TYPE_DEFINITION_CLASS_MEMBERS };

DEFINE_TYPE_INFO(type_definition,type_definition_default_ctor,NULL,
      NULL,NULL,NULL,&type_definition_class_members,item_definition)


/*
  Arg Definition
*/
ISA_IMPLEMENTATION(arg_definition,item_definition)
void arg_definition_default_ctor(pointer p)
{
  arg_definition_pointer this=p;
  this->type_=new(type_definition);
  newp(&this->name_,yaooc_string);
}

void arg_definition_virtual_dtor(pointer p)
{
  arg_definition_pointer this=p;
  delete(this->type_);
  deletep(&this->name_,yaooc_string);
}

void arg_definition_virtual_copy_ctor(pointer d,const_pointer s)
{
  arg_definition_default_ctor(d);
  arg_definition_virtual_assign(d,s);
}

void arg_definition_virtual_assign(pointer d,const_pointer s)
{
  arg_definition_pointer dst=d;
  arg_definition_const_pointer src=s;
  assign_static(&dst->type_,&src->type_,yaooc_string);
  assign_static(&dst->name_,&src->name_,yaooc_string);
}

void arg_definition_print_to_header_class(const_pointer p,FILE* out)
{
  arg_definition_const_pointer this=p;
  M(this->type_,print_to_header_class,out);
//  fprintf(out," %s",M(this->name_,get));
}

void arg_definition_print_to_header_prototype(const_pointer p,FILE* out)
{
  arg_definition_const_pointer this=p;
  M(this->type_,print_to_header_class,out);
  fprintf(out," %s",M(&this->name_,c_str));
}

void arg_definition_print_to_source(const_pointer p,FILE* out)
{
  arg_definition_const_pointer this=p;
  M(this->type_,print_to_header_class,out);
  fprintf(out," %s",M(&this->name_,c_str));
}

void arg_definition_dump(const_pointer p,FILE* out,int level)
{
  arg_definition_const_pointer this=p;
  M(this->type_,dump,out,level+1);
  fprintf(out,"%*.*sName: %s",INDENT(level),M(&this->name_,c_str));
}

type_definition_const_pointer arg_definition_type(const_pointer p)
{
  return ((arg_definition_const_pointer)p)->type_;
}

void arg_definition_set(pointer p,const char* t,const char* n)
{
  arg_definition_pointer this=p;
  M(this->type_,set,t);
  M(&this->name_,set,n);
}

void arg_definition_setv(pointer p,const char* t,const char* n)
{
}

void arg_definition_ctor_type_name(pointer p,va_list args)
{
  arg_definition_pointer this=p;
  arg_definition_default_ctor(p);
  const char* type=va_arg(args,const char*);
  const char* name=va_arg(args,const char*);
  M(this,set,type,name);
}

arg_definition_class_members_t arg_definition_class_members = { ARG_DEFINITION_CLASS_MEMBERS };

DEFINE_TYPE_INFO(arg_definition,arg_definition_default_ctor,NULL,
      NULL,NULL,NULL,&arg_definition_class_members,item_definition)


/*
  Variable definition
*/
ISA_IMPLEMENTATION(variable_definition,arg_definition)

void variable_definition_default_ctor(pointer p)
{
  arg_definition_default_ctor(p);
  newp(&((variable_definition_pointer)p)->default_value_,yaooc_string);
}

void variable_definition_virtual_dtor(pointer p)
{
  deletep(&((variable_definition_pointer)p)->default_value_,yaooc_string);
  arg_definition_virtual_dtor(p);
}

void variable_definition_virtual_copy_ctor(pointer d,const_pointer s)
{
  variable_definition_default_ctor(d);
  variable_definition_virtual_assign(d,s);
}

void variable_definition_virtual_assign(pointer d,const_pointer s)
{
  arg_definition_virtual_assign(d,s);
  assign_static(&((variable_definition_pointer)d)->default_value_,
          &((variable_definition_const_pointer)s)->default_value_,yaooc_string);
}

void variable_definition_print_to_header_class(const_pointer p,FILE* out)
{
  arg_definition_print_to_header_prototype(p,out);
  fprintf(out,";\n");
}

void variable_definition_print_to_header_prototype(const_pointer p,FILE* out)
{
  variable_definition_const_pointer this=p;
  fprintf(out,"extern ");
  arg_definition_print_to_header_prototype(this,out);
  fprintf(out,";\n");
}

void variable_definition_print_to_header_define(const_pointer p,FILE* out)
{
  variable_definition_const_pointer this=p;
  fprintf(out,"(");
  arg_definition_print_to_header_class(p,out);
  fprintf(out,") %s",M(&this->default_value_,size)==0?"0":M(&this->default_value_,c_str));
//  arg_definition_print_to_header_prototype(this,out);
}

void variable_definition_print_to_source(const_pointer p,FILE* out)
{
  arg_definition_print_to_source(p,out);
  variable_definition_const_pointer this=p;
  fprintf(out," = %s;\n",M(&this->default_value_,size)>0?M(&this->default_value_,c_str):"0");
}

void variable_definition_dump(const_pointer p,FILE* out,int level)
{
  variable_definition_const_pointer this=p;
  arg_definition_dump(p,out,level);
  fprintf(out,"Default Value: %s",M(&this->default_value_,size)==0?"0":M(&this->default_value_,c_str));
}

/*void variable_definition_set(pointer p,const_pointer t,const_pointer n,const_pointer v)
{
  arg_definition_set(p,t,n);
  assign(((variable_definition_pointer)p)->default_value_,v);
}
*/
void variable_definition_set(pointer p,const char* t,const char* n,const char* v)
{
  variable_definition_pointer this=p;
  arg_definition_set(p,t,n);
  M(&this->default_value_,set,v);
}

void variable_definition_ctor_type_name_default_value(pointer p,va_list args)
{
  variable_definition_default_ctor(p);
  const char* type=va_arg(args,const char*);
  const char* name=va_arg(args,const char*);
  const char* default_value=va_arg(args,const char*);
  variable_definition_set(p,type,name,default_value);
}

variable_definition_class_members_t variable_definition_class_members = { VARIABLE_DEFINITION_CLASS_MEMBERS };

DEFINE_TYPE_INFO(variable_definition,variable_definition_default_ctor,NULL,
      NULL,NULL,NULL,&variable_definition_class_members,arg_definition)

VECTOR_IMPLEMENTATION(item_definition_shared_ptr)

/*
  Constructor definition
*/
ISA_IMPLEMENTATION(constructor_definition,item_definition)

void constructor_definition_default_ctor(pointer p)
{
  constructor_definition_pointer this=p;
  newp(&this->prefix_,yaooc_string);
  newp(&this->name_,yaooc_string);
  this->args_=new(item_definition_shared_ptr_vector);
}

void constructor_definition_virtual_dtor(pointer p)
{
  constructor_definition_pointer this=p;
  deletep(&this->prefix_,yaooc_string);
  deletep(&this->name_,yaooc_string);
  delete(this->args_);
}

void constructor_definition_virtual_copy_ctor(pointer d,const_pointer s)
{
  constructor_definition_default_ctor(d);
  constructor_definition_virtual_assign(d,s);
}

void constructor_definition_virtual_assign(pointer d,const_pointer s)
{
  constructor_definition_pointer dst=d;
  constructor_definition_const_pointer src=s;
  assign_static(&dst->prefix_,&src->prefix_,yaooc_string);
  assign_static(&dst->name_,&src->name_,yaooc_string);
  assign(dst->args_,src->args_);
}

void constructor_definition_print_to_header_class(const_pointer p,FILE* out)
{
}

void constructor_definition_print_to_header_prototype(const_pointer p,FILE* out)
{
  constructor_definition_const_pointer this=p;
  fprintf(out,"void %s%s(pointer,va_list);\n",M(&this->prefix_,c_str),M(&this->name_,c_str));
}

void constructor_definition_print_to_header_define(const_pointer p,FILE* out)
{
}

void constructor_definition_print_to_source(const_pointer p,FILE* out)
{
  constructor_definition_const_pointer this=p;
  fprintf(out,"void %s%s(pointer p,va_list args)\n{\n"
      "   %s_pointer this=p;\n",M(&this->prefix_,c_str),M(&this->name_,c_str),M(&this->prefix_,c_str));
  item_definition_shared_ptr_vector_const_iterator i;
  CFOR_EACH(i,this->args_) {
    item_definition_const_pointer id=M(i,cget);
    fprintf(out,"  ");
    M(id,print_to_source,out);
    type_definition_const_pointer tcp=M((arg_definition_pointer)id,type);
    fprintf(out,"=va_arg(args,");
    M(tcp,print_to_source,out);
    fprintf(out,");\n");
  }
  fprintf(out,"\n}\n");
}

void constructor_definition_dump(const_pointer p,FILE* out,int level)
{
  constructor_definition_const_pointer this=p;
  fprintf(out,"%*.*sConstructor:\n%*.*sName: %s%s\n",INDENT(level),INDENT(level+1),M(&this->prefix_,c_str),M(&this->name_,c_str));
  item_definition_shared_ptr_vector_const_iterator i;
  CFOR_EACH(i,this->args_) {
    M(M(i,cget),dump,out,level+1);
    fprintf(out,"\n");
  }
}

void constructor_definition_add_arg(pointer p,const_pointer v)
{
}

constructor_definition_class_members_t constructor_definition_class_members = { CONSTRUCTOR_DEFINITION_CLASS_MEMBERS };

DEFINE_TYPE_INFO(constructor_definition,constructor_definition_default_ctor,NULL,
      NULL,NULL,NULL,&constructor_definition_class_members,item_definition)


/*
  method
*/
ISA_IMPLEMENTATION(method_definition,constructor_definition)

void method_definition_default_ctor(pointer p)
{
  method_definition_pointer this=p;
  constructor_definition_default_ctor(p);
  this->return_type_=new(type_definition);
  newp(&this->implementation_function_,yaooc_string);
  this->is_const_=false;
}

void method_definition_virtual_dtor(pointer p)
{
  method_definition_pointer this=p;
  delete(this->return_type_);
  deletep(&this->implementation_function_,yaooc_string);
  constructor_definition_virtual_dtor(p);
}

void method_definition_virtual_copy_ctor(pointer d,const_pointer s)
{
  method_definition_default_ctor(d);
  method_definition_virtual_assign(d,s);
}

void method_definition_virtual_assign(pointer d,const_pointer s)
{
  constructor_definition_virtual_assign(d,s);
  method_definition_pointer dst=d;
  method_definition_const_pointer src=s;
  assign(dst->return_type_,src->return_type_);
  assign_static(&dst->implementation_function_,&src->implementation_function_,yaooc_string);
  dst->is_const_=src->is_const_;
}

void method_definition_print_to_header_class(const_pointer p,FILE* out)
{
  method_definition_const_pointer this=p;
  M(this->return_type_,print_to_header_class,out);
  fprintf(out," (*%s)(%spointer",M(&this->name_,c_str),this->is_const_?"const_":"");
  item_definition_shared_ptr_vector_const_iterator i;
  CFOR_EACH(i,this->args_) {
    fprintf(out,",");
    item_definition_const_pointer id=M(i,cget);
    type_definition_const_pointer tcp=M((arg_definition_pointer)id,type);
    M(tcp,print_to_header_class,out);
  }
  fprintf(out,");\n");
}

void method_definition_print_to_header_prototype(const_pointer p,FILE* out)
{
  method_definition_const_pointer this=p;
  M(this->return_type_,print_to_header_class,out);
  fprintf(out," %s_%s(",M(&this->prefix_,c_str),M(&this->name_,c_str));
  if(this->is_const_)
    fprintf(out,"const_");
  fprintf(out,"pointer");
  item_definition_shared_ptr_vector_const_iterator i;
  CFOR_EACH(i,this->args_) {
    fprintf(out,",");
    M(M((arg_definition_pointer)M(i,cget),type),print_to_header_prototype,out);
  }
  fprintf(out,");\n");

}

void method_definition_print_to_header_define(const_pointer p,FILE* out)
{
  method_definition_const_pointer this=p;
  fprintf(out,"(");
  M(this->return_type_,print_to_header_define,out);
  fprintf(out,"(*) (");
  if(this->is_const_)
    fprintf(out,"const_");
  fprintf(out,"pointer");
  item_definition_shared_ptr_vector_const_iterator i;
  CFOR_EACH(i,this->args_) {
    fprintf(out,",");
    M(M((arg_definition_pointer)M(i,cget),type),print_to_header_define,out);
  }
  fprintf(out,"))");
  if(M(&this->implementation_function_,size)==0)
    fprintf(out," %s_%s",M(&this->prefix_,c_str),M(&this->name_,c_str));
  else
    fprintf(out," %s",M(&this->implementation_function_,c_str));
}

void method_definition_print_to_source(const_pointer p,FILE* out)
{
  method_definition_const_pointer this=p;
  M(this->return_type_,print_to_source,out);
  const char* const_prefix=(this->is_const_?"const_":"");
  fprintf(out," %s_%s(%spointer p",M(&this->prefix_,c_str),M(&this->name_,c_str),const_prefix);
  item_definition_shared_ptr_vector_const_iterator i;
  CFOR_EACH(i,this->args_) {
    fprintf(out,",");
    M(M(i,cget),print_to_source,out);
  }
  fprintf(out,"))\n{\n  %s_%spointer this=p;\n",M(&this->prefix_,c_str),const_prefix);

  if(strcmp(M(&this->return_type_->type_string_,c_str),"void")!=0) {
    fprintf(out,"  ");
    M(this->return_type_,print_to_source,out);
    fprintf(out," ret;\n\n  return ret;\n");
  }
  fprintf(out,"}\n");
}

void method_definition_dump(const_pointer p,FILE* out,int level)
{
  method_definition_const_pointer this=p;
  fprintf(out,"%*.*sMethod Name: %s_%s\n"
          "%*.*sMethod return ",INDENT(level),M(&this->prefix_,c_str),M(&this->name_,c_str),INDENT(level));
  M(this->return_type_,dump,out,level);
  item_definition_shared_ptr_vector_const_iterator i;
  CFOR_EACH(i,this->args_) {
    M(M(i,cget),dump,out,level+1);
  }
}

method_definition_class_members_t method_definition_class_members = { METHOD_DEFINITION_CLASS_MEMBERS };

DEFINE_TYPE_INFO(method_definition,method_definition_default_ctor,NULL,
      NULL,NULL,NULL,&method_definition_class_members,constructor_definition)


/*
  Members
*/
ISA_IMPLEMENTATION(member_definition,item_definition)

void member_definition_default_ctor(pointer p)
{
  member_definition_pointer this=p;
  this->items_=new(item_definition_shared_ptr_vector);
  this->print_variable_members_=false;
}

void member_definition_virtual_dtor(pointer p)
{
  delete(((member_definition_pointer)p)->items_);
}

void member_definition_virtual_copy_ctor(pointer d,const_pointer s)
{
  member_definition_default_ctor(d);
  member_definition_virtual_assign(d,s);
}

void member_definition_virtual_assign(pointer d,const_pointer s)
{
  member_definition_pointer dst=d;
  member_definition_const_pointer src=s;
  assign(dst->items_,src->items_);
  dst->print_variable_members_=src->print_variable_members_;
}

/*
void member_definition_print_to_header(const_pointer p,FILE* out)
{
  member_definition_const_pointer this=p;
  item_definition_shared_ptr_vector_const_iterator i;
  CFOR_EACH(i,this->items_) {
    item_definition_const_pointer id=M(i,cget);
    M(id,print_to_header_class,out);
  }
}
*/
void member_definition_dump(const_pointer p,FILE* out,int level)
{
  member_definition_const_pointer this=p;
  item_definition_shared_ptr_vector_const_iterator i;
  CFOR_EACH(i,this->items_) {
    item_definition_const_pointer id=M(i,cget);
    M(id,dump,out,level+1);
  }
}

void member_definition_print_to_header_class(const_pointer p,FILE* out)
{
  member_definition_const_pointer this=p;
  item_definition_shared_ptr_vector_const_iterator i;
  CFOR_EACH(i,this->items_) {
    fprintf(out,"  ");
    M(M(i,cget),print_to_header_class,out);
  }
}

void member_definition_print_to_header_prototype(const_pointer p,FILE* out)
{
  member_definition_const_pointer this=p;
  item_definition_shared_ptr_vector_const_iterator i;
  CFOR_EACH(i,this->items_) {
    item_definition_const_pointer item=(M(i,cget));
    if(strcmp(M(item,isa),"variable_definition_t")!=0 || this->print_variable_members_)
      M(item,print_to_header_prototype,out);
  }
}

void member_definition_print_to_header_define(const_pointer p,FILE* out)
{
  member_definition_const_pointer this=p;
  item_definition_shared_ptr_vector_const_iterator i;
  CFOR_EACH(i,this->items_) {
    fprintf(out,"  ");
    M(M(i,cget),print_to_header_define,out);
    fprintf(out,", \\\n");
  }
}

void member_definition_print_to_source(const_pointer p,FILE* out)
{
  member_definition_const_pointer this=p;
  item_definition_shared_ptr_vector_const_iterator i;
  CFOR_EACH(i,this->items_) {
    item_definition_const_pointer item=M(i,cget);
    if(strcmp(M(item,isa),"variable_definition_t")!=0 || this->print_variable_members_) {
      M(item,print_to_source,out);
      fprintf(out,"\n");
    }
  }
}

void member_definition_add_item(pointer p,const_pointer v)
{
  M(((member_definition_pointer)p)->items_,push_back,v);
}

member_definition_class_members_t member_definition_class_members = { MEMBER_DEFINITION_CLASS_MEMBERS };

DEFINE_TYPE_INFO(member_definition,member_definition_default_ctor,NULL,
      NULL,NULL,NULL,&member_definition_class_members,item_definition)

/*
  Class definition
*/
ISA_IMPLEMENTATION(class_definition,item_definition)

void class_definition_default_ctor(pointer p)
{
  class_definition_pointer this=p;
  newp(&this->name_,yaooc_string);
  newp(&this->parent_name_,yaooc_string);
//  this->constructors_=new(item_definition_shared_ptr_vector);
  this->constructors_=new(member_definition);
  this->table_=new(member_definition);
  this->private_=new(member_definition);
  this->protected_=new(member_definition);
  this->instance_=new(member_definition);
  this->has_default_ctor_=false;
  this->has_dtor_=false;
  this->has_copy_ctor_=false;
  this->has_assignment_=false;
  this->has_lt_compare_=false;
}

void class_definition_virtual_dtor(pointer p)
{
  class_definition_pointer this=p;
  deletep(&this->name_,yaooc_string);
  deletep(&this->parent_name_,yaooc_string);
  delete(this->constructors_);
  delete(this->table_);
  delete(this->private_);
  delete(this->protected_);
  delete(this->instance_);
}

void class_definition_virtual_copy_ctor(pointer d,const_pointer s)
{
  class_definition_default_ctor(d);
  class_definition_virtual_assign(d,s);
}

void class_definition_virtual_assign(pointer d,const_pointer s)
{
  class_definition_pointer dst=d;
  class_definition_const_pointer src=s;
  assign_static(&dst->name_,&src->name_,yaooc_string);
  assign_static(&dst->parent_name_,&src->parent_name_,yaooc_string);
  assign(dst->constructors_,src->constructors_);
  assign(dst->table_,src->table_);
  assign(dst->private_,src->private_);
  assign(dst->protected_,src->protected_);
  assign(dst->instance_,src->instance_);
  dst->has_default_ctor_=src->has_default_ctor_;
  dst->has_dtor_=src->has_dtor_;
  dst->has_copy_ctor_=src->has_copy_ctor_;
  dst->has_assignment_=src->has_assignment_;
  dst->has_lt_compare_=src->has_lt_compare_;
}

void class_definition_print_to_header_class(const_pointer p,FILE* out)
{
  class_definition_const_pointer this=p;
  fprintf(out,"class_table(%s)\n{\n",M(&this->name_,c_str));
  if(M(&this->parent_name_,size)!=0)
    fprintf(out,"  %s_class_members_t;\n",M(&this->parent_name_,c_str));
  M(this->table_,print_to_header_class,out);
  fprintf(out,"};\n\n");
  fprintf(out,"class_instance(%s)\n{\n",M(&this->name_,c_str));
  if(M(&this->parent_name_,size)!=0)
    fprintf(out,"  %s_instance_members_t;\n",M(&this->parent_name_,c_str));
  M(this->instance_,print_to_header_class,out);
  fprintf(out,"};\n\n"
      "class(%s);\n\n",M(&this->name_,c_str));

}

void class_definition_print_to_header_prototype(const_pointer p,FILE* out)
{
  class_definition_const_pointer this=p;

  fprintf(out,"/* Prototypes for type info */\n");
  if(this->has_default_ctor_)
    fprintf(out,"void %s_default_ctor(pointer);\n",M(&this->name_,c_str));
  if(this->has_dtor_)
    fprintf(out,"void %s_dtor(pointer);\n",M(&this->name_,c_str));
  if(this->has_copy_ctor_)
    fprintf(out,"void %s_copy_ctor(pointer,const_pointer);\n",M(&this->name_,c_str));
  if(this->has_assignment_)
    fprintf(out,"void %s_assign(pointer,const_pointer);\n",M(&this->name_,c_str));
  if(this->has_lt_compare_)
    fprintf(out,"void %s_less_than_compare(const_pointer,const_pointer);\n",M(&this->name_,c_str));

  fprintf(out,"\n/* Prototypes for Constructors */\n");
  M(this->constructors_,print_to_header_prototype,out);

  fprintf(out,"\n/* Prototypes for class table members */\n");
  M(this->table_,print_to_header_prototype,out);

  fprintf(out,"\n/* Prototypes for class instance members */\n");
  M(this->instance_,print_to_header_prototype,out);

  fprintf(out,"\n/* Prototypes for class protected members */\n");
  M(this->protected_,print_to_header_prototype,out);
}

void class_definition_print_to_header_define(const_pointer p,FILE* out)
{
  GB_INIT;
  class_definition_const_pointer this=p;
  yaooc_string_pointer uc_name=GB_SAVE(M(&this->name_,upcase));
  fprintf(out,"\n/* New class table members for %s */\n#define %s_NEW_CLASS_MEMBERS \\\n",M(&this->name_,c_str),M(uc_name,c_str));
  M(this->table_,print_to_header_define,out);
  fprintf(out,"\n/* New plus parent members for %s */\n#define %s_CLASS_MEMBERS \\\n",M(&this->name_,c_str),M(uc_name,c_str));
  if(M(&this->parent_name_,size)>0) {
    yaooc_string_pointer parent_uc_name=GB_SAVE(M(&this->parent_name_,upcase));
    fprintf(out,"  { %s_CLASS_MEMBERS }, \\\n",M(parent_uc_name,c_str));
  }
  fprintf(out,"  %s_NEW_CLASS_MEMBERS\n",M(uc_name,c_str));
  GB_EXIT;
}

void class_definition_print_to_source(const_pointer p,FILE* out)
{
  class_definition_const_pointer this=p;
  fprintf(out,"/* Private members for %s */\n",M(&this->name_,c_str));
  this->private_->print_variable_members_=true;
  M(this->private_,print_to_source,out);
  fprintf(out,"\n/* Protected members for %s */\n",M(&this->name_,c_str));
  this->protected_->print_variable_members_=true;
  M(this->protected_,print_to_source,out);
  fprintf(out,"\n/* Typeinfo for %s */",M(&this->name_,c_str));
  if(this->has_default_ctor_)
    fprintf(out,"\nvoid %s_default_ctor(pointer p)\n"
          "{\n"
          "  %s_pointer this=p;\n"
          "}\n",M(&this->name_,c_str),M(&this->name_,c_str));
  if(this->has_dtor_)
    fprintf(out,"\nvoid %s_dtor(pointer p)\n"
          "{\n"
          "  %s_pointer this=p;\n"
          "}\n",M(&this->name_,c_str),M(&this->name_,c_str));
  if(this->has_copy_ctor_)
    fprintf(out,"\nvoid %s_copy_ctor(pointer d,const_pointer s)\n"
          "{\n"
          "  %s_pointer dst=d;\n"
          "  %s_const_pointer src=s;\n"
          "}\n",M(&this->name_,c_str),M(&this->name_,c_str),M(&this->name_,c_str));
  if(this->has_assignment_)
    fprintf(out,"\nvoid %s_assign(pointer d,const_pointer s)\n"
          "{\n"
          "  %s_pointer dst=d;\n"
          "  %s_const_pointer src=s;\n"
          "}\n",M(&this->name_,c_str),M(&this->name_,c_str),M(&this->name_,c_str));
  if(this->has_lt_compare_)
    fprintf(out,"\nvoid %s_less_than_compare(const_pointer p1,const_pointer p2)\n"
          "{\n"
          "  %s_const_pointer vp1=p1;\n"
          "  %s_const_pointer vp2=p2;\n"
          "}\n",M(&this->name_,c_str),M(&this->name_,c_str),M(&this->name_,c_str));
  fprintf(out,"\n/* Additional constructors for %s */\n",M(&this->name_,c_str));
  M(this->constructors_,print_to_source,out);
  fprintf(out,"\n/* Class table members for %s */\n",M(&this->name_,c_str));
  this->table_->print_variable_members_=false;
  M(this->table_,print_to_source,out);
  fprintf(out,"\n/* Instance members for %s */\n",M(&this->name_,c_str));
  this->instance_->print_variable_members_=false;
  M(this->instance_,print_to_source,out);
  yaooc_string_pointer uc_name=M(&this->name_,upcase);
  fprintf(out,"\n%s_class_members_t %s_class_members = { %s_CLASS_MEMBERS };\n",
        M(&this->name_,c_str),M(&this->name_,c_str),M(uc_name,c_str));
  delete(uc_name);
  fprintf(out,"\nDEFINE_TYPE_INFO(%s",M(&this->name_,c_str));
  if(this->has_default_ctor_)
    fprintf(out,",%s_default_ctor",M(&this->name_,c_str));
  else
    fprintf(out,",NULL");
  if(this->has_dtor_)
    fprintf(out,",%s_dtor",M(&this->name_,c_str));
  else
    fprintf(out,",NULL");
  if(this->has_copy_ctor_)
    fprintf(out,",%s_copy_ctor",M(&this->name_,c_str));
  else
    fprintf(out,",NULL");
  if(this->has_assignment_)
    fprintf(out,",%s_assign",M(&this->name_,c_str));
  else
    fprintf(out,",NULL");
  if(this->has_lt_compare_)
    fprintf(out,",%s_less_than_compare",M(&this->name_,c_str));
  else
    fprintf(out,",NULL");
  fprintf(out,",&%s_class_members",M(&this->name_,c_str));
  if(M(&this->parent_name_,size)>0)
    fprintf(out,",%s)\n",M(&this->parent_name_,c_str));
  else
    fprintf(out,",NULL)\n");
}

void class_definition_dump(const_pointer p,FILE* out,int level)
{
  class_definition_const_pointer this=p;
  fprintf(out,"%*.*sClass:\n"
      "%*.*sName: %s\n",INDENT(level),INDENT(level),M(&this->name_,c_str));
  if(M(&this->parent_name_,size)>0)
    fprintf(out,"%*.*sParent: %s\n",INDENT(level),M(&this->parent_name_,c_str));
  fprintf(out,"%*.*sHas default ctor: %s\n",INDENT(level),(this->has_default_ctor_?"true":"false"));
  fprintf(out,"%*.*sHas dtor: %s\n",INDENT(level),(this->has_dtor_?"true":"false"));
  fprintf(out,"%*.*sHas copy ctor: %s\n",INDENT(level),(this->has_copy_ctor_?"true":"false"));
  fprintf(out,"%*.*sHas assign: %s\n",INDENT(level),(this->has_assignment_?"true":"false"));
  fprintf(out,"%*.*sHas less than compare: %s\n",INDENT(level),(this->has_lt_compare_?"true":"false"));
/*  item_definition_shared_ptr_vector_const_iterator i;
  if(M(this->constructors_,size)>0) {
    fprintf(out,"%*.*sConstructors:\n",INDENT(level));
    CFOR_EACH(i,this->constructors_) {
      M(M(i,cget),dump,out,level+1);
    }
  }*/
  fprintf(out,"Constructors");
  M(this->constructors_,dump,out,level+1);
  fprintf(out,"%*.*sClass Table\n",INDENT(level));
  M(this->table_,dump,out,level+1);
  M(this->instance_,dump,out,level+1);
  M(this->protected_,dump,out,level+1);
  M(this->private_,dump,out,level+1);
}

void class_definition_add_constructor(pointer p,const_pointer con)
{
}

class_definition_class_members_t class_definition_class_members = { CLASS_DEFINITION_CLASS_MEMBERS };

DEFINE_TYPE_INFO(class_definition,class_definition_default_ctor,NULL,
      NULL,NULL,NULL,&class_definition_class_members,item_definition)
