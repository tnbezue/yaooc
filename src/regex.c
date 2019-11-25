#include <yaooc/regex.h>

#include <yaooc/regex.h>
#include <string.h>
#include <stdio.h>


void yaooc_regex_pattern_info_default_ctor(pointer __pthis__)
{
yaooc_regex_pattern_info_pointer this=__pthis__;(void)this;


this->pattern_=NULL;
this->flags_=(int)0;

}
void yaooc_regex_pattern_info_dtor(pointer __pthis__)
{
yaooc_regex_pattern_info_pointer this=__pthis__;(void)this;

if(this->pattern_!=NULL) delete(this->pattern_);

}
void yaooc_regex_pattern_info_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaooc_regex_pattern_info_pointer this=__pthis__;(void)this;
yaooc_regex_pattern_info_const_pointer src=__psrc__;(void)src;

call_default_ctor_static(this,yaooc_regex_pattern_info);
assign_static(this,src,yaooc_regex_pattern_info);


}
void yaooc_regex_pattern_info_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_regex_pattern_info_pointer this=__pthis__;(void)this;
yaooc_regex_pattern_info_const_pointer src=__psrc__;(void)src;

this->pattern_=src->pattern_;
this->flags_=src->flags_;

}
const type_info_t __yaooc_regex_pattern_info_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_regex_pattern_info_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_regex_pattern_info_default_ctor,
.dtor_=yaooc_regex_pattern_info_dtor,
.copy_ctor_=yaooc_regex_pattern_info_copy_ctor,
.assign_=yaooc_regex_pattern_info_assign,
.class_table_=NULL,
.parent_=NULL
};
const type_info_t* const yaooc_regex_pattern_info_ti=(const type_info_t* const)&__yaooc_regex_pattern_info_ti;

bool yaooc_regex_parse_pattern(const char* pat,yaooc_regex_pattern_info_t* rei)
{
  bool ret=false;
 *rei= (yaooc_regex_pattern_info_t){ .pattern_ = NULL, .flags_ = REG_EXTENDED };
 if(pat && *pat == '/') {
  const char* end=pat+strlen(pat)-1;
  for(;end > (pat+1);end--) {
   if(*end == 'm') {
    rei->flags_ |= REG_NEWLINE;
   } else if(*end == 'i') {
    rei->flags_ |= REG_ICASE;
   } else if(*end == '/') {
    size_t n=end-pat;
    rei->pattern_=MALLOC(n);
    strncpy(rei->pattern_,pat+1,n-1);
    rei->pattern_[n-1]=0;
        ret=true;
    break;
   } else {
    break;
   }
  }
 }
 return ret;
}

int yaooc_regex_regexec(const regex_t* re,const char* subject,int ofs,size_t n_ov,regmatch_t* ov,int eflags)
{
  int result=regexec(re,subject+ofs,n_ov,ov,eflags);
  if(result == 0 && ofs > 0) {
    size_t i;

    if(n_ov > (re->re_nsub+1))
      n_ov=re->re_nsub+1;
    for(i=0;i<n_ov;i++) {
      if(ov[i].rm_so >= 0) {
        ov[i].rm_so+=ofs;
        ov[i].rm_eo+=ofs;
      }
    }
  }
  return result;
}


