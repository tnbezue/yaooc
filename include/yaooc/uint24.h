#ifndef __UINT24_INCLUDED__
#define __UINT24_INCLUDED__

/* Begin YAOOCPP output */
#include <yaooc/macros.h>
#include <yaooc/stream.h>
/* Useful macros */
#define tbi_lt_cmp(p1,p2) yaooc_uint24_to_uint32((p1) < yaooc_uint24_to_uint32(p2))
#define uint32_to_yaooc_uint24 yaooc_uint24_from_uint32

/*
  Struct Definition for yaooc_uint24
*/
yaooc_pod_struct(yaooc_uint24) {
  uint8_t bytes_[3];
};

/* Protected prototypes for yaooc_uint24 */
uint32_t yaooc_uint24_to_uint32(const_pointer);
void yaooc_uint24_from_uint32(pointer, uint32_t);

/* Type Info Prototypes for yaooc_uint24 */
#define yaooc_uint24_default_ctor yaooc_do_nothing_default_ctor
#define yaooc_uint24_dtor yaooc_do_nothing_dtor
#define yaooc_uint24_copy_ctor yaooc_do_nothing_copy_ctor
#define yaooc_uint24_assign yaooc_do_nothing_assign
int yaooc_uint24_rich_compare(const_pointer,const_pointer);
void yaooc_uint24_to_stream(const_pointer,ostream_pointer);
void yaooc_uint24_from_stream(pointer,istream_pointer);

/* Constructor prototypes for yaooc_uint24 */

/* End YAOOCPP output */


#endif
