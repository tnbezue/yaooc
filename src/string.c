#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <yaooc/string.h>
#ifdef __YAOOC_BOUNDS_CHECKING__
#include <assert.h>
#endif
yaooc_size_type yaooc_string_size_needed(const_pointer,yaooc_size_type);

static container_private_class_methods_t string_private_class_methods=
{
  yaooc_string_size_needed,
  yaooc_array_container_increase_capacity
};

/*
	Default contructor.
*/
void yaooc_string_default_ctor(pointer p)
{
  yaooc_string_pointer this=p;
	call_constructor(p,yaooc_array_container_ctor,char_ti);
  this->private_class_table_=&string_private_class_methods;
  CPM(this,increase_capacity,1);
	*END(p)=0;
}

void yaooc_string_assign(pointer d,const_pointer s)
{
  yaooc_string_const_pointer src=s;
	yaooc_string_clear(d);
  if(src)
    yaooc_string_insertn(d,0,src->array_,src->size_);
}

void yaooc_string_copy_ctor(pointer d,const_pointer s)
{
	yaooc_string_default_ctor(d);
  yaooc_string_assign(d,s);
}

/*
	Compare strings
*/
bool yaooc_string_less_than_compare(const_pointer v1,const const_pointer v2)
{
  /*
    String will never be NULL
  */
	return strcmp(CBEGIN(v1),CBEGIN(v2)) < 0;
}

/*
  ***** Constructors *******
*/
/*
	Construct string from const char *
*/
void yaooc_string_ctor_ccs(pointer p,va_list args)
{
	yaooc_string_default_ctor(p);
  const char* str=va_arg(args,const char *);
  if(str)
    yaooc_string_insertn(p,0,str,strlen(str));
}

/*
	Construct string from first n characters of const char *
*/
void yaooc_string_ctor_ccs_n(pointer p,va_list args)
{
	yaooc_string_default_ctor(p);
	const char* str = va_arg(args,const char *);
	yaooc_size_type n = va_arg(args,yaooc_size_type);
	yaooc_string_insertn(p,0,str,n);
}

/*
	Construct string by duplicating character n times
*/
void yaooc_string_ctor_chr_n(pointer p,va_list args)
{
	yaooc_string_default_ctor(p);
	char c = va_arg(args,int);
	yaooc_size_type n = va_arg(args,yaooc_size_type);
  yaooc_string_insertn_chr(p,0,c,n);
}

/*
  Methods overridden in base container
*/
void yaooc_string_clear(pointer p)
{
  yaooc_string_pointer this=p;
  this->size_=0;
  this->array_[0]=0;
}

yaooc_size_type yaooc_string_size_needed(const_pointer p,yaooc_size_type n)
{
  return n+1;
}

/*
  **** METHODS *****
*/
void yaooc_string_set(pointer p,const char* str)
{
  yaooc_string_setn(p,str,str?strlen(str):0);
}

void yaooc_string_setn(pointer p,const char* str,yaooc_size_type n)
{
  yaooc_string_clear(p);
  yaooc_string_insertn(p,0,str,n);
}

void yaooc_string_insert_chr(pointer p,yaooc_size_type ipos,char ch)
{
	yaooc_string_pointer this=p;
  yaooc_string_insertn(this,ipos,&ch,1);
}

void yaooc_string_insertn_chr(pointer p,yaooc_size_type ipos,char ch,yaooc_size_type n)
{
  if(n>0) {
    yaooc_string_pointer this=p;
#ifdef __YAOOC_BOUNDS_CHECKING__
    assert(ipos <= M(this,size) && "string insertn_chr ipos out of range");
#endif
    char * temp = (char*)MALLOC(n+1);
    memset(temp,ch,n);
    yaooc_string_insertn(this,ipos,temp,n);
    FREE(temp);
  }
}
//const yaooc_size_type yaooc_string_npos=(yaooc_size_type)-1;
/*
	Append first n characters of const char*
*/
void yaooc_string_appendn(pointer p,const char* s,yaooc_size_type n)
{
	yaooc_string_pointer this=p;
	return yaooc_string_insertn(this,this->size_,s,n);
}

