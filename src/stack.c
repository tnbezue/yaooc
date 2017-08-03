#include <yaooc/stack.h>

pointer yaooc_stack_top(pointer p)
{
  return yaooc_container_begin(p);
}

void yaooc_stack_push(pointer p,const_pointer v)
{
  yaooc_container_insert(p,yaooc_container_begin(p),v);
}

void yaooc_stack_pop(pointer p)
{
  yaooc_container_erase(p,yaooc_container_begin(p));
}
