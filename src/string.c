#include <yaooc/string.h>
#include <yaooc/stream.h>
#include <string.h>
#include <ctype.h>

const char* yaooc_whitespace=" \t\r\n";

static const void *yaooc_string_memrmem(const void *ptr, size_t size, const void *pat, size_t patsize)
{
	const char *p;

	if(ptr != NULL && pat != NULL) {

		
		if (size < patsize)
			return NULL;
		if (patsize == 0)
			return ptr;

		for (p = (const char*)ptr + size - patsize ; size >= patsize; --p, --size)
			if(*p == *(const char*)pat)
				if (memcmp(p, pat, patsize) == 0) 
					return p;
	}
	return NULL;
}

#ifndef HAVE_MEMRCHR
static void* yaooc_string_memrchr(const void* buf,int c,size_t spos)
{
	const char* ptr = (const char*)buf+spos-1;
	while(ptr >= (const char*)buf) {
		if(*ptr == c)
			return (void*)ptr;
		ptr--;
	}
	return NULL;
}
#else
#define yaooc_string_memrchr memrchr
#endif


void yaooc_string_default_ctor(pointer __pthis__)
{
yaooc_string_pointer this=__pthis__;(void)this;
call_constructor(this,yaooc_array_container_ctor_ti,char_ti);



      M(this,increase_capacity,1);
      *END(this)=0;
    
}
void yaooc_string_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaooc_string_pointer this=__pthis__;(void)this;
yaooc_string_const_pointer src=__psrc__;(void)src;

call_default_ctor_static(this,yaooc_string);


      yaooc_string_assign(this,src);
    
}
void yaooc_string_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_string_pointer this=__pthis__;(void)this;
yaooc_string_const_pointer src=__psrc__;(void)src;


      if(this->size_ > 0) {
        this->size_=0;
        *(this->array_)=0;
      }
      M(this,insertn,0,BEGIN(src),SIZE(src));
    
}
int yaooc_string_rich_compare(const_pointer __plhs__,const_pointer __prhs__)
{
yaooc_string_const_pointer lhs=__plhs__;(void)lhs;
yaooc_string_const_pointer rhs=__prhs__;(void)rhs;


      
      return strcmp(lhs->array_,rhs->array_);
    
}
void yaooc_string_to_stream(const_pointer __pthis__,ostream_pointer __pstrm__)
{
yaooc_string_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__pstrm__;(void)ostrm;


      M(ostrm,printf,"%s",this->array_);
    
}
void yaooc_string_from_stream(pointer __pthis__,ostream_pointer __pstrm__)
{
yaooc_string_pointer this=__pthis__;(void)this;
yaooc_istream_pointer istrm=__pstrm__;(void)istrm;


      M(this,clear);
      char temp[256];
      while(!M(istrm,eof)) {
        M(istrm,scanf,"%255s",temp);
        M(this,append,temp);
        if(isspace(M(istrm,peek)))
          break;
      }
    
}
void yaooc_string_ctor_ccs(pointer __pthis,va_list __con_args__){
yaooc_string_pointer this=__pthis;(void)this;
const char* str = va_arg(__con_args__,const char*);

call_default_ctor_static(this,yaooc_string);


      if(str != NULL)
        yaooc_string_insertn(this,0,str,strlen(str));
    
}
void yaooc_string_ctor_ccs_n(pointer __pthis,va_list __con_args__){
yaooc_string_pointer this=__pthis;(void)this;
const char* str = va_arg(__con_args__,const char*);
size_t n = va_arg(__con_args__,size_t);

call_default_ctor_static(this,yaooc_string);


      if(str != NULL)
        yaooc_string_insertn(this,0,str,n);
    
}
void yaooc_string_ctor_chr_n(pointer __pthis,va_list __con_args__){
yaooc_string_pointer this=__pthis;(void)this;
int c = va_arg(__con_args__,int);
size_t n = va_arg(__con_args__,size_t);

call_default_ctor_static(this,yaooc_string);


      yaooc_string_insertn_chr(this,0,n,c);
    
}
 const size_t yaooc_string_npos=-1;
