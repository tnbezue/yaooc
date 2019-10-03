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
#include <string.h>
#include "template_objects.h"
#include <yaooc/regex.h>
#include <yaooc/pointer_bag.h>


VECTOR_IMPLEMENTATION(yaoocpp_argument,yaoocpp_argument_vector);

/* Private variables implementation for yaoocpp_argument */

/* Private methods prototypes for yaoocpp_argument */

/* Type Info implemmentation for yaoocpp_argument */
void yaoocpp_argument_default_ctor(pointer p)
{
  yaoocpp_argument_pointer this=p;
  newp(&this->type_,yaooc_string);
  newp(&this->name_,yaooc_string);
  newp(&this->array_size_,yaooc_string);
  this->is_array_=false;
}

void yaoocpp_argument_dtor(pointer p)
{
  yaoocpp_argument_pointer this=p;
  deletep(&this->type_,yaooc_string);
  deletep(&this->name_,yaooc_string);
  deletep(&this->array_size_,yaooc_string);
}

void yaoocpp_argument_copy_ctor(pointer p,const_pointer s)
{
  yaoocpp_argument_default_ctor(p);
  yaoocpp_argument_assign(p,s);
}

void yaoocpp_argument_assign(pointer p,const_pointer s)
{
  yaoocpp_argument_pointer this=p;
  yaoocpp_argument_const_pointer src=s;
  assign_static(&this->type_,&src->type_,yaooc_string);
  assign_static(&this->name_,&src->name_,yaooc_string);
  assign_static(&this->array_size_,&src->array_size_,yaooc_string);
  this->is_array_=src->is_array_;
}

/* Constructors implementation for yaoocpp_argument */

/* Private methods implementation for yaoocpp_argument */

/* Protected implementation for yaoocpp_argument */
void yaoocpp_argument_print_type(const_pointer p,ostream_pointer o)
{
  yaoocpp_argument_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf," %s",M(&this->type_,c_str));
  if(this->is_array_) {
    M(ostrm,printf,"[%s]",M(&this->array_size_,c_str));
  }
}

void yaoocpp_argument_print_type_name(const_pointer p,ostream_pointer o)
{
  yaoocpp_argument_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf,"%s %s",M(&this->type_,c_str),M(&this->name_,c_str));
  if(this->is_array_) {
    M(ostrm,printf,"[%s]",M(&this->array_size_,c_str));
  }
}

/* Type info structure for yaoocpp_argument */
DEFINE_TYPE_INFO(yaoocpp_argument,Y,Y,Y,Y,N,N,N,N,NULL);

/* Private variables implementation for yaoocpp_element */

/* Private methods prototypes for yaoocpp_element */

/* Type Info implemmentation for yaoocpp_element */
void yaoocpp_element_default_ctor(pointer p)
{
  yaoocpp_element_pointer this=p;
  newp(&this->name_,yaooc_string);
  this->state_=INITIAL;
}

void yaoocpp_element_dtor(pointer p)
{
  yaoocpp_element_pointer this=p;
  deletep(&this->name_,yaooc_string);
}

void yaoocpp_element_copy_ctor(pointer p,const_pointer s)
{
  yaoocpp_element_default_ctor(p);
  yaoocpp_element_assign(p,s);
}

void yaoocpp_element_assign(pointer p,const_pointer s)
{
  yaoocpp_element_pointer this=p;
  yaoocpp_element_const_pointer src=s;
  assign_static(&this->name_,&src->name_,yaooc_string);
  this->state_=src->state_;
}

bool yaoocpp_element_less_than_compare(const_pointer p1,const_pointer p2)
{
  yaoocpp_element_const_pointer vp1=p1;
  yaoocpp_element_const_pointer vp2=p2;
  return op_lt_static(&vp1->name_,&vp2->name_,yaooc_string);
}

/* Constructors implementation for yaoocpp_element */

/* Private methods implementation for yaoocpp_element */

/* Protected implementation for yaoocpp_element */


/* Table implementation for yaoocpp_element */

/* Class table definition for yaoocpp_element */
yaoocpp_element_class_table_t yaoocpp_element_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "yaoocpp_element_t",
  .swap = (void(*)(pointer,pointer)) yaoocpp_element_swap,
  .print_class_table_definition = (void(*)(const_pointer,ostream_pointer)) yaoocpp_element_print_class_table_definition,
  .print_class_instance_definition = (void(*)(const_pointer,ostream_pointer)) yaoocpp_element_print_class_instance_definition,
  .print_prototype = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_element_print_prototype,
  .print_implementation = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_element_print_implementation,
  .print_class_table_implementation = (void(*)(const_pointer,ostream_pointer,const char*)) yaoocpp_element_print_class_table_implementation,
};

/* Type info structure for yaoocpp_element */
DEFINE_TYPE_INFO(yaoocpp_element,Y,Y,Y,Y,Y,N,N,Y,yaooc_object);

DYNAMIC_POINTER_IMPLEMENTATION(yaoocpp_element,yaoocpp_element_pointer);
VECTOR_IMPLEMENTATION(yaoocpp_element_pointer,yaoocpp_element_pointer_vector);


/* Private variables implementation for yaoocpp_type */

/* Private methods prototypes for yaoocpp_type */

/* Type Info implemmentation for yaoocpp_type */
/* Constructors implementation for yaoocpp_type */

/* Private methods implementation for yaoocpp_type */

/* Protected implementation for yaoocpp_type */

/* Table implementation for yaoocpp_type */
void yaoocpp_type_print_class_table_definition(const_pointer p,ostream_pointer o)
{
  yaoocpp_type_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf,"  %s;\n",M(&this->name_,c_str));
}

/* Class table definition for yaoocpp_type */
yaoocpp_type_class_table_t yaoocpp_type_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaoocpp_element_class_table,
  .type_name_ = (const char*) "yaoocpp_type_t",
  .swap = (void(*)(pointer,pointer)) yaoocpp_type_swap,
  .print_class_table_definition = (void(*)(const_pointer,ostream_pointer)) yaoocpp_type_print_class_table_definition,
  .print_class_instance_definition = (void(*)(const_pointer,ostream_pointer)) yaoocpp_type_print_class_instance_definition,
  .print_prototype = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_type_print_prototype,
  .print_implementation = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_type_print_implementation,
  .print_class_table_implementation = (void(*)(const_pointer,ostream_pointer,const char*)) yaoocpp_type_print_class_table_implementation,
};

/* Type info structure for yaoocpp_type */
DEFINE_TYPE_INFO(yaoocpp_type,N,N,N,N,N,N,N,Y,yaoocpp_element);

/* Private variables implementation for yaoocpp_variable */

/* Private methods prototypes for yaoocpp_variable */

/* Type Info implemmentation for yaoocpp_variable */
void yaoocpp_variable_default_ctor(pointer p)
{
  yaoocpp_variable_pointer this=p;
  yaoocpp_element_default_ctor(p);
  newp(&this->type_,yaooc_string);
  newp(&this->default_value_,yaooc_string);
  M(&this->default_value_,set,"0");
	newp(&this->array_size_,yaooc_string);
	this->is_array_=false;
}

void yaoocpp_variable_dtor(pointer p)
{
  yaoocpp_variable_pointer this=p;
  deletep(&this->type_,yaooc_string);
  deletep(&this->default_value_,yaooc_string);
	deletep(&this->array_size_,yaooc_string);
}

void yaoocpp_variable_copy_ctor(pointer p,const_pointer s)
{
  yaoocpp_variable_default_ctor(p);
  yaoocpp_variable_assign(p,s);
}

void yaoocpp_variable_assign(pointer p,const_pointer s)
{
  yaoocpp_variable_pointer this=p;
  yaoocpp_variable_const_pointer src=s;
  yaoocpp_element_assign(p,s);
  assign_static(&this->type_,&src->type_,yaooc_string);
  assign_static(&this->name_,&src->name_,yaooc_string);
  assign_static(&this->default_value_,&src->default_value_,yaooc_string);
  assign_static(&this->array_size_,&src->array_size_,yaooc_string);
	this->is_array_=src->is_array_;
}

