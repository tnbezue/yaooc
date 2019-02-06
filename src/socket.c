/*
		Copyright (C) 2016-2019  by Terry N Bezue

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
/* Begin YAOOCPP output */

#include <yaooc/socket.h>


#include <poll.h>
#ifdef _WIN32
void yaooc_socket_startup()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	wVersionRequested = MAKEWORD(2, 2);				// Request Winsock v2.2
	WSAStartup(wVersionRequested, &wsaData);  // Load Winsock DLL
}

void yaooc_socket_cleanup() { WSACleanup(); }
#endif

/* Private variables implementation for yaooc_socket_exception */

/* Private methods prototypes for yaooc_socket_exception */

/* Type Info implemmentation for yaooc_socket_exception */
/* Constructors implementation for yaooc_socket_exception */

/* Private methods implementation for yaooc_socket_exception */

/* Protected implementation for yaooc_socket_exception */

/* Table implementation for yaooc_socket_exception */

/* Class table definition for yaooc_socket_exception */
yaooc_socket_exception_class_table_t yaooc_socket_exception_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_exception_class_table,
  .type_name_ = (const char*) "yaooc_socket_exception_t",
  .swap = (void(*)(pointer, pointer)) yaooc_socket_exception_swap,
  .what = (const char*(*)(const_pointer)) yaooc_socket_exception_what,
};

/* Type info structure for yaooc_socket_exception */
DEFINE_TYPE_INFO(yaooc_socket_exception,N,N,N,N,N,N,N,Y,yaooc_exception);

/* Private variables implementation for yaooc_socket */

/* Private methods prototypes for yaooc_socket */

/* Type Info implemmentation for yaooc_socket */
void yaooc_socket_default_ctor(pointer p)
{
  THROW(new_ctor(yaooc_socket_exception,yaooc_socket_exception_ctor_v,"Creating a instance of Socket is not allowed"));
}

void yaooc_socket_dtor(pointer p)
{
//  yaooc_socket_pointer this=p;
	yaooc_socket_close(p);
}

void yaooc_socket_copy_ctor(pointer p,const_pointer s)
{
  yaooc_socket_default_ctor(p);
  yaooc_socket_assign(p,s);
}

void yaooc_socket_assign(pointer p,const_pointer s)
{
/*  yaooc_socket_pointer this=p;
  yaooc_socket_const_pointer src=s;
  this->sock_fd_ = src->sock_fd_;*/
	// Don't allow copying of socket.  Multiple instances using the same socket may be problematic
}

/* Constructors implementation for yaooc_socket */

/* Private methods implementation for yaooc_socket */

/* Protected implementation for yaooc_socket */
int yaooc_socket_setsockopt(pointer p,int level,int option_name,const void* option_value,socklen_t option_len)
{
  yaooc_socket_pointer this=p;
  return setsockopt(this->sock_fd_,level,option_name,option_value,option_len);
}


/* Table implementation for yaooc_socket */
void yaooc_socket_close(pointer p)
{
  yaooc_socket_pointer this=p;
	if(this->sock_fd_)
		close(this->sock_fd_);
	this->sock_fd_=-1;
}

int yaooc_socket_send(pointer p,const char* s)
{
  return yaooc_socket_sendn(p,s,s ? strlen(s) : 0);
}

int yaooc_socket_sendn(pointer p,const void* buffer,size_t n)
{
  yaooc_socket_pointer this=p;
	int ret=-1;
	if(this->sock_fd_) {
		ret=sendto(this->sock_fd_,buffer,n,0,NULL,0);
	}
	return ret;
}

int yaooc_socket_poll(pointer p,int timeout_ms)
{
  yaooc_socket_pointer this=p;
	int ret=0;
	if(this->sock_fd_ >=0) {
		struct pollfd pfd;
		pfd.fd = this->sock_fd_;
		pfd.events = POLLIN|POLLOUT|POLLHUP|POLLERR|POLLNVAL;
		pfd.revents = 0;
		ret = poll(&pfd,1,timeout_ms);
	}
	return ret;
}

