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

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <yaooc/pointer_bag.h>
#include <yaooc/algorithm.h>
#include <yaooc/fstream.h>
#include <yaooc/sstream.h>
#include "parser.h"

extern yaooc_string_t includes;
extern yaooc_string_t cpp;
extern yaooc_string_t defines;
char current_file[256];


/* Private variables implementation for yaoocpp_parser_exception */

/* Private methods prototypes for yaoocpp_parser_exception */

/* Type Info implemmentation for yaoocpp_parser_exception */
/* Constructors implementation for yaoocpp_parser_exception */

/* Private methods implementation for yaoocpp_parser_exception */

/* Protected implementation for yaoocpp_parser_exception */

/* Table implementation for yaoocpp_parser_exception */

/* Class table definition for yaoocpp_parser_exception */
yaoocpp_parser_exception_class_table_t yaoocpp_parser_exception_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_exception_class_table,
  .type_name_ = (const char*) "yaoocpp_parser_exception_t",
  .swap = (void(*)(pointer,pointer)) yaoocpp_parser_exception_swap,
  .what = (const char*(*)(const_pointer)) yaoocpp_parser_exception_what,
};

/* Type info structure for yaoocpp_parser_exception */
DEFINE_TYPE_INFO(yaoocpp_parser_exception,N,N,N,N,N,N,N,Y,yaooc_exception);

/* Private variables implementation for name_parent */

/* Private methods prototypes for name_parent */

/* Type Info implemmentation for name_parent */
void name_parent_default_ctor(pointer p)
{
  name_parent_pointer this=p;
  this->name_=NULL;
  this->parent_=NULL;
}

void name_parent_dtor(pointer p)
{
  name_parent_pointer this=p;
  if(this->name_)
    delete(this->name_);
}

/* Constructors implementation for name_parent */

/* Private methods implementation for name_parent */

/* Protected implementation for name_parent */

/* Type info structure for name_parent */
DEFINE_TYPE_INFO(name_parent,Y,Y,N,N,N,N,N,N,NULL);

/* Private variables implementation for yaoocpp_parser */

/* Private methods prototypes for yaoocpp_parser */
static void yaoocpp_parser_preprocess(pointer);
static yaoocpp_container_const_pointer yaoocpp_parser_find_class(pointer,const char*);
static name_parent_t yaoocpp_parser_parse_name_parent(pointer);
static bool yaoocpp_parser_parse_default_ctor(pointer,pointer);
static bool yaoocpp_parser_parse_dtor(pointer,pointer);
static bool yaoocpp_parser_parse_copy_ctor(pointer,pointer);
static bool yaoocpp_parser_parse_assign(pointer,pointer);
static bool yaoocpp_parser_parse_less_than_compare(pointer,pointer);
static bool yaoocpp_parser_parse_to_stream(pointer,pointer);
static bool yaoocpp_parser_parse_from_stream(pointer,pointer);
static yaoocpp_argument_pointer yaoocpp_parser_parse_argument(pointer);
static void yaoocpp_parser_parse_type_info(pointer,pointer);
static void yaoocpp_parser_parse_arguments(pointer,yaoocpp_argument_vector_t*);
static bool yaoocpp_parser_parse_constructor(pointer,pointer);
static yaoocpp_element_pointer yaoocpp_parser_parse_method(pointer);
static yaoocpp_element_pointer yaoocpp_parser_parse_variable(pointer);
static yaoocpp_element_pointer yaoocpp_parser_parse_type(pointer);
static bool yaoocpp_parser_parse_sub_section(pointer,const char*,yaoocpp_element_pointer_vector_t*);
static yaoocpp_container_pointer yaoocpp_parser_parse_class(pointer);
static yaoocpp_container_pointer yaoocpp_parser_parse_struct(pointer);
static yaoocpp_container_pointer yaoocpp_parser_parse_union(pointer);
static yaoocpp_container_pointer yaoocpp_parser_parse_section(pointer);

/* Type Info implemmentation for yaoocpp_parser */
#define OUTPUT_MAX 1048576
void yaoocpp_parser_default_ctor(pointer p)
{
  yaoocpp_parser_pointer this=p;
	yaooc_base_parser_default_ctor(p);
	this->is_top_level_file_=true;
  this->buffer_=new_array(char,OUTPUT_MAX);
	this->file_=NULL;
	this->classes_=NULL;
}

