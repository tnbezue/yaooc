#include <yaooc/base_parser.h>
#include <stdlib.h>
#include <ctype.h>
#define PCRE2_CODE_UNIT_WIDTH 8
#include <pcre2.h>

/* Terminal */
void yaooc_terminal_default_ctor(pointer p)
{
  yaooc_terminal_pointer this=p;
  this->end_=NULL;
  this->beg_=NULL;
}

char* yaooc_terminal_get_text(pointer p)
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

char* yaooc_terminal_get_raw_text(pointer p)
{
  char* text=NULL;
  yaooc_terminal_pointer this=p;
  if(this->end_) {
    size_t n=this->end_-this->beg_;
    text=new_array(char,n+1);
    memcpy(text,this->beg_,n);
    text[n]=0;
  }
  return text;
}

bool yaooc_terminal_has_value(const_pointer p)
{
  return ((yaooc_terminal_const_pointer)p)->end_ != NULL;
}

yaooc_terminal_class_members_t yaooc_terminal_class_members =
{
  YAOOC_TERMINAL_CLASS_MEMBERS
};
DEFINE_TYPE_INFO(yaooc_terminal,yaooc_terminal_default_ctor,NULL,
      NULL,NULL,NULL,&yaooc_terminal_class_members,NULL)

/*
  Parser stack
*/

void parser_position_ctor(pointer p)
{
  parser_position_pointer this=p;
  this->pos_=NULL;
  this->line_no_=1;
}

DEFINE_TYPE_INFO(parser_position,parser_position_ctor,NULL,NULL,NULL,NULL,NULL,NULL)

STACK_IMPLEMENTATION(parser_position)


/* Base Parser */
void yaooc_base_parser_default_ctor(pointer p)
{
  yaooc_base_parser_pointer this=p;
  this->stack_=new(parser_position_stack);
  this->included_in_whitespace_=0;
}

void yaooc_base_parser_dtor(pointer p)
{
  yaooc_base_parser_pointer this=p;
  delete(this->stack_);
}

void yaooc_base_parser_assign(pointer d,const_pointer s)
{
  yaooc_base_parser_pointer dst=d;
  yaooc_base_parser_const_pointer src=s;
  yaooc_base_parser_set_parse_string(dst,src->string_to_parse_);
}

void yaooc_base_parser_copy_ctor(pointer d,const_pointer s)
{
  yaooc_base_parser_default_ctor(d);
  yaooc_base_parser_assign(d,s);
}

void yaooc_base_parser_set_parse_string(pointer p,const char* s)
{
  yaooc_base_parser_pointer this=p;
  this->string_to_parse_=s;
  this->current_pos_=this->string_to_parse_;
  this->parser_error_=0;
  M(this->stack_,clear);
}

char yaooc_base_parser_current_chr(pointer p)
{
  return *((yaooc_base_parser_const_pointer)p)->current_pos_;
}

void yaooc_base_parser_next_chr(pointer p)
{
  yaooc_base_parser_pointer this=p;
  if(*this->current_pos_=='\n')
    this->line_no_++;
  this->current_pos_++;
}

void yaooc_base_parser_next_n_chr(pointer p,uint32_t n)
{
  for(;n>0;n--)
    yaooc_base_parser_next_chr(p);
}

yaooc_static_terminal_t yaooc_base_parser_eos(pointer p)
{
  return yaooc_base_parser_current_chr(p) == 0;
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

/*
  String until specified char "c" that occurs before char "b". Does not remove chr from stream.
  Fails if char "c" not found before "b"
*/
yaooc_terminal_t yaooc_base_parser_string_until_chr_before_chr(pointer p,char c,char b)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t r;
  newp(&r,yaooc_terminal);
  r.beg_=this->current_pos_;
  M(this,rule_start);
  for(;this->current_pos_ !=0;yaooc_base_parser_next_chr(p)) {
    if(*this->current_pos_== b) {
      break;
    } else if(*this->current_pos_ == c) {
      r.end_=this->current_pos_;
      break;
    }
  }
  if(r.end_)
    M(this,rule_success);
  else
    M(this,rule_fail);
  return r;
}

