/* Begin YAOOCPP output */

#include "my_string_map.h"


#include <stdio.h>
#include <stdlib.h>

/* Private variables implementation for my_string */

/* Private methods prototypes for my_string */
static void my_string_allocate_space(pointer, size_t);
static char* my_string_strrstr(const_pointer, const char*);

/* Type Info implemmentation for my_string */
void my_string_default_ctor(pointer p)
{
  my_string_pointer this=p;
  this->str = NULL;
}

void my_string_dtor(pointer p)
{
  my_string_pointer this=p;
  if(this->str)
     free(this->str);
  this->str = NULL;
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
  if(this->str != NULL)
    free(this->str);
  this->str = src->str ? strdup(src->str) : NULL;
}

bool my_string_less_than_compare(const_pointer lhs_cp,const_pointer rhs_cp)
{
  my_string_const_pointer lhs=lhs_cp;
  my_string_const_pointer rhs=rhs_cp;
  if(lhs->str == NULL) {
    if(rhs->str == NULL)
      return false;
    else
      return true;
  } else if(rhs->str == NULL)
    return false;
  return strcmp(lhs->str,rhs->str) < 0;
}

void my_string_to_stream(const_pointer p,ostream_pointer o){
  my_string_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
	M(ostrm,printf,"%s",this->str);
}

void my_string_from_stream(pointer p,istream_pointer i){
  my_string_pointer this=p;
  yaooc_istream_pointer istrm=i;
	char temp[256];
	M(istrm,scanf,"%255s",temp);
	if(this->str)
		free(this->str);
	this->str=strdup(temp);
}

/* Constructors implementation for my_string */
void my_string_ctor_ccs_size(pointer p,va_list args)
{
  my_string_pointer this=p;
	const char* str= va_arg(args, const char*);
	size_t n= va_arg(args, size_t);
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
	const char* str= va_arg(args, const char*);
  call_constructor(p,my_string_ctor_ccs_size,str,SIZE_MAX);
}

void my_string_ctor_chr_size(pointer p,va_list args)
{
  my_string_pointer this=p;
	int ch= va_arg(args, int);
	size_t n= va_arg(args, size_t);
  my_string_default_ctor(p);
  if(ch && n > 0) {
    my_string_insert_space(this,0,n);
    memset(this->str,ch,n);
    this->str[n]=0;
  }
}


/* Private methods implementation for my_string */
static void my_string_allocate_space(pointer p,size_t n)
{
  my_string_pointer this=p;
  this->str=realloc(this->str,n+1);
}

static char* my_string_strrstr(const_pointer p,const char* pat)
{
  my_string_const_pointer this=p;
  char* ret = NULL;
  const char* ptr=this->str;

	if(ptr != NULL && pat != NULL) {
    size_t size = strlen(ptr);
    size_t patsize=strlen(pat);
		/* Special cases */
		if (size < patsize)
			return NULL;
		if (patsize == 0)
			return (char*)ptr;

		for (ret = (char*)ptr + size - patsize ; size >= patsize; --ret, --size)
			if(*ret == *pat)
				if (memcmp(ret, pat, patsize) == 0)
					return ret;
	}
  return ret;
}


/* Protected implementation for my_string */
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


/* Table implementation for my_string */
void my_string_swap(pointer p,pointer p2)
{
  my_string_pointer this=p;
  my_string_pointer other=p2;
  char* temp=this->str;
  this->str=other->str;
  other->str=temp;
}

const char* my_string_get(const_pointer p)
{
  my_string_const_pointer this=p;
  return this->str;
}

void my_string_set(pointer p,const char* s)
{
  my_string_pointer this=p;
  my_string_dtor(this);
  this->str = s ? strdup(s) : NULL;
}

my_string_pointer my_string_substr(pointer p,size_t beg,size_t n)
{
  my_string_pointer this=p;
  my_string_pointer ret=new_ctor(my_string,my_string_ctor_ccs_size,this->str+beg,n);
  return ret;
}

void my_string_insert(pointer p,size_t pos,const char* s)
{
  my_string_pointer this=p;
  my_string_insertn(this,pos,s,SIZE_MAX);
}