void yaoocpp_parser_dtor(pointer p)
{
  yaoocpp_parser_pointer this=p;
  if(this->classes_)
    delete(this->classes_);
  delete(this->buffer_);
}

/* Constructors implementation for yaoocpp_parser */

/* Private methods implementation for yaoocpp_parser */
static void yaoocpp_parser_preprocess(pointer p)
{
  yaoocpp_parser_pointer this=p;
  struct stat st;
  if(stat(this->file_,&st) == 0) {
    yaooc_string_t cpp_cmd;//=YAOOC_STRING_STATIC_DEFAULT_CTOR;
		newp(&cpp_cmd,yaooc_string);
    M(&cpp_cmd,set,M(&cpp,c_str));
    M(&cpp_cmd,append,M(&defines,c_str));
    M(&cpp_cmd,append,M(&includes,c_str));
    M(&cpp_cmd,append," ");
    M(&cpp_cmd,append,this->file_);
    M(&cpp_cmd,append," 2>&1");
    FILE* pipe=popen(M(&cpp_cmd,c_str),"r");
    if(pipe) {
      size_t pos=0;
      while(!feof(pipe) && pos < OUTPUT_MAX) {
        pos+=fread(this->buffer_+pos,1,OUTPUT_MAX-pos,pipe);
      }
      deletep(&cpp_cmd,yaooc_string);
			this->buffer_[pos]=0;
      int rc_system = pclose(pipe);
      if(rc_system != 0) {
				THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
							"Error %d reported by C preprocessor while processing %s.\n",rc_system-255,this->file_));
      }
    } else {
      THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
							"Error opening file %s.\n",this->file_));
    }
  } else {
    THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
            "File %s not found.\n",this->file_));
  }
}

static yaoocpp_container_const_pointer yaoocpp_parser_find_class(pointer p,const char* name)
{
  yaoocpp_parser_pointer this=p;
	yaoocpp_container_pointer_vector_const_iterator i;
	FOR_EACH(i,this->classes_) {
		if(strcmp(name,M(&(*i)->name_,c_str))==0)
			break;
	}
	if(i != M(this->classes_,end))
		return *i;
	return NULL;
}

static name_parent_t yaoocpp_parser_parse_name_parent(pointer p)
{
  yaoocpp_parser_pointer this=p;
	yaooc_terminal_t n=M(this,ident);
	char* name=NULL;
	char* parent=NULL;
	const yaoocpp_container_t* parent_object=NULL;
	if(n.end_) {
		name=M(&n,get_raw_text);
		if(M(this,chr,':').end_) {
			yaooc_terminal_t p=M(this,ident);
			if(p.end_) {
				parent=M(&p,get_raw_text);
				if((parent_object = yaoocpp_parser_find_class(this,parent)) == NULL)
          THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
                "Parent class %s for %s does not exist",parent,name));
				delete(parent);
			} else {
				THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
							"Parent class for %.*s not specified",n.end_-n.beg_,n.beg_));
			}
		}
	}
	return (name_parent_t) { name,parent_object };
}

static bool yaoocpp_parser_parse_default_ctor(pointer p,pointer cc)
{
  yaoocpp_parser_pointer this=p;
  yaoocpp_struct_pointer current_class=cc;
	M(this,rule_start);
	if(M(this,str,M(&current_class->name_,c_str)).end_ && M(this,chr,'(').end_ && M(this,chr,')').end_ && M(this,chr,';').end_) {
		M(this,rule_success);
		current_class->has_default_ctor_=true;
		return true;
	}
	M(this,rule_fail);
	return false;
}

static bool yaoocpp_parser_parse_dtor(pointer p,pointer cc)
{
  yaoocpp_parser_pointer this=p;
  yaoocpp_struct_pointer current_class=cc;
	M(this,rule_start);
	if(M(this,chr,'~').end_ && M(this,str,M(&current_class->name_,c_str)).end_ &&
						M(this,chr,'(').end_ && M(this,chr,')').end_ && M(this,chr,';').end_) {
		M(this,rule_success);
		current_class->has_dtor_=true;
		return true;
	}
	M(this,rule_fail);
	return false;
}

