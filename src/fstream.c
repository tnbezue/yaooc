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

#include <yaooc/fstream.h>

/*  Begin YAOOC PreProcessor generated content */


/* yaooc_ifstream private members */

/* yaooc_ifstream type info members */
void yaooc_ifstream_default_ctor(pointer p)
{
//  yaooc_ifstream_pointer this=p;
	yaooc_base_stream_default_ctor(p);
}

void yaooc_ifstream_dtor(pointer p)
{
  yaooc_ifstream_pointer this=p;
	M(this,close);
}



/* Constructors for yaooc_ifstream */
void yaooc_ifstream_ctor_fname_mode(pointer p,va_list args)
{
	yaooc_ifstream_default_ctor(p);
  yaooc_ifstream_pointer this=p;
  const char* fname = va_arg(args,const char*);
  const char* mode = va_arg(args,const char*);
	M(this,open,fname,mode);
}

/* yaooc_ifstream protected members */

/* Class table methods for yaooc_ifstream */
const char* yaooc_ifstream_isa(const_pointer p) { return "yaooc_ifstream_t"; }

void yaooc_ifstream_open(pointer p,const char* fname,const char* mode)
{
  yaooc_ifstream_pointer this=p;
	M(this,close);
	this->handle_=fopen(fname,mode);
}

void yaooc_ifstream_close(pointer p)
{
  yaooc_ifstream_pointer this=p;
	if(this->handle_) {
		fclose(this->handle_);
		this->handle_=NULL;
	}
}

/* Class table for yaooc_ifstream */
yaooc_ifstream_class_table_t yaooc_ifstream_class_table =
{
  .eof = (bool (*) (const_pointer)) yaooc_istream_eof,
  .seek = (bool (*) (pointer,size_t,int)) yaooc_istream_seek,
  .tell = (size_t (*) (const_pointer)) yaooc_istream_tell,
  .bool = (bool (*) (const_pointer)) yaooc_istream_bool,
	.stream = (void (*) (pointer,...)) yaooc_ifstream_stream,
  .scanf = (int (*) (pointer,const char*,...)) yaooc_istream_scanf,
  .vscanf = (int (*) (pointer,const char*,va_list)) yaooc_istream_vscanf,
  .read = (size_t (*) (pointer,void*,size_t,size_t)) yaooc_istream_read,
  .gets = (char* (*) (pointer,char*,size_t)) yaooc_istream_gets,
  .open = (void (*) (pointer,const char*,const char*)) yaooc_ifstream_open,
  .close = (void (*) (pointer)) yaooc_ifstream_close,
};

DEFINE_TYPE_INFO(yaooc_ifstream,Y,Y,N,N,N,N,N,Y,yaooc_istream)


/* yaooc_ofstream private members */

/* yaooc_ofstream type info members */
void yaooc_ofstream_default_ctor(pointer p)
{
	yaooc_base_stream_default_ctor(p);
}

void yaooc_ofstream_dtor(pointer p)
{
  yaooc_ofstream_pointer this=p;
	M(this,close);
}



/* Constructors for yaooc_ofstream */
void yaooc_ofstream_ctor_fname_mode(pointer p,va_list args)
{
  yaooc_ofstream_pointer this=p;
	yaooc_ofstream_default_ctor(p);
  const char* fname = va_arg(args,const char*);
  const char* mode = va_arg(args,const char*);
	M(this,open,fname,mode);
}



/* yaooc_ofstream protected members */

/* Class table methods for yaooc_ofstream */
const char* yaooc_ofstream_isa(const_pointer p) { return "yaooc_ofstream_t"; }

void yaooc_ofstream_open(pointer p,const char* fname,const char* mode)
{
	yaooc_ofstream_pointer this=p;
	M(this,close);
	this->handle_=fopen(fname,mode);
}

void yaooc_ofstream_close(pointer p)
{
	yaooc_ofstream_pointer this=p;
	if(this->handle_) {
		fclose(this->handle_);
		this->handle_=NULL;
	}
}


/* Class table for yaooc_ofstream */
yaooc_ofstream_class_table_t yaooc_ofstream_class_table =
{
  .eof = (bool (*) (const_pointer)) yaooc_ostream_eof,
  .seek = (bool (*) (pointer,size_t,int)) yaooc_ostream_seek,
  .tell = (size_t (*) (const_pointer)) yaooc_ostream_tell,
  .bool = (bool (*) (const_pointer)) yaooc_ostream_bool,
	.stream = (void (*) (pointer,...)) yaooc_ofstream_stream,
  .printf = (int (*) (pointer,const char*,...)) yaooc_ostream_printf,
  .vprintf = (int (*) (pointer,const char*,va_list)) yaooc_ostream_vprintf,
  .write = (size_t (*) (pointer,const void*,size_t,size_t)) yaooc_ostream_write,
  .puts = (void (*) (pointer,const char*)) yaooc_ostream_puts,
  .open = (void (*) (pointer,const char*,const char*)) yaooc_ofstream_open,
  .close = (void (*) (pointer)) yaooc_ofstream_close,
};

DEFINE_TYPE_INFO(yaooc_ofstream,Y,Y,N,N,N,N,N,Y,yaooc_ostream)

/*  End YAOOC PreProcessor generated content */