/* Constructors implementation for yaoocpp_variable */

/* Private methods implementation for yaoocpp_variable */

/* Protected implementation for yaoocpp_variable */

/* Table implementation for yaoocpp_variable */
void yaoocpp_variable_print_class_table_definition(const_pointer p,ostream_pointer o)
{
  yaoocpp_variable_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf,"  %s %s",M(&this->type_,c_str),M(&this->name_,c_str));
  if(this->is_array_)
		M(ostrm,printf,"[%s]",M(&this->array_size_,c_str));
  M(ostrm,printf,";\n",M(&this->type_,c_str),M(&this->name_,c_str));
}
/*
void yaoocpp_variable_print_class_instance_definition(const_pointer p,ostream_pointer o)
{
  yaoocpp_variable_const_pointer this=p;
}
*/
void yaoocpp_variable_print_prototype(const_pointer p,ostream_pointer o,const char* class_name,const char* storage_class)
{
  yaoocpp_variable_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf,"%s%s %s_%s",storage_class,M(&this->type_,c_str),class_name,M(&this->name_,c_str));
  if(this->is_array_)
		M(ostrm,printf,"[%s]",M(&this->array_size_,c_str));
  M(ostrm,printf,";\n"); //,M(&this->type_,c_str),M(&this->name_,c_str));
}

void yaoocpp_variable_print_implementation(const_pointer p,ostream_pointer o,const char* class_name,const char* storage_class)
{
  yaoocpp_variable_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf,"%s%s %s_%s",storage_class,M(&this->type_,c_str),class_name,M(&this->name_,c_str));
  if(this->is_array_)
		M(ostrm,printf,"[%s]",M(&this->array_size_,c_str));
  M(ostrm,printf,";\n"); //,M(&this->type_,c_str),M(&this->name_,c_str));
}

void yaoocpp_variable_print_class_table_implementation(const_pointer p,ostream_pointer o,const char* class_name)
{
  yaoocpp_variable_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
//  M(ostrm,printf,"  .%s = (%s) %s,\n",M(&this->name_,c_str),M(&this->type_,c_str),M(&this->default_value_,c_str));
  M(ostrm,printf,"  .%s = (%s",M(&this->name_,c_str),M(&this->type_,c_str));
	if(this->is_array_)
		M(ostrm,printf,"[%s]",M(&this->array_size_,c_str));
  M(ostrm,printf,") %s,\n",M(&this->default_value_,c_str));
}


/* Class table definition for yaoocpp_variable */
yaoocpp_variable_class_table_t yaoocpp_variable_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaoocpp_element_class_table,
  .type_name_ = (const char*) "yaoocpp_variable_t",
  .swap = (void(*)(pointer,pointer)) yaoocpp_variable_swap,
  .print_class_table_definition = (void(*)(const_pointer,ostream_pointer)) yaoocpp_variable_print_class_table_definition,
  .print_class_instance_definition = (void(*)(const_pointer,ostream_pointer)) yaoocpp_variable_print_class_instance_definition,
  .print_prototype = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_variable_print_prototype,
  .print_implementation = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_variable_print_implementation,
  .print_class_table_implementation = (void(*)(const_pointer,ostream_pointer,const char*)) yaoocpp_variable_print_class_table_implementation,
};

/* Type info structure for yaoocpp_variable */
DEFINE_TYPE_INFO(yaoocpp_variable,Y,Y,Y,Y,N,N,N,Y,yaoocpp_element);

#if 0
/* Private variables implementation for yaoocpp_raw_struct_union */

/* Private methods prototypes for yaoocpp_raw_struct_union */

/* Type Info implemmentation for yaoocpp_raw_struct_union */
void yaoocpp_raw_struct_union_default_ctor(pointer p)
{
  yaoocpp_raw_struct_union_pointer this=p;
  yaoocpp_element_default_ctor(this);
  newp(&this->raw_string_,yaooc_string);
}

void yaoocpp_raw_struct_union_dtor(pointer p)
{
  yaoocpp_raw_struct_union_pointer this=p;
  deletep(&this->raw_string_,yaooc_string);
}

void yaoocpp_raw_struct_union_copy_ctor(pointer p,const_pointer s)
{
  yaoocpp_raw_struct_union_default_ctor(p);
  yaoocpp_raw_struct_union_assign(p,s);
}

void yaoocpp_raw_struct_union_assign(pointer p,const_pointer s)
{
  yaoocpp_raw_struct_union_pointer this=p;
  yaoocpp_raw_struct_union_const_pointer src=s;
  yaoocpp_element_assign(this,src);
  assign_static(&this->raw_string_,&src->raw_string_,yaooc_string);
}

/* Constructors implementation for yaoocpp_raw_struct_union */

/* Private methods implementation for yaoocpp_raw_struct_union */

/* Protected implementation for yaoocpp_raw_struct_union */

/* Table implementation for yaoocpp_raw_struct_union */
void yaoocpp_raw_struct_union_print_class_table_definition(const_pointer p,ostream_pointer o)
{
//  yaoocpp_raw_struct_union_const_pointer this=p;
}

void yaoocpp_raw_struct_union_print_class_instance_definition(const_pointer p,ostream_pointer o)
{
  yaoocpp_raw_struct_union_const_pointer this=p;
	yaooc_ostream_pointer ostrm=o;
	const char* ptr=M(&this->raw_string_,c_str);
	M(ostrm,printf,"  ");
	for(;*ptr;ptr++) {
		if(*ptr != '\r') {
			if(*ptr == '\n') {
				M(ostrm,printf,"\n  ");
				for(;*ptr;ptr++)
					if(!isspace(*ptr)) {
						--ptr;
						break;
					}
			} else
				M(ostrm,putchr,*ptr);
		}
	}
	M(ostrm,printf,";\n");
}

void yaoocpp_raw_struct_union_print_prototype(const_pointer p,ostream_pointer o,const char* class_name,const char* storage_class)
{
//  yaoocpp_raw_struct_union_const_pointer this=p;
}

void yaoocpp_raw_struct_union_print_implementation(const_pointer p,ostream_pointer o,const char* class_name,const char* storage_class)
{
//  yaoocpp_raw_struct_union_const_pointer this=p;
}

void yaoocpp_raw_struct_union_print_class_table_implementation(const_pointer p,ostream_pointer o,const char* class_name)
{
//  yaoocpp_raw_struct_union_const_pointer this=p;
}


/* Class table definition for yaoocpp_raw_struct_union */
yaoocpp_raw_struct_union_class_table_t yaoocpp_raw_struct_union_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaoocpp_element_class_table,
  .type_name_ = (const char*) "yaoocpp_raw_struct_union_t",
  .swap = (void(*)(pointer, pointer)) yaoocpp_raw_struct_union_swap,
  .print_class_table_definition = (void(*)(const_pointer, ostream_pointer)) yaoocpp_raw_struct_union_print_class_table_definition,
  .print_class_instance_definition = (void(*)(const_pointer, ostream_pointer)) yaoocpp_raw_struct_union_print_class_instance_definition,
  .print_prototype = (void(*)(const_pointer, ostream_pointer, const char*, const char*)) yaoocpp_raw_struct_union_print_prototype,
  .print_implementation = (void(*)(const_pointer, ostream_pointer, const char*, const char*)) yaoocpp_raw_struct_union_print_implementation,
  .print_class_table_implementation = (void(*)(const_pointer, ostream_pointer, const char*)) yaoocpp_raw_struct_union_print_class_table_implementation,
};

/* Type info structure for yaoocpp_raw_struct_union */
DEFINE_TYPE_INFO(yaoocpp_raw_struct_union,Y,Y,Y,Y,N,N,N,Y,yaoocpp_element);
#endif
/* Private variables implementation for yaoocpp_constructor */

/* Private methods prototypes for yaoocpp_constructor */

/* Type Info implemmentation for yaoocpp_constructor */
void yaoocpp_constructor_default_ctor(pointer p)
{
  yaoocpp_constructor_pointer this=p;
  yaoocpp_element_default_ctor(p);
  newp(&this->arguments_,yaoocpp_argument_vector);
  newp(&this->implementation_method_,yaooc_string);
}

