#include <yaooc/json_parser.h>
#include <sys/stat.h>
#include <fcntl.h>

yaooc_json_parser_exception_class_table_t yaooc_json_parser_exception_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_exception_class_table,
.type_name_ = (const char*)"yaooc_json_parser_exception_t",
.swap = (void(*)(pointer,pointer)) yaooc_json_parser_exception_swap,
.what = (const char*(*)(const_pointer)) yaooc_json_parser_exception_what,
.error_code = (int(*)(const_pointer)) yaooc_json_parser_exception_error_code,
};
const type_info_t __yaooc_json_parser_exception_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_json_parser_exception_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_json_parser_exception_class_table,
.parent_=&__yaooc_exception_ti
};
const type_info_t* const yaooc_json_parser_exception_ti=&__yaooc_json_parser_exception_ti;
bool yaooc_json_parser_parse_json_pair(pointer __pthis__,yaooc_json_pair_t* jpair)
{
yaooc_json_parser_pointer this=__pthis__;(void)this;

      bool ret=false;
      *jpair = (yaooc_json_pair_t){ NULL,NULL};
      RULE_START(this);
      yaooc_token_t r;
      if(M(this,parse_json_string,(yaooc_json_value_t**)&jpair->key) && M(this,chr,':',&r)) {
        if(M(this,parse_json_value,(yaooc_json_value_t**)&jpair->value)) {
          RULE_SUCCESS(this);
          ret=true;
        } else {
          RULE_FAIL(this);
          if(jpair->key) delete(jpair->key);
          if(jpair->value) delete(jpair->value);
          ret=false;
        }
      }
      return ret;
    
}
bool yaooc_json_parser_whitespace(pointer __pthis__,yaooc_token_t* r)
{
yaooc_json_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_json_parser_parent_class_table->whitespace(this,r)
#define PM(method,...) CTM((*yaooc_json_parser_parent_class_table),this,method,## __VA_ARGS__)


      *r=yaooc_default_token(this);
      yaooc_token_t ws;
      while(true) {
        if(!yaooc_base_parser_space(this,&ws))
          if(!yaooc_base_parser_crlf(this,&ws))
            if(!yaooc_base_parser_c_comment(this,&ws))
              if(!yaooc_base_parser_cpp_comment(this,&ws))
                if(!yaooc_base_parser_shell_comment(this,&ws))
                  break;
      }
      r->end_=yaooc_base_parser_current_pos(this);
      return r->beg_!=r->end_;
    
#undef PM
#undef super
}
bool yaooc_json_parser_parse_json_null(pointer __pthis__,yaooc_json_value_t** jnull)
{
yaooc_json_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_json_parser_parent_class_table->parse_json_null(this,jnull)
#define PM(method,...) CTM((*yaooc_json_parser_parent_class_table),this,method,## __VA_ARGS__)


      bool ret=false;
      yaooc_token_t r;
      if(M(this,str,"null",&r)) {
        *jnull=new(yaooc_json_null);
        ret=true;
      }
      return ret;
    
#undef PM
#undef super
}
bool yaooc_json_parser_parse_json_bool(pointer __pthis__,yaooc_json_value_t** jbool)
{
yaooc_json_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_json_parser_parent_class_table->parse_json_bool(this,jbool)
#define PM(method,...) CTM((*yaooc_json_parser_parent_class_table),this,method,## __VA_ARGS__)


      bool ret=false;
      yaooc_token_t r;
      if(M(this,str,"true",&r) || M(this,str,"false",&r)) {
        *jbool=new_ctor(yaooc_json_bool,yaooc_json_bool_ctor_bool,*r.beg_=='t');
        ret=true;
      }
      return ret;
    
#undef PM
#undef super
}
bool yaooc_json_parser_parse_json_integer(pointer __pthis__,yaooc_json_value_t** jinteger)
{
yaooc_json_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_json_parser_parent_class_table->parse_json_integer(this,jinteger)
#define PM(method,...) CTM((*yaooc_json_parser_parent_class_table),this,method,## __VA_ARGS__)


      bool ret=false;
      yaooc_token_t r;
      if(M(this,integer,&r)) {
    
        *jinteger=new_ctor(yaooc_json_integer,yaooc_json_integer_ctor_int,atoll(r.beg_));
    
        ret=true;
      }
      return ret;
    
#undef PM
#undef super
}
bool yaooc_json_parser_parse_json_real(pointer __pthis__,yaooc_json_value_t** jreal)
{
yaooc_json_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_json_parser_parent_class_table->parse_json_real(this,jreal)
#define PM(method,...) CTM((*yaooc_json_parser_parent_class_table),this,method,## __VA_ARGS__)


      bool ret=false;
      yaooc_token_t r;
      if(M(this,real,&r)) {
        *jreal=new_ctor(yaooc_json_real,yaooc_json_real_ctor_real,atof(r.beg_));
        ret=true;
      }
      return ret;
    
#undef PM
#undef super
}
bool yaooc_json_parser_parse_json_string(pointer __pthis__,yaooc_json_value_t** jstring)
{
yaooc_json_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_json_parser_parent_class_table->parse_json_string(this,jstring)
#define PM(method,...) CTM((*yaooc_json_parser_parent_class_table),this,method,## __VA_ARGS__)


      bool ret=false;
      yaooc_token_t r;
      if(M(this,double_quoted_string,&r) || M(this,ident,&r)) {
        *jstring=new_ctor(yaooc_json_string,yaooc_json_string_ctor_ccs_size,r.beg_,r.end_-r.beg_);
        ret=true;
      }
      return ret;
    
#undef PM
#undef super
}
bool yaooc_json_parser_parse_json_array(pointer __pthis__,yaooc_json_value_t** jarray)
{
yaooc_json_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_json_parser_parent_class_table->parse_json_array(this,jarray)
#define PM(method,...) CTM((*yaooc_json_parser_parent_class_table),this,method,## __VA_ARGS__)


      bool ret=false;
      yaooc_json_value_t* value;
      yaooc_token_t r;
      RULE_START(this);
      if(M(this,chr,'[',&r)) {
        *jarray=new(yaooc_json_array);
        ret=true;
        while(true) {
          if(!M(this,parse_json_value,&value)) {
            
            
            if(M((yaooc_json_array_t*)*jarray,size) == 0)
              break;
            else
              THROW(new_ctor(yaooc_json_parser_exception,yaooc_json_parser_exception_ctor_v,64,
                  "Error processing json array near line %d",this->line_no_));
          }
          M((yaooc_json_array_pointer)*jarray,insert,value);
          delete(value);
          if(!M(this,chr,',',&r))
            break;
        }
        if(!M(this,chr,']',&r)) {
          THROW(new_ctor(yaooc_json_parser_exception,yaooc_json_parser_exception_ctor_v,64,
              "Error processing json array near line %d",this->line_no_));
        }
      }
      if(ret)
        RULE_SUCCESS(this);
      else
        RULE_FAIL(this);
      return ret;
    
#undef PM
#undef super
}
bool yaooc_json_parser_parse_json_object(pointer __pthis__,yaooc_json_value_t** jobject)
{
yaooc_json_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_json_parser_parent_class_table->parse_json_object(this,jobject)
#define PM(method,...) CTM((*yaooc_json_parser_parent_class_table),this,method,## __VA_ARGS__)


      bool ret=false;
      yaooc_token_t r;
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
          THROW(new_ctor(yaooc_json_parser_exception,yaooc_json_parser_exception_ctor_v,64,
              "Error processing json object near line %d",this->line_no_));
        }
      }
      return ret;
    
