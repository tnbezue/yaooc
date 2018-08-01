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

#include "template_objects.h"
#include <string.h>

/*  Begin YAOOC PreProcessor generated content */

/* Private items for yaoocpp_item */

/* Protected items for yaoocpp_item */


/* Typeinfo for yaoocpp_item */
void yaoocpp_item_default_ctor(pointer p)
{
  ((yaoocpp_item_pointer)p)->flags_=DEFINED_IN_CURRENT_CLASS;
}

void yaoocpp_item_dtor(pointer p)
{
  yaoocpp_item_pointer this=p;
  M(this,virtual_dtor);
}

void yaoocpp_item_copy_ctor(pointer d,const_pointer s)
{
  yaoocpp_item_default_ctor(d);
  yaoocpp_item_assign(d,s);
}

void yaoocpp_item_assign(pointer d,const_pointer s)
{
  ((yaoocpp_item_pointer)d)->flags_=((yaoocpp_item_const_pointer)s)->flags_;
}

bool yaoocpp_item_less_than_compare(const_pointer p1,const_pointer p2)
{
  yaoocpp_item_const_pointer vp1=p1;
  yaoocpp_item_const_pointer vp2=p2;
  int ret = strcmp(M(vp1,isa),M(vp2,isa));
  return ret == 0 ? M(vp1,virtual_less_than_compare,p2) : ret < 0;
}

/* Constructors for yaoocpp_item */

/* Class table methods for yaoocpp_item */
const char* yaoocpp_item_isa(const_pointer p) { return "yaoocpp_item_t"; }

/* Class table for yaoocpp_item */
yaoocpp_item_class_table_t yaoocpp_item_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .isa = (const char* (*) (const_pointer)) yaoocpp_item_isa,
  .is_descendant = (bool (*) (const_pointer,const char*)) yaoocpp_item_is_descendant,
  .swap = (void (*) (pointer,pointer)) yaoocpp_item_swap,
  .virtual_dtor = (void (*) (pointer)) NULL,
  .virtual_less_than_compare = (bool (*) (const_pointer,const_pointer)) NULL,
  .dump = (void (*) (const_pointer p,yaooc_ofstream_pointer)) NULL,
  .print_prototype = (void (*) (const_pointer p,yaooc_ofstream_pointer)) NULL,
  .print_implementation = (void (*) (const_pointer p,yaooc_ofstream_pointer)) NULL,
  .print_class_prototype = (void (*) (const_pointer p,yaooc_ofstream_pointer)) NULL,
  .print_class_implementation = (void (*) (const_pointer p,yaooc_ofstream_pointer)) NULL,
};


DEFINE_TYPE_INFO(yaoocpp_item,Y,Y,Y,Y,Y,N,N,Y,yaooc_object)

DYNAMIC_POINTER_IMPLEMENTATION(yaoocpp_item,yaoocpp_item_ptr);
VECTOR_IMPLEMENTATION(yaoocpp_item_ptr,yaoocpp_item_ptr_vector);


/* Private items for yaoocpp_argument */

/* Protected items for yaoocpp_argument */


/* Typeinfo for yaoocpp_argument */
void yaoocpp_argument_default_ctor(pointer p)
{
  yaoocpp_argument_pointer this=p;
  yaoocpp_item_default_ctor(p);
  this->name_=new(yaooc_string);
  this->type_=new(yaooc_string);
}

void yaoocpp_argument_copy_ctor(pointer d,const_pointer s)
{
  yaoocpp_argument_default_ctor(d);
  yaoocpp_argument_assign(d,s);
}

void yaoocpp_argument_assign(pointer d,const_pointer s)
{
  yaoocpp_argument_pointer dst=d;
  yaoocpp_argument_const_pointer src=s;
  yaoocpp_item_assign(d,s);
  assign_static(dst->name_,src->name_,yaooc_string);
  assign_static(dst->type_,src->type_,yaooc_string);
}

/*bool yaoocpp_argument_less_than_compare(const_pointer p1,const_pointer p2)
{
  yaoocpp_argument_const_pointer vp1=p1;
  yaoocpp_argument_const_pointer vp2=p2;
  return op_lt_static(vp1->name_,vp2->name_,yaooc_string);
}
*/
/* Constructors for yaoocpp_argument */

/* Class table methods for yaoocpp_argument */
const char* yaoocpp_argument_isa(const_pointer p) { return "yaoocpp_argument_t"; }

void yaoocpp_argument_virtual_dtor(pointer p)
{
  yaoocpp_argument_pointer this=p;
  delete(this->name_);
  delete(this->type_);
}

bool yaoocpp_argument_virtual_less_than_compare(const_pointer p,const_pointer o)
{
  yaoocpp_argument_const_pointer this=p;
  yaoocpp_argument_const_pointer other=o;
  return op_lt_static(this->name_,other->name_,yaooc_string);
}

void yaoocpp_argument_dump(const_pointer p,yaooc_ofstream_pointer out)
{
  yaoocpp_argument_const_pointer this=p;
  M(out,printf,"Type: %s Name: %s",M(this->type_,c_str),M(this->name_,c_str));
}

const char* yaoocpp_argument_type(const_pointer p)
{
  return M(((yaoocpp_argument_const_pointer)p)->type_,c_str);
}

