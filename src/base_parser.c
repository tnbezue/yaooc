#include <yaooc/base_parser.h>

#include <yaooc/base_parser.h>
#include <string.h>
#include <ctype.h>





const min_type_info_t __parser_position_ti = {
.min_flag_=1,
.pod_flag_=0,
.type_size_=sizeof(parser_position_t)
};
const type_info_t* const parser_position_ti=(const type_info_t* const)&__parser_position_ti;
char* yaooc_token_raw_text(const_pointer __pthis__)
{
yaooc_token_const_pointer this=__pthis__;(void)this;

      char* text=NULL;
      if(this->end_) {
        size_t n=this->end_-this->beg_;
        text=new_array(char,n+1);
        memcpy(text,this->beg_,n);
        text[n]=0;
      }
      return text;
    
}
char* yaooc_token_text(const_pointer __pthis__)
{
yaooc_token_const_pointer this=__pthis__;(void)this;

      char* text=yaooc_token_raw_text(this);
      if(text) {
        char *inp=text;
        char *out=inp;
        bool finished=false;
        while(*inp != 0 && !finished) {
          if(*inp == '\\') {
            inp++;
            switch(*inp) {
              case 0:
                *out='\\';
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

              default:
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
const min_type_info_t __yaooc_token_ti = {
.min_flag_=1,
.pod_flag_=0,
.type_size_=sizeof(yaooc_token_t)
};
const type_info_t* const yaooc_token_ti=(const type_info_t* const)&__yaooc_token_ti;

STACK_IMPLEMENTATION(parser_position,parser_position_stack);



int yaooc_base_parser_next_chr(pointer __pthis__)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;

      int c=*this->current_pos_;
      if(c=='\n') this->line_no_++;
      if(c!=0) this->current_pos_++;
      return c;
    
}
int yaooc_base_parser_prev_chr(pointer __pthis__)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;

      int c=0;
      if(this->current_pos_ > this->parse_string_) {
        c=*(this->current_pos_-1);
      }
      return c;
    
}
bool yaooc_base_parser_space(pointer __pthis__,yaooc_token_t* r)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;

      *r=yaooc_default_token(this);
      for(;*this->current_pos_!=0;this->current_pos_++) {
        if(*this->current_pos_ != ' ' && *this->current_pos_ != '\t')
          break;
      }
      r->end_=this->current_pos_;
      return r->end_!=r->beg_;
    
}
bool yaooc_base_parser_crlf(pointer __pthis__,yaooc_token_t* r)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;

      *r=yaooc_default_token(this);
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
bool yaooc_base_parser_shell_comment(pointer __pthis__,yaooc_token_t* r)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;

      *r=yaooc_default_token(this);
      r->beg_=yaooc_base_parser_current_pos(this);
      if(*this->current_pos_ =='#') {
        int c;
        for(c=yaooc_base_parser_peek(this);c != 0;c=yaooc_base_parser_peek(this)) {
          if(c=='\r' || c=='\n') {
            r->end_=yaooc_base_parser_current_pos(this);
            break;
          }
          yaooc_base_parser_next_chr(this);
        }
      }
      return r->end_!=NULL;
    
}
bool yaooc_base_parser_c_comment(pointer __pthis__,yaooc_token_t* r)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;

      *r=yaooc_default_token(this);
      RULE_START(this);
      if(yaooc_base_parser_next_chr(this) =='/' && yaooc_base_parser_next_chr(this) =='*') {
        int c;
        for(c=yaooc_base_parser_next_chr(this);c!=0;c=yaooc_base_parser_next_chr(this)) {
          if(c == '*' && (c=yaooc_base_parser_next_chr(this)) == '/') {
            r->end_=yaooc_base_parser_current_pos(this);
            break;
          }
        }
      }
      return r->end_ == NULL ? RULE_FAIL(this) : RULE_SUCCESS(this);
    
}
bool yaooc_base_parser_cpp_comment(pointer __pthis__,yaooc_token_t* r)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;

      *r=yaooc_default_token(this);
      RULE_START(this);
      if(yaooc_base_parser_next_chr(this) =='/' && yaooc_base_parser_next_chr(this) =='/') {
        int c;
        for(c=yaooc_base_parser_peek(this);c != 0;c=yaooc_base_parser_peek(this)) {
          if(c=='\r' || c=='\n') {
            r->end_=yaooc_base_parser_current_pos(this);
            break;
          }
          yaooc_base_parser_next_chr(this);
        }
      }
      return r->end_ == NULL ? RULE_FAIL(this) : RULE_SUCCESS(this);
    
}
void yaooc_base_parser_set_parse_string(pointer __pthis__,const char* pstr)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->set_parse_string(this,pstr)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      this->line_no_=1;
      this->parse_string_=pstr;
      this->current_pos_=pstr;
    