/*
  String until specified chr.  Does not remove chr from stream.
  Fails if chr not found.
*/
yaooc_terminal_t yaooc_base_parser_string_until_chr(pointer p,char c)
{
  return yaooc_base_parser_string_until_chr_before_chr(p,c,0);
}

yaooc_terminal_t yaooc_base_parser_string_until_eol(pointer p)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t r;
  newp(&r,yaooc_terminal);
  r.beg_=this->current_pos_;
  r.end_=yaooc_base_parser_string_until_chr(p,'\n').end_;
  /* Remove \n from stream */
  yaooc_base_parser_next_chr(p);
  /* remove CR from terminal capture */
  while(r.end_>r.beg_) {
    if(*r.end_ != '\r')
      break;
    r.end_--;
  }
  yaooc_base_parser_whitespace(p);
  return r;
}

yaooc_terminal_t yaooc_base_parser_shell_comment(pointer p)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t r;
  newp(&r,yaooc_terminal);
  r.beg_=this->current_pos_;
  if(yaooc_base_parser_current_chr(p)=='#') {
    r.end_=yaooc_base_parser_string_until_eol(p).end_;
    //yaooc_base_parser_whitespace(p);
  }
  return r;
}

yaooc_terminal_t yaooc_base_parser_c_comment(pointer p)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t r;
  newp(&r,yaooc_terminal);
  r.beg_=this->current_pos_;
  if(*this->current_pos_=='/' && *(this->current_pos_+1)=='*') {
    yaooc_base_parser_next_n_chr(p,2);
    for(;*this->current_pos_!=0;yaooc_base_parser_next_chr(p)) {
      if(*this->current_pos_=='*' && *(this->current_pos_+1)=='/' ) {
        r.end_=this->current_pos_;
        yaooc_base_parser_next_n_chr(p,2);
        yaooc_base_parser_whitespace(p);
        break;
      }
    }
  }
  return r;
}

yaooc_terminal_t yaooc_base_parser_cpp_comment(pointer p)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t r;
  newp(&r,yaooc_terminal);
  r.beg_=this->current_pos_;
  if(*this->current_pos_=='/' && *(this->current_pos_+1)=='/') {
    yaooc_base_parser_next_n_chr(p,2);
    r.end_=yaooc_base_parser_string_until_eol(p).end_;
  }
  return r;
}

void yaooc_base_parser_set_whitespace_types(pointer p,uint32_t types)
{
  ((yaooc_base_parser_pointer)p)->included_in_whitespace_=types;
}

void yaooc_base_parser_set_crlf_as_whitespace(pointer p,bool flag)
{
  if(flag)
    ((yaooc_base_parser_pointer)p)->included_in_whitespace_|=CRLF;
  else
    ((yaooc_base_parser_pointer)p)->included_in_whitespace_&= ~CRLF;
}

void yaooc_base_parser_set_c_comment_as_whitespace(pointer p,bool flag)
{
  if(flag)
    ((yaooc_base_parser_pointer)p)->included_in_whitespace_|=C_COMMENT;
  else
    ((yaooc_base_parser_pointer)p)->included_in_whitespace_&= ~C_COMMENT;
}

void yaooc_base_parser_set_cpp_comment_as_whitespace(pointer p,bool flag)
{
  if(flag)
    ((yaooc_base_parser_pointer)p)->included_in_whitespace_|=CPP_COMMENT;
  else
    ((yaooc_base_parser_pointer)p)->included_in_whitespace_&= ~CPP_COMMENT;
}

void yaooc_base_parser_set_shell_comment_as_whitespace(pointer p,bool flag)
{
  if(flag)
    ((yaooc_base_parser_pointer)p)->included_in_whitespace_|=SHELL_COMMENT;
  else
    ((yaooc_base_parser_pointer)p)->included_in_whitespace_&= ~SHELL_COMMENT;
}