const char* yaoocpp_argument_name(const_pointer p)
{
  return M(((yaoocpp_argument_const_pointer)p)->name_,c_str);
}

/* Class table for yaoocpp_argument */
yaoocpp_argument_class_table_t yaoocpp_argument_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaoocpp_item_class_table,
  .isa = (const char* (*) (const_pointer p)) yaoocpp_argument_isa,
  .is_descendant = (bool (*) (const_pointer p,const char*)) yaoocpp_argument_is_descendant,
  .swap = (void (*) (pointer p,pointer)) yaoocpp_argument_swap,
  .virtual_dtor = (void (*) (pointer p)) yaoocpp_argument_virtual_dtor,
  .virtual_less_than_compare = (bool (*) (const_pointer p,const_pointer)) yaoocpp_argument_virtual_less_than_compare,
  .dump = (void (*) (const_pointer p,yaooc_ofstream_pointer)) yaoocpp_argument_dump,
  .type = (const char* (*) (const_pointer)) yaoocpp_argument_type,
  .name = (const char* (*) (const_pointer)) yaoocpp_argument_name,
  .print_prototype = (void (*) (const_pointer p,yaooc_ofstream_pointer)) NULL,
  .print_implementation = (void (*) (const_pointer p,yaooc_ofstream_pointer)) NULL,
  .print_class_prototype = (void (*) (const_pointer p,yaooc_ofstream_pointer)) NULL,
  .print_class_implementation = (void (*) (const_pointer p,yaooc_ofstream_pointer)) NULL,
};


DEFINE_TYPE_INFO(yaoocpp_argument,Y,N,Y,Y,N,N,N,Y,yaoocpp_item)
/* Private items for yaoocpp_variable */

/* Protected items for yaoocpp_variable */


/* Typeinfo for yaoocpp_variable */
void yaoocpp_variable_default_ctor(pointer p)
{
  yaoocpp_variable_pointer this=p;
  yaoocpp_argument_default_ctor(this);
  this->default_value_=new(yaooc_string);
}

void yaoocpp_variable_copy_ctor(pointer d,const_pointer s)
{
  yaoocpp_variable_default_ctor(d);
  yaoocpp_variable_assign(d,s);
}

void yaoocpp_variable_assign(pointer d,const_pointer s)
{
  yaoocpp_variable_pointer dst=d;
  yaoocpp_variable_const_pointer src=s;
  yaoocpp_argument_assign(d,s);
  assign_static(dst->default_value_,src->default_value_,yaooc_string);
}

/* Constructors for yaoocpp_variable */

/* Class table methods for yaoocpp_variable */
const char* yaoocpp_variable_isa(const_pointer p) { return "yaoocpp_variable_t"; }

void yaoocpp_variable_virtual_dtor(pointer p)
{
  yaoocpp_variable_pointer this=p;
  delete(this->default_value_);
  yaoocpp_argument_virtual_dtor(p);
}

bool yaoocpp_variable_virtual_less_than_compare(const_pointer p,const_pointer o)
{
  return yaoocpp_argument_virtual_less_than_compare(p,o);
}

void yaoocpp_variable_dump(const_pointer p,yaooc_ofstream_pointer out)
{
  yaoocpp_variable_const_pointer this=p;
  yaoocpp_argument_dump(p,out);
  M(out,printf," Default value: %s\n",M(this->default_value_,c_str));
}

const char* yaoocpp_variable_default_value(const_pointer p)
{
  return M(((yaoocpp_variable_const_pointer)p)->default_value_,c_str);
}

void yaoocpp_variable_print_prototype(const_pointer p,yaooc_ofstream_pointer out)
{
  yaoocpp_variable_const_pointer this=p;
  M(out,printf,"extern %s %s;\n",M(this,type),M(this,name));
}

void yaoocpp_variable_print_implementation(const_pointer p,yaooc_ofstream_pointer out)
{
  yaoocpp_variable_const_pointer this=p;
  M(out,printf,"%s %s = %s;\n",M(this,type),M(this,name),
        M(this->default_value_,size)==0 ? "0" : M(this,default_value));
}

void yaoocpp_variable_print_class_prototype(const_pointer p,yaooc_ofstream_pointer out)
{
  yaoocpp_variable_const_pointer this=p;
  M(out,printf,"  %s %s;\n",M(this->type_,c_str),M(this->name_,c_str));
}

void yaoocpp_variable_print_class_implementation(const_pointer p,yaooc_ofstream_pointer out)
{
  yaoocpp_variable_const_pointer this=p;
  M(out,printf,"  .%s = (%s) %s,\n",M(this,name),M(this,type),M(this->default_value_,size)==0 ? "0" : M(this,default_value));
}

