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
#include "class_parser.h"

extern yaooc_string_pointer includes;
extern yaooc_string_pointer cpp;
//extern yaooc_string_pointer defines;

char current_file[256];

yaooc_terminal_t yaoocpp_class_parser_custom_whitespace(pointer p)
{
  yaoocpp_class_parser_pointer this=p;
  yaooc_terminal_t ret =default_terminal;
  ret.beg_=this->current_pos_;
  if(*this->current_pos_=='#') {
    int n,ln=0;
    n=sscanf(this->current_pos_+1,"%d \"%255[^\"]",&ln,current_file);
    if(n == 2) {
//      M(cout,printf,"%d %s\n",ln,current_file);
      this->current_pos_+=2;
      this->line_no_=ln-1;
      this->is_top_level_file_=strcmp(M(this->file_,c_str),current_file)==0;
      for(;*this->current_pos_!=0;this->current_pos_++) {
        if(*this->current_pos_=='\n')
          break;
      }
      ret.end_=this->current_pos_;
    }
  }
  return ret;
}


#define MAX_PARTS 32
typedef struct
{
  size_t n_parts;
  char* parts[MAX_PARTS];
} yaoocpp_type_name_t;

void yaoccpp_destroy_type_name(yaoocpp_type_name_t* tn)
{
  int i=0;
  for(i=0;i<tn->n_parts;i++)
    FREE(tn->parts[i]);
  FREE(tn);
}

bool yaoocpp_class_parser_argument(yaoocpp_class_parser_pointer this,yaoocpp_argument_pointer arg)
{
  bool ret=false;
  M(this,rule_start);
  yaooc_terminal_t t;//=default_terminal;
  const char* ptr;
  while(true) {
    t=M(this,ident);
    if(t.end_) {
      if(M(arg->type_,size)>0 && M(arg->name_,size)>0)
        M(arg->type_,append," ");
      ptr=M(arg->name_,c_str);
      M(arg->type_,append,ptr);
      M(arg->name_,setn,t.beg_,t.end_-t.beg_);
    } else if(M(this,chr,'*').end_) {
      if(M(arg->type_,size)>0)
        M(arg->type_,append," ");
      ptr=M(arg->name_,c_str);
      M(arg->type_,append,ptr);
      M(arg->type_,append,"*");
      M(arg->name_,clear);
    } else if(M(this,str,"...").end_) {
      if(M(arg->type_,size)==0 && M(arg->name_,size)==0) {
        M(arg->type_,set,"...");
        M(arg->name_,set," ");
      } else {
        /* error */
        M(arg->type_,clear);
        M(arg->name_,clear);
      }
      break;
    } else
      break;
  }
  if(M(arg->type_,size)>0 && M(arg->name_,size)>0) {
    M(this,rule_success);
    ret=true;
  } else {
    M(this,rule_fail);
    ret=false;
  }
  return ret;
}

yaoocpp_variable_pointer yaoocpp_class_parser_variable(yaoocpp_class_parser_pointer this)
{
  yaoocpp_variable_t* ret=new(yaoocpp_variable);
  M(this,rule_start);
  bool rule_ok=false;
  if(yaoocpp_class_parser_argument(this,(yaoocpp_argument_pointer)ret)) {
    rule_ok=true;
    if(M(this,chr,'=').end_) {
      yaooc_terminal_t t=M(this,string_until_chrs,";");
      if(t.end_) {
        M(ret->default_value_,setn,t.beg_,t.end_-t.beg_);
        M(ret->default_value_,trim_);
      } else
        rule_ok=false;
    }
    if(rule_ok)
      if(!M(this,chr,';').end_)
        rule_ok=false;
  }
  if(rule_ok) {
    M(this,rule_success);
  } else {
    M(this,rule_fail);
    delete(ret);
    ret=NULL;
  }
  return ret;
}

/*  Begin YAOOC PreProcessor generated content */

/* Private items for yaoocpp_class_parser */
/* Protected items for yaoocpp_class_parser */


/* Typeinfo for yaoocpp_class_parser */
void yaoocpp_class_parser_default_ctor(pointer p)
{
  yaoocpp_class_parser_pointer this=p;
  yaooc_base_parser_default_ctor(p);
  this->classes_=new(yaoocpp_item_ptr_vector);
  this->file_=new(yaooc_string);
  this->is_top_level_file_=false;
}