#undef PM
#undef super
}
void yaooc_base_parser_rule_start(pointer __pthis__)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->rule_start(this)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      parser_position_t temp={ this->current_pos_,this->line_no_};
      M(this->stack_,push,&temp);
    
#undef PM
#undef super
}
bool yaooc_base_parser_rule_success(pointer __pthis__)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->rule_success(this)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      M(this->stack_,pop);
      return true;
    
#undef PM
#undef super
}
bool yaooc_base_parser_rule_fail(pointer __pthis__)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->rule_fail(this)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      parser_position_t* temp=M(this->stack_,top);
      this->current_pos_=temp->pos_;
      this->line_no_=temp->line_no_;
      M(this->stack_,pop);
      return false;
    
#undef PM
#undef super
}
bool yaooc_base_parser_eos(pointer __pthis__)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->eos(this)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      return *this->current_pos_==0;
    
#undef PM
#undef super
}
bool yaooc_base_parser_chr(pointer __pthis__,char ch,yaooc_token_t* r)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->chr(this,ch,r)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_token_t ws;
      *r=yaooc_default_token(this);
      if(yaooc_base_parser_peek(this) == ch) {
        yaooc_base_parser_next_chr(this);
        r->end_=yaooc_base_parser_current_pos(this);
        M(this,whitespace,&ws);
      }
      return r->end_!=NULL;
    
#undef PM
#undef super
}
int yaooc_base_parser_chr_choices(pointer __pthis__,const char* ch_choices,yaooc_token_t* r)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->chr_choices(this,ch_choices,r)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_token_t ws;
      *r=yaooc_default_token(this);
      int ret=-1;
      const char* ptr=strchr(ch_choices,yaooc_base_parser_peek(this));
      if(ptr) {
        ret=ptr-ch_choices;
        yaooc_base_parser_next_chr(this);
        r->end_=yaooc_base_parser_current_pos(this);
        M(this,whitespace,&ws);
      }
      return ret;
    
#undef PM
#undef super
}
bool yaooc_base_parser_str(pointer __pthis__,const char* str,yaooc_token_t* r)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->str(this,str,r)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_token_t ws;
      *r=yaooc_default_token(this);
      int l=strlen(str);
      if(l>0 && strncmp(this->current_pos_,str,l)==0) {
        yaooc_base_parser_skip(this,l);
        r->end_=this->current_pos_;
        M(this,whitespace,&ws);
      }
      return r->end_!=NULL;
    
#undef PM
#undef super
}
int yaooc_base_parser_str_choices(pointer __pthis__,yaooc_token_t* r,...)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
va_list args; va_start(args,r);
#define super() yaooc_base_parser_parent_class_table->str_choices(this,r,args)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      int ret=-1;
      int cp=0;

      const char* ptr;
      yaooc_token_t ws;
      *r=yaooc_default_token(this);
      while((ptr=va_arg(args,const char*)) != NULL) {
        if(yaooc_base_parser_str(this,ptr,r)) {
          ret=cp;
          M(this,whitespace,&ws);
          break;
        }
        cp++;
      }
      return ret;
    
#undef PM
#undef super
}
bool yaooc_base_parser_digits(pointer __pthis__,yaooc_token_t* r)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->digits(this,r)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      *r=yaooc_default_token(this);
      int c=yaooc_base_parser_peek(this);
      for(;c!=0 && isdigit(c);c=yaooc_base_parser_peek(this))
        yaooc_base_parser_next_chr(this);
      r->end_=this->current_pos_==r->beg_ ? NULL : this->current_pos_;
      return r->end_!=NULL;
    
#undef PM
#undef super
}
bool yaooc_base_parser_hexdigits(pointer __pthis__,yaooc_token_t* r)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->hexdigits(this,r)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      *r=yaooc_default_token(this);
      while(*this->current_pos_!=0 && isxdigit(yaooc_base_parser_peek(this)))
        yaooc_base_parser_next_chr(this);
      r->end_=this->current_pos_==r->beg_ ? NULL : this->current_pos_;
      return r->end_!=NULL;
    