//void yaoocpp_variable_
/* Class table for yaoocpp_variable */
yaoocpp_variable_class_table_t yaoocpp_variable_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaoocpp_argument_class_table,
  .isa = (const char* (*) (const_pointer p)) yaoocpp_variable_isa,
  .is_descendant = (bool (*) (const_pointer p,const char*)) yaoocpp_variable_is_descendant,
  .swap = (void (*) (pointer p,pointer)) yaoocpp_variable_swap,
  .virtual_dtor = (void (*) (pointer p)) yaoocpp_variable_virtual_dtor,
  .virtual_less_than_compare = (bool (*) (const_pointer p,const_pointer)) yaoocpp_variable_virtual_less_than_compare,
  .dump = (void (*) (const_pointer p,yaooc_ofstream_pointer)) yaoocpp_variable_dump,
  .type = (const char* (*) (const_pointer p)) yaoocpp_argument_type,
  .name = (const char* (*) (const_pointer p)) yaoocpp_argument_name,
  .default_value = (const char* (*) (const_pointer p)) yaoocpp_variable_default_value,
  .print_prototype = (void (*) (const_pointer p,yaooc_ofstream_pointer)) yaoocpp_variable_print_prototype,
  .print_implementation = (void (*) (const_pointer p,yaooc_ofstream_pointer)) yaoocpp_variable_print_implementation,
  .print_class_prototype = (void (*) (const_pointer p,yaooc_ofstream_pointer)) yaoocpp_variable_print_class_prototype,
  .print_class_implementation = (void (*) (const_pointer p,yaooc_ofstream_pointer)) yaoocpp_variable_print_class_implementation,
};


DEFINE_TYPE_INFO(yaoocpp_variable,Y,N,Y,Y,N,N,N,Y,yaoocpp_argument)

/* Private items for yaoocpp_constructor */

/* Protected items for yaoocpp_constructor */


/* Typeinfo for yaoocpp_constructor */
void yaoocpp_constructor_default_ctor(pointer p)
{
  yaoocpp_constructor_pointer this=p;
  yaoocpp_item_default_ctor(p);
  this->name_=new(yaooc_string);
  this->arguments_=new(yaoocpp_item_ptr_vector);
  this->implementation_method_=new(yaooc_string);
  this->prefix_=new(yaooc_string);
}

void yaoocpp_constructor_copy_ctor(pointer d,const_pointer s)
{
  yaoocpp_constructor_default_ctor(d);
  yaoocpp_constructor_assign(d,s);
}

void yaoocpp_constructor_assign(pointer d,const_pointer s)
{
  yaoocpp_item_assign(d,s);
  yaoocpp_constructor_pointer dst=d;
  yaoocpp_constructor_const_pointer src=s;
  assign_static(dst->name_,src->name_,yaooc_string);
  assign_static(dst->arguments_,src->arguments_,yaoocpp_item_ptr_vector);
  assign_static(dst->implementation_method_,src->implementation_method_,yaooc_string);
  assign_static(dst->prefix_,src->prefix_,yaooc_string);
}

/* Constructors for yaoocpp_constructor */

/* Class table methods for yaoocpp_constructor */
const char* yaoocpp_constructor_isa(const_pointer p) { return "yaoocpp_constructor_t"; }

void yaoocpp_constructor_virtual_dtor(pointer p)
{
  yaoocpp_constructor_pointer this=p;
  delete(this->name_);
  delete(this->arguments_);
  delete(this->implementation_method_);
  delete(this->prefix_);
}

bool yaoocpp_constructor_virtual_less_than_compare(const_pointer p,const_pointer o)
{
  yaoocpp_constructor_const_pointer this=p;
  yaoocpp_constructor_const_pointer other=o;
  return op_lt_static(this->name_,other->name_,yaooc_string);
}

void yaoocpp_constructor_dump(const_pointer p,yaooc_ofstream_pointer out)
{
  yaoocpp_constructor_const_pointer this=p;
  M(out,printf,"Name: %s Prefix: %s Defined in Current: %s  Defined in Parent: %s Overridden: %s\n",
        M(this->name_,c_str),M(this->prefix_,c_str),
        (this->flags_ & DEFINED_IN_CURRENT_CLASS) ? "Yes" : "No",
        (this->flags_ & DEFINED_IN_PARENT_CLASS) ? "Yes" : "No",
        (this->flags_ & OVERRIDEN_IN_CURRENT_CLASS) ? "Yes" : "No");
  yaoocpp_item_ptr_vector_const_iterator i;
//  int n=1;
  FOR_EACH(i,this->arguments_) {
    yaoocpp_argument_const_pointer arg= (yaoocpp_argument_const_pointer)*i;
    M(out,printf,"  "); M(arg,dump,out); M(out,printf,"\n");
  }
}

void yaoocpp_constructor_print_prototype(const_pointer p,yaooc_ofstream_pointer out)
{
  yaoocpp_constructor_const_pointer this=p;
  M(out,printf,"void %s%s(pointer,va_list);\n",M(this->prefix_,c_str),M(this->name_,c_str));
}

void yaoocpp_constructor_print_implementation(const_pointer p,yaooc_ofstream_pointer out)
{
  yaoocpp_constructor_const_pointer this=p;
  M(out,printf,"void %s%s(pointer p,va_list args)\n{\n"
        "  %s_pointer this=p;\n",M(this->prefix_,c_str),M(this->name_,c_str),
        M(this->prefix_,c_str));
  yaoocpp_item_ptr_vector_const_iterator i;
  FOR_EACH(i,this->arguments_) {
    yaoocpp_argument_const_pointer arg= (yaoocpp_argument_const_pointer)*i;
    M(out,printf,"  %s %s = va_arg(args,%s);\n",M(arg,type),M(arg,name),M(arg,type));
  }
  M(out,printf,"\n}\n\n");
}

