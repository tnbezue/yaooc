#ifndef __ALGORITHM_INCLUDED__
#define __ALGORITHM_INCLUDED__

#include <yaooc/new.h>

iterator yaooc_find(const type_info_t*,const_iterator,const_iterator,const_pointer);
iterator yaooc_copy(const type_info_t*,const_iterator,const_iterator,iterator);
void yaooc_for_each(const type_info_t*,iterator,iterator,void(*f)(void*));
yaooc_size_type yaooc_count(const type_info_t*,const_iterator,const_iterator,const_pointer);
yaooc_size_type yaooc_count_if(const type_info_t*,const_iterator,const_iterator,bool(*fun)(const void*));
void yaooc_fill(const type_info_t*,iterator,iterator,const_pointer);

#endif
