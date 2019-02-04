/* Begin YAOOCPP output */

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#endif
#include <yaooc/ipaddress.h>
#include <string.h>

/* Private variables implementation for yaooc_ipaddress */

/* Private methods prototypes for yaooc_ipaddress */

/* Type Info implemmentation for yaooc_ipaddress */
void yaooc_ipaddress_default_ctor(pointer p)
{
  yaooc_ipaddress_pointer this=p;
  this->type_ = 0;
  memset(this->buf_,0,16);
}

void yaooc_ipaddress_dtor(pointer p)
{
//  yaooc_ipaddress_pointer this=p;
}

void yaooc_ipaddress_copy_ctor(pointer p,const_pointer s)
{
  yaooc_ipaddress_default_ctor(p);
  yaooc_ipaddress_assign(p,s);
}

void yaooc_ipaddress_assign(pointer p,const_pointer s)
{
  yaooc_ipaddress_pointer this=p;
  yaooc_ipaddress_const_pointer src=s;
  this->type_ = src->type_;
  memcpy(this->buf_,src->buf_,16);
}

bool yaooc_ipaddress_less_than_compare(const_pointer p1,const_pointer p2)
{
  yaooc_ipaddress_const_pointer vp1=p1;
  yaooc_ipaddress_const_pointer vp2=p2;
	return memcmp(vp1->buf_,vp2->buf_,vp1->type_==1 ? 4 : 16) < 0;
}

void yaooc_ipaddress_to_stream(const_pointer p,ostream_pointer o){
  yaooc_ipaddress_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
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

/* Constructors implementation for yaooc_ipaddress */
void yaooc_ipaddress_ctor_ccs(pointer p,va_list args)
{
//  yaooc_ipaddress_pointer this=p;
	yaooc_ipaddress_set(p,va_arg(args, const char*));
}


/* Private methods implementation for yaooc_ipaddress */

/* Protected implementation for yaooc_ipaddress */

/* Table implementation for yaooc_ipaddress */
void yaooc_ipaddress_set(pointer p,const char* ip_str)
{
  yaooc_ipaddress_pointer this=p;
	this->type_=0;
	if (inet_pton(AF_INET, ip_str, this->buf_ ) == 1) {
		this->type_ = AF_INET;
	} else if (inet_pton(AF_INET6, ip_str, this->buf_ ) == 1) {
		this->type_ = AF_INET6;
	}
}

bool yaooc_ipaddress_is_ip4(const_pointer p)
{
  return ((yaooc_ipaddress_const_pointer)p)->type_==AF_INET;
}

bool yaooc_ipaddress_is_ip6(const_pointer p)
{
  return ((yaooc_ipaddress_const_pointer)p)->type_==AF_INET6;
}

bool yaooc_ipaddress_is_undefined(const_pointer p)
{
  return ((yaooc_ipaddress_const_pointer)p)->type_!=AF_INET && ((yaooc_ipaddress_const_pointer)p)->type_!=AF_INET;
}

bool yaooc_ipaddress_is_loopback(const_pointer p)
{
	yaooc_ipaddress_const_pointer this = p;
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
}

int yaooc_ipaddress_type(const_pointer p)
{
	return ((yaooc_ipaddress_const_pointer)p)->type_;
}


/* Class table definition for yaooc_ipaddress */
yaooc_ipaddress_class_table_t yaooc_ipaddress_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "yaooc_ipaddress_t",
  .swap = (void(*)(pointer, pointer)) yaooc_ipaddress_swap,
  .set = (void(*)(pointer, const char*)) yaooc_ipaddress_set,
  .is_ip4 = (bool(*)(const_pointer)) yaooc_ipaddress_is_ip4,
  .is_ip6 = (bool(*)(const_pointer)) yaooc_ipaddress_is_ip6,
  .is_undefined = (bool(*)(const_pointer)) yaooc_ipaddress_is_undefined,
  .is_loopback = (bool(*)(const_pointer)) yaooc_ipaddress_is_loopback,
  .type = (int(*)(const_pointer)) yaooc_ipaddress_type,
};

/* Type info structure for yaooc_ipaddress */
DEFINE_TYPE_INFO(yaooc_ipaddress,Y,Y,Y,Y,Y,Y,N,Y,yaooc_object);

/* End YAOOCPP output */