/* Class table for yaoocpp_constructor */
yaoocpp_constructor_class_table_t yaoocpp_constructor_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaoocpp_item_class_table,
  .isa = (const char* (*) (const_pointer p)) yaoocpp_constructor_isa,
  .is_descendant = (bool (*) (const_pointer p,const char*)) yaoocpp_constructor_is_descendant,
  .swap = (void (*) (pointer p,pointer)) yaoocpp_constructor_swap,
  .virtual_dtor = (void (*) (pointer p)) yaoocpp_constructor_virtual_dtor,
  .virtual_less_than_compare = (bool (*) (const_pointer p,const_pointer)) yaoocpp_constructor_virtual_less_than_compare,
  .dump = (void (*) (const_pointer p,yaooc_ofstream_pointer)) yaoocpp_constructor_dump,
  .print_prototype = (void (*) (const_pointer p,yaooc_ofstream_pointer)) yaoocpp_constructor_print_prototype,
  .print_implementation = (void (*) (const_pointer p,yaooc_ofstream_pointer)) yaoocpp_constructor_print_implementation,
  .print_class_prototype = (void (*) (const_pointer p,yaooc_ofstream_pointer)) NULL,
  .print_class_implementation = (void (*) (const_pointer p,yaooc_ofstream_pointer)) NULL,
};


DEFINE_TYPE_INFO(yaoocpp_constructor,Y,N,Y,Y,N,N,N,Y,yaoocpp_item)
/* Private items for yaoocpp_method */

/* Protected items for yaoocpp_method */


/* Typeinfo for yaoocpp_method */
#define yaoocpp_method_parent_class_table ((yaoocpp_constructor_class_table_t*)(yaoocpp_method_class_table.parent_class_table_))
void yaoocpp_method_default_ctor(pointer p)
{
  yaoocpp_method_pointer this=p;
  yaoocpp_constructor_default_ctor(p);
  this->type_=new(yaooc_string);
  this->is_const_=false;
}

void yaoocpp_method_copy_ctor(pointer d,const_pointer s)
{
  yaoocpp_method_default_ctor(d);
  yaoocpp_method_assign(d,s);
}

void yaoocpp_method_assign(pointer d,const_pointer s)
{
  yaoocpp_method_pointer dst=d;
  yaoocpp_method_const_pointer src=s;
  yaoocpp_constructor_assign(dst,src);
  assign_static(dst->type_,src->type_,yaooc_string);
  dst->is_const_=src->is_const_;
}

/* Constructors for yaoocpp_method */

/* Class table methods for yaoocpp_method */
const char* yaoocpp_method_isa(const_pointer p) { return "yaoocpp_method_t"; }

void yaoocpp_method_virtual_dtor(pointer p)
{
  yaoocpp_method_pointer this=p;
  delete(this->type_);
  yaoocpp_method_parent_class_table->virtual_dtor(p);
}

bool yaoocpp_method_virtual_less_than_compare(const_pointer p,const_pointer o)
{
  return yaoocpp_method_parent_class_table->virtual_less_than_compare(p,o);
}

void yaoocpp_method_dump(const_pointer p,yaooc_ofstream_pointer out)
{
  yaoocpp_method_const_pointer this=p;
  M(out,printf,"Return type: %s\n",M(this->type_,c_str));
  yaoocpp_method_parent_class_table->dump(p,out);
}

void yaoocpp_method_print_prototype(const_pointer p,yaooc_ofstream_pointer out)
{
  yaoocpp_method_const_pointer this=p;
  if(M(this->implementation_method_,size)==0) {
    M(out,printf,"%s %s_%s(%spointer",M(this->type_,c_str),M(this->prefix_,c_str),
            M(this->name_,c_str),this->is_const_ ? "const_" : "");
    yaoocpp_item_ptr_vector_const_iterator i;
    FOR_EACH(i,this->arguments_) {
      yaoocpp_argument_const_pointer arg= (yaoocpp_argument_const_pointer)*i;
      M(out,printf,",%s",M(arg,type));
    }
    M(out,printf,");\n");
  } else {
    M(out,printf,"#define %s_%s %s\n",M(this->prefix_,c_str),M(this->name_,c_str),
            M(this->implementation_method_,c_str));
  }
}

void yaoocpp_method_print_implementation(const_pointer p,yaooc_ofstream_pointer out)
{
  yaoocpp_method_const_pointer this=p;
  if(strcmp(M(this->name_,c_str),"isa")==0) {
    M(out,printf,"const char* %s_isa(const_pointer p) { return \"%s_t\"; }\n\n",
          M(this->prefix_,c_str),M(this->prefix_,c_str));
  } else if(M(this->implementation_method_,size)==0) {
    M(out,printf,"%s %s_%s(%spointer p",M(this->type_,c_str),M(this->prefix_,c_str),
            M(this->name_,c_str),this->is_const_ ? "const_" : "");
    yaoocpp_item_ptr_vector_const_iterator i;
    FOR_EACH(i,this->arguments_) {
      yaoocpp_argument_const_pointer arg= (yaoocpp_argument_const_pointer)*i;
      M(out,printf,",%s %s",M(arg,type),M(arg,name));
    }
    M(out,printf,")\n");
    M(out,printf,"{\n  %s_%spointer this=p;\n",M(this->prefix_,c_str),this->is_const_ ? "const_" : "");
    if(strcmp(M(this->type_,c_str),"void")!=0 && strcmp(M(this->type_,c_str),"static void")!=0) {
      M(out,printf,"  %s ret;\n\n  return ret;",M(this->type_,c_str));
    }
    M(out,printf,"\n}\n\n");
  }
}

