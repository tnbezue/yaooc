#ifndef __FSTREAM_INCLUDED__
#define __FSTREAM_INCLUDED__

#include <yaooc/stream.h>
yaooc_class_table(yaooc_ifstream) {
  yaooc_istream_class_table_t;
void (*open)(pointer,const char*,const char*);
void (*close)(pointer);
};
#define yaooc_ifstream_parent_class_table ((yaooc_istream_class_table_t*)(yaooc_ifstream_class_table.parent_class_table_))

yaooc_class_instance(yaooc_ifstream) {
  yaooc_istream_class_instance_t;
};

yaooc_class(yaooc_ifstream);
void yaooc_ifstream_default_ctor(pointer);
void yaooc_ifstream_dtor(pointer);
void yaooc_ifstream_ctor_fname_mode(pointer,va_list);
#define yaooc_ifstream_swap yaooc_istream_swap
#define yaooc_ifstream_eof yaooc_istream_eof
#define yaooc_ifstream_seek yaooc_istream_seek
#define yaooc_ifstream_tell yaooc_istream_tell
#define yaooc_ifstream_good yaooc_istream_good
#define yaooc_ifstream_stream yaooc_istream_stream
#define yaooc_ifstream_peek yaooc_istream_peek
#define yaooc_ifstream_scanf yaooc_istream_scanf
#define yaooc_ifstream_vscanf yaooc_istream_vscanf
#define yaooc_ifstream_read yaooc_istream_read
#define yaooc_ifstream_getstr yaooc_istream_getstr
 void yaooc_ifstream_open(pointer,const char*,const char*);
 void yaooc_ifstream_close(pointer);
yaooc_class_table(yaooc_ofstream) {
  yaooc_ostream_class_table_t;
void (*open)(pointer,const char*,const char*);
void (*close)(pointer);
};
#define yaooc_ofstream_parent_class_table ((yaooc_ostream_class_table_t*)(yaooc_ofstream_class_table.parent_class_table_))

yaooc_class_instance(yaooc_ofstream) {
  yaooc_ostream_class_instance_t;
};

yaooc_class(yaooc_ofstream);
void yaooc_ofstream_default_ctor(pointer);
void yaooc_ofstream_dtor(pointer);
void yaooc_ofstream_ctor_fname_mode(pointer,va_list);
#define yaooc_ofstream_swap yaooc_ostream_swap
#define yaooc_ofstream_eof yaooc_ostream_eof
#define yaooc_ofstream_seek yaooc_ostream_seek
#define yaooc_ofstream_tell yaooc_ostream_tell
#define yaooc_ofstream_good yaooc_ostream_good
#define yaooc_ofstream_stream yaooc_ostream_stream
#define yaooc_ofstream_printf yaooc_ostream_printf
#define yaooc_ofstream_vprintf yaooc_ostream_vprintf
#define yaooc_ofstream_write yaooc_ostream_write
#define yaooc_ofstream_putstr yaooc_ostream_putstr
#define yaooc_ofstream_putchr yaooc_ostream_putchr
 void yaooc_ofstream_open(pointer,const char*,const char*);
 void yaooc_ofstream_close(pointer);

#endif