#undef PM
#undef super
}
bool yaooc_base_parser_integer(pointer __pthis__,yaooc_token_t* r)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->integer(this,r)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_token_t ws;
      *r=yaooc_default_token(this);
      RULE_START(this);
      if(yaooc_base_parser_peek(this)=='+' || yaooc_base_parser_peek(this)=='-')
        yaooc_base_parser_next_chr(this);
      yaooc_token_t dr;
      if(yaooc_base_parser_digits(this,&dr) && (yaooc_base_parser_peek(this)==0
            || (yaooc_base_parser_peek(this) !='.' && !isalpha(yaooc_base_parser_peek(this))))) {
        r->end_=dr.end_;
        M(this,whitespace,&ws);
        return RULE_SUCCESS(this);
      }
      return RULE_FAIL(this);
    
#undef PM
#undef super
}
bool yaooc_base_parser_hexinteger(pointer __pthis__,yaooc_token_t* r)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->hexinteger(this,r)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_token_t ws;
      *r=yaooc_default_token(this);
      RULE_START(this);
      if(yaooc_base_parser_next_chr(this)=='0' && toupper(yaooc_base_parser_next_chr(this))=='X') {
        yaooc_token_t dr;
        if(yaooc_base_parser_hexdigits(this,&dr)) {
          r->end_=dr.end_;
          M(this,whitespace,&ws);
        }
      }
      return r->end_ == NULL ? RULE_FAIL(this) : RULE_SUCCESS(this);
    
#undef PM
#undef super
}
bool yaooc_base_parser_real(pointer __pthis__,yaooc_token_t* r)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->real(this,r)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_token_t ws;
      *r=yaooc_default_token(this);
      bool has_decimal=false;
      RULE_START(this);
      if(yaooc_base_parser_peek(this)=='+' || yaooc_base_parser_peek(this)=='-')
        yaooc_base_parser_next_chr(this);
      yaooc_token_t whole;
      M(this,digits,&whole);
      yaooc_token_t fraction=yaooc_default_token(this);
      if(yaooc_base_parser_peek(this)=='.') {
        has_decimal=true;

        yaooc_base_parser_next_chr(this);
        M(this,digits,&fraction);
      }
      if(whole.end_ || fraction.end_) {
        if(toupper(yaooc_base_parser_peek(this))=='E') {
          yaooc_base_parser_next_chr(this);
          yaooc_token_t exp;
          M(this,integer,&exp);
          if(exp.end_) {
            r->end_=exp.end_;
          }
        } else {



          if(((whole.end_ && has_decimal) || fraction.end_) &&
                  (yaooc_base_parser_peek(this) != '.' && !isalpha(yaooc_base_parser_peek(this)))) {
            r->end_=this->current_pos_;
            M(this,whitespace,&ws);
          }
        }
      }
      return r->end_ == NULL ? RULE_FAIL(this) : RULE_SUCCESS(this);
    
#undef PM
#undef super
}
bool yaooc_base_parser_ident(pointer __pthis__,yaooc_token_t* r)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->ident(this,r)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_token_t ws;
      *r=yaooc_default_token(this);
      int c=yaooc_base_parser_peek(this);
      if(isalpha(c) || c =='_') {
        do {
          yaooc_base_parser_next_chr(this);
          c=yaooc_base_parser_peek(this);
        } while (c !=0 && (isalnum(c) || c == '_'));
        r->end_=yaooc_base_parser_current_pos(this);
        M(this,whitespace,&ws);
      }
      return r->end_!=NULL;
    
#undef PM
#undef super
}
bool yaooc_base_parser_regex(pointer __pthis__,regex_t* re,uint32_t match_opts,size_t n_ov,regmatch_t* ov,yaooc_token_t* r)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->regex(this,re,match_opts,n_ov,ov,r)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_token_t ws;
      *r=yaooc_default_token(this);
      regmatch_t ov_temp;
      regmatch_t* pov;
      if(ov == NULL || n_ov == 0) {
        pov=&ov_temp;
        n_ov=1;
      } else {
        pov=ov;
      }
      int rc = regexec(re,this->current_pos_,n_ov,pov,match_opts);
      if(rc == 0 && pov[0].rm_so == 0) {
        yaooc_base_parser_skip(this,pov[0].rm_eo);
        r->end_=yaooc_base_parser_current_pos(this);
        M(this,whitespace,&ws);
      }
      return r->end_!=NULL;
    
