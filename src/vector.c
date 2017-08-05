#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <yaooc/vector.h>

void yaooc_vector_ctor(pointer p,va_list args)
{
  call_constructor(p,yaooc_array_container_ctor,va_arg(args,const type_info_t*));
}

iterator yaooc_vector_push_back(pointer p,const_pointer v)
{
	return yaooc_array_container_insert(p,yaooc_array_container_end(p),v);
}

void yaooc_vector_pop_back(pointer this)
{
	yaooc_array_container_erase(this,yaooc_array_container_end(this));
}

iterator yaooc_vector_front(pointer this)
{
	return yaooc_array_container_at(this,0);
}

iterator yaooc_vector_back(pointer this)
{
	return yaooc_array_container_at(this,yaooc_array_container_size(this)-1);
}
