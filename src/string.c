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

#include <yaooc/string.h>
#include <yaooc/stream.h>
#include <string.h>
#include <ctype.h>
#ifdef __YAOOC_USE_TRE__
#include <tre/regex.h>
#else
#include <regex.h>
#endif

extern int yaooc_regex_regexec(const regex_t*,const char*,int,size_t,regmatch_t*,int);
static void yaooc_regex_flags_pat(const char* pat,char** re_pat,int* re_flags);

const void *memrmem(const void *ptr, size_t size, const void *pat, size_t patsize)
{
	const char *p;

	if(ptr != NULL && pat != NULL) {

		/* Special cases */
		if (size < patsize)
			return NULL;
		if (patsize == 0)
			return ptr;

		for (p = (const char*)ptr + size - patsize ; size >= patsize; --p, --size)
			if(*p == *(const char*)pat)
				if (memcmp(p, pat, patsize) == 0) // adding 1 to p and pat maybe slower
					return p;
	}
	return NULL;
}

void* memrchr(const void*,size_t,size_t);

#ifdef _WIN32
void* memrchr(const void* buf,size_t c,size_t spos)
{
	const char* ptr = (const char*)buf+spos-1;
	while(ptr >= (const char*)buf) {
		if(*ptr == c)
			return (void*)ptr;
		ptr--;
	}
	return NULL;
}

#endif

/* Private items for yaooc_string */

/* Protected items for yaooc_string */
const size_t yaooc_string_npos = (const size_t)-1;


/* Typeinfo for yaooc_string */
void yaooc_string_default_ctor(pointer p)
{
  yaooc_string_pointer this=p;
	call_constructor(this,yaooc_array_container_ctor_ti,char_ti);
  M(this,increase_capacity,1);
	*END(p)=0;
}
/*
void yaooc_string_dtor(pointer p)
{
  yaooc_string_pointer this=p;
  this->size_=0;
}
*/
void yaooc_string_copy_ctor(pointer d,const_pointer s)
{
  yaooc_string_default_ctor(d);
  yaooc_string_assign(d,s);
}

void yaooc_string_assign(pointer d,const_pointer s)
{
  yaooc_string_pointer this=d;
  this->size_=0;
  *(this->array_)=0;
  yaooc_string_insertn(d,0,BEGIN(s),SIZE(s));
}

bool yaooc_string_less_than_compare(const_pointer p1,const_pointer p2)
{
  return strcmp(((yaooc_string_const_pointer)p1)->array_,((yaooc_string_const_pointer)p2)->array_) < 0;
}

void yaooc_string_to_stream(const_pointer p,pointer s)
{
	yaooc_string_const_pointer this=p;
	yaooc_ostream_pointer strm=s;
	M(strm,printf,"%s",this->array_);
}

/*
	Need to improve this for very long strings
*/
void yaooc_string_from_stream(pointer p,pointer s)
{
	yaooc_string_pointer this=p;
	yaooc_istream_pointer strm=s;
	char* temp=MALLOC(1024);
	M(strm,scanf,"%s",temp);
	M(this,set,temp);
	FREE(temp);
}

/* Constructors for yaooc_string */
void yaooc_string_ctor_ccs(pointer p,va_list args)
{
//  yaooc_string_pointer this=p;
  const char* str=va_arg(args,const char*);
  yaooc_string_default_ctor(p);
  if(str != NULL)
    yaooc_string_insertn(p,0,str,strlen(str));
}

void yaooc_string_ctor_ccs_n(pointer p,va_list args)
{
  yaooc_string_pointer this=p;
  const char* str=va_arg(args,const char*);
  size_t n=va_arg(args,size_t);
  yaooc_string_default_ctor(p);
  if(str != NULL)
    yaooc_string_insertn(this,0,str,n);
}

void yaooc_string_ctor_n_chr(pointer p,va_list args)
{
  yaooc_string_pointer this=p;
  size_t n=va_arg(args,size_t);
  char c=va_arg(args,int);
  yaooc_string_default_ctor(p);
  yaooc_string_insertn_chr(this,0,n,c);
}

/* Class table methods for yaooc_string */

const char* yaooc_string_isa(const_pointer p) { return "yaooc_string_t"; }

void yaooc_string_insert(pointer p,size_t ipos,const char* str)
{
  if(str)
    yaooc_string_insertn(p,ipos,str,strlen(str));
}

size_t yaooc_string_size_needed(const_pointer p,size_t n)
{
  return n+1;
}