void yaoocpp_constructor_dtor(pointer p)
{
  yaoocpp_constructor_pointer this=p;
  deletep(&this->arguments_,yaoocpp_argument_vector);
  deletep(&this->implementation_method_,yaooc_string);
}

void yaoocpp_constructor_copy_ctor(pointer p,const_pointer s)
{
  yaoocpp_constructor_default_ctor(p);
  yaoocpp_constructor_assign(p,s);
}

void yaoocpp_constructor_assign(pointer p,const_pointer s)
{
  yaoocpp_constructor_pointer this=p;
  yaoocpp_constructor_const_pointer src=s;
  yaoocpp_element_assign(p,s);
  assign_static(&this->arguments_,&src->arguments_,yaoocpp_argument_vector);
  assign_static(&this->implementation_method_,&src->implementation_method_,yaooc_string);
}

/* Constructors implementation for yaoocpp_constructor */

/* Private methods implementation for yaoocpp_constructor */

/* Protected implementation for yaoocpp_constructor */

/* Table implementation for yaoocpp_constructor */
void yaoocpp_constructor_print_prototype(const_pointer p,ostream_pointer o,const char* class_name,const char* storage_class)
{
  yaoocpp_constructor_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  if(M(&this->implementation_method_,size) == 0) {
    M(ostrm,printf,"void %s(pointer,va_list);\n",M(&this->name_,c_str));
  } else {
    M(ostrm,printf,"#define %s %s\n",M(&this->name_,c_str),M(&this->implementation_method_,c_str));
  }
}

void yaoocpp_constructor_print_implementation(const_pointer p,ostream_pointer o,const char* class_name,const char* storage_class)
{
  yaoocpp_constructor_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  if(M(&this->implementation_method_,size) == 0) {
    M(ostrm,printf,"void %s(pointer p,va_list args)\n",M(&this->name_,c_str));
    M(ostrm,printf,"{\n");
    M(ostrm,printf,"  %s_pointer this=p;\n",class_name);
    yaoocpp_argument_vector_const_iterator iarg;
    CFOR_EACH(iarg,&this->arguments_) {
      if(strcmp(M(&iarg->type_,c_str),"...") != 0) {
				M(ostrm,printf,"  ");
				yaoocpp_argument_print_type_name(iarg,o);
				M(ostrm,printf," = va_arg(args,");
				yaoocpp_argument_print_type(iarg,o);
				M(ostrm,printf,");\n");
			}
//        M(ostrm,printf,"  %s %s = va_arg(args,%s);\n",M(&iarg->type_,c_str),M(&iarg->name_,c_str),M(&iarg->type_,c_str));
    }
    M(ostrm,printf,"}\n\n");
  }
}


/* Class table definition for yaoocpp_constructor */
yaoocpp_constructor_class_table_t yaoocpp_constructor_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaoocpp_element_class_table,
  .type_name_ = (const char*) "yaoocpp_constructor_t",
  .swap = (void(*)(pointer,pointer)) yaoocpp_constructor_swap,
  .print_class_table_definition = (void(*)(const_pointer,ostream_pointer)) yaoocpp_constructor_print_class_table_definition,
  .print_class_instance_definition = (void(*)(const_pointer,ostream_pointer)) yaoocpp_constructor_print_class_instance_definition,
  .print_prototype = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_constructor_print_prototype,
  .print_implementation = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_constructor_print_implementation,
  .print_class_table_implementation = (void(*)(const_pointer,ostream_pointer,const char*)) yaoocpp_constructor_print_class_table_implementation,
};

/* Type info structure for yaoocpp_constructor */
DEFINE_TYPE_INFO(yaoocpp_constructor,Y,Y,Y,Y,N,N,N,Y,yaoocpp_element);

/* Private variables implementation for yaoocpp_method */

/* Private methods prototypes for yaoocpp_method */

/* Type Info implemmentation for yaoocpp_method */
void yaoocpp_method_default_ctor(pointer p)
{
  yaoocpp_method_pointer this=p;
  yaoocpp_constructor_default_ctor(p);
  newp(&this->return_type_,yaooc_string);
  this->is_const_=false;

}

void yaoocpp_method_dtor(pointer p)
{
  yaoocpp_method_pointer this=p;
  deletep(&this->return_type_,yaooc_string);
}

void yaoocpp_method_copy_ctor(pointer p,const_pointer s)
{
  yaoocpp_method_default_ctor(p);
  yaoocpp_method_assign(p,s);
}

void yaoocpp_method_assign(pointer p,const_pointer s)
{
  yaoocpp_method_pointer this=p;
  yaoocpp_method_const_pointer src=s;
  yaoocpp_constructor_assign(p,s);
  assign_static(&this->return_type_,&src->return_type_,yaooc_string);
  this->is_const_=src->is_const_;
}

/* Constructors implementation for yaoocpp_method */

/* Private methods implementation for yaoocpp_method */

/* Protected implementation for yaoocpp_method */

/* Table implementation for yaoocpp_method */
void yaoocpp_method_print_class_table_definition(const_pointer p,ostream_pointer o)
{
  yaoocpp_method_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf,"  %s (*%s)(%spointer",M(&this->return_type_,c_str),M(&this->name_,c_str),
        this->is_const_ ? "const_" : "");
  yaoocpp_argument_vector_const_iterator iarg;
  CFOR_EACH(iarg,&this->arguments_) {
		M(ostrm,printf,",");
		yaoocpp_argument_print_type(iarg,ostrm);
//    M(ostrm,printf,",%s",M(&iarg->type_,c_str));
  }
  M(ostrm,printf,");\n");
}

void yaoocpp_method_print_prototype(const_pointer p,ostream_pointer o,const char* class_name,const char* storage_class)
{
  yaoocpp_method_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  if(M(&this->implementation_method_,size) == 0) {
    M(ostrm,printf,"%s%s %s_%s(%spointer",storage_class,M(&this->return_type_,c_str),class_name,M(&this->name_,c_str),
            this->is_const_ ? "const_" : "");
    yaoocpp_argument_vector_const_iterator iarg;
    CFOR_EACH(iarg,&this->arguments_) {
			M(ostrm,printf,",");
			yaoocpp_argument_print_type(iarg,ostrm);
//      M(ostrm,printf,",%s",M(&iarg->type_,c_str));
    }
    M(ostrm,printf,");\n");
  } else {
    M(ostrm,printf,"#define %s_%s %s\n",class_name,M(&this->name_,c_str),M(&this->implementation_method_,c_str));
  }
}

void yaoocpp_method_print_implementation(const_pointer p,ostream_pointer o,const char* class_name,const char* storage_class)
{
  yaoocpp_method_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  if(M(&this->implementation_method_,size) == 0) {
    M(ostrm,printf,"%s%s %s_%s(%spointer p",storage_class,M(&this->return_type_,c_str),class_name,M(&this->name_,c_str),
            (this->is_const_ ? "const_" : ""));
    yaoocpp_argument_vector_const_iterator iarg;
    CFOR_EACH(iarg,&this->arguments_) {
			M(ostrm,printf,",");
			yaoocpp_argument_print_type_name(iarg,ostrm);
//      M(ostrm,printf,",%s %s",M(&iarg->type_,c_str),M(&iarg->name_,c_str));
    }
    M(ostrm,printf,")");
		M(ostrm,printf,"\n{\n"
						"  %s_%spointer this=p;\n",class_name,(this->is_const_ ? "const_": ""));
		if(strcmp(M(&this->return_type_,c_str),"void") != 0)
			M(ostrm,printf,"  %s ret;\n"
										"  return ret;\n",M(&this->return_type_,c_str));
    M(ostrm,printf,"}\n\n");
  }
}

void yaoocpp_method_print_class_table_implementation(const_pointer p,ostream_pointer o,const char* class_name)
{
  yaoocpp_method_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf,"  .%s = (%s(*)(%spointer",M(&this->name_,c_str),M(&this->return_type_,c_str),
        (this->is_const_ ? "const_": ""));
  yaoocpp_argument_vector_const_iterator iarg;
  CFOR_EACH(iarg,&this->arguments_) {
		M(ostrm,printf,",");
		yaoocpp_argument_print_type(iarg,ostrm);
//    M(ostrm,printf,",%s",M(&iarg->type_,c_str));
  }
  M(ostrm,printf,")) %s_%s,\n",class_name,M(&this->name_,c_str));
}