int yaooc_socket_recv(pointer p,void* buffer,int n)
{
  yaooc_socket_pointer this=p;
  int ret=0;
	if(this->sock_fd_ >= 0)
		ret = recvfrom(this->sock_fd_,(char*)buffer,n,0,NULL,0);
  return ret;
}

int yaooc_socket_blocking(pointer p)
{
  yaooc_socket_pointer this=p;
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
}

int yaooc_socket_non_blocking(pointer p)
{
  yaooc_socket_pointer this=p;
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
}

int yaooc_socket_async(pointer p)
{
  yaooc_socket_pointer this=p;
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
}

int yaooc_socket_sync(pointer p)
{
  yaooc_socket_pointer this=p;
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
}

void yaooc_socket_debug(pointer p,bool v)
{
	int option_value = v ? 1 : 0;
	yaooc_socket_setsockopt(p,SOL_SOCKET,SO_DEBUG,&option_value,sizeof(int));
}

void yaooc_socket_reuseaddr(pointer p,bool v)
{
	int option_value = v ? 1 : 0;
	yaooc_socket_setsockopt(p,SOL_SOCKET,SO_REUSEADDR,&option_value,sizeof(int));
}

void yaooc_socket_keepalive(pointer p,int option_value)
{
	yaooc_socket_setsockopt(p,SOL_SOCKET,SO_REUSEADDR,&option_value,sizeof(int));
}

bool yaooc_socket_is_open(const_pointer p)
{
  yaooc_socket_const_pointer this=p;
	return this->sock_fd_>=0;
}

yaooc_ipaddress_pointer yaooc_socket_get_local_ip(const_pointer p)
{
  yaooc_socket_const_pointer this=p;
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
}

unsigned int yaooc_socket_get_local_port(const_pointer p)
{
  yaooc_socket_const_pointer this=p;
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
}

yaooc_ipaddress_pointer yaooc_socket_get_foreign_ip(const_pointer p)
{
  yaooc_socket_const_pointer this=p;
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
}

unsigned int yaooc_socket_get_remote_port(const_pointer p)
{
  yaooc_socket_const_pointer this=p;
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
}


/* Class table definition for yaooc_socket */
yaooc_socket_class_table_t yaooc_socket_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "yaooc_socket_t",
  .swap = (void(*)(pointer, pointer)) yaooc_socket_swap,
  .close = (void(*)(pointer)) yaooc_socket_close,
  .send = (int(*)(pointer, const char*)) yaooc_socket_send,
  .sendn = (int(*)(pointer, const void*, size_t)) yaooc_socket_sendn,
  .poll = (int(*)(pointer, int)) yaooc_socket_poll,
  .recv = (int(*)(pointer, void*, int)) yaooc_socket_recv,
  .blocking = (int(*)(pointer)) yaooc_socket_blocking,
  .non_blocking = (int(*)(pointer)) yaooc_socket_non_blocking,
  .async = (int(*)(pointer)) yaooc_socket_async,
  .sync = (int(*)(pointer)) yaooc_socket_sync,
  .debug = (void(*)(pointer, bool)) yaooc_socket_debug,
  .reuseaddr = (void(*)(pointer, bool)) yaooc_socket_reuseaddr,
  .keepalive = (void(*)(pointer, int)) yaooc_socket_keepalive,
  .is_open = (bool(*)(const_pointer)) yaooc_socket_is_open,
  .get_local_ip = (yaooc_ipaddress_pointer(*)(const_pointer)) yaooc_socket_get_local_ip,
  .get_local_port = (unsigned int(*)(const_pointer)) yaooc_socket_get_local_port,
  .get_foreign_ip = (yaooc_ipaddress_pointer(*)(const_pointer)) yaooc_socket_get_foreign_ip,
  .get_remote_port = (unsigned int(*)(const_pointer)) yaooc_socket_get_remote_port,
};

/* Type info structure for yaooc_socket */
DEFINE_TYPE_INFO(yaooc_socket,Y,Y,Y,Y,N,N,N,Y,yaooc_object);

/* Private variables implementation for yaooc_tcp_socket */

/* Private methods prototypes for yaooc_tcp_socket */

/* Type Info implemmentation for yaooc_tcp_socket */
void yaooc_tcp_socket_default_ctor(pointer p)
{
  yaooc_tcp_socket_pointer this=p;
	this->sock_fd_=-1;
}