void yaooc_string_insertn(pointer p,size_t ipos,const char* str,size_t n)
{
  yaooc_string_pointer this=p;
  if(str) {
    ipos = ipos > SIZE(p) ? SIZE(p) : ipos;
    size_t l = strlen(str);
    n=n>l ? l : n;

    yaooc_pod_array_insert_space(this,AT(p,ipos),n);
    memcpy(AT(p,ipos),str,n);
    *((yaooc_private_iterator)END(this))=0;
  }
}

void yaooc_string_insert_chr(pointer p,size_t pos,char ch)
{
  yaooc_string_insertn_chr(p,pos,1,ch);
}

void yaooc_string_insertn_chr(pointer p,size_t pos,size_t count,char ch)
{
  yaooc_private_iterator ret=yaooc_array_container_insert_space(p,AT(p,pos),count);
  memset(ret,ch,count);
  *((yaooc_private_iterator)END(p))=0;
}

void yaooc_string_set(pointer p,const char* str)
{
  if(str) {
    yaooc_string_setn(p,str,str ? strlen(str) : 0);
  }
}

void yaooc_string_setn(pointer p,const char* str,size_t n)
{
  yaooc_string_pointer this=p;
  yaooc_string_replacen(p,0,this->size_,str,n);
}

void yaooc_string_erase(pointer p,size_t pos)
{
  yaooc_string_erasen(p,pos,1);
}

void yaooc_string_erasen(pointer p,size_t pos,size_t n)
{
  yaooc_string_pointer this=p;
  if(pos < this->size_) {
    if(n == yaooc_string_npos  || this->size_ < (pos+n))
      n=this->size_-pos;
    yaooc_array_container_erase_space(this,AT(p,pos),n);
    *(END(this))=0;
  }
}

yaooc_string_iterator yaooc_string_erase_pos(pointer p,const_iterator pos)
{
  yaooc_string_iterator ret = yaooc_array_container_erase_space(p,pos,1);
  *(END(p))=0;
  return ret;
}

/*
yaooc_string_iterator yaooc_string_erase_range(pointer p,const_iterator first,const_iterator last)
{
  yaooc_string_iterator ret = yaooc_array_container_erase_space(p,INDEX(p,first),DISTANCE(p,first,last));
  *(END(p))=0;
  return ret;
}
*/
void yaooc_string_replace(pointer p,size_t pos,size_t n,const char* str)
{
  yaooc_string_replacen(p,pos,n,str,str ? strlen(str) : 0);
}

void yaooc_string_replacen(pointer p,size_t pos,size_t n,const char* str,size_t count)
{
  yaooc_string_pointer this=p;
  if(str) {
    size_t l;
    if(count > (l=strlen(str))) count=l;
  } else {
    count = 0;
  }
  if(pos > this->size_) pos=this->size_;
  if(n == yaooc_string_npos || this->size_ < (pos+n))
    n=this->size_-pos;
/*  if(n < count)
    yaooc_array_container_increase_capacity(p,count-n);*/
  yaooc_private_iterator dpos = yaooc_array_container_replace_space(this,AT(p,pos),AT(p,pos+n),count);
  memcpy(dpos,str,count);
  *((yaooc_private_iterator)END(this))=0;
}

void yaooc_string_clear(pointer p)
{
  yaooc_string_pointer this=p;
  this->size_=0;
  *this->array_=0;
}
/*
void yaooc_string_resize(pointer p,size_t n)
{
  char ch=' ';
  yaooc_array_container_resize_value(p,n,&ch);
  *(END(p))=0;
}

void yaooc_string_resize_value(pointer p,size_t n,char ch)
{
  yaooc_array_container_resize_value(p,n,&ch);
  *(END(p))=0;
}


void yaooc_string_shrink_to_fit(pointer p)
{
  yaooc_string_pointer this=p;
  if(this->capacity_ > INITIAL_CAPACITY  && this->size_ < this->capacity_) {
    this->capacity_=this->size_;
    this->array_=REALLOC(this->array_,this->capacity_*this->type_info_->type_size_+1);
  }
}
*/
void yaooc_string_append(pointer p,const char* str)
{
  if(str) {
    yaooc_string_insertn(p,SIZE(p),str,strlen(str));
  }
}

