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
#include <ctype.h>

#ifdef __YAOOC_USE_TRE__
#include <tre/regex.h>
#else
#include <regex.h>
#endif
#include <yaooc/base_parser.h>

DEFINE_TYPE_INFO(parser_position,N,N,N,N,N,N,N,N,NULL)
STACK_IMPLEMENTATION(parser_position,parser_position_stack)

void yaooc_terminal_default_ctor(pointer p)
{
  yaooc_terminal_pointer this=p;
  this->beg_=NULL;
  this->end_=NULL;
}

char* yaooc_terminal_get_text(const_pointer p)
{
  char* text=yaooc_terminal_get_raw_text(p);
  if(text) {
    char *inp=text;
    char *out=inp;
    bool finished=false;
    while(*inp != 0 && !finished) {
      if(*inp == '\\') {
        inp++;
        switch(*inp) {
          case 0: // end_ of string
            *out='\\'; // include in string
            finished=true;
            break;

          case 'a':
            *out='\a';
            break;

          case 'b':
            *out='\b';
            break;

          case 'f':
            *out='\f';
            break;

          case 'n':
            *out='\n';
            break;

          case 'r':
            *out='\r';
            break;

          case 't':
            *out='\t';
            break;

          case 'v':
            *out='\v';
            break;

          case '\'':
          case '"':
          case '?':
          case '\\':
            *out=*inp;
            break;

          default:  // put backslash and char in string
            *out++='\\';
            *out=*inp;
        }
      } else
        *out=*inp;
      inp++;
      out++;
    }
    *out=0;

  }
  return text;
}

char* yaooc_terminal_get_raw_text(const_pointer p)
{
  char* text=NULL;
  yaooc_terminal_const_pointer this=p;
  if(this->end_) {
    size_t n=this->end_-this->beg_;
    text=new_array(char,n+1);
    memcpy(text,this->beg_,n);
    text[n]=0;
  }
  return text;
}

yaooc_terminal_class_table_t yaooc_terminal_class_table =
{
  .get_text = yaooc_terminal_get_text,
  .get_raw_text = yaooc_terminal_get_raw_text
};


/*  Begin YAOOC PreProcessor generated content */

/* Private items for yaooc_base_parser */

/* Protected items for yaooc_base_parser */


/* Typeinfo for yaooc_base_parser */
void yaooc_base_parser_default_ctor(pointer p)
{
  yaooc_base_parser_pointer this=p;
  this->current_pos_=NULL;
  this->stack_=new(parser_position_stack);
  this->line_no_=1;
  this->whitespace_types_=0;
}

void yaooc_base_parser_dtor(pointer p)
{
  yaooc_base_parser_pointer this=p;
  delete(this->stack_);
}

/*
void yaooc_base_parser_copy_ctor(pointer d,const_pointer s)
{
  yaooc_base_parser_pointer dst=d;
  yaooc_base_parser_const_pointer src=s;
}

void yaooc_base_parser_assign(pointer d,const_pointer s)
{
  yaooc_base_parser_pointer dst=d;
  yaooc_base_parser_const_pointer src=s;
}
*/
/* Constructors for yaooc_base_parser */

/* Class table methods for yaooc_base_parser */
void yaooc_base_parser_swap(pointer p,pointer o)
{
}

void yaooc_base_parser_set_parse_string(pointer p,const char* pstr)
{
  yaooc_base_parser_pointer this=p;
//  this->string_to_parse_=pstr;
  this->current_pos_=pstr;
}

void yaooc_base_parser_rule_start(pointer p)
{
  yaooc_base_parser_pointer this=p;
  parser_position_t temp={ this->current_pos_,this->line_no_};
  M(this->stack_,push,&temp);
}

void yaooc_base_parser_rule_success(pointer p)
{
  yaooc_base_parser_pointer this=p;
  M(this->stack_,pop);
}

void yaooc_base_parser_rule_fail(pointer p)
{
  yaooc_base_parser_pointer this=p;
  parser_position_t* temp=M(this->stack_,top);
  this->current_pos_=temp->pos_;
  this->line_no_=temp->line_no_;
  M(this->stack_,pop);
}

