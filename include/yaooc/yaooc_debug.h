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

#ifndef __YAOOC_DEBUG_LIST_INCLUDED__
#define __YAOOC_DEBUG_LIST_INCLUDED__

#define DEBUG_ALL 0xFFFFFFFF
#define DEBUG_NONE 0x0

#ifdef	__DEBUG__

#ifndef DEBUG_MASK
#define DEBUG_MASK DEBUG_ALL
#endif

#define debug(x) if((x) & DEBUG_MASK )

#define debug_fprintf(out,fmt,...) fprintf(out,"%s %d: " fmt,__FILE__,__LINE__, ## __VA_ARGS__)
#define debug_printf(fmt,...) printf("%s %d: " fmt,__FILE__,__LINE__, ## __VA_ARGS__)
#define debug_puts(s) debug_printf("%s\n",s)
#define debug_fputs(out,s) debug_fprintf(out,"%s\n",s)

#else

#define	debug(x) if(0)

#define debug_fprintf(out,fmt,...)
#define debug_printf(fmt,...)
#define debug_puts(s)
#define debug_fputs(out,s)

#endif

#define DEBUG_NEW     1
#define DEBUG_OBJECT  1 << 1
#define DEBUG_EXCEPTION  1 << 2
#define DEBUG_ALGORITHM 1 << 3
#define DEBUG_POD_ARRAY 1 << 4
#define DEBUG_ARRAY_CONTAINER 1 << 5
#define DEBUG_STRING 1 << 6
#define DEBUG_VECTOR 1 << 7
#define DEBUG_UNIQUE_ARRAY_CONTAINER 1 << 8
#define DEBUG_ORDERED_ARRAY_CONTAINER 1 << 9
#define DEBUG_UNIQUE_ORDERED_ARRAY_CONTAINER 1 << 10
#define DEBUG_INDEX_ARRAY_CONTAINER 1 << 11
#define DEBUG_UNIQUE_INDEX_ARRAY_CONTAINER 1 << 12
#define DEBUG_MAP   1 << 13
#define DEBUG_SET   1 << 14
#define DEBUG_ORDERED_MAP   1 << 15
#define DEBUG_ORDERED_SET   1 << 16
#define DEBUG_STACK 1 << 17
#define DEBUG_QUEUE 1 << 18
#define DEBUG_MEMORY 1 << 19
#define DEBUG_BASE_PARSER 1 << 20
#define DEBUG_JSON  1 << 21
#define DEBUG_JSON_PARSER  1 << 22
#define DEBUG_REGEX  1 << 23

/*#define DEBUG_MASK DEBUG_NONE*/

#endif
