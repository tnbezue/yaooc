/*
		Copyright (C) 2016-2018  by Terry N Bezue

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

#include <stdio.h>
#include <string.h>
#include <yaooc/regex.h>
#include <yaooc/stream.h>

/*  Begin YAOOC PreProcessor generated content */

/* Private items for yaooc_matchdata */

/* Protected items for yaooc_matchdata */


/* Typeinfo for yaooc_matchdata */
void yaooc_matchdata_default_ctor(pointer p)
{
  yaooc_matchdata_pointer this=p;
  this->ovector_=NULL;
  this->subject_=NULL;
  this->match_result_=-1;
  this->n_captures_=0;
  this->match_flags_=0;
}

void yaooc_matchdata_dtor(pointer p)
{
  yaooc_matchdata_pointer this=p;
  if(this->ovector_)
    FREE(this->ovector_);
  if(this->subject_)
    FREE(this->subject_);
}

void yaooc_matchdata_copy_ctor(pointer d,const_pointer s)
{
  yaooc_matchdata_default_ctor(d);
  yaooc_matchdata_assign(d,s);
}

void yaooc_matchdata_assign(pointer d,const_pointer s)
{
  yaooc_matchdata_pointer this=d;
  yaooc_matchdata_const_pointer src=s;
  if(this->ovector_)
    FREE(this->ovector_);
  if(this->subject_)
    FREE(this->subject_);
  this->n_captures_=src->n_captures_;
  this->match_flags_=src->match_flags_;
  this->match_result_=src->match_result_;
  if(src->ovector_) {
    size_t size=this->n_captures_*sizeof(regmatch_t);
    this->ovector_=MALLOC(size);
    memcpy(this->ovector_,src->ovector_,size);
  } else
    this->ovector_=NULL;
  this->subject_ = src->subject_ ? STRDUP(src->subject_) : NULL;
}

/* Constructors for yaooc_matchdata */

/* Class table methods for yaooc_matchdata */
const char* yaooc_matchdata_isa(const_pointer p) { return "yaooc_matchdata_t"; }

void yaooc_matchdata_swap(pointer p,pointer o)
{
  yaooc_matchdata_pointer this=p;
  yaooc_matchdata_pointer other=o;
  SWAP(regmatch_t *,this->ovector_,other->ovector_);
  SWAP(char*,this->subject_,other->subject_);
  SWAP(int,this->match_result_,other->match_result_);
  SWAP(int,this->n_captures_,other->n_captures_);
  SWAP(int,this->match_flags_,other->match_flags_);
}

yaooc_string_pointer yaooc_matchdata_at(const_pointer p,size_t i)
{
  yaooc_matchdata_const_pointer this=p;
  yaooc_string_pointer ret=new(yaooc_string);
  if(this->ovector_  && this->match_result_==0 && i>= 0 && i < this->n_captures_) {
    M(ret,insertn,0,this->subject_+this->ovector_[i].rm_so,this->ovector_[i].rm_eo-this->ovector_[i].rm_so);
  }
  return ret;
}

yaooc_string_pointer yaooc_matchdata_exec(pointer p,const char* str)
{
  yaooc_matchdata_pointer this=p;
  yaooc_string_pointer ret=new(yaooc_string);
  if(str) {
    regex_t re;
    M(ret,set,str);
//    tre_regcomp(&re,"\\$([0-9]+)|\\$\\{([0-9]+)\\}",REG_EXTENDED);
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
}

const char* yaooc_matchdata_subject(const_pointer p)
{
  yaooc_matchdata_const_pointer this=p;
  return this->subject_;
}

bool yaooc_matchdata_bool(const_pointer p)
{
  return ((yaooc_matchdata_const_pointer)p)->match_result_==0;
}

size_t yaooc_matchdata_size(const_pointer p)
{
  yaooc_matchdata_const_pointer this=p;
  return this->match_result_==0 ? this->n_captures_ : 0;
}


/* Class table for yaooc_matchdata */
yaooc_matchdata_class_table_t yaooc_matchdata_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .isa = (const char* (*) (const_pointer p)) yaooc_matchdata_isa,
  .is_descendant = (bool (*) (const_pointer p,const char*)) yaooc_matchdata_is_descendant,
  .swap = (void (*) (pointer p,pointer)) yaooc_matchdata_swap,
  .at = (yaooc_string_pointer (*) (const_pointer p,size_t)) yaooc_matchdata_at,
  .exec = (yaooc_string_pointer (*) (pointer p,const char*)) yaooc_matchdata_exec,
  .subject = (const char* (*) (const_pointer p)) yaooc_matchdata_subject,
  .bool = (bool (*) (const_pointer p)) yaooc_matchdata_bool,
  .size = (size_t (*) (const_pointer p)) yaooc_matchdata_size,
};


DEFINE_TYPE_INFO(yaooc_matchdata,yaooc_matchdata_default_ctor,yaooc_matchdata_dtor,yaooc_matchdata_copy_ctor,
			yaooc_matchdata_assign,NULL,NULL,NULL,&yaooc_matchdata_class_table,yaooc_object)


/* Private items for yaooc_regex */
void yaooc_regex_compile(pointer p)
{
  yaooc_regex_pointer this=p;
  this->re_=MALLOC(sizeof(regex_t));
  this->compile_result_=regcomp(this->re_,this->pattern_,this->compile_flags_);
  if(this->compile_result_ != 0) {
    regfree(this->re_);
    FREE(this->re_);
  }
}

