#ifndef __STREAM_INCLUDED__
#define __STREAM_INCLUDED__

#include <yaooc/object.h>

#include <stdio.h>
void throw_stream_exception(pointer,const char*);

yaooc_class_table(yaooc_base_stream) {
  yaooc_object_class_table_t;
bool (*eof)(const_pointer);
bool (*seek)(pointer,size_t,int);
size_t (*tell)(const_pointer);
bool (*good)(const_pointer);
};
#define yaooc_base_stream_parent_class_table ((yaooc_object_class_table_t*)(yaooc_base_stream_class_table.parent_class_table_))

yaooc_class_instance(yaooc_base_stream) {
FILE* handle_;
};

yaooc_class(yaooc_base_stream);
void yaooc_base_stream_default_ctor(pointer);
#define yaooc_base_stream_swap yaooc_object_swap
 bool yaooc_base_stream_eof(const_pointer);
 bool yaooc_base_stream_seek(pointer,size_t,int);
 size_t yaooc_base_stream_tell(const_pointer);
 bool yaooc_base_stream_good(const_pointer);
 void yaooc_base_stream_set_handle(pointer,FILE*);
yaooc_class_table(yaooc_istream) {
  yaooc_base_stream_class_table_t;
void (*stream)(pointer,...);
int (*peek)(pointer);
int (*scanf)(pointer,const char*,...);
int (*vscanf)(pointer,const char*,va_list);
size_t (*read)(pointer,void*,size_t,size_t);
char* (*getstr)(pointer,char*,size_t);
};
#define yaooc_istream_parent_class_table ((yaooc_base_stream_class_table_t*)(yaooc_istream_class_table.parent_class_table_))

yaooc_class_instance(yaooc_istream) {
  yaooc_base_stream_class_instance_t;
};

yaooc_class(yaooc_istream);
void yaooc_istream_default_ctor(pointer);
#define yaooc_istream_swap yaooc_base_stream_swap
#define yaooc_istream_eof yaooc_base_stream_eof
#define yaooc_istream_seek yaooc_base_stream_seek
#define yaooc_istream_tell yaooc_base_stream_tell
#define yaooc_istream_good yaooc_base_stream_good
 void yaooc_istream_stream(pointer,...);
 int yaooc_istream_peek(pointer);
 int yaooc_istream_scanf(pointer,const char*,...);
 int yaooc_istream_vscanf(pointer,const char*,va_list);
 size_t yaooc_istream_read(pointer,void*,size_t,size_t);
 char* yaooc_istream_getstr(pointer,char*,size_t);
yaooc_class_table(yaooc_ostream) {
  yaooc_base_stream_class_table_t;
void (*stream)(pointer,...);
int (*printf)(pointer,const char*,...);
int (*vprintf)(pointer,const char*,va_list);
size_t (*write)(pointer,const void*,size_t,size_t);
int (*putstr)(pointer,const char*);
int (*putchr)(pointer,int);
};
#define yaooc_ostream_parent_class_table ((yaooc_base_stream_class_table_t*)(yaooc_ostream_class_table.parent_class_table_))

yaooc_class_instance(yaooc_ostream) {
  yaooc_base_stream_class_instance_t;
};

yaooc_class(yaooc_ostream);
void yaooc_ostream_default_ctor(pointer);
#define yaooc_ostream_swap yaooc_base_stream_swap
#define yaooc_ostream_eof yaooc_base_stream_eof
#define yaooc_ostream_seek yaooc_base_stream_seek
#define yaooc_ostream_tell yaooc_base_stream_tell
#define yaooc_ostream_good yaooc_base_stream_good
 void yaooc_ostream_stream(pointer,...);
 int yaooc_ostream_printf(pointer,const char*,...);
 int yaooc_ostream_vprintf(pointer,const char*,va_list);
 size_t yaooc_ostream_write(pointer,const void*,size_t,size_t);
 int yaooc_ostream_putstr(pointer,const char*);
 int yaooc_ostream_putchr(pointer,int);
extern yaooc_istream_pointer cin;
extern yaooc_ostream_pointer cout;
extern yaooc_ostream_pointer cerr;

#define STREAM(S,...) M(S,stream,__VA_ARGS__,NULL)
#define OSTREAM STREAM
#define ISTREAM STREAM

#define __S_OBJ(ti) ((memory_header_t){ .type_info_=ti , .n_elem_=(size_t)-1 }).ptr_
#define S_OBJ(T) __S_OBJ(T ## _ti)
#define O_OBJ(T,O) S_OBJ(T),&O
#define O_CHR(c) S_OBJ(char),c
#define O_UCHR(uc) S_OBJ(uchar),uc
#define O_SHORT(s) S_OBJ(short),s
#define O_USHORT(us) S_OBJ(ushort),us
#define O_INT(i) S_OBJ(int),i
#define O_UINT(ui) S_OBJ(uint),ui
#define O_LONG(l) S_OBJ(long),l
#define O_ULONG(ul) S_OBJ(ulong),ul
#define O_SIZE(sz) S_OBJ(size),sz
#define O_DOUBLE(d) S_OBJ(double),d
#define O_CCS(ccs) S_OBJ(yaooc_ccs),ccs

#define I_OBJ(T,O) S_OBJ(T),&O
#define I_CHR(c) I_OBJ(char,c)
#define I_UCHR(uc) I_OBJ(uchar,uc)
#define I_SHORT(s) I_OBJ(short,s)
#define I_USHORT(us) I_OBJ(ushort,us)
#define I_INT(i) I_OBJ(int,i)
#define I_UINT(ui) I_OBJ(uint,ui)
#define I_LONG(l) I_OBJ(long,l)
#define I_ULONG(ul) I_OBJ(ulong,ul)
#define I_SIZE(sz) I_OBJ(size,sz)
#define I_DOUBLE(d) I_OBJ(double,d)
#define I_CCS(ccs) S_OBJ(yaooc_ccs),ccs

#ifdef _WIN32
#define endl O_CCS("\r\n")
#else
#define endl O_CHR('\n')
#endif
#define ends O_CHR(0)


#endif