void yaoocpp_class_parser_dtor(pointer p)
{
  yaoocpp_class_parser_pointer this=p;
  delete(this->classes_);
  delete(this->file_);
}

/* Constructors for yaoocpp_class_parser */

/* Class table methods for yaoocpp_class_parser */
/*bool yaoocpp_class_parser_constructor(pointer p)
{
  yaoocpp_class_parser_pointer this=p;
  bool ret;

  return ret;
}

bool yaoocpp_class_parser_operator(pointer p)
{
  yaoocpp_class_parser_pointer this=p;
  bool ret;

  return ret;
}
*/
yaoocpp_class_pointer yaoocpp_class_parser_find_class(yaoocpp_class_parser_pointer this,const char* classname)
{
  yaoocpp_item_ptr_vector_iterator i;
  FOR_EACH(i,this->classes_) {
    if(strcmp(M(((yaoocpp_class_const_pointer)*i)->name_,c_str),classname) == 0)
      return (yaoocpp_class_pointer)*i;
  }
  return NULL;
}

bool yaoocpp_class_parser_has_default_ctor(yaoocpp_class_parser_pointer this,const char* classname)
{
  M(this,rule_start);
  if(M(this,str,classname).end_ && M(this,chr,'(').end_ && M(this,chr,')').end_ && M(this,chr,';').end_) {
    M(this,rule_success);
    return true;
  }
  M(this,rule_fail);
  return false;
}

bool yaoocpp_class_parser_has_dtor(yaoocpp_class_parser_pointer this,const char* classname)
{
  M(this,rule_start);
  if(M(this,chr,'~').end_ && M(this,str,classname).end_ && M(this,chr,'(').end_ && M(this,chr,')').end_ && M(this,chr,';').end_) {
    M(this,rule_success);
    return true;
  }
  M(this,rule_fail);
  return false;
}

bool yaoocpp_class_parser_has_copy_ctor(yaoocpp_class_parser_pointer this,const char* classname)
{
  M(this,rule_start);
  if(M(this,str,classname).end_ && M(this,chr,'(').end_ && M(this,str,classname).end_ && M(this,chr,')').end_ && M(this,chr,';').end_) {
    M(this,rule_success);
    return true;
  }
  M(this,rule_fail);
  return false;
}

bool yaoocpp_class_parser_has_assign(yaoocpp_class_parser_pointer this)
{
  M(this,rule_start);
  if(M(this,str,"operator").end_ && M(this,chr,'=').end_ && M(this,chr,'(').end_ && M(this,chr,')').end_ && M(this,chr,';').end_) {
    M(this,rule_success);
    return true;
  }
  M(this,rule_fail);
  return false;
}

bool yaoocpp_class_parser_has_less_than_compare(yaoocpp_class_parser_pointer this)
{
  M(this,rule_start);
  if(M(this,str,"operator").end_ && M(this,chr,'<').end_ && M(this,chr,'(').end_ && M(this,chr,')').end_ && M(this,chr,';').end_) {
    M(this,rule_success);
    return true;
  }
  M(this,rule_fail);
  return false;
}

bool yaoocpp_class_parser_has_to_stream(yaoocpp_class_parser_pointer this)
{
  M(this,rule_start);
  if(M(this,str,"operator").end_ && M(this,str,"<<").end_ && M(this,chr,'(').end_ && M(this,chr,')').end_ && M(this,chr,';').end_) {
    M(this,rule_success);
    return true;
  }
  M(this,rule_fail);
  return false;
}

bool yaoocpp_class_parser_has_from_stream(yaoocpp_class_parser_pointer this)
{
  M(this,rule_start);
  if(M(this,str,"operator").end_ && M(this,str,">>").end_ && M(this,chr,'(').end_ && M(this,chr,')').end_ && M(this,chr,';').end_) {
    M(this,rule_success);
    return true;
  }
  M(this,rule_fail);
  return false;
}

