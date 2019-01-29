#include "my_string_vector.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <yaooc/stream.h>
#include <yaooc/pointer_bag.h>
#include <yaooc/algorithm.h>

char *strrstr(const char *ptr, const char *pat)
{
	char *p;

	if(ptr != NULL && pat != NULL) {
    size_t size = strlen(ptr);
    size_t patsize=strlen(pat);
		/* Special cases */
		if (size < patsize)
			return NULL;
		if (patsize == 0)
			return (char*)ptr;

		for (p = (char*)ptr + size - patsize ; size >= patsize; --p, --size)
			if(*p == *pat)
				if (memcmp(p, pat, patsize) == 0)
					return p;
	}
	return NULL;
}

/*  Begin YAOOC PreProcessor generated content */


/* Implementation of my_string private members */
static void my_string_allocate_space(pointer p,size_t n)
{
  my_string_pointer this=p;
  this->str=realloc(this->str,n+1);
}

/* Implementation of my_string type info members */
void my_string_default_ctor(pointer p)
{
  my_string_pointer this=p;
  this->str=NULL;
}

void my_string_dtor(pointer p)
{
  my_string_pointer this=p;
  if(this->str)
    free(this->str);
}

void my_string_copy_ctor(pointer p,const_pointer s)
{
  my_string_default_ctor(p);
  my_string_assign(p,s);
}

void my_string_assign(pointer p,const_pointer s)
{
  my_string_pointer this=p;
  my_string_const_pointer src=s;
  my_string_dtor(p);
  this->str = src->str == NULL ? NULL : strdup(src->str);
}

bool my_string_less_than_compare(const_pointer p1,const_pointer p2)
{
  my_string_const_pointer bsp1 = p1;
  my_string_const_pointer bsp2 = p2;
  if(bsp1->str == NULL) {
    if(bsp2->str == NULL)
      return false; /* both NULL, equal -- NULL is not less than NULL */
    else
      return true; /* 1st is NULL, second is not.  NULL is less than not NULL */
  } else if(bsp2 == NULL)
    return false; /* 1st is not NULL, second is NULL. Not NULL is not less than NULL */
  return strcmp(bsp1->str,bsp2->str) < 0; /* Both not null, compare the strings */
}

void my_string_to_stream(const_pointer p,pointer s)
{
	my_string_const_pointer this = p;
	yaooc_ostream_pointer strm=s;
	M(strm,printf,"%s",this->str);
}

void my_string_from_stream(pointer p,pointer s)
{
	my_string_pointer this = p;
	yaooc_istream_pointer strm=s;
	char temp[256];
	M(strm,scanf,"%s",temp);
	if(this->str)
		free(this->str);
	this->str=strdup(temp);
}

/* Constructors for my_string */
void my_string_ctor_ccs_n(pointer p,va_list args)
{
  my_string_pointer this=p;
  const char* str=va_arg(args,const char*);
  size_t n = va_arg(args,size_t);
  my_string_default_ctor(p);
  if(str != NULL) {
    if(n > strlen(str))
      n=strlen(str);
    if(n > 0) {
      my_string_insert_space(this,0,n);
      strncpy(this->str,str,n);
      this->str[n]=0;
    }
  }
}

void my_string_ctor_ccs(pointer p,va_list args)
{
  const char* str=va_arg(args,const char*);
  call_constructor(p,my_string_ctor_ccs_n,str,SIZE_MAX);
}

void my_string_ctor_chr_n(pointer p,va_list args)
{
  my_string_pointer this=p;
  char c = va_arg(args,int);
  size_t n = va_arg(args,size_t);
  my_string_default_ctor(p);
  if(c && n > 0) {
    my_string_insert_space(this,0,n);
    memset(this->str,c,n);
    this->str[n]=0;
  }
}

/* my_string protected members */
void my_string_insert_space(pointer p,size_t pos,size_t n)
{
  my_string_pointer this=p;
  size_t cur_size=my_string_size(this);
  my_string_allocate_space(this,cur_size+n);
  memmove(this->str+pos+n,this->str+pos,cur_size-pos);
  this->str[cur_size+n]=0;
}

void my_string_erase_space(pointer p,size_t pos,size_t n)
{
  my_string_pointer this=p;
  size_t cur_size=my_string_size(this);
  memmove(this->str+pos,this->str+pos+n,strlen(this->str)-(pos+n));
  this->str[cur_size-n]=0;
}

/* Class table methods for my_string */
void my_string_swap(pointer p,pointer o)
{
  my_string_pointer this=p;
  my_string_pointer other=o;
  SWAP(char*,this->str,other->str);
}

const char* my_string_get(const_pointer p)
{
  return ((my_string_const_pointer)p)->str;
}

void my_string_set(pointer p,const char* s)
{
  my_string_pointer this=p;
  my_string_dtor(this);
  this->str = s==NULL ? NULL : strdup(s);
}

my_string_pointer my_string_substr(pointer p,size_t beg,size_t n)
{
  my_string_pointer this=p;
  my_string_pointer ret=new_ctor(my_string,my_string_ctor_ccs_n,this->str+beg,n);
  return ret;
}