yaooc_regex_exception_class_table_t yaooc_regex_exception_class_table ={
.parent_class_table_ = (const class_table_t*) &yaooc_exception_class_table,
.type_name_ = (const char*) "yaooc_regex_exception_t",
.swap = (void(*)(pointer,pointer)) yaooc_regex_exception_swap,
.what = (const char*(*)(const_pointer)) yaooc_regex_exception_what,
};
const type_info_t __yaooc_regex_exception_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_regex_exception_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_regex_exception_class_table,
.parent_=&__yaooc_exception_ti
};
const type_info_t* const yaooc_regex_exception_ti=&__yaooc_regex_exception_ti;
void yaooc_matchdata_swap(pointer __pthis__,pointer s)
{
yaooc_matchdata_pointer this=__pthis__;(void)this;
#define super() yaooc_matchdata_parent_class_table->swap(this,s)
#define PM(method,...) CTM((*yaooc_matchdata_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_matchdata_t* other=s;
      SWAP(regmatch_t *,this->ovector_,other->ovector_);
      SWAP(char*,this->subject_,other->subject_);
      SWAP(int,this->match_result_,other->match_result_);
      SWAP(int,this->n_captures_,other->n_captures_);
    
#undef PM
#undef super
}
yaooc_string_pointer yaooc_matchdata_at(const_pointer __pthis__,size_t i)
{
yaooc_matchdata_const_pointer this=__pthis__;(void)this;
#define super() yaooc_matchdata_parent_class_table->at(this,i)
#define PM(method,...) CTM((*yaooc_matchdata_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_string_pointer ret=new(yaooc_string);
      if(this->ovector_ && this->match_result_==0 && i>= 0 && i < this->n_captures_) {
        if(this->ovector_[i].rm_so >= 0)
          M(ret,insertn,0,this->subject_+this->ovector_[i].rm_so,this->ovector_[i].rm_eo-this->ovector_[i].rm_so);
      }
      return ret;
    
#undef PM
#undef super
}
yaooc_string_pointer yaooc_matchdata_exec(pointer __pthis__,const char* str)
{
yaooc_matchdata_pointer this=__pthis__;(void)this;
#define super() yaooc_matchdata_parent_class_table->exec(this,str)
#define PM(method,...) CTM((*yaooc_matchdata_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_string_pointer ret=new(yaooc_string);
      if(str) {
        regex_t re;
        M(ret,set,str);

        regcomp(&re,"\\$([0-9]+)|\\$\\{([0-9]+)\\}",REG_EXTENDED);
        regmatch_t ov[3];
        int ofs=0;
        while(regexec(&re,M(ret,c_str)+ofs,3,ov,0) == 0) {
          if((ofs !=0 || ov[0].rm_so !=0) && *(M(ret,c_str)+ofs+ov[0].rm_so-1) == '\\') {
            M(ret,erase,ofs+ov[0].rm_so-1);
            ofs+=ov[0].rm_eo-1;
          } else {
            int iov=ov[1].rm_so == -1 ? 2 : 1;
            int i=atoi(M(ret,c_str)+ofs+ov[iov].rm_so);
            printf("YY -- %d %d X%.5sX\n",iov,i,M(ret,c_str)+ofs+ov[iov].rm_so);
            const char* repstr;
            int l;
            if(i < this->n_captures_) {
              repstr=this->subject_+this->ovector_[i].rm_so;
              l=this->ovector_[i].rm_eo-this->ovector_[i].rm_so;
            } else {
              repstr="";
              l=0;
            }
            debug_printf("MM -- %d %d %d %d\n",i,ofs+ov[0].rm_so,ov[0].rm_eo-ov[0].rm_so,l);
            M(ret,replacen,ofs+ov[0].rm_so,ov[0].rm_eo-ov[0].rm_so,repstr,l);
            ofs+=l;
          }
        }
      }
      return ret;
    
#undef PM
#undef super
}
const char* yaooc_matchdata_subject(const_pointer __pthis__)
{
yaooc_matchdata_const_pointer this=__pthis__;(void)this;
#define super() yaooc_matchdata_parent_class_table->subject(this)
#define PM(method,...) CTM((*yaooc_matchdata_parent_class_table),this,method,## __VA_ARGS__)


      return this->subject_;
    
#undef PM
#undef super
}
bool yaooc_matchdata_good(const_pointer __pthis__)
{
yaooc_matchdata_const_pointer this=__pthis__;(void)this;
#define super() yaooc_matchdata_parent_class_table->good(this)
#define PM(method,...) CTM((*yaooc_matchdata_parent_class_table),this,method,## __VA_ARGS__)


      return ((yaooc_matchdata_const_pointer)this)->match_result_==0;
    
#undef PM
#undef super
}
size_t yaooc_matchdata_size(const_pointer __pthis__)
{
yaooc_matchdata_const_pointer this=__pthis__;(void)this;
#define super() yaooc_matchdata_parent_class_table->size(this)
#define PM(method,...) CTM((*yaooc_matchdata_parent_class_table),this,method,## __VA_ARGS__)


      return this->match_result_==0 ? this->n_captures_ : 0;
    
#undef PM
#undef super
}
yaooc_matchdata_class_table_t yaooc_matchdata_class_table ={
.parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
.type_name_ = (const char*) "yaooc_matchdata_t",
.swap = (void(*)(pointer,pointer)) yaooc_matchdata_swap,
.at = (yaooc_string_pointer(*)(const_pointer,size_t)) yaooc_matchdata_at,
.exec = (yaooc_string_pointer(*)(pointer,const char*)) yaooc_matchdata_exec,
.subject = (const char*(*)(const_pointer)) yaooc_matchdata_subject,
.good = (bool(*)(const_pointer)) yaooc_matchdata_good,
.size = (size_t(*)(const_pointer)) yaooc_matchdata_size,
};
void yaooc_matchdata_default_ctor(pointer __pthis__)
{
yaooc_matchdata_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_matchdata);



      this->ovector_=NULL;
      this->subject_=NULL;
      this->match_result_=-1;
      this->n_captures_=0;
    
}
void yaooc_matchdata_dtor(pointer __pthis__)
{
yaooc_matchdata_pointer this=__pthis__;(void)this;


      if(this->ovector_)
        FREE(this->ovector_);
      if(this->subject_)
        FREE(this->subject_);
    
}
void yaooc_matchdata_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaooc_matchdata_pointer this=__pthis__;(void)this;
yaooc_matchdata_const_pointer src=__psrc__;(void)src;