void yaooc_string_appendn(pointer p,const char* str,size_t count)
{
  if(str)
    yaooc_string_insertn(p,SIZE(p),str,count);
}
/*
void yaooc_string_reserve(pointer p,size_t n)
{
  if(CAPACITY(p) < n)
//    yaooc_array_container_increase_capacity_extra(p,n-SIZE(p),1);
}
*/
void yaooc_string_resize(pointer p,size_t n)
{
  yaooc_string_resize_value(p,n,' ');
}

void yaooc_string_resize_value(pointer p,size_t n,char ch)
{
  if(n < SIZE(p)) {
    ((yaooc_string_pointer)p)->size_=n;
  } else {
    yaooc_string_insertn_chr(p,SIZE(p),n-SIZE(p),ch);
  }
  *(END(p))=0;
}

yaooc_string_pointer yaooc_string_substr(const_pointer p,size_t ipos,size_t n)
{
	yaooc_string_const_pointer this=p;
  yaooc_string_pointer ret=new(yaooc_string);
  if(ipos < this->size_) {
    if(n>(this->size_-ipos))
      n=this->size_-ipos;
    yaooc_string_insertn(ret,0,this->array_+ipos,n);
  }
	return ret; //new_ctor(yaooc_string,yaooc_string_ctor_ccs_n,this->array_+pos,n);
}

yaooc_string_pointer yaooc_string_upcase(const_pointer p)
{
  yaooc_string_pointer ret=new_copy_static(yaooc_string,p);
  yaooc_string_upcase_(ret);
  return ret;
}

void yaooc_string_upcase_(pointer p)
{
	char* ptr=BEGIN(p);
	for(;*ptr != 0;ptr++) {
		if(islower(*ptr))
			*ptr=toupper(*ptr);
	}
}

yaooc_string_pointer yaooc_string_downcase(const_pointer p)
{
  yaooc_string_pointer ret=new_copy_static(yaooc_string,p);
  yaooc_string_downcase_(ret);
  return ret;
}

void yaooc_string_downcase_(pointer p)
{
	char* ptr=BEGIN(p);
	for(;*ptr != 0;ptr++) {
		if(isupper(*ptr))
			*ptr=tolower(*ptr);
	}
}

yaooc_string_pointer yaooc_string_ltrim(const_pointer p)
{
  yaooc_string_pointer ret=new_copy_static(yaooc_string,p);
  yaooc_string_ltrim_(ret);
  return ret;
}

static const char* whitespace=" \t\r\n";
void yaooc_string_ltrim_(pointer p)
{
  yaooc_string_pointer this=p;
  char* ptr=BEGIN(this);
  for(;*ptr !=0;ptr++) {// && strchr(whitespace,*ptr)) ptr++;
    const char* ws;
    for(ws=whitespace;*ws!=0;ws++)
      if(*ptr == *ws)
        break;
    if(*ws==0)
      break;
  }
  if(*ptr==0) { // Entire string was whitespace
    this->size_=0;
    this->array_[0]=0;
  } else {
    this->size_=END(this)-ptr;
    memmove(this->array_,ptr,this->size_+1);
  }
}

yaooc_string_pointer yaooc_string_rtrim(const_pointer p)
{
  yaooc_string_pointer ret=new_copy_static(yaooc_string,p);
  yaooc_string_rtrim_(ret);
  return ret;
}

void yaooc_string_rtrim_(pointer p)
{
  yaooc_string_pointer this=p;
  char* ptr=this->array_+this->size_-1;
  char* beg=this->array_;
  for(;ptr>=beg;ptr--) {// && strchr(whitespace,*ptr)) ptr++;
    const char* ws;
    for(ws=whitespace;*ws!=0;ws++)
      if(*ptr == *ws)
        break;
    if(*ws==0) // No whitespace
      break;
  }
  if(ptr<beg) { // Entire string was whitespace
    this->size_=0;
    this->array_[0]=0;
  } else {
    this->size_=ptr-beg+1;
    this->array_[this->size_]=0;
  }
}

yaooc_string_pointer yaooc_string_trim(const_pointer p)
{
  yaooc_string_pointer ret=new_copy_static(yaooc_string,p);
  yaooc_string_trim_(ret);
  return ret;
}

void yaooc_string_trim_(pointer p)
{
  yaooc_string_rtrim_(p);
  yaooc_string_ltrim_(p);
}

yaooc_string_pointer yaooc_string_sub(const_pointer p,const char* pat,const char* str)
{
	yaooc_string_pointer ret=new_copy_static(yaooc_string,p);
	yaooc_string_sub_(ret,pat,str);
	return ret;
}