yaooc_terminal_t yaooc_base_parser_eos(pointer p)
{
  yaooc_base_parser_const_pointer this=p;
  yaooc_terminal_t ret = default_terminal;
  if(*this->current_pos_ == 0) ret.end_=this->current_pos_;
  return ret;
}

yaooc_terminal_t yaooc_base_parser_string_until_chrs(pointer p,const char* chrs)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ret=default_terminal;
  ret.beg_=this->current_pos_;
  size_t n=strcspn(this->current_pos_,chrs);
  if(n>0) {
    this->current_pos_+=n;
    ret.end_=this->current_pos_;
  }
  return ret;
}

yaooc_terminal_t yaooc_base_parser_string_while_chrs(pointer p,const char* chrs)
{
  yaooc_base_parser_pointer this=p;
  size_t n=strspn(this->current_pos_,chrs);
  yaooc_terminal_t ret=default_terminal;
  ret.beg_=this->current_pos_;
  if(n>0) {
    this->current_pos_+=n;
    ret.end_=this->current_pos_;
  }
  return ret;
}

yaooc_terminal_t yaooc_base_parser_string_until_eol(pointer p)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ret=default_terminal;
  ret.end_=yaooc_base_parser_string_until_chrs(p,"\r\n").end_;
  /* remove CR from terminal capture
  while(ret.end_>ret.beg_) {
    if(*ret.end_ != '\r')
      break;
    ret.end_--;
  }*/
  yaooc_base_parser_whitespace(p);
  return ret;
}

yaooc_terminal_t yaooc_base_parser_shell_comment(pointer p)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ret=default_terminal;
  ret.beg_=this->current_pos_;
  if(*this->current_pos_=='#') {
    ret.end_=yaooc_base_parser_string_until_eol(p).end_;
    //yaooc_base_parser_whitespace(p);
  }
  return ret;
}

yaooc_terminal_t yaooc_base_parser_c_comment(pointer p)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ret=default_terminal;
  if(*this->current_pos_=='/' && *(this->current_pos_+1)=='*') {
    this->current_pos_+=2;
    for(;*this->current_pos_!=0;this->current_pos_++) {
      if(*this->current_pos_=='*' && *(this->current_pos_+1)=='/' ) {
        ret.end_=this->current_pos_;
        this->current_pos_+=2;
//        yaooc_base_parser_whitespace(p);
        break;
      }
    }
  }
  return ret;
}

yaooc_terminal_t yaooc_base_parser_cpp_comment(pointer p)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ret=default_terminal;
  ret.beg_=this->current_pos_;
  if(*this->current_pos_=='/' && *(this->current_pos_+1)=='/') {
    this->current_pos_+=2;
    ret.end_=yaooc_base_parser_string_until_eol(p).end_;
  }
  return ret;
}

yaooc_terminal_t yaooc_base_parser_custom_whitespace(pointer p)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ret=default_terminal;

  return ret;
}

void yaooc_base_parser_set_whitespace_types(pointer p,uint32_t ws)
{
  yaooc_base_parser_pointer this=p;
  this->whitespace_types_=ws;
}

uint32_t yaooc_base_parser_get_whitespace_types(pointer p)
{
  yaooc_base_parser_pointer this=p;
  return this->whitespace_types_;
}

int yaooc_base_parser_whitespace(pointer p)
{
  yaooc_base_parser_pointer this=p;
  const char* pos=this->current_pos_;
  while(*this->current_pos_!=0) {
    char cc=*this->current_pos_;
    if(cc==' ' || cc=='\t') {
      this->current_pos_++;
    } else if((this->whitespace_types_ & CRLF) && (cc=='\r' || cc=='\n') ) {
      if(cc=='\n')
        this->line_no_++;
      this->current_pos_++;
    } else if((this->whitespace_types_ & C_COMMENT) && yaooc_base_parser_c_comment(p).end_) {
      continue;
    } else if((this->whitespace_types_ & CPP_COMMENT) && yaooc_base_parser_cpp_comment(p).end_) {
      continue;
    } else if((this->whitespace_types_ & SHELL_COMMENT) && yaooc_base_parser_shell_comment(p).end_) {
      continue;
    } else if((this->whitespace_types_ & CUSTOM_WHITESPACE) && M(this,custom_whitespace).end_) {
      continue;
    } else
      break;
  }
  return this->current_pos_-pos;
}