void yaoocpp_method_print_class_prototype(const_pointer p,yaooc_ofstream_pointer out)
{
  yaoocpp_method_const_pointer this=p;
  M(out,printf,"  %s (*%s)(%spointer",M(this->type_,c_str),M(this->name_,c_str),this->is_const_ ? "const_" : "");
  yaoocpp_item_ptr_vector_const_iterator i;
  FOR_EACH(i,this->arguments_) {
    yaoocpp_argument_const_pointer arg= (yaoocpp_argument_const_pointer)*i;
    M(out,printf,",%s",M(arg,type));
  }
  M(out,printf,");\n");
}

void yaoocpp_method_print_class_implementation(const_pointer p,yaooc_ofstream_pointer out)
{
  yaoocpp_method_const_pointer this=p;
  M(out,printf,"  .%s = (%s (*) (%spointer",M(this->name_,c_str),M(this->type_,c_str),this->is_const_ ? "const_" : "");
  yaoocpp_item_ptr_vector_const_iterator i;
  FOR_EACH(i,this->arguments_) {
    yaoocpp_argument_const_pointer arg= (yaoocpp_argument_const_pointer)*i;
    M(out,printf,",%s",M(arg,type));
  }
  M(out,printf,")) ");
  if(M(this->implementation_method_,size)==0) {
    M(out,printf,"%s_%s,\n",M(this->prefix_,c_str),M(this->name_,c_str));
  } else {
    M(out,printf,"%s,\n",M(this->implementation_method_,c_str));
  }
}

/* Class table for yaoocpp_method */
yaoocpp_method_class_table_t yaoocpp_method_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaoocpp_constructor_class_table,
  .isa = (const char* (*) (const_pointer p)) yaoocpp_method_isa,
  .is_descendant = (bool (*) (const_pointer p,const char*)) yaoocpp_method_is_descendant,
  .swap = (void (*) (pointer p,pointer)) yaoocpp_method_swap,
  .virtual_dtor = (void (*) (pointer p)) yaoocpp_method_virtual_dtor,
  .virtual_less_than_compare = (bool (*) (const_pointer p,const_pointer)) yaoocpp_method_virtual_less_than_compare,
  .dump = (void (*) (const_pointer p,yaooc_ofstream_pointer)) yaoocpp_method_dump,
  .print_prototype = (void (*) (const_pointer p,yaooc_ofstream_pointer)) yaoocpp_method_print_prototype,
  .print_implementation = (void (*) (const_pointer p,yaooc_ofstream_pointer)) yaoocpp_method_print_implementation,
  .print_class_prototype = (void (*) (const_pointer p,yaooc_ofstream_pointer)) yaoocpp_method_print_class_prototype,
  .print_class_implementation = (void (*) (const_pointer p,yaooc_ofstream_pointer)) yaoocpp_method_print_class_implementation,
};


DEFINE_TYPE_INFO(yaoocpp_method,Y,N,Y,Y,N,N,N,Y,yaoocpp_constructor)
/* Private items for yaoocpp_class */

/* Protected items for yaoocpp_class */


/* Typeinfo for yaoocpp_class */
void yaoocpp_class_default_ctor(pointer p)
{
  yaoocpp_class_pointer this=p;
  this->parent_=NULL;
  this->name_=new(yaooc_string);
  this->constructors_=new(yaoocpp_item_ptr_vector);
  this->table_=new(yaoocpp_item_ptr_vector);
  this->instance_=new(yaoocpp_item_ptr_vector);
  this->private_=new(yaoocpp_item_ptr_vector);
  this->protected_=new(yaoocpp_item_ptr_vector);
  this->has_default_ctor_ = false;
  this->has_dtor_ = false;
  this->has_copy_ctor_ = false;
  this->has_assign_ = false;
  this->has_lt_cmp_ = false;
	this->has_to_stream_ = false;
	this->has_from_stream_ = false;
  this->defined_in_top_level_file_ = false;
}

void yaoocpp_class_copy_ctor(pointer d,const_pointer s)
{
  yaoocpp_class_default_ctor(d);
  yaoocpp_class_assign(d,s);
}

void yaoocpp_class_assign(pointer d,const_pointer s)
{
  yaoocpp_class_pointer dst=d;
  yaoocpp_class_const_pointer src=s;
  dst->parent_=src->parent_;
  assign_static(dst->name_,src->name_,yaooc_string);
  assign_static(dst->constructors_,src->constructors_,yaoocpp_item_ptr_vector);
  assign_static(dst->table_,src->table_,yaoocpp_item_ptr_vector);
  assign_static(dst->instance_,src->instance_,yaoocpp_item_ptr_vector);
  assign_static(dst->private_,src->private_,yaoocpp_item_ptr_vector);
  assign_static(dst->protected_,src->protected_,yaoocpp_item_ptr_vector);
  dst->has_default_ctor_ = src->has_default_ctor_;
  dst->has_dtor_ = src->has_dtor_;
  dst->has_copy_ctor_ = src->has_copy_ctor_;
  dst->has_assign_ = src->has_assign_;
  dst->has_lt_cmp_ = src->has_lt_cmp_;
  dst->has_to_stream_ = src->has_to_stream_;
  dst->has_from_stream_ = src->has_from_stream_;
  dst->defined_in_top_level_file_ = src->defined_in_top_level_file_;
}
/* Constructors for yaoocpp_class */

