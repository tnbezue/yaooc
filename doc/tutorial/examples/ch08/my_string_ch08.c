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

DEFINE_TYPE_INFO(my_string,Y,Y,Y,Y,Y,Y,Y,Y,NULL);

int main(int argc,char* argv[])
{
  my_string_pointer sp1=new(my_string);
  M(sp1,set,"This is sp1 test string");

  my_string_pointer sp2=new(my_string);
  M(sp2,set,"This is sp2 test string");

  my_string_pointer sp3=new(my_string);
  M(sp3,set,"This is sp3 string");

	M(cout,printf,"Using printf\n%s\n%s\n%s\n\n",M(sp1,get),M(sp2,get),M(sp3,get));

	my_string_pointer msg=new(my_string);
	M(msg,set,"Using stream");
	M(cout,stream,msg,endl,sp1,endl,sp2,endl,sp3,endl,NULL);

	M(cout,printf,"\nEnter an integer\n");
	M(cin,stream,sp1,NULL);
	M(cout,printf,"You entered \"%s\"\n",sp1->str);

  delete(sp1);
  delete(sp2);
  delete(sp3);
}