yaooc_terminal_t yaooc_base_parser_chr(pointer p,char ch)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ret=default_terminal;
  if(*this->current_pos_ == ch) {
    this->current_pos_++;
    ret.end_=this->current_pos_;
    yaooc_base_parser_whitespace(p);
  }
  return ret;
}

int yaooc_base_parser_chr_choices(pointer p,const char* ch_choices)
{
  yaooc_base_parser_pointer this=p;
  int ret=-1;
  const char* ptr=strchr(ch_choices,*this->current_pos_);
  if(ptr) {
    ret=ptr-ch_choices;
    this->current_pos_++;
    yaooc_base_parser_whitespace(p);
  }
  return ret;
}

yaooc_terminal_t yaooc_base_parser_str(pointer p,const char* str)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ret=default_terminal;
  int l=strlen(str);
  if(l>0 && strncmp(this->current_pos_,str,l)==0) {
    this->current_pos_+=l;
    ret.end_=this->current_pos_;
    yaooc_base_parser_whitespace(p);
  }
  return ret;
}

int yaooc_base_parser_str_choices(pointer p,...)
{
//  yaooc_base_parser_pointer this=p;
  int ret=-1;
  int cp=0;
  va_list args;
  va_start (args,p);
  const char* ptr;
  while((ptr=va_arg(args,const char*)) != NULL) {
    if(yaooc_base_parser_str(p,ptr).end_) {
      ret=cp;
      yaooc_base_parser_whitespace(p);
      break;
    }
    cp++;
  }
  va_end(args);
  return ret;
}

yaooc_terminal_t yaooc_base_parser_digits(pointer p)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ret=default_terminal;
  while(*this->current_pos_!=0 && isdigit(*this->current_pos_)) this->current_pos_++;
  ret.end_=this->current_pos_==ret.beg_ ? NULL : this->current_pos_;
  return ret;
}

yaooc_terminal_t yaooc_base_parser_hexdigits(pointer p)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ret=default_terminal;
  while(*this->current_pos_!=0 && isxdigit(*this->current_pos_)) this->current_pos_++;
  ret.end_=this->current_pos_==ret.beg_ ? NULL : this->current_pos_;
  return ret;
}

yaooc_terminal_t yaooc_base_parser_integer(pointer p)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ret=default_terminal;
  M(this,rule_start);
  if(*this->current_pos_=='+' || *this->current_pos_=='-') this->current_pos_++;
  yaooc_terminal_t dr=yaooc_base_parser_digits(p);
  if(dr.end_ && (*this->current_pos_==0 || (*this->current_pos_ !='.' && !isalpha(*this->current_pos_)))) {
    ret.end_=dr.end_;
    M(this,rule_success);
    yaooc_base_parser_whitespace(p);
  } else
    M(this,rule_fail);
  return ret;
}

yaooc_terminal_t yaooc_base_parser_hexinteger(pointer p)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ret=default_terminal;
  if(*this->current_pos_=='0' && toupper(*(this->current_pos_+1))=='X') {
    M(this,rule_start);
    this->current_pos_+=2;
    yaooc_terminal_t dr=yaooc_base_parser_hexdigits(p);
    if(dr.end_ && (*this->current_pos_==0 || (*this->current_pos_ !='.' && !isalpha(*this->current_pos_)))) {
      ret.end_=dr.end_;
      M(this,rule_success);
      yaooc_base_parser_whitespace(p);
    } else
      M(this,rule_fail);
  }
  return ret;
}

