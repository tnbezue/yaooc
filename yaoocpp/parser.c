/* Begin YAOOCPP output */
//#define __DEBUG__

#include "parser.h"
#include <string.h>
#include <yaooc/pointer_bag.h>
#include <yaooc/regex.h>
#include <yaooc/algorithm.h>
#include <fcntl.h>

#define CLASS(term) M(this,str,"class",&term)
#define STRUCT(term) M(this,str,"struct",&term)
#define UNION(term) M(this,str,"union",&term)
#define TABLE(term) M(this,str,"table",&term)
#define INSTANCE(term) M(this,str,"instance",&term)
#define PROTECTED(term) M(this,str,"protected",&term)
#define PRIVATE(term) M(this,str,"private",&term)
#define STATIC(term) M(this,str,"static",&term)
#define __CONST__(term) M(this,str,"const",&term)
#define OPERATOR(term) M(this,str,"operator",&term)
#define COMMA(term) M(this,chr,',',&term)
#define COLON(term) M(this,chr,':',&term)
#define SEMICOLON(term) M(this,chr,';',&term)
#define EQUAL(term) M(this,chr,'=',&term)
#define LPAREN(term) M(this,chr,'(',&term)
#define RPAREN(term) M(this,chr,')',&term)
#define LBRACE(term) M(this,chr,'{',&term)
#define RBRACE(term) M(this,chr,'}',&term)
#define LBRACKET(term) M(this,chr,'[',&term)
#define RBRACKET(term) M(this,chr,']',&term)
#define STAR(term) M(this,chr,'*',&term)

extern yaooc_string_t include_directories;
extern yaooc_string_t defines;
extern yaooc_string_t header_extra;
extern yaooc_string_t source_extra;
extern yaooc_string_vector_t include_files;
#define yaoocpp_find_element(vec,vp) yaooc_find(yaoocpp_element_pointer,M(vec,begin),M(vec,end),&vp)

/* Private variables implementation for yaoocpp_parser_exception */
const char* yaoocpp_parser_current_file=NULL;
bool yaoocpp_parser_is_top_level=false;
yaooc_string_t yaoocpp_parser_buffer = YAOOC_STRING_STATIC_DEFAULT_CTOR;

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
  .swap = (void(*)(pointer, pointer)) yaoocpp_parser_exception_swap,
  .what = (const char*(*)(const_pointer)) yaoocpp_parser_exception_what,
};

/* Type info structure for yaoocpp_parser_exception */
DEFINE_TYPE_INFO(yaoocpp_parser_exception,N,N,N,N,N,N,N,Y,yaooc_exception);

/* Private variables implementation for yaoocpp_parser */

/* Private methods prototypes for yaoocpp_parser */
static void yaoocpp_parser_preprocess(pointer);
static yaoocpp_container_const_pointer yaoocpp_parser_find_class(pointer, const char*);
static void yaoocpp_parser_extract_section(pointer,const char*,const char*,const char*,yaooc_string_t*);
static void yaoocpp_parser_find_yaooc_includes(pointer,const char*,yaooc_string_vector_t*);
static bool yaoocpp_parser_line_directive(pointer,yaooc_terminal_t*);
static bool yaoocpp_parser_containers(pointer);
static bool yaoocpp_parser_name_parent(pointer);
static bool yaoocpp_parser_contents(pointer);
static bool yaoocpp_parser_type_info(pointer);
static bool yaoocpp_parser_default_constructor(pointer);
static bool yaoocpp_parser_destructor(pointer);
static bool yaoocpp_parser_copy_constructor(pointer);
static bool yaoocpp_parser_assignment(pointer);
static bool yaoocpp_parser_less_than_compare(pointer);
static bool yaoocpp_parser_to_stream(pointer);
static bool yaoocpp_parser_from_stream(pointer);
static bool yaoocpp_parser_arguments(pointer,yaoocpp_argument_vector_t**);
static bool yaoocpp_parser_argument(pointer,yaoocpp_argument_t**);
static bool yaoocpp_parser_va_argument(pointer,yaoocpp_argument_t**);
static bool yaoocpp_parser_constructor(pointer);
static bool yaoocpp_parser_method(pointer,yaoocpp_method_t**);
static bool yaoocpp_parser_method_with_implementation_method(pointer,yaoocpp_method_t**);
static bool yaoocpp_parser_method_base(pointer,yaoocpp_method_t**);
static bool yaoocpp_parser_variable_with_default_value(pointer,yaoocpp_variable_t**);
static bool yaoocpp_parser_variable(pointer,yaoocpp_variable_t**);
static bool yaoocpp_parser_variable_base(pointer,yaoocpp_variable_t**);
static bool yaoocpp_parser_type_variable(pointer,yaoocpp_variable_t**);
static bool yaoocpp_parser_type_only(pointer,yaoocpp_type_t**);
static bool yaoocpp_parser_table(pointer);
static bool yaoocpp_parser_instance(pointer);
static bool yaoocpp_parser_protected(pointer);
static bool yaoocpp_parser_private(pointer);
static bool yaoocpp_parser_static(pointer);
static bool yaoocpp_parser_table_struct_not_allowed(pointer);

/* Type Info implemmentation for yaoocpp_parser */
void yaoocpp_parser_default_ctor(pointer p)
{
  yaoocpp_parser_pointer this=p;
  yaooc_base_parser_default_ctor(this);
  this->classes_ = NULL;
  this->current_class_=NULL;
  newp(&this->header_text_,yaooc_string);
  newp(&this->source_text_,yaooc_string);
  newp(&this->include_files_,yaooc_string_vector);
}