static bool yaoocpp_parser_parse_copy_ctor(pointer p,pointer cc)
{
  yaoocpp_parser_pointer this=p;
  yaoocpp_struct_pointer current_class=cc;
	M(this,rule_start);
	if(M(this,str,M(&current_class->name_,c_str)).end_ && M(this,chr,'(').end_ &&
						M(this,str,M(&current_class->name_,c_str)).end_ && M(this,chr,')').end_ && M(this,chr,';').end_) {
		M(this,rule_success);
		current_class->has_copy_ctor_=true;
		return true;
	}
	M(this,rule_fail);
	return false;
}

static bool yaoocpp_parser_parse_assign(pointer p,pointer cc)
{
  yaoocpp_parser_pointer this=p;
  yaoocpp_struct_pointer current_class=cc;
	M(this,rule_start);
	if(M(this,str,"operator").end_ && M(this,chr,'=').end_ &&
						M(this,chr,'(').end_ && M(this,chr,')').end_ && M(this,chr,';').end_) {
		M(this,rule_success);
		current_class->has_assign_=true;
		return true;
	}
	M(this,rule_fail);
	return false;
}

static bool yaoocpp_parser_parse_less_than_compare(pointer p,pointer cc)
{
  yaoocpp_parser_pointer this=p;
  yaoocpp_struct_pointer current_class=cc;
	M(this,rule_start);
	if(M(this,str,"operator").end_ && M(this,chr,'<').end_ &&
						M(this,chr,'(').end_ && M(this,chr,')').end_ && M(this,chr,';').end_) {
		M(this,rule_success);
		current_class->has_lt_cmp_=true;
		return true;
	}
	M(this,rule_fail);
	return false;
}

static bool yaoocpp_parser_parse_to_stream(pointer p,pointer cc)
{
  yaoocpp_parser_pointer this=p;
  yaoocpp_struct_pointer current_class=cc;
	M(this,rule_start);
	if(M(this,str,"operator").end_ && M(this,str,"<<").end_ &&
						M(this,chr,'(').end_ && M(this,chr,')').end_ && M(this,chr,';').end_) {
		M(this,rule_success);
		current_class->has_to_stream_=true;
		return true;
	}
	M(this,rule_fail);
	return false;
}

static bool yaoocpp_parser_parse_from_stream(pointer p,pointer cc)
{
  yaoocpp_parser_pointer this=p;
  yaoocpp_struct_pointer current_class=cc;
	M(this,rule_start);
	if(M(this,str,"operator").end_ && M(this,str,">>").end_ &&
						M(this,chr,'(').end_ && M(this,chr,')').end_ && M(this,chr,';').end_) {
		M(this,rule_success);
		current_class->has_from_stream_=true;
		return true;
	}
	M(this,rule_fail);
	return false;
}

static yaoocpp_argument_pointer yaoocpp_parser_parse_argument(pointer p)
{
  yaoocpp_parser_pointer this=p;
	yaoocpp_argument_t* arg=new(yaoocpp_argument);
	M(this,rule_start);
	yaooc_terminal_t t;
	while(true) {
		if((t=M(this,ident)).end_) {
			if(M(&arg->type_,size) == 0) {
        // Type is set first
					M(&arg->type_,setn,t.beg_,t.end_-t.beg_);
			} else {
				if(M(&arg->name_,size) == 0) { // Type already specified, assume this is name
					M(&arg->name_,setn,t.beg_,t.end_-t.beg_);
				} else { // present name is actually part of type
          M(&arg->type_,append," ");
          M(&arg->type_,append,M(&arg->name_,c_str));
          M(&arg->name_,setn,t.beg_,t.end_-t.beg_);
        }
			}
		} else if(M(this,chr,'*').end_) {
			if(M(&arg->type_,size)>0) {
				if(M(&arg->name_,size) > 0) {
					M(&arg->type_,append," ");
					M(&arg->type_,append,M(&arg->name_,c_str));
					M(&arg->name_,clear);
				}
				M(&arg->type_,append,"*");
			} else { // * is first, error
				THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
							"Invalid argument/type specification"));
			}
		} else if(M(this,str,"...").end_) {
			if(M(&arg->type_,size)>0)
				THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
							"Invalid argument/type specification"));
			M(&arg->type_,set,"...");
			break;
		} else
			break;
	}
