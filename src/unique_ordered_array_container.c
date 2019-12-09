#include <yaooc/unique_ordered_array_container.h>
#include <stdio.h>
#include <stdlib.h>


iterator yaooc_unique_ordered_array_container_insert(pointer __pthis__,const_iterator pos,const_pointer value)
{
yaooc_unique_ordered_array_container_pointer this=__pthis__;(void)this;

      yaooc_ordered_array_container_find_result_t ret=yaooc_ordered_array_container_find_protected(this,value);
      size_t ofs=INDEX(this,ret.position_);
      if(!ret.found_) {
        yaooc_array_container_insertn(this,ret.position_,1,value);
      }
      return AT(this,ofs);
    
}
iterator yaooc_unique_ordered_array_container_insertn(pointer __pthis__,const_iterator pos,size_t n,const_pointer val)
{
yaooc_unique_ordered_array_container_pointer this=__pthis__;(void)this;

      return yaooc_unique_ordered_array_container_insert(this,pos,val); 
    
}
iterator yaooc_unique_ordered_array_container_insert_range(pointer __pthis__,const_iterator pos,const_iterator f,const_iterator l)
{
yaooc_unique_ordered_array_container_pointer this=__pthis__;(void)this;

      yaooc_private_iterator first=(yaooc_private_iterator)f;
      yaooc_private_iterator last=(yaooc_private_iterator)l;
      size_t index=(size_t)-1;
      for(;first!=last;first+=TYPE_SIZE(this)) {
        iterator temp=yaooc_unique_ordered_array_container_insert(this,pos,first);
        if(index == (size_t)-1)
          index=INDEX(this,temp);
      }
      return AT(this,index == (size_t)-1 ? SIZE(this) : index);
    
}
void yaooc_unique_ordered_array_container_resize_value(pointer __pthis__,size_t n,const_pointer value)
{
yaooc_unique_ordered_array_container_pointer this=__pthis__;(void)this;

      if(n < SIZE(this)) {
        yaooc_array_container_erase_range(this,AT(this,n),END(this));
      } else if (n > SIZE(this)) {
        yaooc_unique_ordered_array_container_insertn(this,END(this),1,value);
      }
    
}
void yaooc_unique_ordered_array_container_resize(pointer __pthis__,size_t n)
{
yaooc_unique_ordered_array_container_pointer this=__pthis__;(void)this;

      pointer temp=__new_array(TYPE_INFO(this),1);
      yaooc_unique_ordered_array_container_resize_value(this,1,temp);
      delete(temp);
    
}
yaooc_unique_ordered_array_container_class_table_t yaooc_unique_ordered_array_container_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_ordered_array_container_class_table,
.type_name_ = (const char*)"yaooc_unique_ordered_array_container_t",
.swap = (void(*)(pointer,pointer)) yaooc_unique_ordered_array_container_swap,
.increase_capacity = (bool(*)(pointer,size_t)) yaooc_unique_ordered_array_container_increase_capacity,
.size_needed = (size_t(*)(const_pointer,size_t)) yaooc_unique_ordered_array_container_size_needed,
.size = (size_t(*)(const_pointer)) yaooc_unique_ordered_array_container_size,
.capacity = (size_t(*)(const_pointer)) yaooc_unique_ordered_array_container_capacity,
.empty = (bool(*)(const_pointer)) yaooc_unique_ordered_array_container_empty,
.begin = (iterator(*)(pointer)) yaooc_unique_ordered_array_container_begin,
.end = (iterator(*)(pointer)) yaooc_unique_ordered_array_container_end,
.cbegin = (const_iterator(*)(const_pointer)) yaooc_unique_ordered_array_container_cbegin,
.cend = (const_iterator(*)(const_pointer)) yaooc_unique_ordered_array_container_cend,
};
const type_info_t __yaooc_unique_ordered_array_container_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_unique_ordered_array_container_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_unique_ordered_array_container_class_table,
.parent_=&__yaooc_ordered_array_container_ti
};
const type_info_t* const yaooc_unique_ordered_array_container_ti=&__yaooc_unique_ordered_array_container_ti;
