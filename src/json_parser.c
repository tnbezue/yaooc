#include <yaooc/json_parser.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>

void json_pair_default_ctor(pointer p)
{
  json_pair_pointer this=p;
  this->key=NULL;
  this->value=NULL;
}

void json_pair_dtor(pointer p)
{
  json_pair_pointer this=p;
  if(this->key)
    delete(this->key);
  if(this->value)
    delete(this->value);
}

DEFINE_TYPE_INFO(json_pair,json_pair_default_ctor,json_pair_dtor,NULL,NULL,NULL,NULL,NULL)

void json_parser_default_ctor(pointer p)
{
//  json_parser_pointer this=p;
  yaooc_base_parser_default_ctor(p);
}

void json_parser_swap(pointer p,pointer o)
{
  swap_object(p,o,sizeof(json_parser_t));
}

json_value_pointer json_parser_jnull(pointer p)
{
  json_parser_pointer this=p;
  json_value_pointer ret=NULL;
  if(M(this,str,"null")) {
    ret=new(json_null);
  }
  return ret;
}

json_value_pointer json_parser_jbool(pointer p)
{
  json_parser_pointer this=p;
  json_value_pointer ret=NULL;
  if(M(this,str,"true")) {
    ret=new_ctor(json_bool,json_bool_ctor_bool,true);
  } else if(M(this,str,"false")) {
    ret=new_ctor(json_bool,json_bool_ctor_bool,false);
  }
  return ret;
}

json_value_pointer json_parser_jinteger(pointer p)
{
  json_parser_pointer this=p;
  json_value_pointer ret=NULL;
  yaooc_terminal_t r=M(this,integer);
  if(r.end_) {
    char* text=M(&r,get_text);
    ret=new_ctor(json_integer,json_integer_ctor_int,atoll(text));
    delete(text);
  }
  return ret;
}

json_value_pointer json_parser_jreal(pointer p)
{
  json_parser_pointer this=p;
  json_value_pointer ret=NULL;
  yaooc_terminal_t r=M(this,real);
  if(r.end_) {
    char* text=M(&r,get_text);
    ret=new_ctor(json_real,json_real_ctor_real,atof(text));
    delete(text);
  }
  return ret;
}

json_value_pointer json_parser_jstring(pointer p)
{
  json_parser_pointer this=p;
  json_value_pointer ret=NULL;
  yaooc_terminal_t r=M(this,double_quoted_string);
  if(r.end_) {
    char* text=M(&r,get_text);
    ret=new_ctor(json_string,json_string_ctor_ccs,text);
    delete(text);
  } else if((r=M(this,ident)).end_) {
    char* text=M(&r,get_text);
    ret=new_ctor(json_string,json_string_ctor_ccs,text);
    delete(text);
  }
  return ret;
}

json_value_pointer json_parser_jarray(pointer p)
{
  json_parser_pointer this=p;
  json_value_pointer ret=NULL;
  json_value_pointer value;
  if(M(this,chr,'[')) {
    ret=new(json_array);
    while((value=M(this,jvalue))!=NULL) {
      M((json_array_pointer)ret,add,value);
      delete(value);
      if(!M(this,chr,','))
        break;
    };
    if(!M(this,chr,']')) {
      /* FIX ME */
      /* Should abort */
    }
  }
  return ret;
}

json_pair_pointer json_parser_jpair(pointer p)
{
  json_parser_pointer this=p;
  json_pair_pointer ret=new(json_pair);
  M(this,rule_start);
  if((ret->key=(json_string_pointer)M(this,jstring)) != NULL && M(this,chr,':') && (ret->value=M(this,jvalue))!=NULL) {
    M(this,rule_success);
  } else {
    M(this,rule_fail);
    delete(ret);
    ret=NULL;
  }
  return ret;
}

json_value_pointer json_parser_jobject(pointer p)
{
  json_parser_pointer this=p;
  json_value_pointer ret=NULL;
  if(M(this,chr,'{')) {
    ret=new(json_object);
    json_pair_pointer jp;
    while((jp=M(this,jpair))!=NULL) {
      M((json_object_pointer)ret,insert,jp->key,jp->value);
      delete(jp);
      if(!M(this,chr,','))
        break;
    }
    if(!M(this,chr,'}')) {
      /* FIX ME */
      /* Should return error */
    }
  }
  return ret;
}

json_value_pointer json_parser_jvalue(pointer p)
{
  json_parser_pointer this=p;
  json_value_pointer ret=NULL;
  if((ret=M(this,jobject))==NULL)
    if((ret=M(this,jarray))==NULL)
      if((ret=M(this,jbool))==NULL)
        if((ret=M(this,jnull))==NULL)
          if((ret=M(this,jstring))==NULL)
            if((ret=M(this,jinteger))==NULL)
              ret=M(this,jreal);

  return ret;
}

json_value_pointer json_parser_parse_string(pointer p,const char * str)
{
  json_parser_pointer this=p;
  json_value_pointer ret=NULL;
  if(str) {
    M(this,set_parse_string,str);
    M(this,set_crlf_as_whitespace,true);
    M(this,set_c_comment_as_whitespace,true);
    M(this,set_cpp_comment_as_whitespace,true);
    M(this,set_shell_comment_as_whitespace,true);
    M(this,whitespace);
    ret=M(this,jvalue);
    if(*this->current_pos_!=0)
      puts("Error parsing file");
  }
  return ret;
}

#ifndef _WIN32
#define	O_BINARY 0
#endif
json_value_pointer json_parser_parse_file(pointer p,const char * filename)
{
  json_parser_pointer this=p;
  json_value_pointer ret=NULL;
  struct stat st;
  if(stat(filename,&st)==0 && S_ISREG(st.st_mode)) {
    int fh=open(filename,O_RDONLY|O_BINARY);
		if(fh > 0) {
			char* buffer=(char*)MALLOC(st.st_size+1);
			read(fh,buffer,st.st_size);
			buffer[st.st_size]=0;
			close(fh);
//			puts(buffer);
			ret=M(this,parse_string,buffer);
			FREE(buffer);
		}
  }
  return ret;
}

json_parser_class_members_t json_parser_class_members = {
   { YAOOC_BASE_PARSER_CLASS_MEMBERS },
  (json_value_pointer (*)(pointer)) json_parser_jnull,
  (json_value_pointer (*)(pointer)) json_parser_jbool,
  (json_value_pointer (*)(pointer)) json_parser_jinteger,
  (json_value_pointer (*)(pointer)) json_parser_jreal,
  (json_value_pointer (*)(pointer)) json_parser_jstring,
  (json_value_pointer (*)(pointer)) json_parser_jarray,
  (json_pair_pointer (*)(pointer)) json_parser_jpair,
  (json_value_pointer (*)(pointer)) json_parser_jobject,
  (json_value_pointer (*)(pointer)) json_parser_jvalue,
  (json_value_pointer (*)(pointer,const char *)) json_parser_parse_string,
  (json_value_pointer (*)(pointer,const char *)) json_parser_parse_file,
};

DEFINE_TYPE_INFO(json_parser,json_parser_default_ctor,NULL,NULL,NULL,NULL,&json_parser_class_members,yaooc_base_parser)

