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

DEFINE_MIN_TYPE_INFO(parser_position);
//DEFINE_TYPE_INFO(parser_position,N,N,N,N,N,N,N,N,NULL)
STACK_IMPLEMENTATION(parser_position,parser_position_stack);
DEFINE_MIN_TYPE_INFO(yaooc_terminal);

char* yaooc_terminal_text(const_pointer p)
{
  char* text=yaooc_terminal_raw_text(p);
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

char* yaooc_terminal_raw_text(const_pointer p)
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
/*
yaooc_terminal_class_table_t yaooc_terminal_class_table =
{
  .get_text = yaooc_terminal_get_text,
  .get_raw_text = yaooc_terminal_get_raw_text
};
*/

/*  Begin YAOOC PreProcessor generated content */

/* Private items for yaooc_base_parser */

/* Protected items for yaooc_base_parser */

int yaooc_base_parser_next_chr(pointer p)
{
  yaooc_base_parser_pointer this=p;
  int c=*this->current_pos_;
  if(c=='\n') this->line_no_++;
  if(c!=0) this->current_pos_++;
  return c;
}

bool yaooc_base_parser_space(pointer p,yaooc_terminal_t* r)
{
  yaooc_base_parser_pointer this=p;
  *r=default_terminal(p);
  for(;*this->current_pos_!=0;this->current_pos_++) {
    if(*this->current_pos_ != ' ' && *this->current_pos_ != '\t')
      break;
  }
  r->end_=this->current_pos_;
  return r->end_!=r->beg_;
}

bool yaooc_base_parser_crlf(pointer p,yaooc_terminal_t* r)
{
  yaooc_base_parser_pointer this=p;
  *r=default_terminal(p);
  for(;*this->current_pos_ != 0;this->current_pos_++) {
    if(*this->current_pos_ != '\r') {
      if(*this->current_pos_ == '\n')
        this->line_no_++;
      else
        break;
    }
  }
  r->end_=this->current_pos_;
  return r->end_!=r->beg_;
}

bool yaooc_base_parser_shell_comment(pointer p,yaooc_terminal_t* r)
{
  yaooc_base_parser_pointer this=p;
  *r=default_terminal(p);
  r->beg_=yaooc_base_parser_current_pos(this);
  if(*this->current_pos_ =='#') {
    for(;*this->current_pos_ != 0;this->current_pos_++)
      if(*this->current_pos_=='\r' || *this->current_pos_=='\n') {
        r->end_=this->current_pos_;
        break;
      }
  }
  return r->end_!=NULL;
}

bool yaooc_base_parser_c_comment(pointer p,yaooc_terminal_t* r)
{
  yaooc_base_parser_pointer this=p;
  *r=default_terminal(p);
  RULE_START(p);
//  printf("*** C is %d (%c)\n",c,c);
  if(*this->current_pos_ =='/' && *(this->current_pos_+1) =='*') {
    this->current_pos_+=2;
    for(;*this->current_pos_!=0;this->current_pos_++) {
      if(*this->current_pos_ == '*' && *(this->current_pos_+1) == '/') {
        this->current_pos_+=2;
        r->end_=this->current_pos_;
        break;
      }
//            M(this,whitespace,&ws);
    }
  }
  if(r->end_)
    RULE_SUCCESS(p);
  else
    RULE_FAIL(p);
  return r->end_!=NULL;
}

bool yaooc_base_parser_cpp_comment(pointer p,yaooc_terminal_t* r)
{
  yaooc_base_parser_pointer this=p;
  *r=default_terminal(p);
//  r->beg_=this->current_pos_;
  RULE_START(p);
  if(*this->current_pos_ =='/' && *(this->current_pos_+1) =='/') {
    this->current_pos_+=2;
    for(;*this->current_pos_ != 0;this->current_pos_++)
      if(*this->current_pos_=='\r' || *this->current_pos_=='\n') {
        r->end_=this->current_pos_;
        break;
      }
  }
  if(r->end_)
    RULE_SUCCESS(p);
  else
    RULE_FAIL(p);
  return r->end_!=NULL;
}

/* Typeinfo for yaooc_base_parser */
void yaooc_base_parser_default_ctor(pointer p)
{
  yaooc_base_parser_pointer this=p;
  this->current_pos_=NULL;
  this->stack_=new(parser_position_stack);
  this->line_no_=1;
//  this->whitespace_types_=0;
}

void yaooc_base_parser_dtor(pointer p)
{
  yaooc_base_parser_pointer this=p;
  delete(this->stack_);
}

/* Constructors for yaooc_base_parser */

/* Class table methods for yaooc_base_parser */
void yaooc_base_parser_swap(pointer p,pointer o)
{
}

void yaooc_base_parser_set_parse_string(pointer p,const char* pstr)
{
  yaooc_base_parser_pointer this=p;
  this->line_no_=1;
  this->current_pos_=pstr;
}

void yaooc_base_parser_rule_start(pointer p)
{
  yaooc_base_parser_pointer this=p;
  parser_position_t temp={ this->current_pos_,this->line_no_};
  M(this->stack_,push,&temp);
}

bool yaooc_base_parser_rule_success(pointer p)
{
  yaooc_base_parser_pointer this=p;
  M(this->stack_,pop);
  return true;
}

bool yaooc_base_parser_rule_fail(pointer p)
{
  yaooc_base_parser_pointer this=p;
  parser_position_t* temp=M(this->stack_,top);
  this->current_pos_=temp->pos_;
  this->line_no_=temp->line_no_;
  M(this->stack_,pop);
  return false;
}

bool yaooc_base_parser_eos(pointer p)
{
  yaooc_base_parser_const_pointer this=p;
  return *this->current_pos_ == 0;
}

bool yaooc_base_parser_string_until_chrs(pointer p,const char* chrs,yaooc_terminal_t* r)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ws;
  *r=default_terminal(p);
//  r->beg_=this->current_pos_;
  size_t n=strcspn(this->current_pos_,chrs);
  if(n>0) {
    yaooc_base_parser_skip(this,n); //this->current_pos_+=n;
    r->end_=yaooc_base_parser_current_pos(this);
    M(this,whitespace,&ws);
  }
  return r->end_!=NULL;
}

