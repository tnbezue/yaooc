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

#ifndef __POINTER_BAG_INCLUDED__
#define __POINTER_BAG_INCLUDED__

#include <yaooc/object.h>
#include <yaooc/pod_array.h>

/* YAOOC_POD_ARRAY_DEFINITION(pointer,pointer_bag_array) */

/*
  Class definition for yaooc_pointer_bag
*/
yaooc_class_table(yaooc_pointer_bag)
{
  yaooc_pod_array_class_table_t;
  pointer (*push)(pointer,pointer);
  void (*push_list)(pointer,...);
  void (*remove)(pointer,pointer);
  void (*clear)(pointer);
  void (*delete_all)(pointer);
};

yaooc_class_instance(yaooc_pointer_bag)
{
  yaooc_pod_array_class_instance_t;
};

yaooc_class(yaooc_pointer_bag);

typedef pointer* pointer_bag_iterator;
typedef const pointer* pointer_bag_const_iterator;

/* Prototypes for type info */
void yaooc_pointer_bag_default_ctor(pointer);
void yaooc_pointer_bag_dtor(pointer);

/* Prototypes for Constructors */

/* Prototypes for class table members */
const char* yaooc_pointer_bag_isa(const_pointer);
#define yaooc_pointer_bag_is_descendant yaooc_object_is_descendant
void yaooc_pointer_bag_swap(pointer,pointer);
pointer yaooc_pointer_bag_push(pointer,pointer);
void yaooc_pointer_bag_push_list(pointer,...);
void yaooc_pointer_bag_remove(pointer,pointer);
void yaooc_pointer_bag_clear(pointer);
void yaooc_pointer_bag_delete_all(pointer);
size_t yaooc_pointer_bag_size(const_pointer);
bool yaooc_pointer_bag_empty(const_pointer);

/* Prototypes for class instance members */

/* Prototypes for class protected members */


/* Use this at start of routine */
#define PB_INIT  yaooc_pointer_bag_pointer local_pb=__new_array(yaooc_pointer_bag_ti,1)
/* Saves objects to be deleted at end */
#define PB_SAVE(ptr) (local_pb->class_table_->push(local_pb,ptr))
/* Clears objects, thus none will be deleted at end */
#define PB_CLEAR  (local_pb->class_table_->clear(local_pb))
/* Delete pointers contained in pointer */
#define PB_DELETE (local_pb->class_table_->delete_all(local_pb))
/* Delete pointers in bag and delete pointer bag */
#define PB_EXIT   delete(local_pb)

#endif
