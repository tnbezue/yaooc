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
yaooc_json_value_pointer yaooc_json_parser_parse_json_null(pointer p)
{
  yaooc_json_parser_pointer this=p;
  yaooc_json_value_t* ret=NULL;
  if(M(this,str,"null").end_) {
    ret=new(yaooc_json_null);
  }
  return ret;
}

yaooc_json_value_pointer yaooc_json_parser_parse_json_bool(pointer p)
{
  yaooc_json_parser_pointer this=p;
  yaooc_json_value_t* ret=NULL;
  if(M(this,str,"true").end_) {
    ret=new_ctor(yaooc_json_bool,yaooc_json_bool_ctor_bool,true);
  } else if(M(this,str,"false").end_) {
    ret=new_ctor(yaooc_json_bool,yaooc_json_bool_ctor_bool,false);
  }
  return ret;
}

yaooc_json_value_pointer yaooc_json_parser_parse_json_integer(pointer p)
{
  yaooc_json_parser_pointer this=p;
  yaooc_json_value_t* ret=NULL;
  yaooc_terminal_t r=M(this,integer);
  if(r.end_) {
//    char* text=M(&r,get_text);
    ret=new_ctor(yaooc_json_integer,yaooc_json_integer_ctor_int,atoll(r.beg_));
//    delete(text);
  }
  return ret;
}

yaooc_json_value_pointer yaooc_json_parser_parse_json_real(pointer p)
{
  yaooc_json_parser_pointer this=p;
  yaooc_json_value_t* ret=NULL;
  yaooc_terminal_t r=M(this,real);
  if(r.end_) {
    ret=new_ctor(yaooc_json_real,yaooc_json_real_ctor_real,atof(r.beg_));
  }
  return ret;
}

yaooc_json_value_pointer yaooc_json_parser_parse_json_string(pointer p)
{
  yaooc_json_parser_pointer this=p;
  yaooc_json_value_t* ret=NULL;
  yaooc_terminal_t r=M(this,double_quoted_string);
  if(r.end_) {
//    char* text=M(&r,get_text);
    ret=new_ctor(yaooc_json_string,yaooc_json_string_ctor_ccs_size,r.beg_,r.end_-r.beg_);
//    delete(text);
  } else if((r=M(this,ident)).end_) {
//    char* text=M(&r,get_text);
    ret=new_ctor(yaooc_json_string,yaooc_json_string_ctor_ccs_size,r.beg_,r.end_-r.beg_);
//    delete(text);
  }
  return ret;
}

yaooc_json_value_pointer yaooc_json_parser_parse_json_array(pointer p)
{
  yaooc_json_parser_pointer this=p;
  yaooc_json_value_t* ret=NULL;
  yaooc_json_value_t* value;
  if(M(this,chr,'[').end_) {
    ret=new(yaooc_json_array);
    while((value=M(this,parse_json_value))!=NULL) {
      M((yaooc_json_array_pointer)ret,insert,value);
      delete(value);
      if(!M(this,chr,',').end_)
        break;
    };
    if(!M(this,chr,']').end_) {
      /* FIX ME */
      /* Should abort */
    }
  }
  return ret;
}
typedef struct {
  yaooc_json_string_t* key;
  yaooc_json_value_t* value;
} yaooc_json_pair_t;

yaooc_json_pair_t yaooc_json_parser_parse_json_pair(pointer p)
{
  yaooc_json_parser_pointer this=p;
  yaooc_json_pair_t ret = { NULL,NULL};
  M(this,rule_start);
  ret.key=(yaooc_json_string_pointer)M(this,parse_json_string);
  if(ret.key && M(this,chr,':').end_) {
    ret.value=M(this,parse_json_value);
  }
  if(ret.value) {
    M(this,rule_success);
  } else {
    M(this,rule_fail);
    if(ret.key) delete(ret.key);
    /*
      Need to mark as error
    */
    ret.key=NULL;
  }
  return ret;
}