/* Class table methods for yaoocpp_class */
const char* yaoocpp_class_isa(const_pointer p) { return "yaoocpp_class_t"; }

void yaoocpp_class_virtual_dtor(pointer p)
{
  yaoocpp_class_pointer this=p;
  delete(this->name_);
  delete(this->constructors_);
  delete(this->table_);
  delete(this->instance_);
  delete(this->private_);
  delete(this->protected_);
}

bool yaoocpp_class_virtual_less_than_compare(const_pointer p,const_pointer o)
{
  yaoocpp_class_const_pointer this=p;
  yaoocpp_class_const_pointer other=o;
  return op_lt_static(this->name_,other->name_,yaooc_string);
}

void yaoocpp_class_dump(const_pointer p,yaooc_ofstream_pointer out)
{
  yaoocpp_class_const_pointer this=p;
  M(out,printf,"Class Name: %s\n",M(this->name_,c_str));
  M(out,printf,"Parent Name: %s\n",this->parent_==NULL ? "None" : M(this->parent_->name_,c_str));
  M(out,printf,"Has default ctor: %s\n",this->has_default_ctor_ ? "Yes" : "No" );
  M(out,printf,"Has dtor: %s\n",this->has_dtor_ ? "Yes" : "No" );
  M(out,printf,"Has copy ctor: %s\n",this->has_copy_ctor_ ? "Yes" : "No" );
  M(out,printf,"Has assigment: %s\n",this->has_assign_ ? "Yes" : "No" );
  M(out,printf,"Has less than compare ctor: %s\n",this->has_lt_cmp_ ? "Yes" : "No" );
	M(out,printf,"Has to stream: %s\n",this->has_to_stream_ ?  "Yes" : "No" );
	M(out,printf,"Has from stream: %s\n",this->has_from_stream_ ?  "Yes" : "No" );
  M(out,printf,"Constructors\n");
  yaoocpp_item_ptr_vector_const_iterator i;
  FOR_EACH(i,this->constructors_) {
    M(*i,dump,out);
  }
  M(out,printf,"Table\n");
  FOR_EACH(i,this->table_) {
    M(*i,dump,out);
  }
  M(out,printf,"Instance\n");
  FOR_EACH(i,this->instance_) {
    M(*i,dump,out);
  }
  M(out,printf,"Private\n");
  FOR_EACH(i,this->private_) {
    M(*i,dump,out);
  }
  M(out,printf,"Protected\n");
  FOR_EACH(i,this->protected_) {
    M(*i,dump,out);
  }
}

void yaoocpp_class_print_class_definition(const_pointer p,yaooc_ofstream_pointer out)
{
  yaoocpp_class_const_pointer this=p;
  M(out,printf,"\n/*\n"
      "  Class definition for %s\n"
      "*/\n"
      "yaooc_class_table(%s)\n"
      "{\n",M(this->name_,c_str),M(this->name_,c_str));

  if(this->parent_) {
    M(out,printf,"  %s_class_table_t;\n",M(this->parent_->name_,c_str));
  }
  yaoocpp_item_ptr_vector_const_iterator item;
  FOR_EACH(item,this->table_) {
    if((*item)->flags_ == DEFINED_IN_CURRENT_CLASS) {
      M(*item,print_class_prototype,out);
    }
  }
  M(out,printf,"};\n");
  if(this->parent_)
    M(out,printf,"#define %s_parent_class_table ((%s_class_table_t*)(%s_class_table.parent_class_table_))\n",
            M(this->name_,c_str),M(this->parent_->name_,c_str),M(this->name_,c_str));

  M(out,printf,"\nyaooc_class_instance(%s)\n{\n",M(this->name_,c_str));
  if(this->parent_) {
    M(out,printf,"  %s_class_instance_t;\n",M(this->parent_->name_,c_str));
  }
  FOR_EACH(item,this->instance_) {
    if((*item)->flags_ == DEFINED_IN_CURRENT_CLASS) {
      M(*item,print_class_prototype,out);
    }
  }
  M(out,printf,"};\n");
  M(out,printf,"\nyaooc_class(%s);\n\n",M(this->name_,c_str));
}

void yaoocpp_class_print_type_info_prototypes(const_pointer p,yaooc_ofstream_pointer out)
{
  yaoocpp_class_const_pointer this=p;
  M(out,printf,"/* Prototypes for %s type info */\n",M(this->name_,c_str));
  if(this->has_default_ctor_)
    M(out,printf,"void %s_default_ctor(pointer);\n",M(this->name_,c_str));
  if(this->has_dtor_)
    M(out,printf,"void %s_dtor(pointer);\n",M(this->name_,c_str));
  if(this->has_copy_ctor_)
    M(out,printf,"void %s_copy_ctor(pointer,const_pointer);\n",M(this->name_,c_str));
  if(this->has_assign_)
    M(out,printf,"void %s_assign(pointer,const_pointer);\n",M(this->name_,c_str));
  if(this->has_lt_cmp_)
    M(out,printf,"bool %s_less_than_compare(const_pointer,const_pointer);\n",M(this->name_,c_str));
  if(this->has_to_stream_)
    M(out,printf,"void %s_to_stream(const_pointer,pointer);\n",M(this->name_,c_str));
  if(this->has_from_stream_)
    M(out,printf,"void %s_from_stream(pointer,pointer);\n",M(this->name_,c_str));
  M(out,printf,"\n");
}