/*
	Append const char*
*/
void yaooc_string_append(pointer p,const char* s)
{
	yaooc_string_pointer this=p;
	return yaooc_string_insertn(this,this->size_,s,s ? strlen(s) : 0);
}

void yaooc_string_insert(pointer p,yaooc_size_type spos,const char* s)
{
	yaooc_string_pointer this=p;
	return yaooc_string_insertn(this,spos,s,s ? strlen(s) : 0);
}

void yaooc_string_insertn(pointer p,yaooc_size_type spos,const char* s,yaooc_size_type n)
{
	yaooc_string_pointer this=p;
#ifdef __YAOOC_BOUNDS_CHECKING__
	assert(spos <= this->size_ && "spos out of range in yaooc_string_insertn");
#endif
  if(s) {
    char* ptr=memchr(s,0,n); /* can't use strlen */
    if(ptr)
      n=ptr-s;
    if(n>0) {
      CPM(this,increase_capacity,n);
      yaooc_size_type nb_move=this->size_-spos;
      char* insert_pos=AT(this,spos);
      memmove(AT(this,spos+n),insert_pos,nb_move);
      memcpy(insert_pos,s,n);
      this->size_+=n;
      *END(this)=0;
    }
  }
}

/*
	Erase n characters starting at spos
*/
void yaooc_string_erase(pointer p,yaooc_size_type spos, yaooc_size_type n)
{
	yaooc_string_pointer this=p;
#ifdef __YAOOC_BOUNDS_CHECKING__
	assert(spos <= this->size_ && "spos out of range in yaooc_string_erase");
#endif
  if(n > (this->size_ - spos))
		n=this->size_ - spos;
  yaooc_size_type nb = this->size_ - (spos+n);
  memmove(AT(this,spos),AT(this,spos+n),nb);
  this->size_-=n;
	*END(this)=0;
}

void yaooc_string_replace(pointer p,yaooc_size_type pos,yaooc_size_type len,const char* str)
{
  yaooc_string_erase(p,pos,len);
  yaooc_string_insertn(p,pos,str,strlen(str));
}

void yaooc_string_replacen(pointer p,yaooc_size_type pos,yaooc_size_type len,const char* str,yaooc_size_type n)
{
  yaooc_string_erase(p,pos,len);
  yaooc_string_insertn(p,pos,str,n);
}
/*
	Convert string to upper case
*/
void yaooc_string_upcase_(pointer p)
{
	char* ptr=BEGIN(p);
	for(;*ptr != 0;ptr++) {
		if(islower(*ptr))
			*ptr=toupper(*ptr);
	}
}

yaooc_string_pointer yaooc_string_upcase(const_pointer p)
{
  yaooc_string_pointer new_str=new_copy_static(yaooc_string,p);
  yaooc_string_upcase_(new_str);
  return new_str;
}

/*
	Convert string to lower case
*/
void yaooc_string_downcase_(pointer p)
{
	char* ptr=BEGIN(p);
	for(;*ptr != 0;ptr++) {
		if(isupper(*ptr))
			*ptr=tolower(*ptr);
	}
}

yaooc_string_pointer yaooc_string_downcase(const_pointer p)
{
  yaooc_string_pointer new_str=new_copy_static(yaooc_string,p);
  yaooc_string_downcase_(new_str);
  return new_str;
}

/*
	Return new string creates from n characters starting a pos
*/
yaooc_string_pointer yaooc_string_substr(const_pointer p,yaooc_size_type pos,yaooc_size_type n)
{
	yaooc_string_const_pointer this=p;
//	printf("substr: pos: %zu size: %zu\n",pos,this->size_);
#ifdef __YAOOC_BOUNDS_CHECKING__
	assert(pos <= this->size_ && "pos out of range in yaooc_string_substr");
#endif
  if(n>(this->size_-pos))
		n=this->size_-pos;
	return new_ctor(yaooc_string,yaooc_string_ctor_ccs_n,this->array_+pos,n);
}

