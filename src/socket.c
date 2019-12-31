#include <yaooc/socket.h>
yaooc_socket_exception_class_table_t yaooc_socket_exception_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_exception_class_table,
.type_name_ = (const char*)"yaooc_socket_exception_t",
.swap = (void(*)(pointer,pointer)) yaooc_socket_exception_swap,
.what = (const char*(*)(const_pointer)) yaooc_socket_exception_what,
.error_code = (int(*)(const_pointer)) yaooc_socket_exception_error_code,
};
const type_info_t __yaooc_socket_exception_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_socket_exception_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_socket_exception_class_table,
.parent_=&__yaooc_exception_ti
};
const type_info_t* const yaooc_socket_exception_ti=&__yaooc_socket_exception_ti;
#ifdef _WIN32
void yaooc_socket_startup()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);				
	WSAStartup(wVersionRequested, &wsaData);  
}

void yaooc_socket_cleanup() { WSACleanup(); }

#else
#include <poll.h>
#endif


void yaooc_socket_default_ctor(pointer __pthis__)
{
yaooc_socket_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_socket);



      THROW(new_ctor(yaooc_socket_exception,yaooc_socket_exception_ctor_v,21,"Creating a instance of Socket is not allowed"));
    
}
void yaooc_socket_dtor(pointer __pthis__)
{
yaooc_socket_pointer this=__pthis__;(void)this;


      M(this,close);
    
}
int yaooc_socket_setsockopt(pointer __pthis__,int level,int option_name,const void* option_value,socklen_t option_len)
{
yaooc_socket_pointer this=__pthis__;(void)this;

      return this->sock_fd_ == -1 ? 0 : setsockopt(this->sock_fd_,level,option_name,option_value,option_len);
    
}
void yaooc_socket_close(pointer __pthis__)
{
yaooc_socket_pointer this=__pthis__;(void)this;
#define super() yaooc_socket_parent_class_table->close(this)
#define PM(method,...) CTM((*yaooc_socket_parent_class_table),this,method,## __VA_ARGS__)


      if(this->sock_fd_ >= 0) {
        close(this->sock_fd_);
        this->sock_fd_=-1;
      }
    
#undef PM
#undef super
}
int yaooc_socket_send(pointer __pthis__,const char* str)
{
yaooc_socket_pointer this=__pthis__;(void)this;
#define super() yaooc_socket_parent_class_table->send(this,str)
#define PM(method,...) CTM((*yaooc_socket_parent_class_table),this,method,## __VA_ARGS__)


      return str == NULL ? 0 : M(this,sendn,str,strlen(str));
    
#undef PM
#undef super
}
int yaooc_socket_sendn(pointer __pthis__,const void* buffer,size_t n)
{
yaooc_socket_pointer this=__pthis__;(void)this;
#define super() yaooc_socket_parent_class_table->sendn(this,buffer,n)
#define PM(method,...) CTM((*yaooc_socket_parent_class_table),this,method,## __VA_ARGS__)


      int ret=-1;
      if(this->sock_fd_ > 0) {
        ret=sendto(this->sock_fd_,buffer,n,0,NULL,0);
      }
      return ret;
    
#undef PM
#undef super
}
int yaooc_socket_poll(pointer __pthis__,int timeout_ms)
{
yaooc_socket_pointer this=__pthis__;(void)this;
#define super() yaooc_socket_parent_class_table->poll(this,timeout_ms)
#define PM(method,...) CTM((*yaooc_socket_parent_class_table),this,method,## __VA_ARGS__)


      int ret=0;
      if(this->sock_fd_ >=0) {
        struct pollfd pfd;
        pfd.fd = this->sock_fd_;
        pfd.events = POLLIN|POLLOUT|POLLHUP|POLLERR|POLLNVAL;
        pfd.revents = 0;
#ifdef _WIN32
        ret = WSAPoll(&pfd,1,timeout_ms);
#else
        ret = poll(&pfd,1,timeout_ms);
#endif
      }
      return ret;
    
#undef PM
#undef super
}
int yaooc_socket_recv(pointer __pthis__,void* buffer,int n)
{
yaooc_socket_pointer this=__pthis__;(void)this;
#define super() yaooc_socket_parent_class_table->recv(this,buffer,n)
#define PM(method,...) CTM((*yaooc_socket_parent_class_table),this,method,## __VA_ARGS__)


      int ret=0;
      if(this->sock_fd_ >= 0)
        ret = recvfrom(this->sock_fd_,(char*)buffer,n,0,NULL,0);
      return ret;
    
#undef PM
#undef super
}
int yaooc_socket_blocking(pointer __pthis__)
{
yaooc_socket_pointer this=__pthis__;(void)this;
#define super() yaooc_socket_parent_class_table->blocking(this)
#define PM(method,...) CTM((*yaooc_socket_parent_class_table),this,method,## __VA_ARGS__)


      if(this->sock_fd_>=0)  {
#ifdef	__WIN32__
        u_long flag=0;
        return ioctlsocket(this->sock_fd_,FIONBIO,&flag);
#else
        uint32_t flag=0;
        return ioctl(this->sock_fd_,FIONBIO,&flag);
#endif
      }
      return -1;
    
#undef PM
#undef super
}
int yaooc_socket_non_blocking(pointer __pthis__)
{
yaooc_socket_pointer this=__pthis__;(void)this;
#define super() yaooc_socket_parent_class_table->non_blocking(this)
#define PM(method,...) CTM((*yaooc_socket_parent_class_table),this,method,## __VA_ARGS__)


      if(this->sock_fd_>=0)  {
#ifdef	__WIN32__
        u_long flag=1;
        return ioctlsocket(this->sock_fd_,FIONBIO,&flag);
#else
        uint32_t flag=1;
        return ioctl(this->sock_fd_,FIONBIO,&flag);
#endif
      }
      return -1;
    
#undef PM
#undef super
}
int yaooc_socket_async(pointer __pthis__)
{
yaooc_socket_pointer this=__pthis__;(void)this;
#define super() yaooc_socket_parent_class_table->async(this)
#define PM(method,...) CTM((*yaooc_socket_parent_class_table),this,method,## __VA_ARGS__)


      if(this->sock_fd_>=0) {
#ifdef	__WIN32__
        return 0;
#else
        int flag = 1;
        pid_t pid = getpid();
        if(ioctl(this->sock_fd_,FIOSETOWN,&pid) != -1)
          return ioctl(this->sock_fd_,FIOASYNC,&flag);
#endif
      }
      return -1;
    
#undef PM
#undef super
}
int yaooc_socket_sync(pointer __pthis__)
{
yaooc_socket_pointer this=__pthis__;(void)this;
#define super() yaooc_socket_parent_class_table->sync(this)
#define PM(method,...) CTM((*yaooc_socket_parent_class_table),this,method,## __VA_ARGS__)


      if(this->sock_fd_>=0) {
#ifdef	__WIN32__
        return 0;
#else
        int flag = 0;
        pid_t pid = getpid();
        if(ioctl(this->sock_fd_,FIOSETOWN,&pid) != -1)
          return ioctl(this->sock_fd_,FIOASYNC,&flag);
#endif
      }
      return -1;
    
#undef PM
#undef super
}
void yaooc_socket_debug(pointer __pthis__,bool v)
{
yaooc_socket_pointer this=__pthis__;(void)this;
#define super() yaooc_socket_parent_class_table->debug(this,v)
#define PM(method,...) CTM((*yaooc_socket_parent_class_table),this,method,## __VA_ARGS__)


      int option_value = v ? 1 : 0;
      yaooc_socket_setsockopt(this,SOL_SOCKET,SO_DEBUG,&option_value,sizeof(int));
    
#undef PM
#undef super
}
void yaooc_socket_reuseaddr(pointer __pthis__,bool v)
{
yaooc_socket_pointer this=__pthis__;(void)this;
#define super() yaooc_socket_parent_class_table->reuseaddr(this,v)
#define PM(method,...) CTM((*yaooc_socket_parent_class_table),this,method,## __VA_ARGS__)


      int option_value = v ? 1 : 0;
      yaooc_socket_setsockopt(this,SOL_SOCKET,SO_REUSEADDR,&option_value,sizeof(int));
   
#undef PM
#undef super
}
void yaooc_socket_keepalive(pointer __pthis__,int option_value)
{
yaooc_socket_pointer this=__pthis__;(void)this;
#define super() yaooc_socket_parent_class_table->keepalive(this,option_value)
#define PM(method,...) CTM((*yaooc_socket_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_socket_setsockopt(this,SOL_SOCKET,SO_REUSEADDR,&option_value,sizeof(int));
    
#undef PM
#undef super
}
bool yaooc_socket_is_open(const_pointer __pthis__)
{
yaooc_socket_const_pointer this=__pthis__;(void)this;
#define super() yaooc_socket_parent_class_table->is_open(this)
#define PM(method,...) CTM((*yaooc_socket_parent_class_table),this,method,## __VA_ARGS__)


      return this->sock_fd_>=0;
    
#undef PM
#undef super
}
yaooc_ipaddress_pointer yaooc_socket_get_local_ip(const_pointer __pthis__)
{
yaooc_socket_const_pointer this=__pthis__;(void)this;
#define super() yaooc_socket_parent_class_table->get_local_ip(this)
#define PM(method,...) CTM((*yaooc_socket_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_ipaddress_pointer ret=new(yaooc_ipaddress);
      if(this->sock_fd_>=0) {
        struct sockaddr_storage ss = {0};
        socklen_t sockaddrlen = sizeof(ss);
        if(getsockname(this->sock_fd_, (struct sockaddr*)&ss, &sockaddrlen) == 0) {
          ret->type_=ss.ss_family;
          memcpy(ret->buf_,&((struct sockaddr_in *)&ss)->sin_addr,ret->type_==AF_INET?4:16);
        }
      }
      return ret;
    
#undef PM
#undef super
}
unsigned int yaooc_socket_get_local_port(const_pointer __pthis__)
{
yaooc_socket_const_pointer this=__pthis__;(void)this;
#define super() yaooc_socket_parent_class_table->get_local_port(this)
#define PM(method,...) CTM((*yaooc_socket_parent_class_table),this,method,## __VA_ARGS__)


      unsigned int ret=-1;
      if(this->sock_fd_>=0) {
        struct sockaddr_storage ss = {0};
        socklen_t sockaddrlen = sizeof(ss);
        if(getsockname(this->sock_fd_, (struct sockaddr*)&ss, &sockaddrlen) >= 0) {
          switch(ss.ss_family) {
            case AF_INET:
              ret = ((struct sockaddr_in *)&ss)->sin_port;
              break;

            case AF_INET6:
              ret = ((struct sockaddr_in6 *)&ss)->sin6_port;
              break;
          }
        }
      }
      return ret;
    
#undef PM
#undef super
}
yaooc_ipaddress_pointer yaooc_socket_get_foreign_ip(const_pointer __pthis__)
{
yaooc_socket_const_pointer this=__pthis__;(void)this;
#define super() yaooc_socket_parent_class_table->get_foreign_ip(this)
#define PM(method,...) CTM((*yaooc_socket_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_ipaddress_pointer ret=new(yaooc_ipaddress);
      if(this->sock_fd_>=0) {
        struct sockaddr_storage ss = {0};
        socklen_t sockaddrlen = sizeof(ss);
        if(getpeername(this->sock_fd_, (struct sockaddr*)&ss, &sockaddrlen) == 0) {
          ret->type_=ss.ss_family;
          memcpy(ret->buf_,&((struct sockaddr_in *)&ss)->sin_addr,ret->type_==AF_INET?4:16);
        }
      }
      return ret;
    
#undef PM
#undef super
}
unsigned int yaooc_socket_get_remote_port(const_pointer __pthis__)
{
yaooc_socket_const_pointer this=__pthis__;(void)this;
#define super() yaooc_socket_parent_class_table->get_remote_port(this)
#define PM(method,...) CTM((*yaooc_socket_parent_class_table),this,method,## __VA_ARGS__)


      unsigned int ret=-1;
      if(this->sock_fd_>=0) {
        struct sockaddr_storage ss = {0};
        socklen_t sockaddrlen = sizeof(ss);
        if(getpeername(this->sock_fd_, (struct sockaddr*)&ss, &sockaddrlen) >= 0) {
          switch(ss.ss_family) {
            case AF_INET:
              ret = ((struct sockaddr_in *)&ss)->sin_port;
              break;

            case AF_INET6:
              ret = ((struct sockaddr_in6 *)&ss)->sin6_port;
              break;
          }
        }
      }
      return ret;
    
#undef PM
#undef super
}
yaooc_socket_class_table_t yaooc_socket_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_object_class_table,
.type_name_ = (const char*)"yaooc_socket_t",
.swap = (void(*)(pointer,pointer)) yaooc_socket_swap,
.close = (void(*)(pointer)) yaooc_socket_close,
.send = (int(*)(pointer,const char*)) yaooc_socket_send,
.sendn = (int(*)(pointer,const void*,size_t)) yaooc_socket_sendn,
.poll = (int(*)(pointer,int)) yaooc_socket_poll,
.recv = (int(*)(pointer,void*,int)) yaooc_socket_recv,
.blocking = (int(*)(pointer)) yaooc_socket_blocking,
.non_blocking = (int(*)(pointer)) yaooc_socket_non_blocking,
.async = (int(*)(pointer)) yaooc_socket_async,
.sync = (int(*)(pointer)) yaooc_socket_sync,
.debug = (void(*)(pointer,bool)) yaooc_socket_debug,
.reuseaddr = (void(*)(pointer,bool)) yaooc_socket_reuseaddr,
.keepalive = (void(*)(pointer,int)) yaooc_socket_keepalive,
.is_open = (bool(*)(const_pointer)) yaooc_socket_is_open,
.get_local_ip = (yaooc_ipaddress_pointer(*)(const_pointer)) yaooc_socket_get_local_ip,
.get_local_port = (unsigned int(*)(const_pointer)) yaooc_socket_get_local_port,
.get_foreign_ip = (yaooc_ipaddress_pointer(*)(const_pointer)) yaooc_socket_get_foreign_ip,
.get_remote_port = (unsigned int(*)(const_pointer)) yaooc_socket_get_remote_port,
};
const type_info_t __yaooc_socket_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_socket_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_socket_default_ctor,
.dtor_=yaooc_socket_dtor,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_socket_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_socket_ti=&__yaooc_socket_ti;
static void yaooc_socket_ctor_private(pointer p,va_list args)
{
  yaooc_socket_t* this=p;
  this->sock_fd_=-1;
}