call_parent_default_ctor_static(this,yaooc_matchdata);


      yaooc_matchdata_default_ctor(this);
      yaooc_matchdata_assign(this,src);
    
}
void yaooc_matchdata_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_matchdata_pointer this=__pthis__;(void)this;
yaooc_matchdata_const_pointer src=__psrc__;(void)src;


      if(this->ovector_)
        FREE(this->ovector_);
      if(this->subject_)
        FREE(this->subject_);
      this->n_captures_=src->n_captures_;

      this->match_result_=src->match_result_;
      if(src->ovector_) {
        size_t size=this->n_captures_*sizeof(regmatch_t);
        this->ovector_=MALLOC(size);
        memcpy(this->ovector_,src->ovector_,size);
      } else
        this->ovector_=NULL;
      this->subject_ = src->subject_ ? STRDUP(src->subject_) : NULL;
    
}
const type_info_t __yaooc_matchdata_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_matchdata_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_matchdata_default_ctor,
.dtor_=yaooc_matchdata_dtor,
.copy_ctor_=yaooc_matchdata_copy_ctor,
.assign_=yaooc_matchdata_assign,
.class_table_=(const class_table_t*) &yaooc_matchdata_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_matchdata_ti=&__yaooc_matchdata_ti;
static void yaooc_regex_compile(pointer);
static bool yaooc_regex_match_private(pointer,yaooc_matchdata_pointer,int);
static void yaooc_regex_compile(pointer __pthis__)
{
yaooc_regex_pointer this=__pthis__;(void)this;

      this->re_=MALLOC(sizeof(regex_t));
      this->compile_result_=regcomp(this->re_,this->pattern_,this->compile_flags_|REG_EXTENDED);
      if(this->compile_result_ != 0) {
        regfree(this->re_);
        FREE(this->re_);
      }
    
}
static bool yaooc_regex_match_private(pointer __pthis__,yaooc_matchdata_pointer md,int offset)
{
yaooc_regex_pointer this=__pthis__;(void)this;

      bool ret=false;
      if(this->re_) {
        if((md->match_result_=yaooc_regex_regexec(this->re_,md->subject_,offset,md->n_captures_,md->ovector_,0)) == 0) {
          md->n_captures_=this->re_->re_nsub+1;
          ret=true;
        } else {



          md->n_captures_=0;
        }
      }
      return ret;
    
}
void yaooc_regex_ctor_ccs_int(pointer __pthis__,va_list __con_args__)
{
yaooc_regex_pointer this=__pthis__;
const char* pattern = va_arg(__con_args__,const char*);
int flags = va_arg(__con_args__,int);

call_parent_default_ctor_static(this,yaooc_regex);


      yaooc_regex_default_ctor(this);
      yaooc_regex_set_pattern_flags(this,pattern,flags);
    
}
void yaooc_regex_ctor_ccs(pointer __pthis__,va_list __con_args__)
{
yaooc_regex_pointer this=__pthis__;
const char* re_str = va_arg(__con_args__,const char*);

call_parent_default_ctor_static(this,yaooc_regex);


      yaooc_regex_pattern_info_t rei;
      if(!yaooc_regex_parse_pattern(re_str,&rei)) {
        THROW(new_ctor(yaooc_regex_exception,yaooc_regex_exception_ctor_v,"Invalid regular expression: %s",re_str));
      }
      yaooc_regex_set_pattern_flags(this,rei.pattern_,rei.flags_);
      FREE(rei.pattern_);
    
}
void yaooc_regex_set_pattern_flags(pointer __pthis__,const char* pattern,int flags)
{
yaooc_regex_pointer this=__pthis__;(void)this;
#define super() yaooc_regex_parent_class_table->set_pattern_flags(this,pattern,flags)
#define PM(method,...) CTM((*yaooc_regex_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_regex_dtor(this);
      this->compile_flags_=flags;
      this->compile_result_=-1;
      if(pattern) {
        this->pattern_=STRDUP(pattern);
        yaooc_regex_compile(this);
      }
    
#undef PM
#undef super
}
const char* yaooc_regex_get_pattern(const_pointer __pthis__)
{
yaooc_regex_const_pointer this=__pthis__;(void)this;
#define super() yaooc_regex_parent_class_table->get_pattern(this)
#define PM(method,...) CTM((*yaooc_regex_parent_class_table),this,method,## __VA_ARGS__)


      return this->pattern_;
    
#undef PM
#undef super
}
int yaooc_regex_get_flags(const_pointer __pthis__)
{
yaooc_regex_const_pointer this=__pthis__;(void)this;
#define super() yaooc_regex_parent_class_table->get_flags(this)
#define PM(method,...) CTM((*yaooc_regex_parent_class_table),this,method,## __VA_ARGS__)


      return this->compile_flags_;
    
#undef PM
#undef super
}
yaooc_matchdata_pointer yaooc_regex_match(pointer __pthis__,const char* subject,int match_flags)
{
yaooc_regex_pointer this=__pthis__;(void)this;
#define super() yaooc_regex_parent_class_table->match(this,subject,match_flags)
#define PM(method,...) CTM((*yaooc_regex_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_matchdata_pointer ret=new(yaooc_matchdata);
      if(this->compile_result_==0) {
        ret->n_captures_=this->re_->re_nsub+1;
        ret->ovector_=MALLOC(sizeof(regmatch_t)*ret->n_captures_);
        ret->subject_=STRDUP(subject);
        yaooc_regex_match_private(this,ret,0);
      }
      return ret;
    
#undef PM
#undef super
}
bool yaooc_regex_match_next(pointer __pthis__,yaooc_matchdata_pointer md)
{
yaooc_regex_pointer this=__pthis__;(void)this;
#define super() yaooc_regex_parent_class_table->match_next(this,md)
#define PM(method,...) CTM((*yaooc_regex_parent_class_table),this,method,## __VA_ARGS__)


      if(md->match_result_ == 0) {
        return yaooc_regex_match_private(this,md,md->ovector_[0].rm_eo);
      }
      return false;
    
#undef PM
#undef super
}
bool yaooc_regex_good(const_pointer __pthis__)
{
yaooc_regex_const_pointer this=__pthis__;(void)this;
#define super() yaooc_regex_parent_class_table->good(this)
#define PM(method,...) CTM((*yaooc_regex_parent_class_table),this,method,## __VA_ARGS__)


      return this->compile_result_==0;
    
#undef PM
#undef super
}
yaooc_regex_class_table_t yaooc_regex_class_table ={
.parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
.type_name_ = (const char*) "yaooc_regex_t",
.swap = (void(*)(pointer,pointer)) yaooc_regex_swap,
.set_pattern_flags = (void(*)(pointer,const char*,int)) yaooc_regex_set_pattern_flags,
.get_pattern = (const char*(*)(const_pointer)) yaooc_regex_get_pattern,
.get_flags = (int(*)(const_pointer)) yaooc_regex_get_flags,
.match = (yaooc_matchdata_pointer(*)(pointer,const char*,int)) yaooc_regex_match,
.match_next = (bool(*)(pointer,yaooc_matchdata_pointer)) yaooc_regex_match_next,
.good = (bool(*)(const_pointer)) yaooc_regex_good,
};
void yaooc_regex_default_ctor(pointer __pthis__)
{
yaooc_regex_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_regex);



      this->re_=NULL;
      this->pattern_=NULL;
      this->compile_flags_=0;
      this->compile_result_=-1;
    
}
void yaooc_regex_dtor(pointer __pthis__)
{
yaooc_regex_pointer this=__pthis__;(void)this;


      if(this->re_) {
        regfree(this->re_);
        FREE(this->re_);
      }
      if(this->pattern_)
        FREE(this->pattern_);
    
}
void yaooc_regex_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaooc_regex_pointer this=__pthis__;(void)this;
yaooc_regex_const_pointer src=__psrc__;(void)src;