yaooc_terminal_t yaooc_base_parser_real(pointer p)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ret=default_terminal;
   bool has_decimal=false;
  yaooc_base_parser_rule_start(p);
  if(*this->current_pos_=='+' || *this->current_pos_=='-') this->current_pos_++;
  yaooc_terminal_t whole=M(this,digits);
  yaooc_terminal_t fraction=default_terminal;
  if(*this->current_pos_=='.') {
    has_decimal=true;
    fraction.beg_=this->current_pos_;
    this->current_pos_++;
    fraction.end_=M(this,digits).end_;
  }
  if(whole.end_ || fraction.end_) {
    if(toupper(*this->current_pos_)=='E') {
      this->current_pos_++;
      yaooc_terminal_t exp=M(this,integer);
      if(exp.end_) {
        ret.end_=exp.end_; // integer already consumed whitespace
      }
    } else {
      /*
        No exponent.  Must have whole and decimal or franction
      */
      if(((whole.end_ && has_decimal) || fraction.end_) && (*this->current_pos_ !='.' && !isalpha(*this->current_pos_))) {
        ret.end_=this->current_pos_;
        M(this,whitespace);
      }
    }
  }
  if(ret.end_)
    M(this,rule_success);
  else
    M(this,rule_fail);
  return ret;
}

yaooc_terminal_t yaooc_base_parser_ident(pointer p)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ret=default_terminal;
  if(isalpha(*this->current_pos_) || *this->current_pos_=='_') {
    do {
      this->current_pos_++;
    } while (isalnum(*this->current_pos_) || *this->current_pos_=='_');
    ret.end_=this->current_pos_;
    M(this,whitespace);
  }
  return ret;
}

yaooc_terminal_t yaooc_base_parser_regex(pointer p,const char* re_str,uint32_t compile_opts,uint32_t match_opts)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ret=default_terminal;
  regex_t re;
  if(regcomp(&re,re_str,compile_opts) == 0) {
    regmatch_t ov;
    int rc = regexec(&re,this->current_pos_,1,&ov,match_opts);
    if(rc == 0 && ov.rm_so == 0) {
      this->current_pos_+=ov.rm_eo;
      ret.end_=this->current_pos_;
      M(this,whitespace);
    }
    regfree(&re);
  }
  return ret;
}

yaooc_terminal_t yaooc_base_parser_quoted_string(pointer p,char quote_char)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ret=default_terminal;
  bool escape=false;
  M(this,rule_start);
  if(*this->current_pos_==quote_char) {
    this->current_pos_++;
    ret.beg_=this->current_pos_;
    for(;*this->current_pos_!=0;this->current_pos_++) {
      if(escape) {
        escape=false;
      } else if(*this->current_pos_=='\\') {
        escape=true;
      } else if(*this->current_pos_==quote_char) {
        ret.end_=this->current_pos_;
        this->current_pos_++;
        M(this,whitespace);
        break;
      }
    }
  }
  if(ret.end_)
    M(this,rule_success);
  else
    M(this,rule_fail);
  return ret;
}

yaooc_terminal_t yaooc_base_parser_single_quoted_string(pointer p)
{
  return yaooc_base_parser_quoted_string(p,'\'');
}

yaooc_terminal_t yaooc_base_parser_double_quoted_string(pointer p)
{
  return yaooc_base_parser_quoted_string(p,'"');
}

yaooc_terminal_t yaooc_base_parser_bare_string(pointer p)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ret=default_terminal;
  if(!isspace(*this->current_pos_)) {
    this->current_pos_++;
    while(*this->current_pos_!=0 && !isspace(*this->current_pos_)) this->current_pos_++;
    ret.end_=this->current_pos_;
  }
  return ret;
}

yaooc_terminal_t yaooc_base_parser_string_until_matching_chr(pointer p,char lch,char rch)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ret=default_terminal;
  int level=1;
  const char* pos=this->current_pos_;
  for(;*pos!= 0;pos++) {
    if(*pos==lch) {
      level++;
    } else if(*pos==rch) {
      if(--level==0) {
        ret.end_=pos;
        this->current_pos_=pos+1;
        M(this,whitespace);
        break;
      }
    }
  }
  return ret;
}