static const char* whitespace=" \t\r\n";
void yaooc_string_ltrim_(pointer p)
{
	yaooc_string_pointer this=p;
	if(this->size_ > 0) {
		char* ptr=BEGIN(this);
		char* last=END(this);
		while(ptr < last && strchr(whitespace,*ptr)) ptr++;
		yaooc_string_erase(this,0,ptr-BEGIN(this));
	}
}

yaooc_string_pointer yaooc_string_ltrim(const_pointer p)
{
  yaooc_string_pointer new_str=new_copy_static(yaooc_string,p);
  yaooc_string_ltrim_(new_str);
  return new_str;
}

void yaooc_string_rtrim_(pointer p)
{
	yaooc_string_pointer this=p;
	if(this->size_ > 0) {
		char* end=END(this);
		char* ptr=end-1;
		while(ptr >= BEGIN(this) && strchr(whitespace,*ptr)) ptr--;
		ptr++;
		yaooc_string_erase(this,ptr-BEGIN(this),end-ptr);
	}
}

yaooc_string_pointer yaooc_string_rtrim(const_pointer p)
{
  yaooc_string_pointer new_str=new_copy_static(yaooc_string,p);
  yaooc_string_rtrim_(new_str);
  return new_str;
}

void yaooc_string_trim_(pointer p)
{
	yaooc_string_ltrim_(p);
	yaooc_string_rtrim_(p);
}

yaooc_string_pointer yaooc_string_trim(const_pointer p)
{
  yaooc_string_pointer new_str=new_copy_static(yaooc_string,p);
  yaooc_string_trim_(new_str);
  return new_str;
}
/*

*/
typedef struct {
	char min;
	char max;
} char_range;
static int n_ranges;
#define max_ranges 25
char_range ranges[max_ranges];
char_range* rptr;
void add_to_range(char b,char e)
{
#ifdef __YAOOC_BOUNDS_CHECKING__
	assert(n_ranges < max_ranges && "Too many ranges specified for squeeze");
#endif
	if(b != 0) {
		rptr->min=b;
		if(e != 0)
			rptr->max=e;
		else
			rptr->max=b;
		n_ranges++;
		rptr++;
	}
}

static void parse_ranges(const char* squeeze_chars)
{
	n_ranges=0;
	if(squeeze_chars) {
		rptr=ranges;
		char beg_chr=0,end_chr;
		while((end_chr=*squeeze_chars) !=0) {
			if(end_chr == '-') {
				if(beg_chr) {
					end_chr=*++squeeze_chars;
					if(end_chr==0) { /* at end of string, '-' will be used as range character */
						add_to_range(beg_chr,-1);
						beg_chr=0;
						break;
					} else {
						add_to_range(beg_chr,end_chr);
					}
					beg_chr=0;
				} else { /* first char in string, '-' will be used as range character */
					beg_chr='-';
				}
			} else {
				if(beg_chr != 0)
				/* prev char not part of range (ie, a-z) so add it as a range */
					add_to_range(beg_chr,beg_chr);
				/* current char may be first char in a range (ie, a-z) wait til next char to add it */
				beg_chr=end_chr;
			}
			squeeze_chars++;
		}
		if(beg_chr)
			add_to_range(beg_chr,beg_chr);
	}
}

static inline bool in_range(char c)
{
	if(n_ranges==0)
		return true;
	int i;
	const char_range* rptr=ranges;
	for(i=0;i<n_ranges;i++,rptr++)
		if(rptr->min <= c && c <= rptr->max)
			return true;
	return false;
}

