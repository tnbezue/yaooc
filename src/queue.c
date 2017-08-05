#include <yaooc/queue.h>

pointer yaooc_queue_front(pointer p)
{
  return yaooc_array_container_begin(p);
}

pointer yaooc_queue_back(pointer p)
{
  return yaooc_array_container_end(p);
}

void yaooc_queue_push(pointer p,const_pointer v)
{
  yaooc_array_container_insert(p,yaooc_array_container_end(p),v);
}

void yaooc_queue_pop(pointer p)
{
  yaooc_array_container_erase(p,yaooc_array_container_begin(p));
}