/* Class table definition for yaoocpp_method */
yaoocpp_method_class_table_t yaoocpp_method_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaoocpp_constructor_class_table,
  .type_name_ = (const char*) "yaoocpp_method_t",
  .swap = (void(*)(pointer,pointer)) yaoocpp_method_swap,
  .print_class_table_definition = (void(*)(const_pointer,ostream_pointer)) yaoocpp_method_print_class_table_definition,
  .print_class_instance_definition = (void(*)(const_pointer,ostream_pointer)) yaoocpp_method_print_class_instance_definition,
  .print_prototype = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_method_print_prototype,
  .print_implementation = (void(*)(const_pointer,ostream_pointer,const char*,const char*)) yaoocpp_method_print_implementation,
  .print_class_table_implementation = (void(*)(const_pointer,ostream_pointer,const char*)) yaoocpp_method_print_class_table_implementation,
};

/* Type info structure for yaoocpp_method */
DEFINE_TYPE_INFO(yaoocpp_method,Y,Y,Y,Y,N,N,N,Y,yaoocpp_constructor);

/* Private variables implementation for yaoocpp_container */

/* Private methods prototypes for yaoocpp_container */
typedef enum { PRINT_ANY = 0, PRINT_VAR = 1, PRINT_METHOD = 2, PRINT_BOTH = 3 } print_element_t;
static void yaoocpp_container_print_define_type_info(const_pointer,ostream_pointer,bool);
static void yaoocpp_container_print_type_info_implementation(const_pointer,ostream_pointer);
static void yaoocpp_container_print_element_prototype(const_pointer,ostream_pointer,const char*,
        yaoocpp_element_pointer_vector_const_pointer,print_element_t,const char*);
static void yaoocpp_container_print_element_implementation(const_pointer,ostream_pointer,const char*,yaoocpp_element_pointer_vector_const_pointer,print_element_t,const char*);
static void yaoocpp_container_print_type_info_prototype(const_pointer,ostream_pointer);

/* Type Info implemmentation for yaoocpp_container */
void yaoocpp_container_default_ctor(pointer p)
{
  yaoocpp_container_pointer this=p;
	this->parent_=NULL;
	newp(&this->name_,yaooc_string);
	newp(&this->constructors_,yaoocpp_element_pointer_vector);
	newp(&this->instance_,yaoocpp_element_pointer_vector);
	newp(&this->private_,yaoocpp_element_pointer_vector);
	newp(&this->protected_,yaoocpp_element_pointer_vector);
	newp(&this->static_,yaoocpp_element_pointer_vector);
	this->has_default_ctor_ = false;
	this->has_dtor_ = false;
	this->has_copy_ctor_ = false;
	this->has_assign_ = false;
	this->has_lt_cmp_ = false;
	this->has_to_stream_ = false;
	this->has_from_stream_ = false;
	this->defined_in_top_level_file_ = false;
}

void yaoocpp_container_dtor(pointer p)
{
  yaoocpp_container_pointer this=p;
	deletep(&this->name_,yaooc_string);
	deletep(&this->constructors_,yaoocpp_element_pointer_vector);
	deletep(&this->instance_,yaoocpp_element_pointer_vector);
	deletep(&this->private_,yaoocpp_element_pointer_vector);
	deletep(&this->protected_,yaoocpp_element_pointer_vector);
	deletep(&this->static_,yaoocpp_element_pointer_vector);
}

void yaoocpp_container_copy_ctor(pointer p,const_pointer s)
{
	yaoocpp_container_default_ctor(p);
	yaoocpp_container_assign(p,s);
}

void yaoocpp_container_assign(pointer p,const_pointer s)
{
  yaoocpp_container_pointer this=p;
  yaoocpp_container_const_pointer src=s;
	this->parent_=src->parent_;
  assign_static(&this->name_,&src->name_,yaooc_string);
	assign_static(&this->constructors_,&src->constructors_,yaoocpp_element_pointer_vector);
	assign_static(&this->instance_,&src->instance_,yaoocpp_element_pointer_vector);
	assign_static(&this->private_,&src->private_,yaoocpp_element_pointer_vector);
	assign_static(&this->protected_,&src->protected_,yaoocpp_element_pointer_vector);
	this->has_default_ctor_ = src->has_default_ctor_;
	this->has_dtor_ = src->has_dtor_;
	this->has_copy_ctor_ = src->has_copy_ctor_;
	this->has_assign_ = src->has_assign_;
	this->has_lt_cmp_ = src->has_lt_cmp_;
	this->has_to_stream_ = src->has_to_stream_;
	this->has_from_stream_ = src->has_from_stream_;
	this->defined_in_top_level_file_ = src->defined_in_top_level_file_;
}

bool yaoocpp_container_less_than_compare(const_pointer p1,const_pointer p2)
{
  yaoocpp_container_const_pointer vp1=p1;
  yaoocpp_container_const_pointer vp2=p2;
  return op_lt_static(&vp1->name_,&vp2->name_,yaooc_string);
}

/* Constructors implementation for yaoocpp_container */

/* Private methods implementation for yaoocpp_container */
static void yaoocpp_container_print_define_type_info(const_pointer p,ostream_pointer o,bool has_class_table)
{
  yaoocpp_container_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf,"/* Type info structure for %s */\n",M(&this->name_,c_str));
  if(M(this,is_min_pod)) {
    M(ostrm,printf,"DEFINE_MIN_TYPE_INFO(%s);\n",M(&this->name_,c_str));
  } else if (M(this,is_pod)) {
    M(ostrm,printf,"DEFINE_POD_TYPE_INFO(%s",M(&this->name_,c_str));
    M(ostrm,printf,",%c",this->has_lt_cmp_ ? 'Y' : 'N');
    M(ostrm,printf,",%c",this->has_to_stream_ ? 'Y' : 'N');
    M(ostrm,printf,",%c);\n\n",this->has_from_stream_ ? 'Y' : 'N');
  } else {
    M(ostrm,printf,"DEFINE_TYPE_INFO(%s",M(&this->name_,c_str));
    M(ostrm,printf,",%c",this->has_default_ctor_ ? 'Y' : 'N');
    M(ostrm,printf,",%c",this->has_dtor_ ? 'Y' : 'N');
    M(ostrm,printf,",%c",this->has_copy_ctor_ ? 'Y' : 'N');
    M(ostrm,printf,",%c",this->has_assign_ ? 'Y' : 'N');
    M(ostrm,printf,",%c",this->has_lt_cmp_ ? 'Y' : 'N');
    M(ostrm,printf,",%c",this->has_to_stream_ ? 'Y' : 'N');
    M(ostrm,printf,",%c",this->has_from_stream_ ? 'Y' : 'N');
    M(ostrm,printf,",%c",has_class_table ? 'Y' : 'N' );
    M(ostrm,printf,",%s);\n\n",this->parent_ ? M(&this->parent_->name_,c_str) : "NULL" );
  }
}

static void yaoocpp_container_print_default_ctor_implementation(const_pointer p,ostream_pointer o)
{
  yaoocpp_container_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf,"void %s_default_ctor(pointer p)\n"
                "{\n"
                "  %s_pointer this=p;\n",M(&this->name_,c_str),M(&this->name_,c_str));
  if(this->parent_ && strcmp(M(&this->parent_->name_,c_str),"yaooc_object") != 0) {
    M(ostrm,printf,"  %s_default_ctor(this);\n",M(&this->parent_->name_,c_str));
  }
  yaoocpp_element_pointer_vector_const_iterator i;
  CFOR_EACH(i,&this->instance_) {
    if((*i)->state_ == INITIAL && ISA(*i,yaoocpp_variable)) {
      yaoocpp_variable_pointer ivar=(yaoocpp_variable_pointer)*i;
      if(M(&ivar->type_,ends_with,"*")) {
        M(ostrm,printf,"  this->%s = NULL;\n",M(&ivar->name_,c_str));
      } else if(M(&ivar->type_,ends_with,"_t")) {
        yaooc_string_pointer temp=M(&ivar->type_,substr,0,M(&ivar->type_,size)-2);
        M(ostrm,printf,"  newp(&this->%s,%s);\n",M(&ivar->name_,c_str),M(temp,c_str));
        delete(temp);
      } else {
        M(ostrm,printf,"  this->%s = 0;\n",M(&ivar->name_,c_str));
      }
    }
  }
  M(ostrm,printf,"}\n\n");
}

