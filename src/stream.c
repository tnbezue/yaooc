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

#include <yaooc/stream.h>
#include <string.h>

/*  Begin YAOOC PreProcessor generated content */


/* yaooc_stream_exception private members */

/* yaooc_stream_exception type info members */

/* Constructors for yaooc_stream_exception */

/* yaooc_stream_exception protected members */

/* Class table methods for yaooc_stream_exception */

/* Class table for yaooc_stream_exception */
yaooc_stream_exception_class_table_t yaooc_stream_exception_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_exception_class_table,
  .type_name_ = (const char*) "yaooc_stream_exception_t",
  .swap = (void (*) (pointer,pointer)) yaooc_exception_swap,
  .what = (const char* (*) (const_pointer)) yaooc_stream_exception_what,
};

DEFINE_TYPE_INFO(yaooc_stream_exception,N,N,N,N,N,N,N,Y,yaooc_exception);

/* yaooc_base_stream private members */

/* yaooc_base_stream type info members */
void yaooc_base_stream_default_ctor(pointer p)
{
	((yaooc_base_stream_pointer)p)->handle_=NULL;
}

/* Constructors for yaooc_base_stream */


/* yaooc_base_stream protected members */
void yaooc_base_stream_set_handle(pointer p,FILE* h)
{
  yaooc_base_stream_pointer this=p;
	this->handle_=h;
}

/* Class table methods for yaooc_base_stream */

bool yaooc_base_stream_eof(const_pointer p)
{
  yaooc_base_stream_const_pointer this=p;
  return this->handle_ ? feof(this->handle_) : true;
}

bool yaooc_base_stream_seek(pointer p,size_t ofs,int whence)
{
  yaooc_base_stream_pointer this=p;
	return fseek(this->handle_,ofs,whence) == 0;
}

size_t yaooc_base_stream_tell(const_pointer p)
{
  yaooc_base_stream_const_pointer this=p;
  return ftell(this->handle_);
}

bool yaooc_base_stream_bool(const_pointer p)
{
  yaooc_base_stream_const_pointer this=p;
	return this->handle_ != NULL;
}


/* Class table for yaooc_base_stream */
yaooc_base_stream_class_table_t yaooc_base_stream_class_table =
{
  .eof = (bool (*) (const_pointer)) yaooc_base_stream_eof,
  .seek = (bool (*) (pointer,size_t,int)) yaooc_base_stream_seek,
  .tell = (size_t (*) (const_pointer)) yaooc_base_stream_tell,
  .bool = (bool (*) (const_pointer)) yaooc_base_stream_bool,
};

DEFINE_TYPE_INFO(yaooc_base_stream,Y,N,N,N,N,N,N,Y,yaooc_object);


/* yaooc_istream private members */

/* yaooc_istream type info members */
void yaooc_istream_default_ctor(pointer p)
{
  yaooc_base_stream_default_ctor(p);
}

/* Constructors for yaooc_istream */


/* yaooc_istream protected members */

/* Class table methods for yaooc_istream */

void yaooc_istream_stream(pointer p,...)
{
	va_list args;
	va_start(args,p);
	void* ptr;
	while((ptr = va_arg(args,pointer)) != NULL) {
		memory_header_t* smh=get_memory_header(ptr);
		from_stream from_s = get_from_stream(get_type_info(ptr));
		if(from_s) {
			if(smh->n_elem_==(size_t)-1) {
				ptr=va_arg(args,pointer);
				from_s(ptr,p);
			} else {
				from_s(ptr,p);
			}
		} else
			THROW(new_ctor(yaooc_stream_exception,yaooc_stream_exception_ctor_v,"No from_stream method for object"));
	}
	va_end(args);
}

int yaooc_istream_peek(pointer p)
{
  yaooc_istream_pointer this=p;
	int c=0;
	if(this->handle_) {
		c=fgetc(this->handle_);
		ungetc(c,this->handle_);
	}
	return c;
}

int yaooc_istream_scanf(pointer p,const char* fmt,...)
{
  yaooc_istream_pointer this=p;
  va_list args;
	va_start(args,fmt);
	int ret=M(this,vscanf,fmt,args);
	va_end(args);
  return ret;
}

int yaooc_istream_vscanf(pointer p,const char* fmt,va_list args)
{
  yaooc_istream_pointer this=p;
	return vfscanf(this->handle_,fmt,args);
}

size_t yaooc_istream_read(pointer p,void* buffer,size_t size,size_t count)
{
  yaooc_istream_pointer this=p;
	return fread(buffer,size,count,this->handle_);
}

char* yaooc_istream_getstr(pointer p,char* buffer,size_t n)
{
  yaooc_istream_pointer this=p;
	return fgets(buffer,n,this->handle_);
}