void yaoocpp_parser_dtor(pointer p)
{
  yaoocpp_parser_pointer this=p;
  if(this->classes_)
     delete(this->classes_);
  this->classes_ = NULL;
  deletep(&this->header_text_,yaooc_string);
  deletep(&this->source_text_,yaooc_string);
  deletep(&this->include_files_,yaooc_string_vector);
}

/* Constructors implementation for yaoocpp_parser */

/* Private methods implementation for yaoocpp_parser */
bool yaoocpp_parser_line_directive(pointer p,yaooc_terminal_t* ws)
{
  yaoocpp_parser_pointer this=p;
  bool ret=false;
  RULE_START(p);
  *ws=(yaooc_terminal_t) { NULL, NULL };
  yaooc_terminal_t r,l;
//        && YAOOC_PARSER_OPTIONAL(M(this,integer,&r) && YAOOC_PARSER_OPTIONAL(M(this,integer,&r) && YAOOC_PARSER_OPTIONAL(M(this,integer,&r))) {
  if(M(this,chr,'#',&r) && M(this,integer,&l)) {
    this->line_no_=atoi(l.beg_)-1;
    if(*this->current_pos_=='"') { // This should always be true -- but just in case
      // Find end of file name
      this->current_pos_++;
      const char* ptr=this->current_pos_;
      for(;*this->current_pos_!='"';this->current_pos_++);
      yaoocpp_parser_is_top_level=strncmp(yaoocpp_parser_current_file,ptr,this->current_pos_-ptr-2)==0;
      for(;*this->current_pos_ != 0;this->current_pos_++)
        if(*this->current_pos_ == '\r' || *this->current_pos_ == '\n')
          break;
    }
    ws->end_=this->current_pos_;
    ret=true;
  }
  if(ret) {
    RULE_SUCCESS(p);
    ws->end_=this->current_pos_;
  }
  else
    RULE_FAIL(p);
  return ret;
}

#define BUF_SIZE 1024
static void yaoocpp_parser_preprocess(pointer p)
{
//  yaoocpp_parser_pointer this=p;

  // Generate preprocessor command line
  yaooc_string_t cpp = YAOOC_STRING_STATIC_DEFAULT_CTOR;
  M(&cpp,set,"/usr/bin/cpp -nostdinc");
  M(&cpp,append,M(&defines,c_str));
//    M(&cpp,append," ");
  M(&cpp,append,M(&include_directories,c_str));
  const char* temp=getenv("YAOOCPP_FLAGS");
  if(temp) {
    M(&cpp,append," ");
    M(&cpp,append,temp);
  }
  temp=getenv("YAOOCPP_INCLUDE_PATH");
  if(temp) {
    M(&cpp,append," -I");
    M(&cpp,append,temp);
  }
  M(&cpp,append," ");
  M(&cpp,append,yaoocpp_parser_current_file);
  M(&cpp,append," 2>&1");
  FILE* pipe=popen(M(&cpp,c_str),"r");
  if(pipe) {
    char temp[BUF_SIZE];
    newp(&yaoocpp_parser_buffer,yaooc_string);
    while(!feof(pipe)) {
      size_t n=fread(temp,1,BUF_SIZE-1,pipe);
//      temp[n]=0;
      M(&yaoocpp_parser_buffer,appendn,temp,n);
    }
    int rc=pclose(pipe);
    //STREAM(cout,O_OBJ(yaooc_string,yaoocpp_parser_buffer));
    if(rc!=0) {
      STREAM(cerr,O_OBJ(yaooc_string,yaoocpp_parser_buffer));
      THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
          "Preprocessor error (error code %d).  Review above ouput",rc-255));
    }
    deletep(&cpp,yaooc_string);
  }
}

static yaoocpp_container_const_pointer yaoocpp_parser_find_class(pointer p,const char* name)
{
  yaoocpp_parser_pointer this=p;
	yaoocpp_container_pointer_vector_const_iterator i;
	CFOR_EACH(i,this->classes_) {
		if(strcmp(name,M(&(*i)->name_,c_str))==0)
			break;
	}
	if(i != M(this->classes_,end))
		return *i;
  return NULL;
}

static void yaoocpp_parser_extract_section(pointer p,const char* str,const char* beg,const char* end,yaooc_string_t* content_extracted)
{
//  yaoocpp_parser_pointer this=p;
  regex_t re_beg;
  regex_t re_end;
  int rc=0;
  if(regcomp(&re_beg,beg,REG_EXTENDED|REG_NEWLINE)==0) {
    if(regcomp(&re_end,end,REG_EXTENDED|REG_NEWLINE)==0) {
      size_t beg_pos=0;
      regmatch_t ov;
      do {
        if((rc=yaooc_regex_regexec(&re_beg,str,beg_pos,1,&ov,0))==0) {
          beg_pos=ov.rm_eo;
          if((rc=yaooc_regex_regexec(&re_end,str,beg_pos,1,&ov,0))==0) {
            M(content_extracted,appendn,str+beg_pos,ov.rm_so-beg_pos);
            beg_pos=ov.rm_eo;
          }
        }
      } while(rc==0);
      regfree(&re_end);
    } else {
      fprintf(stderr,"End regex \"%s\" failed\n",end);
      exit(1);
    }
    regfree(&re_beg);
  } else {
    fprintf(stderr,"Begin regex \"%s\" failed\n",beg);
    exit(1);
  }
}

