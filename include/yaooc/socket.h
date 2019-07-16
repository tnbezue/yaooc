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
#ifndef __SOCKET_INCLUDED__
#define __SOCKET_INCLUDED__

/* Begin YAOOCPP output */

#include <yaooc/object.h>
#include <yaooc/ipaddress.h>
#include <yaooc/exception.h>


#include <string.h>
#include <unistd.h>
#ifdef __WIN32__
# include <winsock2.h>         // for socket(), connect(), send(), and recv()
# include <ws2tcpip.h>
  typedef int socklen_t;
#else
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
# include <sys/types.h>
# include <sys/socket.h>      // for socket(), connect(), send(), and recv()
# include <sys/ioctl.h>
# include <netdb.h>           // for gethostbyname()
# include <arpa/inet.h>       // for sockaddr_in and inet_addr()
#endif

#ifdef _WIN32
void yaooc_socket_startup();
void yaooc_socket_cleanup();
#else
#define yaooc_socket_startup()
#define yaooc_socket_cleanup()
#endif

/*
  Class Definition for yaooc_socket_exception
*/
yaooc_class_table(yaooc_socket_exception) {
  yaooc_exception_class_table_t;
};
#define yaooc_socket_exception_parent_class_table ((yaooc_exception_class_table_t*)(yaooc_socket_exception_class_table.parent_class_table_))

yaooc_class_instance(yaooc_socket_exception) {
  yaooc_exception_class_instance_t;
};

yaooc_class(yaooc_socket_exception);

/* Type Info Prototypes for yaooc_socket_exception */
#define yaooc_socket_exception_default_ctor yaooc_exception_default_ctor
#define yaooc_socket_exception_dtor yaooc_exception_dtor
#define yaooc_socket_exception_copy_ctor yaooc_exception_copy_ctor
#define yaooc_socket_exception_assign yaooc_exception_assign

/* Constructors prototypes for yaooc_socket_exception */
#define yaooc_socket_exception_ctor_v yaooc_exception_ctor_v

/* Table prototypes for yaooc_socket_exception */
#define yaooc_socket_exception_swap yaooc_exception_swap
#define yaooc_socket_exception_what yaooc_exception_what

/* Protected prototypes for yaooc_socket_exception */

/*
  Class Definition for yaooc_socket
*/
yaooc_class_table(yaooc_socket) {
  yaooc_object_class_table_t;
  void (*close)(pointer);
  int (*send)(pointer, const char*);
  int (*sendn)(pointer, const void*, size_t);
  int (*poll)(pointer, int);
  int (*recv)(pointer, void*, int);
  int (*blocking)(pointer);
  int (*non_blocking)(pointer);
  int (*async)(pointer);
  int (*sync)(pointer);
  void (*debug)(pointer, bool);
  void (*reuseaddr)(pointer, bool);
  void (*keepalive)(pointer, int);
  bool (*is_open)(const_pointer);
  yaooc_ipaddress_pointer (*get_local_ip)(const_pointer);
  unsigned int (*get_local_port)(const_pointer);
  yaooc_ipaddress_pointer (*get_foreign_ip)(const_pointer);
  unsigned int (*get_remote_port)(const_pointer);
};
#define yaooc_socket_parent_class_table ((yaooc_object_class_table_t*)(yaooc_socket_class_table.parent_class_table_))

yaooc_class_instance(yaooc_socket) {
  yaooc_object_class_instance_t;
  int sock_fd_;
};

yaooc_class(yaooc_socket);

/* Type Info Prototypes for yaooc_socket */
void yaooc_socket_default_ctor(pointer);
void yaooc_socket_dtor(pointer);
void yaooc_socket_copy_ctor(pointer,const_pointer);
void yaooc_socket_assign(pointer,const_pointer);

/* Constructors prototypes for yaooc_socket */

/* Table prototypes for yaooc_socket */
#define yaooc_socket_swap yaooc_object_swap
void yaooc_socket_close(pointer);
int yaooc_socket_send(pointer, const char*);
int yaooc_socket_sendn(pointer, const void*, size_t);
int yaooc_socket_poll(pointer, int);
int yaooc_socket_recv(pointer, void*, int);
int yaooc_socket_blocking(pointer);
int yaooc_socket_non_blocking(pointer);
int yaooc_socket_async(pointer);
int yaooc_socket_sync(pointer);
void yaooc_socket_debug(pointer, bool);
void yaooc_socket_reuseaddr(pointer, bool);
void yaooc_socket_keepalive(pointer, int);
bool yaooc_socket_is_open(const_pointer);
yaooc_ipaddress_pointer yaooc_socket_get_local_ip(const_pointer);
unsigned int yaooc_socket_get_local_port(const_pointer);
yaooc_ipaddress_pointer yaooc_socket_get_foreign_ip(const_pointer);
unsigned int yaooc_socket_get_remote_port(const_pointer);