void yaooc_string_squeeze(pointer p,const char* squeeze_chars)
{
	yaooc_string_pointer this=p;
	if(this->size_ > 0) {
		parse_ranges(squeeze_chars);
		char prev=0;
		char* dst=BEGIN(this);
		char* src=dst;
		while(*src) {
			if(!(in_range(*src) && prev==*src))
				*dst++=*src;
			prev=*src++;
		}
		*dst=0;
		this->size_=dst-BEGIN(this);
	}
}

void yaooc_string_shrink_to_fit(pointer p)
{
	yaooc_string_pointer this=p;
	yaooc_array_container_shrink_to_fit(this);
	*END(this)=0;
}

void yaooc_string_resize(pointer p,yaooc_size_type new_size,char c)
{
	yaooc_string_pointer this=p;
	yaooc_array_container_resize(this,new_size,&c);
	*END(this)=0;
}

const void *memrmem(const void *ptr, yaooc_size_type size, const void *pat, yaooc_size_type patsize)
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

#ifdef _WIN32
void* memrchr(const void* buf,yaooc_size_type c,yaooc_size_type spos)
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

char* memrchr(void*,yaooc_size_type,yaooc_size_type);

#endif

/*
const char* strrstr(const char* s1,const char* s2,int pos)
{
	const char* r = NULL;
	if(s1 && pos > 0) {
		int l=strlen(s1);
		if(pos > l)
			pos=l;
		r=static_cast<const char*>(memrmem(s1,pos,s2,strlen(s2)));
	}
	return r;
}
*/

yaooc_size_type yaooc_string_findstr(const_pointer p,const char* s,yaooc_size_type spos)
{
  yaooc_string_const_pointer this=p;
  yaooc_size_type pos=this->class_table_->npos;
	if(this->size_ > 0 && spos < this->size_) {
		char* ptr=strstr(BEGIN(this)+spos,s);
		if(ptr)
			pos=ptr-BEGIN(this);
	}
	return pos;
}

yaooc_size_type yaooc_string_rfindstr(const_pointer p,const char* s,yaooc_size_type spos)
{
  yaooc_string_const_pointer this=p;
	yaooc_size_type pos=this->class_table_->npos;
	if(this->size_ > 0) {
		if(spos >= this->size_)
			spos=this->size_-1;
		const char* ptr = memrmem(BEGIN(this),spos+1,s,strlen(s));
		if(ptr)
			pos=ptr-BEGIN(this);
	}
	return pos;
}

yaooc_size_type yaooc_string_findchr(const_pointer p,char c,yaooc_size_type spos)
{
  yaooc_string_const_pointer this=p;
	yaooc_size_type pos=this->class_table_->npos;
	if(this->size_ > 0 && spos < this->size_) {
		char* ptr=strchr(BEGIN(this)+spos,c);
		if(ptr)
			pos=ptr-BEGIN(this);
	}
	return pos;
}

yaooc_size_type yaooc_string_rfindchr(const_pointer p,char c,yaooc_size_type spos)
{
  yaooc_string_const_pointer this=p;
	yaooc_size_type pos=this->class_table_->npos;
	if(this->size_ > 0) {
		if(spos >= this->size_)
			spos=this->size_-1;
		const char* ptr = memrchr(BEGIN(this),c,spos+1);
		if(ptr)
			pos=ptr-BEGIN(this);
	}
	return pos;
}

ISA_IMPLEMENTATION(yaooc_string,yaooc_array_container)

yaooc_string_class_members_t yaooc_string_class_members = { YAOOC_STRING_CLASS_MEMBERS };

DEFINE_TYPE_INFO(yaooc_string,yaooc_string_default_ctor,NULL,
      yaooc_string_copy_ctor,yaooc_string_assign,yaooc_string_less_than_compare,
      (const class_table_t*)&yaooc_string_class_members,
#ifdef __YAOOC_USE_GC__
      yaooc_object   /* If using GC, want to skip container destructor */
#else
      yaooc_array_container
#endif
  )