#define re_match(re) (yaooc_regex_regexec(&re,line,0,0,NULL,0) == 0)
static void yaoocpp_parser_find_yaooc_includes(pointer p,const char* str,yaooc_string_vector_t*includes)
{
//  yaoocpp_parser_pointer this=p;
  regex_t re_yaooc_include_beg;
  regex_t re_yaooc_include_end;
  regmatch_t ov;
  if(regcomp(&re_yaooc_include_beg,"#\\s*include\\s*[\"<]",REG_EXTENDED|REG_NEWLINE)!=0) {
    puts("regcomp 1 failed");
    exit(1);
  }

  if(regcomp(&re_yaooc_include_end,"\\.yaooc[\">]",REG_EXTENDED|REG_NEWLINE)!=0) {
    puts("regcomp 2 failed");
    exit(1);
  }
  int ofs=0;
  int rc=0;
  yaooc_string_t inc_file;
  newp(&inc_file,yaooc_string);
  do {
    rc=yaooc_regex_regexec(&re_yaooc_include_beg,str,ofs,1,&ov,0);
    if(rc==0) {
      ofs=ov.rm_eo;
      rc=yaooc_regex_regexec(&re_yaooc_include_end,str,ofs,1,&ov,0);
      if(rc == 0) {
        M(&inc_file,setn,str+ofs,ov.rm_so-ofs);
        M(includes,push_back,&inc_file);
        ofs=ov.rm_eo;
      }
    }
  } while(rc==0);
  deletep(&inc_file,yaooc_string);
  regfree(&re_yaooc_include_beg);
  regfree(&re_yaooc_include_end);
}

static bool yaoocpp_parser_containers(pointer p)
{
  yaoocpp_parser_pointer this=p;
  bool ret=false;
  yaooc_terminal_t r;
  while(true) {
    if(CLASS(r)) {
      this->current_class_=new(yaoocpp_class);
      ret=true;
    } else if(STRUCT(r)) {
      this->current_class_=new(yaoocpp_struct);
      ret=true;
    } else if(UNION(r)) {
      this->current_class_=new(yaoocpp_union);
      ret=true;
    } else
      break;
    this->current_class_->defined_in_top_level_file_=yaoocpp_parser_is_top_level;
    yaoocpp_parser_name_parent(p);
    if(yaoocpp_parser_contents(this)) {
      M(this->classes_,push_back,&this->current_class_);
      delete(this->current_class_);
    }
  }
  // should be at end of file
  if(*this->current_pos_!=0) {
    THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
        "Error processing %s near line %d\n",yaoocpp_parser_current_file,this->line_no_));
  }
  return ret;
}

static bool yaoocpp_parser_name_parent(pointer p)
{
  yaoocpp_parser_pointer this=p;
  bool ret=false;
  yaooc_terminal_t r,name,parent;
  if(M(this,ident,&name)) {
    char* parent_name=NULL;
    M(&this->current_class_->name_,setn,name.beg_,name.end_-name.beg_);
    if(strncmp(name.beg_,"yaooc_object",name.end_-name.beg_)!=0) { // no parent for base object
      if(COLON(r)) {
        if(M(this,ident,&parent)) {
          parent_name=yaooc_terminal_raw_text(&parent);
        }
      }
      if(parent_name==NULL && !ISA(this->current_class_,yaoocpp_struct)) {
        parent_name=yaooc_strdup("yaooc_object");
      }
      if(parent_name != NULL) {  // If NULL, then it must be a struct.  OK not to have a parent
        this->current_class_->parent_=yaoocpp_parser_find_class(p,parent_name);
        if(this->current_class_->parent_ == NULL) {
          THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
              "Parent class %s for class %s has not been defined.",
              parent_name,M(&this->current_class_->name_,c_str)));
        }
      }
      M(this->current_class_,inherit);
      if(parent_name)
        delete(parent_name);
    }
    ret=true;
  }
  return ret;
}

static bool yaoocpp_parser_contents(pointer p)
{
  yaoocpp_parser_pointer this=p;
  bool ret=false;
  yaooc_terminal_t r;
  if(LBRACE(r)) {
    while(true) {
      if(!yaoocpp_parser_type_info(p))
        if(!yaoocpp_parser_constructor(p))
          break;
    }
    while(true) {
      if(!((ISA(this->current_class_,yaoocpp_struct) && yaoocpp_parser_table_struct_not_allowed(p))
              || yaoocpp_parser_table(p)))
        if(!yaoocpp_parser_instance(p))
          if(!yaoocpp_parser_protected(p))
            if(!yaoocpp_parser_private(p))
              if(!yaoocpp_parser_static(p))
                break;
    }
    if(RBRACE(r) && SEMICOLON(r))
      ret=true;
  }
  return ret;
}

static bool yaoocpp_parser_type_info(pointer p)
{
  yaoocpp_parser_pointer this=p;
  bool ret=true;
  if(yaoocpp_parser_default_constructor(p)) {
    this->current_class_->has_default_ctor_=true;
  } else if(yaoocpp_parser_destructor(p)) {
    this->current_class_->has_dtor_=true;
  } else if(yaoocpp_parser_copy_constructor(p)) {
    this->current_class_->has_copy_ctor_=true;
  } else if(yaoocpp_parser_assignment(p)) {
    this->current_class_->has_assign_=true;
  } else if(yaoocpp_parser_less_than_compare(p)) {
    this->current_class_->has_lt_cmp_=true;
  } else if(yaoocpp_parser_to_stream(p)) {
    this->current_class_->has_to_stream_=true;
  } else if(yaoocpp_parser_from_stream(p)) {
    this->current_class_->has_from_stream_=true;
  } else
    ret=false;
  return ret;
}