/* Constructors implementation for yaooc_tcp_socket */
void yaooc_tcp_socket_ctor_host_port(pointer p,va_list args)
{
//  yaooc_tcp_socket_pointer this=p;
	const char* host= va_arg(args, const char*);
	unsigned int port= va_arg(args, unsigned int);
	yaooc_tcp_socket_connect_port(p,host,port);
}

void yaooc_tcp_socket_ctor_host_service(pointer p,va_list args)
{
//  yaooc_tcp_socket_pointer this=p;
	const char* host= va_arg(args, const char*);
	const char* service= va_arg(args, const char*);
	yaooc_tcp_socket_connect_service(p,host,service);
}


/* Private methods implementation for yaooc_tcp_socket */

/* Protected implementation for yaooc_tcp_socket */

/* Table implementation for yaooc_tcp_socket */
void yaooc_tcp_socket_connect_service(pointer p,const char* host,const char* service)
{
  yaooc_tcp_socket_pointer this=p;
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
}

void yaooc_tcp_socket_connect_port(pointer p,const char* host,unsigned int port)
{
	char port_str[32];
	sprintf(port_str,"%u",port);
  yaooc_tcp_socket_connect_service(p,host,port_str);
}

/* Class table definition for yaooc_tcp_socket */
yaooc_tcp_socket_class_table_t yaooc_tcp_socket_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_socket_class_table,
  .type_name_ = (const char*) "yaooc_tcp_socket_t",
  .swap = (void(*)(pointer, pointer)) yaooc_tcp_socket_swap,
  .close = (void(*)(pointer)) yaooc_tcp_socket_close,
  .send = (int(*)(pointer, const char*)) yaooc_tcp_socket_send,
  .sendn = (int(*)(pointer, const void*, size_t)) yaooc_tcp_socket_sendn,
  .poll = (int(*)(pointer, int)) yaooc_tcp_socket_poll,
  .recv = (int(*)(pointer, void*, int)) yaooc_tcp_socket_recv,
  .blocking = (int(*)(pointer)) yaooc_tcp_socket_blocking,
  .non_blocking = (int(*)(pointer)) yaooc_tcp_socket_non_blocking,
  .async = (int(*)(pointer)) yaooc_tcp_socket_async,
  .sync = (int(*)(pointer)) yaooc_tcp_socket_sync,
  .debug = (void(*)(pointer, bool)) yaooc_tcp_socket_debug,
  .reuseaddr = (void(*)(pointer, bool)) yaooc_tcp_socket_reuseaddr,
  .keepalive = (void(*)(pointer, int)) yaooc_tcp_socket_keepalive,
  .is_open = (bool(*)(const_pointer)) yaooc_tcp_socket_is_open,
  .get_local_ip = (yaooc_ipaddress_pointer(*)(const_pointer)) yaooc_tcp_socket_get_local_ip,
  .get_local_port = (unsigned int(*)(const_pointer)) yaooc_tcp_socket_get_local_port,
  .get_foreign_ip = (yaooc_ipaddress_pointer(*)(const_pointer)) yaooc_tcp_socket_get_foreign_ip,
  .get_remote_port = (unsigned int(*)(const_pointer)) yaooc_tcp_socket_get_remote_port,
  .connect_serice = (void(*)(pointer, const char*, const char*)) yaooc_tcp_socket_connect_service,
  .connect_port = (void(*)(pointer, const char*, unsigned int)) yaooc_tcp_socket_connect_port,
};

/* Type info structure for yaooc_tcp_socket */
DEFINE_TYPE_INFO(yaooc_tcp_socket,Y,N,N,N,N,N,N,Y,yaooc_socket);

/* Private variables implementation for yaooc_tcp_socket_server */

/* Private methods prototypes for yaooc_tcp_socket_server */

/* Type Info implemmentation for yaooc_tcp_socket_server */
void yaooc_tcp_socket_server_default_ctor(pointer p)
{
  yaooc_tcp_socket_server_pointer this=p;
	this->sock_fd_=-1;
}