bool yaooc_base_parser_string_while_chrs(pointer p,const char* chrs,yaooc_terminal_t* r)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ws;
  size_t n=strspn(this->current_pos_,chrs);
  *r=default_terminal(p);
//  r->beg_=this->current_pos_;
  if(n>0) {
    yaooc_base_parser_skip(this,n); //this->current_pos_+=n;
    r->end_=yaooc_base_parser_current_pos(this);
    M(this,whitespace,&ws);
  }
  return r->end_!=NULL;
}

bool yaooc_base_parser_string_until_eol(pointer p,yaooc_terminal_t* r)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ws;
  *r=default_terminal(p);
  yaooc_base_parser_string_until_chrs(p,"\r\n",r);
  /* remove CR from terminal capture
  while(ret.end_>ret.beg_) {
    if(*ret.end_ != '\r')
      break;
    ret.end_--;
  }*/
  if(r->end_!=NULL) {
      M(this,whitespace,&ws);
    return true;
  }
  return false;
}


/*
  Derived classes should override this

bool yaooc_base_parser_custom_whitespace(pointer p,yaooc_terminal_t* r)
{
//  yaooc_base_parser_pointer this=p;
//  yaooc_terminal_t ret=default_terminal(p);

  return false;
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
*/
/*
  Derived classes that want to use a different whitespace routine should use the following
  as a template
 */
bool yaooc_base_parser_whitespace(pointer p,yaooc_terminal_t* r)
{
//  yaooc_base_parser_pointer this=p;
  *r=default_terminal(p);
  yaooc_terminal_t temp;
  while(true) {
    if(!yaooc_base_parser_space(p,&temp))
      if(!yaooc_base_parser_crlf(p,&temp))
      break;
  }
  r->end_=yaooc_base_parser_current_pos(p);
  return r->beg_ != r->end_;
#if 0
  while(*this->current_pos_!=0) {
    char cc=yaooc_base_parser_peek(p);
    if(cc==' ' || cc=='\t') {
      yaooc_base_parser_next_chr(p);
    } else if((this->whitespace_types_ & CRLF) && (cc=='\r' || cc=='\n') ) {
      yaooc_base_parser_next_chr(p);
    } else if((this->whitespace_types_ & C_COMMENT) && yaooc_base_parser_c_comment(p,&r)) {
      continue;
    } else if((this->whitespace_types_ & CPP_COMMENT) && yaooc_base_parser_cpp_comment(p,&r)) {
      continue;
    } else if((this->whitespace_types_ & SHELL_COMMENT) && yaooc_base_parser_shell_comment(p,&r)) {
      continue;
    } else if((this->whitespace_types_ & CUSTOM_WHITESPACE) && M(this,custom_whitespace,&r)) {
      continue;
    } else
      break;
  }
  return this->current_pos_-pos;
#endif
}