bool yaooc_string_sub_re_(pointer p,const char* pat,int flags,const char *str)
{
	yaooc_string_pointer this=p;
	regex_t re;
	bool ret=false;
	if(regcomp(&re,pat,REG_EXTENDED|flags) == 0) {
		regmatch_t ov;
		if(regexec(&re,this->array_,1,&ov,0) == 0) {
			M(this,replace,ov.rm_so,ov.rm_eo-ov.rm_so,str);
			ret=true;
		}
		regfree(&re);
	}
	return ret;
}

void yaooc_string_sub_(pointer p,const char* pat,const char* str)
{
	yaooc_string_pointer this=p;
	if(pat) {
		char* re_str;
		int re_flags;
		yaooc_regex_flags_pat(pat,&re_str,&re_flags);
		if(re_str) {
			yaooc_string_sub_re_(p,re_str,re_flags,str);
		} else if (strcmp(pat," ")==0) {
			yaooc_string_sub_re_(p,"  +",REG_EXTENDED,str);
		} else {
			char* ptr=strstr(this->array_,pat);
			if(ptr)
				M(this,replace,ptr-this->array_,strlen(pat),str);
		}
	}
}

yaooc_string_pointer yaooc_string_gsub(const_pointer p,const char* pat,const char* str)
{
	yaooc_string_pointer ret=new_copy_static(yaooc_string,p);
	yaooc_string_gsub_(ret,pat,str);
	return ret;
}

static void yaooc_string_gsub_re_(pointer p,const char* pat,int flags,const char* str)
{
	yaooc_string_pointer this=p;
	regex_t re;
	if(regcomp(&re,pat,REG_EXTENDED|flags) == 0) {
		regmatch_t ov;
		size_t ofs=0;
		size_t l=strlen(str);
		while(ofs < this->size_ && regexec(&re,this->array_+ofs,1,&ov,0) == 0) {
			M(this,replace,ofs+ov.rm_so,ov.rm_eo-ov.rm_so,str);
			ofs+=ov.rm_so+l;
		}
		regfree(&re);
	}
}

void yaooc_string_gsub_(pointer p,const char* pat,const char* str)
{
	yaooc_string_pointer this=p;
	size_t l;
	size_t sl= str ? strlen(str) : 0;
	if(pat && (l=strlen(pat))>0) {
		char *re_str;
		int re_flags;
		yaooc_regex_flags_pat(pat,&re_str,&re_flags);
		if(re_str) {
			yaooc_string_gsub_re_(p,re_str,re_flags,str);
			FREE(re_str);
		} else {
			char* ptr;
			int ofs=0;
			while((ptr=strstr(this->array_+ofs,pat))!=NULL) {
				size_t pos=ptr-this->array_;
				M(this,replace,pos,l,str);
				ofs=pos+sl;
			}
		}
	}
}

bool yaooc_string_match(const_pointer p,const char* pat)
{
	yaooc_string_const_pointer this=p;
	bool ret=true;
	if(pat) {
		ret=false;
		char* re_str;
		int re_flags;
		yaooc_regex_flags_pat(pat,&re_str,&re_flags);
		if(re_str!=NULL) {
			pat=re_str;
		} else {
			re_flags=REG_EXTENDED|REG_NEWLINE;
		}
		regex_t re;
		if(regcomp(&re,pat,re_flags|REG_EXTENDED|REG_NOSUB)==0) {
			ret =regexec(&re,this->array_,0,NULL,0) == 0;
			regfree(&re);
		}
		if(re_str)
			FREE(re_str);
	}
	return ret;
}

size_t yaooc_string_findstr(pointer p,const char* str,size_t pos)
{
  yaooc_string_const_pointer this=p;
  size_t ret=yaooc_string_npos;
	if(this->size_ > 0 && pos < this->size_) {
		char* ptr=strstr(BEGIN(this)+pos,str);
		if(ptr)
			ret=ptr-BEGIN(this);
	}
	return ret;
}

size_t yaooc_string_rfindstr(pointer p,const char* str,size_t pos)
{
  yaooc_string_pointer this=p;
  size_t ret=yaooc_string_npos;
	if(this->size_ > 0 && str) {
		if(pos >= this->size_)
			pos=this->size_;
		const char* ptr = memrmem(BEGIN(this),pos,str,strlen(str));
		if(ptr)
			ret=ptr-BEGIN(this);
	}

  return ret;
}