/* Constructors implementation for yaooc_tcp_socket_server */
void yaooc_tcp_socket_server_ctor_service_n(pointer p,va_list args)
{
//  yaooc_tcp_socket_server_pointer this=p;
	const char* service= va_arg(args, const char*);
	unsigned int n= va_arg(args, unsigned int);
	yaooc_tcp_socket_server_listen_service(p,service,n);
}

void yaooc_tcp_socket_server_ctor_port_n(pointer p,va_list args)
{
//  yaooc_tcp_socket_server_pointer this=p;
	unsigned int port= va_arg(args, unsigned int);
	unsigned int n= va_arg(args, unsigned int);
	yaooc_tcp_socket_server_listen_port(p,port,n);
}


/* Private methods implementation for yaooc_tcp_socket_server */

/* Protected implementation for yaooc_tcp_socket_server */

/* Table implementation for yaooc_tcp_socket_server */
void yaooc_tcp_socket_server_listen_service(pointer p,const char* service,unsigned int max_connections)
{
  yaooc_tcp_socket_server_pointer this=p;
	struct addrinfo hints;
	struct addrinfo *result, *rp;

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
	hints.ai_socktype = SOCK_STREAM; /* Datagram socket */
	hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
	hints.ai_protocol = 0;          /* Any protocol */
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
}

void yaooc_tcp_socket_server_listen_port(pointer p,unsigned int port,unsigned int max_connections)
{
	char port_str[32];
	sprintf(port_str,"%u",port);
	yaooc_tcp_socket_server_listen_service(p,port_str,max_connections);
}

yaooc_tcp_socket_pointer yaooc_tcp_socket_server_accept(pointer p)
{
  yaooc_tcp_socket_server_pointer this=p;
  yaooc_tcp_socket_pointer ret=new(yaooc_tcp_socket);
	if(this->sock_fd_>=0) {
		ret->sock_fd_=accept(this->sock_fd_, NULL, NULL);
	}
  return ret;
}

/* Class table definition for yaooc_tcp_socket_server */
yaooc_tcp_socket_server_class_table_t yaooc_tcp_socket_server_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_socket_class_table,
  .type_name_ = (const char*) "yaooc_tcp_socket_server_t",
  .swap = (void(*)(pointer, pointer)) yaooc_tcp_socket_server_swap,
  .close = (void(*)(pointer)) yaooc_tcp_socket_server_close,
  .send = (int(*)(pointer, const char*)) yaooc_tcp_socket_server_send,
  .sendn = (int(*)(pointer, const void*, size_t)) yaooc_tcp_socket_server_sendn,
  .poll = (int(*)(pointer, int)) yaooc_tcp_socket_server_poll,
  .recv = (int(*)(pointer, void*, int)) yaooc_tcp_socket_server_recv,
  .blocking = (int(*)(pointer)) yaooc_tcp_socket_server_blocking,
  .non_blocking = (int(*)(pointer)) yaooc_tcp_socket_server_non_blocking,
  .async = (int(*)(pointer)) yaooc_tcp_socket_server_async,
  .sync = (int(*)(pointer)) yaooc_tcp_socket_server_sync,
  .debug = (void(*)(pointer, bool)) yaooc_tcp_socket_server_debug,
  .reuseaddr = (void(*)(pointer, bool)) yaooc_tcp_socket_server_reuseaddr,
  .keepalive = (void(*)(pointer, int)) yaooc_tcp_socket_server_keepalive,
  .is_open = (bool(*)(const_pointer)) yaooc_tcp_socket_server_is_open,
  .get_local_ip = (yaooc_ipaddress_pointer(*)(const_pointer)) yaooc_tcp_socket_server_get_local_ip,
  .get_local_port = (unsigned int(*)(const_pointer)) yaooc_tcp_socket_server_get_local_port,
  .get_foreign_ip = (yaooc_ipaddress_pointer(*)(const_pointer)) yaooc_tcp_socket_server_get_foreign_ip,
  .get_remote_port = (unsigned int(*)(const_pointer)) yaooc_tcp_socket_server_get_remote_port,
  .listen_service = (void(*)(pointer, const char*, unsigned int)) yaooc_tcp_socket_server_listen_service,
  .listen_port = (void(*)(pointer, unsigned int, unsigned int)) yaooc_tcp_socket_server_listen_port,
  .accept = (yaooc_tcp_socket_pointer(*)(pointer)) yaooc_tcp_socket_server_accept,
};