//  printf("Type: X%sX  Name: Y%sY\n",M(&arg->type_,c_str),M(&arg->name_,c_str));
  if((M(&arg->type_,size)>0 && M(&arg->name_,size) > 0)) {
		M(this,rule_success);
    if(M(this,chr,'[').end_ && ((t=M(this,ident)).end_ || (t=M(this,integer)).end_) && M(this,chr,']').end_) {
      M(&arg->array_size_,setn,t.beg_,t.end_-t.beg_);
      arg->is_array_=true;
    }
  } else if(strcmp(M(&arg->type_,c_str),"...")==0) {
    M(this,rule_success);
	} else {
		M(this,rule_fail);
		delete(arg);
		arg=NULL;
	}
	return arg;

}

static void yaoocpp_parser_parse_type_info(pointer p,pointer cc)
{
  yaoocpp_parser_pointer this=p;
  while(true) {
    if(!yaoocpp_parser_parse_default_ctor(this,cc)) {
      if(!yaoocpp_parser_parse_dtor(this,cc)) {
        if(!yaoocpp_parser_parse_copy_ctor(this,cc)) {
          if(!yaoocpp_parser_parse_assign(this,cc)) {
            if(!yaoocpp_parser_parse_less_than_compare(this,cc)) {
              if(!yaoocpp_parser_parse_to_stream(this,cc)) {
                if(!yaoocpp_parser_parse_from_stream(this,cc)) {
                  if(!yaoocpp_parser_parse_constructor(this,cc)) {
                    break;
                  }
                }
              }
            }
          }
        }
      }
    }
  }

}

static void yaoocpp_parser_parse_arguments(pointer p,yaoocpp_argument_vector_t* args)
{
  yaoocpp_parser_pointer this=p;
  PB_INIT;
	while(true) {
		yaoocpp_argument_pointer arg=PB_SAVE(yaoocpp_parser_parse_argument(p));
		if(!arg)
			break;
		M(args,push_back,arg);
		if(M(this,chr,',').end_==NULL)
			break;
	}
  PB_EXIT;
}

static bool yaoocpp_parser_parse_constructor(pointer p,pointer cc)
{
  yaoocpp_parser_pointer this=p;
  yaoocpp_container_pointer current_class=cc;
  bool rule_ok=false;
	M(this,rule_start);
	yaooc_terminal_t name;
	const char* cp=this->current_pos_;
	if(M(this,str,M(&current_class->name_,c_str)).end_ && (name=M(this,ident)).end_ && M(this,chr,'(').end_) {
		yaoocpp_element_pointer con=new(yaoocpp_constructor);
		M(&((yaoocpp_constructor_pointer)con)->name_,setn,cp,name.end_-cp);
		yaoocpp_parser_parse_arguments(this,&((yaoocpp_constructor_pointer)con)->arguments_);
		if(M(this,chr,')').end_) {
			if(M(this,chr,'=').end_ && (name=M(this,ident)).end_) {
				M(&((yaoocpp_constructor_pointer)con)->implementation_method_,setn,name.beg_,name.end_-name.beg_);
			}
			if(M(this,chr,';').end_) {
				M(this,rule_success);
        M(&current_class->constructors_,push_back,&con);
        rule_ok=true;
			}
		}
		delete(con);
	}
	rule_ok ? M(this,rule_success) : M(this,rule_fail);
	return rule_ok;
}

static yaoocpp_element_pointer yaoocpp_parser_parse_method(pointer p)
{
  yaoocpp_parser_pointer this=p;
  M(this,rule_start);
  bool rule_ok=false;
  yaoocpp_method_t* method=NULL;
  yaoocpp_argument_pointer arg=(yaoocpp_argument_pointer)yaoocpp_parser_parse_argument(p);
  if(arg && !arg->is_array_) {
    if(M(this,chr,'(').end_) {
      method=new(yaoocpp_method);
      M(&method->return_type_,set,M(&arg->type_,c_str));
      M(&method->name_,set,M(&arg->name_,c_str));
      yaoocpp_parser_parse_arguments(this,&method->arguments_);
      if(M(this,chr,')').end_) {
        if(M(this,str,"const").end_)
          method->is_const_=true;
        yaooc_terminal_t name;
        if(M(this,chr,'=').end_) {
          if((name=M(this,ident)).end_) {
            M(&method->implementation_method_,setn,name.beg_,name.end_-name.beg_);
          } else {
            THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
              "Error while processing method %s\n",M(&arg->name_,c_str)));
          }
        }
        if(M(this,chr,';').end_) {
          rule_ok=true;
        } else {
          THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
            "Error while processing method %s\n",M(&arg->name_,c_str)));
        }
      } else {
        delete(method);
        THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
					"Error while processing method %s\n",M(&arg->name_,c_str)));
      }
    }
    delete(arg);
	}
  if(rule_ok)
    M(this,rule_success);
  else
    M(this,rule_fail);
  return (yaoocpp_element_pointer)method;
}

