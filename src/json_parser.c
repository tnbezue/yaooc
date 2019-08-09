/*
		Copyright (C) 2016-2019  by Terry N Bezue

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
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <ctype.h>
#include <yaooc/json_parser.h>

/*  Begin YAOOC PreProcessor generated content */

/* Private items for yaooc_json_parser */

/* Protected items for yaooc_json_parser */


/* Typeinfo for yaooc_json_parser */
/* Constructors for yaooc_json_parser */

/* Class table methods for yaooc_json_parser */
bool yaooc_json_parser_whitespace(pointer p,yaooc_terminal_t* r)
{
  *r=default_terminal(p);
  yaooc_terminal_t ws;
  while(true) {
    if(!yaooc_base_parser_space(p,&ws))
      if(!yaooc_base_parser_crlf(p,&ws))
        if(!yaooc_base_parser_c_comment(p,&ws))
          if(!yaooc_base_parser_cpp_comment(p,&ws))
            if(!yaooc_base_parser_shell_comment(p,&ws))
              break;
  }
  r->end_=yaooc_base_parser_current_pos(p);
  return r->beg_!=r->end_;
}
bool yaooc_json_parser_parse_json_null(pointer p,yaooc_json_value_t** jnull)
{
  yaooc_json_parser_pointer this=p;
  bool ret=false;
  yaooc_terminal_t r;
  if(M(this,str,"null",&r)) {
    *jnull=new(yaooc_json_null);
    ret=true;
  }
  return ret;
}

bool yaooc_json_parser_parse_json_bool(pointer p,yaooc_json_value_t** jbool)
{
  yaooc_json_parser_pointer this=p;
  bool ret=false;
  yaooc_terminal_t r;
  if(M(this,str,"true",&r) || M(this,str,"false",&r)) {
    *jbool=new_ctor(yaooc_json_bool,yaooc_json_bool_ctor_bool,*r.beg_=='t');
    ret=true;
  }
  return ret;
}

bool yaooc_json_parser_parse_json_integer(pointer p,yaooc_json_value_t** jinteger)
{
  yaooc_json_parser_pointer this=p;
  bool ret=false;
  yaooc_terminal_t r;
  if(M(this,integer,&r)) {
//    char* text=M(&r,get_text);
    *jinteger=new_ctor(yaooc_json_integer,yaooc_json_integer_ctor_int,atoll(r.beg_));
//    delete(text);
    ret=true;
  }
  return ret;
}

bool yaooc_json_parser_parse_json_real(pointer p,yaooc_json_value_t** jreal)
{
  yaooc_json_parser_pointer this=p;
  bool ret=false;
  yaooc_terminal_t r;
  if(M(this,real,&r)) {
    *jreal=new_ctor(yaooc_json_real,yaooc_json_real_ctor_real,atof(r.beg_));
    ret=true;
  }
  return ret;
}

bool yaooc_json_parser_parse_json_string(pointer p,yaooc_json_value_t** jstring)
{
  yaooc_json_parser_pointer this=p;
  bool ret=false;
  yaooc_terminal_t r;
  if(M(this,double_quoted_string,&r) || M(this,ident,&r)) {
    *jstring=new_ctor(yaooc_json_string,yaooc_json_string_ctor_ccs_size,r.beg_,r.end_-r.beg_);
    ret=true;
  }
  return ret;
}

bool yaooc_json_parser_parse_json_array(pointer p,yaooc_json_value_t** jarray)
{
  yaooc_json_parser_pointer this=p;
  bool ret=false;
  yaooc_json_value_t* value;
  yaooc_terminal_t r;
  RULE_START(p);
  if(M(this,chr,'[',&r)) {
    *jarray=new(yaooc_json_array);
    ret=true;
    while(true) {
      if(!M(this,parse_json_value,&value)) {
        // Array can be empty.  However, one or more items in array means that a comma
        // preceded this attempt to obtain a jvalue -- thus this will be a syntax error
        if(M((yaooc_json_array_t*)*jarray,size) == 0)
          break;
        else
          break;  /* FIX ME  -- Throw exception */
      }
      M((yaooc_json_array_pointer)*jarray,insert,value);
      delete(value);
      if(!M(this,chr,',',&r))
        break;
    }
    if(!M(this,chr,']',&r)) {
      /* FIX ME */
      /* Should throw exception */
      ret=false;
    }
  }
  if(ret)
    RULE_SUCCESS(p);
  else
    RULE_FAIL(p);
  return ret;
}

