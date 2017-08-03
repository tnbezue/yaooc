#include "yaooc_definition_parser.h"
#include <yaooc/garbage_bag.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#ifndef _WIN32
#define O_BINARY 0
#endif

/*
  Parses a variable, argument, or beginning of a function.
  Consumes idents and "*".  Last item must be an ident
*/
/*VECTOR_DEFINITION(yaooc_string_shared_ptr)
VECTOR_IMPLEMENTATION(yaooc_string_shared_ptr)
*/
class_(type_name) {
  char* type_;
  char* name_;
};

void type_name_default_ctor(pointer p)
{
  type_name_pointer this=p;
  this->type_=NULL;
  this->name_=NULL;
}

void type_name_dtor(pointer p)
{
  type_name_pointer this=p;
  if(this->type_)
    delete (this->type_);
  if(this->name_)
    delete (this->name_);
}

DEFINE_TYPE_INFO(type_name,type_name_default_ctor,type_name_dtor,NULL,NULL,NULL,NULL,NULL)

type_name_pointer yaooc_definition_parser_variable(pointer p)
{
  GB_INIT;
  yaooc_definition_parser_pointer this=p;
  type_name_pointer tn=new(type_name);
  tn->type_=new_array(char,128);
  tn->type_[0]=0;
  bool last_item_is_word=false;
  M(this,rule_start);
  yaooc_terminal_t r;
  int word_count=0;
  char* last_word=NULL;
  while(true) {
    r=M(this,ident);
    if(r.end_) {
      if(last_word!=NULL) {
        strcat(tn->type_,last_word);
        strcat(tn->type_," ");
      }
      last_word=GB_SAVE(M(&r,get_raw_text));
      word_count++;
      last_item_is_word=true;
    } else if(M(this,chr,'*')) {
      if(last_word!=NULL) {
        strcat(tn->type_,last_word);
        strcat(tn->type_,"*");
        strcat(tn->type_," ");
      }
      last_word=NULL;
      last_item_is_word=false;
    } else
      break;
  }
  if(word_count > 1 && last_item_is_word) {
    /* Remove last space from type */
    tn->type_[strlen(tn->type_)-1]=0;
    tn->name_=yaooc_strdup(last_word);
    M(this,rule_success);
  } else {
    M(this,rule_fail);
    delete(tn);
    tn=NULL;
  }
  GB_EXIT;
  return tn;
}

bool yaooc_definition_parser_operators(pointer p,class_definition_pointer obj)
{
  yaooc_definition_parser_pointer this=p;
  M(this,rule_start);
  bool rule_ok=false;
  if(M(this,str,"operator")) {
    if(M(this,chr,'=') ) {
      obj->has_assignment_=true;
      rule_ok=true;
    } else if(M(this,chr,'<')) {
      obj->has_lt_compare_=true;
      rule_ok=true;
    }
    if(!(rule_ok && M(this,chr,'(') && M(this,chr,')') && M(this,chr,';')))
      rule_ok=false;
  }
  if(rule_ok)
    M(this,rule_success);
  else
    M(this,rule_fail);
  return rule_ok;
}


bool yaooc_definition_parser_default_constructor(pointer p,class_definition_pointer obj)
{
  yaooc_definition_parser_pointer this=p;
  M(this,rule_start);
  if(M(this,str,M(&obj->name_,c_str)) && M(this,chr,'(') && M(this,chr,')') && M(this,chr,';')) {
    obj->has_default_ctor_=true;
    M(this,rule_success);
    return true;
  }
  M(this,rule_fail);
  return false;
}

bool yaooc_definition_parser_copy_constructor(pointer p,class_definition_pointer obj)
{
  yaooc_definition_parser_pointer this=p;
  M(this,rule_start);
  if(M(this,str,M(&obj->name_,c_str)) && M(this,chr,'(') && M(this,str,M(&obj->name_,c_str)) && M(this,chr,')') && M(this,chr,';')) {
    obj->has_copy_ctor_=true;
    M(this,rule_success);
    return true;
  }
  M(this,rule_fail);
  return false;
}

/*
  Return vector of arguments for constructor or method
*/
item_definition_shared_ptr_vector_pointer yaooc_definition_parser_args(pointer p)
{
  GB_INIT;
  yaooc_definition_parser_pointer this=p;
  item_definition_shared_ptr_vector_pointer args=new(item_definition_shared_ptr_vector);
  do {
    type_name_pointer type_name=GB_SAVE(yaooc_definition_parser_variable(p));
    if(type_name) {
      /*
        Create a new argument wrapped in shared ptr then add to vector
      */
      M(args,push_back,
            GB_SAVE(new_ctor(item_definition_shared_ptr,item_definition_shared_ptr_ctor_ptr,
            new_ctor(arg_definition,arg_definition_ctor_type_name,type_name->type_,type_name->name_))));
    }
  } while(M(this,chr,','));
  GB_EXIT;
  return args;
}

