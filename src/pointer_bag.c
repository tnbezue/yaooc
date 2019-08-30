/* Begin YAOOCPP output */

#include <yaooc/pointer_bag.h>

/* Private variables implementation for yaooc_pointer_bag_item */

/* Private methods prototypes for yaooc_pointer_bag_item */

/* Type Info implemmentation for yaooc_pointer_bag_item */
/* Constructors implementation for yaooc_pointer_bag_item */

/* Private methods implementation for yaooc_pointer_bag_item */

/* Protected implementation for yaooc_pointer_bag_item */

/* Type info structure for yaooc_pointer_bag_item */
DEFINE_MIN_TYPE_INFO(yaooc_pointer_bag_item);

/* Private variables implementation for yaooc_pointer_bag */

/* Private methods prototypes for yaooc_pointer_bag */
static yaooc_pointer_bag_iterator yaooc_pointer_bag_find_item(const_pointer,const_pointer);

/* Type Info implemmentation for yaooc_pointer_bag */
void yaooc_pointer_bag_default_ctor(pointer p)
{
  yaooc_pointer_bag_pointer this=p;
//  yaooc_array_container_default_ctor(this);
	call_constructor(this,yaooc_array_container_ctor_ti,yaooc_pointer_bag_item_ti);
}

void yaooc_pointer_bag_dtor(pointer p)
{
  yaooc_pointer_bag_del_all(p);
}

/* Constructors implementation for yaooc_pointer_bag */

/* Private methods implementation for yaooc_pointer_bag */
static yaooc_pointer_bag_iterator yaooc_pointer_bag_find_item(const_pointer p,const_pointer v)
{
  yaooc_pointer_bag_const_pointer this=p;
  yaooc_pointer_bag_const_iterator i=M(this,cbegin);
  for(;i!=M(this,cend);i++) {
    if(i->pointer_==v)
      break;
  }
  return (yaooc_pointer_bag_iterator) i;
}

/* Protected implementation for yaooc_pointer_bag */

pointer yaooc_pointer_bag_newp_array(pointer p,pointer value,const type_info_t* ti,size_t n)
{
  yaooc_pointer_bag_pointer this=p;
  yaooc_pointer_bag_iterator pitem=yaooc_pointer_bag_find_item(this,value);
  if(pitem == M(this,end)) {
    yaooc_pointer_bag_item_t item={value,ti,n};
    yaooc_array_container_insert(this,M(this,cend),&item);
  } else {
    __deletep_array(value,pitem->ti_,pitem->count_);
    pitem->ti_=ti;
    pitem->count_=n;
  }
  __newp_array(value,ti,n);
  return value;
}

void new_ctor_private(yaooc_private_iterator,const type_info_t*,size_t,constructor,va_list);

pointer yaooc_pointer_bag_newp_array_ctor(pointer p,pointer value,const type_info_t* ti,size_t n,constructor ctor,...)
{
  yaooc_pointer_bag_pointer this=p;
  yaooc_pointer_bag_iterator pitem=yaooc_pointer_bag_find_item(this,value);
  if(pitem == M(this,end)) {
    yaooc_pointer_bag_item_t item={value,ti,n};
    yaooc_array_container_insert(this,M(this,cend),&item);
  } else {
    __deletep_array(value,pitem->ti_,pitem->count_);
    pitem->ti_=ti;
    pitem->count_=n;
  }
	va_list args;
	va_start(args,ctor);
	new_ctor_private(value,ti,n,ctor,args);
	va_end(args);
  return value;
}

pointer yaooc_pointer_bag_newp_array_copy_static(pointer p,pointer value,const type_info_t* ti,const_pointer src,size_t n)
{
  yaooc_pointer_bag_pointer this=p;
  yaooc_pointer_bag_iterator pitem=yaooc_pointer_bag_find_item(this,value);
  if(pitem == M(this,end)) {
    yaooc_pointer_bag_item_t item={value,ti,n};
    yaooc_array_container_insert(this,M(this,cend),&item);
  } else {
    __deletep_array(value,pitem->ti_,pitem->count_);
    pitem->ti_=ti;
    pitem->count_=n;
  }
  __newp_array_copy_static(value,ti,src,n);
  return value;
}