int yaooc_base_parser_result(const_pointer p)
{
  return ((yaooc_base_parser_const_pointer)p)->result_;
}

/* Class table for yaooc_base_parser */
yaooc_base_parser_class_table_t yaooc_base_parser_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "yaooc_base_parser_t",
  .swap = (void (*) (pointer p,pointer)) yaooc_base_parser_swap,
  .set_parse_string = (void (*) (pointer p,const char*)) yaooc_base_parser_set_parse_string,
  .rule_start = (void (*) (pointer p)) yaooc_base_parser_rule_start,
  .rule_success = (void (*) (pointer p)) yaooc_base_parser_rule_success,
  .rule_fail = (void (*) (pointer p)) yaooc_base_parser_rule_fail,
  .eos = (yaooc_terminal_t (*) (pointer p)) yaooc_base_parser_eos,
  .string_until_chrs = (yaooc_terminal_t (*) (pointer p,const char*)) yaooc_base_parser_string_until_chrs,
  .string_while_chrs = (yaooc_terminal_t (*) (pointer p,const char*)) yaooc_base_parser_string_while_chrs,
  .string_until_eol = (yaooc_terminal_t (*) (pointer p)) yaooc_base_parser_string_until_eol,
  .shell_comment = (yaooc_terminal_t (*) (pointer p)) yaooc_base_parser_shell_comment,
  .c_comment = (yaooc_terminal_t (*) (pointer p)) yaooc_base_parser_c_comment,
  .cpp_comment = (yaooc_terminal_t (*) (pointer p)) yaooc_base_parser_cpp_comment,
  .custom_whitespace = (yaooc_terminal_t (*) (pointer p)) yaooc_base_parser_custom_whitespace,
  .set_whitespace_types = (void (*) (pointer p,uint32_t)) yaooc_base_parser_set_whitespace_types,
  .get_whitespace_types = (uint32_t (*) (pointer p)) yaooc_base_parser_get_whitespace_types,
  .whitespace = (int (*) (pointer p)) yaooc_base_parser_whitespace,
  .chr = (yaooc_terminal_t (*) (pointer p,char)) yaooc_base_parser_chr,
  .chr_choices = (int (*) (pointer p,const char*)) yaooc_base_parser_chr_choices,
  .str = (yaooc_terminal_t (*) (pointer p,const char*)) yaooc_base_parser_str,
  .str_choices = (int (*) (pointer p,...)) yaooc_base_parser_str_choices,
  .digits = (yaooc_terminal_t (*) (pointer p)) yaooc_base_parser_digits,
  .hexdigits = (yaooc_terminal_t (*) (pointer p)) yaooc_base_parser_hexdigits,
  .integer = (yaooc_terminal_t (*) (pointer p)) yaooc_base_parser_integer,
  .hexinteger = (yaooc_terminal_t (*) (pointer p)) yaooc_base_parser_hexinteger,
  .real = (yaooc_terminal_t (*) (pointer p)) yaooc_base_parser_real,
  .ident = (yaooc_terminal_t (*) (pointer p)) yaooc_base_parser_ident,
  .regex = (yaooc_terminal_t (*) (pointer p,const char*,uint32_t,uint32_t)) yaooc_base_parser_regex,
  .quoted_string = (yaooc_terminal_t (*) (pointer p,char)) yaooc_base_parser_quoted_string,
  .single_quoted_string = (yaooc_terminal_t (*) (pointer p)) yaooc_base_parser_single_quoted_string,
  .double_quoted_string = (yaooc_terminal_t (*) (pointer p)) yaooc_base_parser_double_quoted_string,
  .bare_string = (yaooc_terminal_t (*) (pointer p)) yaooc_base_parser_bare_string,
  .string_until_matching_chr = (yaooc_terminal_t (*) (pointer p,char,char)) yaooc_base_parser_string_until_matching_chr,
  .result = (int (*) (const_pointer)) yaooc_base_parser_result,
};


DEFINE_TYPE_INFO(yaooc_base_parser,Y,Y,N,N,N,N,N,Y,yaooc_object)
/*  End YAOOC PreProcessor generated content */
