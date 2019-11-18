#include <yaooc/stream.h>

#include <string.h>


void yaooc_base_stream_set_handle(pointer __pthis__,FILE* h)
{
yaooc_base_stream_pointer this=__pthis__;(void)this;

      this->handle_=h;
    
}
bool yaooc_base_stream_eof(const_pointer __pthis__)
{
yaooc_base_stream_const_pointer this=__pthis__;(void)this;
#define super() yaooc_base_stream_parent_class_table->eof(this)
#define PM(method,...) CTM((*yaooc_base_stream_parent_class_table),this,method,## __VA_ARGS__)


      return this->handle_ ? feof(this->handle_) : true;
    
#undef PM
#undef super
}
bool yaooc_base_stream_seek(pointer __pthis__,size_t ofs,int whence)
{
yaooc_base_stream_pointer this=__pthis__;(void)this;
#define super() yaooc_base_stream_parent_class_table->seek(this,ofs,whence)
#define PM(method,...) CTM((*yaooc_base_stream_parent_class_table),this,method,## __VA_ARGS__)


      return fseek(this->handle_,ofs,whence) == 0;
    
#undef PM
#undef super
}
size_t yaooc_base_stream_tell(const_pointer __pthis__)
{
yaooc_base_stream_const_pointer this=__pthis__;(void)this;
#define super() yaooc_base_stream_parent_class_table->tell(this)
#define PM(method,...) CTM((*yaooc_base_stream_parent_class_table),this,method,## __VA_ARGS__)


      return ftell(this->handle_);
    
#undef PM
#undef super
}
bool yaooc_base_stream_good(const_pointer __pthis__)
{
yaooc_base_stream_const_pointer this=__pthis__;(void)this;
#define super() yaooc_base_stream_parent_class_table->good(this)
#define PM(method,...) CTM((*yaooc_base_stream_parent_class_table),this,method,## __VA_ARGS__)


      return this->handle_ != NULL;
    
#undef PM
#undef super
}
yaooc_base_stream_class_table_t yaooc_base_stream_class_table ={
.parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
.type_name_ = (const char*) "yaooc_base_stream_t",
.swap = (void(*)(pointer,pointer)) yaooc_base_stream_swap,
.eof = (bool(*)(const_pointer)) yaooc_base_stream_eof,
.seek = (bool(*)(pointer,size_t,int)) yaooc_base_stream_seek,
.tell = (size_t(*)(const_pointer)) yaooc_base_stream_tell,
.good = (bool(*)(const_pointer)) yaooc_base_stream_good,
};
void yaooc_base_stream_default_ctor(pointer __pthis__)
{
yaooc_base_stream_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_base_stream);



      this->handle_=NULL;
    
}
const type_info_t __yaooc_base_stream_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_base_stream_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_base_stream_default_ctor,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_base_stream_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_base_stream_ti=&__yaooc_base_stream_ti;
void yaooc_istream_stream(pointer __pthis__,...)
{
yaooc_istream_pointer this=__pthis__;(void)this;
va_list args; va_start(args,__pthis__);
#define super() yaooc_istream_parent_class_table->stream(this,args)
#define PM(method,...) CTM((*yaooc_istream_parent_class_table),this,method,## __VA_ARGS__)


      void* ptr;
      while((ptr = va_arg(args,pointer)) != NULL) {
        memory_header_t* smh=get_memory_header(ptr);
        from_stream from_s = get_from_stream(get_type_info(ptr));
        if(from_s) {
          if(smh->n_elem_==(size_t)-1) {
            ptr=va_arg(args,pointer);
            from_s(ptr,this);
          } else {
            from_s(ptr,this);
          }
        } else
          throw_stream_exception(this,"from_stream");
      }
    
#undef PM
#undef super
}
int yaooc_istream_peek(pointer __pthis__)
{
yaooc_istream_pointer this=__pthis__;(void)this;
#define super() yaooc_istream_parent_class_table->peek(this)
#define PM(method,...) CTM((*yaooc_istream_parent_class_table),this,method,## __VA_ARGS__)


      int c=0;
      if(this->handle_) {
        c=fgetc(this->handle_);
        ungetc(c,this->handle_);
      }
      return c;
    
#undef PM
#undef super
}
int yaooc_istream_scanf(pointer __pthis__,const char* fmt,...)
{
yaooc_istream_pointer this=__pthis__;(void)this;
va_list args; va_start(args,fmt);
#define super() yaooc_istream_parent_class_table->scanf(this,fmt,args)
#define PM(method,...) CTM((*yaooc_istream_parent_class_table),this,method,## __VA_ARGS__)


      int ret=M(this,vscanf,fmt,args);
      return ret;
    
#undef PM
#undef super
}
int yaooc_istream_vscanf(pointer __pthis__,const char* fmt,va_list args)
{
yaooc_istream_pointer this=__pthis__;(void)this;
#define super() yaooc_istream_parent_class_table->vscanf(this,fmt,args)
#define PM(method,...) CTM((*yaooc_istream_parent_class_table),this,method,## __VA_ARGS__)


      return vfscanf(this->handle_,fmt,args);
    
#undef PM
#undef super
}
size_t yaooc_istream_read(pointer __pthis__,void* buffer,size_t size,size_t count)
{
yaooc_istream_pointer this=__pthis__;(void)this;
#define super() yaooc_istream_parent_class_table->read(this,buffer,size,count)
#define PM(method,...) CTM((*yaooc_istream_parent_class_table),this,method,## __VA_ARGS__)


      return fread(buffer,size,count,this->handle_);
    
#undef PM
#undef super
}
char* yaooc_istream_getstr(pointer __pthis__,char* buffer,size_t n)
{
yaooc_istream_pointer this=__pthis__;(void)this;
#define super() yaooc_istream_parent_class_table->getstr(this,buffer,n)
#define PM(method,...) CTM((*yaooc_istream_parent_class_table),this,method,## __VA_ARGS__)


      return fgets(buffer,n,this->handle_);
    
#undef PM
#undef super
}
yaooc_istream_class_table_t yaooc_istream_class_table ={
.parent_class_table_ = (const class_table_t*) &yaooc_base_stream_class_table,
.type_name_ = (const char*) "yaooc_istream_t",
.swap = (void(*)(pointer,pointer)) yaooc_istream_swap,
.eof = (bool(*)(const_pointer)) yaooc_istream_eof,
.seek = (bool(*)(pointer,size_t,int)) yaooc_istream_seek,
.tell = (size_t(*)(const_pointer)) yaooc_istream_tell,
.good = (bool(*)(const_pointer)) yaooc_istream_good,
.stream = (void(*)(pointer,...)) yaooc_istream_stream,
.peek = (int(*)(pointer)) yaooc_istream_peek,
.scanf = (int(*)(pointer,const char*,...)) yaooc_istream_scanf,
.vscanf = (int(*)(pointer,const char*,va_list)) yaooc_istream_vscanf,
.read = (size_t(*)(pointer,void*,size_t,size_t)) yaooc_istream_read,
.getstr = (char*(*)(pointer,char*,size_t)) yaooc_istream_getstr,
};
void yaooc_istream_default_ctor(pointer __pthis__)
{
yaooc_istream_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_istream);



      yaooc_base_stream_default_ctor(this);
    
}
const type_info_t __yaooc_istream_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_istream_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_istream_default_ctor,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_istream_class_table,
.parent_=&__yaooc_base_stream_ti
};
const type_info_t* const yaooc_istream_ti=&__yaooc_istream_ti;
void yaooc_ostream_stream(pointer __pthis__,...)
{
yaooc_ostream_pointer this=__pthis__;(void)this;
va_list args; va_start(args,__pthis__);
#define super() yaooc_ostream_parent_class_table->stream(this,args)
#define PM(method,...) CTM((*yaooc_ostream_parent_class_table),this,method,## __VA_ARGS__)


      const void* ptr;
      while((ptr = va_arg(args,const_pointer)) != NULL) {
        memory_header_t* smh=get_memory_header(ptr);
        to_stream to_s = get_to_stream(smh->type_info_);
        if(to_s) {
          if(smh->n_elem_==(size_t)-1) {
            if(smh->type_info_==yaooc_ccs_ti) {
              ptr=va_arg(args,const char*);
              to_s(ptr,this);
            } else if(smh->type_info_==int_ti || smh->type_info_==char_ti || smh->type_info_==short_ti) {
              int_t v=va_arg(args,int_t);
              to_s(&v,this);
            } else if(smh->type_info_==uint_ti || smh->type_info_==uchar_ti || smh->type_info_==ushort_ti) {
              uint_t v=va_arg(args,uint_t);
              to_s(&v,this);
            } else if(smh->type_info_==double_ti) {
              double v=va_arg(args,double);
              to_s(&v,this);
            } else if(smh->type_info_==long_ti) {
              long_t v=va_arg(args,long_t);
              to_s(&v,this);
            } else if(smh->type_info_==ulong_ti) {
              ulong_t v=va_arg(args,ulong_t);
              to_s(&v,this);
            } else if(smh->type_info_==size_ti) {
              ulong_t v=va_arg(args,size_t);
              to_s(&v,this);
            } else {
              ptr = va_arg(args,pointer);
              to_s(ptr,this);
            }
          } else {
            to_s(ptr,this);
          }
        } else {
          throw_stream_exception(this,"to_stream");
        }
      }
    
#undef PM
#undef super
}
int yaooc_ostream_printf(pointer __pthis__,const char* fmt,...)
{
yaooc_ostream_pointer this=__pthis__;(void)this;
va_list args; va_start(args,fmt);
#define super() yaooc_ostream_parent_class_table->printf(this,fmt,args)
#define PM(method,...) CTM((*yaooc_ostream_parent_class_table),this,method,## __VA_ARGS__)


      int ret=M(this,vprintf,fmt,args);
      return ret;
    
#undef PM
#undef super
}
int yaooc_ostream_vprintf(pointer __pthis__,const char* fmt,va_list args)
{
yaooc_ostream_pointer this=__pthis__;(void)this;
#define super() yaooc_ostream_parent_class_table->vprintf(this,fmt,args)
#define PM(method,...) CTM((*yaooc_ostream_parent_class_table),this,method,## __VA_ARGS__)


      return vfprintf(this->handle_,fmt,args);
    
#undef PM
#undef super
}
size_t yaooc_ostream_write(pointer __pthis__,const void* buffer,size_t size,size_t count)
{
yaooc_ostream_pointer this=__pthis__;(void)this;
#define super() yaooc_ostream_parent_class_table->write(this,buffer,size,count)
#define PM(method,...) CTM((*yaooc_ostream_parent_class_table),this,method,## __VA_ARGS__)


      return fwrite(buffer,size,count,this->handle_);
    
#undef PM
#undef super
}
int yaooc_ostream_putstr(pointer __pthis__,const char* str)
{
yaooc_ostream_pointer this=__pthis__;(void)this;
#define super() yaooc_ostream_parent_class_table->putstr(this,str)
#define PM(method,...) CTM((*yaooc_ostream_parent_class_table),this,method,## __VA_ARGS__)


      return fputs(str,this->handle_);
    
#undef PM
#undef super
}
int yaooc_ostream_putchr(pointer __pthis__,int c)
{
yaooc_ostream_pointer this=__pthis__;(void)this;
#define super() yaooc_ostream_parent_class_table->putchr(this,c)
#define PM(method,...) CTM((*yaooc_ostream_parent_class_table),this,method,## __VA_ARGS__)


      return fputc(c,this->handle_);
    
#undef PM
#undef super
}
yaooc_ostream_class_table_t yaooc_ostream_class_table ={
.parent_class_table_ = (const class_table_t*) &yaooc_base_stream_class_table,
.type_name_ = (const char*) "yaooc_ostream_t",
.swap = (void(*)(pointer,pointer)) yaooc_ostream_swap,
.eof = (bool(*)(const_pointer)) yaooc_ostream_eof,
.seek = (bool(*)(pointer,size_t,int)) yaooc_ostream_seek,
.tell = (size_t(*)(const_pointer)) yaooc_ostream_tell,
.good = (bool(*)(const_pointer)) yaooc_ostream_good,
.stream = (void(*)(pointer,...)) yaooc_ostream_stream,
.printf = (int(*)(pointer,const char*,...)) yaooc_ostream_printf,
.vprintf = (int(*)(pointer,const char*,va_list)) yaooc_ostream_vprintf,
.write = (size_t(*)(pointer,const void*,size_t,size_t)) yaooc_ostream_write,
.putstr = (int(*)(pointer,const char*)) yaooc_ostream_putstr,
.putchr = (int(*)(pointer,int)) yaooc_ostream_putchr,
};
void yaooc_ostream_default_ctor(pointer __pthis__)
{
yaooc_ostream_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_ostream);



      yaooc_base_stream_default_ctor(this);
    
}
const type_info_t __yaooc_ostream_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_ostream_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_ostream_default_ctor,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_ostream_class_table,
.parent_=&__yaooc_base_stream_ti
};
const type_info_t* const yaooc_ostream_ti=&__yaooc_ostream_ti;