/* Protected prototypes for yaooc_socket */
extern int yaooc_socket_setsockopt(pointer, int, int, const void*, socklen_t);

/*
  Class Definition for yaooc_tcp_socket
*/
yaooc_class_table(yaooc_tcp_socket) {
  yaooc_socket_class_table_t;
  void (*connect_serice)(pointer, const char*, const char*);
  void (*connect_port)(pointer, const char*, unsigned int);
};
#define yaooc_tcp_socket_parent_class_table ((yaooc_socket_class_table_t*)(yaooc_tcp_socket_class_table.parent_class_table_))

yaooc_class_instance(yaooc_tcp_socket) {
  yaooc_socket_class_instance_t;
};

yaooc_class(yaooc_tcp_socket);

/* Type Info Prototypes for yaooc_tcp_socket */
void yaooc_tcp_socket_default_ctor(pointer);
#define yaooc_tcp_socket_dtor yaooc_socket_dtor
#define yaooc_tcp_socket_copy_ctor yaooc_socket_copy_ctor
#define yaooc_tcp_socket_assign yaooc_socket_assign

/* Constructors prototypes for yaooc_tcp_socket */
void yaooc_tcp_socket_ctor_host_port(pointer,va_list);
void yaooc_tcp_socket_ctor_host_service(pointer,va_list);

/* Table prototypes for yaooc_tcp_socket */
#define yaooc_tcp_socket_swap yaooc_socket_swap
#define yaooc_tcp_socket_close yaooc_socket_close
#define yaooc_tcp_socket_send yaooc_socket_send
#define yaooc_tcp_socket_sendn yaooc_socket_sendn
#define yaooc_tcp_socket_poll yaooc_socket_poll
#define yaooc_tcp_socket_recv yaooc_socket_recv
#define yaooc_tcp_socket_blocking yaooc_socket_blocking
#define yaooc_tcp_socket_non_blocking yaooc_socket_non_blocking
#define yaooc_tcp_socket_async yaooc_socket_async
#define yaooc_tcp_socket_sync yaooc_socket_sync
#define yaooc_tcp_socket_debug yaooc_socket_debug
#define yaooc_tcp_socket_reuseaddr yaooc_socket_reuseaddr
#define yaooc_tcp_socket_keepalive yaooc_socket_keepalive
#define yaooc_tcp_socket_is_open yaooc_socket_is_open
#define yaooc_tcp_socket_get_local_ip yaooc_socket_get_local_ip
#define yaooc_tcp_socket_get_local_port yaooc_socket_get_local_port
#define yaooc_tcp_socket_get_foreign_ip yaooc_socket_get_foreign_ip
#define yaooc_tcp_socket_get_remote_port yaooc_socket_get_remote_port

/* Protected prototypes for yaooc_tcp_socket */
extern void yaooc_tcp_socket_connect_service(pointer, const char*, const char*);
extern void yaooc_tcp_socket_connect_port(pointer, const char*, unsigned int);

/*
  Class Definition for yaooc_tcp_socket_server
*/
yaooc_class_table(yaooc_tcp_socket_server) {
  yaooc_socket_class_table_t;
  void (*listen_service)(pointer, const char*, unsigned int);
  void (*listen_port)(pointer, unsigned int, unsigned int);
  yaooc_tcp_socket_pointer (*accept)(pointer);
};
#define yaooc_tcp_socket_server_parent_class_table ((yaooc_socket_class_table_t*)(yaooc_tcp_socket_server_class_table.parent_class_table_))

yaooc_class_instance(yaooc_tcp_socket_server) {
  yaooc_socket_class_instance_t;
};

yaooc_class(yaooc_tcp_socket_server);

/* Type Info Prototypes for yaooc_tcp_socket_server */
void yaooc_tcp_socket_server_default_ctor(pointer);
#define yaooc_tcp_socket_server_dtor yaooc_socket_dtor
#define yaooc_tcp_socket_server_copy_ctor yaooc_socket_copy_ctor
#define yaooc_tcp_socket_server_assign yaooc_socket_assign

/* Constructors prototypes for yaooc_tcp_socket_server */
void yaooc_tcp_socket_server_ctor_service_n(pointer,va_list);
void yaooc_tcp_socket_server_ctor_port_n(pointer,va_list);