#undef PM
#undef super
}
bool yaooc_base_parser_quoted_string(pointer __pthis__,char quote_char,yaooc_token_t* r)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->quoted_string(this,quote_char,r)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_token_t ws;
      *r=yaooc_default_token(this);
      bool escaped=false;
      RULE_START(this);
      int c=yaooc_base_parser_next_chr(this);
      if(c==quote_char) {
        r->beg_=yaooc_base_parser_current_pos(this);
      do {
          c=yaooc_base_parser_next_chr(this);
          if(escaped) {
            escaped=false;
          } else if(c=='\\') {
            escaped=true;
          } else if(c==quote_char) {
            r->end_=yaooc_base_parser_current_pos(this)-1;
            M(this,whitespace,&ws);
            break;
          }
        } while(c != 0);
      }
      return r->end_ == NULL ? RULE_FAIL(this) : RULE_SUCCESS(this);
    
#undef PM
#undef super
}
bool yaooc_base_parser_single_quoted_string(pointer __pthis__,yaooc_token_t* r)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->single_quoted_string(this,r)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_base_parser_quoted_string(this,'\'',r);
    
#undef PM
#undef super
}
bool yaooc_base_parser_double_quoted_string(pointer __pthis__,yaooc_token_t* r)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->double_quoted_string(this,r)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_base_parser_quoted_string(this,'"',r);
    
#undef PM
#undef super
}
bool yaooc_base_parser_bare_string(pointer __pthis__,yaooc_token_t* r)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->bare_string(this,r)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_token_t ws;
      *r=yaooc_default_token(this);
      int c=yaooc_base_parser_peek(this);
      if(!isspace(c)) {
        for(;c!=0;c=yaooc_base_parser_peek(this)) {
          if(isspace(c))
            break;
          yaooc_base_parser_next_chr(this);
        }

        r->end_=this->current_pos_;
        M(this,whitespace,&ws);
      }
      return r->end_!=NULL;
    
#undef PM
#undef super
}
bool yaooc_base_parser_string_until_chrs(pointer __pthis__,const char* chrs,yaooc_token_t* r)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->string_until_chrs(this,chrs,r)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_token_t ws;
      *r=yaooc_default_token(this);
      size_t n=strcspn(this->current_pos_,chrs);
      if(n>0) {
        yaooc_base_parser_skip(this,n);
        r->end_=yaooc_base_parser_current_pos(this);
        M(this,whitespace,&ws);
      }
      return r->end_!=NULL;
    
#undef PM
#undef super
}
bool yaooc_base_parser_string_while_chrs(pointer __pthis__,const char* chrs,yaooc_token_t* r)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->string_while_chrs(this,chrs,r)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_token_t ws;
      size_t n=strspn(this->current_pos_,chrs);
      *r=yaooc_default_token(this);
      if(n>0) {
        yaooc_base_parser_skip(this,n);
        r->end_=yaooc_base_parser_current_pos(this);
        M(this,whitespace,&ws);
      }
      return r->end_!=NULL;
    
#undef PM
#undef super
}
bool yaooc_base_parser_string_until_eol(pointer __pthis__,yaooc_token_t* r)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->string_until_eol(this,r)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_token_t ws;
      *r=yaooc_default_token(this);
      yaooc_base_parser_string_until_chrs(this,"\r\n",r);






      if(r->end_!=NULL) {
        M(this,whitespace,&ws);
        return true;
      }
      return false;
    
#undef PM
#undef super
}
bool yaooc_base_parser_whitespace(pointer __pthis__,yaooc_token_t* r)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->whitespace(this,r)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      *r=yaooc_default_token(this);
      yaooc_token_t temp;
      while(true) {
        if(!yaooc_base_parser_space(this,&temp))
          if(!yaooc_base_parser_crlf(this,&temp))
          break;
      }
      r->end_=yaooc_base_parser_current_pos(this);
      return r->beg_ != r->end_;
    
#undef PM
#undef super
}
bool yaooc_base_parser_string_within_matching_chr(pointer __pthis__,char lch,char rch,yaooc_token_t* r)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->string_within_matching_chr(this,lch,rch,r)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_token_t ws;
      *r=yaooc_default_token(this);
      int level=0;
      RULE_START(this);
      if(*this->current_pos_ == lch) {
        char c=yaooc_base_parser_next_chr(this);
        r->beg_ = this->current_pos_;
        for(;c!= 0;c=yaooc_base_parser_next_chr(this)) {
          if(c==lch) {
            level++;
          } else if(c==rch) {
            if(--level==0) {
              r->end_=yaooc_base_parser_current_pos(this)-1;
              M(this,whitespace,&ws);
              break;
            }
          }
        }
      }
      return r->end_ == NULL ? RULE_FAIL(this) : RULE_SUCCESS(this);
    
