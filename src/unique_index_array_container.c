#include <yaooc/unique_index_array_container.h>
iterator yaooc_unique_index_array_container_insert(pointer __pthis__,const_iterator pos,const_pointer value)
{
yaooc_unique_index_array_container_pointer this=__pthis__;(void)this;

      return yaooc_unique_index_array_container_insert_range(this,pos,value,((yaooc_private_const_pointer)value)+TYPE_SIZE(this));
    
}
iterator yaooc_unique_index_array_container_insertn(pointer __pthis__,const_iterator pos,size_t n,const_pointer value)
{
yaooc_unique_index_array_container_pointer this=__pthis__;(void)this;




      return yaooc_unique_index_array_container_insert_range(this,pos,value,((yaooc_private_const_pointer)value)+TYPE_SIZE(this));
    
}
iterator yaooc_unique_index_array_container_insert_range(pointer __pthis__,const_iterator pos,const_iterator f,const_iterator l)
{
yaooc_unique_index_array_container_pointer this=__pthis__;(void)this;

      size_t n = DISTANCE(TYPE_INFO(this),f,l);
      size_t idx=INDEX(this,pos);
      yaooc_index_array_container_increase_capacity(this,n);
      yaooc_private_const_iterator first=f;
      yaooc_private_const_iterator last=l;
      yaooc_private_iterator ipos=AT(this,idx);
      size_t fpos=-1;
      for(;first < last;first+=TYPE_SIZE(this)) {
        yaooc_index_array_container_find_result_t fr=yaooc_index_array_container_find_protected(this,first);
        if(!fr.found_) {
          size_t cur_size=SIZE(this);
          yaooc_index_array_container_insert_index(this,fr.lower_index_,1,idx,cur_size);
          yaooc_array_container_insert_space(this,AT(this,idx),1);
          __newp_array_copy_static(ipos,TYPE_INFO(this),first,1);
          idx++;
          ipos+=TYPE_SIZE(this);
        }
        if(fpos == (size_t)-1)
          fpos=fr.lower_index_;
      }
      return AT(this,fpos == (size_t)-1 ? SIZE(this) : fpos);
    
}
void yaooc_unique_index_array_container_yaooc_unique_index_array_container_resize(pointer __pthis__,size_t n)
{
yaooc_unique_index_array_container_pointer this=__pthis__;(void)this;

      pointer temp=__new_array(TYPE_INFO(this),1);
      yaooc_unique_index_array_container_resize_value(this,1,temp);
    
}
void yaooc_unique_index_array_container_resize_value(pointer __pthis__,size_t n,const_pointer value)
{
yaooc_unique_index_array_container_pointer this=__pthis__;(void)this;

      if(n<SIZE(this)) {
        yaooc_index_array_container_erase_range(this,AT(this,n),END(this));
      } else {
        yaooc_unique_index_array_container_insert_range(this,END(this),value,((yaooc_private_const_pointer)value)+TYPE_SIZE(this));
      }
    
}
yaooc_unique_index_array_container_class_table_t yaooc_unique_index_array_container_class_table ={
.parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
.type_name_ = (const char*) "yaooc_unique_index_array_container_t",
.swap = (void(*)(pointer,pointer)) yaooc_unique_index_array_container_swap,
};
const type_info_t __yaooc_unique_index_array_container_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_unique_index_array_container_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_unique_index_array_container_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_unique_index_array_container_ti=&__yaooc_unique_index_array_container_ti;
