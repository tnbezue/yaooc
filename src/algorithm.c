#include <assert.h>
#include <string.h>
#include <yaooc/algorithm.h>

iterator yaooc_find(const type_info_t* ti,const_iterator f,const_iterator l,const_pointer value)
{
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
	assert(first <= last && "First > last in yaooc_find");
  less_than_compare lt_cmp=get_lt_cmp(ti);
  if(lt_cmp) {
    while(first!=last && (__lt_cmp__(first,value,lt_cmp) || __lt_cmp__(value,first,lt_cmp)))
      first+=ti->type_size_;
  }
	return (iterator)first;
}

/*
  In C++, the destination iterator can be a template that initilizes dest before copy.  It also
  increases the size/capacity of destination if needed.  That is not available in C.
  Therefore, for copy and copy_if, user must make sure destination has been properly
  initilized and there is sufficient space.  Also
*/
iterator yaooc_copy(const type_info_t* ti,const_iterator f,const_iterator l,iterator d)
{
	assert(f <= l && "First > last in yaooc_copy");
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
  yaooc_private_iterator dst=d;
  if(get_assignment(ti)) {
    for(;first!=last;dst+=ti->type_size_,first+=ti->type_size_)
      real_assign_static(dst,first,ti);
  } else {
    memcpy(dst,first,last-first);
    dst+=last-first;
  }
	return dst;
}

/*
  User must update count of destination if needed.
  Number of elements copied is (returned dest - initial dest)/ti->type_size_
*/
iterator yaooc_copy_if(const type_info_t* ti,const_iterator f,const_iterator l,iterator d,bool(*fun)(const void*))
{
	assert(f <= l && "First > last in yaooc_copy");
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
  yaooc_private_iterator dst=d;
  bool has_assignment=get_assignment(ti) != NULL;
  for(;first!=last;first+=ti->type_size_) {
    if(fun(first)) {
      if(has_assignment) {
        real_assign_static(dst,first,ti);
      } else {
        memcpy(dst,first,ti->type_size_);
      }
      dst+=ti->type_size_;
    }
  }
	return dst;

}

void yaooc_for_each(const type_info_t* ti,iterator f,iterator l,void(*fun)(void*))
{
	yaooc_private_iterator first=f;
	yaooc_private_iterator last=l;
	assert(first <= last && "First > last in yaooc_for_each");
	for(;first!=last;first+=ti->type_size_) {
		fun(first);
	}
}

size_t yaooc_count(const type_info_t* ti,const_iterator f,const_iterator l,const_pointer value)
{
	size_t count=0;
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
	assert(first <= last && "First > last in yaooc_count");
	less_than_compare lt_cmp=get_lt_cmp(ti);
  if(lt_cmp) {
    for(;first!=last;first+=ti->type_size_) {
      if(!(__lt_cmp__(first,value,lt_cmp) || __lt_cmp__(value,first,lt_cmp)))
        count++;
    }
  }
	return count;
}

size_t yaooc_count_if(const type_info_t*ti,const_iterator f,const_iterator l,bool(*fun)(const void*))
{
	size_t count=0;
	yaooc_private_const_iterator first=f;
	yaooc_private_const_iterator last=l;
	assert(first <= last && "First > last in yaooc_count_if");
	for(;first!=last;first+=ti->type_size_) {
		if(fun(first))
			count++;
	}
	return count;
}