yaoocpp_method_pointer yaoocpp_class_parser_method(yaoocpp_class_parser_pointer this)
{
  PB_INIT;
  yaoocpp_method_t* ret=new(yaoocpp_method);
  M(this,rule_start);
  bool rule_ok=false;
  yaoocpp_argument_pointer arg=PB_SAVE(new(yaoocpp_argument));
  if(yaoocpp_class_parser_argument(this,arg)) {
    const char* ptr=M(arg->name_,c_str);
    M(ret->name_,set,ptr);
    ptr=M(arg->type_,c_str);
    M(ret->type_,set,ptr);
    if(M(this,chr,'(').end_) {
      while(true) {
        yaoocpp_argument_pointer arg=PB_SAVE(new(yaoocpp_argument));
        if(!yaoocpp_class_parser_argument(this,arg)) {
          break;
        }
        M(ret->arguments_,push_back,(pointer)&arg);
        if(!M(this,chr,',').end_)
          break;
      }
      if(M(this,chr,')').end_)
        rule_ok=true;
      if(M(this,str,"const").end_)
        ret->is_const_=true;
      if(M(this,chr,'=').end_) {
        yaooc_terminal_t t=M(this,string_until_chrs,"\r\n;");
        if(t.end_) {
          M(ret->implementation_method_,setn,t.beg_,t.end_-t.beg_);
          M(ret->implementation_method_,trim_);
          if(M(ret->implementation_method_,size)==0)
            rule_ok=false;
        } else {
          rule_ok=false;
        }
      }
      if(rule_ok && !M(this,chr,';').end_)
        rule_ok=false;
    }

  }
  if(rule_ok) {
    M(this,rule_success);
  } else {
    M(this,rule_fail);
    delete(ret);
    ret=NULL;
  }
  PB_EXIT;
  return ret;
}

yaoocpp_item_pointer yaoocpp_class_find_item(yaoocpp_item_ptr_vector_const_pointer this,yaoocpp_item_ptr_const_pointer item)
{
  yaoocpp_item_ptr_pointer ptr=yaooc_find(yaoocpp_item_ptr,M(this,begin),M(this,end),item);
  if(ptr==M(this,end))
    return NULL;
  return *ptr;
}

void yaoocpp_class_parser_items(yaoocpp_class_parser_pointer this,yaoocpp_item_ptr_vector_pointer items,
      const char* classname,bool make_static)
{
  PB_INIT;
  yaoocpp_variable_t* vp;
  yaoocpp_method_t* mp;
  while(true) {
    if((vp=PB_SAVE(yaoocpp_class_parser_variable(this)))) {
      yaoocpp_variable_pointer prev_var= (yaoocpp_variable_pointer)yaoocpp_class_find_item(items,(yaoocpp_item_ptr_const_pointer)&vp);
      if(prev_var) {
        printf("WARNING: Duplicated definition of %s in class %s\n",
                M(vp,name),classname);
      } else {
        if(make_static)
          M(vp->type_,insert,0,"static ");
        M(items,push_back,(yaoocpp_item_ptr_const_pointer)&vp);
      }
    } else if((mp=PB_SAVE(yaoocpp_class_parser_method(this)))) {
      yaoocpp_method_pointer prev_meth = (yaoocpp_method_pointer)yaoocpp_class_find_item(items,(yaoocpp_item_ptr_const_pointer)&mp);
      if(prev_meth) {
        assign_static(prev_meth,mp,yaoocpp_method);
        prev_meth->flags_ |= OVERRIDEN_IN_CURRENT_CLASS;
        M(prev_meth->prefix_,set,classname);
      } else {
        M(mp->prefix_,set,classname);
        if(make_static)
          M(mp->type_,insert,0,"static ");
        M(items,push_back,(yaoocpp_item_ptr_const_pointer)&mp);
      }
    } else
      break;
  }
  PB_EXIT;
}

yaoocpp_constructor_pointer yaoocpp_class_parser_constructor(yaoocpp_class_parser_pointer this,const char* classname)
{
  PB_INIT;
  M(this,rule_start);
  yaoocpp_constructor_t* con=new(yaoocpp_constructor);
  bool rule_ok=false;
  if(M(this,str,classname).end_) {
    yaooc_terminal_t t=M(this,ident);
    if(t.end_ && M(this,chr,'(').end_) {
      M(con->prefix_,set,classname);
      M(con->name_,setn,t.beg_,t.end_-t.beg_);
      while(true) {
        yaoocpp_argument_pointer arg=PB_SAVE(new(yaoocpp_argument));
        if(!yaoocpp_class_parser_argument(this,arg)) {
          break;
        }
        M(con->arguments_,push_back,(pointer)&arg);
        if(!M(this,chr,',').end_)
          break;
      }
      if(M(this,chr,')').end_ && M(this,chr,';').end_)
        rule_ok=true;
    }
  }
  if(rule_ok)
    M(this,rule_success);
  else {
    M(this,rule_fail);
    delete(con);
    con=NULL;
  }
  PB_EXIT;
  return con;
}

