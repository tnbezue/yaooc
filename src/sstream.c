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

#include <string.h>
#include <yaooc/sstream.h>

/*  Begin YAOOC PreProcessor generated content */


/* yaooc_istringstream private members */

/* yaooc_istringstream type info members */
void yaooc_istringstream_default_ctor(pointer p)
{
  yaooc_istringstream_pointer this=p;
	yaooc_base_stream_default_ctor(p);
	this->buffer_=NULL;
}

void yaooc_istringstream_dtor(pointer p)
{
  yaooc_istringstream_pointer this=p;
	if(this->handle_) {
		fclose(this->handle_);
		this->handle_=NULL;
	}
	if(this->buffer_)
		FREE(this->buffer_);
}



/* Constructors for yaooc_istringstream */
void yaooc_istringstream_ctor_ccs(pointer p,va_list args)
{
  yaooc_istringstream_pointer this=p;
	yaooc_base_stream_default_ctor(p);
  const char* str = va_arg(args,const char*);
	yaooc_istringstream_setn(p,str,SIZE_MAX);
}

void yaooc_istringstream_ctor_ccs_n(pointer p,va_list args)
{
  yaooc_istringstream_pointer this=p;
	yaooc_base_stream_default_ctor(p);
  const char* str = va_arg(args,const char*);
  size_t n = va_arg(args,size_t);
	yaooc_istringstream_setn(p,str,SIZE_MAX);
}

/* yaooc_istringstream protected members */

/* Class table methods for yaooc_istringstream */
const char* yaooc_istringstream_isa(const_pointer p) { return "yaooc_istringstream_t"; }

const char* yaooc_istringstream_c_str(const_pointer p)
{
  yaooc_istringstream_pointer this=(pointer)p;
	if(this->buffer_==NULL) {
		size_t ofs = ftell(this->handle_);
		fseek(this->handle_,0,SEEK_END);
		size_t n=ftell(this->handle_);
		if(n>0) {
			fseek(this->handle_,0,SEEK_SET);
			this->buffer_=MALLOC(n+1);
			fread(this->buffer_,1,n,this->handle_);
			this->buffer_[n]=0;
		}
		fseek(this->handle_,ofs,SEEK_SET);
	}
	return this->buffer_;
}

void yaooc_istringstream_reset(pointer p)
{
  yaooc_istringstream_pointer this=p;
	if(this->handle_)
		fclose(this->handle_);
  this->handle_=tmpfile();
}

void yaooc_istringstream_set(pointer p,const char* str)
{
	yaooc_istringstream_setn(p,str,SIZE_MAX);
}

void yaooc_istringstream_setn(pointer p,const char* str,size_t n)
{
  yaooc_istringstream_pointer this=p;
	yaooc_istringstream_reset(p);
	size_t l= str ? strlen(str) : 0;
	if(n>l) n=l;
	if(n> 0) {
		this->handle_=tmpfile();
		fwrite(str,1,n,this->handle_);
		fseek(this->handle_,0,SEEK_SET);
	}
	this->buffer_=NULL;
}

/* Class table for yaooc_istringstream */
yaooc_istringstream_class_table_t yaooc_istringstream_class_table =
{
  .eof = (bool (*) (const_pointer)) yaooc_istream_eof,
  .seek = (bool (*) (pointer,size_t,int)) yaooc_istream_seek,
  .tell = (size_t (*) (const_pointer)) yaooc_istream_tell,
  .bool = (bool (*) (const_pointer)) yaooc_istream_bool,
	.stream = (void (*) (pointer,...)) yaooc_istringstream_stream,
  .scanf = (int (*) (pointer,const char*,...)) yaooc_istream_scanf,
  .vscanf = (int (*) (pointer,const char*,va_list)) yaooc_istream_vscanf,
  .read = (size_t (*) (pointer,void*,size_t,size_t)) yaooc_istream_read,
  .gets = (char* (*) (pointer,char*,size_t)) yaooc_istream_gets,
  .c_str = (const char* (*) (const_pointer)) yaooc_istringstream_c_str,
  .reset = (void (*) (pointer)) yaooc_istringstream_reset,
  .set = (void (*) (pointer,const char*)) yaooc_istringstream_set,
  .setn = (void (*) (pointer,const char*,size_t)) yaooc_istringstream_setn,
};

DEFINE_TYPE_INFO(yaooc_istringstream,yaooc_istringstream_default_ctor,yaooc_istringstream_dtor,
			NULL,NULL,NULL,NULL,NULL,&yaooc_istringstream_class_table,yaooc_istream)


/* yaooc_ostringstream private members */

/* yaooc_ostringstream type info members */
void yaooc_ostringstream_default_ctor(pointer p)
{
  yaooc_ostringstream_pointer this=p;
	this->buffer_=NULL;
	this->handle_=tmpfile();
}

void yaooc_ostringstream_dtor(pointer p)
{
//  yaooc_ostringstream_pointer this=p;
	yaooc_istringstream_dtor(p);
}



/* Constructors for yaooc_ostringstream */


/* yaooc_ostringstream protected members */

/* Class table methods for yaooc_ostringstream */
const char* yaooc_ostringstream_isa(const_pointer p) { return "yaooc_ostringstream_t"; }

const char* yaooc_ostringstream_c_str(const_pointer p)
{
  yaooc_ostringstream_pointer this=(pointer)p;
	size_t ofs = ftell(this->handle_);
	fseek(this->handle_,0,SEEK_END);
	size_t n=ftell(this->handle_);
	if(n>0) {
		fseek(this->handle_,0,SEEK_SET);
		this->buffer_=MALLOC(n+1);
		fread(this->buffer_,1,n,this->handle_);
		this->buffer_[n]=0;
	}
	fseek(this->handle_,ofs,SEEK_SET);
	return this->buffer_;
}

void yaooc_ostringstream_reset(pointer p)
{
  yaooc_ostringstream_pointer this=p;
  fclose(this->handle_);
  this->handle_=tmpfile();
}


/* Class table for yaooc_ostringstream */
yaooc_ostringstream_class_table_t yaooc_ostringstream_class_table =
{
  .eof = (bool (*) (const_pointer)) yaooc_ostream_eof,
  .seek = (bool (*) (pointer,size_t,int)) yaooc_ostream_seek,
  .tell = (size_t (*) (const_pointer)) yaooc_ostream_tell,
  .bool = (bool (*) (const_pointer)) yaooc_ostream_bool,
	.stream = (void (*) (pointer,...)) yaooc_ostringstream_stream,
  .printf = (int (*) (pointer,const char*,...)) yaooc_ostream_printf,
  .vprintf = (int (*) (pointer,const char*,va_list)) yaooc_ostream_vprintf,
  .write = (size_t (*) (pointer,const void*,size_t,size_t)) yaooc_ostream_write,
  .puts = (void (*) (pointer,const char*)) yaooc_ostream_puts,
  .c_str = (const char* (*) (const_pointer)) yaooc_ostringstream_c_str,
  .reset = (void (*) (pointer)) yaooc_ostringstream_reset,
};

DEFINE_TYPE_INFO(yaooc_ostringstream,yaooc_ostringstream_default_ctor,yaooc_ostringstream_dtor,
			NULL,NULL,NULL,NULL,NULL,&yaooc_ostringstream_class_table,yaooc_ostream)

/*  End YAOOC PreProcessor generated content */
