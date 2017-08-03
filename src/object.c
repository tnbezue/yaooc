#include <yaooc/object.h>

#include <string.h>

const char* yaooc_object_isa(const_pointer p) { return "yaooc_object_t"; }

bool yaooc_object_is_descendent(const_pointer p,const char* s)
{
  return strcmp(s,"yaooc_object_t")==0;
}

void yaooc_object_swap(pointer d,pointer s)
{
}

type_info_t __yaooc_object_ti={0,NULL,NULL,NULL,NULL,NULL,NULL,NULL};
const type_info_t* const yaooc_object_ti=&__yaooc_object_ti;

