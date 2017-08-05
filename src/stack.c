#include <yaooc/stack.h>

pointer yaooc_stack_top(pointer p)
{
  return yaooc_array_container_begin(p);
}

void yaooc_stack_push(pointer p,const_pointer v)
{
  yaooc_array_container_insert(p,yaooc_array_container_begin(p),v);
}

void yaooc_stack_pop(pointer p)
{
  yaooc_array_container_erase(p,yaooc_array_container_begin(p));
}