call_parent_default_ctor_static(this,yaooc_regex);


      yaooc_regex_default_ctor(this);
      yaooc_regex_assign(this,src);
    
}
void yaooc_regex_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_regex_pointer this=__pthis__;(void)this;
yaooc_regex_const_pointer src=__psrc__;(void)src;


      yaooc_regex_set_pattern_flags(this,src->pattern_,src->compile_flags_);
    
}
const type_info_t __yaooc_regex_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_regex_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_regex_default_ctor,
.dtor_=yaooc_regex_dtor,
.copy_ctor_=yaooc_regex_copy_ctor,
.assign_=yaooc_regex_assign,
.class_table_=(const class_table_t*) &yaooc_regex_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_regex_ti=&__yaooc_regex_ti;

void yaooc_string_sub_(pointer p,const char* pat,const char* str)
{
  yaooc_string_t* this=p;
  if(pat) {
    yaooc_regex_pattern_info_t rmi;
    if(yaooc_regex_parse_pattern(pat,&rmi)) {
      yaooc_regex_t* re = new_ctor(yaooc_regex,yaooc_regex_ctor_ccs_int,rmi.pattern_,rmi.flags_);

      yaooc_string_sub_re_(this,re,str);
      delete(re);
      FREE(rmi.pattern_);
    } else if (strcmp(pat," ")==0) {
      yaooc_regex_t* re = new_ctor(yaooc_regex,yaooc_regex_ctor_ccs_int,"\\s+",REG_EXTENDED);
      yaooc_string_sub_re_(this,re,str);
      delete(re);
    } else {
      char* ptr=strstr(this->array_,pat);
      if(ptr)
        M(this,replace,ptr-this->array_,strlen(pat),str);
    }
  }
}

