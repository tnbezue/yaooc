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
#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#else
#include <arpa/inet.h>
#endif
#include <yaooc/ipaddress.h>
#include <yaooc/sstream.h>
#include "test_harness.h"

void test_sizes()
{
  TESTCASE("Sizes");
  TEST("Size of ipaddress 16",sizeof(yaooc_ipaddress_t));
}

void test_default_ctor()
{
	yaooc_ipaddress_t* ip=new(yaooc_ipaddress);
	yaooc_ostringstream_t* os=new(yaooc_ostringstream);
	TEST("Type is undefined",M(ip,type)!=AF_INET && M(ip,type)!=AF_INET6);
	TEST("Is not loopback",!M(ip,is_loopback));
	STREAM(os,ip);
	TEST("Ouput is '(nil)'",strcmp(M(os,c_str),"(nil)")==0);
	delete(os);
	delete(ip);
}

void test_ip4()
{
	yaooc_ipaddress_t* ip4=new_ctor(yaooc_ipaddress,yaooc_ipaddress_ctor_ccs,"127.0.0.1");
	yaooc_ostringstream_t* os=new(yaooc_ostringstream);

	TEST("Type is IP4",M(ip4,type)==AF_INET);
	TEST("Is loopback",M(ip4,is_loopback));
	STREAM(os,ip4);
	TEST("Ouput is '127.0.0.1'",strcmp(M(os,c_str),"127.0.0.1")==0);

	M(ip4,set,"192.168.1.87");
	TEST("Type is IP4",M(ip4,type)==AF_INET);
	TEST("Is not loopback",!M(ip4,is_loopback));
	M(os,seek,0,SEEK_SET);
	STREAM(os,ip4);
	TEST("Ouput is '192.168.1.87'",strcmp(M(os,c_str),"192.168.1.87")==0);

	delete(ip4);
	delete(os);
}

void test_ip6()
{
	yaooc_ipaddress_t* ip6=new_ctor(yaooc_ipaddress,yaooc_ipaddress_ctor_ccs,"::1");
	yaooc_ostringstream_t* os=new(yaooc_ostringstream);

	TEST("Type is IP6",M(ip6,type)==AF_INET6);
	TEST("Is loopback",M(ip6,is_loopback));
	STREAM(os,ip6);
	TEST("Ouput is '::1'",strcmp(M(os,c_str),"::1")==0);

	M(ip6,set,"2600:1700:3901:1b80:7a2b:cbff:fea1:b6d");
	TEST("Type is IP6",M(ip6,type)==AF_INET6);
	TEST("Is not loopback",!M(ip6,is_loopback));
	M(os,seek,0,SEEK_SET);
	STREAM(os,ip6);
	TEST("Ouput is '2600:1700:3901:1b80:7a2b:cbff:fea1:b6d'",strcmp(M(os,c_str),"2600:1700:3901:1b80:7a2b:cbff:fea1:b6d")==0);

	delete(ip6);
	delete(os);
}

typedef struct {
	const char *lhs;
	const char *rhs;
	int result; // what cmp_ipaddress would have returned
} cmp_test_ip;

cmp_test_ip ip4_tests[] = {
	{ "127.0.0.1", "192.168.1.8", -1},
	{ "192.168.1.8", "127.0.0.1",  1},
	{ "127.0.0.1", "127.0.0.1",  0},
	{ "192.168.1.8", "192.168.1.8",  0},
	{ "192.168.1.10", "192.168.1.8",  1},
	{ "192.168.1.2", "192.168.1.8",  -1},
	{ NULL, NULL, 0 }
};