typedef struct {
  yaooc_json_string_t* key;
  yaooc_json_value_t* value;
} yaooc_json_pair_t;

bool yaooc_json_parser_parse_json_pair(pointer p,yaooc_json_pair_t* jpair)
{
  yaooc_json_parser_pointer this=p;
  bool ret=false;
  *jpair = (yaooc_json_pair_t){ NULL,NULL};
  RULE_START(p);
  yaooc_terminal_t r;
  if(M(this,parse_json_string,(yaooc_json_value_t**)&jpair->key) && M(this,chr,':',&r)) {
    if(M(this,parse_json_value,(yaooc_json_value_t**)&jpair->value)) {
      RULE_SUCCESS(p);
      ret=true;
    } else {
      RULE_FAIL(p);
      if(jpair->key) delete(jpair->key);
      if(jpair->value) delete(jpair->value);
      ret=false;
    }
  }
  return ret;
}

bool yaooc_json_parser_parse_json_object(pointer p,yaooc_json_value_t** jobject)
{
  yaooc_json_parser_pointer this=p;
  bool ret=false;
  yaooc_terminal_t r;
  if(M(this,chr,'{',&r)) {
    ret=true;
    *jobject=new(yaooc_json_object);
    yaooc_json_pair_t jp;
    while(yaooc_json_parser_parse_json_pair(this,&jp)) {
      M((yaooc_json_object_pointer)*jobject,insert,jp.key,jp.value);
      delete(jp.key);
      delete(jp.value);
      jp.key=NULL;
      jp.value=NULL;
      if(!M(this,chr,',',&r))
        break;
    }
    if(!M(this,chr,'}',&r)) {
      /* FIX ME */
      /* Should return error */
    }
  }
  return ret;
}

bool yaooc_json_parser_parse_json_value(pointer p,yaooc_json_value_t** jvalue)
{
  yaooc_json_parser_pointer this=p;
  bool ret=true;
  if(!M(this,parse_json_object,jvalue))
    if(!M(this,parse_json_array,jvalue))
      if(!M(this,parse_json_bool,jvalue))
        if(!M(this,parse_json_null,jvalue))
          if(!M(this,parse_json_string,jvalue))
            if(!M(this,parse_json_integer,jvalue))
              if(!M(this,parse_json_real,jvalue))
                ret=false;
  return ret;
}

bool yaooc_json_parser_parse_string(pointer p,const char* str,yaooc_json_value_t** jvalue)
{
  yaooc_json_parser_pointer this=p;
  bool ret=true;
  yaooc_terminal_t ws;
  if(str) {
    M(this,set_parse_string,str);
    M(this,whitespace,&ws);
    ret=M(this,parse_json_value,jvalue);
    if(*this->current_pos_!=0)
      puts("Error parsing file");
  }
  return ret;
}

#ifndef _WIN32
#define	O_BINARY 0
#endif
bool yaooc_json_parser_parse_file(pointer p,const char* file,yaooc_json_value_t** jvalue)
{
  yaooc_json_parser_pointer this=p;
  bool ret=false;
  struct stat st;
  if(stat(file,&st)==0 && S_ISREG(st.st_mode)) {
    int fh=open(file,O_RDONLY|O_BINARY);
		if(fh > 0) {
			char* buffer=(char*)MALLOC(st.st_size+1);
			read(fh,buffer,st.st_size);
			buffer[st.st_size]=0;
			close(fh);
//			puts(buffer);
			ret=M(this,parse_string,buffer,jvalue);
			FREE(buffer);
		}
  }
  return ret;
}