void yaoocpp_class_print_constructor_prototypes(const_pointer p,yaooc_ofstream_pointer out)
{
  yaoocpp_class_const_pointer this=p;
  M(out,printf,"/* Prototypes for %s constructors */\n",M(this->name_,c_str));
  yaoocpp_item_ptr_vector_const_iterator icon;
  FOR_EACH(icon,this->constructors_) {
    M(((yaoocpp_constructor_const_pointer)*icon),print_prototype,out);
  }
  M(out,printf,"\n");
}

void yaoocpp_class_print_class_prototypes(yaoocpp_item_ptr_vector_const_pointer this,yaooc_ofstream_pointer out,
      const char* this_class,bool print_var_proto,bool is_static)
{
  yaoocpp_item_ptr_vector_const_iterator item;
  FOR_EACH(item,this) {
    if(ISA(*item,yaoocpp_method)) {
      M(*item,print_prototype,out);
    } else {
      if(print_var_proto)
        M(*item,print_prototype,out);
    }
  }
  M(out,printf,"\n");
}

void yaoocpp_class_print_implementation(yaoocpp_item_ptr_vector_const_pointer this,yaooc_ofstream_pointer out,
      const char* this_class,bool print_var_implementation)
{
  yaoocpp_item_ptr_vector_const_iterator item;
  FOR_EACH(item,this) {
    if(ISA(*item,yaoocpp_method)) {
      yaoocpp_method_const_pointer method=(yaoocpp_method_const_pointer)*item;
      if(method->flags_ & (DEFINED_IN_CURRENT_CLASS | OVERRIDEN_IN_CURRENT_CLASS)) {
        M(method,print_implementation,out);
      }
    } else if(print_var_implementation) {
      yaoocpp_variable_const_pointer var=(yaoocpp_variable_const_pointer)*item;
      M(var,print_implementation,out);
    }
  }
}

void yaoocpp_class_print_to_header(const_pointer p,yaooc_ofstream_pointer out)
{
  yaoocpp_class_const_pointer this=p;
  yaoocpp_class_print_class_definition(p,out);
  yaoocpp_class_print_type_info_prototypes(p,out);
  yaoocpp_class_print_constructor_prototypes(p,out);
  M(out,printf,"/* Prototypes for %s class table */\n",M(this->name_,c_str));
  yaoocpp_class_print_class_prototypes(this->table_,out,M(this->name_,c_str),false,false);
//  M(out,printf,"/* Prototypes for %s class instance */\n",M(this->name_,c_str));
//  yaoocpp_class_print_class_prototypes(this->instance_,out,M(this->name_,c_str),false,false);
  M(out,printf,"/* Prototypes for %s protected members */\n",M(this->name_,c_str));
  yaoocpp_class_print_class_prototypes(this->protected_,out,M(this->name_,c_str),true,false);
}

void yaoocpp_class_print_type_info_implementation(const_pointer p,yaooc_ofstream_pointer out)
{
  yaoocpp_class_const_pointer this=p;
  if(this->has_default_ctor_)
    M(out,printf,"void %s_default_ctor(pointer p)\n"
            "{\n"
            "  %s_pointer this=p;\n\n"
            "}\n\n",M(this->name_,c_str),M(this->name_,c_str));
  if(this->has_dtor_)
    M(out,printf,"void %s_dtor(pointer p)\n"
            "{\n"
            "  %s_pointer this=p;\n\n"
            "}\n\n",M(this->name_,c_str),M(this->name_,c_str));
  if(this->has_copy_ctor_)
    M(out,printf,"void %s_copy_ctor(pointer p,const_pointer s)\n"
            "{\n"
            "  %s_pointer this=p;\n"
            "  %s_const_pointer src=s;\n"
            "\n}\n\n",M(this->name_,c_str),M(this->name_,c_str),M(this->name_,c_str));
  if(this->has_assign_)
    M(out,printf,"void %s_assign(pointer p,const_pointer s)\n"
            "{\n"
            "  %s_pointer this=p;\n"
            "  %s_const_pointer src=s;\n"
            "\n}\n\n",M(this->name_,c_str),M(this->name_,c_str),M(this->name_,c_str));
  if(this->has_lt_cmp_)
    M(out,printf,"bool %s_less_than_compare(const_pointer p1,const_pointer p2)\n"
            "{\n"
            "  %s_const_pointer vp1=p1;\n"
            "  %s_const_pointer vp2=p2;\n"
            "  bool ret;\n\n"
            "  return ret;\n"
            "\n}\n",M(this->name_,c_str),M(this->name_,c_str),M(this->name_,c_str));
  if(this->has_to_stream_)
    M(out,printf,"void %s_to_stream(const_pointer p,pointer s)\n"
            "{\n"
            "  %s_const_pointer this=p;\n"
            "  yaooc_ostream_pointer strm=s;\n"
            "\n}\n",M(this->name_,c_str),M(this->name_,c_str));
  if(this->has_from_stream_)
    M(out,printf,"void %s_from_stream(pointer p,pointer s)\n"
            "{\n"
            "  %s_pointer this=p;\n"
            "  yaooc_istream_pointer strm=s;\n"
            "\n}\n",M(this->name_,c_str),M(this->name_,c_str));
  M(out,printf,"\n");
}

