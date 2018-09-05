#include <stdio.h>
#include <string.h>
#include <yaooc/new.h>

/* Normall, From here <--- */
yaooc_struct(my_string) {
  char* str;
};
void my_string_default_ctor(pointer);
void my_string_dtor(pointer);
void my_string_assign(pointer,const_pointer);
void my_string_copy_ctor(pointer,const_pointer);
bool my_string_less_than_compare(const_pointer,const_pointer);

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
  this->str=src->str==NULL ? NULL : strdup(src->str);
}

bool my_string_less_than_compare(const_pointer p1,const_pointer p2)
{
  my_string_const_pointer bsp1 = p1;
  my_string_const_pointer bsp2 = p2;
  if(bsp1->str == NULL) {
    if(bsp2->str == NULL)
      return false; /* both NULL, equal -- not less */
    else
      return true; /* 1st is NULL, second is not.  NULL is less than not NULL */
  } else if(bsp2 == NULL)
    return false; /* 1st is not NULL, second is NULL. 1st is greater than 2nd, not less */
  return strcmp(bsp1->str,bsp2->str) < 0; /* Both not null, compare the strings */
}

DEFINE_TYPE_INFO(my_string,Y,Y,Y,Y,Y,N,N,N,NULL);


int main(int argc,char* argv[])
{
  /* Create a new my_string */
  my_string_pointer sp1=new(my_string);

  /* Assign value to sp1 */
  sp1->str=strdup("This is a sp1 test string");

  /* Using copy ctor to create another simple string  */
  my_string_pointer sp2=new_copy(sp1);
  sp2->str[12]='2';

  /* Create a new string and assign sp2 value to it.  Same as using copy ctor */
  /* Note that sp3=sp2 should not be used.  Assignment method should be used */
  my_string_pointer sp3=new(my_string);
  assign(sp3,sp2);
  sp3->str[12]='3';

  printf("%s\n",sp1->str);
  printf("%s\n",sp2->str);
  printf("%s\n",sp3->str);

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