uint32_t yaooc_base_parser_get_whitespace_types(pointer p)
{
  return ((yaooc_base_parser_pointer)p)->included_in_whitespace_;
}

bool yaooc_base_parser_is_crlf_whitespace(pointer p)
{
  return ((yaooc_base_parser_pointer)p)->included_in_whitespace_ & CRLF;
}

bool yaooc_base_parser_is_c_comment_whitespace(pointer p)
{
  return ((yaooc_base_parser_pointer)p)->included_in_whitespace_ & C_COMMENT;
}

bool yaooc_base_parser_is_cpp_comment_whitespace(pointer p)
{
  return ((yaooc_base_parser_pointer)p)->included_in_whitespace_ & CPP_COMMENT;
}

bool yaooc_base_parser_is_shell_comment_whitespace(pointer p)
{
  return ((yaooc_base_parser_pointer)p)->included_in_whitespace_ & SHELL_COMMENT;
}

int yaooc_base_parser_whitespace(pointer p)
{
  yaooc_base_parser_pointer this=p;
  const char* pos=this->current_pos_;
  while(!yaooc_base_parser_eos(p)) {
    char cc=yaooc_base_parser_current_chr(p);
    if(cc==' ' || cc=='\t') {
      yaooc_base_parser_next_chr(p);
    } else if(yaooc_base_parser_is_crlf_whitespace(p) && (cc=='\r' || cc=='\n') ) {
      yaooc_base_parser_next_chr(p);
    } else if(yaooc_base_parser_is_c_comment_whitespace(p) && yaooc_base_parser_c_comment(p).end_) {
      continue;
    } else if(yaooc_base_parser_is_cpp_comment_whitespace(p) && yaooc_base_parser_cpp_comment(p).end_) {
      continue;
    } else if(yaooc_base_parser_is_shell_comment_whitespace(p) && yaooc_base_parser_shell_comment(p).end_) {
      continue;
    } else
      break;
  }
  return this->current_pos_-pos;
}

yaooc_static_terminal_t yaooc_base_parser_chr(pointer p,char c)
{
  if(yaooc_base_parser_current_chr(p) == c) {
    yaooc_base_parser_next_chr(p);
    yaooc_base_parser_whitespace(p);
    return true;
  }
  return false;
}

int yaooc_base_parser_chr_choices(pointer p,const char* choices)
{
  yaooc_base_parser_pointer this=p;
  const char* ptr=strchr(choices,yaooc_base_parser_current_chr(p));
  if(ptr) {
    int pos=ptr-this->current_pos_;
    yaooc_base_parser_next_chr(p);
    yaooc_base_parser_whitespace(p);
    return pos;
  }
  return -1;
}

/*
  Assume CR nor LF in string
*/
yaooc_static_terminal_t yaooc_base_parser_str(pointer p,const char*tok)
{
  yaooc_base_parser_pointer this=p;
  if(tok) {
    int l=strlen(tok);
    if(l>0 && strncmp(this->current_pos_,tok,l)==0) {
      this->current_pos_+=l;
      yaooc_base_parser_whitespace(p);
      return true;
    }
  }
  return false;
}

int yaooc_base_parser_str_choices(pointer p,...)
{
  int pos=-1;
  int cp=0;
  va_list args;
  va_start (args,p);
  const char* ptr;
  while((ptr=va_arg(args,const char*)) != NULL) {
    if(yaooc_base_parser_str(p,ptr)) {
      pos=cp;
      yaooc_base_parser_whitespace(p);
      break;
    }
    cp++;
  }
  va_end(args);
  return pos;
}

yaooc_terminal_t yaooc_base_parser_digits(pointer p)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t r;
  newp(&r,yaooc_terminal);
  r.beg_=this->current_pos_;
  while(*this->current_pos_!=0 && isdigit(*this->current_pos_)) yaooc_base_parser_next_chr(p);
  r.end_=this->current_pos_==r.beg_ ? NULL : this->current_pos_;
  return r;
}