void yaoocpp_class_print_constructor_implementation(const_pointer p,yaooc_ofstream_pointer out)
{
  yaoocpp_class_const_pointer this=p;
  yaoocpp_item_ptr_vector_const_iterator icon;
  FOR_EACH(icon,this->constructors_) {
    M(((yaoocpp_constructor_const_pointer)*icon),print_implementation,out);
  }
  M(out,printf,"\n");
}

void yaoocpp_class_print_class_table(const_pointer p,yaooc_ofstream_pointer out)
{
  yaoocpp_class_const_pointer this=p;
  yaoocpp_item_ptr_vector_const_iterator item;
  M(out,printf,"%s_class_table_t %s_class_table = \n{\n",M(this->name_,c_str),M(this->name_,c_str));
  FOR_EACH(item,this->table_) {
    M(*item,print_class_implementation,out);
  }
  M(out,printf,"};\n\n");
}

void yaoocpp_class_print_define_type_info(const_pointer p,yaooc_ofstream_pointer out)
{
  yaoocpp_class_const_pointer this=p;
  M(out,printf,"DEFINE_TYPE_INFO(%s",M(this->name_,c_str));
	M(out,printf,",%c",(this->has_default_ctor_ ? 'Y' : 'N'));
	M(out,printf,",%c",(this->has_dtor_ ? 'Y' : 'N'));
	M(out,printf,",%c",(this->has_copy_ctor_ ? 'Y' : 'N'));
	M(out,printf,",%c",(this->has_assign_ ? 'Y' : 'N'));
	M(out,printf,",%c",(this->has_lt_cmp_ ? 'Y' : 'N'));
	M(out,printf,",%c",(this->has_to_stream_ ? 'Y' : 'N'));
	M(out,printf,",%c",(this->has_from_stream_ ? 'Y' : 'N'));
  M(out,printf,",Y,%s)\n",this->parent_ ? M(this->parent_->name_,c_str) : "NULL");
}

void yaoocpp_class_print_to_source(const_pointer p,yaooc_ofstream_pointer out)
{
  yaoocpp_class_const_pointer this=p;
  M(out,printf,"\n/* %s private members */\n",M(this->name_,c_str));
  yaoocpp_class_print_implementation(this->private_,out,M(this->name_,c_str),true);
  M(out,printf,"\n/* %s type info members */\n",M(this->name_,c_str));
  yaoocpp_class_print_type_info_implementation(p,out);
  M(out,printf,"\n/* Constructors for %s */\n",M(this->name_,c_str));
  yaoocpp_class_print_constructor_implementation(p,out);
  M(out,printf,"\n/* %s protected members */\n",M(this->name_,c_str));
  yaoocpp_class_print_implementation(this->protected_,out,M(this->name_,c_str),true);
  M(out,printf,"\n/* Class table methods for %s */\n",M(this->name_,c_str));
  yaoocpp_class_print_implementation(this->table_,out,M(this->name_,c_str),false);
  M(out,printf,"\n/* Class table for %s */\n",M(this->name_,c_str));
  yaoocpp_class_print_class_table(this,out);
  yaoocpp_class_print_define_type_info(this,out);
  M(out,printf,"\n");
}


/* Class table for yaoocpp_class */
yaoocpp_class_class_table_t yaoocpp_class_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaoocpp_item_class_table,
  .isa = (const char* (*) (const_pointer p)) yaoocpp_class_isa,
  .is_descendant = (bool (*) (const_pointer p,const char*)) yaoocpp_class_is_descendant,
  .swap = (void (*) (pointer p,pointer)) yaoocpp_class_swap,
  .virtual_dtor = (void (*) (pointer p)) yaoocpp_class_virtual_dtor,
  .virtual_less_than_compare = (bool (*) (const_pointer p,const_pointer)) yaoocpp_class_virtual_less_than_compare,
  .dump = (void (*) (const_pointer p,yaooc_ofstream_pointer)) yaoocpp_class_dump,
  .print_prototype = (void (*) (const_pointer p,yaooc_ofstream_pointer)) NULL,
  .print_implementation = (void (*) (const_pointer p,yaooc_ofstream_pointer)) NULL,
  .print_class_prototype = (void (*) (const_pointer p,yaooc_ofstream_pointer)) NULL,
  .print_class_implementation = (void (*) (const_pointer p,yaooc_ofstream_pointer)) NULL,
  .print_to_header = (void (*) (const_pointer p,yaooc_ofstream_pointer)) yaoocpp_class_print_to_header,
  .print_to_source = (void (*) (const_pointer p,yaooc_ofstream_pointer)) yaoocpp_class_print_to_source,
};


DEFINE_TYPE_INFO(yaoocpp_class,Y,N,Y,Y,N,N,N,Y,yaoocpp_item)
/*  End YAOOC PreProcessor generated content */