void my_string_insert(pointer p,size_t pos,const char* s)
{
//  my_string_pointer this=p;
  my_string_insertn(p,pos,s,SIZE_MAX);
}

void my_string_insertn(pointer p,size_t pos,const char* s,size_t n)
{
  my_string_pointer this=p;
	if(pos > M(this,size))
		THROW(new(my_string_insert_exception));
  if(s) {
    size_t l=strlen(s);
    if(n>l)
      n=l;
    my_string_insert_space(this,pos,n);
    memcpy(this->str+pos,s,n);
  }
}

void my_string_erase(pointer p,size_t pos,size_t n)
{
  my_string_pointer this=p;
  if(pos > M(this,size))
    THROW(new(my_string_erase_exception));
  my_string_erase_space(this,pos,n);
}

void my_string_append(pointer p,const char* s)
{
  my_string_pointer this=p;
  my_string_insertn(this,strlen(this->str),s,SIZE_MAX);
}

void my_string_appendn(pointer p,const char* s,size_t n)
{
  my_string_pointer this=p;
  my_string_insertn(this,strlen(this->str),s,n);
}

const char* my_string_find(const_pointer p,const char* s)
{
  my_string_const_pointer this=p;
  return strstr(this->str,s);
}

const char* my_string_rfind(const_pointer p,const char* s)
{
  my_string_const_pointer this=p;
  return strrstr(this->str,s);
}

const char* my_string_find_chr(const_pointer p,char ch)
{
  my_string_const_pointer this=p;
  return strchr(this->str,ch);
}

const char* my_string_rfind_chr(const_pointer p,char ch)
{
  my_string_const_pointer this=p;
  return strrchr(this->str,ch);
}

char* my_string_at(pointer p,size_t i)
{
  my_string_pointer this=p;
  if(i > M(this,size))
	  THROW(new(my_string_at_exception));
  return this->str+i;
}

size_t my_string_size(const_pointer p)
{
  my_string_const_pointer this=p;
 return this->str ? strlen(this->str) : 0;
}

char* my_string_end(const_pointer p)
{
  my_string_const_pointer this=p;
  return this->str ? this->str+strlen(this->str) : NULL;
}


/* Class table for my_string */
my_string_class_table_t my_string_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "my_string_t",
  .swap = (void (*) (pointer,pointer)) my_string_swap,
  .my_string_n_pos = (const size_t) -1,
  .get = (const char* (*) (const_pointer)) my_string_get,
  .c_str = (const char* (*) (const_pointer)) my_string_get,
  .set = (void (*) (pointer,const char*)) my_string_set,
  .substr = (my_string_pointer (*) (pointer,size_t,size_t)) my_string_substr,
  .insert = (void (*) (pointer,size_t,const char*)) my_string_insert,
  .insertn = (void (*) (pointer,size_t,const char*,size_t)) my_string_insertn,
  .erase = (void (*) (pointer,size_t,size_t)) my_string_erase,
  .append = (void (*) (pointer,const char*)) my_string_append,
  .appendn = (void (*) (pointer,const char*,size_t)) my_string_appendn,
  .find = (const char* (*) (const_pointer,const char*)) my_string_find,
  .rfind = (const char* (*) (const_pointer,const char*)) my_string_rfind,
  .find_chr = (const char* (*) (const_pointer,char)) my_string_find_chr,
  .rfind_chr = (const char* (*) (const_pointer,char)) my_string_rfind_chr,
  .at = (char* (*) (pointer,size_t)) my_string_at,
  .size = (size_t (*) (const_pointer)) my_string_size,
  .length = (size_t (*) (const_pointer)) my_string_size,
  .begin = (char* (*) (const_pointer)) my_string_get,
  .end = (char* (*) (const_pointer)) my_string_end,
};

DEFINE_TYPE_INFO(my_string,Y,Y,Y,Y,Y,Y,Y,Y,yaooc_object)

/* my_string_exception private members */

/* my_string_exception type info members */
void my_string_exception_default_ctor(pointer p)
{
  my_string_exception_pointer this=p;
  this->what_=NULL;
}

void my_string_exception_dtor(pointer p)
{
  my_string_exception_pointer this=p;
  if(this->what_) {
    FREE(this->what_);
  }
}

/* Constructors for my_string_exception */
void my_string_exception_ctor_ccs(pointer p,va_list args)
{
  my_string_exception_pointer this=p;
  const char* msg = va_arg(args,const char*);
  this->what_=msg ? STRDUP(msg) : NULL;
}

/* my_string_exception protected members */

/* Class table methods for my_string_exception */
const char* my_string_exception_what(const_pointer p)
{
  my_string_exception_const_pointer this=p;
  return this->what_;
}

/* Class table for my_string_exception */
my_string_exception_class_table_t my_string_exception_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_exception_class_table,
  .type_name_ = (const char*) "my_string_exception_t",
  .swap = (void (*) (pointer,pointer)) yaooc_exception_swap,
  .what = (const char* (*) (const_pointer)) my_string_exception_what,
};

DEFINE_TYPE_INFO(my_string_exception,Y,Y,N,N,N,N,N,Y,yaooc_exception)

