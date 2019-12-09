#include <yaooc/date_time.h>
#include <time.h>
#include <yaooc/sstream.h>
#include <string.h>


void yaooc_date_time_default_ctor(pointer __pthis__)
{
yaooc_date_time_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_date_time);



      this->time_=time(NULL);
    
}
void yaooc_date_time_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaooc_date_time_pointer this=__pthis__;(void)this;
yaooc_date_time_const_pointer src=__psrc__;(void)src;


call_default_ctor_static(this,yaooc_date_time);
assign_static(this,src,yaooc_date_time);

}
void yaooc_date_time_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_date_time_pointer this=__pthis__;(void)this;
yaooc_date_time_const_pointer src=__psrc__;(void)src;


      this->time_=src->time_;
    
}
int yaooc_date_time_rich_compare(const_pointer __plhs__,const_pointer __prhs__)
{
yaooc_date_time_const_pointer lhs=__plhs__;(void)lhs;
yaooc_date_time_const_pointer rhs=__prhs__;(void)rhs;

      return lhs->time_ - rhs->time_;
    
}
void yaooc_date_time_to_stream(const_pointer __pthis__,ostream_pointer __pstrm__)
{
yaooc_date_time_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__pstrm__;(void)ostrm;


      struct tm* tm=localtime(&this->time_);
      char dstr[64];
      strftime(dstr,64,"%c",tm);
      M(ostrm,printf,"%s",dstr);
    
}
void yaooc_date_time_ctor_int(pointer __pthis,va_list __con_args__){
yaooc_date_time_pointer this=__pthis;(void)this;
time_t t = va_arg(__con_args__,time_t);

call_default_ctor_static(this,yaooc_date_time);


      M(this,set,t);
    
}
void yaooc_date_time_ctor_ymdhms(pointer __pthis,va_list __con_args__){
yaooc_date_time_pointer this=__pthis;(void)this;
int y = va_arg(__con_args__,int);
int mon = va_arg(__con_args__,int);
int d = va_arg(__con_args__,int);
int h = va_arg(__con_args__,int);
int min = va_arg(__con_args__,int);
int s = va_arg(__con_args__,int);

call_default_ctor_static(this,yaooc_date_time);


      M(this,set_ymdhms,y,mon,d,h,min,s);
    
}
void yaooc_date_time_ctor_ymd(pointer __pthis,va_list __con_args__){
yaooc_date_time_pointer this=__pthis;(void)this;
int y = va_arg(__con_args__,int);
int mon = va_arg(__con_args__,int);
int d = va_arg(__con_args__,int);

call_constructor(this,yaooc_date_time_ctor_ymdhms,y,mon,d,0,0,0);


    
}
void yaooc_date_time_ctor_hms(pointer __pthis,va_list __con_args__){
yaooc_date_time_pointer this=__pthis;(void)this;
int h = va_arg(__con_args__,int);
int min = va_arg(__con_args__,int);
int s = va_arg(__con_args__,int);

call_default_ctor_static(this,yaooc_date_time);


      M(this,set_hms,h,min,s);
    
}
void yaooc_date_time_ctor_tm(pointer __pthis,va_list __con_args__){
yaooc_date_time_pointer this=__pthis;(void)this;
const struct tm* tm = va_arg(__con_args__,const struct tm*);

call_parent_default_ctor_static(this,yaooc_date_time);


      struct tm tm2;
      memcpy(&tm2,tm,sizeof(struct tm));
      this->time_=mktime(&tm2);
    
}
void yaooc_date_time_ctor_ccs(pointer __pthis,va_list __con_args__){
yaooc_date_time_pointer this=__pthis;(void)this;
const char* str = va_arg(__con_args__,const char*);

call_default_ctor_static(this,yaooc_date_time);


    
}
void yaooc_date_time_swap(pointer __pthis__,pointer p)
{
yaooc_date_time_pointer this=__pthis__;(void)this;
#define super() yaooc_date_time_parent_class_table->swap(this,p)
#define PM(method,...) CTM((*yaooc_date_time_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_date_time_pointer other=p;
      SWAP(time_t,this->time_,other->time_);
    
#undef PM
#undef super
}
void yaooc_date_time_set(pointer __pthis__,time_t t)
{
yaooc_date_time_pointer this=__pthis__;(void)this;
#define super() yaooc_date_time_parent_class_table->set(this,t)
#define PM(method,...) CTM((*yaooc_date_time_parent_class_table),this,method,## __VA_ARGS__)


      this->time_=t;
    
#undef PM
#undef super
}
void yaooc_date_time_set_ymdhms(pointer __pthis__,int y,int mon,int d,int h,int min,int s)
{
yaooc_date_time_pointer this=__pthis__;(void)this;
#define super() yaooc_date_time_parent_class_table->set_ymdhms(this,y,mon,d,h,min,s)
#define PM(method,...) CTM((*yaooc_date_time_parent_class_table),this,method,## __VA_ARGS__)


      struct tm tm;
      memset(&tm,0,sizeof(struct tm));
      tm.tm_year = y-1900;
      tm.tm_mon = mon-1;
      tm.tm_mday = d;
      tm.tm_hour = h;
      tm.tm_min = min;
      tm.tm_sec = s;
      this->time_=mktime(&tm);
    
#undef PM
#undef super
}
void yaooc_date_time_set_ymd(pointer __pthis__,int y,int mon,int d,int h,int min,int s)
{
yaooc_date_time_pointer this=__pthis__;(void)this;
#define super() yaooc_date_time_parent_class_table->set_ymd(this,y,mon,d,h,min,s)
#define PM(method,...) CTM((*yaooc_date_time_parent_class_table),this,method,## __VA_ARGS__)


      M(this,set_ymdhms,y,mon,d,0,0,0);
    
#undef PM
#undef super
}
void yaooc_date_time_set_hms(pointer __pthis__,int h,int min,int s)
{
yaooc_date_time_pointer this=__pthis__;(void)this;
#define super() yaooc_date_time_parent_class_table->set_hms(this,h,min,s)
#define PM(method,...) CTM((*yaooc_date_time_parent_class_table),this,method,## __VA_ARGS__)


      struct tm tm;
      time_t t=time(NULL);
      localtime_r(&t,&tm);
      tm.tm_hour=h;
      tm.tm_min=min;
      tm.tm_sec=s;
      this->time_=mktime(&tm);
    
#undef PM
#undef super
}
time_t yaooc_date_time_get(const_pointer __pthis__)
{
yaooc_date_time_const_pointer this=__pthis__;(void)this;
#define super() yaooc_date_time_parent_class_table->get(this)
#define PM(method,...) CTM((*yaooc_date_time_parent_class_table),this,method,## __VA_ARGS__)

 return this->time_; 
#undef PM
#undef super
}
int yaooc_date_time_month(const_pointer __pthis__)
{
yaooc_date_time_const_pointer this=__pthis__;(void)this;
#define super() yaooc_date_time_parent_class_table->month(this)
#define PM(method,...) CTM((*yaooc_date_time_parent_class_table),this,method,## __VA_ARGS__)


      return localtime(&this->time_)->tm_mon+1;
    
#undef PM
#undef super
}
int yaooc_date_time_day(const_pointer __pthis__)
{
yaooc_date_time_const_pointer this=__pthis__;(void)this;
#define super() yaooc_date_time_parent_class_table->day(this)
#define PM(method,...) CTM((*yaooc_date_time_parent_class_table),this,method,## __VA_ARGS__)


      return localtime(&this->time_)->tm_mday;
    
#undef PM
#undef super
}
int yaooc_date_time_year(const_pointer __pthis__)
{
yaooc_date_time_const_pointer this=__pthis__;(void)this;
#define super() yaooc_date_time_parent_class_table->year(this)
#define PM(method,...) CTM((*yaooc_date_time_parent_class_table),this,method,## __VA_ARGS__)


      return localtime(&this->time_)->tm_year+1900;
    
#undef PM
#undef super
}
int yaooc_date_time_hour(const_pointer __pthis__)
{
yaooc_date_time_const_pointer this=__pthis__;(void)this;
#define super() yaooc_date_time_parent_class_table->hour(this)
#define PM(method,...) CTM((*yaooc_date_time_parent_class_table),this,method,## __VA_ARGS__)


      return localtime(&this->time_)->tm_hour;
    
#undef PM
#undef super
}
int yaooc_date_time_minute(const_pointer __pthis__)
{
yaooc_date_time_const_pointer this=__pthis__;(void)this;
#define super() yaooc_date_time_parent_class_table->minute(this)
#define PM(method,...) CTM((*yaooc_date_time_parent_class_table),this,method,## __VA_ARGS__)


      return localtime(&this->time_)->tm_min;
    
#undef PM
#undef super
}
int yaooc_date_time_second(const_pointer __pthis__)
{
yaooc_date_time_const_pointer this=__pthis__;(void)this;
#define super() yaooc_date_time_parent_class_table->second(this)
#define PM(method,...) CTM((*yaooc_date_time_parent_class_table),this,method,## __VA_ARGS__)


      return localtime(&this->time_)->tm_sec;
    
#undef PM
#undef super
}
int yaooc_date_time_day_of_week(const_pointer __pthis__)
{
yaooc_date_time_const_pointer this=__pthis__;(void)this;
#define super() yaooc_date_time_parent_class_table->day_of_week(this)
#define PM(method,...) CTM((*yaooc_date_time_parent_class_table),this,method,## __VA_ARGS__)


      return localtime(&this->time_)->tm_wday;
    
#undef PM
#undef super
}
int yaooc_date_time_day_of_year(const_pointer __pthis__)
{
yaooc_date_time_const_pointer this=__pthis__;(void)this;
#define super() yaooc_date_time_parent_class_table->day_of_year(this)
#define PM(method,...) CTM((*yaooc_date_time_parent_class_table),this,method,## __VA_ARGS__)


      return localtime(&this->time_)->tm_yday;
    
#undef PM
#undef super
}
char* yaooc_date_time_strftime(pointer __pthis__,const char* fmt)
{
yaooc_date_time_pointer this=__pthis__;(void)this;
#define super() yaooc_date_time_parent_class_table->strftime(this,fmt)
#define PM(method,...) CTM((*yaooc_date_time_parent_class_table),this,method,## __VA_ARGS__)


      char* buf=new_array(char,64);
      strftime(buf,64,fmt,localtime(&this->time_));
      return buf;
    
#undef PM
#undef super
}
yaooc_date_time_class_table_t yaooc_date_time_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_object_class_table,
.type_name_ = (const char*)"yaooc_date_time_t",
.swap = (void(*)(pointer,pointer)) yaooc_date_time_swap,
.set = (void(*)(pointer,time_t)) yaooc_date_time_set,
.set_ymdhms = (void(*)(pointer,int,int,int,int,int,int)) yaooc_date_time_set_ymdhms,
.set_ymd = (void(*)(pointer,int,int,int,int,int,int)) yaooc_date_time_set_ymd,
.set_hms = (void(*)(pointer,int,int,int)) yaooc_date_time_set_hms,
.get = (time_t(*)(const_pointer)) yaooc_date_time_get,
.month = (int(*)(const_pointer)) yaooc_date_time_month,
.day = (int(*)(const_pointer)) yaooc_date_time_day,
.year = (int(*)(const_pointer)) yaooc_date_time_year,
.hour = (int(*)(const_pointer)) yaooc_date_time_hour,
.minute = (int(*)(const_pointer)) yaooc_date_time_minute,
.second = (int(*)(const_pointer)) yaooc_date_time_second,
.day_of_week = (int(*)(const_pointer)) yaooc_date_time_day_of_week,
.day_of_year = (int(*)(const_pointer)) yaooc_date_time_day_of_year,
.strftime = (char*(*)(pointer,const char*)) yaooc_date_time_strftime,
};
const type_info_t __yaooc_date_time_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_date_time_t),
.rich_compare_=yaooc_date_time_rich_compare,
.to_stream_=yaooc_date_time_to_stream,
.from_stream_=NULL,
.default_ctor_=yaooc_date_time_default_ctor,
.dtor_=NULL,
.copy_ctor_=yaooc_date_time_copy_ctor,
.assign_=yaooc_date_time_assign,
.class_table_=(const class_table_t*) &yaooc_date_time_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_date_time_ti=&__yaooc_date_time_ti;
