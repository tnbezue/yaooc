#include <yaooc/ordered_array_container.h>
yaooc_ordered_array_container_find_result_t yaooc_ordered_array_container_find_protected(const_pointer __pthis__,const_pointer value)
{
yaooc_ordered_array_container_const_pointer this=__pthis__;(void)this;

      yaooc_ordered_array_container_find_result_t ret;
      ret.found_=false;
      ret.position_=AT(this,0);
    
      size_t lower=0,upper=SIZE(this)-1,middle=0,position=0;
      rich_compare rich_cmp=get_rich_compare(this->type_info_);
      while(lower <= upper && upper != (size_t)-1) {
        middle=(lower+upper)>>1;
        pointer middle_ptr=AT(this,middle);
        if(rich_cmp(middle_ptr,value) < 0) {
          lower=middle+1;
          position=lower;
        } else if(rich_cmp(middle_ptr,value) > 0) {
          upper=middle-1;
          position=middle;
        } else {
          ret.found_=true;
          



          while(middle > 0) {
            middle--;
            if(rich_cmp(AT(this,middle),value)!=0) {
              middle++;
              break;
            }
          }
          position=middle;
          break;
        }
      }
      ret.position_=AT(this,position);
      return ret;
    
}
iterator yaooc_ordered_array_container_find(const_pointer __pthis__,const_pointer value)
{
yaooc_ordered_array_container_const_pointer this=__pthis__;(void)this;

      yaooc_ordered_array_container_find_result_t fr=yaooc_ordered_array_container_find_protected(this,value);
      return fr.found_ ? fr.position_ : END(this);
    
}
iterator yaooc_ordered_array_container_insert(pointer __pthis__,const_iterator pos,const_pointer value)
{
yaooc_ordered_array_container_pointer this=__pthis__;(void)this;

      yaooc_ordered_array_container_find_result_t ret=yaooc_ordered_array_container_find_protected(this,value);
      return yaooc_array_container_insertn(this,ret.position_,1,value);
    
}
iterator yaooc_ordered_array_container_insertn(pointer __pthis__,const_iterator pos,size_t n,const_pointer value)
{
yaooc_ordered_array_container_pointer this=__pthis__;(void)this;

      yaooc_ordered_array_container_find_result_t ret=yaooc_ordered_array_container_find_protected(this,value);
      return yaooc_array_container_insertn(this,ret.position_,n,value);
    
}
iterator yaooc_ordered_array_container_insert_range(pointer __pthis__,const_iterator pos,const_iterator f,const_iterator l)
{
yaooc_ordered_array_container_pointer this=__pthis__;(void)this;

      yaooc_private_iterator first=(yaooc_private_iterator)f;
      yaooc_private_iterator last=(yaooc_private_iterator)l;
      size_t index=(size_t)-1;
      for(;first!=last;first+=TYPE_SIZE(this)) {
        iterator temp=yaooc_ordered_array_container_insert(this,pos,first);
        if(index == (size_t)-1)
          index=INDEX(this,temp);
      }
      return AT(this,index == (size_t)-1 ? SIZE(this) : index);
    
}
size_t yaooc_ordered_array_container_erase_value(pointer __pthis__,const_pointer value)
{
yaooc_ordered_array_container_pointer this=__pthis__;(void)this;

      size_t ret=0;
      yaooc_ordered_array_container_find_result_t fr=yaooc_ordered_array_container_find_protected(this,value);
      if(fr.found_) {
        rich_compare rich_cmp=get_rich_compare(TYPE_INFO(this));
        yaooc_private_const_iterator first=fr.position_;
        yaooc_private_const_iterator last=fr.position_+TYPE_SIZE(this);
        while(last < END(this)) {
          if(rich_cmp(fr.position_,value)<0)
            break;
          last+=TYPE_SIZE(this);
        };
        ret=DISTANCE(TYPE_INFO(this),first,last);
        yaooc_array_container_erase_range(this,first,last);
      }
      return ret;
    
}
void yaooc_ordered_array_container_resize_value(pointer __pthis__,size_t n,const_pointer value)
{
yaooc_ordered_array_container_pointer this=__pthis__;(void)this;

      if(n<SIZE(this)) {
        yaooc_array_container_erase_range(this,AT(this,n),END(this));
      } else {
        yaooc_ordered_array_container_find_result_t fr=yaooc_ordered_array_container_find_protected(this,value);
        yaooc_array_container_insertn(this,fr.position_,n-SIZE(this),value);
      }
    
}
void yaooc_ordered_array_container_resize(pointer __pthis__,size_t n)
{
yaooc_ordered_array_container_pointer this=__pthis__;(void)this;

      yaooc_private_pointer temp=__new_array(TYPE_INFO(this),1);
      yaooc_ordered_array_container_resize_value(this,n,temp);
      delete(temp);
    
}
yaooc_ordered_array_container_class_table_t yaooc_ordered_array_container_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_array_container_class_table,
.type_name_ = (const char*)"yaooc_ordered_array_container_t",
.swap = (void(*)(pointer,pointer)) yaooc_ordered_array_container_swap,
.increase_capacity = (bool(*)(pointer,size_t)) yaooc_ordered_array_container_increase_capacity,
.size_needed = (size_t(*)(const_pointer,size_t)) yaooc_ordered_array_container_size_needed,
.size = (size_t(*)(const_pointer)) yaooc_ordered_array_container_size,
.capacity = (size_t(*)(const_pointer)) yaooc_ordered_array_container_capacity,
.empty = (bool(*)(const_pointer)) yaooc_ordered_array_container_empty,
.begin = (iterator(*)(pointer)) yaooc_ordered_array_container_begin,
.end = (iterator(*)(pointer)) yaooc_ordered_array_container_end,
.cbegin = (const_iterator(*)(const_pointer)) yaooc_ordered_array_container_cbegin,
.cend = (const_iterator(*)(const_pointer)) yaooc_ordered_array_container_cend,
};
const type_info_t __yaooc_ordered_array_container_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_ordered_array_container_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_ordered_array_container_class_table,
.parent_=&__yaooc_array_container_ti
};
const type_info_t* const yaooc_ordered_array_container_ti=&__yaooc_ordered_array_container_ti;
