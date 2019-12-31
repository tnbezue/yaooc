#ifndef __SSTREAM_INCLUDED__
#define __SSTREAM_INCLUDED__

#include <yaooc/stream.h>
yaooc_class_table(yaooc_istringstream) {
  yaooc_istream_class_table_t;
void (*reset)(pointer);
void (*set)(pointer,const char*);
void (*setn)(pointer,const char*,size_t);
const char* (*c_str)(const_pointer);
};
#define yaooc_istringstream_parent_class_table ((yaooc_istream_class_table_t*)(yaooc_istringstream_class_table.parent_class_table_))

yaooc_class_instance(yaooc_istringstream) {
  yaooc_istream_class_instance_t;
char* buffer_;
};

yaooc_class(yaooc_istringstream);
void yaooc_istringstream_default_ctor(pointer);
void yaooc_istringstream_dtor(pointer);
void yaooc_istringstream_ctor_ccs(pointer,va_list);
void yaooc_istringstream_ctor_ccs_n(pointer,va_list);
#define yaooc_istringstream_swap yaooc_istream_swap
#define yaooc_istringstream_eof yaooc_istream_eof
#define yaooc_istringstream_seek yaooc_istream_seek
#define yaooc_istringstream_tell yaooc_istream_tell
#define yaooc_istringstream_good yaooc_istream_good
#define yaooc_istringstream_stream yaooc_istream_stream
#define yaooc_istringstream_peek yaooc_istream_peek
#define yaooc_istringstream_scanf yaooc_istream_scanf
#define yaooc_istringstream_vscanf yaooc_istream_vscanf
#define yaooc_istringstream_read yaooc_istream_read
#define yaooc_istringstream_getstr yaooc_istream_getstr
 void yaooc_istringstream_reset(pointer);
 void yaooc_istringstream_set(pointer,const char*);
 void yaooc_istringstream_setn(pointer,const char*,size_t);
 const char* yaooc_istringstream_c_str(const_pointer);
yaooc_class_table(yaooc_ostringstream) {
  yaooc_ostream_class_table_t;
void (*reset)(pointer);
const char* (*c_str)(const_pointer);
};
#define yaooc_ostringstream_parent_class_table ((yaooc_ostream_class_table_t*)(yaooc_ostringstream_class_table.parent_class_table_))

yaooc_class_instance(yaooc_ostringstream) {
  yaooc_ostream_class_instance_t;
char* buffer_;
};

yaooc_class(yaooc_ostringstream);
void yaooc_ostringstream_default_ctor(pointer);
void yaooc_ostringstream_dtor(pointer);
#define yaooc_ostringstream_swap yaooc_ostream_swap
#define yaooc_ostringstream_eof yaooc_ostream_eof
#define yaooc_ostringstream_seek yaooc_ostream_seek
#define yaooc_ostringstream_tell yaooc_ostream_tell
#define yaooc_ostringstream_good yaooc_ostream_good
#define yaooc_ostringstream_stream yaooc_ostream_stream
#define yaooc_ostringstream_printf yaooc_ostream_printf
#define yaooc_ostringstream_vprintf yaooc_ostream_vprintf
#define yaooc_ostringstream_write yaooc_ostream_write
#define yaooc_ostringstream_putstr yaooc_ostream_putstr
#define yaooc_ostringstream_putchr yaooc_ostream_putchr
 void yaooc_ostringstream_reset(pointer);
 const char* yaooc_ostringstream_c_str(const_pointer);

#endif