static bool yaoocpp_parser_default_constructor(pointer p)
{
  yaoocpp_parser_pointer this=p;
  RULE_START(p);
  yaooc_terminal_t r;
  if(M(this,str,M(&this->current_class_->name_,c_str),&r) && LPAREN(r) && RPAREN(r) && SEMICOLON(r)) {
    RULE_SUCCESS(p);
    return true;
  }
  RULE_FAIL(p);
  return false;
}

static bool yaoocpp_parser_destructor(pointer p)
{
  yaoocpp_parser_pointer this=p;
  yaooc_terminal_t r;
  M(this,rule_start);
  if(M(this,chr,'~',&r) && M(this,str,M(&this->current_class_->name_,c_str),&r) &&
            LPAREN(r) && RPAREN(r) && SEMICOLON(r)) {
    RULE_SUCCESS(p);
    return true;
  }
  RULE_FAIL(p);
  return false;
}

static bool yaoocpp_parser_copy_constructor(pointer p)
{
  yaoocpp_parser_pointer this=p;
  yaooc_terminal_t r;
  M(this,rule_start);
  if(M(this,str,M(&this->current_class_->name_,c_str),&r) && LPAREN(r)
        && M(this,str,M(&this->current_class_->name_,c_str),&r) && STAR(r) && RPAREN(r) && SEMICOLON(r)) {
    RULE_SUCCESS(p);
    return true;
  }
  RULE_FAIL(p);
  return false;
}

static bool yaoocpp_parser_assignment(pointer p)
{
  yaoocpp_parser_pointer this=p;
  yaooc_terminal_t r;
  M(this,rule_start);
  if(M(this,str,"operator",&r) && EQUAL(r) && LPAREN(r) && RPAREN(r) && SEMICOLON(r)) {
    RULE_SUCCESS(p);
    return true;
  }
  RULE_FAIL(p);
  return false;
}

static bool yaoocpp_parser_less_than_compare(pointer p)
{
  yaoocpp_parser_pointer this=p;
  yaooc_terminal_t r;
  M(this,rule_start);
  if(M(this,str,"operator",&r) && M(this,chr,'<',&r) && LPAREN(r) && RPAREN(r) && SEMICOLON(r)) {
    RULE_SUCCESS(p);
    return true;
  }
  RULE_FAIL(p);
  return false;
}

static bool yaoocpp_parser_to_stream(pointer p)
{
  yaooc_terminal_t r;
  yaoocpp_parser_pointer this=p;
  M(this,rule_start);
  if(M(this,str,"operator",&r) && M(this,str,"<<",&r) && LPAREN(r) && RPAREN(r) && SEMICOLON(r)) {
    RULE_SUCCESS(p);
    return true;
  }
  RULE_FAIL(p);
  return false;
}

static bool yaoocpp_parser_from_stream(pointer p)
{
  yaoocpp_parser_pointer this=p;
  yaooc_terminal_t r;
  M(this,rule_start);
  if(M(this,str,"operator",&r) && M(this,str,">>",&r) && LPAREN(r) && RPAREN(r) && SEMICOLON(r)) {
    RULE_SUCCESS(p);
    return true;
  }
  RULE_FAIL(p);
  return false;
}

static bool yaoocpp_parser_arguments(pointer p,yaoocpp_argument_vector_t** args)
{
  pb_init();
  yaoocpp_parser_pointer this=p;
  bool ret=false;
  yaooc_terminal_t r;
  *args=new(yaoocpp_argument_vector);
  yaoocpp_argument_t* arg;
  /* One are more argumetns seperated by comma.  Last argument can be va_arg (...) */
  if(yaoocpp_parser_argument(this,&arg)) {
    M(*args,push_back,arg);
    delete(arg);
    ret=true;
    while(YAOOC_PARSER_TRY_RULE(p,COMMA(r) && yaoocpp_parser_argument(this,&arg))) {
      M(*args,push_back,arg);
      delete(arg);
    }
    if(YAOOC_PARSER_TRY_RULE(p,COMMA(r) && yaoocpp_parser_va_argument(this,&arg))) {
      M(*args,push_back,arg);
      delete(arg);
    }
  } else {
    /* Or single va_arg (...) */
    if(yaoocpp_parser_va_argument(this,&arg)) {
      M(*args,push_back,arg);
      delete(arg);
      ret = true;
    }
  }
  pb_exit();
  return ret;
}

static bool yaoocpp_parser_argument(pointer p,yaoocpp_argument_t** arg)
{
  pb_init();
  yaoocpp_parser_pointer this=p;
  bool ret=false;
  yaoocpp_variable_t* var;
  if(yaoocpp_parser_variable_base(this,&var)) {
    *arg=new(yaoocpp_argument);
    assign_static(&(*arg)->type_,&var->type_,yaooc_string);
    assign_static(&(*arg)->name_,&var->name_,yaooc_string);
    assign_static(&(*arg)->array_size_,&var->array_size_,yaooc_string);
    (*arg)->is_array_=var->is_array_;
    delete(var);
    ret=true;
  }
  pb_exit();
  return ret;
}