size_t yaooc_string_findchr(pointer p,char ch,size_t pos)
{
  yaooc_string_pointer this=p;
  size_t ret=yaooc_string_npos;
	if(this->size_ > 0 && pos < this->size_) {
		const char* ptr=strchr(BEGIN(this)+pos,ch);
		if(ptr)
			ret=ptr-BEGIN(this);
	}
  return ret;
}

size_t yaooc_string_rfindchr(pointer p,char ch,size_t pos)
{
  yaooc_string_pointer this=p;
  size_t ret=yaooc_string_npos;
	if(this->size_ > 0) {
		if(pos >= this->size_)
			pos=this->size_;
		const char* ptr = memrchr(BEGIN(this),ch,pos);
		if(ptr)
			ret=ptr-BEGIN(this);
	}
  return ret;
}

static void yaooc_regex_flags_pat(const char* pat,char** re_pat,int* re_flags)
{
	*re_flags=REG_EXTENDED|REG_NEWLINE;
	if(pat && *pat == '/') {
		const char* end=pat+strlen(pat)-1;
		for(;end > pat;end--) {
			if(*end == 'm') {
				*re_flags &= ~REG_NEWLINE;
			} else if(*end == 'i') {
				*re_flags |= REG_ICASE;
			} else if(*end == '/') {
				size_t n=end-pat;
				*re_pat=MALLOC(n);
				strncpy(*re_pat,pat+1,n-1);
				(*re_pat)[n-1]=0;
				return;
			} else {
				break; /* Not a regular expression. */
			}
		}
	}
	*re_pat=NULL;
}
static yaooc_string_vector_pointer yaooc_string_split_re(const_pointer,const char*,int,size_t);
yaooc_string_vector_pointer yaooc_string_split(const_pointer p,const char* str,size_t max)
{
  yaooc_string_const_pointer this=p;
  yaooc_string_vector_t* ret=NULL; //new(yaooc_string_vector);
  char* re_str;
	int re_flags;
	yaooc_regex_flags_pat(str,&re_str,&re_flags);
	if(re_str) {
    //delete(ret);
    ret = yaooc_string_split_re(p,re_str,re_flags,max);
		FREE(re_str);
	} else {
		ret=new(yaooc_string_vector);
    char *beg,*end;
		size_t l=strlen(str);
    yaooc_string_t* temp=new(yaooc_string);
    if(strcmp(str," ")==0) {
      beg=this->array_;
      do {
        beg+=strspn(beg,whitespace);
        size_t ofs=strcspn(beg,whitespace);
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
  /*
    Remove null items at end
  */
  while(M(ret,size)>0 && M(M(ret,back),size)==0)
    M(ret,pop_back);
  return ret;
}

static yaooc_string_vector_pointer yaooc_string_split_re(const_pointer p,const char* re_str,int flags,size_t max)
{
  yaooc_string_const_pointer this=p;
  yaooc_string_vector_pointer ret=new(yaooc_string_vector);
  regex_t re;
  regmatch_t rm;
  if(regcomp(&re,re_str,REG_EXTENDED|flags)==0) {
    yaooc_string_t* temp=new(yaooc_string);
    char* beg=this->array_;
    while(regexec(&re,beg,1,&rm,0)==0) {
      M(temp,setn,beg,rm.rm_so);
      beg+=rm.rm_eo;
      M(ret,push_back,temp);
    }
    if(*beg != 0) {
      M(temp,set,beg);
      M(ret,push_back,temp);
    }
    regfree(&re);
    delete(temp);
  }
  return ret;
}

/* Class table for yaooc_string */
yaooc_string_class_table_t yaooc_string_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_pod_array_class_table,
  .isa = (const char* (*) (const_pointer p)) yaooc_string_isa,
  .is_descendant = (bool (*) (const_pointer p,const char*)) yaooc_string_is_descendant,
  .swap = (void (*) (pointer p,pointer)) yaooc_pod_array_swap,
  .increase_capacity = (bool (*) (pointer,size_t)) yaooc_pod_array_increase_capacity,
  .size_needed = (size_t (*)(const_pointer,size_t)) yaooc_string_size_needed,
  .size = (size_t (*) (const_pointer p)) yaooc_pod_array_size,
  .capacity = (size_t (*) (const_pointer p)) yaooc_pod_array_capacity,
  .empty = (bool (*) (const_pointer p)) yaooc_pod_array_empty,
  .begin = (iterator (*) (const_pointer p)) yaooc_pod_array_begin,
  .end = (iterator (*) (const_pointer p)) yaooc_pod_array_end,
  .at = (yaooc_string_iterator (*) (const_pointer p,size_t)) yaooc_pod_array_at,
  .reserve = (void (*) (pointer p,size_t)) yaooc_pod_array_reserve,
  .insert = (void (*) (pointer p,size_t,const char*)) yaooc_string_insert,
  .insertn = (void (*) (pointer p,size_t,const char*,size_t)) yaooc_string_insertn,
  .insert_chr = (void (*) (pointer p,size_t,char)) yaooc_string_insert_chr,
  .insertn_chr = (void (*) (pointer p,size_t,size_t,char)) yaooc_string_insertn_chr,
  .set = (void (*) (pointer p,const char*)) yaooc_string_set,
  .setn = (void (*) (pointer p,const char*,size_t)) yaooc_string_setn,
  .erase = (void (*) (pointer p,size_t)) yaooc_string_erase,
  .erasen = (void (*) (pointer p,size_t,size_t)) yaooc_string_erasen,
  .replace = (void (*) (pointer p,size_t,size_t,const char*)) yaooc_string_replace,
  .replacen = (void (*) (pointer p,size_t,size_t,const char*,size_t)) yaooc_string_replacen,
  .resize = (void (*) (pointer p,size_t)) yaooc_string_resize,
  .resize_value = (void (*) (pointer p,size_t,char)) yaooc_string_resize_value,
  .shrink_to_fit = (void (*) (pointer p)) yaooc_pod_array_shrink_to_fit,
  .append = (void (*) (pointer p,const char*)) yaooc_string_append,
  .appendn = (void (*) (pointer p,const char*,size_t)) yaooc_string_appendn,
  .substr = (yaooc_string_pointer (*) (const_pointer p,size_t,size_t)) yaooc_string_substr,
  .upcase = (yaooc_string_pointer (*) (const_pointer p)) yaooc_string_upcase,
  .upcase_ = (void (*) (pointer p)) yaooc_string_upcase_,
  .downcase = (yaooc_string_pointer (*) (const_pointer p)) yaooc_string_downcase,
  .downcase_ = (void (*) (pointer p)) yaooc_string_downcase_,
  .ltrim = (yaooc_string_pointer (*) (const_pointer p)) yaooc_string_ltrim,
  .ltrim_ = (void (*) (pointer p)) yaooc_string_ltrim_,
  .rtrim = (yaooc_string_pointer (*) (const_pointer p)) yaooc_string_rtrim,
  .rtrim_ = (void (*) (pointer p)) yaooc_string_rtrim_,
  .trim = (yaooc_string_pointer (*) (const_pointer p)) yaooc_string_trim,
  .trim_ = (void (*) (pointer p)) yaooc_string_trim_,
	.sub = (yaooc_string_pointer (*) (const_pointer,const char*,const char*)) yaooc_string_sub,
	.sub_ = (void (*) (pointer,const char*,const char*)) yaooc_string_sub_,
	.gsub = (yaooc_string_pointer (*) (const_pointer,const char*,const char*)) yaooc_string_gsub,
	.gsub_ = (void (*) (pointer,const char*,const char*)) yaooc_string_gsub_,
	.match = (bool (*) (const_pointer,const char*)) yaooc_string_match,
  .clear = (void (*) (pointer p)) yaooc_string_clear,
  .findstr = (size_t (*) (pointer p,const char*,size_t)) yaooc_string_findstr,
  .rfindstr = (size_t (*) (pointer p,const char*,size_t)) yaooc_string_rfindstr,
  .findchr = (size_t (*) (pointer p,char,size_t)) yaooc_string_findchr,
  .rfindchr = (size_t (*) (pointer p,char,size_t)) yaooc_string_rfindchr,
  .split = (yaooc_string_vector_pointer (*) (const_pointer p,const char*,size_t)) yaooc_string_split,
//  .split_re = (yaooc_string_vector_pointer (*) (const_pointer p,const char*,size_t)) yaooc_string_split_re,
  .c_str = (const char* (*) (const_pointer p)) yaooc_pod_array_begin,
};


DEFINE_TYPE_INFO(yaooc_string,Y,N,Y,Y,Y,Y,Y,Y,yaooc_array_container)

/* End */

VECTOR_IMPLEMENTATION(yaooc_string,yaooc_string_vector)
