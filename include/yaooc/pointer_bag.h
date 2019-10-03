#ifndef __POINTER_BAG_INCLUDED__
#define __POINTER_BAG_INCLUDED__

/* Begin YAOOCPP output */

#include <yaooc/array_container.h>
#include <yaooc/macros.h>

/*
  Struct Definition for yaooc_pointer_bag_item
*/
yaooc_min_struct(yaooc_pointer_bag_item) {
  void* pointer_;
  const type_info_t* ti_;
  unsigned count_;
};

/* Protected prototypes for yaooc_pointer_bag_item */

/* Type Info Prototypes for yaooc_pointer_bag_item */
#define yaooc_pointer_bag_item_default_ctor yaooc_do_nothing_default_ctor
#define yaooc_pointer_bag_item_dtor yaooc_do_nothing_dtor
#define yaooc_pointer_bag_item_copy_ctor yaooc_do_nothing_copy_ctor
#define yaooc_pointer_bag_item_assign yaooc_do_nothing_assign

/* Constructor prototypes for yaooc_pointer_bag_item */

/*
  Class Definition for yaooc_pointer_bag
*/
yaooc_class_table(yaooc_pointer_bag) {
  yaooc_array_container_class_table_t;
  pointer (*add)(pointer, pointer);
  pointer (*add_static)(pointer, pointer, const type_info_t*, size_t);
  void (*del)(pointer,const_pointer);
  void (*del_all)(pointer);
  pointer (*remove)(pointer, pointer);
  void (*clear)(pointer);
};
#define yaooc_pointer_bag_parent_class_table ((yaooc_array_container_class_table_t*)(yaooc_pointer_bag_class_table.parent_class_table_))

yaooc_class_instance(yaooc_pointer_bag) {
  yaooc_array_container_class_instance_t;
};

yaooc_class(yaooc_pointer_bag);

typedef yaooc_pointer_bag_item_t* yaooc_pointer_bag_iterator;
typedef const yaooc_pointer_bag_item_t* yaooc_pointer_bag_const_iterator;

/* Type Info Prototypes for yaooc_pointer_bag */
void yaooc_pointer_bag_default_ctor(pointer);
void yaooc_pointer_bag_dtor(pointer);
#define yaooc_pointer_bag_copy_ctor yaooc_array_container_copy_ctor
#define yaooc_pointer_bag_assign yaooc_array_container_assign

/* Constructors prototypes for yaooc_pointer_bag */

/* Table prototypes for yaooc_pointer_bag */
#define yaooc_pointer_bag_swap yaooc_array_container_swap
#define yaooc_pointer_bag_increase_capacity yaooc_array_container_increase_capacity
#define yaooc_pointer_bag_size_needed yaooc_array_container_size_needed
#define yaooc_pointer_bag_size yaooc_array_container_size
#define yaooc_pointer_bag_capacity yaooc_array_container_capacity
#define yaooc_pointer_bag_empty yaooc_array_container_empty
#define yaooc_pointer_bag_begin yaooc_array_container_begin
#define yaooc_pointer_bag_end yaooc_array_container_end
#define yaooc_pointer_bag_cbegin yaooc_array_container_cbegin
#define yaooc_pointer_bag_cend yaooc_array_container_cend
pointer yaooc_pointer_bag_add(pointer, pointer);
pointer yaooc_pointer_bag_add_static(pointer, pointer, const type_info_t*, size_t);
void yaooc_pointer_bag_del_all(pointer);
void yaooc_pointer_bag_del(pointer,const_pointer);
pointer yaooc_pointer_bag_remove(pointer, pointer);
void yaooc_pointer_bag_clear(pointer);

/* Protected prototypes for yaooc_pointer_bag */

/* End YAOOCPP output */
#define pb_init()         yaooc_pointer_bag_pointer local_pb=__new_array(yaooc_pointer_bag_ti,1)

#define pb_save(P)        yaooc_pointer_bag_add(local_pb,P)
#define pb_new(T)         pb_save(new(T))
#define pb_new_array(T,N) pb_save(new_array(T,N))
#define pb_new_copy(P)    pb_save(new_copy(P))
#define pb_new_array_copy(P,N)    pb_save(new_array_copy(P,N))
#define pb_new_ctor(T,CON,...)     pb_save(new_ctor(T,CON,## __VA_ARGS__))
#define pb_new_array_ctor(T,N,...)     pb_save(new_array_ctor(T,N,CON,## __VA_ARGS__))

#define pb_save_static(P,T)       yaooc_pointer_bag_add_static(local_pb,P,T ## _ti,1)
#define pb_save_array_static(P,T,N)       yaooc_pointer_bag_add_static(local_pb,P,T ## _ti,N)
#define pb_newp(P,T)      yaooc_pointer_bag_newp_array(local_pb,P,T ## _ti,1)
#define pb_newp_array(P,T,N)      yaooc_pointer_bag_newp_array(local_pb,P,T ## _ti,N)
#define pb_newp_copy_static(P,T,CP)      yaooc_pointer_bag_newp_array_copy_static(local_pb,P,T ## _ti,1)
#define pb_newp_array_copy_static(P,T,CP,N)      yaooc_pointer_bag_newp_array_copy_static(local_pb,P,T ## _ti,N)
#define pb_newp_ctor(P,T,CON,...)      yaooc_pointer_bag_newp_array_ctor(local_pb,P,T,1,CON,## __VA_ARGG__)
#define pb_newp_array_ctor(P,T,N,CON,...)      yaooc_pointer_bag_newp_array_ctor(local_pb,P,T,N,CON,## __VA_ARGG__)

#define pb_delete()  yaooc_pointer_bag_del_all(local_pb)
#define pb_exit()   delete(local_pb)

#endif