yaooc_terminal_t yaooc_base_parser_hexdigits(pointer p)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t r;
  newp(&r,yaooc_terminal);
  r.beg_=this->current_pos_;
  while(*this->current_pos_!=0 && isxdigit(*this->current_pos_)) yaooc_base_parser_next_chr(p);
  r.end_=this->current_pos_==r.beg_ ? NULL : this->current_pos_;
  return r;
}

yaooc_terminal_t yaooc_base_parser_integer(pointer p)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t r;
  newp(&r,yaooc_terminal);
  r.beg_=this->current_pos_;
  yaooc_base_parser_rule_start(p);
  if(*this->current_pos_=='+' || *this->current_pos_=='-') this->current_pos_++;
  yaooc_terminal_t dr=yaooc_base_parser_digits(p);
  if(dr.end_ && (yaooc_base_parser_eos(p) || (*this->current_pos_ !='.' && !isalpha(*this->current_pos_)))) {
    r.end_=dr.end_;
    yaooc_base_parser_rule_success(p);
    yaooc_base_parser_whitespace(p);
  } else
    yaooc_base_parser_rule_fail(p);
  return r;
}

yaooc_terminal_t yaooc_base_parser_hexinteger(pointer p)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t r;
  newp(&r,yaooc_terminal);
  r.beg_=this->current_pos_;
  if(*this->current_pos_=='0' && toupper(*(this->current_pos_+1))=='X') {
    yaooc_base_parser_rule_start(p);
    this->current_pos_+=2;
    yaooc_terminal_t dr=yaooc_base_parser_hexdigits(p);
    if(dr.end_ && (yaooc_base_parser_eos(p) || (*this->current_pos_ !='.' && !isalpha(*this->current_pos_)))) {
      r.end_=dr.end_;
      yaooc_base_parser_rule_success(p);
      yaooc_base_parser_whitespace(p);
    } else
      yaooc_base_parser_rule_fail(p);
  }
  return r;
}

yaooc_terminal_t yaooc_base_parser_real(pointer p)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t r;
  newp(&r,yaooc_terminal);
  r.beg_=this->current_pos_;
  bool has_decimal=false;
  yaooc_base_parser_rule_start(p);
  if(*this->current_pos_=='+' || *this->current_pos_=='-') this->current_pos_++;
  yaooc_terminal_t whole=M(this,digits);
  yaooc_terminal_t fraction;
  fraction.end_=NULL;
  if(*this->current_pos_=='.') {
    has_decimal=true;
    this->current_pos_++;
    fraction=M(this,digits);
  }
  if(whole.end_ || fraction.end_) {
    if(toupper(*this->current_pos_)=='E') {
      this->current_pos_++;
      yaooc_terminal_t exp=M(this,integer);
      if(exp.end_) {
        r.end_=exp.end_; // integer already consumed whitespace
      }
    } else {
      /*
        No exponent.  Must have whole and decimal or franction
      */
      if(((whole.end_ && has_decimal) || fraction.end_) && (*this->current_pos_ !='.' && !isalpha(*this->current_pos_))) {
        r.end_=this->current_pos_;
        M(this,whitespace);
      }
    }
  }
  if(r.end_)
    M(this,rule_success);
  else
    M(this,rule_fail);
  return r;
}

yaooc_terminal_t yaooc_base_parser_ident(pointer p)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t r;
  newp(&r,yaooc_terminal);
  r.beg_=this->current_pos_;
  if(isalpha(*this->current_pos_) || *this->current_pos_=='_') {
    do {
      this->current_pos_++;
    } while (isalnum(*this->current_pos_) || *this->current_pos_=='_');
    r.end_=this->current_pos_;
    M(this,whitespace);
  }
  return r;
}

