#include <yaooc/ordered_map.h>

#include <string.h>
#include <stdio.h>

yaooc_ordered_container_find_result_t yaooc_ordered_map_insert(pointer p,const_iterator value)
{
	yaooc_unique_ordered_container_pointer this=p;
	yaooc_unique_ordered_container_find_result_t fr=yaooc_unique_ordered_container_find_private(p,value);
  if(!fr.found_) {
    size_t index=INDEX(this,fr.position_);
    if(yaooc_unique_ordered_container_increase_capacity(this,1))
      fr.position_=BEGIN(this)+index*this->type_info_->type_size_;
		yaooc_container_insert_n_private(this,index,1,value);
	}
	return fr;

//  return yaooc_unique_ordered_container_insert(p,yaooc_container_end(p),value);
}

iterator yaooc_ordered_map_insert_range(pointer p,const_iterator first,const_iterator last)
{
	return yaooc_unique_ordered_container_insert_range(p,yaooc_container_end(p),first,last);
}

void yaooc_ordered_map_ctor(pointer p,va_list args)
{
	call_constructor(p,yaooc_unique_ordered_container_ctor,va_arg(args,const type_info_t*));
}

iterator yaooc_ordered_map_private_find(pointer p,const_pointer k,size_t ks,size_t os)
{
  char obj[os];
  memcpy(obj,k,ks);
  return yaooc_unique_ordered_container_find(p,obj);
}

/*iterator yaooc_ordered_map_private_insert_pair(pointer p,const_pointer k,const type_info* k_ti,const_pointer v,const type_info* v_ti)
{
  iterator pos
}
*/
/*
iterator yaooc_ordered_map_private_find(pointer p,const_pointer k,size_t ks,size_t os)
{
  char obj[os];
  memcpy(obj,k,ks);
  return yaooc_unique_container_find(p,obj);
}
*/