#undef PM
#undef super
}
bool yaooc_base_parser_result(const_pointer __pthis__)
{
yaooc_base_parser_const_pointer this=__pthis__;(void)this;
#define super() yaooc_base_parser_parent_class_table->result(this)
#define PM(method,...) CTM((*yaooc_base_parser_parent_class_table),this,method,## __VA_ARGS__)


      return *this->current_pos_==0;
    
#undef PM
#undef super
}
yaooc_base_parser_class_table_t yaooc_base_parser_class_table ={
.parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
.type_name_ = (const char*) "yaooc_base_parser_t",
.swap = (void(*)(pointer,pointer)) yaooc_base_parser_swap,
.set_parse_string = (void(*)(pointer,const char*)) yaooc_base_parser_set_parse_string,
.rule_start = (void(*)(pointer)) yaooc_base_parser_rule_start,
.rule_success = (bool(*)(pointer)) yaooc_base_parser_rule_success,
.rule_fail = (bool(*)(pointer)) yaooc_base_parser_rule_fail,
.eos = (bool(*)(pointer)) yaooc_base_parser_eos,
.chr = (bool(*)(pointer,char,yaooc_token_t*)) yaooc_base_parser_chr,
.chr_choices = (int(*)(pointer,const char*,yaooc_token_t*)) yaooc_base_parser_chr_choices,
.str = (bool(*)(pointer,const char*,yaooc_token_t*)) yaooc_base_parser_str,
.str_choices = (int(*)(pointer,yaooc_token_t*,...)) yaooc_base_parser_str_choices,
.digits = (bool(*)(pointer,yaooc_token_t*)) yaooc_base_parser_digits,
.hexdigits = (bool(*)(pointer,yaooc_token_t*)) yaooc_base_parser_hexdigits,
.integer = (bool(*)(pointer,yaooc_token_t*)) yaooc_base_parser_integer,
.hexinteger = (bool(*)(pointer,yaooc_token_t*)) yaooc_base_parser_hexinteger,
.real = (bool(*)(pointer,yaooc_token_t*)) yaooc_base_parser_real,
.ident = (bool(*)(pointer,yaooc_token_t*)) yaooc_base_parser_ident,
.regex = (bool(*)(pointer,regex_t*,uint32_t,size_t,regmatch_t*,yaooc_token_t*)) yaooc_base_parser_regex,
.quoted_string = (bool(*)(pointer,char,yaooc_token_t*)) yaooc_base_parser_quoted_string,
.single_quoted_string = (bool(*)(pointer,yaooc_token_t*)) yaooc_base_parser_single_quoted_string,
.double_quoted_string = (bool(*)(pointer,yaooc_token_t*)) yaooc_base_parser_double_quoted_string,
.bare_string = (bool(*)(pointer,yaooc_token_t*)) yaooc_base_parser_bare_string,
.string_until_chrs = (bool(*)(pointer,const char*,yaooc_token_t*)) yaooc_base_parser_string_until_chrs,
.string_while_chrs = (bool(*)(pointer,const char*,yaooc_token_t*)) yaooc_base_parser_string_while_chrs,
.string_until_eol = (bool(*)(pointer,yaooc_token_t*)) yaooc_base_parser_string_until_eol,
.whitespace = (bool(*)(pointer,yaooc_token_t*)) yaooc_base_parser_whitespace,
.string_within_matching_chr = (bool(*)(pointer,char,char,yaooc_token_t*)) yaooc_base_parser_string_within_matching_chr,
.result = (bool(*)(const_pointer)) yaooc_base_parser_result,
};
void yaooc_base_parser_default_ctor(pointer __pthis__)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_base_parser);



      this->parse_string_=NULL;
      this->current_pos_=NULL;
      this->stack_=new(parser_position_stack);
      this->line_no_=1;
    
}
void yaooc_base_parser_dtor(pointer __pthis__)
{
yaooc_base_parser_pointer this=__pthis__;(void)this;


      delete(this->stack_);
    
}
const type_info_t __yaooc_base_parser_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_base_parser_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_base_parser_default_ctor,
.dtor_=yaooc_base_parser_dtor,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_base_parser_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_base_parser_ti=&__yaooc_base_parser_ti;
