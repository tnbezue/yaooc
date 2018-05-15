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

#ifndef __FSTREAM_INCLUDED__
#define __FSTREAM_INCLUDED__

#include <yaooc/stream.h>

/*  Begin YAOOC PreProcessor generated content */

/*
  Class definition for yaooc_ifstream
*/
class_table(yaooc_ifstream)
{
  yaooc_istream_class_table_t;
	void (*open)(pointer,const char*,const char*);
  void (*close)(pointer);
};
#define yaooc_ifstream_parent_class_table ((yaooc_istream_class_table_t*)(yaooc_ifstream_class_table.parent_class_table_))

class_instance(yaooc_ifstream)
{
  yaooc_istream_class_instance_t;
};

class(yaooc_ifstream);

/* Prototypes for yaooc_ifstream type info */
void yaooc_ifstream_default_ctor(pointer);
void yaooc_ifstream_dtor(pointer);

/* Prototypes for yaooc_ifstream constructors */
void yaooc_ifstream_ctor_fname_mode(pointer,va_list);

/* Prototypes for yaooc_ifstream class table */
const char* yaooc_ifstream_isa(const_pointer);
#define yaooc_ifstream_is_descendant yaooc_istream_is_descendant
#define yaooc_ifstream_swap yaooc_istream_swap
#define yaooc_ifstream_to_s yaooc_istream_to_s
#define yaooc_ifstream_eof yaooc_istream_eof
#define yaooc_ifstream_seek yaooc_istream_seek
#define yaooc_ifstream_tell yaooc_istream_tell
#define yaooc_ifstream_bool yaooc_istream_bool
#define yaooc_ifstream_scanf yaooc_istream_scanf
#define yaooc_ifstream_vscanf yaooc_istream_vscanf
#define yaooc_ifstream_read yaooc_istream_read
#define yaooc_ifstream_gets yaooc_istream_gets
void yaooc_ifstream_open(pointer,const char*,const char*);
void yaooc_ifstream_close(pointer);

/* Prototypes for yaooc_ifstream protected members */


/*
  Class definition for yaooc_ofstream
*/
class_table(yaooc_ofstream)
{
  yaooc_ostream_class_table_t;
	void (*open)(pointer,const char*,const char*);
 	void (*close)(pointer);
};
#define yaooc_ofstream_parent_class_table ((yaooc_ostream_class_table_t*)(yaooc_ofstream_class_table.parent_class_table_))

class_instance(yaooc_ofstream)
{
  yaooc_ostream_class_instance_t;
};

class(yaooc_ofstream);

/* Prototypes for yaooc_ofstream type info */
void yaooc_ofstream_default_ctor(pointer);
void yaooc_ofstream_dtor(pointer);

/* Prototypes for yaooc_ofstream constructors */
void yaooc_ofstream_ctor_fname_mode(pointer,va_list);

/* Prototypes for yaooc_ofstream class table */
const char* yaooc_ofstream_isa(const_pointer);
#define yaooc_ofstream_is_descendant yaooc_ostream_is_descendant
#define yaooc_ofstream_swap yaooc_ostream_swap
#define yaooc_ofstream_to_s yaooc_ostream_to_s
#define yaooc_ofstream_eof yaooc_ostream_eof
#define yaooc_ofstream_seek yaooc_ostream_seek
#define yaooc_ofstream_tell yaooc_ostream_tell
#define yaooc_ofstream_bool yaooc_ostream_bool
#define yaooc_ofstream_printf yaooc_ostream_printf
#define yaooc_ofstream_vprintf yaooc_ostream_vprintf
#define yaooc_ofstream_write yaooc_ostream_write
#define yaooc_ofstream_puts yaooc_ostream_puts
void yaooc_ofstream_open(pointer,const char*,const char*);
void yaooc_ofstream_close(pointer);

/* Prototypes for yaooc_ofstream protected members */

/*  End YAOOC PreProcessor generated content */

#endif