yaooc_json_value_pointer yaooc_json_parser_parse_json_object(pointer p)
{
  yaooc_json_parser_pointer this=p;
  yaooc_json_value_t* ret=NULL;
  if(M(this,chr,'{').end_) {
    ret=new(yaooc_json_object);
    yaooc_json_pair_t jp;
    while((jp=yaooc_json_parser_parse_json_pair(this)).key!=NULL) {
      M((yaooc_json_object_pointer)ret,insert,jp.key,jp.value);
      delete(jp.key);
      delete(jp.value);
      jp.key=NULL;
      jp.value=NULL;
      if(!M(this,chr,',').end_)
        break;
    }
    if(!M(this,chr,'}').end_) {
      /* FIX ME */
      /* Should return error */
    }
  }
  return ret;
}

yaooc_json_value_pointer yaooc_json_parser_parse_json_value(pointer p)
{
  yaooc_json_parser_pointer this=p;
  yaooc_json_value_t* ret=NULL;
  if((ret=M(this,parse_json_object))==NULL)
    if((ret=M(this,parse_json_array))==NULL)
      if((ret=M(this,parse_json_bool))==NULL)
        if((ret=M(this,parse_json_null))==NULL)
          if((ret=M(this,parse_json_string))==NULL)
            if((ret=M(this,parse_json_integer))==NULL)
              ret=M(this,parse_json_real);
  return ret;
}

yaooc_json_value_pointer yaooc_json_parser_parse_string(pointer p,const char* str)
{
  yaooc_json_parser_pointer this=p;
  yaooc_json_value_t* ret=NULL;
  if(str) {
    M(this,set_parse_string,str);
    M(this,set_whitespace_types,CRLF|C_COMMENT|CPP_COMMENT|SHELL_COMMENT);
    M(this,whitespace);
    ret=M(this,parse_json_value);
    if(*this->current_pos_!=0)
      puts("Error parsing file");
  }
  return ret;
}