static bool yaoocpp_parser_va_argument(pointer p,yaoocpp_argument_t** arg)
{
  yaoocpp_parser_pointer this=p;
  bool ret=false;
  yaooc_terminal_t r;
  if(M(this,str,"...",&r)) {
    *arg=new(yaoocpp_argument);
    M(&(*arg)->type_,set,"...");
    ret=true;
  }
  return ret;
}

static bool yaoocpp_parser_constructor(pointer p)
{
  yaoocpp_parser_pointer this=p;
  bool ret=false;
  pb_init();
  RULE_START(p);
  yaoocpp_constructor_t* con=pb_new(yaoocpp_constructor);
  yaooc_terminal_t r,name,imp_con={NULL,NULL};
  yaoocpp_argument_vector_t* args;
  if(M(this,ident,&name) && LPAREN(r) && yaoocpp_parser_arguments(this,&args) && RPAREN(r)) {
    size_t class_name_len=M(&this->current_class_->name_,size);
    if(class_name_len < name.end_-name.beg_ &&
            strncmp(M(&this->current_class_->name_,c_str),name.beg_,class_name_len) ==0) {
      ret=true;
      if(EQUAL(r)) {
        if(M(this,ident,&imp_con))
          ret=true;
        else
          ret=false;
      }
      if(ret && SEMICOLON(r)) {
        M(&con->name_,setn,name.beg_,name.end_-name.beg_);
        yaoocpp_argument_vector_const_iterator i;
        CFOR_EACH(i,args)
          M(&con->arguments_,push_back,i);
        delete(args);
        if(imp_con.end_!=NULL)
          M(&con->implementation_method_,setn,imp_con.beg_,imp_con.end_-imp_con.beg_);
      } else
        ret=false;
    }
  }
  if(ret) {
    RULE_SUCCESS(p);
    M(&this->current_class_->constructors_,push_back,(yaoocpp_element_t **)&con);
  }
  else
    RULE_FAIL(p);
  pb_exit();
  return ret;
}

static bool yaoocpp_parser_table(pointer p)
{
  yaoocpp_parser_pointer this=p;
  bool ret=false;
  pb_init();
  yaooc_terminal_t r;
  if(TABLE(r) && COLON(r)) {
    while(true) {
#define container ((yaoocpp_container_with_class_table_t*)(this->current_class_))->table_
      yaoocpp_method_t* proc;
      if(yaoocpp_parser_method_with_implementation_method(p,&proc)) {
        debug_printf("Table: Got method %s\n",M(&proc->name_,c_str));
        yaoocpp_method_t** orig=yaoocpp_find_element(&container,proc);
        /* If already defined, override existing element */
        if(orig == M(&container,end)) {
          M(&container,push_back,(yaoocpp_element_t**)&proc);
        } else {
          assign_static(&(*orig)->implementation_method_,&proc->implementation_method_,yaooc_string);
          (*orig)->state_=OVERRIDDEN;
        }
        delete(proc);
      } else {
        yaoocpp_variable_t* var;
        if(yaoocpp_parser_variable_with_default_value(p,&var)) {
          debug_printf("Table: Got var %s\n",M(&var->name_,c_str));
          /* If already defined, replace default value */
          yaoocpp_variable_t** orig=yaoocpp_find_element(&container,var);
          if(orig == M(&container,end)) {
            M(&container,push_back,(yaoocpp_element_t**)&var);
          } else {
            assign_static(&(*orig)->default_value_,&var->default_value_,yaooc_string);
          }
          delete(var);
        } else
          break;
      }
#undef container
    }
    ret=true;
  }
  pb_exit();
  return ret;
}

static bool yaoocpp_parser_instance(pointer p)
{
  yaoocpp_parser_pointer this=p;
  bool ret=false;
  pb_init();
  yaooc_terminal_t r;
  if(INSTANCE(r) && COLON(r)) {
#define container this->current_class_->instance_
    while(true) {
      yaoocpp_variable_t* var;
      if(yaoocpp_parser_variable(p,&var)) {
        debug_printf("Instance: Got var %s\n",M(&var->name_,c_str));
        /* Variables can't be redefined in instance definition */
        if(yaoocpp_find_element(&container,var) != M(&container,end)) {
          THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
                "Redefining instance variable %s on or before line %d",
                M(&var->name_,c_str),this->line_no_));
        }
        M(&container,push_back,(yaoocpp_element_t**)&var);
        delete(var);
      } else {
        yaoocpp_method_t* proc;
        if(yaoocpp_parser_method(p,&proc)) {
          debug_printf("Instance: Got method %s\n",M(&proc->name_,c_str));
          /* Methods can't be overridden in instance definition */
          if(yaoocpp_find_element(&container,proc) != M(&container,end)) {
            THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
                  "Redefining instance method %s on or before line %d",
                  M(&proc->name_,c_str),this->line_no_));
          }
          M(&container,push_back,(yaoocpp_element_t**)&proc);
          delete(proc);
        } else {
          yaoocpp_type_t* type;
          if(yaoocpp_parser_type_only(p,&type)) {
            /* Can only have one type only entry */
            if(yaoocpp_find_element(&container,type) != M(&container,end)) {
              THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
                    "Only one %s type allowed as type only entry on or before line %d",
                    M(&proc->name_,c_str),this->line_no_));
            }
            M(&container,push_back,(yaoocpp_element_t**)&type);
            delete(type);
          } else
            break;
        }
      }
    }
#undef container
    ret=true;
  }
  pb_exit();
  return ret;
}