static yaoocpp_element_pointer yaoocpp_parser_parse_variable(pointer p)
{
  yaoocpp_parser_pointer this=p;
  M(this,rule_start);
  yaoocpp_variable_t* var=NULL;
  yaoocpp_argument_pointer arg=(yaoocpp_argument_pointer)yaoocpp_parser_parse_argument(p);
  if(arg) {
    yaooc_terminal_t value=default_terminal;
    if(M(this,chr,'=').end_) {
      value=M(this,string_until_chrs,";");
    }
    if(M(this,chr,';').end_) {
      var=new(yaoocpp_variable);
      M(&var->type_,set,M(&arg->type_,c_str));
      M(&var->name_,set,M(&arg->name_,c_str));
			assign_static(&var->array_size_,&arg->array_size_,yaooc_string);
			var->is_array_=arg->is_array_;
      if(value.end_)
        M(&var->default_value_,setn,value.beg_,value.end_-value.beg_);
      else
        M(&var->default_value_,set,"0");
      M(this,rule_success);
      delete(arg);
      return (yaoocpp_element_pointer)var;
    }
	}
	M(this,rule_fail);
  return (yaoocpp_element_pointer)NULL;
}

static yaoocpp_element_pointer yaoocpp_parser_parse_type(pointer p)
{
  yaoocpp_parser_pointer this=p;
  yaoocpp_type_t* ret = NULL;
  yaooc_terminal_t r;
  M(this,rule_start);
  if((r=M(this,ident)).end_ && M(this,chr,';').end_) {
    ret=new(yaoocpp_type);
    M(&ret->name_,setn,r.beg_,r.end_-r.beg_);
  }
  if(ret)
    M(this,rule_success);
  else
    M(this,rule_fail);
  return (yaoocpp_element_pointer) ret;
}

static bool yaoocpp_parser_parse_sub_section(pointer p,const char* section,yaoocpp_element_pointer_vector_t* element_vector)
{
  yaoocpp_parser_pointer this=p;
  PB_INIT;
  bool ret=false;
  if(M(this,str,section).end_ && M(this,chr,':').end_) {
    while(true) {
      yaoocpp_element_t* mp;
      if((mp=PB_SAVE(yaoocpp_parser_parse_method(this)))!=NULL) {
        yaoocpp_element_pointer_pointer orig=yaooc_find(yaoocpp_element_pointer,M(element_vector,begin),M(element_vector,end),&mp);
        if(orig == M(element_vector,end))
          M(element_vector,push_back,&mp);
        else {
          ((yaoocpp_method_pointer)*orig)->state_=OVERRIDDEN;
          M(&((yaoocpp_method_pointer)*orig)->implementation_method_,clear);
        }
      } else if((mp=PB_SAVE(yaoocpp_parser_parse_variable(this)))!=NULL) {
        if(yaooc_find(yaoocpp_element_pointer,M(element_vector,begin),M(element_vector,end),&mp) == M(element_vector,end))
          M(element_vector,push_back,&mp);
        else
          THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
							"Duplicate variable %s defined\n",M(&((yaoocpp_variable_pointer)mp)->name_,c_str)));
      } else if((mp=PB_SAVE(yaoocpp_parser_parse_type(this)))!=NULL) {
        M(element_vector,push_back,&mp);
      } else
        break;
    }
    ret=true;
  }
  PB_EXIT;
  return ret;
}

