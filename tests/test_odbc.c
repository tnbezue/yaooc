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
#include <unistd.h>
#include <libgen.h>
#include <yaooc/odbc.h>
#include <yaooc/stream.h>
#include "test_harness.h"

char sqlite_connect_string[1024]="DRIVER=SQLite3;Database=";

void test_get_drivers()
{
	map_odbc_string_string_t *drivers=yaooc_odbc_environment_get_drivers(NULL);
	map_odbc_string_string_const_iterator i;
	printf("Found %zu drivers\n",M(drivers,size));
	for(i=M(drivers,begin);i!=M(drivers,end);i++)
		printf("%s %s\n",M(&i->first,c_str),M(&i->second,c_str));
	delete(drivers);
}

void test_get_sources()
{
	map_odbc_string_string_t *drivers=yaooc_odbc_environment_get_sources(NULL);
	map_odbc_string_string_const_iterator i;
	printf("Found %zu sources\n",M(drivers,size));
	for(i=M(drivers,begin);i!=M(drivers,end);i++)
		printf("%s %s\n",M(&i->first,c_str),M(&i->second,c_str));
	delete(drivers);
}

void test_sqlite_select()
{
/*	yaooc_odbc_integer_t* id = new(yaooc_odbc_integer);
	yaooc_odbc_string_t* lname = new(yaooc_odbc_string);
	yaooc_odbc_string_t* fname =  new(yaooc_odbc_string);
	yaooc_odbc_timestamp_t* birthday =  new(yaooc_odbc_timestamp);
	yaooc_odbc_real_t* salary =  new(yaooc_odbc_real);*/
	int id;
	char lname[64],fname[64];
	char birthday[64];
	double salary;
	yaooc_odbc_connection_t* con = new(yaooc_odbc_connection);
//	con.connect("DRIVER=SQLite;Database=mytest.db");
	M(con,connect,sqlite_connect_string);
	TEST("Connection",con);
	if(con) {
		yaooc_odbc_statement_t* stmt = M(con,exec_direct,"select * from Demo");
		if(stmt) {
				M(stmt,bindcol_int,&id);
				M(stmt,bindcol_str,lname,64);
				M(stmt,bindcol_str,fname,64);
				M(stmt,bindcol_str,birthday,64);
				M(stmt,bindcol_dbl,&salary);
//			stmt.bindcols(row);
			while(M(stmt,fetch)) {
/*				struct tm tm=M(birthday,get_tm);
				char date_str[64];
				strftime(date_str,64,"%c",&tm);*/
				printf("%d %s %s %s %.2lf\n",id,lname,fname,birthday,salary);
			}
			delete(stmt);
		}
	} else
		puts("Failed connect");
//	DELETE_LIST(id,lname,fname,birthday,salary,con);
	delete(con);
}

typedef struct  {
	const char* lname;
	const char* fname;
	const char* birthday;
	double salary;
} sqlite_schema_t;

sqlite_schema_t sdata[] = {
	{ "Mouse","Mickey","1928-11-29 00:00:00",88000.0 },
	{ "Bunny","Bugs","1940-07-27 00:00:00",88000.0 },
	{ "Simpson","Homer","1956-05-12 17:32:53",50000.20 }
};

void test_sqlite_insert()
{
	yaooc_odbc_connection_t* con = new(yaooc_odbc_connection);
	char lname[64],fname[64];
	char birthday[64];
	double salary;
	M(con,connect,sqlite_connect_string);
	TEST("Connection",con);
	int nData=sizeof(sdata)/sizeof(sdata[0]);
	if(con) {
		yaooc_odbc_statement_t *stmt=M(con,prepare,"insert into Demo (lname,fname,birthday,salary) values (?,?,?,?)");
		if(stmt) {
			bool rc = M(stmt,bindparam_str,lname,64);
			rc = rc && M(stmt,bindparam_str,fname,64);
			rc = rc && M(stmt,bindparam_str,birthday,64);
			rc = rc && M(stmt,bindparam_dbl,&salary);
			if(rc) {
				for(int i=0;i<nData;i++) {
					strcpy(lname,sdata[i].lname);
					strcpy(fname,sdata[i].fname);
/*					struct tm tm;
					memset(&tm,0,sizeof(struct tm));
					strptime(sdata[i].birthday,"%Y-%m-%d %H:%M:%S",&tm);*/
/*					if(*ptr != 0)
						puts("Failed");
					printf("%zd\n",mktime(&tm));*/
					strcpy(birthday,sdata[i].birthday);
					salary = sdata[i].salary;
					if(!M(stmt,execute)) {
						puts("Execute failed");
						break;
					}
				}
				} else {
					puts("Failed to bind");
			}
			M(con,commit);
			delete(stmt);
		}
		delete(con);
	}
}