/* Class table for yaooc_istream */
yaooc_istream_class_table_t yaooc_istream_class_table =
{
  .eof = (bool (*) (const_pointer)) yaooc_base_stream_eof,
  .seek = (bool (*) (pointer,size_t,int)) yaooc_base_stream_seek,
  .tell = (size_t (*) (const_pointer)) yaooc_base_stream_tell,
  .bool = (bool (*) (const_pointer)) yaooc_base_stream_bool,
	.stream = (void (*) (pointer,...)) yaooc_istream_stream,
  .peek = (int (*) (pointer)) yaooc_istream_peek,
  .scanf = (int (*) (pointer,const char*,...)) yaooc_istream_scanf,
  .vscanf = (int (*) (pointer,const char*,va_list)) yaooc_istream_vscanf,
  .read = (size_t (*) (pointer,void*,size_t,size_t)) yaooc_istream_read,
  .getstr = (char* (*) (pointer,char*,size_t)) yaooc_istream_getstr,
};

DEFINE_TYPE_INFO(yaooc_istream,Y,N,N,N,N,N,N,Y,yaooc_base_stream);


/* yaooc_ostream private members */

/* yaooc_ostream type info members */
void yaooc_ostream_default_ctor(pointer p)
{
  yaooc_base_stream_default_ctor(p);
}

/* Constructors for yaooc_ostream */


/* yaooc_ostream protected members */

/* Class table methods for yaooc_ostream */

void yaooc_ostream_stream(pointer p,...)
{
	va_list args;
	va_start(args,p);
	const void* ptr;
	while((ptr = va_arg(args,const_pointer)) != NULL) {
		memory_header_t* smh=get_memory_header(ptr);
		to_stream to_s = get_to_stream(smh->type_info_);
		if(to_s) {
			if(smh->n_elem_==(size_t)-1) { // POD and next object in stream is actual value
				if(smh->type_info_==yaooc_ccs_ti) {
					ptr=va_arg(args,const char*);
					to_s(ptr,p);
				} else if(smh->type_info_==int_ti || smh->type_info_==char_ti || smh->type_info_==short_ti) {
					int_t v=va_arg(args,int_t);
					to_s(&v,p);
				} else if(smh->type_info_==uint_ti || smh->type_info_==uchar_ti || smh->type_info_==ushort_ti) {
					uint_t v=va_arg(args,uint_t);
					to_s(&v,&v);
				} else if(smh->type_info_==double_ti) {
					double v=va_arg(args,double);
					to_s(&v,p);
				} else if(smh->type_info_==long_ti) {
					long_t v=va_arg(args,long_t);
					to_s(&v,p);
				} else if(smh->type_info_==ulong_ti) {
					ulong_t v=va_arg(args,ulong_t);
					to_s(&v,p);
				} else if(smh->type_info_==size_ti) {
					ulong_t v=va_arg(args,size_t);
					to_s(&v,p);
				} else { /* Static object */
					ptr = va_arg(args,pointer);
					to_s(ptr,p);
				}
			} else { // dynamic object
				to_s(ptr,p);
			}
		} else {
			THROW(new_ctor(yaooc_stream_exception,yaooc_stream_exception_ctor_v,"No to_stream method for object"));
		}
	}
	va_end(args);
}

int yaooc_ostream_printf(pointer p,const char* fmt,...  )
{
  yaooc_ostream_pointer this=p;
	va_list args;
  va_start(args,fmt);
  int ret=M(this,vprintf,fmt,args);
  va_end(args);
	return ret;
}

int yaooc_ostream_vprintf(pointer p,const char* fmt,va_list args)
{
  yaooc_ostream_pointer this=p;
  return vfprintf(this->handle_,fmt,args);
}

size_t yaooc_ostream_write(pointer p,const void* buffer,size_t size,size_t count)
{
  yaooc_ostream_pointer this=p;
  return fwrite(buffer,size,count,this->handle_);
}

int yaooc_ostream_putstr(pointer p,const char* str)
{
	yaooc_ostream_pointer this=p;
	return fputs(str,this->handle_);
}

int yaooc_ostream_putchr(pointer p,int c)
{
	yaooc_ostream_pointer this=p;
	return fputc(c,this->handle_);
}


/* Class table for yaooc_ostream */
yaooc_ostream_class_table_t yaooc_ostream_class_table =
{
  .eof = (bool (*) (const_pointer)) yaooc_base_stream_eof,
  .seek = (bool (*) (pointer,size_t,int)) yaooc_base_stream_seek,
  .tell = (size_t (*) (const_pointer)) yaooc_base_stream_tell,
  .bool = (bool (*) (const_pointer)) yaooc_base_stream_bool,
	.stream = (void (*) (pointer,...)) yaooc_ostream_stream,
  .printf = (int (*) (pointer,const char*,...)) yaooc_ostream_printf,
  .vprintf = (int (*) (pointer,const char*,va_list)) yaooc_ostream_vprintf,
  .write = (size_t (*) (pointer,const void*,size_t,size_t)) yaooc_ostream_write,
	.putstr = (int (*) (pointer,const char*)) yaooc_ostream_putstr,
	.putchr = (int (*) (pointer,int)) yaooc_ostream_putchr,
};

	DEFINE_TYPE_INFO(yaooc_ostream,Y,N,N,N,N,N,N,Y,yaooc_base_stream);

/*  End YAOOC PreProcessor generated content */

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
//POD_TO_FROM_STREAM(double,"%lf")
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
//POD_TO_FROM_STREAM(pointer,"%p")
//POD_TO_FROM_STREAM(yaooc_ccs,"%s")
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

//extern type_info_t __yaooc_ccs_ti;