bool yaooc_base_parser_chr(pointer p,char ch,yaooc_terminal_t* r)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ws;
  *r=default_terminal(p);
  if(yaooc_base_parser_peek(p) == ch) {
    yaooc_base_parser_next_chr(p);
    r->end_=yaooc_base_parser_current_pos(p);
      M(this,whitespace,&ws);
  }
  return r->end_!=NULL;
}

int yaooc_base_parser_chr_choices(pointer p,const char* ch_choices)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ws;
  int ret=-1;
  const char* ptr=strchr(ch_choices,yaooc_base_parser_peek(p));
  if(ptr) {
    ret=ptr-ch_choices;
    yaooc_base_parser_next_chr(p);
    M(this,whitespace,&ws);
  }
  return ret;
}

bool yaooc_base_parser_str(pointer p,const char* str,yaooc_terminal_t* r)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ws;
  *r=default_terminal(p);
  int l=strlen(str);
  if(l>0 && strncmp(this->current_pos_,str,l)==0) {
    yaooc_base_parser_skip(p,l);
    r->end_=this->current_pos_;
    M(this,whitespace,&ws);
  }
  return r->end_!=NULL;
}

int yaooc_base_parser_str_choices(pointer p,...)
{
//  yaooc_base_parser_pointer this=p;
  int ret=-1;
  int cp=0;
  va_list args;
  va_start (args,p);
  const char* ptr;
  yaooc_terminal_t r;
  while((ptr=va_arg(args,const char*)) != NULL) {
    if(yaooc_base_parser_str(p,ptr,&r)) {
      ret=cp;
//      yaooc_base_parser_whitespace(p);
      break;
    }
    cp++;
  }
  va_end(args);
  return ret;
}

bool yaooc_base_parser_digits(pointer p,yaooc_terminal_t* r)
{
  yaooc_base_parser_pointer this=p;
  *r=default_terminal(p);
  int c=yaooc_base_parser_peek(p);
  for(;c!=0 && isdigit(c);c=yaooc_base_parser_peek(p))
    yaooc_base_parser_next_chr(p);
//  while(*this->current_pos_!=0 && isdigit(yaooc_base_parser_peek(p)))
//    yaooc_base_parser_next_chr(p);
  r->end_=this->current_pos_==r->beg_ ? NULL : this->current_pos_;
  return r->end_!=NULL;
}

bool yaooc_base_parser_hexdigits(pointer p,yaooc_terminal_t* r)
{
  yaooc_base_parser_pointer this=p;
  *r=default_terminal(p);
  while(*this->current_pos_!=0 && isxdigit(yaooc_base_parser_peek(p)))
    yaooc_base_parser_next_chr(p);
  r->end_=this->current_pos_==r->beg_ ? NULL : this->current_pos_;
  return r->end_!=NULL;
}

bool yaooc_base_parser_integer(pointer p,yaooc_terminal_t* r)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ws;
  *r=default_terminal(p);
  RULE_START(p);
  if(yaooc_base_parser_peek(p)=='+' || yaooc_base_parser_peek(p)=='-')
    yaooc_base_parser_next_chr(p);
  yaooc_terminal_t dr;
  if(yaooc_base_parser_digits(p,&dr) && (yaooc_base_parser_peek(p)==0
        || (yaooc_base_parser_peek(p) !='.' && !isalpha(yaooc_base_parser_peek(p))))) {
    r->end_=dr.end_;
    RULE_SUCCESS(p);
    M(this,whitespace,&ws);
    return true;
  } else
    RULE_FAIL(p);
  return false;
}

bool yaooc_base_parser_hexinteger(pointer p,yaooc_terminal_t* r)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ws;
  *r=default_terminal(p);
  RULE_START(p);
  if(yaooc_base_parser_next_chr(p)=='0' && toupper(yaooc_base_parser_next_chr(p))=='X') {
    yaooc_terminal_t dr;
    if(yaooc_base_parser_hexdigits(p,&dr)) {
      r->end_=dr.end_;
      M(this,whitespace,&ws);
    }
  }
  if(r->end_)
    RULE_SUCCESS(p);
  else
    RULE_FAIL(p);
  return r->end_!=NULL;
}

