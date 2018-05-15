#include <stdio.h>
#include <string.h>
#include <yaooc/new.h>
#include <yaooc/stream.h>

/* Normall, From here <--- */
class_table(my_string) {
  const char* (*get)(const_pointer);
  void (*set)(pointer,const char*);
};

class_instance(my_string) {
  char* str;
};

class(my_string);

void my_string_default_ctor(pointer);
void my_string_dtor(pointer);
void my_string_assign(pointer,const_pointer);
void my_string_copy_ctor(pointer,const_pointer);
bool my_string_less_than_compare(const_pointer,const_pointer);

const char* my_string_get(const_pointer);
void my_string_set(pointer,const char*);
void my_string_ctor_ccs(pointer,va_list);
void my_string_ctor_ccs_n(pointer,va_list);
void my_string_ctor_chr_n(pointer,va_list);

/*  --> to here. would be in the header file */

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

my_string_class_table_t my_string_class_table =
{
  .get = my_string_get,
  .set = my_string_set
};

DEFINE_TYPE_INFO(my_string,my_string_default_ctor,my_string_dtor,my_string_copy_ctor,my_string_assign,my_string_less_than_compare,my_string_to_stream,my_string_from_stream,&my_string_class_table,NULL);

/*
  Constructors for my_string
*/

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
      this->str=malloc(n+1);
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
    this->str=malloc(n+1);
    memset(this->str,c,n);
    this->str[n]=0;
  }
}

int main(int argc,char* argv[])
{
  /* Create a new my_string object using my_string_ctor_ccs ctor */
  my_string_pointer sp1=new_ctor(my_string,my_string_ctor_ccs,"This is sp1 test string.");

  /* Create a new my_string object using my_string_ctor_ccs_n ctor */
  my_string_pointer sp2=new_ctor(my_string,my_string_ctor_ccs_n,"This is sp2 test string. This part will not be included.",24);

  /* Create a new my_string object using my_string_ctor_chr_n ctor */
  my_string_pointer sp3=new_ctor(my_string,my_string_ctor_chr_n,'Y',24);

	STREAM(cout,sp1,endl);
	STREAM(cout,sp2,endl);
	STREAM(cout,sp3,endl);

  /* Delete allocated objects */
  delete(sp1);
  delete(sp2);
  delete(sp3);
}