static yaoocpp_container_pointer yaoocpp_parser_parse_class(pointer p)
{
  yaoocpp_parser_pointer this=p;
	yaoocpp_class_t* ret=NULL;
	name_parent_t np=yaoocpp_parser_parse_name_parent(this);
	if(np.name_) {
		ret=new(yaoocpp_class);
    ret->defined_in_top_level_file_=this->is_top_level_file_;
		M(&ret->name_,set,np.name_);
		if(strcmp(np.name_,"yaooc_object")==0) {
			if(np.parent_)
				THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
							"Parent is defined for yaooc_object"));
		} else if(np.parent_ == NULL) { // If not defined, inherit from yaooc_object
      if((np.parent_ = yaoocpp_parser_find_class(this,"yaooc_object")) == NULL)
        THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
            "In defintion of class %s, parent class yaooc_object is not defined.",np.name_));
		}
		ret->parent_=np.parent_;
    yaoocpp_class_inherit(ret);
		if(M(this,chr,'{' ).end_) {
			yaoocpp_parser_parse_type_info(this,ret);
      while(true) {
        if(!yaoocpp_parser_parse_sub_section(this,"table",&ret->table_))
          if(!yaoocpp_parser_parse_sub_section(this,"instance",&ret->instance_))
            if(!yaoocpp_parser_parse_sub_section(this,"protected",&ret->protected_))
              if(!yaoocpp_parser_parse_sub_section(this,"private",&ret->private_))
                break;
      }
			if(!(M(this,chr,'}').end_ && M(this,chr,';').end_)) {
				THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
							"Error parsing %s class.",np.name_));
			}
		}
    delete(np.name_);
	}
	return (yaoocpp_container_pointer) ret;
}

static yaoocpp_container_pointer yaoocpp_parser_parse_struct(pointer p)
{
  yaoocpp_parser_pointer this=p;
	yaoocpp_struct_t* ret=NULL; //new(yaoocpp_struct);
	name_parent_t np=yaoocpp_parser_parse_name_parent(this);
	if(np.name_) {
		if(strcmp(np.name_,"yaooc_object")==0) {
			THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
						"yaooc_object is defined as a struct"));
		}
		ret=new(yaoocpp_struct);
    ret->defined_in_top_level_file_=this->is_top_level_file_;
		M(&ret->name_,set,np.name_);
		ret->parent_=np.parent_;
    yaoocpp_struct_inherit(ret);
		if(M(this,chr,'{').end_) {
			yaoocpp_parser_parse_type_info(this,ret);
      while(true) {
        if(!yaoocpp_parser_parse_sub_section(this,"instance",&ret->instance_))
          if(!yaoocpp_parser_parse_sub_section(this,"protected",&ret->protected_))
            if(!yaoocpp_parser_parse_sub_section(this,"private",&ret->private_))
              break;
      }
			if(!(M(this,chr,'}').end_ && M(this,chr,';').end_)) {
				THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
							"Error parsing %s struct.",np.name_));
			}
		}
    delete(np.name_);
	}
	return (yaoocpp_container_pointer) ret;
}

static yaoocpp_container_pointer yaoocpp_parser_parse_union(pointer p)
{
  yaoocpp_parser_pointer this=p;
	yaoocpp_union_t* ret=NULL;
	name_parent_t np=yaoocpp_parser_parse_name_parent(this);
	if(np.name_) {
		if(strcmp(np.name_,"yaooc_object")==0) {
			THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
						"yaooc_object is defined as a union"));
		}
		ret=new(yaoocpp_union);
    ret->defined_in_top_level_file_=this->is_top_level_file_;
		M(&ret->name_,set,np.name_);
		if(np.parent_ == NULL) { // If not defined, inherit from yaooc_object
      if((np.parent_ = yaoocpp_parser_find_class(this,"yaooc_object")) == NULL)
        THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
            "In defintion of union %s, parent class yaooc_object is not defined.",np.name_));
		}
		ret->parent_=np.parent_;
    yaoocpp_union_inherit(ret);
		if(M(this,chr,'{' ).end_) {
			yaoocpp_parser_parse_type_info(this,ret);
      while(true) {
        if(!yaoocpp_parser_parse_sub_section(this,"table",&ret->table_))
          if(!yaoocpp_parser_parse_sub_section(this,"instance",&ret->instance_))
            if(!yaoocpp_parser_parse_sub_section(this,"protected",&ret->protected_))
              if(!yaoocpp_parser_parse_sub_section(this,"private",&ret->private_))
                break;
      }
			if(!(M(this,chr,'}').end_ && M(this,chr,';').end_)) {
				THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
							"Error parsing %s union.",np.name_));
			}
		}
    delete(np.name_);
	}
	return (yaoocpp_container_pointer) ret;