static void yaoocpp_container_print_dtor_implementation(const_pointer p,ostream_pointer o)
{
  yaoocpp_container_const_pointer this=p;
  pb_init();
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf,"void %s_dtor(pointer p)\n"
                "{\n"
                "  %s_pointer this=p;\n",M(&this->name_,c_str),M(&this->name_,c_str));
  yaoocpp_element_pointer_vector_const_iterator i;
  yaooc_regex_pointer re=pb_new_ctor(yaooc_regex,yaooc_regex_ctor_ccs_int,"(.*)_t\\s+\\*",0);
  CFOR_EACH(i,&this->instance_) {
    if((*i)->state_ == INITIAL && ISA(*i,yaoocpp_variable)) {
      yaoocpp_variable_pointer ivar=(yaoocpp_variable_pointer)*i;
      if(M(&ivar->type_,ends_with,"*")) {
        // If varible is const, then most likely a pointer to an object that was deleted elsewhere
        if(!M(&ivar->type_,starts_with,"const")) {
          yaooc_matchdata_pointer md=pb_save(M(re,match,M(&ivar->type_,c_str),0));
          if(M(md,bool)) {
            M(ostrm,printf,"  if(this->%s)\n"
                           "     delete(this->%s);\n",M(&ivar->name_,c_str),M(&ivar->name_,c_str));
//            delete(md);
          } else {
            M(ostrm,printf,"  if(this->%s)\n"
                           "     FREE(this->%s);\n",M(&ivar->name_,c_str),M(&ivar->name_,c_str));
          }
          M(ostrm,printf,"  this->%s = NULL;\n",M(&ivar->name_,c_str));
        }
      } else if(M(&ivar->type_,ends_with,"_t")) {
        yaooc_string_pointer temp=pb_save(M(&ivar->type_,substr,0,M(&ivar->type_,size)-2));
        M(ostrm,printf,"  deletep(&this->%s,%s);\n",M(&ivar->name_,c_str),M(temp,c_str));
//        delete(temp);
      }
    }
  }
  M(ostrm,printf,"}\n\n");
  pb_exit();
}

static void yaoocpp_container_print_assign_implementation(const_pointer p,ostream_pointer o)
{
  yaoocpp_container_const_pointer this=p;
  pb_init();
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf,"void %s_assign(pointer p,const_pointer s)\n"
                "{\n"
                "  %s_pointer this=p;\n"
                "  %s_const_pointer src=s;\n",M(&this->name_,c_str),M(&this->name_,c_str),M(&this->name_,c_str));
  if(this->parent_ && strcmp(M(&this->parent_->name_,c_str),"yaooc_object") != 0) {
    M(ostrm,printf,"  %s_assign(this,src);\n",M(&this->parent_->name_,c_str));
  }
  yaooc_regex_pointer re=pb_new_ctor(yaooc_regex,yaooc_regex_ctor_ccs_int,"(.*)_t\\s+\\*",0);
  yaoocpp_element_pointer_vector_const_iterator i;
  CFOR_EACH(i,&this->instance_) {
    if((*i)->state_ == INITIAL && ISA(*i,yaoocpp_variable)) {
      yaoocpp_variable_pointer ivar=(yaoocpp_variable_pointer)*i;
      if(M(&ivar->type_,ends_with,"*")) {
        if(M(&ivar->type_,starts_with,"const")) {
          M(ostrm,printf,"  this->%s=src->%s;\n",M(&ivar->name_,c_str),M(&ivar->name_,c_str));
        } else {
//          M(ostrm,printf,"  if(this->%s != NULL) \n",M(&ivar->name_,c_str));
          yaooc_matchdata_pointer md=pb_save(M(re,match,M(&ivar->type_,c_str),0));
//          yaooc_string_pointer temp=M(md,at,1);
          if(M(md,bool)) {
            M(ostrm,printf,"  if(this->%s!=NULL)\n"
                           "    delete(this->%s;\n"
                           "  this->%s = src->%s != NULL ? new_copy(src->%s) : NULL;\n",
                           M(&ivar->name_,c_str),M(&ivar->name_,c_str),M(&ivar->name_,c_str),M(&ivar->name_,c_str));
          } else {
            M(ostrm,printf,"  DO_NOT_KNOW_HOW_TO_ASSIGN(this->%s,src->%s);\n",M(&ivar->name_,c_str),M(&ivar->name_,c_str));
          }
        }
      } else if(M(&ivar->type_,ends_with,"_t")) {
        yaooc_string_pointer temp=pb_save(M(&ivar->type_,substr,0,M(&ivar->type_,size)-2));
        M(ostrm,printf,"  assign_static(&this->%s,&src->%s,%s);\n",M(&ivar->name_,c_str),M(&ivar->name_,c_str),M(temp,c_str));
      } else {
        M(ostrm,printf,"  this->%s = src->%s;\n",M(&ivar->name_,c_str),M(&ivar->name_,c_str));
      }
    }
  }
  M(ostrm,printf,"}\n\n");
  pb_exit();
}

static void yaoocpp_container_print_type_info_implementation(const_pointer p,ostream_pointer o)
{
  yaoocpp_container_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf,"/* Type Info implemmentation for %s */\n",M(&this->name_,c_str));
  if(this->has_default_ctor_)
    yaoocpp_container_print_default_ctor_implementation(this,ostrm);
  if(this->has_dtor_)
    yaoocpp_container_print_dtor_implementation(this,ostrm);
  if(this->has_copy_ctor_)
    M(ostrm,printf,"void %s_copy_ctor(pointer p,const_pointer s)\n"
                  "{\n"
                  "  %s_default_ctor(p);\n"
                  "  %s_assign(p,s);\n"
                  "}\n\n",M(&this->name_,c_str),M(&this->name_,c_str),M(&this->name_,c_str));
  if(this->has_assign_)
    yaoocpp_container_print_assign_implementation(this,ostrm);
/*    M(ostrm,printf,"void %s_assign(pointer p,const_pointer s)\n"
                  "{\n"
                  "  %s_pointer this=p;\n"
                  "  %s_const_pointer src=s;\n"
                  "}\n\n",M(&this->name_,c_str),M(&this->name_,c_str),M(&this->name_,c_str));*/
  if(this->has_lt_cmp_)
    M(ostrm,printf,"bool %s_less_than_compare(const_pointer p1,const_pointer p2)\n"
                  "{\n"
                  "  %s_const_pointer lhs=p1;\n"
                  "  %s_const_pointer rhs=p2;\n"
                  "  bool ret=false;\n"
                  "  return ret;\n"
                  "}\n\n",M(&this->name_,c_str),M(&this->name_,c_str),M(&this->name_,c_str));
  if(this->has_to_stream_)
    M(ostrm,printf,"void %s_to_stream(const_pointer p,ostream_pointer o)\n"
                  "{\n"
                  "  %s_const_pointer this=p;\n"
                  "  yaooc_ostream_pointer ostrm=o;\n"
                  "}\n\n",M(&this->name_,c_str),M(&this->name_,c_str));
  if(this->has_from_stream_)
    M(ostrm,printf,"void %s_from_stream(pointer p,istream_pointer i)\n"
                  "{\n"
                  "  %s_pointer this=p;\n"
                  "  yaooc_istream_pointer istrm=i;\n"
                  "}\n\n",M(&this->name_,c_str),M(&this->name_,c_str));
}