size_t yaooc_string_size_needed(const_pointer __pthis__,size_t n)
{
yaooc_string_const_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->size_needed(this,n)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      return n+1;
    
#undef PM
#undef super
}
char* yaooc_string_at(pointer __pthis__,size_t pos)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->at(this,pos)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      return yaooc_array_container_at(this,pos);
    
#undef PM
#undef super
}
void yaooc_string_insert(pointer __pthis__,size_t ipos,const char* str)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->insert(this,ipos,str)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      if(str)
        yaooc_string_insertn(this,ipos,str,strlen(str));
    
#undef PM
#undef super
}
void yaooc_string_insertn(pointer __pthis__,size_t ipos,const char* str,size_t n)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->insertn(this,ipos,str,n)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      if(str) {
        ipos = ipos > SIZE(this) ? SIZE(this) : ipos;
        size_t l = strnlen(str,n);
        n=n>l ? l : n;

        yaooc_array_container_insert_space(this,AT(this,ipos),n);
        memcpy(AT(this,ipos),str,n);
        *((yaooc_private_iterator)END(this))=0;
      }
    
#undef PM
#undef super
}
void yaooc_string_insert_chr(pointer __pthis__,size_t pos,char ch)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->insert_chr(this,pos,ch)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      M(this,insertn_chr,pos,1,ch);
    
#undef PM
#undef super
}
void yaooc_string_insertn_chr(pointer __pthis__,size_t pos,size_t count,char ch)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->insertn_chr(this,pos,count,ch)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_private_iterator ret=yaooc_array_container_insert_space(this,AT(this,pos),count);
      memset(ret,ch,count);
      *((yaooc_private_iterator)END(this))=0;
    
#undef PM
#undef super
}
void yaooc_string_set(pointer __pthis__,const char* str)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->set(this,str)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      if(str) {
        yaooc_string_setn(this,str,strlen(str));
      } else {
        this->size_=0;
        *END(this)=0;
      }
    
#undef PM
#undef super
}
void yaooc_string_setn(pointer __pthis__,const char* str,size_t count)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->setn(this,str,count)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      M(this,replacen,0,this->size_,str,count);
    
#undef PM
#undef super
}
void yaooc_string_erase(pointer __pthis__,size_t pos)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->erase(this,pos)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      M(this,erasen,pos,1);
    
#undef PM
#undef super
}
void yaooc_string_erasen(pointer __pthis__,size_t pos,size_t n)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->erasen(this,pos,n)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      if(pos < this->size_) {
        if(n == yaooc_string_npos  || this->size_ < (pos+n))
          n=this->size_-pos;
        yaooc_array_container_erase_space(this,AT(this,pos),n);
        *(END(this))=0;
      }
    
#undef PM
#undef super
}
void yaooc_string_replace(pointer __pthis__,size_t pos,size_t n,const char* str)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->replace(this,pos,n,str)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      M(this,replacen,pos,n,str,str ? strlen(str) : 0);
    
#undef PM
#undef super
}
void yaooc_string_replacen(pointer __pthis__,size_t pos,size_t n,const char* str,size_t count)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->replacen(this,pos,n,str,count)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      if(str) {
        size_t l;
        if(count > (l=strnlen(str,count))) count=l;
      } else {
        count = 0;
      }
      if(pos > this->size_) pos=this->size_;
      if(n == yaooc_string_npos || this->size_ < (pos+n))
        n=this->size_-pos;
      yaooc_private_iterator dpos = yaooc_array_container_replace_space(this,AT(this,pos),AT(this,pos+n),count);
      memcpy(dpos,str,count);
      *((yaooc_private_iterator)END(this))=0;
    