void my_string_insertn(pointer p,size_t pos,const char* s,size_t n)
{
  my_string_pointer this=p;
	if(pos > M(this,size))
		THROW(new_ctor(my_string_insert_exception,my_string_insert_exception_ctor_v,"Position out of range in insert"));
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
    THROW(new_ctor(my_string_erase_exception,my_string_erase_exception_ctor_v,"Position out of range in erase"));
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
  const char* ret = strstr(this->str,s);
  return ret;
}

const char* my_string_rfind(const_pointer p,const char* s)
{
  my_string_const_pointer this=p;
  const char* ret = my_string_strrstr(this,s);;
  return ret;
}

const char* my_string_find_chr(const_pointer p,char ch)
{
  my_string_const_pointer this=p;
  const char* ret = strchr(this->str,ch);
  return ret;
}

const char* my_string_rfind_chr(const_pointer p,char ch)
{
  my_string_const_pointer this=p;
  const char* ret = strrchr(this->str,ch);
  return ret;
}

char* my_string_at(pointer p,size_t i)
{
  my_string_pointer this=p;
  if(i > M(this,size))
    THROW(new_ctor(my_string_at_exception,my_string_at_exception_ctor_v,"Position out of range in at"));
  char* ret = this->str+i;
  return ret;
}

size_t my_string_size(const_pointer p)
{
  my_string_const_pointer this=p;
  size_t ret = this->str ? strlen(this->str) : 0;
  return ret;
}

char* my_string_end(const_pointer p)
{
  my_string_const_pointer this=p;
  char* ret = this->str ? this->str+strlen(this->str) : NULL;
  return ret;
}


/* Class table definition for my_string */
my_string_class_table_t my_string_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "my_string_t",
  .swap = (void(*)(pointer, pointer)) my_string_swap,
  .n_pos = (const size_t) -1,
  .get = (const char*(*)(const_pointer)) my_string_get,
  .c_str = (const char*(*)(const_pointer)) my_string_c_str,
  .set = (void(*)(pointer, const char*)) my_string_set,
  .substr = (my_string_pointer(*)(pointer, size_t, size_t)) my_string_substr,
  .insert = (void(*)(pointer, size_t, const char*)) my_string_insert,
  .insertn = (void(*)(pointer, size_t, const char*, size_t)) my_string_insertn,
  .erase = (void(*)(pointer, size_t, size_t)) my_string_erase,
  .append = (void(*)(pointer, const char*)) my_string_append,
  .appendn = (void(*)(pointer, const char*, size_t)) my_string_appendn,
  .find = (const char*(*)(const_pointer, const char*)) my_string_find,
  .rfind = (const char*(*)(const_pointer, const char*)) my_string_rfind,
  .find_chr = (const char*(*)(const_pointer, char)) my_string_find_chr,
  .rfind_chr = (const char*(*)(const_pointer, char)) my_string_rfind_chr,
  .at = (char*(*)(pointer, size_t)) my_string_at,
  .size = (size_t(*)(const_pointer)) my_string_size,
  .length = (size_t(*)(const_pointer)) my_string_length,
  .begin = (char*(*)(const_pointer)) my_string_begin,
  .end = (char*(*)(const_pointer)) my_string_end,
};

/* Type info structure for my_string */
DEFINE_TYPE_INFO(my_string,Y,Y,Y,Y,Y,Y,Y,Y,yaooc_object);

/* Private variables implementation for my_string_exception */

/* Private methods prototypes for my_string_exception */

/* Type Info implemmentation for my_string_exception */
/* Constructors implementation for my_string_exception */

/* Private methods implementation for my_string_exception */

/* Protected implementation for my_string_exception */

/* Table implementation for my_string_exception */

/* Class table definition for my_string_exception */
my_string_exception_class_table_t my_string_exception_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_exception_class_table,
  .type_name_ = (const char*) "my_string_exception_t",
  .swap = (void(*)(pointer, pointer)) my_string_exception_swap,
  .what = (const char*(*)(const_pointer)) my_string_exception_what,
};

/* Type info structure for my_string_exception */
DEFINE_TYPE_INFO(my_string_exception,N,N,N,N,N,N,N,Y,yaooc_exception);

/* Private variables implementation for my_string_insert_exception */

/* Private methods prototypes for my_string_insert_exception */