void yaooc_tcp_socket_default_ctor(pointer __pthis__)
{
yaooc_tcp_socket_pointer this=__pthis__;(void)this;
call_constructor(this,yaooc_socket_ctor_private,NULL);



      this->sock_fd_=-1;
    
}
void yaooc_tcp_socket_ctor_host_port(pointer __pthis,va_list __con_args__){
yaooc_tcp_socket_pointer this=__pthis;(void)this;
const char* host = va_arg(__con_args__,const char*);
unsigned int port = va_arg(__con_args__,unsigned int);

call_default_ctor_static(this,yaooc_tcp_socket);


      M(this,connect_port,host,port);
    
}
void yaooc_tcp_socket_ctor_host_service(pointer __pthis,va_list __con_args__){
yaooc_tcp_socket_pointer this=__pthis;(void)this;
const char* host = va_arg(__con_args__,const char*);
const char* service = va_arg(__con_args__,const char*);

call_default_ctor_static(this,yaooc_tcp_socket);


      M(this,connect_service,host,service);
    
}
void yaooc_tcp_socket_connect_port(pointer __pthis__,const char* host,unsigned int port)
{
yaooc_tcp_socket_pointer this=__pthis__;(void)this;
#define super() yaooc_tcp_socket_parent_class_table->connect_port(this,host,port)
#define PM(method,...) CTM((*yaooc_tcp_socket_parent_class_table),this,method,## __VA_ARGS__)


      char port_str[32];
      sprintf(port_str,"%u",port);
      M(this,connect_service,host,port_str);
    
#undef PM
#undef super
}
void yaooc_tcp_socket_connect_service(pointer __pthis__,const char* host,const char* service)
{
yaooc_tcp_socket_pointer this=__pthis__;(void)this;
#define super() yaooc_tcp_socket_parent_class_table->connect_service(this,host,service)
#define PM(method,...) CTM((*yaooc_tcp_socket_parent_class_table),this,method,## __VA_ARGS__)


      struct addrinfo hints;
      struct addrinfo *result, *rp;
      memset(&hints, 0, sizeof(struct addrinfo));
      hints.ai_family = AF_UNSPEC;
      hints.ai_socktype = SOCK_STREAM;
      hints.ai_flags = 0;
      hints.ai_protocol = 0;
      if(getaddrinfo(host, service, &hints, &result) == 0) {
        for(rp=result;rp!=NULL;rp=rp->ai_next) {
          this->sock_fd_=socket(rp->ai_family, rp->ai_socktype,rp->ai_protocol);
          if(this->sock_fd_>=0) {
            if (connect(this->sock_fd_, rp->ai_addr, rp->ai_addrlen) != -1)
              break;
            close(this->sock_fd_);
          }
        }
        freeaddrinfo(result);
      }
    
#undef PM
#undef super
}
yaooc_tcp_socket_class_table_t yaooc_tcp_socket_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_socket_class_table,
.type_name_ = (const char*)"yaooc_tcp_socket_t",
.swap = (void(*)(pointer,pointer)) yaooc_tcp_socket_swap,
.close = (void(*)(pointer)) yaooc_tcp_socket_close,
.send = (int(*)(pointer,const char*)) yaooc_tcp_socket_send,
.sendn = (int(*)(pointer,const void*,size_t)) yaooc_tcp_socket_sendn,
.poll = (int(*)(pointer,int)) yaooc_tcp_socket_poll,
.recv = (int(*)(pointer,void*,int)) yaooc_tcp_socket_recv,
.blocking = (int(*)(pointer)) yaooc_tcp_socket_blocking,
.non_blocking = (int(*)(pointer)) yaooc_tcp_socket_non_blocking,
.async = (int(*)(pointer)) yaooc_tcp_socket_async,
.sync = (int(*)(pointer)) yaooc_tcp_socket_sync,
.debug = (void(*)(pointer,bool)) yaooc_tcp_socket_debug,
.reuseaddr = (void(*)(pointer,bool)) yaooc_tcp_socket_reuseaddr,
.keepalive = (void(*)(pointer,int)) yaooc_tcp_socket_keepalive,
.is_open = (bool(*)(const_pointer)) yaooc_tcp_socket_is_open,
.get_local_ip = (yaooc_ipaddress_pointer(*)(const_pointer)) yaooc_tcp_socket_get_local_ip,
.get_local_port = (unsigned int(*)(const_pointer)) yaooc_tcp_socket_get_local_port,
.get_foreign_ip = (yaooc_ipaddress_pointer(*)(const_pointer)) yaooc_tcp_socket_get_foreign_ip,
.get_remote_port = (unsigned int(*)(const_pointer)) yaooc_tcp_socket_get_remote_port,
.connect_port = (void(*)(pointer,const char*,unsigned int)) yaooc_tcp_socket_connect_port,
.connect_service = (void(*)(pointer,const char*,const char*)) yaooc_tcp_socket_connect_service,
};
const type_info_t __yaooc_tcp_socket_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_tcp_socket_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_tcp_socket_default_ctor,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_tcp_socket_class_table,
.parent_=&__yaooc_socket_ti
};
const type_info_t* const yaooc_tcp_socket_ti=&__yaooc_tcp_socket_ti;
void yaooc_tcp_socket_server_default_ctor(pointer __pthis__)
{
yaooc_tcp_socket_server_pointer this=__pthis__;(void)this;
call_constructor(this,yaooc_socket_ctor_private,NULL);



      this->sock_fd_=-1;
    
}
void yaooc_tcp_socket_server_ctor_service_n(pointer __pthis,va_list __con_args__){
yaooc_tcp_socket_server_pointer this=__pthis;(void)this;
const char* service = va_arg(__con_args__,const char*);
unsigned int n = va_arg(__con_args__,unsigned int);

call_default_ctor_static(this,yaooc_tcp_socket_server);


      M(this,listen_service,service,n);
    
}
void yaooc_tcp_socket_server_ctor_port_n(pointer __pthis,va_list __con_args__){
yaooc_tcp_socket_server_pointer this=__pthis;(void)this;
unsigned int port = va_arg(__con_args__,unsigned int);
unsigned int n = va_arg(__con_args__,unsigned int);

call_default_ctor_static(this,yaooc_tcp_socket_server);


      M(this,listen_port,port,n);
    
}
void yaooc_tcp_socket_server_listen_service(pointer __pthis__,const char* service,unsigned int max_connections)
{
yaooc_tcp_socket_server_pointer this=__pthis__;(void)this;
#define super() yaooc_tcp_socket_server_parent_class_table->listen_service(this,service,max_connections)
#define PM(method,...) CTM((*yaooc_tcp_socket_server_parent_class_table),this,method,## __VA_ARGS__)


      struct addrinfo hints;
      struct addrinfo *result, *rp;

      memset(&hints, 0, sizeof(struct addrinfo));
      hints.ai_family = AF_UNSPEC;    
      hints.ai_socktype = SOCK_STREAM; 
      hints.ai_flags = AI_PASSIVE;    
      hints.ai_protocol = 0;          
      hints.ai_canonname = NULL;
      hints.ai_addr = NULL;
      hints.ai_next = NULL;
      if(getaddrinfo(NULL, service, &hints, &result)==0) {
        for (rp = result; rp != NULL; rp = rp->ai_next) {
          printf("Trying %d AF_INET%s\n",rp->ai_family,(rp->ai_family == AF_INET ? "" : "6"));
          this->sock_fd_ = socket(rp->ai_family, rp->ai_socktype,rp->ai_protocol);
          if(this->sock_fd_>=0) {
            if (bind(this->sock_fd_, rp->ai_addr, rp->ai_addrlen) == 0) {
              if (listen(this->sock_fd_, max_connections) == 0)
                break;
            }
          }
          close(this->sock_fd_);
        }
        if(rp==NULL) {
          puts("not listening");
        }
      } else {
        puts("Get addrinfo failed");
      }
    
#undef PM
#undef super
}
void yaooc_tcp_socket_server_listen_port(pointer __pthis__,unsigned int port,unsigned int max_connections)
{
yaooc_tcp_socket_server_pointer this=__pthis__;(void)this;
#define super() yaooc_tcp_socket_server_parent_class_table->listen_port(this,port,max_connections)
#define PM(method,...) CTM((*yaooc_tcp_socket_server_parent_class_table),this,method,## __VA_ARGS__)


      char port_str[32];
      sprintf(port_str,"%u",port);
      M(this,listen_service,port_str,max_connections);
    
#undef PM
#undef super
}
yaooc_tcp_socket_pointer yaooc_tcp_socket_server_accept(pointer __pthis__)
{
yaooc_tcp_socket_server_pointer this=__pthis__;(void)this;
#define super() yaooc_tcp_socket_server_parent_class_table->accept(this)
#define PM(method,...) CTM((*yaooc_tcp_socket_server_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_tcp_socket_pointer ret=new(yaooc_tcp_socket);
      if(this->sock_fd_>=0) {
        ret->sock_fd_=accept(this->sock_fd_, NULL, NULL);
      }
      return ret;
    
#undef PM
#undef super
}
yaooc_tcp_socket_server_class_table_t yaooc_tcp_socket_server_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_socket_class_table,
.type_name_ = (const char*)"yaooc_tcp_socket_server_t",
.swap = (void(*)(pointer,pointer)) yaooc_tcp_socket_server_swap,
.close = (void(*)(pointer)) yaooc_tcp_socket_server_close,
.send = (int(*)(pointer,const char*)) yaooc_tcp_socket_server_send,
.sendn = (int(*)(pointer,const void*,size_t)) yaooc_tcp_socket_server_sendn,
.poll = (int(*)(pointer,int)) yaooc_tcp_socket_server_poll,
.recv = (int(*)(pointer,void*,int)) yaooc_tcp_socket_server_recv,
.blocking = (int(*)(pointer)) yaooc_tcp_socket_server_blocking,
.non_blocking = (int(*)(pointer)) yaooc_tcp_socket_server_non_blocking,
.async = (int(*)(pointer)) yaooc_tcp_socket_server_async,
.sync = (int(*)(pointer)) yaooc_tcp_socket_server_sync,
.debug = (void(*)(pointer,bool)) yaooc_tcp_socket_server_debug,
.reuseaddr = (void(*)(pointer,bool)) yaooc_tcp_socket_server_reuseaddr,
.keepalive = (void(*)(pointer,int)) yaooc_tcp_socket_server_keepalive,
.is_open = (bool(*)(const_pointer)) yaooc_tcp_socket_server_is_open,
.get_local_ip = (yaooc_ipaddress_pointer(*)(const_pointer)) yaooc_tcp_socket_server_get_local_ip,
.get_local_port = (unsigned int(*)(const_pointer)) yaooc_tcp_socket_server_get_local_port,
.get_foreign_ip = (yaooc_ipaddress_pointer(*)(const_pointer)) yaooc_tcp_socket_server_get_foreign_ip,
.get_remote_port = (unsigned int(*)(const_pointer)) yaooc_tcp_socket_server_get_remote_port,
.listen_service = (void(*)(pointer,const char*,unsigned int)) yaooc_tcp_socket_server_listen_service,
.listen_port = (void(*)(pointer,unsigned int,unsigned int)) yaooc_tcp_socket_server_listen_port,
.accept = (yaooc_tcp_socket_pointer(*)(pointer)) yaooc_tcp_socket_server_accept,
};
const type_info_t __yaooc_tcp_socket_server_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_tcp_socket_server_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_tcp_socket_server_default_ctor,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_tcp_socket_server_class_table,
.parent_=&__yaooc_socket_ti
};
const type_info_t* const yaooc_tcp_socket_server_ti=&__yaooc_tcp_socket_server_ti;
void yaooc_udp_socket_default_ctor(pointer __pthis__)
{
yaooc_udp_socket_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_udp_socket);



      this->sock_fd_=-1;
    
}
void yaooc_udp_socket_ctor_host_port(pointer __pthis,va_list __con_args__){
yaooc_udp_socket_pointer this=__pthis;(void)this;
const char* host = va_arg(__con_args__,const char*);
unsigned int port = va_arg(__con_args__,unsigned int);

call_default_ctor_static(this,yaooc_udp_socket);


    
}
void yaooc_udp_socket_broadcast(pointer __pthis__,bool v)
{
yaooc_udp_socket_pointer this=__pthis__;(void)this;
#define super() yaooc_udp_socket_parent_class_table->broadcast(this,v)
#define PM(method,...) CTM((*yaooc_udp_socket_parent_class_table),this,method,## __VA_ARGS__)


      int option_value = v ? 1 : 0;
      yaooc_socket_setsockopt(this,SOL_SOCKET,SO_BROADCAST,&option_value,sizeof(int));
    
#undef PM
#undef super
}
void yaooc_udp_socket_connect_service(pointer __pthis__,const char* host,const char* service)
{
yaooc_udp_socket_pointer this=__pthis__;(void)this;
#define super() yaooc_udp_socket_parent_class_table->connect_service(this,host,service)
#define PM(method,...) CTM((*yaooc_udp_socket_parent_class_table),this,method,## __VA_ARGS__)


    
#undef PM
#undef super
}
void yaooc_udp_socket_connect_port(pointer __pthis__,const char* host,unsigned int port)
{
yaooc_udp_socket_pointer this=__pthis__;(void)this;
#define super() yaooc_udp_socket_parent_class_table->connect_port(this,host,port)
#define PM(method,...) CTM((*yaooc_udp_socket_parent_class_table),this,method,## __VA_ARGS__)


    
#undef PM
#undef super
}
yaooc_udp_socket_class_table_t yaooc_udp_socket_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_socket_class_table,
.type_name_ = (const char*)"yaooc_udp_socket_t",
.swap = (void(*)(pointer,pointer)) yaooc_udp_socket_swap,
.close = (void(*)(pointer)) yaooc_udp_socket_close,
.send = (int(*)(pointer,const char*)) yaooc_udp_socket_send,
.sendn = (int(*)(pointer,const void*,size_t)) yaooc_udp_socket_sendn,
.poll = (int(*)(pointer,int)) yaooc_udp_socket_poll,
.recv = (int(*)(pointer,void*,int)) yaooc_udp_socket_recv,
.blocking = (int(*)(pointer)) yaooc_udp_socket_blocking,
.non_blocking = (int(*)(pointer)) yaooc_udp_socket_non_blocking,
.async = (int(*)(pointer)) yaooc_udp_socket_async,
.sync = (int(*)(pointer)) yaooc_udp_socket_sync,
.debug = (void(*)(pointer,bool)) yaooc_udp_socket_debug,
.reuseaddr = (void(*)(pointer,bool)) yaooc_udp_socket_reuseaddr,
.keepalive = (void(*)(pointer,int)) yaooc_udp_socket_keepalive,
.is_open = (bool(*)(const_pointer)) yaooc_udp_socket_is_open,
.get_local_ip = (yaooc_ipaddress_pointer(*)(const_pointer)) yaooc_udp_socket_get_local_ip,
.get_local_port = (unsigned int(*)(const_pointer)) yaooc_udp_socket_get_local_port,
.get_foreign_ip = (yaooc_ipaddress_pointer(*)(const_pointer)) yaooc_udp_socket_get_foreign_ip,
.get_remote_port = (unsigned int(*)(const_pointer)) yaooc_udp_socket_get_remote_port,
.broadcast = (void(*)(pointer,bool)) yaooc_udp_socket_broadcast,
.connect_service = (void(*)(pointer,const char*,const char*)) yaooc_udp_socket_connect_service,
.connect_port = (void(*)(pointer,const char*,unsigned int)) yaooc_udp_socket_connect_port,
};
const type_info_t __yaooc_udp_socket_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_udp_socket_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_udp_socket_default_ctor,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_udp_socket_class_table,
.parent_=&__yaooc_socket_ti
};
const type_info_t* const yaooc_udp_socket_ti=&__yaooc_udp_socket_ti;