bool yaooc_base_parser_real(pointer p,yaooc_terminal_t* r)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ws;
  *r=default_terminal(p);
  bool has_decimal=false;
  RULE_START(p);
  if(yaooc_base_parser_peek(p)=='+' || yaooc_base_parser_peek(p)=='-')
    yaooc_base_parser_next_chr(p);
  yaooc_terminal_t whole;
  M(this,digits,&whole);
  yaooc_terminal_t fraction=default_terminal(p);
  if(yaooc_base_parser_peek(p)=='.') {
    has_decimal=true;
//    fraction.beg_=this->current_pos_;
    yaooc_base_parser_next_chr(p);
    M(this,digits,&fraction);
  }
  if(whole.end_ || fraction.end_) {
    if(toupper(yaooc_base_parser_peek(p))=='E') {
      yaooc_base_parser_next_chr(p);
      yaooc_terminal_t exp;
      M(this,integer,&exp);
      if(exp.end_) {
        r->end_=exp.end_; // integer already consumed whitespace
      }
    } else {
      /*
        No exponent.  Must have whole and decimal or franction
      */
      if(((whole.end_ && has_decimal) || fraction.end_) &&
              (yaooc_base_parser_peek(p) != '.' && !isalpha(yaooc_base_parser_peek(p)))) {
        r->end_=this->current_pos_;
        M(this,whitespace,&ws);
      }
    }
  }
  if(r->end_)
    RULE_SUCCESS(p);
  else
    RULE_FAIL(p);
  return r->end_!=NULL;
}

bool yaooc_base_parser_ident(pointer p,yaooc_terminal_t* r)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ws;
  *r=default_terminal(p);
  int c=yaooc_base_parser_peek(p);
  if(isalpha(c) || c =='_') {
    do {
      yaooc_base_parser_next_chr(p);
      c=yaooc_base_parser_peek(p);
    } while (c !=0 && (isalnum(c) || c == '_'));
    r->end_=yaooc_base_parser_current_pos(p);
    M(this,whitespace,&ws);
  }
  return r->end_!=NULL;
}

bool yaooc_base_parser_regex(pointer p,const char* re_str,uint32_t compile_opts,
        uint32_t match_opts,yaooc_terminal_t* r)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ws;
  *r=default_terminal(p);
  regex_t re;
  if(regcomp(&re,re_str,compile_opts) == 0) {
    regmatch_t ov;
    int rc = regexec(&re,this->current_pos_,1,&ov,match_opts);
    if(rc == 0 && ov.rm_so == 0) {
      yaooc_base_parser_skip(p,ov.rm_eo);
      r->end_=yaooc_base_parser_current_pos(p);
      M(this,whitespace,&ws);
    }
    regfree(&re);
  }
  return r->end_!=NULL;
}

bool yaooc_base_parser_quoted_string(pointer p,char quote_char,yaooc_terminal_t* r)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ws;
  *r=default_terminal(p);
  bool escape=false;
  RULE_START(p);
  int c=yaooc_base_parser_next_chr(p);
  if(c==quote_char) {
    r->beg_=yaooc_base_parser_current_pos(p);
  do {
      c=yaooc_base_parser_next_chr(p);
      if(escape) {
        escape=false;
      } else if(c=='\\') {
        escape=true;
      } else if(c==quote_char) {
        r->end_=yaooc_base_parser_current_pos(p)-1;
        M(this,whitespace,&ws);
        break;
      }
    } while(c != 0);
  }
  if(r->end_)
    RULE_SUCCESS(p);
  else
    RULE_FAIL(p);
  return r->end_!=NULL;
}

bool yaooc_base_parser_single_quoted_string(pointer p,yaooc_terminal_t* r)
{
  return yaooc_base_parser_quoted_string(p,'\'',r);
}

bool yaooc_base_parser_double_quoted_string(pointer p,yaooc_terminal_t* r)
{
  return yaooc_base_parser_quoted_string(p,'"',r);
}

bool yaooc_base_parser_bare_string(pointer p,yaooc_terminal_t* r)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ws;
  *r=default_terminal(p);
  int c=yaooc_base_parser_peek(p);
  if(!isspace(c)) {
    for(;c!=0;c=yaooc_base_parser_peek(p)) {
      if(isspace(c))
        break;
      yaooc_base_parser_next_chr(p);
    }
//    while(*this->current_pos_!=0 && !isspace(*this->current_pos_)) this->current_pos_++;
    r->end_=this->current_pos_;
    M(this,whitespace,&ws);
  }
  return r->end_!=NULL;
}

