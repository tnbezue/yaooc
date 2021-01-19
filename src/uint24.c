#include <yaooc/uint24.h>
#include <string.h>
typedef union {
  struct {
#   if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
      uint8_t not_used;
      uint8_t tbi[3];
#   else
      uint8_t tbi[3];
      uint8_t not_used;
#   endif
  };
  uint32_t ui32;
} uint32_uint24_conversion_t;



int yaooc_uint24_rich_compare(const_pointer __plhs__,const_pointer __prhs__)
{
yaooc_uint24_const_pointer lhs=__plhs__;(void)lhs;
yaooc_uint24_const_pointer rhs=__prhs__;(void)rhs;


      return yaooc_uint24_to_uint32(lhs) - yaooc_uint24_to_uint32(rhs);
    
}
void yaooc_uint24_to_stream(const_pointer __pthis__,ostream_pointer __pstrm__)
{
yaooc_uint24_const_pointer this=__pthis__;(void)this;
yaooc_ostream_pointer ostrm=__pstrm__;(void)ostrm;


      M(ostrm,printf,"%u",yaooc_uint24_to_uint32(this));
    
}
void yaooc_uint24_from_stream(pointer __pthis__,ostream_pointer __pstrm__)
{
yaooc_uint24_pointer this=__pthis__;(void)this;
yaooc_istream_pointer istrm=__pstrm__;(void)istrm;


      uint32_t ui32;
      M(istrm,scanf,"%u",&ui32);
      yaooc_uint24_from_uint32(this,ui32);
    
}
uint32_t yaooc_uint24_to_uint32(const_pointer __pthis__)
{
yaooc_uint24_const_pointer this=__pthis__;(void)this;

      uint32_uint24_conversion_t temp;
      temp.ui32=0;
      memcpy(temp.tbi,this->bytes_,3);
      return temp.ui32;
    
}
void yaooc_uint24_from_uint32(pointer __pthis__,uint32_t ui)
{
yaooc_uint24_pointer this=__pthis__;(void)this;

      memcpy(this->bytes_,((const uint32_uint24_conversion_t*)&ui)->tbi,3);
    
}
const pod_type_info_t __yaooc_uint24_ti = {
.min_flag_=0,
.pod_flag_=1,
.type_size_=sizeof(yaooc_uint24_t),
.rich_compare_=yaooc_uint24_rich_compare,
.to_stream_=yaooc_uint24_to_stream,
.from_stream_=yaooc_uint24_from_stream,
};
const type_info_t* const yaooc_uint24_ti=(const type_info_t* const)&__yaooc_uint24_ti;
