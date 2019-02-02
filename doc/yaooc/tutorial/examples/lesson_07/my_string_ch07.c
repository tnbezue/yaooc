#include <stdio.h>
#include <string.h>
#include <yaooc/new.h>
#include <yaooc/stream.h>

/* Normally, From here <--- */
yaooc_class_table(my_string) {
  const char* (*get)(const_pointer);
  void (*set)(pointer,const char*);
};

yaooc_class_instance(my_string) {
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

DEFINE_TYPE_INFO(my_string,Y,Y,Y,Y,Y,N,N,Y,NULL);

int main(int argc,char* argv[])
{
  my_string_pointer sp1=new(my_string);
	sp1->class_table_->set(sp1,"sp1 test string");  // Calling set using class table pointer

  my_string_pointer sp2=new(my_string);
  M(sp2,set,"sp2 test string");   // Calling set method using M macro

  my_string_pointer sp3=new(my_string);
  M(sp3,set,"sp3 string");

	printf("SP1: %s\nSP2: %s\nSP3: %s\n",M(sp1,get),sp2->class_table_->get(sp2),M(sp3,get));

  delete(sp1);
  delete(sp2);
  delete(sp3);
}