yaooc_terminal_t yaooc_base_parser_regex(pointer p,const char* str,uint32_t compile_options,uint32_t match_options)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t r;
  newp(&r,yaooc_terminal);
  r.beg_=this->current_pos_;
  int error_code;
  PCRE2_SIZE error_ofs;
  pcre2_code *re=pcre2_compile((PCRE2_SPTR8)str,PCRE2_ZERO_TERMINATED,PCRE2_ANCHORED|compile_options,&error_code,&error_ofs,NULL);
  if(re) {
    pcre2_match_data *md = pcre2_match_data_create(1, NULL);
    int rc = pcre2_match(re,(PCRE2_SPTR8)this->current_pos_,PCRE2_ZERO_TERMINATED,0,PCRE2_ANCHORED|match_options,md,NULL);
    if(rc >= 0) {
      PCRE2_SIZE len;
      pcre2_substring_length_bynumber(md,0,&len);
      this->current_pos_+=len;
      r.end_=this->current_pos_;
      M(this,whitespace);
    }
    pcre2_match_data_free(md);
    pcre2_code_free(re);
  }
  return r;
}

yaooc_terminal_t yaooc_base_parser_quoted_string(pointer p,char quote_char)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t r;
  newp(&r,yaooc_terminal);
  bool escape=false;
  M(this,rule_start);
  if(*this->current_pos_==quote_char) {
    M(this,next_chr);
    r.beg_=this->current_pos_;
    for(;*this->current_pos_!=0;M(this,next_chr)) {
      if(escape) {
        escape=false;
      } else if(*this->current_pos_=='\\') {
        escape=true;
      } else if(*this->current_pos_==quote_char) {
        r.end_=this->current_pos_;
        M(this,next_chr);
        M(this,whitespace);
        break;
      }
    }
  }
  if(r.end_)
    M(this,rule_success);
  else
    M(this,rule_fail);
  return r;
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
  yaooc_terminal_t r;
  newp(&r,yaooc_terminal);
  r.beg_=this->current_pos_;
  if(!isspace(*this->current_pos_)) {
    M(this,next_chr);
    while(*this->current_pos_!=0 && !isspace(*this->current_pos_)) M(this,next_chr);
    r.end_=this->current_pos_;
  }
  return r;
}

yaooc_terminal_t yaooc_base_parser_string_until_matching_chr(pointer p,char left,char right)
{
  yaooc_base_parser_pointer this=p;
  yaooc_terminal_t r;
  newp(&r,yaooc_terminal);
  r.beg_=this->current_pos_;
  int level=1;
  const char* pos=this->current_pos_;
  for(;*pos!= 0;pos++) {
    if(*pos==left) {
      level++;
    } if(*pos==right) {
      if(--level==0) {
        r.end_=pos;
        this->current_pos_=pos+1;
        M(this,whitespace);
        break;
      }
    }
  }
  return r;
}

ISA_IMPLEMENTATION(yaooc_base_parser,yaooc_object)

void yaooc_base_parser_swap(pointer p,pointer o)
{
  yaooc_base_parser_pointer this=p;
  yaooc_base_parser_pointer other=o;
  SWAP(const char*,this->string_to_parse_,other->string_to_parse_)
  SWAP(const char*,this->current_pos_,other->current_pos_)
  SWAP(parser_position_stack_pointer,this->stack_,other->stack_)
  SWAP(uint32_t,this->line_no_,other->line_no_)
  SWAP(uint32_t,this->included_in_whitespace_,other->included_in_whitespace_)
  SWAP(int,this->parser_error_,other->parser_error_)
}

yaooc_base_parser_class_members_t yaooc_base_parser_class_members = { YAOOC_BASE_PARSER_CLASS_MEMBERS };

DEFINE_TYPE_INFO(yaooc_base_parser,yaooc_base_parser_default_ctor,yaooc_base_parser_dtor,
      yaooc_base_parser_copy_ctor,yaooc_base_parser_assign,NULL,&yaooc_base_parser_class_members,NULL)
