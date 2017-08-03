#include <yaooc/regex.h>

void yaooc_matchdata_default_ctor(pointer p)
{
  yaooc_matchdata_pointer this=p;
  this->subject_=new(yaooc_string);
  this->match_data_=NULL;
  this->match_flags_=0;
}

void yaooc_matchdata_dtor(pointer p)
{
  yaooc_matchdata_pointer this=p;
  delete(this->subject_);
  if(this->match_data_)
    pcre2_match_data_free(this->match_data_);
}

void yaooc_matchdata_copy_ctor(pointer d,const_pointer s)
{
  yaooc_matchdata_default_ctor(d);
  //yaooc_matchdata_assign(d,s); /* Don't allow match data to be copied */
}

void yaooc_matchdata_assign(pointer d,const_pointer s)
{
//  yaooc_matchdata_pointer dst=d;
//  yaooc_matchdata_const_pointer src=s;
//  assign_static(dst->subject_,src->subject_,yaooc_string_ti);
}

ISA_IMPLEMENTATION(yaooc_matchdata,yaooc_object)

char* yaooc_matchdata_at(pointer p,uint32_t i)
{
  yaooc_matchdata_pointer this=p;
  char* ret=NULL;
  if(this->match_data_) {
    PCRE2_SIZE length;
    if(pcre2_substring_length_bynumber(this->match_data_,i,&length)==0) {
      ret=new_array(char,++length);
      pcre2_substring_copy_bynumber(this->match_data_,i,(PCRE2_UCHAR*)ret,&length);
    }
  }
  return ret;
}

yaooc_string_const_pointer yaooc_matchdata_subject(const_pointer p)
{
  return ((yaooc_matchdata_const_pointer)p)->subject_;
}

bool yaooc_matchdata_good(const_pointer p)
{
  return ((yaooc_matchdata_const_pointer)p)->match_data_!=NULL;
}

bool yaooc_matchdata_bad(const_pointer p)
{
  return ((yaooc_matchdata_const_pointer)p)->match_data_==NULL;
}

uint32_t yaooc_matchdata_size(const_pointer p)
{
  yaooc_matchdata_const_pointer this=p;
  return this->match_data_ ? pcre2_get_ovector_count(this->match_data_) : 0;
}

yaooc_matchdata_class_members_t yaooc_matchdata_class_members = { YAOOC_MATCHDATA_CLASS_MEMBERS };

DEFINE_TYPE_INFO(yaooc_matchdata,yaooc_matchdata_default_ctor,yaooc_matchdata_dtor,yaooc_matchdata_copy_ctor,yaooc_matchdata_assign,NULL,&yaooc_matchdata_class_members,yaooc_object)

void yaooc_regex_compile_pattern(yaooc_regex_pointer);

void yaooc_regex_default_ctor(pointer p)
{
  yaooc_regex_pointer this=p;
  this->re_=NULL;
  this->pattern_=new(yaooc_string);
  this->compile_flags_=0;
}

void yaooc_regex_dtor(pointer p)
{
  yaooc_regex_pointer this=p;
  if(this->re_!=NULL)
    pcre2_code_free(this->re_);
  delete(this->pattern_);
}

void yaooc_regex_copy_ctor(pointer d,const_pointer s)
{
  yaooc_regex_default_ctor(d);
  yaooc_regex_assign(d,s);
}

void yaooc_regex_assign(pointer d,const_pointer s)
{
  yaooc_regex_pointer dst=d;
  yaooc_regex_const_pointer src=s;
/*  if(dst->re_) {
    pcre2_code_free(this->re_);
    dst->re_=NULL;
  }*/
  real_assign_static(dst->pattern_,src->pattern_,yaooc_string_ti);
  dst->compile_flags_=src->compile_flags_;
  yaooc_regex_compile_pattern(dst);
}

ISA_IMPLEMENTATION(yaooc_regex,yaooc_object)

bool yaooc_regex_match_private(yaooc_regex_pointer,yaooc_matchdata_pointer,PCRE2_SIZE);

void yaooc_regex_set_pattern(pointer p,const char * pat,int flags)
{
  yaooc_regex_pointer this=p;
  M(this->pattern_,set,pat);
  this->compile_flags_=flags;
  yaooc_regex_compile_pattern(this);
}

yaooc_string_const_pointer yaooc_regex_get_pattern(const_pointer p)
{
  return ((yaooc_regex_const_pointer)p)->pattern_;
}

int yaooc_regex_get_flags(const_pointer p)
{
  return ((yaooc_regex_const_pointer)p)->compile_flags_;
}

yaooc_matchdata_pointer yaooc_regex_match(pointer p,const char * subject,uint32_t match_flags)
{
  yaooc_regex_pointer this=p;
  yaooc_matchdata_pointer ret=new(yaooc_matchdata);
  if(this->re_) {
    ret->match_data_=pcre2_match_data_create_from_pattern(this->re_,NULL);
    M(ret->subject_,set,subject);
    ret->match_flags_=match_flags;
    yaooc_regex_match_private(this,ret,0);
  }
  return ret;
}

bool yaooc_regex_match_next(pointer p,pointer s)
{
  yaooc_matchdata_pointer md=s;
  if(md->match_data_ != NULL) {
    PCRE2_SIZE* ovector=pcre2_get_ovector_pointer(md->match_data_);
    return yaooc_regex_match_private(p,md,ovector[1]);
  }
  return false;
}

bool yaooc_regex_good(const_pointer p)
{
  return ((yaooc_regex_const_pointer)p)->re_!=NULL;
}

bool yaooc_regex_bad(const_pointer p)
{
  return ((yaooc_regex_const_pointer)p)->re_==NULL;
}

void yaooc_regex_ctor_pat_flags(pointer p,va_list args)
{
  yaooc_regex_pointer this=p;
  const char * pat=va_arg(args,const char *);
  int compile_flags=va_arg(args,int);
  yaooc_regex_default_ctor(this);
  yaooc_regex_set_pattern(this,pat,compile_flags);
};

void yaooc_regex_compile_pattern(yaooc_regex_pointer this)
{
  int errorcode;
  PCRE2_SIZE erroroffset;
  if(M(this->pattern_,size)>0)
    this->re_=pcre2_compile((PCRE2_SPTR)M(this->pattern_,c_str),PCRE2_ZERO_TERMINATED,this->compile_flags_,&errorcode,&erroroffset,NULL);
}

bool yaooc_regex_match_private(yaooc_regex_pointer this,yaooc_matchdata_pointer md,PCRE2_SIZE offset)
{
  if(this->re_) {
    if(pcre2_match(this->re_,(PCRE2_SPTR)M(md->subject_,c_str),PCRE2_ZERO_TERMINATED,offset,md->match_flags_,md->match_data_,NULL) < 0) {
      /* Match failed, destroy match data */
      pcre2_match_data_free(md->match_data_);
      md->match_data_=NULL;
    }
  }
  return false;
}

yaooc_regex_class_members_t yaooc_regex_class_members = { YAOOC_REGEX_CLASS_MEMBERS };

DEFINE_TYPE_INFO(yaooc_regex,yaooc_regex_default_ctor,yaooc_regex_dtor,yaooc_regex_copy_ctor,yaooc_regex_assign,NULL,&yaooc_regex_class_members,yaooc_object)

