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
#include <yaooc/date_time.h>
#include <yaooc/sstream.h>
#include "test_harness.h"

void test_construtor()
{
	time_t now=time(NULL);
	yaooc_date_time_t* dt=new(yaooc_date_time);
	TEST("Time is current",(dt->time_-now)<=1);
	delete(dt);

	dt=new_ctor(yaooc_date_time,yaooc_date_time_ctor_ymdhms,2016,10,10,2,37,21);
	TEST("DT is 1476081441",dt->time_==1476081441);
	delete(dt);

	dt=new_ctor(yaooc_date_time,yaooc_date_time_ctor_int,1458254743);
	TEST("Time set to 'Thu Mar 17 18:45:43 2016'",strncmp(ctime(&dt->time_),"Thu Mar 17 18:45:43 2016",24)==0);
	delete(dt);

	struct tm tm;
	memset(&tm,0,sizeof(struct tm));
	tm.tm_year=103;
	tm.tm_mon=3;
	tm.tm_mday=17;
	tm.tm_hour=19;
	tm.tm_min=16;
	tm.tm_sec=5;
	tm.tm_isdst=-1;
	dt=new_ctor(yaooc_date_time,yaooc_date_time_ctor_tm,&tm);
	TEST("DT is 1050621365",dt->time_==1050621365);
	delete(dt);

	dt=new_ctor(yaooc_date_time,yaooc_date_time_ctor_ccs,"2010-05-31 12:00:00");
	TEST("DT is 1275321600",dt->time_==1275321600);
	delete(dt);
}

void test_stream()
{
	/* Output stream */
	yaooc_date_time_t* dt=new(yaooc_date_time);
	char* time_str=ctime(&dt->time_);
	yaooc_ostringstream_t* os=new(yaooc_ostringstream);
	STREAM(os,dt,endl);
	TEST("Time string is correct",strcmp(M(os,c_str),time_str)==0);

	/* Input Stream */
	yaooc_istringstream_t* is=new_ctor(yaooc_istringstream,yaooc_istringstream_ctor_ccs,"x 10/10/60 2:37:21");
	time_t temp=dt->time_;
	STREAM(is,dt);
	TEST("DT unchanged",dt->time_==temp);
	TEST("Stream pos not changed",M(is,tell)==0);

	M(is,set,"10/10/2014 2:37:21 x");
	STREAM(is,dt);
	TEST("DT is 1412923041",dt->time_==1412923041);
	TEST("Stream pos is 18",M(is,tell)==18);

	M(is,set,"Tue Nov 4 23:30:00 2008   ");
	STREAM(is,dt);
	TEST("DT is 1225859400",dt->time_==1225859400);
	TEST("Stream pos is 23",M(is,tell)==23);

	M(is,set,"  2000-10-28   ");
	STREAM(is,dt);
	TEST("DT is 972705600",dt->time_==972705600);
	TEST("Stream pos is 12",M(is,tell)==12);

	M(is,set,"  01/20/2009   ");
	STREAM(is,dt);
	TEST("DT is 1232427600",dt->time_==1232427600);
	TEST("Stream pos is 12",M(is,tell)==12);

	time_t now=time(NULL);
	struct tm tm;
	memcpy(&tm,localtime(&now),sizeof(struct tm));
	tm.tm_hour=0;
	tm.tm_min=0;
	tm.tm_sec=0;
	time_t midnight=mktime(&tm);
	M(is,set,"  8:15:33  ");
	STREAM(is,dt);
	TEST("DT is 29733 seconds past midnight",dt->time_==(midnight+29733));
	TEST("Stream pos is 9",M(is,tell)==9);

	delete_list(dt,os,is);
}

test_function tests[]=
{
	test_construtor,
	test_stream,
};

STD_MAIN(tests)
