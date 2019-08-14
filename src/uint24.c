/* Begin YAOOCPP output */

#include <yaooc/uint24.h>

#include <string.h>

/* Private variables implementation for yaooc_uint24 */

/* Private methods prototypes for yaooc_uint24 */

/* Type Info implemmentation for yaooc_uint24 */
bool yaooc_uint24_less_than_compare(const_pointer p1,const_pointer p2)
{
  return yaooc_uint24_to_uint32(p1) < yaooc_uint24_to_uint32(p2);
}

void yaooc_uint24_to_stream(const_pointer p,ostream_pointer o)
{
  yaooc_uint24_const_pointer this=p;
  yaooc_ostream_pointer ostrm=o;
  M(ostrm,printf,"%u",yaooc_uint24_to_uint32(this));
}

void yaooc_uint24_from_stream(pointer p,istream_pointer i)
{
  yaooc_uint24_pointer this=p;
  yaooc_istream_pointer istrm=i;
  uint32_t ui32;
  M(istrm,scanf,"%u",&ui32);
  yaooc_uint24_from_uint32(this,ui32);
}

/* Constructors implementation for yaooc_uint24 */

/* Private methods implementation for yaooc_uint24 */

/* Protected implementation for yaooc_uint24 */
uint32_t yaooc_uint24_to_uint32(const_pointer p)
{
  yaooc_uint24_const_pointer this=p;
  uint32_t ui=0;
  memcpy(&ui,this->bytes_,3);
  return ui;
}

void yaooc_uint24_from_uint32(pointer p,uint32_t ui)
{
  yaooc_uint24_pointer this=p;
  memcpy(this->bytes_,&ui,3);
}


/* Type info structure for yaooc_uint24 */
DEFINE_POD_TYPE_INFO(yaooc_uint24,Y,Y,Y)

/* End YAOOCPP output */