static bool yaoocpp_parser_protected(pointer p)
{
  yaoocpp_parser_pointer this=p;
  bool ret=false;
  pb_init();
  yaooc_terminal_t r;
  if(PROTECTED(r) && COLON(r)) {
#define container this->current_class_->protected_
    while(true) {
      yaoocpp_method_t* proc;
      if(yaoocpp_parser_method_with_implementation_method(p,&proc)) {
        debug_printf("Protected: Got method %s\n",M(&proc->name_,c_str));
        /* Methods can't be overridden in protected definition */
        if(yaoocpp_find_element(&container,proc) != M(&container,end)) {
          THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
                "Redefining protected method %s on or before line %d",
                M(&proc->name_,c_str),this->line_no_));
        }
        M(&container,push_back,(yaoocpp_element_t**)&proc);
        delete(proc);
      } else {
        yaoocpp_variable_t* var;
        if(yaoocpp_parser_variable_with_default_value(p,&var)) {
          debug_printf("Protected: Got var %s\n",M(&var->name_,c_str));
          /* Variables can't be redefined in instance definition */
          if(yaoocpp_find_element(&container,var) != M(&container,end)) {
            THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
                  "Redefining protected variable %s on or before line %d",
                  M(&var->name_,c_str),this->line_no_));
          }
          M(&container,push_back,(yaoocpp_element_t**)&var);
          delete(var);
        } else
          break;
      }
    }
#undef container
    ret=true;
  }
  pb_exit();
  return ret;
}

static bool yaoocpp_parser_private(pointer p)
{
  yaoocpp_parser_pointer this=p;
  bool ret=false;
  pb_init();
  yaooc_terminal_t r;
  if(PRIVATE(r) && COLON(r)) {
#define container this->current_class_->private_
    while(true) {
      yaoocpp_method_t* proc;
      if(yaoocpp_parser_method_with_implementation_method(p,&proc)) {
        debug_printf("Private: Got method %s\n",M(&proc->name_,c_str));
        /* Methods can't be overridden in private definition */
        if(yaoocpp_find_element(&container,proc) != M(&container,end)) {
          THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
                "Redefining private method %s on or before line %d",
                M(&proc->name_,c_str),this->line_no_));
        }
        M(&container,push_back,(yaoocpp_element_t**)&proc);
        delete(proc);
      } else {
        yaoocpp_variable_t* var;
        if(yaoocpp_parser_variable_with_default_value(p,&var)) {
          debug_printf("Private: Got var %s\n",M(&var->name_,c_str));
          /* Variables can't be redefined in private definition */
          if(yaoocpp_find_element(&container,var) != M(&container,end)) {
            THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
                  "Redefining private variable %s on or before line %d",
                  M(&var->name_,c_str),this->line_no_));
          }
          M(&container,push_back,(yaoocpp_element_t**)&var);
          delete(var);
        } else
          break;
      }
    }
#undef container
    ret=true;
  }
  pb_exit();
  return ret;
}

static bool yaoocpp_parser_static(pointer p)
{
  yaoocpp_parser_pointer this=p;
  bool ret=false;
  pb_init();
  yaooc_terminal_t r;
  if(STATIC(r) && COLON(r)) {
#define container this->current_class_->static_
    while(true) {
      yaoocpp_method_t* proc;
      if(yaoocpp_parser_method_with_implementation_method(p,&proc)) {
        debug_printf("Static: Got method %s\n",M(&proc->name_,c_str));
        /* Methods can't be overridden in private definition */
        if(yaoocpp_find_element(&container,proc) != M(&container,end)) {
          THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
                "Redefining static method %s on or before line %d",
                M(&proc->name_,c_str),this->line_no_));
        }
        M(&container,push_back,(yaoocpp_element_t**)&proc);
        delete(proc);
      } else {
        yaoocpp_variable_t* var;
        if(yaoocpp_parser_variable_with_default_value(p,&var)) {
          debug_printf("Static: Got var %s\n",M(&var->name_,c_str));
          /* Variables can't be redefined in private definition */
          if(yaoocpp_find_element(&container,var) != M(&container,end)) {
            THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
                  "Redefining static variable %s on or before line %d",
                  M(&var->name_,c_str),this->line_no_));
          }
          M(&container,push_back,(yaoocpp_element_t**)&var);
          delete(var);
        } else
          break;
      }
    }
#undef container
    ret=true;
  }
  pb_exit();
  return ret;
}

static bool yaoocpp_parser_table_struct_not_allowed(pointer p)
{
  yaoocpp_parser_pointer this=p;
  bool ret=false;
  yaooc_terminal_t r;
  if(YAOOC_PARSER_TRY_RULE(p,TABLE(r) && COLON(r))) {
     THROW(new_ctor(yaoocpp_parser_exception,yaoocpp_parser_exception_ctor_v,
        "Table section not allowd in struct declaration"));
  }
  return ret;
}

static bool yaoocpp_parser_method_with_implementation_method(pointer p,yaoocpp_method_t** meth)
{
  yaoocpp_parser_pointer this=p;

  pb_init();
  RULE_START(p);
  yaooc_terminal_t r;
  bool ret=yaoocpp_parser_method_base(this,meth);
  if(ret) {
    if(EQUAL(r)) {
      if(M(this,ident,&r)) {
        M(&(*meth)->implementation_method_,setn,r.beg_,r.end_-r.beg_);
        ret=true;
      }
    }
  }
  if(!SEMICOLON(r))
    ret=false;
  if(ret)
    RULE_SUCCESS(p);
  else
    RULE_FAIL(p);
  pb_exit();
  return ret;
}