#if 0
void test_substr()
{
	const char* str="this is the test string";

	yaooc_string_t* s1=new(yaooc_string);

	yaooc_string_t* s2 = M(s1,substr,0,20);
	TEST("Substr of empty string is empty string",M(s2,size) == 0);
  delete(s2);

	M(s1,append,str);
	TEST("String matches str",strcmp(M(s1,c_str),str)==0);
	s2 = M(s1,substr,0,5);
	TEST("substr 0 5",strcmp(M(s2,c_str),"this ")==0);
  delete(s2);

	s2 = M(s1,substr,0,-1);
	TEST("substr 0 -1 is entire string",strcmp(M(s2,c_str),str)==0);
  delete(s2);

  /*	s2 = M(s1,substr,100,-1);
	TEST("substr beyond end is empty string",M(s2,size) == 0);
	*/
	s2 = M(s1,substr,5,0);
	TEST("substr retrieving 0 chars is empty string",M(s2,size) == 0);
  delete(s2);
  delete(s1);
}

void test_append()
{
	const char* str1="This is";
	const char* str2=" a test";

	yaooc_string_t* s1=new(yaooc_string);
	TEST("s1 is empty",M(s1,size) == 0);

	M(s1,append,str1);
	TEST("s1 equal str1",strcmp(M(s1,c_str),str1)==0);

	M(s1,appendn,str2,2);
	TEST("s1 equal str1",strcmp(M(s1,c_str),"This is a")==0);

	M(s1,append,str2+2);
	TEST("s1 equal str1",strcmp(M(s1,c_str),"This is a test")==0);
  delete(s1);
}

void test_set()
{
  TESTCASE("SET");
  yaooc_string_t* s1=new(yaooc_string);
	TEST("s1 is empty",M(s1,size) == 0);

  M(s1,set,"Testing");

  TEST("s1 is \"Testing\"",strcmp(M(s1,c_str),"Testing")==0);

  M(s1,setn,"This is a test",10);
  TEST("s1 is \"This is a \"",strcmp(M(s1,c_str),"This is a ")==0);
  TEST("Size is 10",M(s1,size)==10);
  delete(s1);
}

#endif

test_function tests[]=
{
	test_get_drivers,
	test_get_sources,
	test_sqlite_select,
	test_sqlite_insert,
};

void create_sqlite_db(const char* exe)
{
	// get location of this executable
	char* ptr=sqlite_connect_string + strlen(sqlite_connect_string);
	if(exe[0]=='/') { // absolute path
		strncpy(ptr,exe,1023);
	} else { // relative path
		getcwd(ptr,1024);
		strcat(ptr,"/");
		strcat(ptr,exe);
	}
	// Make connect string
	strcpy(ptr,dirname(ptr));
	strcat(ptr,"/test_sqlite.db");

	// If database does not exist, create if
	if(access(ptr,R_OK) != 0) {
		yaooc_odbc_connection_t* con = new(yaooc_odbc_connection);
		M(con,connect,sqlite_connect_string);
		M(con,exec_direct,"CREATE TABLE Demo (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, lname varchar(255),fname varchar(255),birthday timestamp, salary decimal(12,2));");
		M(con,commit);
		delete(con);
	}
}

int main(int argc,char*argv[])
{
	setbuf(stdout,NULL);
	setbuf(stderr,NULL);
	yaooc_init();
	output=(char*)malloc(10240);
	optr=NULL;
  srand(time(NULL));

	yaooc_odbc_environment_t* env=new(yaooc_odbc_environment);
	create_sqlite_db(argv[0]);

	int ntest=sizeof(tests)/sizeof(tests[0]);
	if(argc == 1)
		{ TEST_ALL(tests); }
	else {
		for(int i=1;i<argc;i++) {
      optr=NULL;
			int itest=atoi(argv[i]);
			if(itest >=0 && itest < ntest)
				tests[itest]();
			else
				printf("No test for %d\n",itest);
		}
	}
	FINAL_SUMMARY;
	free(output);
	delete(env);
	return 0;
}