bool yaooc_definition_parser_other_constructor(pointer p,class_definition_pointer obj)
{
  GB_INIT;
  yaooc_definition_parser_pointer this=p;
  constructor_definition_pointer con=new(constructor_definition);
  M(this,rule_start);
  bool rule_ok=false;
  if(M(this,str,M(&obj->name_,c_str))) {
    yaooc_terminal_t r=M(this,ident);
    if(r.end_ && M(this,chr,'(')) {
      assign_static(&con->prefix_,&obj->name_,yaooc_string);
      M(&con->name_,set,GB_SAVE(M(&r,get_raw_text)));
      item_definition_shared_ptr_vector_pointer args=GB_SAVE(yaooc_definition_parser_args(this));
      assign(con->args_,args);
      if(M(this,chr,')') && M(this,chr,';'))
        rule_ok=true;
    }
  }
  if(rule_ok) {
    M(this,rule_success);
    M(obj->constructors_->items_,push_back,GB_SAVE(new_ctor(item_definition_shared_ptr,
          item_definition_shared_ptr_ctor_ptr,con)));
  } else {
    M(this,rule_fail);
    delete(con);
  }
  GB_EXIT;
  return rule_ok;
}


bool yaooc_definition_parser_constructors(pointer p,class_definition_pointer obj)
{
  return yaooc_definition_parser_default_constructor(p,obj)
      || yaooc_definition_parser_other_constructor(p,obj)
      || yaooc_definition_parser_copy_constructor(p,obj);
}

bool yaooc_definition_parser_destructor(pointer p,class_definition_pointer obj)
{
  yaooc_definition_parser_pointer this=p;
//  printf("Trying destructors for %s\n",class_name);
  if(M(this,chr,'~') && M(this,str,M(&obj->name_,c_str)) && M(this,chr,'(') && M(this,chr,')') && M(this,chr,';')) {
    obj->has_dtor_=true;
   return true;
  }
  return false;
}

/*
  A function is:
    word ((word|*) (word|*) ...)* word(args?) const? (= function_name)?
*/
method_definition_pointer yaooc_definition_parser_method(pointer p)
{
  GB_INIT;
  yaooc_definition_parser_pointer this=p;
  method_definition_pointer mdp=new(method_definition);
  bool rule_ok=false;
  M(this,rule_start);
  yaooc_terminal_t r;
  type_name_pointer type_name=GB_SAVE(yaooc_definition_parser_variable(p));
  if(type_name != NULL) {
    if(M(this,chr,'(')) {

      M(mdp->return_type_,set,type_name->type_);
      M(&mdp->name_,set,type_name->name_);
      item_definition_shared_ptr_vector_pointer args=GB_SAVE(yaooc_definition_parser_args(this));
      assign(mdp->args_,args);
      if(M(this,chr,')')) {
        if(M(this,str,"const")) {
          mdp->is_const_=true;
        }
        if(M(this,chr,'=') && (r=M(this,ident)).end_) {
          M(&mdp->implementation_function_,set,GB_SAVE(M(&r,get_raw_text)));
        }
        if(M(this,chr,';'))
          rule_ok=true;
      }
    }
  }
  if(rule_ok) {
    M(this,rule_success);
  } else {
    M(this,rule_fail);
    delete(mdp);
    mdp=NULL;
  }
  GB_EXIT;
  return mdp;
}

/*
  A variable definition should be
    word ((word|*) (word|*)) ... word ;
*/
variable_definition_pointer yaooc_definition_parser_variables(pointer p)
{
  GB_INIT;
  yaooc_definition_parser_pointer this=p;
  variable_definition_pointer vdp=NULL;
  M(this,rule_start);
  const char* default_value="0";
  type_name_pointer type_name=GB_SAVE(yaooc_definition_parser_variable(this));
  bool rule_ok=false;
  if(type_name != NULL) {
    if(M(this,chr,'=')) {
      yaooc_terminal_t r=M(this,string_until_chr_before_chr,';','\n');
      default_value = GB_SAVE(M(&r,get_raw_text));
    }
    if(M(this,chr,';')) {
      vdp=new_ctor(variable_definition,variable_definition_ctor_type_name_default_value,type_name->type_,type_name->name_,default_value);
      rule_ok=true;
    }
  }
  if(rule_ok)
    M(this,rule_success);
  else {
    M(this,rule_fail);
    if(vdp)
      delete(vdp);
    vdp=NULL;
  }
  GB_EXIT;
  return vdp;
}

