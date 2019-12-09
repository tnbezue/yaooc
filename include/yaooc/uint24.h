#ifndef __UINT24_INCLUDED__
#define __UINT24_INCLUDED__

#include <yaooc/new.h>
#include <yaooc/stream.h>
typedef uint8_t uint8_bytes_t[3];

yaooc_pod_struct(yaooc_uint24) {
uint8_bytes_t bytes_;
};
int yaooc_uint24_rich_compare(const_pointer,const_pointer);
void yaooc_uint24_to_stream(const_pointer,ostream_pointer);
void yaooc_uint24_from_stream(pointer,ostream_pointer);
 uint32_t yaooc_uint24_to_uint32(const_pointer);
 void yaooc_uint24_from_uint32(pointer,uint32_t);
#define tbi_lt_cmp(p1,p2) yaooc_uint24_to_uint32((p1) < yaooc_uint24_to_uint32(p2))
#define uint32_to_yaooc_uint24 yaooc_uint24_from_uint32


#endif