void yaooc_string_sub_re_(pointer p,yaooc_regex_const_pointer re,const char *str)
{
  yaooc_string_pointer this=p;
 regmatch_t ov;
 if(yaooc_regex_regexec(re->re_,this->array_,0,1,&ov,0) == 0) {
  M(this,replace,ov.rm_so,ov.rm_eo-ov.rm_so,str);
 }
}

void yaooc_string_gsub_(pointer p,const char* pat,const char* str)
{
 yaooc_string_pointer this=p;
 size_t sl= str ? strlen(str) : 0;
 if(pat) {
  yaooc_regex_pattern_info_t rmi;
    if(yaooc_regex_parse_pattern(pat,&rmi)) {
   yaooc_regex_t* re = new_ctor(yaooc_regex,yaooc_regex_ctor_ccs_int,rmi.pattern_,rmi.flags_);
   yaooc_string_gsub_re_(this,re,str);
   delete(re);
   FREE(rmi.pattern_);
  } else if(strcmp(pat," ")==0) {
   yaooc_regex_t* re = new_ctor(yaooc_regex,yaooc_regex_ctor_ccs_int,"\\s+",REG_EXTENDED);
   yaooc_string_gsub_re_(this,re,str);
   delete(re);
  } else {
   size_t l=strlen(pat);
   char* ptr;
   size_t ofs=0;
   while((ptr=strstr(this->array_+ofs,pat))!=NULL) {
    size_t pos=ptr-this->array_;
    M(this,replace,pos,l,str);
    ofs=pos+sl;
   }
  }
 }
}