#define POD_TO_FROM_STREAM(N,FMT) \
void N ## _to_stream(const_pointer p,pointer s) \
{ \
 yaooc_ostream_pointer strm=s; \
 M(strm,printf,FMT,*(N ## _t*) p); \
}\
\
void N ## _from_stream(pointer p,pointer s) \
{ \
 yaooc_istream_pointer strm=s; \
 M(strm,scanf,FMT,p);\
}

POD_TO_FROM_STREAM(char,"%c")
POD_TO_FROM_STREAM(uchar,"%uc")
POD_TO_FROM_STREAM(short,"%hd")
POD_TO_FROM_STREAM(ushort,"%hu")
POD_TO_FROM_STREAM(int,"%d")
POD_TO_FROM_STREAM(uint,"%u")

#if __WORDSIZE == 64
POD_TO_FROM_STREAM(long,"%ld")
POD_TO_FROM_STREAM(ulong,"%lu")
#else
POD_TO_FROM_STREAM(long,"%lld")
POD_TO_FROM_STREAM(ulong,"%llu")
#endif

void double_to_stream(const_pointer p,pointer s)
{
 yaooc_ostream_pointer strm=s;
 M(strm,printf,"%lg",*(double*) p);
}

void double_from_stream(pointer p,pointer s)
{
 yaooc_istream_pointer strm=s;
 M(strm,scanf,"%lg",p);
}


POD_TO_FROM_STREAM(size,"%zu")

void yaooc_ccs_to_stream(const_pointer p,pointer s)
{
 yaooc_ostream_pointer strm=s;
 M(strm,printf,"%s",p);
}

void yaooc_ccs_from_stream(pointer p,pointer s)
{
 yaooc_istream_pointer strm=s;
 M(strm,scanf,"%s",p);
}

static yaooc_istream_t __cin = { .class_table_=&yaooc_istream_class_table,.handle_=NULL };
yaooc_istream_pointer cin = &__cin;
static yaooc_ostream_t __cout = { .class_table_=&yaooc_ostream_class_table,.handle_=NULL };
yaooc_ostream_pointer cout = &__cout;
static yaooc_ostream_t __cerr = { .class_table_=&yaooc_ostream_class_table,.handle_=NULL };
yaooc_ostream_pointer cerr = &__cerr;

__attribute__((constructor))
void init_streams()
{
 __cin.handle_ = stdin;
 __cout.handle_ = stdout;
 __cerr.handle_ = stderr;
}