#if 0
	name_parent_t np=yaoocpp_parser_parse_name_parent(this);
	if(np.name_) {
		ret=new(yaoocpp_union);
    ret->defined_in_top_level_file_=this->is_top_level_file_;
		M(&ret->name_,set,np.name_);
		ret->parent_=np.parent_;
    yaoocpp_union_inherit(ret);
		if(M(this,chr,'{').end_) {
			yaoocpp_parser_parse_type_info(this,ret);
      while(true) {
        if(!yaoocpp_parser_parse_sub_section(this,"table",&ret->table_))
          if(!yaoocpp_parser_parse_sub_section(this,"instance",&ret->instance_))
            if(!yaoocpp_parser_parse_sub_section(this,"protected",&ret->protected_))
              if(!yaoocpp_parser_parse_sub_section(this,"private",&ret->private_))
                break;
      }
			if(!(M(this,chr,'}').end_ && M(this,chr,';').end_)) {
				THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
							"Error parsing %s union.",np.name_));
			}
		}
    delete(np.name_);
	}
	return (yaoocpp_container_pointer) ret;
#endif
}

static yaoocpp_container_pointer yaoocpp_parser_parse_section(pointer p)
{
  yaoocpp_parser_pointer this=p;
	switch(M(this,str_choices,"class","struct","union",NULL))
	{
		case 0:
			return yaoocpp_parser_parse_class(this);
			break;

		case 1:
			return yaoocpp_parser_parse_struct(this);
			break;

		case 2:
			return yaoocpp_parser_parse_union(this);
			break;

	}
	return NULL;
}


/* Protected implementation for yaoocpp_parser */

/* Table implementation for yaoocpp_parser */

yaooc_terminal_t yaoocpp_parser_custom_whitespace(pointer p)
{
  yaoocpp_parser_pointer this=p;
  yaooc_terminal_t ret =default_terminal;
  ret.beg_=this->current_pos_;
  if(*this->current_pos_=='#') {
    int n,ln=0;
    n=sscanf(this->current_pos_+1,"%d \"%255[^\"]",&ln,current_file);
    if(n == 2) {
//      M(cout,printf,"%d %s\n",ln,current_file);
      this->current_pos_+=2;
      this->line_no_=ln-1;
      this->is_top_level_file_=strcmp(this->file_,current_file)==0;
      for(;*this->current_pos_!=0;this->current_pos_++) {
        if(*this->current_pos_=='\n')
          break;
      }
      ret.end_=this->current_pos_;
    }
  }
  return ret;
}

void yaoocpp_parser_parse_file(pointer p,const char* file)
{
  yaoocpp_parser_pointer this=p;
	PB_INIT;
	this->file_=file;
  if(this->classes_)
    delete(this->classes_);
	this->classes_=new(yaoocpp_container_pointer_vector);
	yaoocpp_parser_preprocess(this);
/*	char *beg=this->buffer_;
	char *ptr=strstr(beg,"\n%h");
	this->header_text_=NULL;
	if(ptr!=NULL) {
		this->header_text_=beg;
		*ptr=0;
		beg=ptr+3;
	}
	this->source_text_= NULL;
	if((ptr=strstr(beg,"\n%c")) != NULL) {
		this->source_text_=beg;
		*ptr=0;
		beg=ptr+3;
	}*/
  M(this,set_parse_string,this->buffer_);
  M(this,set_whitespace_types,CRLF|CUSTOM_WHITESPACE);
  M(this,whitespace);
	while(true) {
		yaoocpp_container_pointer klass=PB_SAVE(yaoocpp_parser_parse_section(this));
		if(!klass)
			break;
		yaooc_object_t* cp=yaooc_find(yaoocpp_container_pointer,M(this->classes_,begin),M(this->classes_,end),&klass);
		if(cp == M(this->classes_,end))
			M(this->classes_,push_back,&klass);
		else {
			THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
						"Duplicate class %s found in file %s.\n",M(&((yaoocpp_class_pointer)klass)->name_,c_str),file));
		}