void yaooc_string_gsub_re_(pointer p,yaooc_regex_const_pointer re,const char* str)
{
 yaooc_string_pointer this=p;
 regmatch_t ov;
 size_t ofs=0;
 size_t l=strlen(str);
 while(ofs < this->size_ && yaooc_regex_regexec(re->re_,this->array_,ofs,1,&ov,0) == 0) {
  M(this,replace,ov.rm_so,ov.rm_eo-ov.rm_so,str);
  ofs=ov.rm_so+l;
 }
}


bool yaooc_string_match(const_pointer p,const char* pat)
{
 yaooc_string_const_pointer this=p;
 bool ret=true;
 if(pat) {
  yaooc_regex_pattern_info_t rmi;
    if(yaooc_regex_parse_pattern(pat,&rmi)) {
   yaooc_regex_t* re = new_ctor(yaooc_regex,yaooc_regex_ctor_ccs_int,rmi.pattern_,rmi.flags_);
   ret = yaooc_string_match_re(this,re);
   delete(re);
   FREE(rmi.pattern_);
  } else {
   ret = strstr(this->array_,pat) != NULL;
  }
 }
 return ret;
}

bool yaooc_string_match_re(const_pointer p,yaooc_regex_const_pointer re)
{
 yaooc_string_const_pointer this=p;
 return yaooc_regex_regexec(re->re_,this->array_,0,0,NULL,0) == 0;
}

extern const char* yaooc_whitespace;
yaooc_string_vector_pointer yaooc_string_split(const_pointer p,const char* str,size_t max)
{
  yaooc_string_const_pointer this=p;
  yaooc_string_vector_t* ret=NULL;
 if(str) {
  yaooc_regex_pattern_info_t rmi;
    if(yaooc_regex_parse_pattern(str,&rmi)) {
   yaooc_regex_t* re = new_ctor(yaooc_regex,yaooc_regex_ctor_ccs_int,rmi.pattern_,rmi.flags_);
   ret = yaooc_string_split_re(p,re,max);
   delete(re);
   FREE(rmi.pattern_);
  } else {
   ret=new(yaooc_string_vector);
   char *beg,*end;
   size_t l=strlen(str);
   yaooc_string_t* temp=new(yaooc_string);
   if(strcmp(str," ")==0) {
    beg=this->array_;
    do {
     beg+=strspn(beg,yaooc_whitespace);
     size_t ofs=strcspn(beg,yaooc_whitespace);
     M(temp,setn,beg,ofs);
     M(ret,push_back,temp);
     beg+=ofs;
    } while(*beg!=0);
   } else {
    beg=this->array_;
    while((end=strstr(beg,str)) && --max > 0) {
     M(temp,setn,beg,end-beg);
     beg=end+l;
     M(ret,push_back,temp);
    }
   }
   if(*beg != 0) {
    M(temp,set,beg);
    M(ret,push_back,temp);
   }
   delete(temp);
  }



  while(M(ret,size)>0 && M(M(ret,back),size)==0)
   M(ret,pop_back);
 }
  return ret ? ret : new(yaooc_string_vector);
}

yaooc_string_vector_pointer yaooc_string_split_re(const_pointer p,yaooc_regex_const_pointer re,size_t max)
{
  yaooc_string_const_pointer this=p;
  yaooc_string_vector_pointer ret=new(yaooc_string_vector);

  regmatch_t rm;

 if(re && re->re_) {
    yaooc_string_t* temp=new(yaooc_string);
    char* beg=this->array_;
    while(yaooc_regex_regexec(re->re_,beg,0,1,&rm,0)==0) {
      M(temp,setn,beg,rm.rm_so);
      beg+=rm.rm_eo;
      M(ret,push_back,temp);
    }
    if(*beg != 0) {
      M(temp,set,beg);
      M(ret,push_back,temp);
    }

    delete(temp);
  }
  return ret;
}