#ifndef _WIN32
#define	O_BINARY 0
#endif
yaooc_json_value_pointer yaooc_json_parser_parse_file(pointer p,const char* file)
{
  yaooc_json_parser_pointer this=p;
  yaooc_json_value_t* ret=NULL;
  struct stat st;
  if(stat(file,&st)==0 && S_ISREG(st.st_mode)) {
    int fh=open(file,O_RDONLY|O_BINARY);
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


/* Class table for yaooc_json_parser */
yaooc_json_parser_class_table_t yaooc_json_parser_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_base_parser_class_table,
  .type_name_ = (const char*) "yaooc_json_parser_t",
  .swap = (void (*) (pointer p,pointer)) yaooc_json_parser_swap,
  .set_parse_string = (void (*) (pointer,const char*)) yaooc_json_parser_set_parse_string,
  .rule_start = (void (*) (pointer p)) yaooc_json_parser_rule_start,
  .rule_success = (void (*) (pointer p)) yaooc_json_parser_rule_success,
  .rule_fail = (void (*) (pointer p)) yaooc_json_parser_rule_fail,
  .eos = (yaooc_terminal_t (*) (pointer p)) yaooc_json_parser_eos,
  .string_until_chrs = (yaooc_terminal_t (*) (pointer p,const char*)) yaooc_json_parser_string_until_chrs,
  .string_while_chrs = (yaooc_terminal_t (*) (pointer p,const char*)) yaooc_json_parser_string_while_chrs,
  .string_until_eol = (yaooc_terminal_t (*) (pointer p)) yaooc_json_parser_string_until_eol,
  .shell_comment = (yaooc_terminal_t (*) (pointer p)) yaooc_json_parser_shell_comment,
  .c_comment = (yaooc_terminal_t (*) (pointer p)) yaooc_json_parser_c_comment,
  .cpp_comment = (yaooc_terminal_t (*) (pointer p)) yaooc_json_parser_cpp_comment,
  .custom_whitespace = (yaooc_terminal_t (*) (pointer p)) yaooc_json_parser_custom_whitespace,
  .set_whitespace_types = (void (*) (pointer p,uint32_t)) yaooc_json_parser_set_whitespace_types,
  .get_whitespace_types = (uint32_t (*) (pointer p)) yaooc_json_parser_get_whitespace_types,
  .whitespace = (int (*) (pointer p)) yaooc_json_parser_whitespace,
  .chr = (yaooc_terminal_t (*) (pointer p,char)) yaooc_json_parser_chr,
  .chr_choices = (int (*) (pointer p,const char*)) yaooc_json_parser_chr_choices,
  .str = (yaooc_terminal_t (*) (pointer p,const char*)) yaooc_json_parser_str,
  .str_choices = (int (*) (pointer p,...)) yaooc_json_parser_str_choices,
  .digits = (yaooc_terminal_t (*) (pointer p)) yaooc_json_parser_digits,
  .hexdigits = (yaooc_terminal_t (*) (pointer p)) yaooc_json_parser_hexdigits,
  .integer = (yaooc_terminal_t (*) (pointer p)) yaooc_json_parser_integer,
  .hexinteger = (yaooc_terminal_t (*) (pointer p)) yaooc_json_parser_hexinteger,
  .real = (yaooc_terminal_t (*) (pointer p)) yaooc_json_parser_real,
  .ident = (yaooc_terminal_t (*) (pointer p)) yaooc_json_parser_ident,
  .regex = (yaooc_terminal_t (*) (pointer p,const char*,uint32_t,uint32_t)) yaooc_json_parser_regex,
  .quoted_string = (yaooc_terminal_t (*) (pointer p,char)) yaooc_json_parser_quoted_string,
  .single_quoted_string = (yaooc_terminal_t (*) (pointer p)) yaooc_json_parser_single_quoted_string,
  .double_quoted_string = (yaooc_terminal_t (*) (pointer p)) yaooc_json_parser_double_quoted_string,
  .bare_string = (yaooc_terminal_t (*) (pointer p)) yaooc_json_parser_bare_string,
  .string_until_matching_chr = (yaooc_terminal_t (*) (pointer p,char,char)) yaooc_json_parser_string_until_matching_chr,
  .parse_json_null = (yaooc_json_value_pointer (*) (pointer p)) yaooc_json_parser_parse_json_null,
  .parse_json_bool = (yaooc_json_value_pointer (*) (pointer p)) yaooc_json_parser_parse_json_bool,
  .parse_json_integer = (yaooc_json_value_pointer (*) (pointer p)) yaooc_json_parser_parse_json_integer,
  .parse_json_real = (yaooc_json_value_pointer (*) (pointer p)) yaooc_json_parser_parse_json_real,
  .parse_json_string = (yaooc_json_value_pointer (*) (pointer p)) yaooc_json_parser_parse_json_string,
  .parse_json_array = (yaooc_json_value_pointer (*) (pointer p)) yaooc_json_parser_parse_json_array,
  .parse_json_object = (yaooc_json_value_pointer (*) (pointer p)) yaooc_json_parser_parse_json_object,
  .parse_json_value = (yaooc_json_value_pointer (*) (pointer p)) yaooc_json_parser_parse_json_value,
  .parse_string = (yaooc_json_value_pointer (*) (pointer p,const char*)) yaooc_json_parser_parse_string,
  .parse_file = (yaooc_json_value_pointer (*) (pointer p,const char*)) yaooc_json_parser_parse_file,
  .result = (yaooc_base_parser_result_t (*) (const_pointer)) yaooc_base_parser_result,
};


DEFINE_TYPE_INFO(yaooc_json_parser,N,N,N,N,N,N,N,Y,yaooc_base_parser)
/*  End YAOOC PreProcessor generated content */