void yaoocpp_class_parser_type_info(yaoocpp_class_parser_pointer this,yaoocpp_class_pointer klass)
{
  PB_INIT;
  yaoocpp_constructor_t* con;
  while(true) {
    if(yaoocpp_class_parser_has_default_ctor(this,M(klass->name_,c_str))) {
      klass->has_default_ctor_=true;
    } else if(yaoocpp_class_parser_has_dtor(this,M(klass->name_,c_str))) {
      klass->has_dtor_=true;
    } else if(yaoocpp_class_parser_has_copy_ctor(this,M(klass->name_,c_str))) {
      klass->has_copy_ctor_=true;
    } else if(yaoocpp_class_parser_has_assign(this)) {
      klass->has_assign_=true;
    } else if(yaoocpp_class_parser_has_less_than_compare(this)) {
      klass->has_lt_cmp_=true;
    } else if(yaoocpp_class_parser_has_to_stream(this)) {
      klass->has_to_stream_=true;
    } else if(yaoocpp_class_parser_has_from_stream(this)) {
      klass->has_from_stream_=true;
    } else if((con=PB_SAVE(yaoocpp_class_parser_constructor(this,M(klass->name_,c_str))))!=NULL) {
      M(klass->constructors_,push_back,(const_pointer)&con);
    } else
      break;
  }
  PB_EXIT;
}

void yaoocpp_class_parser_inherit(yaoocpp_class_pointer klass)
{
  if(klass->parent_) {
    assign_static(klass->table_,klass->parent_->table_,yaoocpp_item_ptr_vector);
    yaoocpp_item_ptr_vector_iterator i;
    FOR_EACH(i,klass->table_) {
      (*i)->flags_=DEFINED_IN_PARENT_CLASS;
      if(ISA(*i,yaoocpp_method)) {
        yaoocpp_method_pointer method=(yaoocpp_method_pointer)*i;
        if(strcmp(M(method->name_,c_str),"isa") != 0) {
          M(method->implementation_method_,set,M(klass->parent_->name_,c_str));
          M(method->implementation_method_,append,"_");
          M(method->implementation_method_,append,M(method->name_,c_str));
        } else {
          method->flags_=OVERRIDEN_IN_CURRENT_CLASS;
          M(method->implementation_method_,clear);
        }
        M(method->prefix_,set,M(klass->name_,c_str));
      } else {
        yaoocpp_variable_pointer var=(yaoocpp_variable_pointer)*i;
        if(strcmp(M(var->name_,c_str),"parent_class_table_")==0) {
          M(var->default_value_,set,"&");
          M(var->default_value_,append,M(klass->parent_->name_,c_str));
          M(var->default_value_,append,"_class_table");
        }
      }
    }
/*    assign_static(klass->instance_,klass->parent_->instance_,yaoocpp_item_ptr_vector);
    FOR_EACH(i,klass->instance_) {
      (*i)->flags_=DEFINED_IN_PARENT_CLASS;
    }*/
/*    assign_static(klass->constructors_,klass->parent_->constructors_,yaoocpp_item_ptr_vector);
    FOR_EACH(i,klass->constructors_) {
      (*i)->flags_=DEFINED_IN_PARENT_CLASS;
    } */
  }
}