/* Type Info implemmentation for my_string_insert_exception */
/* Constructors implementation for my_string_insert_exception */

/* Private methods implementation for my_string_insert_exception */

/* Protected implementation for my_string_insert_exception */

/* Table implementation for my_string_insert_exception */

/* Class table definition for my_string_insert_exception */
my_string_insert_exception_class_table_t my_string_insert_exception_class_table =
{
  .parent_class_table_ = (const class_table_t*) &my_string_exception_class_table,
  .type_name_ = (const char*) "my_string_insert_exception_t",
  .swap = (void(*)(pointer, pointer)) my_string_insert_exception_swap,
  .what = (const char*(*)(const_pointer)) my_string_insert_exception_what,
};

/* Type info structure for my_string_insert_exception */
DEFINE_TYPE_INFO(my_string_insert_exception,N,N,N,N,N,N,N,Y,my_string_exception);

/* Private variables implementation for my_string_erase_exception */

/* Private methods prototypes for my_string_erase_exception */

/* Type Info implemmentation for my_string_erase_exception */
/* Constructors implementation for my_string_erase_exception */

/* Private methods implementation for my_string_erase_exception */

/* Protected implementation for my_string_erase_exception */

/* Table implementation for my_string_erase_exception */

/* Class table definition for my_string_erase_exception */
my_string_erase_exception_class_table_t my_string_erase_exception_class_table =
{
  .parent_class_table_ = (const class_table_t*) &my_string_exception_class_table,
  .type_name_ = (const char*) "my_string_erase_exception_t",
  .swap = (void(*)(pointer, pointer)) my_string_erase_exception_swap,
  .what = (const char*(*)(const_pointer)) my_string_erase_exception_what,
};

/* Type info structure for my_string_erase_exception */
DEFINE_TYPE_INFO(my_string_erase_exception,N,N,N,N,N,N,N,Y,my_string_exception);

/* Private variables implementation for my_string_at_exception */

/* Private methods prototypes for my_string_at_exception */

/* Type Info implemmentation for my_string_at_exception */
/* Constructors implementation for my_string_at_exception */

/* Private methods implementation for my_string_at_exception */

/* Protected implementation for my_string_at_exception */

/* Table implementation for my_string_at_exception */

/* Class table definition for my_string_at_exception */
my_string_at_exception_class_table_t my_string_at_exception_class_table =
{
  .parent_class_table_ = (const class_table_t*) &my_string_exception_class_table,
  .type_name_ = (const char*) "my_string_at_exception_t",
  .swap = (void(*)(pointer, pointer)) my_string_at_exception_swap,
  .what = (const char*(*)(const_pointer)) my_string_at_exception_what,
};

/* Type info structure for my_string_at_exception */
DEFINE_TYPE_INFO(my_string_at_exception,N,N,N,N,N,N,N,Y,my_string_exception);

/* End YAOOCPP output */

MAP_IMPLEMENTATION(my_string,long,my_string_long_map);

int main(int argc,char* argv[])
{
	PB_INIT;
	my_string_long_map_pointer shows_by_character=PB_SAVE(new(my_string_long_map));

	// Another way to initialize a static object without calling newp
	my_string_t name={ .class_table_=&my_string_class_table, .str=NULL };
	long_t n_shows;

	/* FYI, these numbers are made up */
	M(&name,set,"Bugs Bunny");
	n_shows=2385;
	M(shows_by_character,insert,&name,&n_shows);
	n_shows=1995;
	M(shows_by_character,insert,PB_SAVE(new_ctor(my_string,my_string_ctor_ccs,"Daffy Duck")),&n_shows);
	n_shows=1234;
	M(shows_by_character,insert,PB_SAVE(new_ctor(my_string,my_string_ctor_ccs,"Tweety Bird")),&n_shows);
	n_shows=1523;
	M(shows_by_character,insert,PB_SAVE(new_ctor(my_string,my_string_ctor_ccs,"Foghorn Leghorn")),&n_shows);

	my_string_long_map_const_iterator i;
	FOR_EACH(i,shows_by_character)
		M(cout,printf,"%s has done %ld shows\n",M(&i->first,c_str),i->second);
	deletep(&name,my_string);
	PB_EXIT;
}
