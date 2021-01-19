#ifndef __DATE_TIME_INCLUDED__
#define __DATE_TIME_INCLUDED__
#include <yaooc/new.h>
#include <yaooc/object.h>
#include <yaooc/string.h>
#include <yaooc/stream.h>

yaooc_class_table(yaooc_date_time) {
  yaooc_object_class_table_t;
void (*set)(pointer,time_t);
void (*set_ymdhms)(pointer,int,int,int,int,int,int);
void (*set_ymd)(pointer,int,int,int,int,int,int);
void (*set_hms)(pointer,int,int,int);
time_t (*get)(const_pointer);
int (*month)(const_pointer);
int (*day)(const_pointer);
int (*year)(const_pointer);
int (*hour)(const_pointer);
int (*minute)(const_pointer);
int (*second)(const_pointer);
int (*day_of_week)(const_pointer);
int (*day_of_year)(const_pointer);
char* (*strftime)(pointer,const char*);
};
#define yaooc_date_time_parent_class_table ((yaooc_object_class_table_t*)(yaooc_date_time_class_table.parent_class_table_))

yaooc_class_instance(yaooc_date_time) {
time_t time_;
};

yaooc_class(yaooc_date_time);
void yaooc_date_time_default_ctor(pointer);
void yaooc_date_time_copy_ctor(pointer,const_pointer);
void yaooc_date_time_assign(pointer,const_pointer);
int yaooc_date_time_rich_compare(const_pointer,const_pointer);
void yaooc_date_time_to_stream(const_pointer,ostream_pointer);
void yaooc_date_time_ctor_int(pointer,va_list);
void yaooc_date_time_ctor_ymdhms(pointer,va_list);
void yaooc_date_time_ctor_ymd(pointer,va_list);
void yaooc_date_time_ctor_hms(pointer,va_list);
void yaooc_date_time_ctor_tm(pointer,va_list);
void yaooc_date_time_ctor_ccs(pointer,va_list);
 void yaooc_date_time_swap(pointer,pointer);
 void yaooc_date_time_set(pointer,time_t);
 void yaooc_date_time_set_ymdhms(pointer,int,int,int,int,int,int);
 void yaooc_date_time_set_ymd(pointer,int,int,int,int,int,int);
 void yaooc_date_time_set_hms(pointer,int,int,int);
 time_t yaooc_date_time_get(const_pointer);
 int yaooc_date_time_month(const_pointer);
 int yaooc_date_time_day(const_pointer);
 int yaooc_date_time_year(const_pointer);
 int yaooc_date_time_hour(const_pointer);
 int yaooc_date_time_minute(const_pointer);
 int yaooc_date_time_second(const_pointer);
 int yaooc_date_time_day_of_week(const_pointer);
 int yaooc_date_time_day_of_year(const_pointer);
 char* yaooc_date_time_strftime(pointer,const char*);

#endif