//		delete(klass);
	}
	if(*this->current_pos_ !=0) {
			THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
						"Error processing file %s on or before line %d near %s.\n",file,this->line_no_,this->current_pos_));
	}
	PB_EXIT;
//	return this->classes_;
}


/* Class table definition for yaoocpp_parser */
yaoocpp_parser_class_table_t yaoocpp_parser_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_base_parser_class_table,
  .type_name_ = (const char*) "yaoocpp_parser_t",
  .swap = (void(*)(pointer,pointer)) yaoocpp_parser_swap,
  .set_parse_string = (void(*)(pointer,const char*)) yaoocpp_parser_set_parse_string,
  .rule_start = (void(*)(pointer)) yaoocpp_parser_rule_start,
  .rule_success = (void(*)(pointer)) yaoocpp_parser_rule_success,
  .rule_fail = (void(*)(pointer)) yaoocpp_parser_rule_fail,
  .eos = (yaooc_terminal_t(*)(pointer)) yaoocpp_parser_eos,
  .string_until_chrs = (yaooc_terminal_t(*)(pointer,const char*)) yaoocpp_parser_string_until_chrs,
  .string_while_chrs = (yaooc_terminal_t(*)(pointer,const char*)) yaoocpp_parser_string_while_chrs,
  .string_until_eol = (yaooc_terminal_t(*)(pointer)) yaoocpp_parser_string_until_eol,
  .shell_comment = (yaooc_terminal_t(*)(pointer)) yaoocpp_parser_shell_comment,
  .c_comment = (yaooc_terminal_t(*)(pointer)) yaoocpp_parser_c_comment,
  .cpp_comment = (yaooc_terminal_t(*)(pointer)) yaoocpp_parser_cpp_comment,
  .custom_whitespace = (yaooc_terminal_t(*)(pointer)) yaoocpp_parser_custom_whitespace,
  .set_whitespace_types = (void(*)(pointer,uint32_t)) yaoocpp_parser_set_whitespace_types,
  .get_whitespace_types = (uint32_t(*)(pointer)) yaoocpp_parser_get_whitespace_types,
  .whitespace = (int(*)(pointer)) yaoocpp_parser_whitespace,
  .chr = (yaooc_terminal_t(*)(pointer,char)) yaoocpp_parser_chr,
  .chr_choices = (int(*)(pointer,const char*)) yaoocpp_parser_chr_choices,
  .str = (yaooc_terminal_t(*)(pointer,const char*)) yaoocpp_parser_str,
  .str_choices = (int(*)(pointer,...)) yaoocpp_parser_str_choices,
  .digits = (yaooc_terminal_t(*)(pointer)) yaoocpp_parser_digits,
  .hexdigits = (yaooc_terminal_t(*)(pointer)) yaoocpp_parser_hexdigits,
  .integer = (yaooc_terminal_t(*)(pointer)) yaoocpp_parser_integer,
  .hexinteger = (yaooc_terminal_t(*)(pointer)) yaoocpp_parser_hexinteger,
  .real = (yaooc_terminal_t(*)(pointer)) yaoocpp_parser_real,
  .ident = (yaooc_terminal_t(*)(pointer)) yaoocpp_parser_ident,
  .regex = (yaooc_terminal_t(*)(pointer,const char*,uint32_t,uint32_t)) yaoocpp_parser_regex,
  .quoted_string = (yaooc_terminal_t(*)(pointer,char)) yaoocpp_parser_quoted_string,
  .single_quoted_string = (yaooc_terminal_t(*)(pointer)) yaoocpp_parser_single_quoted_string,
  .double_quoted_string = (yaooc_terminal_t(*)(pointer)) yaoocpp_parser_double_quoted_string,
  .bare_string = (yaooc_terminal_t(*)(pointer)) yaoocpp_parser_bare_string,
  .string_until_matching_chr = (yaooc_terminal_t(*)(pointer,char,char)) yaoocpp_parser_string_until_matching_chr,
  .result = (yaooc_base_parser_result_t(*)(const_pointer)) yaoocpp_parser_result,
  .parse_file = (void(*)(pointer,const char*)) yaoocpp_parser_parse_file,
};

/* Type info structure for yaoocpp_parser */
DEFINE_TYPE_INFO(yaoocpp_parser,Y,Y,N,N,N,N,N,Y,yaooc_base_parser);