void test_cmp_ip4()
{
	yaooc_ipaddress_t* lhs = new(yaooc_ipaddress);
	yaooc_ipaddress_t* rhs = new(yaooc_ipaddress);
	char msg[128];
	cmp_test_ip* ipt=ip4_tests;
	for(;ipt->lhs != NULL;ipt++) {
		M(lhs,set,ipt->lhs);
		M(rhs,set,ipt->rhs);
		int result = ipt->result;
		sprintf(msg,"operator == : '%s' is%s equal to '%s'",ipt->lhs,(result==0 ? "" :" not"),ipt->rhs);
		TEST(msg,op_eq(lhs,rhs) == (result == 0));
		sprintf(msg,"operator != : '%s' is%s equal to '%s'",ipt->lhs,(result!=0 ? " not" : "" ),ipt->rhs);
		TEST(msg,op_ne(lhs,rhs) == (result != 0));
		sprintf(msg,"operator >  : '%s' is%s greater than '%s'",ipt->lhs,(result > 0 ? "" :" not"),ipt->rhs);
		TEST(msg,op_gt(lhs,rhs) == (result >  0));
		sprintf(msg,"operator >= : '%s' is%s greater than or equal to '%s'",ipt->lhs,(result >= 0 ? "" :" not"),ipt->rhs);
		TEST(msg,op_ge(lhs,rhs) == (result >= 0));
		sprintf(msg,"operator <  : '%s' is%s less than '%s'",ipt->lhs,(result > 0 ? "" :" not"),ipt->rhs);
		TEST(msg,op_lt(lhs,rhs) == (result <  0));
		sprintf(msg,"operator <= : '%s' is%s less than or equal to '%s'",ipt->lhs,(result > 0 ? "" :" not"),ipt->rhs);
		TEST(msg,op_le(lhs,rhs) == (result <= 0));
	}

}

cmp_test_ip ip6_tests[] = {
	{ "::1" , "2600:1700:3901:1b80:7a2b:cbff:fea1:b6d" , -1},
	{ "2600:1700:3901:1b80:7a2b:cbff:fea1:b6d" , "::1" , 1},
	{ "2600:1700:3901:1b80:7a2b:cbff:fea1:b6d" , "2600:1700:3901:1b80:7a2b:cbff:fea1:b6d" , 0},
	{ "2600:1700:3901:1b80:7a2b:cbff:fea1:b6d" , "2600:1700:3901:1b80:baac:6fff:fea2:906a" , -1},
	{ "2600:1700:3901:1b80:baac:6fff:fea2:906a" ,"2600:1700:3901:1b80:7a2b:cbff:fea1:b6d" , 1},
	{ NULL, NULL, 0 }
};

void test_cmp_ip6()
{
	yaooc_ipaddress_t* lhs = new(yaooc_ipaddress);
	yaooc_ipaddress_t* rhs = new(yaooc_ipaddress);
	char msg[128];
	cmp_test_ip* ipt=ip6_tests;
	for(;ipt->lhs != NULL;ipt++) {
		M(lhs,set,ipt->lhs);
		M(rhs,set,ipt->rhs);
		int result = ipt->result;
		sprintf(msg,"operator == : '%s' is%s equal to '%s'",ipt->lhs,(result==0 ? "" :" not"),ipt->rhs);
		TEST(msg,op_eq(lhs,rhs) == (result == 0));
		sprintf(msg,"operator != : '%s' is%s equal to '%s'",ipt->lhs,(result!=0 ? " not" : "" ),ipt->rhs);
		TEST(msg,op_ne(lhs,rhs) == (result != 0));
		sprintf(msg,"operator >  : '%s' is%s greater than '%s'",ipt->lhs,(result > 0 ? "" :" not"),ipt->rhs);
		TEST(msg,op_gt(lhs,rhs) == (result >  0));
		sprintf(msg,"operator >= : '%s' is%s greater than or equal to '%s'",ipt->lhs,(result >= 0 ? "" :" not"),ipt->rhs);
		TEST(msg,op_ge(lhs,rhs) == (result >= 0));
		sprintf(msg,"operator <  : '%s' is%s less than '%s'",ipt->lhs,(result > 0 ? "" :" not"),ipt->rhs);
		TEST(msg,op_lt(lhs,rhs) == (result <  0));
		sprintf(msg,"operator <= : '%s' is%s less than or equal to '%s'",ipt->lhs,(result > 0 ? "" :" not"),ipt->rhs);
		TEST(msg,op_le(lhs,rhs) == (result <= 0));
	}
}

test_function tests[]=
{
  test_sizes,
	test_default_ctor,
	test_ip4,
	test_ip6,
	test_cmp_ip4,
	test_cmp_ip6
};

STD_MAIN(tests)