yaoocpp_class_pointer yaoocpp_class_parser_class(yaoocpp_class_parser_pointer this)
{
  PB_INIT;
  yaoocpp_class_t* ret=NULL;
  bool rule_ok=true;
  if(M(this,str,"class").end_) {
    yaooc_terminal_t t=M(this,ident);
    if(t.end_) {
      ret=new(yaoocpp_class);
      M(ret->name_,setn,t.beg_,t.end_-t.beg_);
      ret->defined_in_top_level_file_=this->is_top_level_file_;
      if(M(this,chr,':').end_) {
        t=M(this,ident);
        if(t.end_) {
          char* classname=PB_SAVE(M(&t,get_raw_text));
          ret->parent_=yaoocpp_class_parser_find_class(this,classname);
          if(ret->parent_ == NULL && strcmp(M(ret->name_,c_str),"yaooc_object")!=0) {
            fprintf(stderr,"Could not find class parent %s for class %s\n",classname,M(ret->name_,c_str));
            exit(1);
          }
        }
      }
      if(ret->parent_==NULL && strcmp(M(ret->name_,c_str),"yaooc_object") != 0) {
        ret->parent_=yaoocpp_class_parser_find_class(this,"yaooc_object");
        if(ret->parent_==NULL) {
          fprintf(stderr,"Classes must be descendant of yaooc_object and yaooc_object definition has not been included\n");
          exit(2);
        }
      }
      yaoocpp_class_parser_inherit(ret);
      if(M(this,chr,'{').end_) {
        yaoocpp_class_parser_type_info(this,ret);
        while(true) {
          if(M(this,str,"table").end_ && M(this,chr,':').end_) {
            yaoocpp_class_parser_items(this,ret->table_,M(ret->name_,c_str),false);
          } else if(M(this,str,"instance").end_ && M(this,chr,':').end_) {
            yaoocpp_class_parser_items(this,ret->instance_,M(ret->name_,c_str),false);
          } else if(M(this,str,"protected").end_ && M(this,chr,':').end_) {
            yaoocpp_class_parser_items(this,ret->protected_,M(ret->name_,c_str),false);
          } else if(M(this,str,"private").end_ && M(this,chr,':').end_) {
            yaoocpp_class_parser_items(this,ret->private_,M(ret->name_,c_str),true);
          } else
            break;
        }
        if(M(this,chr,'}').end_ && M(this,chr,';').end_)
          rule_ok=true;
      }
      if(!rule_ok) {
        delete(ret);
        ret=NULL;
      }
    }
  }
  PB_EXIT;
  return ret;
}

#define OUTPUT_MAX 1048576

static char* preprocess(const char* fname)
{
  char* cpp_output=NULL;
  struct stat st;
  if(stat(fname,&st) == 0) {
    yaooc_string_pointer cpp_cmd=new(yaooc_string);
    const char* ptr=M(cpp,c_str);
    M(cpp_cmd,append,ptr);
/*    ptr=M(defines,c_str);
    M(cpp_cmd,append,ptr);*/
    ptr=M(includes,c_str);
    M(cpp_cmd,append,ptr);
    M(cpp_cmd,append," ");
    M(cpp_cmd,append,fname);
    M(cpp_cmd,append," 2>&1");
    FILE* pipe=popen(M(cpp_cmd,c_str),"r");
    if(pipe) {
      char* temp=new_array(char,OUTPUT_MAX);
      size_t pos=0;
      while(!feof(pipe) && pos < OUTPUT_MAX) {
        pos+=fread(temp+pos,1,OUTPUT_MAX-pos,pipe);
      }
      delete(cpp_cmd);
			temp[pos]=0;
      int rc_system = pclose(pipe);
      if(rc_system == 0) {
        cpp_output=temp;
      } else {
        puts(temp);
        printf("Error %d reported by C preprocessor while processing %s.\n",rc_system-255,fname);
        delete(temp);
      }
    } else {
      printf("Error: File %s not found\n",fname);
    }
  }
  return cpp_output;
}

bool yaoocpp_class_parser_parse_file(pointer p,const char* yaooc_file)
{
  PB_INIT;
  yaoocpp_class_parser_pointer this=p;
  M(this->file_,set,yaooc_file);
  const char* str=PB_SAVE(preprocess(yaooc_file));
  if(str) {
    M(this,set_parse_string,str);
    M(this,set_whitespace_types,CRLF|CUSTOM_WHITESPACE);
    M(this,whitespace);
    while(true) {
      yaoocpp_class_pointer klass=PB_SAVE(yaoocpp_class_parser_class(this));
      if(!klass)
        break;
      /* Check if class already exists.  May have been included twice from different files.  If it already exists, skip it */
      yaoocpp_item_ptr_vector_const_iterator cp=yaooc_find(yaoocpp_item_ptr,M(this->classes_,begin),M(this->classes_,end),&klass);
      if(cp == M(this->classes_,end))
        M(this->classes_,push_back,(const_pointer)&klass);
    }
    if(*this->current_pos_ == 0) {
      this->result_=PARSE_SUCCESS;
    } else {
      this->result_=PARSE_FAILED;
    }
  }
  PB_EXIT;
  return this->result_==0;
}