#undef PM
#undef super
}
void yaooc_string_resize(pointer __pthis__,size_t n)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->resize(this,n)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      M(this,resize_value,n,' ');
    
#undef PM
#undef super
}
void yaooc_string_resize_value(pointer __pthis__,size_t n,char ch)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->resize_value(this,n,ch)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      if(n < SIZE(this)) {
        this->size_=n;
      } else {
        yaooc_string_insertn_chr(this,SIZE(this),n-SIZE(this),ch);
      }
      *(END(this))=0;
    
#undef PM
#undef super
}
void yaooc_string_append(pointer __pthis__,const char* str)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->append(this,str)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      if(str) {
        M(this,insertn,SIZE(this),str,strlen(str));
      }
    
#undef PM
#undef super
}
void yaooc_string_appendn(pointer __pthis__,const char* str,size_t count)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->appendn(this,str,count)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      if(str)
        yaooc_string_insertn(this,SIZE(this),str,count);
    
#undef PM
#undef super
}
yaooc_string_pointer yaooc_string_substr(const_pointer __pthis__,size_t ipos,size_t n)
{
yaooc_string_const_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->substr(this,ipos,n)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_string_pointer ret=new(yaooc_string);
      if(ipos < this->size_) {
        if(n>(this->size_-ipos))
          n=this->size_-ipos;
        yaooc_string_insertn(ret,0,this->array_+ipos,n);
      }
      return ret; 
    
#undef PM
#undef super
}
yaooc_string_pointer yaooc_string_upcase(const_pointer __pthis__)
{
yaooc_string_const_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->upcase(this)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_string_pointer ret=new_copy_static(yaooc_string,this);
      M(ret,upcase_);
      return ret;
    
#undef PM
#undef super
}
void yaooc_string_upcase_(pointer __pthis__)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->upcase_(this)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      char* ptr=BEGIN(this);
      for(;*ptr != 0;ptr++) {
        if(islower(*ptr))
          *ptr=toupper(*ptr);
      }
    
#undef PM
#undef super
}
yaooc_string_pointer yaooc_string_downcase(const_pointer __pthis__)
{
yaooc_string_const_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->downcase(this)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_string_pointer ret=new_copy_static(yaooc_string,this);
      M(ret,downcase_);
      return ret;
    
#undef PM
#undef super
}
void yaooc_string_downcase_(pointer __pthis__)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->downcase_(this)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      char* ptr=BEGIN(this);
      for(;*ptr != 0;ptr++) {
        if(isupper(*ptr))
          *ptr=tolower(*ptr);
      }
    
#undef PM
#undef super
}
yaooc_string_pointer yaooc_string_ltrim(const_pointer __pthis__)
{
yaooc_string_const_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->ltrim(this)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_string_pointer ret=new_copy_static(yaooc_string,this);
      M(ret,ltrim_);
      return ret;
    
#undef PM
#undef super
}
void yaooc_string_ltrim_(pointer __pthis__)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->ltrim_(this)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      char* ptr=BEGIN(this);
      for(;*ptr !=0;ptr++) {
        const char* ws;
        for(ws=yaooc_whitespace;*ws!=0;ws++)
          if(*ptr == *ws)
            break;
        if(*ws==0)
          break;
      }
      if(*ptr==0) { 
        this->size_=0;
        this->array_[0]=0;
      } else {
        this->size_=END(this)-ptr;
        memmove(this->array_,ptr,this->size_+1);
      }
    
