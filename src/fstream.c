#include <yaooc/fstream.h>
void yaooc_ifstream_default_ctor(pointer __pthis__)
{
yaooc_ifstream_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_ifstream);



      yaooc_base_stream_default_ctor(this);
    
}
void yaooc_ifstream_dtor(pointer __pthis__)
{
yaooc_ifstream_pointer this=__pthis__;(void)this;


      M(this,close);
    
}
void yaooc_ifstream_ctor_fname_mode(pointer __pthis,va_list __con_args__){
yaooc_ifstream_pointer this=__pthis;(void)this;
const char* fname = va_arg(__con_args__,const char*);
const char* mode = va_arg(__con_args__,const char*);

call_default_ctor_static(this,yaooc_ifstream);


      M(this,open,fname,mode);
    
}
void yaooc_ifstream_open(pointer __pthis__,const char* fname,const char* mode)
{
yaooc_ifstream_pointer this=__pthis__;(void)this;
#define super() yaooc_ifstream_parent_class_table->open(this,fname,mode)
#define PM(method,...) CTM((*yaooc_ifstream_parent_class_table),this,method,## __VA_ARGS__)


      M(this,close);
      this->handle_=fopen(fname,mode);
    
#undef PM
#undef super
}
void yaooc_ifstream_close(pointer __pthis__)
{
yaooc_ifstream_pointer this=__pthis__;(void)this;
#define super() yaooc_ifstream_parent_class_table->close(this)
#define PM(method,...) CTM((*yaooc_ifstream_parent_class_table),this,method,## __VA_ARGS__)


      if(this->handle_) {
        fclose(this->handle_);
        this->handle_=NULL;
      }
    
#undef PM
#undef super
}
yaooc_ifstream_class_table_t yaooc_ifstream_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_istream_class_table,
.type_name_ = (const char*)"yaooc_ifstream_t",
.swap = (void(*)(pointer,pointer)) yaooc_ifstream_swap,
.eof = (bool(*)(const_pointer)) yaooc_ifstream_eof,
.seek = (bool(*)(pointer,size_t,int)) yaooc_ifstream_seek,
.tell = (size_t(*)(const_pointer)) yaooc_ifstream_tell,
.good = (bool(*)(const_pointer)) yaooc_ifstream_good,
.stream = (void(*)(pointer,...)) yaooc_ifstream_stream,
.peek = (int(*)(pointer)) yaooc_ifstream_peek,
.scanf = (int(*)(pointer,const char*,...)) yaooc_ifstream_scanf,
.vscanf = (int(*)(pointer,const char*,va_list)) yaooc_ifstream_vscanf,
.read = (size_t(*)(pointer,void*,size_t,size_t)) yaooc_ifstream_read,
.getstr = (char*(*)(pointer,char*,size_t)) yaooc_ifstream_getstr,
.open = (void(*)(pointer,const char*,const char*)) yaooc_ifstream_open,
.close = (void(*)(pointer)) yaooc_ifstream_close,
};
const type_info_t __yaooc_ifstream_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_ifstream_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_ifstream_default_ctor,
.dtor_=yaooc_ifstream_dtor,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_ifstream_class_table,
.parent_=&__yaooc_istream_ti
};
const type_info_t* const yaooc_ifstream_ti=&__yaooc_ifstream_ti;
void yaooc_ofstream_default_ctor(pointer __pthis__)
{
yaooc_ofstream_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_ofstream);



      yaooc_base_stream_default_ctor(this);
    
}
void yaooc_ofstream_dtor(pointer __pthis__)
{
yaooc_ofstream_pointer this=__pthis__;(void)this;


      M(this,close);
    
}
void yaooc_ofstream_ctor_fname_mode(pointer __pthis,va_list __con_args__){
yaooc_ofstream_pointer this=__pthis;(void)this;
const char* fname = va_arg(__con_args__,const char*);
const char* mode = va_arg(__con_args__,const char*);

call_default_ctor_static(this,yaooc_ofstream);


      M(this,open,fname,mode);
    
}
void yaooc_ofstream_open(pointer __pthis__,const char* fname,const char* mode)
{
yaooc_ofstream_pointer this=__pthis__;(void)this;
#define super() yaooc_ofstream_parent_class_table->open(this,fname,mode)
#define PM(method,...) CTM((*yaooc_ofstream_parent_class_table),this,method,## __VA_ARGS__)


      M(this,close);
      this->handle_=fopen(fname,mode);
    
#undef PM
#undef super
}
void yaooc_ofstream_close(pointer __pthis__)
{
yaooc_ofstream_pointer this=__pthis__;(void)this;
#define super() yaooc_ofstream_parent_class_table->close(this)
#define PM(method,...) CTM((*yaooc_ofstream_parent_class_table),this,method,## __VA_ARGS__)


      if(this->handle_) {
        fclose(this->handle_);
        this->handle_=NULL;
      }
    
#undef PM
#undef super
}
yaooc_ofstream_class_table_t yaooc_ofstream_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_ostream_class_table,
.type_name_ = (const char*)"yaooc_ofstream_t",
.swap = (void(*)(pointer,pointer)) yaooc_ofstream_swap,
.eof = (bool(*)(const_pointer)) yaooc_ofstream_eof,
.seek = (bool(*)(pointer,size_t,int)) yaooc_ofstream_seek,
.tell = (size_t(*)(const_pointer)) yaooc_ofstream_tell,
.good = (bool(*)(const_pointer)) yaooc_ofstream_good,
.stream = (void(*)(pointer,...)) yaooc_ofstream_stream,
.printf = (int(*)(pointer,const char*,...)) yaooc_ofstream_printf,
.vprintf = (int(*)(pointer,const char*,va_list)) yaooc_ofstream_vprintf,
.write = (size_t(*)(pointer,const void*,size_t,size_t)) yaooc_ofstream_write,
.putstr = (int(*)(pointer,const char*)) yaooc_ofstream_putstr,
.putchr = (int(*)(pointer,int)) yaooc_ofstream_putchr,
.open = (void(*)(pointer,const char*,const char*)) yaooc_ofstream_open,
.close = (void(*)(pointer)) yaooc_ofstream_close,
};
const type_info_t __yaooc_ofstream_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_ofstream_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_ofstream_default_ctor,
.dtor_=yaooc_ofstream_dtor,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_ofstream_class_table,
.parent_=&__yaooc_ostream_ti
};
const type_info_t* const yaooc_ofstream_ti=&__yaooc_ofstream_ti;
