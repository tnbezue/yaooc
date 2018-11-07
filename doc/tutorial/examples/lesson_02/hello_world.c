#include <string.h>
#include <stdio.h>
#include <yaooc/new.h>

int main(int argc,char* argv[])
{
  char* str=new_array(char,128);
  strcpy(str,"Hello world!");
  printf("%s\n",str);
  delete(str);
}