#undef PM
#undef super
}
yaooc_string_pointer yaooc_string_rtrim(const_pointer __pthis__)
{
yaooc_string_const_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->rtrim(this)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_string_pointer ret=new_copy_static(yaooc_string,this);
      M(ret,rtrim_);
      return ret;
    
#undef PM
#undef super
}
void yaooc_string_rtrim_(pointer __pthis__)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->rtrim_(this)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      char* ptr=this->array_+this->size_-1;
      char* beg=this->array_;
      for(;ptr>=beg;ptr--) {
        const char* ws;
        for(ws=yaooc_whitespace;*ws!=0;ws++)
          if(*ptr == *ws)
            break;
        if(*ws==0) 
          break;
      }
      if(ptr<beg) { 
        this->size_=0;
        this->array_[0]=0;
      } else {
        this->size_=ptr-beg+1;
        this->array_[this->size_]=0;
      }
    
#undef PM
#undef super
}
yaooc_string_pointer yaooc_string_trim(const_pointer __pthis__)
{
yaooc_string_const_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->trim(this)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_string_pointer ret=new_copy_static(yaooc_string,this);
      M(ret,trim_);
      return ret;
    
#undef PM
#undef super
}
void yaooc_string_trim_(pointer __pthis__)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->trim_(this)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      M(this,rtrim_);
      M(this,ltrim_);
    
#undef PM
#undef super
}
yaooc_string_pointer yaooc_string_sub(const_pointer __pthis__,const char* pat,const char* str)
{
yaooc_string_const_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->sub(this,pat,str)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_string_pointer ret=new_copy_static(yaooc_string,this);
      M(ret,sub_,pat,str);
      return ret;
    
#undef PM
#undef super
}
yaooc_string_pointer yaooc_string_sub_re(const_pointer __pthis__,yaooc_regex_const_pointer re,const char* repl_str)
{
yaooc_string_const_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->sub_re(this,re,repl_str)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_string_pointer ret=new_copy_static(yaooc_string,this);
      M(ret,sub_re_,re,repl_str);
      return ret;
    
#undef PM
#undef super
}
yaooc_string_pointer yaooc_string_gsub(const_pointer __pthis__,const char* pat,const char* repl_str)
{
yaooc_string_const_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->gsub(this,pat,repl_str)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_string_pointer ret=new_copy_static(yaooc_string,this);
      M(ret,gsub_,pat,repl_str);
      return ret;
    
#undef PM
#undef super
}
yaooc_string_pointer yaooc_string_gsub_re(const_pointer __pthis__,yaooc_regex_const_pointer re,const char* repl_str)
{
yaooc_string_const_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->gsub_re(this,re,repl_str)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_string_pointer ret=new_copy_static(yaooc_string,this);
      M(ret,gsub_re_,re,repl_str);
      return ret;
    
#undef PM
#undef super
}
bool yaooc_string_starts_with(const_pointer __pthis__,const char* str)
{
yaooc_string_const_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->starts_with(this,str)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      bool ret=false;
      if(str) {
        ret = strncmp(BEGIN(this),str,strlen(str))==0;
      }
      return ret;
    
#undef PM
#undef super
}
bool yaooc_string_ends_with(const_pointer __pthis__,const char* str)
{
yaooc_string_const_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->ends_with(this,str)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      bool ret=false;
      if(str && this->size_ > 0) {
        int l = strlen(str);
        if(l > 0 && l<=this->size_) {
          char* ptr=END(this)-l;
          ret=strcmp(ptr,str)==0;
        }
      }
      return ret;
    
#undef PM
#undef super
}
void yaooc_string_clear(pointer __pthis__)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->clear(this)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      this->size_=0;
      *this->array_=0;
    
#undef PM
#undef super
}
size_t yaooc_string_findstr(pointer __pthis__,const char* str,size_t pos)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->findstr(this,str,pos)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      size_t ret=yaooc_string_npos;
      if(this->size_ > 0 && pos < this->size_) {
        char* ptr=strstr(BEGIN(this)+pos,str);
        if(ptr)
          ret=ptr-BEGIN(this);
      }
      return ret;
    
