#include <stdio.h>
#include <string.h>
#include <yaooc/new.h>

/* Normally, From here <--- */
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

DEFINE_TYPE_INFO(my_string,my_string_default_ctor,my_string_dtor,my_string_copy_ctor,my_string_assign,my_string_less_than_compare,NULL,NULL,&my_string_class_table,NULL);

int main(int argc,char* argv[])
{
  /* Create a new my_string object */
  my_string_pointer sp1=new(my_string);

  /* Assign value to sp1 */
  M(sp1,set,"This is sp1 test string");

  /* Using copy ctor to create another simple string object */
  my_string_pointer sp2=new_copy(sp1);
  M(sp2,set,"This is sp2 test string");

  /* Create a new string object and assign sp2 value to it.  Same as using copy ctor */
  /* Note that sp3=sp2 can not be used.  Assignment method must be used */
  my_string_pointer sp3=new(my_string);
  assign(sp3,sp2);
  M(sp3,set,"This is sp3 string");

  printf("%s\n",M(sp1,get));
  printf("%s\n",M(sp2,get));
  printf("%s\n",M(sp3,get));

  /*
    Comparing objects.  Can not use ==, !=, <, <=, > , or >=.
    Use op_eq, op_ne, op_lt, op_le, op_gt, and op_ge
  */
  printf("sp1 %s sp2\n",op_eq(sp1,sp2) ? "is equal" : "is not equal");
  printf("sp1 %s sp2\n",op_ne(sp1,sp2) ? "is not equal" : "is equal");
  printf("sp1 %s sp2\n",op_lt(sp1,sp2) ? "is less than" : "is not less than");
  printf("sp1 %s sp2\n",op_le(sp1,sp2) ? "is less than or equal to" : "is not less than nor equal to");
  printf("sp1 %s sp2\n",op_gt(sp1,sp2) ? "is greater than" : "is not greater than");
  printf("sp1 %s sp2\n",op_ge(sp1,sp2) ? "is greater than or equal to" : "is not greater than nor equal to");

  /* Delete allocated objects */
  delete(sp1);
  delete(sp2);
  delete(sp3);
}