/* Type info structure for yaooc_tcp_socket_server */
DEFINE_TYPE_INFO(yaooc_tcp_socket_server,Y,N,N,N,N,N,N,Y,yaooc_socket);

/* Private variables implementation for yaooc_udp_socket */

/* Private methods prototypes for yaooc_udp_socket */

/* Type Info implemmentation for yaooc_udp_socket */
void yaooc_udp_socket_default_ctor(pointer p)
{
	((yaooc_udp_socket_pointer)p)->sock_fd_=-1;
}

/* Constructors implementation for yaooc_udp_socket */
void yaooc_udp_socket_ctor_host_port(pointer p,va_list args)
{
  yaooc_udp_socket_pointer this=p;
	const char* host= va_arg(args, const char*);
	unsigned int port= va_arg(args, unsigned int);
}


/* Private methods implementation for yaooc_udp_socket */

/* Protected implementation for yaooc_udp_socket */

/* Table implementation for yaooc_udp_socket */
void yaooc_udp_socket_broadcast(pointer p,bool v)
{
	int option_value = v ? 1 : 0;
	yaooc_socket_setsockopt(p,SOL_SOCKET,SO_BROADCAST,&option_value,sizeof(int));
}

void yaooc_udp_socket_connect_service(pointer p,const char* host,const char* service)
{
  yaooc_udp_socket_pointer this=p;
}

void yaooc_udp_socket_connect_port(pointer p,const char* host,unsigned int port)
{
  yaooc_udp_socket_pointer this=p;
}


/* Class table definition for yaooc_udp_socket */
yaooc_udp_socket_class_table_t yaooc_udp_socket_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_socket_class_table,
  .type_name_ = (const char*) "yaooc_udp_socket_t",
  .swap = (void(*)(pointer, pointer)) yaooc_udp_socket_swap,
  .close = (void(*)(pointer)) yaooc_udp_socket_close,
  .send = (int(*)(pointer, const char*)) yaooc_udp_socket_send,
  .sendn = (int(*)(pointer, const void*, size_t)) yaooc_udp_socket_sendn,
  .poll = (int(*)(pointer, int)) yaooc_udp_socket_poll,
  .recv = (int(*)(pointer, void*, int)) yaooc_udp_socket_recv,
  .blocking = (int(*)(pointer)) yaooc_udp_socket_blocking,
  .non_blocking = (int(*)(pointer)) yaooc_udp_socket_non_blocking,
  .async = (int(*)(pointer)) yaooc_udp_socket_async,
  .sync = (int(*)(pointer)) yaooc_udp_socket_sync,
  .debug = (void(*)(pointer, bool)) yaooc_udp_socket_debug,
  .reuseaddr = (void(*)(pointer, bool)) yaooc_udp_socket_reuseaddr,
  .keepalive = (void(*)(pointer, int)) yaooc_udp_socket_keepalive,
  .is_open = (bool(*)(const_pointer)) yaooc_udp_socket_is_open,
  .get_local_ip = (yaooc_ipaddress_pointer(*)(const_pointer)) yaooc_udp_socket_get_local_ip,
  .get_local_port = (unsigned int(*)(const_pointer)) yaooc_udp_socket_get_local_port,
  .get_foreign_ip = (yaooc_ipaddress_pointer(*)(const_pointer)) yaooc_udp_socket_get_foreign_ip,
  .get_remote_port = (unsigned int(*)(const_pointer)) yaooc_udp_socket_get_remote_port,
  .broadcast = (void(*)(pointer, bool)) yaooc_udp_socket_broadcast,
  .connect_service = (void(*)(pointer, const char*, const char*)) yaooc_udp_socket_connect_service,
  .connect_port = (void(*)(pointer, const char*, unsigned int)) yaooc_udp_socket_connect_port,
};

/* Type info structure for yaooc_udp_socket */
DEFINE_TYPE_INFO(yaooc_udp_socket,N,N,N,N,N,N,N,Y,yaooc_socket);

/* End YAOOCPP output */