static void yaoocpp_container_print_element_prototype(const_pointer p,ostream_pointer o,const char* sub_section,
      yaoocpp_element_pointer_vector_const_pointer elements,print_element_t pvt, const char* storage_class)
{
  yaoocpp_container_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf,"/* %s prototypes for %s */\n",sub_section,M(&this->name_,c_str));
  yaoocpp_element_pointer_vector_const_iterator iter;
  CFOR_EACH(iter,elements) {
    if((pvt == PRINT_ANY) || ((pvt & PRINT_VAR) && ISA(*iter,yaoocpp_variable))
       || ((pvt & PRINT_METHOD) && ISA(*iter,yaoocpp_method)))
      M(*iter,print_prototype,ostrm,M(&this->name_,c_str),storage_class);

  }
  M(ostrm,printf,"\n");
}

static void yaoocpp_container_print_element_implementation(const_pointer p,ostream_pointer o,const char* sub_section,
      yaoocpp_element_pointer_vector_const_pointer elements,print_element_t pvt, const char* storage_class)
{
  yaoocpp_container_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf,"/* %s implementation for %s */\n",sub_section,M(&this->name_,c_str));
  yaoocpp_element_pointer_vector_const_iterator iter;
  CFOR_EACH(iter,elements) {
    if((pvt == PRINT_ANY) || ((pvt & PRINT_VAR) && ISA(*iter,yaoocpp_variable))
       || ((pvt & PRINT_METHOD) && ISA(*iter,yaoocpp_method))) {
      M(*iter,print_implementation,ostrm,M(&this->name_,c_str),storage_class);
    }
  }
  M(ostrm,printf,"\n");
}

static void yaoocpp_container_print_type_info_prototype(const_pointer p,ostream_pointer o)
{
  yaoocpp_container_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf,"/* Type Info Prototypes for %s */\n",M(&this->name_,c_str));
  if(this->has_default_ctor_)
    M(ostrm,printf,"void %s_default_ctor(pointer);\n",M(&this->name_,c_str));
  else if(this->parent_)
    M(ostrm,printf,"#define %s_default_ctor %s_default_ctor\n",M(&this->name_,c_str),M(&this->parent_->name_,c_str));
  else
    M(ostrm,printf,"#define %s_default_ctor yaooc_do_nothing_default_ctor\n",M(&this->name_,c_str));
  if(this->has_dtor_)
    M(ostrm,printf,"void %s_dtor(pointer);\n",M(&this->name_,c_str));
  else if(this->parent_)
    M(ostrm,printf,"#define %s_dtor %s_dtor\n",M(&this->name_,c_str),M(&this->parent_->name_,c_str));
  else
    M(ostrm,printf,"#define %s_dtor yaooc_do_nothing_dtor\n",M(&this->name_,c_str));
  if(this->has_copy_ctor_)
    M(ostrm,printf,"void %s_copy_ctor(pointer,const_pointer);\n",M(&this->name_,c_str));
  else if(this->parent_)
    M(ostrm,printf,"#define %s_copy_ctor %s_copy_ctor\n",M(&this->name_,c_str),M(&this->parent_->name_,c_str));
  else
    M(ostrm,printf,"#define %s_copy_ctor yaooc_do_nothing_copy_ctor\n",M(&this->name_,c_str));
  if(this->has_assign_)
    M(ostrm,printf,"void %s_assign(pointer,const_pointer);\n",M(&this->name_,c_str));
  else if(this->parent_)
    M(ostrm,printf,"#define %s_assign %s_assign\n",M(&this->name_,c_str),M(&this->parent_->name_,c_str));
  else
    M(ostrm,printf,"#define %s_assign yaooc_do_nothing_assign\n",M(&this->name_,c_str));
  if(this->has_lt_cmp_)
    M(ostrm,printf,"bool %s_less_than_compare(const_pointer,const_pointer);\n",M(&this->name_,c_str));
  if(this->has_to_stream_)
    M(ostrm,printf,"void %s_to_stream(const_pointer,ostream_pointer);\n",M(&this->name_,c_str));
  if(this->has_from_stream_)
    M(ostrm,printf,"void %s_from_stream(pointer,istream_pointer);\n",M(&this->name_,c_str));
  M(ostrm,printf,"\n");
}


/* Protected implementation for yaoocpp_container */

/* Table implementation for yaoocpp_container */
void yaoocpp_container_inherit(pointer p)
{
  yaoocpp_container_pointer this=p;
  if(this->parent_) {
    assign_static(&this->instance_,&this->parent_->instance_,yaoocpp_element_pointer_vector);
    yaoocpp_element_pointer_vector_iterator i;
    FOR_EACH(i,&this->instance_)
      (*i)->state_=INHERITED;
  }
}

bool yaoocpp_container_is_min_pod(const_pointer p)
{
  return false;
}

/* Class table definition for yaoocpp_container */
yaoocpp_container_class_table_t yaoocpp_container_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "yaoocpp_container_t",
  .swap = (void(*)(pointer,pointer)) yaoocpp_container_swap,
  .inherit = (void(*)(pointer)) yaoocpp_container_inherit,
  .is_min_pod = (bool(*)(const_pointer)) yaoocpp_container_is_min_pod,
  .is_pod = (bool(*)(const_pointer)) yaoocpp_container_is_pod,
  .print_to_header = (void(*)(const_pointer,ostream_pointer)) yaoocpp_container_print_to_header,
  .print_to_source = (void(*)(const_pointer,ostream_pointer)) yaoocpp_container_print_to_source,
};

/* Type info structure for yaoocpp_container */
DEFINE_TYPE_INFO(yaoocpp_container,Y,Y,Y,Y,Y,N,N,Y,yaooc_object);

DYNAMIC_POINTER_IMPLEMENTATION(yaoocpp_container,yaoocpp_container_pointer);
VECTOR_IMPLEMENTATION(yaoocpp_container_pointer,yaoocpp_container_pointer_vector);

/* Private variables implementation for yaoocpp_struct */

/* Private methods prototypes for yaoocpp_struct */

/* Type Info implemmentation for yaoocpp_struct */
/* Constructors implementation for yaoocpp_struct */

/* Private methods implementation for yaoocpp_struct */

/* Protected implementation for yaoocpp_struct */

/* Table implementation for yaoocpp_struct */

bool yaoocpp_struct_is_min_pod(const_pointer p)
{
  yaoocpp_struct_const_pointer this=p;
  bool ret = this->parent_ ? yaoocpp_struct_is_min_pod(this->parent_) : true;
  return ret && !this->has_default_ctor_ && !this->has_dtor_ && !this->has_copy_ctor_ && !this->has_assign_ && !this->has_lt_cmp_ && !this->has_to_stream_ && !this->has_from_stream_;
}

bool yaoocpp_struct_is_pod(const_pointer p)
{
  yaoocpp_struct_const_pointer this=p;
  bool ret = this->parent_ ? yaoocpp_struct_is_pod(this->parent_) : true;
  return ret && !this->has_default_ctor_ && !this->has_dtor_ && !this->has_copy_ctor_ && !this->has_assign_;
}

void yaoocpp_struct_print_to_header(const_pointer p,ostream_pointer o)
{
  yaoocpp_struct_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf,"/*\n  Struct Definition for %s\n*/\n",M(&this->name_,c_str));
  if(M(this,is_min_pod)) {
    M(ostrm,printf,"yaooc_min_struct(%s) {\n",M(&this->name_,c_str));
  } else if(M(this,is_pod)) {
    M(ostrm,printf,"yaooc_pod_struct(%s) {\n",M(&this->name_,c_str));
  } else {
    M(ostrm,printf,"yaooc_struct(%s) {\n",M(&this->name_,c_str));
  }
  if(this->parent_)
    M(ostrm,printf,"  %s_t;\n",M(&this->parent_->name_,c_str));
  yaoocpp_element_pointer_vector_const_iterator iter;
  CFOR_EACH(iter,&this->instance_) {
    if((*iter)->state_==INITIAL)
      M(*iter,print_class_instance_definition,ostrm);
  }
  M(ostrm,printf,"};\n\n");
