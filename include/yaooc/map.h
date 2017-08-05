#ifndef __YAOOC_MAP_INCLUDED__
#define __YAOOC_MAP_INCLUDED__
#include <stdlib.h>

#include <yaooc/unique_index_array_container.h>
#include <yaooc/pair.h>

// Constructor
void yaooc_map_ctor(pointer,va_list);

// Member methods
typedef struct {
  yaooc_private_iterator pos_;
  bool found_;
}yaooc_map_insert_result_t;
yaooc_map_insert_result_t yaooc_map_insert(pointer,const_pointer);
/*iterator yaooc_map_insert_range(pointer,const_iterator,const_iterator);*/
iterator yaooc_map_at(pointer,const_pointer);
const_iterator yaooc_map_cat(const_pointer,const_pointer);
iterator yaooc_map_private_find(pointer p,const_pointer k,yaooc_size_type ks,yaooc_size_type os);

#define MAP_DEFINITION(K,V) \
PAIR_DEFINITION(K,V) \
typedef K ## _ ## V ## _pair_t* K ## _ ## V ## _map_iterator; \
typedef const K ## _ ## V ## _pair_t* K ## _ ## V ## _map_const_iterator; \
V ## _t* K ## _ ## V ## _map_at(pointer,const_pointer); \
const V ## _t* K ## _ ## V ## _map_cat(const_pointer,const_pointer); \
K ## _ ## V ## _map_iterator K ## _ ## V ## _map_find(pointer,const_pointer); \
K ## _ ## V ## _map_const_iterator K ## _ ## V ## _map_cfind(const_pointer,const_pointer); \
K ## _ ## V ## _map_iterator K ## _ ## V ## _map_insert(pointer,const_pointer,const_pointer); \
K ## _ ## V ## _map_iterator K ## _ ## V ## _map_insert_kv(pointer,K ## _t,V ## _t); \
K ## _ ## V ## _map_iterator K ## _ ## V ## _map_insert_kp(pointer,K ## _t,const_pointer); \
K ## _ ## V ## _map_iterator K ## _ ## V ## _map_insert_pv(pointer,const_pointer,V ## _t); \
class_table(K ## _ ## V ## _map) { \
	yaooc_unique_index_array_container_class_members_t; \
	K ## _ ## V ## _map_iterator (*insert)(pointer,const_pointer,const_pointer); \
	K ## _ ## V ## _map_iterator (*insert_kv)(pointer,K ## _t,V ## _t); \
	K ## _ ## V ## _map_iterator (*insert_kp)(pointer,K ## _t,const_pointer); \
	K ## _ ## V ## _map_iterator (*insert_pv)(pointer,const_pointer,V ## _t); \
	V ## _t* (*at)(pointer,const_pointer); \
	const V ## _t* (*cat)(const_pointer,const_pointer); \
	K ## _ ## V ## _map_iterator (*erase) (pointer,iterator); \
	K ## _ ## V ## _map_iterator (*erase_range) (pointer,iterator,iterator); \
	K ## _ ## V ## _map_iterator (*find)(const_pointer,const_pointer); \
	K ## _ ## V ## _map_const_iterator (*cfind)(const_pointer,const_pointer); \
	K ## _ ## V ## _map_iterator (*begin) (pointer); \
	K ## _ ## V ## _map_iterator (*end)(pointer); \
	K ## _ ## V ## _map_const_iterator (*cbegin) (const_pointer); \
	K ## _ ## V ## _map_const_iterator (*cend)(const_pointer); \
};\
class_instance(K ## _ ## V ## _map) { \
  yaooc_unique_index_array_container_instance_members_t; \
};\
class(K ## _ ## V ## _map);\
ISA_DEFINITION(K ## _ ## V ## _map,yaooc_unique_index_array_container)

#define MAP_IMPLEMENTATION(K,V) \
PAIR_IMPLEMENTATION(K,V) \
V ## _t* K ## _ ## V ## _map_at(pointer p,const_pointer k) \
{ \
  K ## _ ## V ## _map_pointer this=p; \
  K ## _ ## V ## _map_iterator pos=yaooc_map_private_find(p,k,sizeof(K ## _t),sizeof(K ## _ ## V ## _map_t)); \
  return pos==M(this,end) ? NULL : &pos->second; \
} \
const V ## _t* K ## _ ## V ## _map_cat(const_pointer p,const_pointer k) \
{ \
  K ## _ ## V ## _map_pointer this=(pointer)p; \
  K ## _ ## V ## _map_iterator pos=yaooc_map_private_find((pointer)p,k,sizeof(K ## _t),sizeof(K ## _ ## V ## _map_t)); \
  return pos==M(this,end) ? NULL : &pos->second; \
} \
K ## _ ## V ## _map_iterator K ## _ ## V ## _map_find(pointer p,const_pointer k) \
{ \
  return yaooc_map_private_find(p,k,sizeof(K ## _t),sizeof(K ## _ ## V ## _map_t)); \
} \
K ## _ ## V ## _map_const_iterator K ## _ ## V ## _map_cfind(const_pointer p,const_pointer k) \
{ \
  return yaooc_map_private_find((pointer)p,k,sizeof(K ## _t),sizeof(K ## _ ## V ## _map_t)); \
} \
K ## _ ## V ## _map_iterator K ## _ ## V ## _map_insert(pointer p,const_pointer k,const_pointer v) \
{ \
  K ## _ ## V ## _pair_t* pair=make_ ## K ## _ ## V ## _pair(k,v); \
  yaooc_map_insert_result_t r=yaooc_map_insert(p,pair); \
  if(r.found_) \
    real_assign_static(&((K ## _ ## V ## _pair_t*)r.pos_)->second,v,V ## _ti); \
  delete(pair); \
  return (K ## _ ## V ## _map_iterator)r.pos_; \
} \
K ## _ ## V ## _map_iterator K ## _ ## V ## _map_insert_kv(pointer p,K ## _t k,V ## _t v) \
{ \
  return K ## _ ## V ## _map_insert(p,&k,&v); \
}\
K ## _ ## V ## _map_iterator K ## _ ## V ## _map_insert_kp(pointer p,K ## _t k,const_pointer v) \
{ \
  return K ## _ ## V ## _map_insert(p,&k,v); \
}\
K ## _ ## V ## _map_iterator K ## _ ## V ## _map_insert_pv(pointer p,const_pointer k,V ## _t v) \
{ \
  return K ## _ ## V ## _map_insert(p,k,&v); \
}\
void K ## _ ## V ## _map_default_ctor(pointer p) { call_constructor(p,yaooc_map_ctor,K ## _ ## V ## _pair_ti); } \
ISA_IMPLEMENTATION(K ## _ ## V ## _map,yaooc_unique_index_array_container) \
K ## _ ## V ## _map_class_members_t K ## _ ## V ## _map_class_members = \
{ \
  { \
    { \
      { \
        { \
          K ## _ ## V ## _map_isa, \
          K ## _ ## V ## _map_is_descendent, \
          yaooc_index_array_container_swap \
        }, \
        YAOOC_ARRAY_CONTAINER_NEW_METHODS \
      } \
    } \
  }, \
	(K ## _ ## V ## _map_iterator (*)(pointer,const_pointer,const_pointer)) K ## _ ## V ## _map_insert, \
	(K ## _ ## V ## _map_iterator (*)(pointer,K ## _t,V ## _t)) K ## _ ## V ## _map_insert_kv, \
	(K ## _ ## V ## _map_iterator (*)(pointer,K ## _t,const_pointer)) K ## _ ## V ## _map_insert_kp, \
	(K ## _ ## V ## _map_iterator (*)(pointer,const_pointer,V ## _t)) K ## _ ## V ## _map_insert_pv, \
	(V ## _t* (*)(pointer,const_pointer)) K ## _ ## V ## _map_at, \
	(const V ## _t* (*)(const_pointer,const_pointer)) K ## _ ## V ## _map_cat, \
	(K ## _ ## V ## _map_iterator (*) (pointer,iterator)) yaooc_unique_index_array_container_erase, \
	(K ## _ ## V ## _map_iterator (*) (pointer,iterator,iterator)) yaooc_unique_index_array_container_erase_range, \
	(K ## _ ## V ## _map_iterator (*)(const_pointer,const_pointer)) K ## _ ## V ## _map_find, \
	(K ## _ ## V ## _map_const_iterator (*)(const_pointer,const_pointer)) K ## _ ## V ## _map_cfind, \
	(K ## _ ## V ## _map_iterator (*) (pointer)) yaooc_array_container_begin, \
	(K ## _ ## V ## _map_iterator (*)(pointer)) yaooc_array_container_end, \
	(K ## _ ## V ## _map_const_iterator (*) (const_pointer)) yaooc_array_container_begin, \
	(K ## _ ## V ## _map_const_iterator (*)(const_pointer)) yaooc_array_container_end, \
};\
DEFINE_TYPE_INFO(K ## _ ## V ## _map,K ## _ ## V ## _map_default_ctor, \
        NULL,NULL,NULL,NULL,&K ## _ ## V ## _map_class_members,\
        yaooc_unique_index_array_container)

#endif
