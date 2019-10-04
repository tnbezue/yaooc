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

#include <time.h>
#include <yaooc/date_time.h>
#include <yaooc/sstream.h>
#include <string.h>

/*  Begin YAOOC PreProcessor generated content */


/* yaooc_date_time private members */

/* yaooc_date_time type info members */
void yaooc_date_time_default_ctor(pointer p)
{
  yaooc_date_time_pointer this=p;
	this->time_=time(NULL);
}

void yaooc_date_time_copy_ctor(pointer p,const_pointer s)
{
  yaooc_date_time_pointer this=p;
  yaooc_date_time_const_pointer src=s;
	this->time_=src->time_;
}

int yaooc_date_time_rich_compare(const_pointer p1,const_pointer p2)
{
  yaooc_date_time_const_pointer vp1=p1;
  yaooc_date_time_const_pointer vp2=p2;
  return vp1->time_-vp2->time_ ;

}
void yaooc_date_time_to_stream(const_pointer p,pointer s)
{
  yaooc_date_time_const_pointer this=p;
  yaooc_ostream_pointer strm=s;
	struct tm* tm=localtime(&this->time_);
	char dstr[64];
	strftime(dstr,64,"%c",tm);
	M(strm,printf,"%s",dstr);
}

static const char* short_day_of_week[]= { "sun","mon","tue","wed","thu","fri","sat"};
static const char* long_day_of_week[]= { "sunday","monday","tuesday","wednesday","thursday","friday","saturday" };
static const char* short_month[]={"jan","feb","mar","apr","may","jun","jul","aug","sep","oct","nov","dec"};
static const char* long_month[]={"january","february","march","april","may","june","july","august","september","october","november","december"};
static int day_of_week(const char* str)
{
	int i;
	for(i=0;i<7;i++)
		if(strcasecmp(str,short_day_of_week[i])==0)
			return i;
	for(i=0;i<7;i++)
		if(strcasecmp(str,long_day_of_week[i])==0)
			return i;
	return -1;
}

static int month_of_year(const char* str)
{
	int i;
	for(i=0;i<12;i++)
		if(strcasecmp(str,short_month[i])==0)
			return i;
	for(i=0;i<12;i++)
		if(strcasecmp(str,long_month[i])==0)
			return i;
	return -1;
}

/* Trys to read date as if strftime had used "%a %b %d %H:%M:%S %Y" */
static bool read_abdHMSY(yaooc_istream_pointer strm,struct tm* tm)
{
	char mon[16],dow[16];
	int n=M(strm,scanf,"%15s %15s %d %d:%d:%d %d",dow,mon,&tm->tm_mday,&tm->tm_hour,&tm->tm_min,&tm->tm_sec,&tm->tm_year);
	if(n==7) {
		if(day_of_week(dow)>=0) {
			if((tm->tm_mon=month_of_year(mon)) >= 0) {
				tm->tm_year -= 1900;
				return true;
			}
		}
	}
	return false;
}

static bool read_date_only(yaooc_istream_pointer strm,struct tm* tm)
{
	long pos=M(strm,tell);
	int n=M(strm,scanf,"%d-%d-%d",&tm->tm_year,&tm->tm_mon,&tm->tm_mday);
	if(n!=3) {
		M(strm,seek,pos,SEEK_SET);
		n=M(strm,scanf,"%d/%d/%d",&tm->tm_mon,&tm->tm_mday,&tm->tm_year);
	}
	if(n==3) {
		if(tm->tm_year > 1900)
			tm->tm_year -= 1900;
		tm->tm_mon--;
		return true;
	}
	return false;
}

static bool read_time_only(yaooc_istream_pointer strm,struct tm* tm)
{
	char ampm[4];
	int n=M(strm,scanf,"%d:%d:%d",&tm->tm_hour,&tm->tm_min,&tm->tm_sec);
	if(n==3) {
		/* Valid time.  Check if AM/PM specified */
		long_t pos=M(strm,tell);
		n=M(strm,scanf,"%3s",ampm);
		if(n==1 && (strcasecmp(ampm,"am")==0 || strcasecmp(ampm,"pm") ==0)) {
			if(strcasecmp(ampm,"pm") == 0 && tm->tm_hour < 12)
				tm->tm_hour+=12;
		} else {
			M(strm,seek,pos,SEEK_SET);
		}
		return true;
	}
	return false;
}

void yaooc_date_time_from_stream(pointer p,pointer s)
{
  yaooc_date_time_pointer this=p;
  yaooc_istream_pointer strm=s;
	ulong_t pos=M(strm,tell); /* Hold string pos in case read fails */
	struct tm tm,tm_now;
	bool success=false;
	/*
		Try various format types
	*/
//	int year,day,hour,min,sec;
	memset(&tm,0,sizeof(struct tm));
	if(!(success=read_abdHMSY(strm,&tm))) {
	memset(&tm,0,sizeof(struct tm));
		M(strm,seek,pos,SEEK_SET);
		if(!(success=(read_date_only(strm,&tm) && read_time_only(strm,&tm)))) {
			memset(&tm,0,sizeof(struct tm));
			M(strm,seek,pos,SEEK_SET);
			if(!(success=read_date_only(strm,&tm))) {
				memset(&tm,0,sizeof(struct tm));
				M(strm,seek,pos,SEEK_SET);
				if((success=read_time_only(strm,&tm))) {
					time_t now=time(NULL);
					memcpy(&tm_now,localtime(&now),sizeof(struct tm));
					tm.tm_year=tm_now.tm_year;
					tm.tm_mon=tm_now.tm_mon;
					tm.tm_mday=tm_now.tm_mday;
				}
			}
		}
	}
	if(success) {
		tm.tm_isdst=-1;
		this->time_=mktime(&tm);
	} else {
		M(strm,seek,pos,SEEK_SET);
	}
}


