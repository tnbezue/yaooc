#ifndef __IPADDRESS_INCLUDED__
#define __IPADDRESS_INCLUDED__

#include <yaooc/object.h>

#include <yaooc/stream.h>

yaooc_class_table(yaooc_ipaddress) {
  yaooc_object_class_table_t;
void (*set)(pointer,const char*);
bool (*is_ip4)(const_pointer);
bool (*is_ip6)(const_pointer);
bool (*is_undefined)(const_pointer);
bool (*is_loopback)(const_pointer);
int (*type)(const_pointer);
};
#define yaooc_ipaddress_parent_class_table ((yaooc_object_class_table_t*)(yaooc_ipaddress_class_table.parent_class_table_))

yaooc_class_instance(yaooc_ipaddress) {
int type_;
char buf_[16];
};

yaooc_class(yaooc_ipaddress);
void yaooc_ipaddress_default_ctor(pointer);
void yaooc_ipaddress_copy_ctor(pointer,const_pointer);
void yaooc_ipaddress_assign(pointer,const_pointer);
int yaooc_ipaddress_rich_compare(const_pointer,const_pointer);
void yaooc_ipaddress_to_stream(const_pointer,ostream_pointer);
void yaooc_ipaddress_ctor_ccs(pointer,va_list);
#define yaooc_ipaddress_swap yaooc_object_swap
 void yaooc_ipaddress_set(pointer,const char*);
 bool yaooc_ipaddress_is_ip4(const_pointer);
 bool yaooc_ipaddress_is_ip6(const_pointer);
 bool yaooc_ipaddress_is_undefined(const_pointer);
 bool yaooc_ipaddress_is_loopback(const_pointer);
 int yaooc_ipaddress_type(const_pointer);

#endif