static bool yaoocpp_parser_method(pointer p,yaoocpp_method_t** meth)
{
  yaoocpp_parser_pointer this=p;
  bool ret=false;
  yaooc_terminal_t r;
  if(YAOOC_PARSER_TRY_RULE(p,yaoocpp_parser_method_base(this,meth) && SEMICOLON(r))) {
    ret=true;
  }
  return ret;
}

static bool yaoocpp_parser_method_base(pointer p,yaoocpp_method_t** meth)
{
  yaoocpp_parser_pointer this=p;
  pb_init();
  RULE_START(p);
  yaoocpp_variable_t* var=NULL;
  yaoocpp_argument_vector_t* args;
  yaooc_terminal_t r,is_const;
  bool ret=false;
  if(yaoocpp_parser_type_variable(p,&var)) {
    if(LPAREN(r) && YAOOC_PARSER_OPTIONAL(yaoocpp_parser_arguments(p,&args)) && RPAREN(r) &&
          YAOOC_PARSER_OPTIONAL(__CONST__(is_const))) {
      *meth=new(yaoocpp_method);
      assign_static(&(*meth)->return_type_,&var->type_,yaooc_string);
      assign_static(&(*meth)->name_,&var->name_,yaooc_string);
      delete(var);
      yaoocpp_argument_vector_const_iterator i;
      CFOR_EACH(i,args)
        M(&(*meth)->arguments_,push_back,i);
      (*meth)->is_const_=is_const.end_!=NULL;
      delete(args);
      ret=true;
    } else
      delete(var);
  }
  pb_exit();
  if(ret)
    RULE_SUCCESS(p);
  else
    RULE_FAIL(p);
  return ret;
}

static bool yaoocpp_parser_variable_with_default_value(pointer p,yaoocpp_variable_t** var)
{
  yaoocpp_parser_pointer this=p;
  RULE_START(p);
  bool ret=yaoocpp_parser_variable_base(this,var);
  if(ret) {
    yaooc_terminal_t r;
    if(EQUAL(r)) {
      if(M(this,string_until_chrs,";",&r)) {
        M(&(*var)->default_value_,setn,r.beg_,r.end_-r.beg_);
      }
    }
    if(!SEMICOLON(r)) {
      ret=false;
    }
  }
  if(ret)
    RULE_SUCCESS(p);
  else
    RULE_FAIL(p);
  return ret;
}

static bool yaoocpp_parser_variable(pointer p,yaoocpp_variable_t** var)
{
  yaoocpp_parser_pointer this=p;
  yaooc_terminal_t r;
  bool ret=YAOOC_PARSER_TRY_RULE(p,yaoocpp_parser_variable_base(p,var) && SEMICOLON(r));
  return ret;
}

static bool yaoocpp_parser_variable_base(pointer p,yaoocpp_variable_t** var)
{
  yaoocpp_parser_pointer this=p;
  RULE_START(p);
  bool ret=yaoocpp_parser_type_variable(p,var);
  if(ret) {
    yaooc_terminal_t r;
    yaooc_terminal_t dv;
    if(LBRACKET(r)) {
      if(M(this,string_until_matching_chr,'[',']',&dv)) {  // RBRACKET consumed in this call
        M(&(*var)->array_size_,setn,dv.beg_,dv.end_-dv.beg_);
        (*var)->is_array_=true;
      } else {
        delete(*var);
        ret=false;
      }
    }
  }
  if(ret)
    RULE_SUCCESS(p);
  else
    RULE_FAIL(p);
  return ret;
}

static bool yaoocpp_parser_type_variable(pointer p,yaoocpp_variable_t** var)
{
  yaoocpp_parser_pointer this=p;
  bool ret=false;
  RULE_START(p);
  yaooc_terminal_t r;
  if(M(this,ident,&r)) {
    *var=new(yaoocpp_variable);
    M(&(*var)->type_,setn,r.beg_,r.end_-r.beg_);
    while(true) {
      if(M(this,ident,&r)) {
        if(M(&(*var)->name_,size)>0) {
          M(&(*var)->type_,append," ");
          M(&(*var)->type_,append,M(&(*var)->name_,c_str));
        }
        M(&(*var)->name_,setn,r.beg_,r.end_-r.beg_);
      } else if(STAR(r)) {
        if(M(&(*var)->name_,size)>0) {
          M(&(*var)->type_,append," ");
          M(&(*var)->type_,append,M(&(*var)->name_,c_str));
          M(&(*var)->name_,clear);
        }
        M(&(*var)->type_,append,"*");
      } else
        break;
    }
    if(M(&(*var)->name_,size)>0)
      ret=true;
    else
      delete(*var);
  }
  if(ret)
    RULE_SUCCESS(p);
  else
    RULE_FAIL(p);
  return ret;
}

static bool yaoocpp_parser_type_only(pointer p,yaoocpp_type_t** type)
{
  yaoocpp_parser_pointer this=p;
  bool ret=false;
  yaooc_terminal_t t;
  yaooc_terminal_t r;
  if(YAOOC_PARSER_TRY_RULE(this,M(this,ident,&t) && SEMICOLON(r))) {
    *type=new(yaoocpp_type);
    M(&(*type)->name_,setn,t.beg_,t.end_-t.beg_);
    ret=true;
  }
  return ret;
}


/* Protected implementation for yaoocpp_parser */

/* Table implementation for yaoocpp_parser */

