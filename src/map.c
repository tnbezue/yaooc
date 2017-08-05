#include <yaooc/map.h>

#include <string.h>
#include <stdio.h>

yaooc_map_insert_result_t yaooc_map_insert(pointer p,const_iterator value)
{
	yaooc_unique_index_array_container_pointer this=p;
  yaooc_map_insert_result_t r;
/*  r.found_=false;
  r.pos_=yaooc_unique_index_array_container_insert(p,yaooc_array_container_cend(this),value);*/
	yaooc_index_array_container_find_result_t fr=yaooc_index_array_container_private_find(p,value);
  if(!fr.found_) {
//    yaooc_size_type index=(ipos-(char*)BEGIN(this))/this->type_info_->type_size_;
    yaooc_index_array_container_increase_capacity(this,1);
    yaooc_insert_index(this,fr.index_,1,this->size_,this->size_);
    yaooc_array_container_insert_n(this,yaooc_array_container_end(this),1,value);
    r.pos_=(char*)BEGIN(this) + this->index_[fr.index_]*this->type_info_->type_size_;
    r.found_=false;
  } else {
    r.pos_=(char*)BEGIN(this) + this->index_[fr.index_]*this->type_info_->type_size_;
    r.found_=true;
  }
	return r;

//	return yaooc_unique_index_array_container_insert(p,yaooc_array_container_end(p),value);
}

iterator yaooc_map_insert_range(pointer p,const_iterator first,const_iterator last)
{
	return yaooc_unique_index_array_container_insert_range(p,yaooc_array_container_end(p),first,last);
}

void yaooc_map_ctor(pointer p,va_list args)
{
	call_constructor(p,yaooc_unique_index_array_container_ctor,va_arg(args,const type_info_t*));
}

iterator yaooc_map_private_find(pointer p,const_pointer k,yaooc_size_type ks,yaooc_size_type os)
{
  char obj[os];
  debug(DEBUG_CONTAINER) {
    printf("Key size is %d, obj size is %zu\n",ks,sizeof(obj));
  }
  memcpy(obj,k,ks);
  return yaooc_unique_index_array_container_find(p,obj);
}
/*
iterator yaooc_map_private_insert_pair(pointer p,const_pointer k,const type_info* k_ti,const_pointer v,const type_info* v_ti)
{
  iterator pos
}
*/
/*
iterator yaooc_map_private_find(pointer p,const_pointer k,yaooc_size_type ks,yaooc_size_type os)
{
  char obj[os];
  memcpy(obj,k,ks);
  return yaooc_unique_index_array_container_find(p,obj);
}
*/
