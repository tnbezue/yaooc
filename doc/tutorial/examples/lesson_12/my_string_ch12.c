#include <stdio.h>
#include <string.h>
#include <yaooc/new.h>
#include <yaooc/object.h>
#include <yaooc/stream.h>

/* Normall, From here <--- */
yaooc_class_table(my_string) {
  yaooc_object_class_table_t;
  const char* (*get)(const_pointer);
  void (*set)(pointer,const char*);
};

yaooc_class_instance(my_string) {
  yaooc_object_class_instance_t;
  char* str;
};

yaooc_class(my_string);

void my_string_default_ctor(pointer);
void my_string_dtor(pointer);
void my_string_assign(pointer,const_pointer);
void my_string_copy_ctor(pointer,const_pointer);
bool my_string_less_than_compare(const_pointer,const_pointer);

const char* my_string_get(const_pointer);
void my_string_set(pointer,const char*);
void my_string_ctor_ccs(pointer,va_list);
void my_string_ctor_ccs_size(pointer,va_list);
void my_string_ctor_chr_size(pointer,va_list);

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
      return false;
    else
      return true;
  } else if(bsp2 == NULL)
    return false;
  return strcmp(bsp1->str,bsp2->str) < 0;
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

void my_string_swap(pointer p,pointer o)
{
  my_string_pointer this=p;
  my_string_pointer other=o;
  char* temp=this->str;
  this->str=other->str;
  other->str=temp;
}
void my_string_set(pointer p,const char* s)
{
  my_string_pointer this=p;
  my_string_dtor(this);
  this->str = s==NULL ? NULL : strdup(s);
}

my_string_class_table_t my_string_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = "my_string_t",
  .swap = my_string_swap,
  .get = my_string_get,
  .set = my_string_set
};

DEFINE_TYPE_INFO(my_string,Y,Y,Y,Y,Y,Y,Y,Y,yaooc_object);

/*
  Constructors for my_string
*/

void my_string_ctor_ccs_size(pointer p,va_list args)
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
  call_constructor(p,my_string_ctor_ccs_size,str,SIZE_MAX);
}

void my_string_ctor_chr_size(pointer p,va_list args)
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

  my_string_t ms1;
  newp(&ms1,my_string);
  M(&ms1,set,"This is a test");
  STREAM(cout,O_CCS("SP1 is \""),O_OBJ(my_string,ms1),O_CCS("\""),endl);

	int z;
	char temp[64];
	STREAM(cout,O_CCS("Enter an integer and a string containing at least two words\n"));
	STREAM(cin,I_INT(z),I_CCS(temp),I_OBJ(my_string,ms1));
	STREAM(cout,O_CCS("The integer is "),O_INT(z),O_CCS(".\nThe first word is \""),O_CCS(temp),
					O_CCS("\"\nThe second word is \""),O_OBJ(my_string,ms1),O_CCS("\".\n"));

  deletep(&ms1,my_string);
}