/*
*/
bool yaooc_base_parser_string_until_matching_chr(pointer p,char lch,char rch,yaooc_terminal_t* r)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t ws;
  *r=default_terminal(p);
  int level=0;
  RULE_START(p);
  if(*this->current_pos_ == lch) {
    char c=yaooc_base_parser_next_chr(p);
    r->beg_ = this->current_pos_;
    for(;c!= 0;c=yaooc_base_parser_next_chr(p)) {
      if(c==lch) {
        level++;
      } else if(c==rch) {
        if(--level==0) {
          r->end_=yaooc_base_parser_current_pos(p)-1;
          M(this,whitespace,&ws);
          break;
        }
      }
    }
  }
  if(r->end_)
    RULE_SUCCESS(p);
  else
    RULE_FAIL(p);
  return r->end_!=NULL;
}

bool yaooc_base_parser_result(const_pointer p)
{
  return *(((yaooc_base_parser_const_pointer)p)->current_pos_)==0;
}

/* Class table for yaooc_base_parser */
yaooc_base_parser_class_table_t yaooc_base_parser_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "yaooc_base_parser_t",
  .swap = (void(*)(pointer, pointer)) yaooc_base_parser_swap,
  .set_parse_string = (void(*)(pointer, const char*)) yaooc_base_parser_set_parse_string,
  .rule_start = (void(*)(pointer)) yaooc_base_parser_rule_start,
  .rule_success = (bool(*)(pointer)) yaooc_base_parser_rule_success,
  .rule_fail = (bool(*)(pointer)) yaooc_base_parser_rule_fail,
  .eos = (bool(*)(pointer)) yaooc_base_parser_eos,
  .string_until_chrs = (bool(*)(pointer, const char*, yaooc_terminal_t*)) yaooc_base_parser_string_until_chrs,
  .string_while_chrs = (bool(*)(pointer, const char*, yaooc_terminal_t*)) yaooc_base_parser_string_while_chrs,
  .string_until_eol = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_base_parser_string_until_eol,
#if 0
  .shell_comment = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_base_parser_shell_comment,
  .c_comment = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_base_parser_c_comment,
  .cpp_comment = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_base_parser_cpp_comment,
  .custom_whitespace = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_base_parser_custom_whitespace,
  .set_whitespace_types = (void(*)(pointer, uint32_t)) yaooc_base_parser_set_whitespace_types,
  .get_whitespace_types = (uint32_t(*)(pointer)) yaooc_base_parser_get_whitespace_types,
#endif
  .whitespace = (bool(*)(pointer,yaooc_terminal_t*)) yaooc_base_parser_whitespace,
  .chr = (bool(*)(pointer, char, yaooc_terminal_t*)) yaooc_base_parser_chr,
  .chr_choices = (int(*)(pointer, const char*)) yaooc_base_parser_chr_choices,
  .str = (bool(*)(pointer, const char*, yaooc_terminal_t*)) yaooc_base_parser_str,
  .str_choices = (int(*)(pointer, ...)) yaooc_base_parser_str_choices,
  .digits = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_base_parser_digits,
  .hexdigits = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_base_parser_hexdigits,
  .integer = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_base_parser_integer,
  .hexinteger = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_base_parser_hexinteger,
  .real = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_base_parser_real,
  .ident = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_base_parser_ident,
  .regex = (bool(*)(pointer, const char*, uint32_t, uint32_t, yaooc_terminal_t*)) yaooc_base_parser_regex,
  .quoted_string = (bool(*)(pointer, char, yaooc_terminal_t*)) yaooc_base_parser_quoted_string,
  .single_quoted_string = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_base_parser_single_quoted_string,
  .double_quoted_string = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_base_parser_double_quoted_string,
  .bare_string = (bool(*)(pointer, yaooc_terminal_t*)) yaooc_base_parser_bare_string,
  .string_until_matching_chr = (bool(*)(pointer, char, char, yaooc_terminal_t*)) yaooc_base_parser_string_until_matching_chr,
  .result = (bool(*)(const_pointer)) yaooc_base_parser_result,
};


DEFINE_TYPE_INFO(yaooc_base_parser,Y,Y,N,N,N,N,N,Y,yaooc_object);
/*  End YAOOC PreProcessor generated content */