//  yaoocpp_container_print_element_prototype(this,ostrm,"Private",&this->private_);
  yaoocpp_container_print_element_prototype(this,ostrm,"Protected",&this->protected_,PRINT_BOTH,"extern ");
  yaoocpp_container_print_type_info_prototype(this,ostrm);
  yaoocpp_container_print_element_prototype(this,ostrm,"Constructor",&this->constructors_,PRINT_ANY,"");
}

void yaoocpp_struct_print_to_source(const_pointer p,ostream_pointer o)
{
  yaoocpp_struct_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;

  yaoocpp_container_print_element_implementation(this,ostrm,"Private variables",&this->private_,PRINT_VAR,"static ");
  yaoocpp_container_print_element_prototype(this,ostrm,"Private methods",&this->private_,PRINT_METHOD,"static ");
  yaoocpp_container_print_type_info_implementation(this,ostrm);
  yaoocpp_container_print_element_implementation(this,ostrm,"Constructors",&this->constructors_,PRINT_ANY,"");
  yaoocpp_container_print_element_implementation(this,ostrm,"Private methods",&this->private_,PRINT_METHOD,"static ");
  yaoocpp_container_print_element_implementation(this,ostrm,"Protected",&this->protected_,PRINT_BOTH,"");
  yaoocpp_container_print_define_type_info(this,ostrm,false);
}


/* Class table definition for yaoocpp_struct */
yaoocpp_struct_class_table_t yaoocpp_struct_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaoocpp_container_class_table,
  .type_name_ = (const char*) "yaoocpp_struct_t",
  .swap = (void(*)(pointer,pointer)) yaoocpp_struct_swap,
  .inherit = (void(*)(pointer)) yaoocpp_struct_inherit,
  .is_min_pod = (bool(*)(const_pointer)) yaoocpp_struct_is_min_pod,
  .is_pod = (bool(*)(const_pointer)) yaoocpp_struct_is_pod,
  .print_to_header = (void(*)(const_pointer,ostream_pointer)) yaoocpp_struct_print_to_header,
  .print_to_source = (void(*)(const_pointer,ostream_pointer)) yaoocpp_struct_print_to_source,
};

/* Private variables implementation for yaoocpp_container_with_class_table */

/* Private methods prototypes for yaoocpp_container_with_class_table */

/* Type Info implemmentation for yaoocpp_container_with_class_table */
void yaoocpp_container_with_class_table_default_ctor(pointer p)
{
  yaoocpp_container_with_class_table_pointer this=p;
  yaoocpp_container_default_ctor(this);
  newp(&this->table_,yaoocpp_element_pointer_vector);
}

void yaoocpp_container_with_class_table_dtor(pointer p)
{
  yaoocpp_container_with_class_table_pointer this=p;
  deletep(&this->table_,yaoocpp_element_pointer_vector);
}

void yaoocpp_container_with_class_table_copy_ctor(pointer p,const_pointer s)
{
  yaoocpp_container_with_class_table_default_ctor(p);
  yaoocpp_container_with_class_table_assign(p,s);
}

void yaoocpp_container_with_class_table_assign(pointer p,const_pointer s)
{
  yaoocpp_container_with_class_table_pointer this=p;
  yaoocpp_container_with_class_table_const_pointer src=s;
  yaoocpp_container_assign(this,src);
  assign_static(&this->table_,&src->table_,yaoocpp_element_pointer_vector);
}

/* Constructors implementation for yaoocpp_container_with_class_table */

/* Private methods implementation for yaoocpp_container_with_class_table */


/* Protected implementation for yaoocpp_container_with_class_table */

/* Table implementation for yaoocpp_container_with_class_table */
void yaoocpp_container_with_class_table_inherit(pointer p)
{
  yaoocpp_container_with_class_table_pointer this=p;
  if(this->parent_) {
    yaoocpp_container_inherit(this);
    // If inheriting from a class, assign
    yaoocpp_class_t* p=(yaoocpp_class_pointer)this->parent_;
    assign_static(&this->table_,&p->table_,yaoocpp_element_pointer_vector);
    yaoocpp_element_pointer_vector_iterator i;
    FOR_EACH(i,&this->table_) {
      (*i)->state_=INHERITED;
      if(ISA(*i,yaoocpp_method)) {
        yaoocpp_method_pointer method=(yaoocpp_method_pointer)*i;
        M(&method->implementation_method_,set,M(&p->name_,c_str));
        M(&method->implementation_method_,append,"_");
        M(&method->implementation_method_,append,M(&method->name_,c_str));
      } else {
        yaoocpp_variable_pointer var=(yaoocpp_variable_pointer)*i;
        if(strcmp(M(&var->name_,c_str),"parent_class_table_")==0) {
          M(&var->default_value_,set,"&");
          M(&var->default_value_,append,M(&p->name_,c_str));
          M(&var->default_value_,append,"_class_table");
        } else if(strcmp(M(&var->name_,c_str),"type_name_")==0) {
          M(&var->default_value_,set,"\"");
          M(&var->default_value_,append,M(&this->name_,c_str));
          M(&var->default_value_,append,"_t\"");
        }
      }
    }
  }
}

void yaoocpp_container_with_class_table_print_to_header(const_pointer p,ostream_pointer o)
{
//  yaoocpp_container_with_class_table_const_pointer this=p;
}

void yaoocpp_container_with_class_table_print_to_source(const_pointer p,ostream_pointer o)
{
//  yaoocpp_container_with_class_table_const_pointer this=p;
}


/* Class table definition for yaoocpp_container_with_class_table */
yaoocpp_container_with_class_table_class_table_t yaoocpp_container_with_class_table_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaoocpp_container_class_table,
  .type_name_ = (const char*) "yaoocpp_container_with_class_table_t",
  .swap = (void(*)(pointer, pointer)) yaoocpp_container_with_class_table_swap,
  .inherit = (void(*)(pointer)) yaoocpp_container_with_class_table_inherit,
  .is_min_pod = (bool(*)(const_pointer)) yaoocpp_container_with_class_table_is_min_pod,
  .is_pod = (bool(*)(const_pointer)) yaoocpp_container_with_class_table_is_pod,
  .print_to_header = (void(*)(const_pointer, ostream_pointer)) yaoocpp_container_with_class_table_print_to_header,
  .print_to_source = (void(*)(const_pointer, ostream_pointer)) yaoocpp_container_with_class_table_print_to_source,
};

/* Type info structure for yaoocpp_container_with_class_table */
DEFINE_TYPE_INFO(yaoocpp_container_with_class_table,Y,Y,Y,Y,N,N,N,Y,yaoocpp_container);

/* Type info structure for yaoocpp_struct */
DEFINE_TYPE_INFO(yaoocpp_struct,N,N,N,N,N,N,N,Y,yaoocpp_container);

/* Private variables implementation for yaoocpp_union */

/* Private methods prototypes for yaoocpp_union */

/* Type Info implemmentation for yaoocpp_union */

/* Constructors implementation for yaoocpp_union */

/* Private methods implementation for yaoocpp_union */

/* Protected implementation for yaoocpp_union */

/* Table implementation for yaoocpp_union */
void yaoocpp_union_print_to_header(const_pointer p,ostream_pointer o)
{
  yaoocpp_union_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf,"/*\n  Union Definition for %s\n*/\n",M(&this->name_,c_str));
  M(ostrm,printf,"yaooc_union_table(%s) {\n",M(&this->name_,c_str));
  if(this->parent_)
    M(ostrm,printf,"  %s_class_table_t;\n",M(&this->parent_->name_,c_str));
  yaoocpp_element_pointer_vector_const_iterator iter;
  CFOR_EACH(iter,&this->table_) {
    if((*iter)->state_==INITIAL)
      M(*iter,print_class_table_definition,ostrm);
  }
  M(ostrm,printf,"};\n");
  if(this->parent_)
    M(ostrm,printf,"#define %s_parent_class_table ((%s_class_table_t*)(%s_class_table.parent_class_table_))\n",
          M(&this->name_,c_str),M(&this->parent_->name_,c_str),M(&this->name_,c_str));
  M(ostrm,printf,"\nyaooc_union_instance(%s) {\n",M(&this->name_,c_str));
  if(this->parent_)
    M(ostrm,printf,"  %s_class_instance_t;\n",M(&this->parent_->name_,c_str));
  CFOR_EACH(iter,&this->instance_) {
    if((*iter)->state_==INITIAL)
      M(*iter,print_class_instance_definition,ostrm);
  }
  M(ostrm,printf,"};\n\n");
  M(ostrm,printf,"yaooc_union(%s);\n\n",M(&this->name_,c_str));
  yaoocpp_container_print_type_info_prototype(this,ostrm);
  yaoocpp_container_print_element_prototype(this,ostrm,"Constructors",&this->constructors_,PRINT_ANY,"");
  yaoocpp_container_print_element_prototype(this,ostrm,"Table",&this->table_,PRINT_METHOD,"");
  yaoocpp_container_print_element_prototype(this,ostrm,"Protected",&this->protected_,PRINT_BOTH,"extern ");
}