#define min(x,y) ((x)<(y)) ? (x) : (y)
int yaooc_regex_regexec(const regex_t* re,const char* subject,int ofs,size_t n,regmatch_t* ov,int eflags)
{
  int result=regexec(re,subject+ofs,n,ov,eflags);
  if(result == 0 && ofs > 0) {
    size_t i;
    n=min(re->re_nsub+1,n);
    for(i=0;i<n;i++) {
      ov[i].rm_so+=ofs;
      ov[i].rm_eo+=ofs;
    }
  }
  return result;
}

bool yaooc_regex_match_private(yaooc_regex_const_pointer this,yaooc_matchdata_pointer md,int offset)
{
  bool ret=false;
  if(this->re_) {
    if((md->match_result_=yaooc_regex_regexec(this->re_,md->subject_,offset,md->n_captures_,md->ovector_,0)) == 0) {
      md->n_captures_=this->re_->re_nsub+1;
      ret=true;
    } else {
      /* Match failed, indicate no matches found */
/*      free(md->ovector_);
      md->ovector_=NULL;*/
      md->n_captures_=0;
    }
  }
  return ret;
}
/* Protected items for yaooc_regex */


/* Typeinfo for yaooc_regex */
void yaooc_regex_default_ctor(pointer p)
{
  yaooc_regex_pointer this=p;
  this->re_=NULL;
  this->pattern_=NULL;
  this->compile_flags_=0;
  this->compile_result_=-1;
}

void yaooc_regex_dtor(pointer p)
{
  yaooc_regex_pointer this=p;
  if(this->re_) {
    regfree(this->re_);
    FREE(this->re_);
  }
  if(this->pattern_)
    FREE(this->pattern_);
}

void yaooc_regex_copy_ctor(pointer d,const_pointer s)
{
  yaooc_regex_default_ctor(d);
  yaooc_regex_assign(d,s);
}

void yaooc_regex_assign(pointer d,const_pointer s)
{
  yaooc_regex_const_pointer src=s;
  yaooc_regex_set_pattern_flags(d,src->pattern_,src->compile_flags_);
}

/* Constructors for yaooc_regex */
void yaooc_regex_ctor_ccs_int(pointer p,va_list args)
{
  const char* pattern=va_arg(args,const char*);
  int flags=va_arg(args,int);
  yaooc_regex_default_ctor(p);
  yaooc_regex_set_pattern_flags(p,pattern,flags);
}

/* Class table methods for yaooc_regex */
void yaooc_regex_set_pattern_flags(pointer p,const char* pattern,int flags)
{
  yaooc_regex_pointer this=p;
  yaooc_regex_dtor(p);
  this->compile_flags_=flags;
  this->compile_result_=-1;
  if(pattern) {
    this->pattern_=STRDUP(pattern);
    yaooc_regex_compile(p);
  }
}

const char* yaooc_regex_get_pattern(const_pointer p)
{
  yaooc_regex_const_pointer this=p;
  return this->pattern_;
}

void yaooc_regex_set_flags(pointer p,int flags)
{
  yaooc_regex_pointer this=p;
  this->compile_flags_=flags;
}

int yaooc_regex_get_flags(const_pointer p)
{
  yaooc_regex_const_pointer this=p;
  return this->compile_flags_;
}

yaooc_matchdata_pointer yaooc_regex_match(pointer p,const char* subject,int match_flags)
{
  yaooc_regex_pointer this=p;
  yaooc_matchdata_pointer ret=new(yaooc_matchdata);
  if(this->compile_result_==0) {
    ret->n_captures_=this->re_->re_nsub+1;
    ret->ovector_=MALLOC(sizeof(regmatch_t)*ret->n_captures_);
    ret->subject_=STRDUP(subject);
    yaooc_regex_match_private(this,ret,0);
  }
  return ret;
}

bool yaooc_regex_match_next(pointer p,yaooc_matchdata_pointer md)
{
  yaooc_regex_pointer this=p;
  if(md->match_result_ == 0) {
    return yaooc_regex_match_private(this,md,md->ovector_[0].rm_eo);
  }
  return false;
}

bool yaooc_regex_bool(const_pointer p)
{
  yaooc_regex_const_pointer this=p;
  return this->compile_result_==0;
}

/* Class table for yaooc_regex */
yaooc_regex_class_table_t yaooc_regex_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .isa = (const char* (*) (const_pointer p)) yaooc_regex_isa,
  .is_descendant = (bool (*) (const_pointer p,const char*)) yaooc_regex_is_descendant,
  .swap = (void (*) (pointer p,pointer)) yaooc_regex_swap,
  .set_pattern_flags = (void (*) (pointer p,const char*,int)) yaooc_regex_set_pattern_flags,
  .get_pattern = (const char* (*) (const_pointer p)) yaooc_regex_get_pattern,
  .get_flags = (int (*) (const_pointer p)) yaooc_regex_get_flags,
  .match = (yaooc_matchdata_pointer (*) (pointer p,const char*,int)) yaooc_regex_match,
  .match_next = (bool (*) (pointer p,yaooc_matchdata_pointer)) yaooc_regex_match_next,
  .bool = (bool (*) (const_pointer p)) yaooc_regex_bool,
};


DEFINE_TYPE_INFO(yaooc_regex,yaooc_regex_default_ctor,yaooc_regex_dtor,yaooc_regex_copy_ctor,yaooc_regex_assign,
		NULL,NULL,NULL,&yaooc_regex_class_table,yaooc_object)
/*  End YAOOC PreProcessor generated content */
