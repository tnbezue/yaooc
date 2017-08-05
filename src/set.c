#include <yaooc/set.h>

#include <string.h>
#include <stdio.h>

void yaooc_set_ctor(pointer p,va_list args)
{
  call_constructor(p,yaooc_unique_index_array_container_ctor,va_arg(args,const type_info_t*));
}

iterator yaooc_set_insert(pointer p,const_iterator value)
{
	return yaooc_unique_index_array_container_insert(p,yaooc_array_container_end(p),value);
}
iterator yaooc_set_insert_range(pointer p,const_iterator first,const_iterator last)
{
	return yaooc_unique_index_array_container_insert_range(p,yaooc_array_container_end(p),first,last);
}

iterator yaooc_set_erase(pointer p,iterator pos)
{
	return yaooc_array_container_erase(p,pos);
}

iterator yaooc_set_erase_range(pointer p,iterator first,iterator last)
{
	return yaooc_array_container_erase_range(p,first,last);
}
iterator yaooc_set_find(pointer p,const_iterator value)
{
	iterator end=yaooc_array_container_end(p);
	yaooc_index_array_container_find_result_t fr=yaooc_index_array_container_private_find(p,value);
	if(!fr.found_)
		return end;
	return yaooc_index_array_container_begin(p)+fr.index_;
}
/*
const_iterator yaooc_set_cfind(const_pointer p,const_iterator value)
{
	const_iterator end=yaooc_array_container_cend(p);
	yaooc_index_array_container_find_result_t fr=yaooc_index_array_container_private_find((pointer)p,value);
	if(!fr.found_)
		return end;
	return yaooc_index_array_container_cbegin(p)+fr.index_;

}
*/
pointer yaooc_set_sunion(const_pointer p,const_pointer o)
{
	return (pointer)p;
}