void yaoocpp_union_print_to_source(const_pointer p,ostream_pointer o)
{
  yaoocpp_union_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;

  yaoocpp_container_print_element_implementation(this,ostrm,"Private variables",&this->private_,PRINT_VAR,"static ");
  yaoocpp_container_print_element_prototype(this,ostrm,"Private methods",&this->private_,PRINT_METHOD,"static ");
  yaoocpp_container_print_type_info_implementation(this,ostrm);
  yaoocpp_container_print_element_implementation(this,ostrm,"Constructors",&this->constructors_,PRINT_ANY,"");
  yaoocpp_container_print_element_implementation(this,ostrm,"Private methods",&this->private_,PRINT_METHOD,"static ");
  yaoocpp_container_print_element_implementation(this,ostrm,"Protected",&this->protected_,PRINT_ANY,"");
  yaoocpp_container_print_define_type_info(this,ostrm,false);
}


/* Class table definition for yaoocpp_union */
yaoocpp_union_class_table_t yaoocpp_union_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaoocpp_container_class_table,
  .type_name_ = (const char*) "yaoocpp_union_t",
  .swap = (void(*)(pointer,pointer)) yaoocpp_union_swap,
  .inherit = (void(*)(pointer)) yaoocpp_union_inherit,
  .is_min_pod = (bool(*)(const_pointer)) yaoocpp_union_is_min_pod,
  .is_pod = (bool(*)(const_pointer)) yaoocpp_union_is_pod,
  .print_to_header = (void(*)(const_pointer,ostream_pointer)) yaoocpp_union_print_to_header,
  .print_to_source = (void(*)(const_pointer,ostream_pointer)) yaoocpp_union_print_to_source,
};

/* Type info structure for yaoocpp_union */
DEFINE_TYPE_INFO(yaoocpp_union,N,N,N,N,N,N,N,Y,yaoocpp_container_with_class_table);

/* Private variables implementation for yaoocpp_class */

/* Private methods prototypes for yaoocpp_class */
static void yaoocpp_class_print_class_table_implementation(const_pointer,ostream_pointer);

/* Type Info implemmentation for yaoocpp_class */

/* Constructors implementation for yaoocpp_class */

/* Private methods implementation for yaoocpp_class */
static void yaoocpp_class_print_class_table_implementation(const_pointer p,ostream_pointer o)
{
  yaoocpp_class_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf,"/* Class table definition for %s */\n",M(&this->name_,c_str));
  M(ostrm,printf,"%s_class_table_t %s_class_table = \n{\n",M(&this->name_,c_str),M(&this->name_,c_str));
  yaoocpp_element_pointer_vector_const_iterator i;
  CFOR_EACH(i,&this->table_) {
    M(*i,print_class_table_implementation,ostrm,M(&this->name_,c_str));
  }
  M(ostrm,printf,"};\n\n");
}


/* Protected implementation for yaoocpp_class */

/* Table implementation for yaoocpp_class */
void yaoocpp_class_print_to_header(const_pointer p,ostream_pointer o)
{
  yaoocpp_class_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf,"/*\n  Class Definition for %s\n*/\n",M(&this->name_,c_str));
  M(ostrm,printf,"yaooc_class_table(%s) {\n",M(&this->name_,c_str));
  if(this->parent_)
    M(ostrm,printf,"  %s_class_table_t;\n",M(&this->parent_->name_,c_str));
  yaoocpp_element_pointer_vector_const_iterator iter;
  CFOR_EACH(iter,&this->table_) {
    if((*iter)->state_==INITIAL)
      M(*iter,print_class_table_definition,ostrm);
  }
  M(ostrm,printf,"};\n");
  if(this->parent_)
    M(ostrm,printf,"#define %s_parent_class_table ((%s_class_table_t*)(%s_class_table.parent_class_table_))\n",
          M(&this->name_,c_str),M(&this->parent_->name_,c_str),M(&this->name_,c_str));
  if(M(&this->instance_,size) > 0) {
    M(ostrm,printf,"\nyaooc_class_instance(%s) {\n",M(&this->name_,c_str));
    if(this->parent_ && M(&this->parent_->instance_,size) > 0)
      M(ostrm,printf,"  %s_class_instance_t;\n",M(&this->parent_->name_,c_str));
    CFOR_EACH(iter,&this->instance_) {
      if((*iter)->state_==INITIAL)
        M(*iter,print_class_instance_definition,ostrm);
    }
    M(ostrm,printf,"};\n\n");
    M(ostrm,printf,"yaooc_class(%s);\n\n",M(&this->name_,c_str));
  } else {
    M(ostrm,printf,"yaooc_class_without_instance(%s);\n\n",M(&this->name_,c_str));
  }
  yaoocpp_container_print_type_info_prototype(this,ostrm);
  yaoocpp_container_print_element_prototype(this,ostrm,"Constructors",&this->constructors_,PRINT_ANY,"");
  yaoocpp_container_print_element_prototype(this,ostrm,"Table",&this->table_,PRINT_METHOD,"");
  yaoocpp_container_print_element_prototype(this,ostrm,"Protected",&this->protected_,PRINT_BOTH,"extern ");
}

void yaoocpp_class_print_to_source(const_pointer p,ostream_pointer o)
{
  yaoocpp_class_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  yaoocpp_container_print_element_implementation(this,ostrm,"Private variables",&this->private_,PRINT_VAR,"static ");
  yaoocpp_container_print_element_prototype(this,ostrm,"Private methods",&this->private_,PRINT_METHOD,"static ");
  yaoocpp_container_print_type_info_implementation(this,ostrm);
  yaoocpp_container_print_element_implementation(this,ostrm,"Constructors",&this->constructors_,PRINT_ANY,"");
  yaoocpp_container_print_element_implementation(this,ostrm,"Private methods",&this->private_,PRINT_METHOD,"static ");
  yaoocpp_container_print_element_implementation(this,ostrm,"Protected",&this->protected_,PRINT_BOTH,"");
  yaoocpp_container_print_element_implementation(this,ostrm,"Table",&this->table_,PRINT_METHOD,"");
  yaoocpp_class_print_class_table_implementation(this,ostrm);
  yaoocpp_container_print_define_type_info(this,ostrm,true);
}


/* Class table definition for yaoocpp_class */
yaoocpp_class_class_table_t yaoocpp_class_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaoocpp_container_class_table,
  .type_name_ = (const char*) "yaoocpp_class_t",
  .swap = (void(*)(pointer,pointer)) yaoocpp_class_swap,
  .inherit = (void(*)(pointer)) yaoocpp_class_inherit,
  .is_min_pod = (bool(*)(const_pointer)) yaoocpp_class_is_min_pod,
  .is_pod = (bool(*)(const_pointer)) yaoocpp_class_is_pod,
  .print_to_header = (void(*)(const_pointer,ostream_pointer)) yaoocpp_class_print_to_header,
  .print_to_source = (void(*)(const_pointer,ostream_pointer)) yaoocpp_class_print_to_source,
};

/* Type info structure for yaoocpp_class */
DEFINE_TYPE_INFO(yaoocpp_class,N,N,N,N,N,N,N,Y,yaoocpp_container_with_class_table);
