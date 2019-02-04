/*
		Copyright (C) 2016-2018  by Terry N Bezue

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

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stddef.h>
#include <yaooc/socket.h>
#include <yaooc/thread.h>
#include <yaooc/sstream.h>
#include "test_harness.h"

void talk_thread(pointer p,void* data)
{
//	yaooc_thread_pointer this=p;
	yaooc_tcp_socket_pointer sock=data;
	size_t n;
	char buffer[1024];
	while(true) {
		printf("Waiting for data to be available\n");
		M(sock,poll,-1);
		n=M(sock,recv,buffer,1024);
		if(n<=0)
			break;
		buffer[n]=0;
		M(sock,send,buffer);
	}
	puts("Exiting thread");
}

void test_sizes()
{
  TESTCASE("Sizes");
  TEST("Size of ipaddress 16",sizeof(yaooc_socket_t)==16);
}

void test_server()
{
	yaooc_tcp_socket_server_t* server=new(yaooc_tcp_socket_server);
	M(server,listen_port,2020,5);
	while(true) {
		yaooc_tcp_socket_pointer sock=M(server,accept);
		if(sock >= 0) {
			printf("Starting a talk thread\n");
			yaooc_thread_pointer thrd=new_ctor(yaooc_thread,yaooc_thread_ctor_method,talk_thread);
			M(thrd,start,sock);
		}
		printf("Waiting 3 seconds before accepting another\n");
		sleep(3);
	}
}



test_function tests[]=
{
  test_sizes,
	test_server,
};

STD_MAIN(tests)