/* Table implementation for yaooc_pointer_bag */
pointer yaooc_pointer_bag_add(pointer p,pointer v)
{
  yaooc_pointer_bag_pointer this=p;
  /*
    If pointer already in bag, then ignore skip adding it
    If pointer is in bag, just skip adding it -- may throw exception in future
  */
  if(yaooc_pointer_bag_find_item(this,v)==M(this,cend)) {
    yaooc_pointer_bag_item_t item={v,NULL,0};
    yaooc_array_container_insert(this,M(this,cend),&item);
  }
  return v;
}

pointer yaooc_pointer_bag_add_static(pointer p,pointer v,const type_info_t* ti,size_t n)
{
  /*
    If pointer to static object not already in bag, add it.
    If pointer to static object is in bag, just skip adding it -- may throw exception in future
  */
  yaooc_pointer_bag_pointer this=p;
  yaooc_pointer_bag_iterator pitem=yaooc_pointer_bag_find_item(this,v);
  if(pitem==M(this,end)) {
    yaooc_pointer_bag_item_t item={v,ti,n};
    yaooc_array_container_insert(this,M(this,cend),&item);
  }
  return v;
}

void yaooc_pointer_bag_del(pointer p,const_pointer ptr)
{
  yaooc_pointer_bag_pointer this=p;
  yaooc_pointer_bag_iterator i=yaooc_pointer_bag_find_item(this,ptr);
  if(i!=M(this,end))
    yaooc_array_container_erase(this,i);
}

void yaooc_pointer_bag_del_all(pointer p)
{
  yaooc_pointer_bag_pointer this=p;
  yaooc_pointer_bag_iterator i;
  for(i=M(this,begin);i!=M(this,end);i++) {
    if(i->ti_ == NULL)
      delete_array(i->pointer_);
    else
      __deletep_array(i->pointer_,i->ti_,i->count_);
  }
  this->size_=0;
}

pointer yaooc_pointer_bag_remove(pointer p,pointer v)
{
  yaooc_pointer_bag_pointer this=p;
  void* ret=NULL;
  yaooc_pointer_bag_iterator i=yaooc_pointer_bag_find_item(this,v);
  if(i!=M(this,end)) {
    ret=i->pointer_;
    yaooc_array_container_erase(this,i);
  }
  return ret;
}

void yaooc_pointer_bag_clear(pointer p)
{
  yaooc_array_container_clear(p);
}

/* Class table definition for yaooc_pointer_bag */
yaooc_pointer_bag_class_table_t yaooc_pointer_bag_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_array_container_class_table,
  .type_name_ = (const char*) "yaooc_pointer_bag_t",
  .swap = (void(*)(pointer, pointer)) yaooc_pointer_bag_swap,
  .increase_capacity = (bool(*)(pointer, size_t)) yaooc_pointer_bag_increase_capacity,
  .size_needed = (size_t(*)(const_pointer, size_t)) yaooc_pointer_bag_size_needed,
  .size = (size_t(*)(const_pointer)) yaooc_pointer_bag_size,
  .capacity = (size_t(*)(const_pointer)) yaooc_pointer_bag_capacity,
  .empty = (bool(*)(const_pointer)) yaooc_pointer_bag_empty,
  .begin = (iterator(*)(pointer)) yaooc_pointer_bag_begin,
  .end = (iterator(*)(pointer)) yaooc_pointer_bag_end,
  .cbegin = (const_iterator(*)(const_pointer)) yaooc_pointer_bag_cbegin,
  .cend = (const_iterator(*)(const_pointer)) yaooc_pointer_bag_cend,
  .add = (pointer(*)(pointer, pointer)) yaooc_pointer_bag_add,
  .add_static = (pointer(*)(pointer, pointer, const type_info_t*, size_t)) yaooc_pointer_bag_add_static,
  .del = (void(*)(pointer,const_pointer)) yaooc_pointer_bag_del,
  .del_all = (void(*)(pointer)) yaooc_pointer_bag_del_all,
  .remove = (pointer(*)(pointer, pointer)) yaooc_pointer_bag_remove,
  .clear = (void(*)(pointer)) yaooc_pointer_bag_clear,
};

/* Type info structure for yaooc_pointer_bag */
DEFINE_TYPE_INFO(yaooc_pointer_bag,Y,Y,N,N,N,N,N,Y,yaooc_array_container);

/* End YAOOCPP output */

