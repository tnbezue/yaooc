#include <yaooc/ipaddress.h>
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#endif
#include <yaooc/ipaddress.h>
#include <string.h>


void yaooc_ipaddress_default_ctor(pointer __pthis__)
{
yaooc_ipaddress_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_ipaddress);



      this->type_ = 0;
      memset(this->buf_,0,16);
    
}
void yaooc_ipaddress_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaooc_ipaddress_pointer this=__pthis__;(void)this;
yaooc_ipaddress_const_pointer src=__psrc__;(void)src;


call_default_ctor_static(this,yaooc_ipaddress);
assign_static(this,src,yaooc_ipaddress);

}
void yaooc_ipaddress_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_ipaddress_pointer this=__pthis__;(void)this;
yaooc_ipaddress_const_pointer src=__psrc__;(void)src;


      this->type_ = src->type_;
      memcpy(this->buf_,src->buf_,16);
    
}
int yaooc_ipaddress_rich_compare(const_pointer __plhs__,const_pointer __prhs__)
{
yaooc_ipaddress_const_pointer lhs=__plhs__;(void)lhs;
yaooc_ipaddress_const_pointer rhs=__prhs__;(void)rhs;


      return memcmp(lhs->buf_,rhs->buf_,lhs->type_==1 ? 4 : 16);
    
}
void yaooc_ipaddress_to_stream(const_pointer __pthis__,ostream_pointer __pstrm__)
{
yaooc_ipaddress_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__pstrm__;(void)ostrm;


      char temp[INET6_ADDRSTRLEN];
      switch(this->type_) {

        case AF_INET:
          inet_ntop(AF_INET,(void*)this->buf_,temp,INET_ADDRSTRLEN);
          break;

        case AF_INET6:
          inet_ntop(AF_INET6,(void*)this->buf_,temp,INET6_ADDRSTRLEN);
          break;

        default:
          strcpy(temp,"(nil)");
          break;
      }
      M(ostrm,printf,temp);
    
}
void yaooc_ipaddress_ctor_ccs(pointer __pthis,va_list __con_args__){
yaooc_ipaddress_pointer this=__pthis;(void)this;
const char* ip_str = va_arg(__con_args__,const char*);

call_default_ctor_static(this,yaooc_ipaddress);


      M(this,set,ip_str);
    
}
void yaooc_ipaddress_set(pointer __pthis__,const char* ip_str)
{
yaooc_ipaddress_pointer this=__pthis__;(void)this;
#define super() yaooc_ipaddress_parent_class_table->set(this,ip_str)
#define PM(method,...) CTM((*yaooc_ipaddress_parent_class_table),this,method,## __VA_ARGS__)


      this->type_=0;
      if (inet_pton(AF_INET, ip_str, (void*)this->buf_ ) == 1) {
        this->type_ = AF_INET;
      } else if (inet_pton(AF_INET6, ip_str, (void*)this->buf_ ) == 1) {
        this->type_ = AF_INET6;
      }
    
#undef PM
#undef super
}
bool yaooc_ipaddress_is_ip4(const_pointer __pthis__)
{
yaooc_ipaddress_const_pointer this=__pthis__;(void)this;
#define super() yaooc_ipaddress_parent_class_table->is_ip4(this)
#define PM(method,...) CTM((*yaooc_ipaddress_parent_class_table),this,method,## __VA_ARGS__)


      return this->type_==AF_INET;
    
#undef PM
#undef super
}
bool yaooc_ipaddress_is_ip6(const_pointer __pthis__)
{
yaooc_ipaddress_const_pointer this=__pthis__;(void)this;
#define super() yaooc_ipaddress_parent_class_table->is_ip6(this)
#define PM(method,...) CTM((*yaooc_ipaddress_parent_class_table),this,method,## __VA_ARGS__)


      return this->type_==AF_INET6;
    
#undef PM
#undef super
}
bool yaooc_ipaddress_is_undefined(const_pointer __pthis__)
{
yaooc_ipaddress_const_pointer this=__pthis__;(void)this;
#define super() yaooc_ipaddress_parent_class_table->is_undefined(this)
#define PM(method,...) CTM((*yaooc_ipaddress_parent_class_table),this,method,## __VA_ARGS__)


      return this->type_!=AF_INET && this->type_!=AF_INET6;
    
#undef PM
#undef super
}
bool yaooc_ipaddress_is_loopback(const_pointer __pthis__)
{
yaooc_ipaddress_const_pointer this=__pthis__;(void)this;
#define super() yaooc_ipaddress_parent_class_table->is_loopback(this)
#define PM(method,...) CTM((*yaooc_ipaddress_parent_class_table),this,method,## __VA_ARGS__)


      bool ret=false;
      char buf[16];
      switch(this->type_) {
        case AF_INET:
          inet_pton(AF_INET, "127.0.0.1", buf );
          ret = memcmp(this->buf_,buf,4)==0;
          break;

        case AF_INET6:
          inet_pton(AF_INET6, "::1", buf );
          ret = memcmp(this->buf_,buf,16)==0;
          break;
      }
      return ret;
    
#undef PM
#undef super
}
int yaooc_ipaddress_type(const_pointer __pthis__)
{
yaooc_ipaddress_const_pointer this=__pthis__;(void)this;
#define super() yaooc_ipaddress_parent_class_table->type(this)
#define PM(method,...) CTM((*yaooc_ipaddress_parent_class_table),this,method,## __VA_ARGS__)


      return this->type_;
    
#undef PM
#undef super
}
yaooc_ipaddress_class_table_t yaooc_ipaddress_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_object_class_table,
.type_name_ = (const char*)"yaooc_ipaddress_t",
.swap = (void(*)(pointer,pointer)) yaooc_ipaddress_swap,
.set = (void(*)(pointer,const char*)) yaooc_ipaddress_set,
.is_ip4 = (bool(*)(const_pointer)) yaooc_ipaddress_is_ip4,
.is_ip6 = (bool(*)(const_pointer)) yaooc_ipaddress_is_ip6,
.is_undefined = (bool(*)(const_pointer)) yaooc_ipaddress_is_undefined,
.is_loopback = (bool(*)(const_pointer)) yaooc_ipaddress_is_loopback,
.type = (int(*)(const_pointer)) yaooc_ipaddress_type,
};
const type_info_t __yaooc_ipaddress_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_ipaddress_t),
.rich_compare_=yaooc_ipaddress_rich_compare,
.to_stream_=yaooc_ipaddress_to_stream,
.from_stream_=NULL,
.default_ctor_=yaooc_ipaddress_default_ctor,
.dtor_=NULL,
.copy_ctor_=yaooc_ipaddress_copy_ctor,
.assign_=yaooc_ipaddress_assign,
.class_table_=(const class_table_t*) &yaooc_ipaddress_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_ipaddress_ti=&__yaooc_ipaddress_ti;
