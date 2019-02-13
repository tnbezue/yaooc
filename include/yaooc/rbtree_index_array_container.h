#ifndef __RBTREE_INDEX_ARRAY_CONTAINER_INCLUDED__
#define __RBTREE_INDEX_ARRAY_CONTAINER_INCLUDED__

/* Begin YAOOCPP output */

#include <yaooc/array_container.h>


enum yaooc_rbcolor {
    yaooc_rbred,
    yaooc_rbblack
};

typedef struct yaooc_rbnode_s yaooc_rbnode_t;
struct yaooc_rbnode_s {
	yaooc_rbnode_t* left_;
	yaooc_rbnode_t* right_;
	yaooc_rbnode_t* parent_;
	unsigned int index_;
	enum yaooc_rbcolor color_;
};

extern yaooc_rbnode_t* yaooc_rbnode_rbnil;
#define yaooc_rbtree_index_array_container_rbapply(t, f, i, n, c )	\
			yaooc_rbtree_index_array_container_rbapply_node((t)->root_->left_, (f), (i), n, (c))
#define yaooc_rbtree_index_array_container_rbisempty(t)		((t)->root_->left_ == yaooc_rbnode_rbnil && (t)->root.right_ == yaooc_rbnode_rbnil)
#define yaooc_rbtree_index_array_container_rbfirst(t)		((t)->root_->left_)
#define yaooc_rbtree_index_array_container_rbroot(t)		((t)->root_)
//#define yaooc_rbtree_index_array_container_rbnil(t)		((t)->nil_)

typedef int (*action_func)(yaooc_rbnode_t*, unsigned int,unsigned int,unsigned int*);
int yaooc_rbnode_increment_index(yaooc_rbnode_t*, unsigned int,unsigned int,unsigned int*);
int yaooc_rbnode_decrement_index(yaooc_rbnode_t*, unsigned int,unsigned int,unsigned int*);

/*
	If found is true, node is pointer to pointer of node.
	If found is false, node is pointer to pointer of parent node.
*/
typedef struct { yaooc_rbnode_t** node_; bool found_; } yaooc_rbtree_index_array_container_find_result_t;
/*
  Class Definition for yaooc_rbtree_index_array_container
*/
yaooc_class_table(yaooc_rbtree_index_array_container) {
  yaooc_array_container_class_table_t;
};
#define yaooc_rbtree_index_array_container_parent_class_table ((yaooc_array_container_class_table_t*)(yaooc_rbtree_index_array_container_class_table.parent_class_table_))

yaooc_class_instance(yaooc_rbtree_index_array_container) {
  yaooc_array_container_class_instance_t;
  yaooc_rbnode_t *root_;
};

yaooc_class(yaooc_rbtree_index_array_container);

/* Type Info Prototypes for yaooc_rbtree_index_array_container */
#define yaooc_rbtree_index_array_container_default_ctor yaooc_array_container_default_ctor
void yaooc_rbtree_index_array_container_dtor(pointer);
void yaooc_rbtree_index_array_container_copy_ctor(pointer,const_pointer);
void yaooc_rbtree_index_array_container_assign(pointer,const_pointer);

/* Constructors prototypes for yaooc_rbtree_index_array_container */
void yaooc_rbtree_index_array_container_ctor_ti(pointer,va_list);

/* Table prototypes for yaooc_rbtree_index_array_container */
void yaooc_rbtree_index_array_container_swap(pointer, pointer);
#define yaooc_rbtree_index_array_container_increase_capacity yaooc_array_container_increase_capacity
#define yaooc_rbtree_index_array_container_size_needed yaooc_array_container_size_needed
#define yaooc_rbtree_index_array_container_size yaooc_array_container_size
#define yaooc_rbtree_index_array_container_capacity yaooc_array_container_capacity
#define yaooc_rbtree_index_array_container_empty yaooc_array_container_empty
#define yaooc_rbtree_index_array_container_begin yaooc_array_container_begin
#define yaooc_rbtree_index_array_container_end yaooc_array_container_end
#define yaooc_rbtree_index_array_container_cbegin yaooc_array_container_cbegin
#define yaooc_rbtree_index_array_container_cend yaooc_array_container_cend

/* Protected prototypes for yaooc_rbtree_index_array_container */
//extern void yaooc_rbtree_index_array_container_insert_index(pointer, unsigned int);
//extern void yaooc_rbtree_index_array_container_remove_index(pointer, unsigned int);
extern iterator yaooc_rbtree_index_array_container_insert(pointer, const_iterator, const_pointer);
extern iterator yaooc_rbtree_index_array_container_insertn(pointer, const_iterator, size_t, const_pointer);
extern iterator yaooc_rbtree_index_array_container_insert_range(pointer, const_iterator, const_iterator, const_iterator);
extern iterator yaooc_rbtree_index_array_container_find(pointer, const_pointer);
extern iterator yaooc_rbtree_index_array_container_erase(pointer, const_iterator);
extern size_t yaooc_rbtree_index_array_container_erase_value(pointer, const_pointer);
extern iterator yaooc_rbtree_index_array_container_erase_range(pointer, const_iterator, const_iterator);
extern void yaooc_rbtree_index_array_container_resize(pointer, size_t);
extern void yaooc_rbtree_index_array_container_resize_value(pointer, size_t, const_pointer);
#define yaooc_rbtree_index_array_container_shrink_to_fit yaooc_array_container_shrink_to_fit
#define yaooc_rbtree_index_array_container_reserve yaooc_array_container_reserve
extern void yaooc_rbtree_index_array_container_clear(pointer);
extern int yaooc_rbtree_index_array_container_rbapply_node(yaooc_rbnode_t*, action_func, unsigned int,unsigned int,unsigned int*);
//extern void yaooc_rbtree_index_array_container_delete_node(pointer,yaooc_rbnode_t*);
extern yaooc_rbtree_index_array_container_find_result_t yaooc_rbtree_index_array_container_rbfind(const_pointer, const_pointer);
extern yaooc_rbnode_t* yaooc_rbtree_index_array_container_rbinsert(pointer, const_pointer);
extern void yaooc_rbtree_index_array_container_rbdelete(pointer, yaooc_rbnode_t*);

/* End YAOOCPP output */


#endif