bool yaoocpp_parser_whitespace(pointer p,yaooc_terminal_t* ws)
{
  *ws=default_terminal(p);
  yaooc_terminal_t temp;
  while(true) {
    if(!yaooc_base_parser_space(p,&temp))
      if(!yaooc_base_parser_crlf(p,&temp))
        if(!yaoocpp_parser_line_directive(p,&temp))
          break;
  }
  ws->end_=yaooc_base_parser_current_pos(p);
  return ws->beg_ != ws->end_;

}

void yaoocpp_parser_parse_file(pointer p,const char* file)
{
  yaooc_terminal_t ws;
  yaoocpp_parser_pointer this=p;
  yaoocpp_parser_current_file=file;
  yaoocpp_parser_preprocess(this);
  this->current_pos_=M(&yaoocpp_parser_buffer,c_str);
  this->classes_=new(yaoocpp_element_pointer_vector);
//  M(this,set_whitespace_types,CRLF|CUSTOM_WHITESPACE);
  M(this,whitespace,&ws);
  yaoocpp_parser_containers(this);
  if(M(this,result)) {
    int handle=open(file,O_RDONLY);
    if(handle>=0) {
      size_t size=lseek(handle,0,SEEK_END);
      lseek(handle,0,SEEK_SET);
      char*buffer = malloc(size+1);
      read(handle,buffer,size);
      close(handle);
      buffer[size]=0;
      yaoocpp_parser_extract_section(this,buffer,"^\\s*#\\s*if.*//\\s*HEADER\\s*$","^\\s*#\\s*endif.*//\\s*HEADER\\s*$",&this->header_text_);
      yaoocpp_parser_extract_section(this,buffer,"^\\s*#\\s*if.*//\\s*SOURCE\\s*$","^\\s*#\\s*endif.*//\\s*SOURCE\\s*$",&this->source_text_);
      yaoocpp_parser_find_yaooc_includes(this,buffer,&this->include_files_);
      free(buffer);
    }
  }
  deletep(&yaoocpp_parser_buffer,yaooc_string);
}


/* Class table definition for yaoocpp_parser */
yaoocpp_parser_class_table_t yaoocpp_parser_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_base_parser_class_table,
  .type_name_ = (const char*) "yaoocpp_parser_t",
  .swap = (void(*)(pointer, pointer)) yaoocpp_parser_swap,
  .set_parse_string = (void(*)(pointer, const char*)) yaoocpp_parser_set_parse_string,
  .rule_start = (void(*)(pointer)) yaoocpp_parser_rule_start,
  .rule_success = (bool(*)(pointer)) yaoocpp_parser_rule_success,
  .rule_fail = (bool(*)(pointer)) yaoocpp_parser_rule_fail,
  .eos = (bool(*)(pointer)) yaoocpp_parser_eos,
  .string_until_chrs = (bool(*)(pointer, const char*, yaooc_terminal_t*)) yaoocpp_parser_string_until_chrs,
  .string_while_chrs = (bool(*)(pointer, const char*, yaooc_terminal_t*)) yaoocpp_parser_string_while_chrs,
  .string_until_eol = (bool(*)(pointer, yaooc_terminal_t*)) yaoocpp_parser_string_until_eol,
  .whitespace = (bool(*)(pointer,yaooc_terminal_t*)) yaoocpp_parser_whitespace,
  .chr = (bool(*)(pointer, char, yaooc_terminal_t*)) yaoocpp_parser_chr,
  .chr_choices = (int(*)(pointer, const char*)) yaoocpp_parser_chr_choices,
  .str = (bool(*)(pointer, const char*, yaooc_terminal_t*)) yaoocpp_parser_str,
  .str_choices = (int(*)(pointer, ...)) yaoocpp_parser_str_choices,
  .digits = (bool(*)(pointer, yaooc_terminal_t*)) yaoocpp_parser_digits,
  .hexdigits = (bool(*)(pointer, yaooc_terminal_t*)) yaoocpp_parser_hexdigits,
  .integer = (bool(*)(pointer, yaooc_terminal_t*)) yaoocpp_parser_integer,
  .hexinteger = (bool(*)(pointer, yaooc_terminal_t*)) yaoocpp_parser_hexinteger,
  .real = (bool(*)(pointer, yaooc_terminal_t*)) yaoocpp_parser_real,
  .ident = (bool(*)(pointer, yaooc_terminal_t*)) yaoocpp_parser_ident,
  .regex = (bool(*)(pointer, const char*, uint32_t, uint32_t, yaooc_terminal_t*)) yaoocpp_parser_regex,
  .quoted_string = (bool(*)(pointer, char, yaooc_terminal_t*)) yaoocpp_parser_quoted_string,
  .single_quoted_string = (bool(*)(pointer, yaooc_terminal_t*)) yaoocpp_parser_single_quoted_string,
  .double_quoted_string = (bool(*)(pointer, yaooc_terminal_t*)) yaoocpp_parser_double_quoted_string,
  .bare_string = (bool(*)(pointer, yaooc_terminal_t*)) yaoocpp_parser_bare_string,
  .string_until_matching_chr = (bool(*)(pointer, char, char, yaooc_terminal_t*)) yaoocpp_parser_string_until_matching_chr,
  .result = (bool(*)(const_pointer)) yaoocpp_parser_result,
  .parse_file = (void(*)(pointer, const char*)) yaoocpp_parser_parse_file,
};

/* Type info structure for yaoocpp_parser */
DEFINE_TYPE_INFO(yaoocpp_parser,Y,Y,N,N,N,N,N,Y,yaooc_base_parser);

/* End YAOOCPP output */