bool yaooc_definition_parser_member_definition(pointer p,member_definition_pointer members,yaooc_string_pointer prefix)
{
//  yaooc_definition_parser_pointer this=p;
//  members_pointer members=new(members_ti);
  GB_INIT;
  while(true) {
    method_definition_pointer method=yaooc_definition_parser_method(p);
    if(method) {
      assign_static(&method->prefix_,prefix,yaooc_string);
      M(members->items_,push_back,GB_SAVE(new_ctor(item_definition_shared_ptr,item_definition_shared_ptr_ctor_ptr,method)));
    } else {
      variable_definition_pointer variable=yaooc_definition_parser_variables(p);
      if(variable) {
        M(members->items_,push_back,GB_SAVE(new_ctor(item_definition_shared_ptr,item_definition_shared_ptr_ctor_ptr,variable)));
      } else {
        break;
      }
    }
  }
  GB_EXIT;
  return true;
}

class_definition_pointer yaooc_definition_parser_class_definition(pointer p)
{
  GB_INIT;
  yaooc_definition_parser_pointer this=p;
  class_definition_pointer obj=NULL;
  if(M(this,str,"class")) {
    obj=new(class_definition);
    yaooc_terminal_t cn=M(this,ident);
    if(cn.end_) {
      M(&obj->name_,set,GB_SAVE(M(&cn,get_raw_text)));
    }
    if(M(this,chr,':')) {
      yaooc_terminal_t pt=M(this,ident);
      if(pt.end_) {
        M(&obj->parent_name_,set,GB_SAVE(M(&pt,get_raw_text)));
      } /* else {
          Error if parent name not found
      } */
    }
    if(M(this,chr,'{')) {
      while(true) {
        if(M(this,str,"protected") && M(this,chr,':')) {
          M(this,member_definition,obj->protected_,&obj->name_);
        } if(M(this,str,"table") && M(this,chr,':')) {
          M(this,member_definition,obj->table_,&obj->name_);
        } if(M(this,str,"instance") && M(this,chr,':')) {
          M(this,member_definition,obj->instance_,&obj->name_);
        } else if(M(this,str,"private") && M(this,chr,':')) {
          M(this,member_definition,obj->private_,&obj->name_);
        } else if(!M(this,constructors,obj))
          if(!M(this,destructor,obj))
            if(!M(this,operators,obj))
              break;
      }
    }
    M(this,chr,'}');
    M(this,chr,';');
  }
  GB_EXIT;
  return obj;
}

item_definition_shared_ptr_vector_pointer yaooc_definition_parser_parse_file(pointer p,const char* fname)
{
  GB_INIT;
  yaooc_definition_parser_pointer this=p;
	struct stat st;
  item_definition_shared_ptr_vector_pointer classes=NULL;
	if(stat(fname,&st) == 0 && S_ISREG(st.st_mode)) {
		int fh=open(fname,O_RDONLY|O_BINARY);
		if(fh > 0) {
			char* buffer=GB_SAVE(new_array(char,st.st_size+1));
			read(fh,buffer,st.st_size);
			buffer[st.st_size]=0;
			close(fh);
			classes=M(this,parse,buffer);
		}
	}
  GB_EXIT;
	return classes;
}

item_definition_shared_ptr_vector_pointer yaooc_definition_parser_parse(pointer p,const char*str)
{
  GB_INIT;
  yaooc_definition_parser_pointer this=p;
  item_definition_shared_ptr_vector_pointer classes=new(item_definition_shared_ptr_vector);
  M(this,set_parse_string,str);
  M(this,set_whitespace_types,CRLF|C_COMMENT|CPP_COMMENT);
  M(this,whitespace);
  while(true) {
    class_definition_pointer cd=(M(this,class_definition));
    if(cd == NULL)
      break;
    M(classes,push_back,GB_SAVE(new_ctor(item_definition_shared_ptr,item_definition_shared_ptr_ctor_ptr,cd)));
  };
  if(*this->current_pos_!=0) {
    printf("Parsing failed at line number %u near\n%.50s",this->line_no_,this->current_pos_);
  }
  GB_EXIT;
  return classes;
}

ISA_IMPLEMENTATION(yaooc_definition_parser,yaooc_base_parser)

yaooc_definition_parser_class_members_t yaooc_definition_parser_class_members = { YAOOC_DEFINITION_PARSER_CLASS_MEMBERS };

DEFINE_TYPE_INFO(yaooc_definition_parser,NULL,NULL,
      NULL,NULL,NULL,&yaooc_definition_parser_class_members,yaooc_base_parser)