/* Constructors for yaooc_date_time */
void yaooc_date_time_ctor_int(pointer p,va_list args)
{
  yaooc_date_time_pointer this=p;
  this->time_ = va_arg(args,int);
}

void yaooc_date_time_ctor_ymdhms(pointer p,va_list args)
{
  yaooc_date_time_pointer this=p;
	struct tm tm;
	time_t now=time(NULL);
	memcpy(&tm,localtime(&now),sizeof(struct tm));
	tm.tm_isdst=-1;
  tm.tm_year = va_arg(args,int)-1900;
  tm.tm_mon = va_arg(args,int)-1;
  tm.tm_mday = va_arg(args,int);
  tm.tm_hour = va_arg(args,int);
  tm.tm_min = va_arg(args,int);
  tm.tm_sec = va_arg(args,int);
	this->time_=mktime(&tm);
}

void yaooc_date_time_ctor_tm(pointer p,va_list args)
{
  yaooc_date_time_pointer this=p;
	struct tm tm;
  memcpy(&tm,va_arg(args,const struct tm*),sizeof(struct tm));
	this->time_=mktime(&tm);
}

void yaooc_date_time_ctor_ccs(pointer p,va_list args)
{
//  yaooc_date_time_pointer this=p;
  const char* str = va_arg(args,const char*);
	yaooc_istringstream_t* is=new_ctor(yaooc_istringstream,yaooc_istringstream_ctor_ccs,str);
	yaooc_date_time_from_stream(p,is);
	delete(is);
}



/* yaooc_date_time protected members */

/* Class table methods for yaooc_date_time */
void yaooc_date_time_swap(pointer p,pointer o)
{
  yaooc_date_time_pointer this=p;
	yaooc_date_time_pointer other=o;
	SWAP(time_t,this->time_,other->time_);
}

void yaooc_date_time_set(pointer p,time_t t)
{
  yaooc_date_time_pointer this=p;
	this->time_=t;
}

time_t yaooc_date_time_get(const_pointer p)
{
  yaooc_date_time_const_pointer this=p;
	return this->time_;
}

int yaooc_date_time_month(const_pointer p)
{
  yaooc_date_time_const_pointer this=p;
	return localtime(&this->time_)->tm_mon;
}

int yaooc_date_time_day(const_pointer p)
{
  yaooc_date_time_const_pointer this=p;
	return localtime(&this->time_)->tm_mday;
}

int yaooc_date_time_year(const_pointer p)
{
  yaooc_date_time_const_pointer this=p;
	return localtime(&this->time_)->tm_year;
}

int yaooc_date_time_hour(const_pointer p)
{
  yaooc_date_time_const_pointer this=p;
	return localtime(&this->time_)->tm_hour;
}

int yaooc_date_time_minute(const_pointer p)
{
  yaooc_date_time_const_pointer this=p;
	return localtime(&this->time_)->tm_min;
}

int yaooc_date_time_second(const_pointer p)
{
  yaooc_date_time_const_pointer this=p;
	return localtime(&this->time_)->tm_sec;
}

int yaooc_date_time_day_of_week(const_pointer p)
{
  yaooc_date_time_const_pointer this=p;
	return localtime(&this->time_)->tm_wday;
}

int yaooc_date_time_day_of_year(const_pointer p)
{
  yaooc_date_time_const_pointer this=p;
	return localtime(&this->time_)->tm_yday;
}

char* yaooc_date_time_strftime(const_pointer p,const char* fmt)
{
  yaooc_date_time_const_pointer this=p;
	if(fmt==NULL || strlen(fmt)==0)
		fmt="%c";
	char* temp=new_array(char,64);
	strftime(temp,64,fmt,localtime(&this->time_));
  return temp;
}


/* Class table for yaooc_date_time */
yaooc_date_time_class_table_t yaooc_date_time_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "yaooc_date_time_t",
  .swap = (void (*) (pointer,pointer)) yaooc_date_time_swap,
  .set = (void (*) (pointer,time_t)) yaooc_date_time_set,
  .get = (time_t (*) (const_pointer)) yaooc_date_time_get,
  .month = (int (*) (const_pointer)) yaooc_date_time_month,
  .day = (int (*) (const_pointer)) yaooc_date_time_day,
  .year = (int (*) (const_pointer)) yaooc_date_time_year,
  .hour = (int (*) (const_pointer)) yaooc_date_time_hour,
  .minute = (int (*) (const_pointer)) yaooc_date_time_minute,
  .second = (int (*) (const_pointer)) yaooc_date_time_second,
  .day_of_week = (int (*) (const_pointer)) yaooc_date_time_day_of_week,
  .day_of_year = (int (*) (const_pointer)) yaooc_date_time_day_of_year,
  .strftime = (char* (*) (const_pointer,const char*)) yaooc_date_time_strftime,
};

DEFINE_TYPE_INFO(yaooc_date_time,Y,N,Y,Y,Y,Y,Y,Y,yaooc_object);

/*  End YAOOC PreProcessor generated content */