/* Class table for yaoocpp_class_parser */
yaoocpp_class_parser_class_table_t yaoocpp_class_parser_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_base_parser_class_table,
  .isa = (const char* (*) (const_pointer p)) yaoocpp_class_parser_isa,
  .is_descendant = (bool (*) (const_pointer p,const char*)) yaoocpp_class_parser_is_descendant,
  .swap = (void (*) (pointer p,pointer)) yaoocpp_class_parser_swap,
  .set_parse_string = (void (*) (pointer p,const char*)) yaoocpp_class_parser_set_parse_string,
  .rule_start = (void (*) (pointer p)) yaoocpp_class_parser_rule_start,
  .rule_success = (void (*) (pointer p)) yaoocpp_class_parser_rule_success,
  .rule_fail = (void (*) (pointer p)) yaoocpp_class_parser_rule_fail,
  .eos = (yaooc_terminal_t (*) (pointer p)) yaoocpp_class_parser_eos,
  .string_until_chrs = (yaooc_terminal_t (*) (pointer p,const char*)) yaoocpp_class_parser_string_until_chrs,
  .string_while_chrs = (yaooc_terminal_t (*) (pointer p,const char*)) yaoocpp_class_parser_string_while_chrs,
  .string_until_eol = (yaooc_terminal_t (*) (pointer p)) yaoocpp_class_parser_string_until_eol,
  .shell_comment = (yaooc_terminal_t (*) (pointer p)) yaoocpp_class_parser_shell_comment,
  .c_comment = (yaooc_terminal_t (*) (pointer p)) yaoocpp_class_parser_c_comment,
  .cpp_comment = (yaooc_terminal_t (*) (pointer p)) yaoocpp_class_parser_cpp_comment,
  .custom_whitespace = (yaooc_terminal_t (*) (pointer p)) yaoocpp_class_parser_custom_whitespace,
  .set_whitespace_types = (void (*) (pointer p,uint32_t)) yaoocpp_class_parser_set_whitespace_types,
  .get_whitespace_types = (uint32_t (*) (pointer p)) yaoocpp_class_parser_get_whitespace_types,
  .whitespace = (int (*) (pointer p)) yaoocpp_class_parser_whitespace,
  .chr = (yaooc_terminal_t (*) (pointer p,char)) yaoocpp_class_parser_chr,
  .chr_choices = (int (*) (pointer p,const char*)) yaoocpp_class_parser_chr_choices,
  .str = (yaooc_terminal_t (*) (pointer p,const char*)) yaoocpp_class_parser_str,
  .str_choices = (int (*) (pointer p,...)) yaoocpp_class_parser_str_choices,
  .digits = (yaooc_terminal_t (*) (pointer p)) yaoocpp_class_parser_digits,
  .hexdigits = (yaooc_terminal_t (*) (pointer p)) yaoocpp_class_parser_hexdigits,
  .integer = (yaooc_terminal_t (*) (pointer p)) yaoocpp_class_parser_integer,
  .hexinteger = (yaooc_terminal_t (*) (pointer p)) yaoocpp_class_parser_hexinteger,
  .real = (yaooc_terminal_t (*) (pointer p)) yaoocpp_class_parser_real,
  .ident = (yaooc_terminal_t (*) (pointer p)) yaoocpp_class_parser_ident,
  .regex = (yaooc_terminal_t (*) (pointer p,const char*,uint32_t,uint32_t)) yaoocpp_class_parser_regex,
  .quoted_string = (yaooc_terminal_t (*) (pointer p,char)) yaoocpp_class_parser_quoted_string,
  .single_quoted_string = (yaooc_terminal_t (*) (pointer p)) yaoocpp_class_parser_single_quoted_string,
  .double_quoted_string = (yaooc_terminal_t (*) (pointer p)) yaoocpp_class_parser_double_quoted_string,
  .bare_string = (yaooc_terminal_t (*) (pointer p)) yaoocpp_class_parser_bare_string,
  .string_until_matching_chr = (yaooc_terminal_t (*) (pointer p,char,char)) yaoocpp_class_parser_string_until_matching_chr,
  .parse_file = (bool (*) (pointer p,const char*)) yaoocpp_class_parser_parse_file,
  .result = (yaooc_base_parser_result_t (*) (const_pointer)) yaooc_base_parser_result,
};


DEFINE_TYPE_INFO(yaoocpp_class_parser,yaoocpp_class_parser_default_ctor,yaoocpp_class_parser_dtor,NULL,NULL,NULL,NULL,NULL,&yaoocpp_class_parser_class_table,yaooc_base_parser)
/*  End YAOOC PreProcessor generated content */
