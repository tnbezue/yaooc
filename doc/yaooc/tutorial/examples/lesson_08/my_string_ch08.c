#include <stdio.h>
#include <string.h>
#include <yaooc/new.h>
#include <yaooc/stream.h>

/* Normall, From here <--- */
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
int my_string_rich_compare(const_pointer,const_pointer);
void my_string_to_stream(const_pointer,ostream_pointer);
void my_string_from_stream(pointer,istream_pointer);
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
	M(this,set,src->str);  // Could have used my_string_set(this,src->str);
}

int my_string_rich_compare(const_pointer p1,const_pointer p2)
{
  my_string_const_pointer lhs = p1;
  my_string_const_pointer rhs = p2;
  if(lhs->str == NULL) {
    if(rhs->str == NULL)
      return 0; /* both NULL, equal */
    else
      return -1; /* lhs is NULL, rhs is not.  NULL is less than not NULL */
  } else if(rhs->str == NULL)
    return 1; /* lhs is not NULL, rhs is NULL. non NULL greater than NULL */
  return strcmp(lhs->str,rhs->str); /* Both not null, compare the strings */
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
	M(strm,scanf,"%255s",temp);
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
	M(cout,printf,"Enter value for SP1\n");
	STREAM(cin,sp1,NULL);
	M(cout,printf,"You entered :");
	STREAM(cout,sp1,endl,NULL);

	delete(sp1);
}
