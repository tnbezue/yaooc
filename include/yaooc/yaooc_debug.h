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

#ifndef __YAOOC_DEBUG_LIST_INCLUDED__
#define __YAOOC_DEBUG_LIST_INCLUDED__

#include <limits.h>

#define DEBUG_ALL SIZE_MAX
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

#define DEBUG_NEW                            1
#define DEBUG_OBJECT                         DEBUG_NEW << 1
#define DEBUG_EXCEPTION                      DEBUG_OBJECT << 1
#define DEBUG_ALGORITHM                      DEBUG_EXCEPTION << 1
#define DEBUG_ARRAY_CONTAINER                DEBUG_ALGORITHM << 1
#define DEBUG_STRING                         DEBUG_ARRAY_CONTAINER << 1
#define DEBUG_VECTOR                         DEBUG_STRING << 1
#define DEBUG_UNIQUE_ARRAY_CONTAINER         DEBUG_VECTOR << 1
#define DEBUG_ORDERED_ARRAY_CONTAINER        DEBUG_UNIQUE_ARRAY_CONTAINER << 1
#define DEBUG_UNIQUE_ORDERED_ARRAY_CONTAINER DEBUG_ORDERED_ARRAY_CONTAINER << 1
#define DEBUG_INDEX_ARRAY_CONTAINER          DEBUG_UNIQUE_ORDERED_ARRAY_CONTAINER << 1
#define DEBUG_UNIQUE_INDEX_ARRAY_CONTAINER   DEBUG_INDEX_ARRAY_CONTAINER << 1
#define DEBUG_MAP                            DEBUG_UNIQUE_INDEX_ARRAY_CONTAINER << 1
#define DEBUG_SET                            DEBUG_MAP << 1
#define DEBUG_ORDERED_MAP                    DEBUG_SET << 1
#define DEBUG_ORDERED_SET                    DEBUG_ORDERED_MAP << 1
#define DEBUG_STACK                          DEBUG_ORDERED_SET << 1
#define DEBUG_QUEUE                          DEBUG_STACK << 1
#define DEBUG_MEMORY                         DEBUG_QUEUE << 1
#define DEBUG_BASE_PARSER                    DEBUG_MEMORY << 1
#define DEBUG_JSON                           DEBUG_BASE_PARSER << 1
#define DEBUG_JSON_PARSER                    DEBUG_JSON << 1
#define DEBUG_REGEX                          DEBUG_JSON_PARSER  << 1

/*#define DEBUG_MASK DEBUG_NONE*/

#endif