/* Class table for yaooc_json_parser */
yaooc_json_parser_class_table_t yaooc_json_parser_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_base_parser_class_table,
  .type_name_ = (const char*) "yaooc_json_parser_t",
  .swap = (void(*)(pointer, pointer)) yaooc_json_parser_swap,
  .set_parse_string = (void(*)(pointer, const char*)) yaooc_json_parser_set_parse_string,
  .rule_start = (void(*)(pointer)) yaooc_json_parser_rule_start,
  .rule_success = (bool(*)(pointer)) yaooc_json_parser_rule_success,
  .rule_fail = (bool(*)(pointer)) yaooc_json_parser_rule_fail,
  .eos = (bool(*)(pointer)) yaooc_json_parser_eos,
  .string_until_chrs = (bool(*)(pointer, const char*, yaooc_terminal_t*)) yaooc_json_parser_string_until_chrs,
  .string_while_chrs = (bool(*)(pointer, const char*, yaooc_terminal_t*)) yaooc_json_parser_string_while_chrs,
  .string_until_eol = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_json_parser_string_until_eol,
  .whitespace = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_json_parser_whitespace,
  .chr = (bool(*)(pointer, char, yaooc_terminal_t*)) yaooc_json_parser_chr,
  .chr_choices = (int(*)(pointer, const char*)) yaooc_json_parser_chr_choices,
  .str = (bool(*)(pointer, const char*, yaooc_terminal_t*)) yaooc_json_parser_str,
  .str_choices = (int(*)(pointer, ...)) yaooc_json_parser_str_choices,
  .digits = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_json_parser_digits,
  .hexdigits = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_json_parser_hexdigits,
  .integer = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_json_parser_integer,
  .hexinteger = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_json_parser_hexinteger,
  .real = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_json_parser_real,
  .ident = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_json_parser_ident,
  .regex = (bool(*)(pointer, const char*, uint32_t, uint32_t, yaooc_terminal_t*)) yaooc_json_parser_regex,
  .quoted_string = (bool(*)(pointer, char, yaooc_terminal_t*)) yaooc_json_parser_quoted_string,
  .single_quoted_string = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_json_parser_single_quoted_string,
  .double_quoted_string = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_json_parser_double_quoted_string,
  .bare_string = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_json_parser_bare_string,
  .string_until_matching_chr = (bool(*)(pointer, char, char, yaooc_terminal_t*)) yaooc_json_parser_string_until_matching_chr,
  .result = (bool(*)(const_pointer)) yaooc_json_parser_result,
  .parse_json_null = (bool(*)(pointer,yaooc_json_value_t**)) yaooc_json_parser_parse_json_null,
  .parse_json_bool = (bool(*)(pointer,yaooc_json_value_t**)) yaooc_json_parser_parse_json_bool,
  .parse_json_integer = (bool(*)(pointer,yaooc_json_value_t**)) yaooc_json_parser_parse_json_integer,
  .parse_json_real = (bool(*)(pointer,yaooc_json_value_t**)) yaooc_json_parser_parse_json_real,
  .parse_json_string = (bool(*)(pointer,yaooc_json_value_t**)) yaooc_json_parser_parse_json_string,
  .parse_json_array = (bool(*)(pointer,yaooc_json_value_t**)) yaooc_json_parser_parse_json_array,
  .parse_json_object = (bool(*)(pointer,yaooc_json_value_t**)) yaooc_json_parser_parse_json_object,
  .parse_json_value = (bool(*)(pointer,yaooc_json_value_t**)) yaooc_json_parser_parse_json_value,
  .parse_string = (bool(*)(pointer, const char*,yaooc_json_value_t**)) yaooc_json_parser_parse_string,
  .parse_file = (bool(*)(pointer, const char*,yaooc_json_value_t**)) yaooc_json_parser_parse_file,
};


DEFINE_TYPE_INFO(yaooc_json_parser,N,N,N,N,N,N,N,Y,yaooc_base_parser)
/*  End YAOOC PreProcessor generated content */
