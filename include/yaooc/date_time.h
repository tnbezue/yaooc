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

#ifndef __DATE_TIME_INCLUDED__
#define __DATE_TIME_INCLUDED__

#include <yaooc/string.h>
#include <yaooc/stream.h>

/*  Begin YAOOC PreProcessor generated content */


/*
  Class definition for yaooc_date_time
*/
yaooc_class_table(yaooc_date_time)
{
  yaooc_object_class_table_t;
  void (*set)(pointer,time_t);
  time_t (*get)(const_pointer);
  int (*month)(const_pointer);
  int (*day)(const_pointer);
  int (*year)(const_pointer);
  int (*hour)(const_pointer);
  int (*minute)(const_pointer);
  int (*second)(const_pointer);
  int (*day_of_week)(const_pointer);
  int (*day_of_year)(const_pointer);
  char* (*strftime)(const_pointer,const char*);
};
#define yaooc_date_time_parent_class_table ((yaooc_object_class_table_t*)(yaooc_date_time_class_table.parent_class_table_))

yaooc_class_instance(yaooc_date_time)
{
  yaooc_object_class_instance_t;
  time_t time_;
};

yaooc_class(yaooc_date_time);

/* Prototypes for yaooc_date_time type info */
void yaooc_date_time_default_ctor(pointer);
void yaooc_date_time_copy_ctor(pointer,const_pointer);
#define yaooc_date_time_assign yaooc_date_time_copy_ctor
bool yaooc_date_time_less_than_compare(const_pointer,const_pointer);
void yaooc_date_time_to_stream(const_pointer,pointer);
void yaooc_date_time_from_stream(pointer,pointer);

/* Prototypes for yaooc_date_time constructors */
void yaooc_date_time_ctor_int(pointer,va_list);
void yaooc_date_time_ctor_ymdhms(pointer,va_list);
void yaooc_date_time_ctor_tm(pointer,va_list);
void yaooc_date_time_ctor_ccs(pointer,va_list);

/* Prototypes for yaooc_date_time class table */
void yaooc_date_time_swap(pointer,pointer);
void yaooc_date_time_set(pointer,time_t);
time_t yaooc_date_time_get(const_pointer);
int yaooc_date_time_month(const_pointer);
int yaooc_date_time_day(const_pointer);
int yaooc_date_time_year(const_pointer);
int yaooc_date_time_hour(const_pointer);
int yaooc_date_time_minute(const_pointer);
int yaooc_date_time_second(const_pointer);
int yaooc_date_time_day_of_week(const_pointer);
int yaooc_date_time_day_of_year(const_pointer);
char* yaooc_date_time_strftime(const_pointer,const char*);

/* Prototypes for yaooc_date_time protected members */

/*  End YAOOC PreProcessor generated content */

#endif
