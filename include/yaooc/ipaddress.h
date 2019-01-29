#ifndef __IPADDRESS_INCLUDED__
#define __IPADDRESS_INCLUDED__

/* Begin YAOOCPP output */

#include <yaooc/object.h>
#include <yaooc/stream.h>

/*
  Class Definition for yaooc_ipaddress
*/
typedef enum { UNDEFINED=0, IP4, IP6 } iptype_t;
yaooc_class_table(yaooc_ipaddress) {
  yaooc_object_class_table_t;
  void (*set)(pointer, const char*);
  bool (*is_ip4)(const_pointer);
  bool (*is_ip6)(const_pointer);
  bool (*is_undefined)(const_pointer);
  bool (*is_loopback)(const_pointer);
  iptype_t (*type)(const_pointer);
};
#define yaooc_ipaddress_parent_class_table ((yaooc_object_class_table_t*)(yaooc_ipaddress_class_table.parent_class_table_))

yaooc_class_instance(yaooc_ipaddress) {
  yaooc_object_class_instance_t;
  iptype_t type_;
  char buf_[16];
};

yaooc_class(yaooc_ipaddress);

/* Type Info Prototypes for yaooc_ipaddress */
void yaooc_ipaddress_default_ctor(pointer);
void yaooc_ipaddress_dtor(pointer);
void yaooc_ipaddress_copy_ctor(pointer,const_pointer);
void yaooc_ipaddress_assign(pointer,const_pointer);
bool yaooc_ipaddress_less_than_compare(const_pointer,const_pointer);
void yaooc_ipaddress_to_stream(const_pointer,ostream_pointer);

/* Constructors prototypes for yaooc_ipaddress */
void yaooc_ipaddress_ctor_ccs(pointer,va_list);

/* Table prototypes for yaooc_ipaddress */
#define yaooc_ipaddress_swap yaooc_object_swap
void yaooc_ipaddress_set(pointer, const char*);
bool yaooc_ipaddress_is_ip4(const_pointer);
bool yaooc_ipaddress_is_ip6(const_pointer);
bool yaooc_ipaddress_is_undefined(const_pointer);
bool yaooc_ipaddress_is_loopback(const_pointer);
iptype_t yaooc_ipaddress_type(const_pointer);

/* Protected prototypes for yaooc_ipaddress */

/* End YAOOCPP output */


#endif
