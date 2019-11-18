#include <yaooc/sstream.h>

#include <string.h>


void yaooc_istringstream_ctor_ccs(pointer __pthis__,va_list __con_args__)
{
yaooc_istringstream_pointer this=__pthis__;
const char* str = va_arg(__con_args__,const char*);

call_parent_default_ctor_static(this,yaooc_istringstream);


      yaooc_base_stream_default_ctor(this);
      yaooc_istringstream_setn(this,str,SIZE_MAX);
    
}
void yaooc_istringstream_ctor_ccs_n(pointer __pthis__,va_list __con_args__)
{
yaooc_istringstream_pointer this=__pthis__;
const char* str = va_arg(__con_args__,const char*);
size_t n = va_arg(__con_args__,size_t);

call_parent_default_ctor_static(this,yaooc_istringstream);


      yaooc_base_stream_default_ctor(this);
      yaooc_istringstream_setn(this,str,n);
    
}
void yaooc_istringstream_reset(pointer __pthis__)
{
yaooc_istringstream_pointer this=__pthis__;(void)this;
#define super() yaooc_istringstream_parent_class_table->reset(this)
#define PM(method,...) CTM((*yaooc_istringstream_parent_class_table),this,method,## __VA_ARGS__)


      if(this->buffer_)
        FREE(this->buffer_);
      if(this->handle_)
        fclose(this->handle_);
      this->handle_=tmpfile();
    
#undef PM
#undef super
}
void yaooc_istringstream_set(pointer __pthis__,const char* str)
{
yaooc_istringstream_pointer this=__pthis__;(void)this;
#define super() yaooc_istringstream_parent_class_table->set(this,str)
#define PM(method,...) CTM((*yaooc_istringstream_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_istringstream_setn(this,str,SIZE_MAX);
    
#undef PM
#undef super
}
void yaooc_istringstream_setn(pointer __pthis__,const char* str,size_t n)
{
yaooc_istringstream_pointer this=__pthis__;(void)this;
#define super() yaooc_istringstream_parent_class_table->setn(this,str,n)
#define PM(method,...) CTM((*yaooc_istringstream_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_istringstream_reset(this);
      size_t l= str ? strlen(str) : 0;
      if(n>l) n=l;
      if(n> 0) {
        this->handle_=tmpfile();
        fwrite(str,1,n,this->handle_);
        fseek(this->handle_,0,SEEK_SET);
      }
    
#undef PM
#undef super
}
const char* yaooc_istringstream_c_str(const_pointer __pthis__)
{
yaooc_istringstream_const_pointer this=__pthis__;(void)this;
#define super() yaooc_istringstream_parent_class_table->c_str(this)
#define PM(method,...) CTM((*yaooc_istringstream_parent_class_table),this,method,## __VA_ARGS__)


      if(this->buffer_!=NULL)
        FREE(((yaooc_istringstream_t*)this)->buffer_);
      size_t ofs = M(this,tell);
      fseek(this->handle_,0,SEEK_END);
      size_t n=M(this,tell);
      if(n>0) {
        fseek(this->handle_,0,SEEK_SET);
        ((yaooc_istringstream_t*)this)->buffer_=MALLOC(n+1);
        fread(this->buffer_,1,n,this->handle_);
        ((yaooc_istringstream_t*)this)->buffer_[n]=0;
      }
      fseek(this->handle_,ofs,SEEK_SET);
      return this->buffer_;
    
#undef PM
#undef super
}
yaooc_istringstream_class_table_t yaooc_istringstream_class_table ={
.parent_class_table_ = (const class_table_t*) &yaooc_istream_class_table,
.type_name_ = (const char*) "yaooc_istringstream_t",
.swap = (void(*)(pointer,pointer)) yaooc_istringstream_swap,
.eof = (bool(*)(const_pointer)) yaooc_istringstream_eof,
.seek = (bool(*)(pointer,size_t,int)) yaooc_istringstream_seek,
.tell = (size_t(*)(const_pointer)) yaooc_istringstream_tell,
.good = (bool(*)(const_pointer)) yaooc_istringstream_good,
.stream = (void(*)(pointer,...)) yaooc_istringstream_stream,
.peek = (int(*)(pointer)) yaooc_istringstream_peek,
.scanf = (int(*)(pointer,const char*,...)) yaooc_istringstream_scanf,
.vscanf = (int(*)(pointer,const char*,va_list)) yaooc_istringstream_vscanf,
.read = (size_t(*)(pointer,void*,size_t,size_t)) yaooc_istringstream_read,
.getstr = (char*(*)(pointer,char*,size_t)) yaooc_istringstream_getstr,
.reset = (void(*)(pointer)) yaooc_istringstream_reset,
.set = (void(*)(pointer,const char*)) yaooc_istringstream_set,
.setn = (void(*)(pointer,const char*,size_t)) yaooc_istringstream_setn,
.c_str = (const char*(*)(const_pointer)) yaooc_istringstream_c_str,
};
void yaooc_istringstream_default_ctor(pointer __pthis__)
{
yaooc_istringstream_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_istringstream);



      yaooc_base_stream_default_ctor(this);
      this->buffer_=NULL;
    
}
void yaooc_istringstream_dtor(pointer __pthis__)
{
yaooc_istringstream_pointer this=__pthis__;(void)this;


      if(this->handle_) {
        fclose(this->handle_);
        this->handle_=NULL;
      }
      if(this->buffer_)
        FREE(this->buffer_);
    
}
const type_info_t __yaooc_istringstream_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_istringstream_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_istringstream_default_ctor,
.dtor_=yaooc_istringstream_dtor,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_istringstream_class_table,
.parent_=&__yaooc_istream_ti
};
const type_info_t* const yaooc_istringstream_ti=&__yaooc_istringstream_ti;
void yaooc_ostringstream_reset(pointer __pthis__)
{
yaooc_ostringstream_pointer this=__pthis__;(void)this;
#define super() yaooc_ostringstream_parent_class_table->reset(this)
#define PM(method,...) CTM((*yaooc_ostringstream_parent_class_table),this,method,## __VA_ARGS__)


      if(this->buffer_)
        FREE(this->buffer_);
      if(this->handle_)
        fclose(this->handle_);
      this->handle_=tmpfile();
    
#undef PM
#undef super
}
const char* yaooc_ostringstream_c_str(const_pointer __pthis__)
{
yaooc_ostringstream_const_pointer this=__pthis__;(void)this;
#define super() yaooc_ostringstream_parent_class_table->c_str(this)
#define PM(method,...) CTM((*yaooc_ostringstream_parent_class_table),this,method,## __VA_ARGS__)


      if(this->buffer_!=NULL)
        FREE(((yaooc_ostringstream_t*)this)->buffer_);
      size_t ofs = M(this,tell);
      fseek(this->handle_,0,SEEK_END);
      size_t n=M(this,tell);
      if(n>0) {
        fseek(this->handle_,0,SEEK_SET);
        ((yaooc_istringstream_t*)this)->buffer_=MALLOC(n+1);
        fread(((yaooc_istringstream_t*)this)->buffer_,1,n,this->handle_);
        ((yaooc_istringstream_t*)this)->buffer_[n]=0;
      }
      fseek(this->handle_,ofs,SEEK_SET);
      return this->buffer_;
    
#undef PM
#undef super
}
yaooc_ostringstream_class_table_t yaooc_ostringstream_class_table ={
.parent_class_table_ = (const class_table_t*) &yaooc_ostream_class_table,
.type_name_ = (const char*) "yaooc_ostringstream_t",
.swap = (void(*)(pointer,pointer)) yaooc_ostringstream_swap,
.eof = (bool(*)(const_pointer)) yaooc_ostringstream_eof,
.seek = (bool(*)(pointer,size_t,int)) yaooc_ostringstream_seek,
.tell = (size_t(*)(const_pointer)) yaooc_ostringstream_tell,
.good = (bool(*)(const_pointer)) yaooc_ostringstream_good,
.stream = (void(*)(pointer,...)) yaooc_ostringstream_stream,
.printf = (int(*)(pointer,const char*,...)) yaooc_ostringstream_printf,
.vprintf = (int(*)(pointer,const char*,va_list)) yaooc_ostringstream_vprintf,
.write = (size_t(*)(pointer,const void*,size_t,size_t)) yaooc_ostringstream_write,
.putstr = (int(*)(pointer,const char*)) yaooc_ostringstream_putstr,
.putchr = (int(*)(pointer,int)) yaooc_ostringstream_putchr,
.reset = (void(*)(pointer)) yaooc_ostringstream_reset,
.c_str = (const char*(*)(const_pointer)) yaooc_ostringstream_c_str,
};
void yaooc_ostringstream_default_ctor(pointer __pthis__)
{
yaooc_ostringstream_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_ostringstream);



      this->buffer_=NULL;
      this->handle_=tmpfile();
    
}
void yaooc_ostringstream_dtor(pointer __pthis__)
{
yaooc_ostringstream_pointer this=__pthis__;(void)this;


      if(this->handle_) {
        fclose(this->handle_);
        this->handle_=NULL;
      }
      if(this->buffer_)
        FREE(this->buffer_);
    
}
const type_info_t __yaooc_ostringstream_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_ostringstream_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_ostringstream_default_ctor,
.dtor_=yaooc_ostringstream_dtor,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_ostringstream_class_table,
.parent_=&__yaooc_ostream_ti
};
const type_info_t* const yaooc_ostringstream_ti=&__yaooc_ostringstream_ti;
