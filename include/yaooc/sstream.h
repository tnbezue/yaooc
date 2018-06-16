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

#ifndef __SSTREAM_INCLUDED__
#define __SSTREAM_INCLUDED__

#include <yaooc/stream.h>

/*  Begin YAOOC PreProcessor generated content */


/*
  Class definition for yaooc_istringstream
*/
class_table(yaooc_istringstream)
{
  yaooc_istream_class_table_t;
  const char* (*c_str)(const_pointer);
  void (*reset)(pointer);
	void (*set)(pointer,const char*);
	void (*setn)(pointer,const char*,size_t);
};
#define yaooc_istringstream_parent_class_table ((yaooc_istream_class_table_t*)(yaooc_istringstream_class_table.parent_class_table_))

class_instance(yaooc_istringstream)
{
  yaooc_istream_class_instance_t;
	char* buffer_;
};

class(yaooc_istringstream);

/* Prototypes for yaooc_istringstream type info */
void yaooc_istringstream_default_ctor(pointer);
void yaooc_istringstream_dtor(pointer);

/* Prototypes for yaooc_istringstream constructors */
void yaooc_istringstream_ctor_ccs(pointer,va_list);
void yaooc_istringstream_ctor_ccs_n(pointer,va_list);

/* Prototypes for yaooc_istringstream class table */
const char* yaooc_istringstream_isa(const_pointer);
#define yaooc_istringstream_is_descendant yaooc_istream_is_descendant
#define yaooc_istringstream_swap yaooc_istream_swap
#define yaooc_istringstream_to_s yaooc_istream_to_s
#define yaooc_istringstream_eof yaooc_istream_eof
#define yaooc_istringstream_seek yaooc_istream_seek
#define yaooc_istringstream_stream yaooc_istream_stream
#define yaooc_istringstream_tell yaooc_istream_tell
#define yaooc_istringstream_bool yaooc_istream_bool
#define yaooc_istringstream_scanf yaooc_istream_scanf
#define yaooc_istringstream_vscanf yaooc_istream_vscanf
#define yaooc_istringstream_read yaooc_istream_read
#define yaooc_istringstream_gets yaooc_istream_gets
const char* yaooc_istringstream_c_str(const_pointer);
void yaooc_istringstream_reset(pointer);
void yaooc_istringstream_set(pointer,const char*);
void yaooc_istringstream_setn(pointer,const char*,size_t);

/* Prototypes for yaooc_istringstream protected members */


/*
  Class definition for yaooc_ostringstream
*/
class_table(yaooc_ostringstream)
{
  yaooc_ostream_class_table_t;
  const char* (*c_str)(const_pointer);
  void (*reset)(pointer);
};
#define yaooc_ostringstream_parent_class_table ((yaooc_ostream_class_table_t*)(yaooc_ostringstream_class_table.parent_class_table_))

class_instance(yaooc_ostringstream)
{
  yaooc_ostream_class_instance_t;
	char* buffer_;
};

class(yaooc_ostringstream);

/* Prototypes for yaooc_ostringstream type info */
void yaooc_ostringstream_default_ctor(pointer);
void yaooc_ostringstream_dtor(pointer);

/* Prototypes for yaooc_ostringstream constructors */

/* Prototypes for yaooc_ostringstream class table */
const char* yaooc_ostringstream_isa(const_pointer);
#define yaooc_ostringstream_is_descendant yaooc_ostream_is_descendant
#define yaooc_ostringstream_swap yaooc_ostream_swap
#define yaooc_ostringstream_to_s yaooc_ostream_to_s
#define yaooc_ostringstream_eof yaooc_ostream_eof
#define yaooc_ostringstream_seek yaooc_ostream_seek
#define yaooc_ostringstream_tell yaooc_ostream_tell
#define yaooc_ostringstream_bool yaooc_ostream_bool
#define yaooc_ostringstream_stream yaooc_ostream_stream
#define yaooc_ostringstream_printf yaooc_ostream_printf
#define yaooc_ostringstream_vprintf yaooc_ostream_vprintf
#define yaooc_ostringstream_write yaooc_ostream_write
#define yaooc_ostringstream_puts yaooc_ostream_puts
const char* yaooc_ostringstream_c_str(const_pointer);
void yaooc_ostringstream_reset(pointer);

/* Prototypes for yaooc_ostringstream protected members */

/*  End YAOOC PreProcessor generated content */

#endif