#undef PM
#undef super
}
size_t yaooc_string_rfindstr(pointer __pthis__,const char* str,size_t pos)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->rfindstr(this,str,pos)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      size_t ret=yaooc_string_npos;
      if(this->size_ > 0 && str) {
        if(pos >= this->size_)
          pos=this->size_;
        const char* ptr = yaooc_string_memrmem(BEGIN(this),pos,str,strlen(str));
        if(ptr)
          ret=ptr-BEGIN(this);
      }
      return ret;
    
#undef PM
#undef super
}
size_t yaooc_string_findchr(pointer __pthis__,char ch,size_t pos)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->findchr(this,ch,pos)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      size_t ret=yaooc_string_npos;
      if(this->size_ > 0 && pos < this->size_) {
        const char* ptr=strchr(BEGIN(this)+pos,ch);
        if(ptr)
          ret=ptr-BEGIN(this);
      }
      return ret;
    
#undef PM
#undef super
}
size_t yaooc_string_rfindchr(pointer __pthis__,char ch,size_t pos)
{
yaooc_string_pointer this=__pthis__;(void)this;
#define super() yaooc_string_parent_class_table->rfindchr(this,ch,pos)
#define PM(method,...) CTM((*yaooc_string_parent_class_table),this,method,## __VA_ARGS__)


      size_t ret=yaooc_string_npos;
      if(this->size_ > 0) {
        if(pos >= this->size_)
          pos=this->size_;
        const char* ptr = yaooc_string_memrchr(BEGIN(this),ch,pos);
        if(ptr)
          ret=ptr-BEGIN(this);
      }
      return ret;
    
#undef PM
#undef super
}
yaooc_string_class_table_t yaooc_string_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_array_container_class_table,
.type_name_ = (const char*)"yaooc_string_t",
.swap = (void(*)(pointer,pointer)) yaooc_string_swap,
.increase_capacity = (bool(*)(pointer,size_t)) yaooc_string_increase_capacity,
.size_needed = (size_t(*)(const_pointer,size_t)) yaooc_string_size_needed,
.size = (size_t(*)(const_pointer)) yaooc_string_size,
.capacity = (size_t(*)(const_pointer)) yaooc_string_capacity,
.empty = (bool(*)(const_pointer)) yaooc_string_empty,
.begin = (iterator(*)(pointer)) yaooc_string_begin,
.end = (iterator(*)(pointer)) yaooc_string_end,
.cbegin = (const_iterator(*)(const_pointer)) yaooc_string_cbegin,
.cend = (const_iterator(*)(const_pointer)) yaooc_string_cend,
.at = (char*(*)(pointer,size_t)) yaooc_string_at,
.reserve = (void(*)(pointer,size_t)) yaooc_string_reserve,
.insert = (void(*)(pointer,size_t,const char*)) yaooc_string_insert,
.insertn = (void(*)(pointer,size_t,const char*,size_t)) yaooc_string_insertn,
.insert_chr = (void(*)(pointer,size_t,char)) yaooc_string_insert_chr,
.insertn_chr = (void(*)(pointer,size_t,size_t,char)) yaooc_string_insertn_chr,
.set = (void(*)(pointer,const char*)) yaooc_string_set,
.setn = (void(*)(pointer,const char*,size_t)) yaooc_string_setn,
.erase = (void(*)(pointer,size_t)) yaooc_string_erase,
.erasen = (void(*)(pointer,size_t,size_t)) yaooc_string_erasen,
.replace = (void(*)(pointer,size_t,size_t,const char*)) yaooc_string_replace,
.replacen = (void(*)(pointer,size_t,size_t,const char*,size_t)) yaooc_string_replacen,
.resize = (void(*)(pointer,size_t)) yaooc_string_resize,
.resize_value = (void(*)(pointer,size_t,char)) yaooc_string_resize_value,
.shrink_to_fit = (void(*)(pointer)) yaooc_string_shrink_to_fit,
.append = (void(*)(pointer,const char*)) yaooc_string_append,
.appendn = (void(*)(pointer,const char*,size_t)) yaooc_string_appendn,
.substr = (yaooc_string_pointer(*)(const_pointer,size_t,size_t)) yaooc_string_substr,
.upcase = (yaooc_string_pointer(*)(const_pointer)) yaooc_string_upcase,
.upcase_ = (void(*)(pointer)) yaooc_string_upcase_,
.downcase = (yaooc_string_pointer(*)(const_pointer)) yaooc_string_downcase,
.downcase_ = (void(*)(pointer)) yaooc_string_downcase_,
.ltrim = (yaooc_string_pointer(*)(const_pointer)) yaooc_string_ltrim,
.ltrim_ = (void(*)(pointer)) yaooc_string_ltrim_,
.rtrim = (yaooc_string_pointer(*)(const_pointer)) yaooc_string_rtrim,
.rtrim_ = (void(*)(pointer)) yaooc_string_rtrim_,
.trim = (yaooc_string_pointer(*)(const_pointer)) yaooc_string_trim,
.trim_ = (void(*)(pointer)) yaooc_string_trim_,
.sub = (yaooc_string_pointer(*)(const_pointer,const char*,const char*)) yaooc_string_sub,
.sub_ = (void(*)(pointer,const char*,const char*)) yaooc_string_sub_,
.sub_re = (yaooc_string_pointer(*)(const_pointer,yaooc_regex_const_pointer,const char*)) yaooc_string_sub_re,
.sub_re_ = (void(*)(pointer,yaooc_regex_const_pointer,const char*)) yaooc_string_sub_re_,
.gsub = (yaooc_string_pointer(*)(const_pointer,const char*,const char*)) yaooc_string_gsub,
.gsub_ = (void(*)(pointer,const char*,const char*)) yaooc_string_gsub_,
.gsub_re = (yaooc_string_pointer(*)(const_pointer,yaooc_regex_const_pointer,const char*)) yaooc_string_gsub_re,
.gsub_re_ = (void(*)(pointer,yaooc_regex_const_pointer,const char*)) yaooc_string_gsub_re_,
.match = (bool(*)(const_pointer,const char*)) yaooc_string_match,
.match_re = (bool(*)(const_pointer,yaooc_regex_const_pointer)) yaooc_string_match_re,
.starts_with = (bool(*)(const_pointer,const char*)) yaooc_string_starts_with,
.ends_with = (bool(*)(const_pointer,const char*)) yaooc_string_ends_with,
.clear = (void(*)(pointer)) yaooc_string_clear,
.findstr = (size_t(*)(pointer,const char*,size_t)) yaooc_string_findstr,
.rfindstr = (size_t(*)(pointer,const char*,size_t)) yaooc_string_rfindstr,
.findchr = (size_t(*)(pointer,char,size_t)) yaooc_string_findchr,
.rfindchr = (size_t(*)(pointer,char,size_t)) yaooc_string_rfindchr,
.split = (yaooc_string_vector_pointer(*)(const_pointer,const char*,size_t)) yaooc_string_split,
.split_re = (yaooc_string_vector_pointer(*)(const_pointer,yaooc_regex_const_pointer,size_t)) yaooc_string_split_re,
.c_str = (const char*(*)(const_pointer)) yaooc_string_c_str,
};
const type_info_t __yaooc_string_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_string_t),
.rich_compare_=yaooc_string_rich_compare,
.to_stream_=yaooc_string_to_stream,
.from_stream_=yaooc_string_from_stream,
.default_ctor_=yaooc_string_default_ctor,
.dtor_=NULL,
.copy_ctor_=yaooc_string_copy_ctor,
.assign_=yaooc_string_assign,
.class_table_=(const class_table_t*) &yaooc_string_class_table,
.parent_=&__yaooc_array_container_ti
};
const type_info_t* const yaooc_string_ti=&__yaooc_string_ti;
VECTOR_IMPLEMENTATION(yaooc_string,yaooc_string_vector);