/* my_string_insert_exception private members */

/* my_string_insert_exception type info members */
void my_string_insert_exception_default_ctor(pointer p)
{
  call_constructor(p,my_string_exception_ctor_ccs,"Position out of range in insert");
}

/* Constructors for my_string_insert_exception */

/* my_string_insert_exception protected members */

/* Class table methods for my_string_insert_exception */

/* Class table for my_string_insert_exception */
my_string_insert_exception_class_table_t my_string_insert_exception_class_table =
{
  .parent_class_table_ = (const class_table_t*) &my_string_exception_class_table,
  .type_name_ = (const char*) "my_string_insert_exception_t",
  .swap = (void (*) (pointer,pointer)) my_string_exception_swap,
  .what = (const char* (*) (const_pointer)) my_string_exception_what,
};

DEFINE_TYPE_INFO(my_string_insert_exception,Y,N,N,N,N,N,N,Y,my_string_exception)

/* my_string_erase_exception private members */

/* my_string_erase_exception type info members */
void my_string_erase_exception_default_ctor(pointer p)
{
  call_constructor(p,my_string_exception_ctor_ccs,"Position out of range in erase");
}

/* Constructors for my_string_erase_exception */

/* my_string_erase_exception protected members */

/* Class table methods for my_string_erase_exception */

/* Class table for my_string_erase_exception */
my_string_erase_exception_class_table_t my_string_erase_exception_class_table =
{
  .parent_class_table_ = (const class_table_t*) &my_string_exception_class_table,
  .type_name_ = (const char*) "my_string_erase_exception_t",
  .swap = (void (*) (pointer,pointer)) my_string_exception_swap,
  .what = (const char* (*) (const_pointer)) my_string_exception_what,
};

DEFINE_TYPE_INFO(my_string_erase_exception,Y,N,N,N,N,N,N,Y,my_string_exception)

/* my_string_at_exception private members */

/* my_string_at_exception type info members */
void my_string_at_exception_default_ctor(pointer p)
{
  call_constructor(p,my_string_exception_ctor_ccs,"Position out of range in at");
}

/* Constructors for my_string_at_exception */

/* my_string_at_exception protected members */

/* Class table methods for my_string_at_exception */

/* Class table for my_string_at_exception */
my_string_at_exception_class_table_t my_string_at_exception_class_table =
{
  .parent_class_table_ = (const class_table_t*) &my_string_exception_class_table,
  .type_name_ = (const char*) "my_string_at_exception_t",
  .swap = (void (*) (pointer,pointer)) my_string_exception_swap,
  .what = (const char* (*) (const_pointer)) my_string_exception_what,
};

DEFINE_TYPE_INFO(my_string_at_exception,Y,N,N,N,N,N,N,Y,my_string_exception)

/*  End YAOOC PreProcessor generated content */
VECTOR_IMPLEMENTATION(my_string,my_string_vector);

int main(int argc,char* argv[])
{
	PB_INIT;
	my_string_vector_pointer msv=PB_SAVE(new(my_string_vector));
	M(msv,push_back,PB_SAVE(new_ctor(my_string,my_string_ctor_ccs,"This is the first string")));
	M(msv,push_back,PB_SAVE(new_ctor(my_string,my_string_ctor_ccs,"This is the second string")));
	M(msv,push_back,PB_SAVE(new_ctor(my_string,my_string_ctor_ccs,"This is the third string")));
	M(msv,push_back,PB_SAVE(new_ctor(my_string,my_string_ctor_ccs,"This is the forth string")));
	M(msv,push_back,PB_SAVE(new_ctor(my_string,my_string_ctor_ccs,"This is the fifth string")));
	M(msv,push_back,PB_SAVE(new_ctor(my_string,my_string_ctor_ccs,"This is the sixth string")));
	M(msv,push_back,PB_SAVE(new_ctor(my_string,my_string_ctor_ccs,"This is the seventh string")));
	M(msv,push_back,PB_SAVE(new_ctor(my_string,my_string_ctor_ccs,"This is the eighth string")));
	M(msv,push_back,PB_SAVE(new_ctor(my_string,my_string_ctor_ccs,"This is the ninth string")));
	M(msv,push_back,PB_SAVE(new_ctor(my_string,my_string_ctor_ccs,"This is the tenth string")));

	my_string_vector_const_iterator i;
	for(i=M(msv,begin);i!=M(msv,end);i++) {
		STREAM(cout,O_OBJ(my_string,*i),endl);
	}

	my_string_pointer temp=PB_SAVE(new_ctor(my_string,my_string_ctor_ccs,"This is the fifth string"));
	my_string_const_pointer pos=yaooc_find(my_string,M(msv,begin),M(msv,end),temp);
	if(pos != M(msv,end))
		STREAM(cout,O_CCS("temp found at pos "),O_SIZE(pos-(my_string_const_pointer)M(msv,begin)),endl);

	STREAM(cout,endl);
	FOR_EACH(i,msv)
		STREAM(cout,O_OBJ(my_string,*i),endl);
	PB_EXIT;
}