/* Table prototypes for yaooc_tcp_socket_server */
#define yaooc_tcp_socket_server_swap yaooc_socket_swap
#define yaooc_tcp_socket_server_close yaooc_socket_close
#define yaooc_tcp_socket_server_send yaooc_socket_send
#define yaooc_tcp_socket_server_sendn yaooc_socket_sendn
#define yaooc_tcp_socket_server_poll yaooc_socket_poll
#define yaooc_tcp_socket_server_recv yaooc_socket_recv
#define yaooc_tcp_socket_server_blocking yaooc_socket_blocking
#define yaooc_tcp_socket_server_non_blocking yaooc_socket_non_blocking
#define yaooc_tcp_socket_server_async yaooc_socket_async
#define yaooc_tcp_socket_server_sync yaooc_socket_sync
#define yaooc_tcp_socket_server_debug yaooc_socket_debug
#define yaooc_tcp_socket_server_reuseaddr yaooc_socket_reuseaddr
#define yaooc_tcp_socket_server_keepalive yaooc_socket_keepalive
#define yaooc_tcp_socket_server_is_open yaooc_socket_is_open
#define yaooc_tcp_socket_server_get_local_ip yaooc_socket_get_local_ip
#define yaooc_tcp_socket_server_get_local_port yaooc_socket_get_local_port
#define yaooc_tcp_socket_server_get_foreign_ip yaooc_socket_get_foreign_ip
#define yaooc_tcp_socket_server_get_remote_port yaooc_socket_get_remote_port

/* Protected prototypes for yaooc_tcp_socket_server */
extern void yaooc_tcp_socket_server_listen_service(pointer, const char*, unsigned int);
extern void yaooc_tcp_socket_server_listen_port(pointer, unsigned int, unsigned int);
extern yaooc_tcp_socket_pointer yaooc_tcp_socket_server_accept(pointer);

/*
  Class Definition for yaooc_udp_socket
*/
yaooc_class_table(yaooc_udp_socket) {
  yaooc_socket_class_table_t;
  void (*broadcast)(pointer, bool);
  void (*connect_service)(pointer, const char*, const char*);
  void (*connect_port)(pointer, const char*, unsigned int);
};
#define yaooc_udp_socket_parent_class_table ((yaooc_socket_class_table_t*)(yaooc_udp_socket_class_table.parent_class_table_))

yaooc_class_instance(yaooc_udp_socket) {
  yaooc_socket_class_instance_t;
};

yaooc_class(yaooc_udp_socket);

/* Type Info Prototypes for yaooc_udp_socket */
void yaooc_udp_socket_default_ctor(pointer);
#define yaooc_udp_socket_dtor yaooc_socket_dtor
#define yaooc_udp_socket_copy_ctor yaooc_socket_copy_ctor
#define yaooc_udp_socket_assign yaooc_socket_assign

/* Constructors prototypes for yaooc_udp_socket */
void yaooc_udp_socket_ctor_host_port(pointer,va_list);

/* Table prototypes for yaooc_udp_socket */
#define yaooc_udp_socket_swap yaooc_socket_swap
#define yaooc_udp_socket_close yaooc_socket_close
#define yaooc_udp_socket_send yaooc_socket_send
#define yaooc_udp_socket_sendn yaooc_socket_sendn
#define yaooc_udp_socket_poll yaooc_socket_poll
#define yaooc_udp_socket_recv yaooc_socket_recv
#define yaooc_udp_socket_blocking yaooc_socket_blocking
#define yaooc_udp_socket_non_blocking yaooc_socket_non_blocking
#define yaooc_udp_socket_async yaooc_socket_async
#define yaooc_udp_socket_sync yaooc_socket_sync
#define yaooc_udp_socket_debug yaooc_socket_debug
#define yaooc_udp_socket_reuseaddr yaooc_socket_reuseaddr
#define yaooc_udp_socket_keepalive yaooc_socket_keepalive
#define yaooc_udp_socket_is_open yaooc_socket_is_open
#define yaooc_udp_socket_get_local_ip yaooc_socket_get_local_ip
#define yaooc_udp_socket_get_local_port yaooc_socket_get_local_port
#define yaooc_udp_socket_get_foreign_ip yaooc_socket_get_foreign_ip
#define yaooc_udp_socket_get_remote_port yaooc_socket_get_remote_port
void yaooc_udp_socket_broadcast(pointer, bool);
void yaooc_udp_socket_connect_service(pointer, const char*, const char*);
void yaooc_udp_socket_connect_port(pointer, const char*, unsigned int);

/* Protected prototypes for yaooc_udp_socket */

/* End YAOOCPP output */


#endif
