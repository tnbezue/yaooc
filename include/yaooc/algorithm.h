#ifndef __ALGORITHM_INCLUDED__
#define __ALGORITHM_INCLUDED__

#include <yaooc/new.h>

iterator __yaooc_move(const_iterator,const_iterator,iterator);
#define yaooc_move(F,L,D) __yaooc_move(F,L,D)

iterator __yaooc_find(const type_info_t*,const_iterator,const_iterator,const_pointer);
#define yaooc_find(T,F,L,V) __yaooc_find(T ## _ti,F,L,V)
const_iterator __yaooc_find_if(const type_info_t*,const_iterator,const_iterator,bool(*f)(const void*));
#define yaooc_find_if(T,F,L,P) __yaooc_find_if(T ## _ti,F,L,P)
const_iterator __yaooc_find_if_not(const type_info_t*,const_iterator,const_iterator,bool(*f)(const void*));
#define yaooc_find_if_not(T,F,L,Q) __yaooc_find_if_not(T ## _ti,F,L,Q)

bool __yaooc_all_of(const type_info_t*,const_iterator,const_iterator,bool(*f)(const void*));
#define yaooc_all_of(T,F,L,Q) __yaooc_all_of(T ## _ti,F,L,Q)
bool __yaooc_any_of(const type_info_t*,const_iterator,const_iterator,bool(*f)(const void*));
#define yaooc_any_of(T,F,L,Q) __yaooc_any_of(T ## _ti,F,L,Q)
bool __yaooc_none_of(const type_info_t*,const_iterator,const_iterator,bool(*f)(const void*));
#define yaooc_none_of(T,F,L,Q) __yaooc_none_of(T ## _ti,F,L,Q)

iterator __yaooc_copy(const type_info_t*,const_iterator,const_iterator,iterator);
#define yaooc_copy(T,F,L,D) __yaooc_copy(T ## _ti,F,L,D)
iterator __yaooc_copy_if(const type_info_t*,const_iterator,const_iterator,iterator,bool(*fun)(const void*));
#define yaooc_copy_if(T,F,L,D,FUN) __yaooc_copy_if(T ## _ti,F,L,D,FUN)

void __yaooc_for_each(const type_info_t*,iterator,iterator,void(*f)(void*));
#define yaooc_for_each(T,F,L,FUN) __yaooc_for_each(T ## _ti,F,L,FUN)

size_t __yaooc_count(const type_info_t*,const_iterator,const_iterator,const_pointer);
#define yaooc_count(T,F,L,V) __yaooc_count(T ## _ti,F,L,V)
size_t __yaooc_count_if(const type_info_t*,const_iterator,const_iterator,bool(*fun)(const void*));
#define yaooc_count_if(T,F,L,FUN) __yaooc_count_if(T ## _ti,F,L,FUN)

void __yaooc_fill(const type_info_t*,iterator,iterator,const_pointer);
#define yaooc_fill(T,F,L,V) __yaooc_fill(T ## _ti,F,L,V)

iterator __yaooc_remove(const type_info_t*,iterator,iterator,const_pointer);
#define yaooc_remove(T,F,L,V) __yaooc_remove(T ## _ti,F,L,V)
iterator __yaooc_remove_if(const type_info_t*,iterator,iterator,bool(*fun)(const void*));
#define yaooc_remove_if(T,F,L,FUN) __yaooc_remove_if(T ## _ti,F,L,FUN)
iterator __yaooc_remove_copy(const type_info_t*,const_iterator,const_iterator,iterator,const_pointer);
#define yaooc_remove_copy(T,F,L,D,V) __yaooc_remove_copy(T ## _ti,F,L,D,V)
iterator __yaooc_remove_copy_if(const type_info_t*,const_iterator,const_iterator,iterator,bool(*fun)(const void*));
#define yaooc_remove_copy_if(T,F,L,D,FUN) __yaooc_remove_copy_if(T ## _ti,F,L,D,FUN)

typedef struct {
	const_iterator first;
	const_iterator second;
} yaooc_iterator_pair_t;

yaooc_iterator_pair_t __yaooc_mismatch(const type_info_t*,const_iterator,const_iterator,const_iterator,const_iterator);
#define yaooc_mismatch(T,F1,L1,F2,L2) __yaooc_mismatch(T ## _ti,F1,L1,F2,L2)

const_iterator __yaooc_find_end(const type_info_t*,const_iterator,const_iterator,const_iterator,const_iterator);
#define yaooc_find_end(T,F,L,SF,SL) __yaooc_find_end(T ## _ti,F,L,SF,SL)

const_iterator __yaooc_find_first_of(const type_info_t*,const_iterator,const_iterator,const_iterator,const_iterator);
#define yaooc_find_first_of(T,F,L,SF,SL) __yaooc_find_first_of(T ## _ti,F,L,SF,SL)

const_iterator __yaooc_search(const type_info_t*,const_iterator,const_iterator,const_iterator,const_iterator);
#define yaooc_search(T,F,L,SF,SL) __yaooc_search(T ## _ti,F,L,SF,SL)



#endif