#undef PM
#undef super
}
bool yaooc_json_parser_parse_json_value(pointer __pthis__,yaooc_json_value_t** jvalue)
{
yaooc_json_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_json_parser_parent_class_table->parse_json_value(this,jvalue)
#define PM(method,...) CTM((*yaooc_json_parser_parent_class_table),this,method,## __VA_ARGS__)


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
    
#undef PM
#undef super
}
bool yaooc_json_parser_parse_string(pointer __pthis__,const char* str,yaooc_json_value_t** jvalue)
{
yaooc_json_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_json_parser_parent_class_table->parse_string(this,str,jvalue)
#define PM(method,...) CTM((*yaooc_json_parser_parent_class_table),this,method,## __VA_ARGS__)


      bool ret=true;
      yaooc_token_t ws;
      if(str) {
        M(this,set_parse_string,str);
        M(this,whitespace,&ws);
        ret=M(this,parse_json_value,jvalue);
        if(*this->current_pos_!=0)
          puts("Error parsing file");
      }
      return ret;
    
#undef PM
#undef super
}
bool yaooc_json_parser_parse_file(pointer __pthis__,const char* file,yaooc_json_value_t** jvalue)
{
yaooc_json_parser_pointer this=__pthis__;(void)this;
#define super() yaooc_json_parser_parent_class_table->parse_file(this,file,jvalue)
#define PM(method,...) CTM((*yaooc_json_parser_parent_class_table),this,method,## __VA_ARGS__)


      bool ret=false;
      struct stat st;
      if(stat(file,&st)==0 && S_ISREG(st.st_mode)) {
        int fh=open(file,O_RDONLY);
        if(fh > 0) {
          char* buffer=(char*)MALLOC(st.st_size+1);
          read(fh,buffer,st.st_size);
          buffer[st.st_size]=0;
          close(fh);
    
          ret=M(this,parse_string,buffer,jvalue);
          FREE(buffer);
        }
      }
      return ret;
    
#undef PM
#undef super
}
yaooc_json_parser_class_table_t yaooc_json_parser_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_base_parser_class_table,
.type_name_ = (const char*)"yaooc_json_parser_t",
.swap = (void(*)(pointer,pointer)) yaooc_json_parser_swap,
.set_parse_string = (void(*)(pointer,const char*)) yaooc_json_parser_set_parse_string,
.rule_start = (void(*)(pointer)) yaooc_json_parser_rule_start,
.rule_success = (bool(*)(pointer)) yaooc_json_parser_rule_success,
.rule_fail = (bool(*)(pointer)) yaooc_json_parser_rule_fail,
.eos = (bool(*)(pointer)) yaooc_json_parser_eos,
.chr = (bool(*)(pointer,char,yaooc_token_t*)) yaooc_json_parser_chr,
.chr_choices = (int(*)(pointer,const char*,yaooc_token_t*)) yaooc_json_parser_chr_choices,
.str = (bool(*)(pointer,const char*,yaooc_token_t*)) yaooc_json_parser_str,
.str_choices = (int(*)(pointer,yaooc_token_t*,...)) yaooc_json_parser_str_choices,
.digits = (bool(*)(pointer,yaooc_token_t*)) yaooc_json_parser_digits,
.hexdigits = (bool(*)(pointer,yaooc_token_t*)) yaooc_json_parser_hexdigits,
.integer = (bool(*)(pointer,yaooc_token_t*)) yaooc_json_parser_integer,
.hexinteger = (bool(*)(pointer,yaooc_token_t*)) yaooc_json_parser_hexinteger,
.real = (bool(*)(pointer,yaooc_token_t*)) yaooc_json_parser_real,
.ident = (bool(*)(pointer,yaooc_token_t*)) yaooc_json_parser_ident,
.regex = (bool(*)(pointer,regex_t*,uint32_t,size_t,regmatch_t*,yaooc_token_t*)) yaooc_json_parser_regex,
.quoted_string = (bool(*)(pointer,char,yaooc_token_t*)) yaooc_json_parser_quoted_string,
.single_quoted_string = (bool(*)(pointer,yaooc_token_t*)) yaooc_json_parser_single_quoted_string,
.double_quoted_string = (bool(*)(pointer,yaooc_token_t*)) yaooc_json_parser_double_quoted_string,
.bare_string = (bool(*)(pointer,yaooc_token_t*)) yaooc_json_parser_bare_string,
.string_until_chrs = (bool(*)(pointer,const char*,yaooc_token_t*)) yaooc_json_parser_string_until_chrs,
.string_while_chrs = (bool(*)(pointer,const char*,yaooc_token_t*)) yaooc_json_parser_string_while_chrs,
.string_until_eol = (bool(*)(pointer,yaooc_token_t*)) yaooc_json_parser_string_until_eol,
.whitespace = (bool(*)(pointer,yaooc_token_t*)) yaooc_json_parser_whitespace,
.string_within_matching_chr = (bool(*)(pointer,char,char,yaooc_token_t*)) yaooc_json_parser_string_within_matching_chr,
.result = (bool(*)(const_pointer)) yaooc_json_parser_result,
.parse_json_null = (bool(*)(pointer,yaooc_json_value_t**)) yaooc_json_parser_parse_json_null,
.parse_json_bool = (bool(*)(pointer,yaooc_json_value_t**)) yaooc_json_parser_parse_json_bool,
.parse_json_integer = (bool(*)(pointer,yaooc_json_value_t**)) yaooc_json_parser_parse_json_integer,
.parse_json_real = (bool(*)(pointer,yaooc_json_value_t**)) yaooc_json_parser_parse_json_real,
.parse_json_string = (bool(*)(pointer,yaooc_json_value_t**)) yaooc_json_parser_parse_json_string,
.parse_json_array = (bool(*)(pointer,yaooc_json_value_t**)) yaooc_json_parser_parse_json_array,
.parse_json_object = (bool(*)(pointer,yaooc_json_value_t**)) yaooc_json_parser_parse_json_object,
.parse_json_value = (bool(*)(pointer,yaooc_json_value_t**)) yaooc_json_parser_parse_json_value,
.parse_string = (bool(*)(pointer,const char*,yaooc_json_value_t**)) yaooc_json_parser_parse_string,
.parse_file = (bool(*)(pointer,const char*,yaooc_json_value_t**)) yaooc_json_parser_parse_file,
};
const type_info_t __yaooc_json_parser_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_json_parser_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_json_parser_class_table,
.parent_=&__yaooc_base_parser_ti
};
const type_info_t* const yaooc_json_parser_ti=&__yaooc_json_parser_ti;
