/* Begin YAOOCPP output */

#include <yaooc/rbtree_index_array_container.h>
#include <sys/types.h>
#include <sys/param.h>

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

/*
	If the index value for this node is >= index, increment it and decrement count.
	If count is zero, return 1 to terminate iteration
*/
int yaooc_rbnode_increment_index(yaooc_rbnode_t* node, unsigned int index,unsigned int* count)
{
	if(node->index_ >= index) {
		node->index_++;
		(*count)--;
		return *count == 0;
	}
	return 0;
}

/*
	If the index value for this node is >= index, decrement it and decrement count.
	If count is zero, return 1 to terminate iteration
*/
int yaooc_rbnode_decrement_index(yaooc_rbnode_t* node, unsigned int index,unsigned int* count)
{
	if(node->index_ >= index) {
		node->index_--;
		(*count)--;
		return *count == 0;
	}
	return 0;
}

/* Private variables implementation for yaooc_rbtree_index_array_container */

/* Private methods prototypes for yaooc_rbtree_index_array_container */
static void yaooc_rbtree_index_array_container_rotate_left(pointer, yaooc_rbnode_t*);
static void yaooc_rbtree_index_array_container_rotate_right(pointer, yaooc_rbnode_t*);
static yaooc_rbnode_t* yaooc_rbtree_index_array_container_rbsuccessor(pointer, yaooc_rbnode_t*);
static void yaooc_rbtree_index_array_container_rbdestroy_private(pointer, yaooc_rbnode_t*);
static void yaooc_rbtree_index_array_container_rbrepair(pointer, yaooc_rbnode_t*);

/* Type Info implemmentation for yaooc_rbtree_index_array_container */
void yaooc_rbtree_index_array_container_dtor(pointer p)
{
  yaooc_rbtree_index_array_container_pointer this=p;
	yaooc_rbtree_index_array_container_rbdestroy_private(this,yaooc_rbtree_index_array_container_rbfirst(this));
}

void yaooc_rbtree_index_array_container_copy_ctor(pointer p,const_pointer s)
{
  call_constructor(p,yaooc_rbtree_index_array_container_ctor_ti,TYPE_INFO(s));
  yaooc_rbtree_index_array_container_assign(p,s);
}

void yaooc_rbtree_index_array_container_assign(pointer p,const_pointer s)
{
  yaooc_rbtree_index_array_container_pointer this=p;
  yaooc_rbtree_index_array_container_const_pointer src=s;
	yaooc_rbtree_index_array_container_clear(this);
//	yaooc_rbtree_index_array_container_rbdestroy_private(this,yaooc_rbtree_index_array_container_rbfirst(this));
//  yaooc_array_container_assign(this,src);
	yaooc_private_const_iterator isrc;
	printf("%zu src items\n",M(src,size));
	for(isrc=M(src,cbegin);isrc!=M(src,cend);isrc+=TYPE_SIZE(src)) {
		yaooc_rbtree_index_array_container_insert(this,M(this,cend),isrc);
	}
}

yaooc_rbnode_t nil = { .left_ = &nil, .right_=&nil, .parent_=&nil };
/* Constructors implementation for yaooc_rbtree_index_array_container */
void yaooc_rbtree_index_array_container_ctor_ti(pointer p,va_list args)
{
  yaooc_rbtree_index_array_container_pointer this=p;
  call_constructor(p,yaooc_array_container_ctor_ti,va_arg(args,const type_info_t*));

	/*
	 * We use a self-referencing sentinel node called nil to simplify the
	 * code by avoiding the need to check for NULL pointers.
	 *
	this->nil_.left_ = this->nil_.right_ = this->nil_.parent_ = &this->nil_;
	this->nil_.color_ = black;
	this->nil_.index_ = 0;
*/
	this->nil_=&nil;
	/*
	 * Similarly, the fake root node keeps us from having to worry
	 * about splitting the root.
	 */
	this->root_.left_ = this->root_.right_ = this->root_.parent_ = &nil;
	this->root_.color_ = black;
	this->root_.index_ = 0;
}


/* Private methods implementation for yaooc_rbtree_index_array_container */
/*
 * Perform a left rotation starting at node.
 */
static void yaooc_rbtree_index_array_container_rotate_left(pointer p,yaooc_rbnode_t* node)
{
	yaooc_rbtree_index_array_container_pointer this=p;
	yaooc_rbnode_t *child;

	child = node->right_;
	node->right_ = child->left_;

	if (child->left_ != yaooc_rbtree_index_array_container_rbnil(this))
		child->left_->parent_ = node;
	child->parent_ = node->parent_;

	if (node == node->parent_->left_)
		node->parent_->left_ = child;
	else
		node->parent_->right_ = child;
	child->left_ = node;
	node->parent_ = child;
}

/*
 * Perform a right rotation starting at node.
 */
static void yaooc_rbtree_index_array_container_rotate_right(pointer p,yaooc_rbnode_t* node)
{
	yaooc_rbtree_index_array_container_pointer this=p;
	yaooc_rbnode_t *child;

	child = node->left_;
	node->left_ = child->right_;

	if (child->right_ != yaooc_rbtree_index_array_container_rbnil(this))
	child->right_->parent_ = node;
	child->parent_ = node->parent_;

	if (node == node->parent_->left_)
	node->parent_->left_ = child;
	else
	node->parent_->right_ = child;
	child->right_ = node;
	node->parent_ = child;
}

static yaooc_rbnode_t* yaooc_rbtree_index_array_container_rbsuccessor(pointer p,yaooc_rbnode_t* node)
{
	yaooc_rbtree_index_array_container_pointer this=p;
	yaooc_rbnode_t* ret;

	if ((ret = node->right_) != yaooc_rbtree_index_array_container_rbnil(this)) {
		while (ret->left_ != yaooc_rbtree_index_array_container_rbnil(this))
		ret = ret->left_;
	} else {
		/* No right child, move up until we find it or hit the root */
		for (ret = node->parent_; node == ret->right_; ret = ret->parent_)
			node = ret;
		if (ret == yaooc_rbtree_index_array_container_rbroot(this))
		ret = yaooc_rbtree_index_array_container_rbnil(this);
	}
	return ret;
}

static void yaooc_rbtree_index_array_container_rbdestroy_private(pointer p,yaooc_rbnode_t* node)
{
  yaooc_rbtree_index_array_container_pointer this=p;
	if (node != yaooc_rbtree_index_array_container_rbnil(this)) {
		yaooc_rbtree_index_array_container_rbdestroy_private(this, node->left_);
		yaooc_rbtree_index_array_container_rbdestroy_private(this, node->right_);
		FREE(node);
	}
}

static void yaooc_rbtree_index_array_container_rbrepair(pointer p,yaooc_rbnode_t* node)
{
	yaooc_rbtree_index_array_container_pointer this=p;
	yaooc_rbnode_t *sibling;

	while (node->color_ == black) {
		if (node == node->parent_->left_) {
			sibling = node->parent_->right_;
			if (sibling->color_ == red) {
				sibling->color_ = black;
				node->parent_->color_ = red;
				yaooc_rbtree_index_array_container_rotate_left(this, node->parent_);
				sibling = node->parent_->right_;
			}
			if (sibling->right_->color_ == black && sibling->left_->color_ == black) {
				sibling->color_ = red;
				node = node->parent_;
			} else {
				if (sibling->right_->color_ == black) {
					sibling->left_->color_ = black;
					sibling->color_ = red;
					yaooc_rbtree_index_array_container_rotate_right(this, sibling);
					sibling = node->parent_->right_;
				}
				sibling->color_ = node->parent_->color_;
				node->parent_->color_ = black;
				sibling->right_->color_ = black;
				yaooc_rbtree_index_array_container_rotate_left(this, node->parent_);
				break;
			}
		} else { /* if (node == node->parent_->right_) */
			sibling = node->parent_->left_;
			if (sibling->color_ == red) {
				sibling->color_ = black;
				node->parent_->color_ = red;
				yaooc_rbtree_index_array_container_rotate_right(this, node->parent_);
				sibling = node->parent_->left_;
			}
			if (sibling->right_->color_ == black && sibling->left_->color_ == black) {
				sibling->color_ = red;
				node = node->parent_;
			} else {
				if (sibling->left_->color_ == black) {
					sibling->right_->color_ = black;
					sibling->color_ = red;
					yaooc_rbtree_index_array_container_rotate_left(this, sibling);
					sibling = node->parent_->left_;
				}
				sibling->color_ = node->parent_->color_;
				node->parent_->color_ = black;
				sibling->left_->color_ = black;
				yaooc_rbtree_index_array_container_rotate_right(this, node->parent_);
				break;
			}
		}
	}
}

/* Protected implementation for yaooc_rbtree_index_array_container */
iterator yaooc_rbtree_index_array_container_insert(pointer p,const_iterator pos,const_pointer value)
{
	yaooc_rbtree_index_array_container_pointer this=p;
	yaooc_rbnode_t *node = yaooc_rbtree_index_array_container_rbfirst(this);
	yaooc_rbnode_t *parent = yaooc_rbtree_index_array_container_rbroot(this);

	/* Find correct insertion point. */
	less_than_compare lt_cmp=get_lt_cmp(this->type_info_);
	if(node!=yaooc_rbtree_index_array_container_rbnil(this)) {
		while (node != yaooc_rbtree_index_array_container_rbnil(this)) {
			parent = node;
			if(lt_cmp(value,AT(this,node->index_)))
				node=node->left_;
			else if(lt_cmp(AT(this,node->index_),value))
				node=node->right_;
			else
				return AT(p,node->index_);  // exists, return iterator to data
		}
	}
	// Not found, insert value into array
	iterator ppos=yaooc_array_container_insert(this,pos,value);
	// Renumber indexes
	unsigned int index=INDEX(this,ppos);
	unsigned int n_gt_index=SIZE(this)-index-1;
	if(n_gt_index > 0)
		yaooc_rbtree_index_array_container_rbapply(this,yaooc_rbnode_increment_index,index,&n_gt_index,preorder);
	node = (yaooc_rbnode_t *) MALLOC(sizeof(yaooc_rbnode_t));
	node->index_ = index;
	node->left_ = node->right_ = yaooc_rbtree_index_array_container_rbnil(this);
	node->parent_ = parent;
	if (parent == yaooc_rbtree_index_array_container_rbroot(this) || lt_cmp(value,AT(this,parent->index_)))
		parent->left_ = node;
	else
		parent->right_ = node;
	node->color_ = red;

	/*
	* If the parent node is black we are all set, if it is red we have
	* the following possible cases to deal with.  We iterate through
	* the rest of the tree to make sure none of the required properties
	* is violated.
	*
	*	1) The uncle is red.  We repaint both the parent and uncle black
	*     and repaint the grandparent node red.
	*
	*  2) The uncle is black and the new node is the right child of its
	*     parent, and the parent in turn is the left child of its parent.
	*     We do a left rotation to switch the roles of the parent and
	*     child, relying on further iterations to fixup the old parent.
	*
	*  3) The uncle is black and the new node is the left child of its
	*     parent, and the parent in turn is the left child of its parent.
	*     We switch the colors of the parent and grandparent and perform
	*     a right rotation around the grandparent.  This makes the former
	*     parent the parent of the new node and the former grandparent.
	*
	* Note that because we use a sentinel for the root node we never
	* need to worry about replacing the root.
	*/
	while (node->parent_->color_ == red) {
		yaooc_rbnode_t *uncle;
		if (node->parent_ == node->parent_->parent_->left_) {
			uncle = node->parent_->parent_->right_;
			if (uncle->color_ == red) {
			node->parent_->color_ = black;
			uncle->color_ = black;
			node->parent_->parent_->color_ = red;
			node = node->parent_->parent_;
			} else /* if (uncle->color_ == black) */ {
				if (node == node->parent_->right_) {
					node = node->parent_;
					yaooc_rbtree_index_array_container_rotate_left(this, node);
				}
				node->parent_->color_ = black;
				node->parent_->parent_->color_ = red;
				yaooc_rbtree_index_array_container_rotate_right(this, node->parent_->parent_);
			}
		} else { /* if (node->parent_ == node->parent_->parent_->right_) */
			uncle = node->parent_->parent_->left_;
			if (uncle->color_ == red) {
				node->parent_->color_ = black;
				uncle->color_ = black;
				node->parent_->parent_->color_ = red;
				node = node->parent_->parent_;
			} else /* if (uncle->color_ == black) */ {
				if (node == node->parent_->left_) {
					node = node->parent_;
					yaooc_rbtree_index_array_container_rotate_right(this, node);
				}
				node->parent_->color_ = black;
				node->parent_->parent_->color_ = red;
				yaooc_rbtree_index_array_container_rotate_left(this, node->parent_->parent_);
			}
		}
	}
	yaooc_rbtree_index_array_container_rbfirst(this)->color_ = black;	/* first node is always black */
	return ppos;
}

/*
iterator yaooc_rbtree_index_array_container_remove_index(pointer p,unsigned int index)
{
  yaooc_rbtree_index_array_container_pointer this=p;
  iterator ret;
  return ret;
}


iterator yaooc_rbtree_index_array_container_insert(pointer p,const_iterator pos,const_pointer value)
{
	yaooc_private_iterator ppos=(yaooc_private_iterator)pos;
  yaooc_rbnode_t* ret=yaooc_rbtree_index_array_container_rbfind(p,value);
	if(ret == NULL) {
		ppos=yaooc_array_container_insert(p,pos,value);
		unsigned index=INDEX(p,ppos);
		yaooc_rbtree_index_array_container_insert_index(p,index);
	}
	return ppos;
}
*/
/*
	red black tree is unique so only insert 1
*/
iterator yaooc_rbtree_index_array_container_insertn(pointer p,const_iterator pos,size_t n,const_pointer value)
{
	return yaooc_rbtree_index_array_container_insert(p,pos,value);
}

iterator yaooc_rbtree_index_array_container_insert_range(pointer p,const_iterator pos,const_iterator f,const_iterator l)
{
  yaooc_rbtree_index_array_container_pointer this=p;
	yaooc_private_const_iterator first=f;
//	yaooc_private_const_iterator ppos=pos;
	size_t idx=SIZE_MAX;
	size_t ipos=INDEX(p,pos);
	size_t old_size=SIZE(this);
	for(;first!=l;first+=TYPE_SIZE(p)) {
		iterator ret=yaooc_rbtree_index_array_container_insert(p,AT(p,ipos),first);
		if(old_size != SIZE(p)) { // Size changed, must have been an insert.
			if(idx==SIZE_MAX)
				idx=INDEX(p,ret);
			old_size++;
			ipos=INDEX(p,ret)+1;
		}
	}
  return AT(p,idx);
}

/*
yaooc_rbtree_index_array_container_find_result_t yaooc_rbtree_index_array_container_find_protected(pointer p,const_pointer value)
{
  yaooc_rbtree_index_array_container_pointer this=p;
  yaooc_rbtree_index_array_container_find_result_t ret;
  return ret;
}
*/

iterator yaooc_rbtree_index_array_container_find(pointer p,const_pointer value)
{
	yaooc_rbnode_t* node=yaooc_rbtree_index_array_container_rbfind(p,value);
  return node ? AT(p,node->index_) : END(p);
}

iterator yaooc_rbtree_index_array_container_erase(pointer p,const_iterator pos)
{
//  yaooc_rbtree_index_array_container_pointer this=p;
	unsigned int index=INDEX(p,pos);
  yaooc_rbtree_index_array_container_erase_value(p,pos);
	return AT(p,index);
}

size_t yaooc_rbtree_index_array_container_erase_value(pointer p,const_pointer value)
{
  yaooc_rbtree_index_array_container_pointer this=p;
  size_t ret=0;
	yaooc_rbnode_t* node=yaooc_rbtree_index_array_container_rbfind(p,value);
	if(node) {
		yaooc_array_container_erase(p,AT(p,node->index_));
		unsigned int index=node->index_;
		unsigned int n_gt_index=SIZE(p)-index;
		yaooc_rbtree_index_array_container_rbdelete(p,node);
		if(n_gt_index > 0)
			yaooc_rbtree_index_array_container_rbapply(this,yaooc_rbnode_decrement_index,index,&n_gt_index,preorder);
		ret++;
	}
  return ret;
}

iterator yaooc_rbtree_index_array_container_erase_range(pointer p,const_iterator f,const_iterator l)
{
//  yaooc_rbtree_index_array_container_pointer this=p;
  iterator ret=(iterator)f;
	yaooc_private_const_iterator last=l;
	yaooc_private_const_iterator first=f;
	for(last-=TYPE_SIZE(p);last>=first;last-=TYPE_SIZE(p))
		yaooc_rbtree_index_array_container_erase_value(p,last);
  return ret;
}

void yaooc_rbtree_index_array_container_resize(pointer p,size_t n)
{
//  yaooc_rbtree_index_array_container_pointer this=p;
	pointer v=__new_array(TYPE_INFO(p),1);
	yaooc_rbtree_index_array_container_resize_value(p,1,v);
	delete(v);
}

void yaooc_rbtree_index_array_container_resize_value(pointer p,size_t n,const_pointer value)
{
//  yaooc_rbtree_index_array_container_pointer this=p;
	if(n <= SIZE(p)) {
		yaooc_rbtree_index_array_container_erase_range(p,END(p)-(SIZE(p)-n)*TYPE_SIZE(p),END(p));
	} else {
		yaooc_rbtree_index_array_container_insert(p,END(p),value);
	}
}

void yaooc_rbtree_index_array_container_clear(pointer p)
{
  yaooc_rbtree_index_array_container_pointer this=p;
	yaooc_rbtree_index_array_container_rbdestroy_private(this,yaooc_rbtree_index_array_container_rbfirst(this));
	this->root_.left_ = this->root_.right_ = this->root_.parent_ = &nil;
	this->root_.color_ = black;
	this->root_.index_ = 0;
	yaooc_array_container_clear(p);
}

int yaooc_rbtree_index_array_container_rbapply_node(pointer p,yaooc_rbnode_t* node,action_func func,unsigned int index,unsigned int* count,enum rbtraversal order)
{
  yaooc_rbtree_index_array_container_pointer this=p;
  int ret=0;
   if (node != yaooc_rbtree_index_array_container_rbnil(this)) {
    if (order == preorder)
      if ((ret = func(node,index,count)) != 0)
        return(ret);
    if ((ret = yaooc_rbtree_index_array_container_rbapply_node(this, node->left_, func, index, count, order)) != 0)
      return(ret);
    if (order == inorder)
      if ((ret = func(node,index,count)) != 0)
        return(ret);
    if ((ret = yaooc_rbtree_index_array_container_rbapply_node(this, node->right_, func, index, count, order)) != 0)
      return(ret);
    if (order == postorder)
      if ((ret = func(node,index,count)) != 0)
        return(ret);
  }
 return ret;
}

yaooc_rbnode_t* yaooc_rbtree_index_array_container_rbfind(pointer p,const_pointer value)
{
  yaooc_rbtree_index_array_container_pointer this=p;
  yaooc_rbnode_t* ret = yaooc_rbtree_index_array_container_rbfirst(this);

	less_than_compare lt_cmp=get_lt_cmp(TYPE_INFO(p));  // lt_cmp should always be defined
	while (ret != yaooc_rbtree_index_array_container_rbnil(this)) {
		if(lt_cmp(value,AT(this,ret->index_)))
			ret=ret->left_;
		else if(lt_cmp(AT(this,ret->index_),value))
			ret=ret->right_;
		else
			return ret;
	}
	return NULL;
}

/*
yaooc_rbnode_t* yaooc_rbtree_index_array_container_rbinsert(pointer p,const_pointer value)
{
  yaooc_rbtree_index_array_container_pointer this=p;
  yaooc_rbnode_t* ret=yaooc_rbtree_index_array_container_rbfind(p,value);
	if(ret == NULL) {

	}
  return ret;
}
*/
void yaooc_rbtree_index_array_container_rbdelete(pointer p,yaooc_rbnode_t* z)
{
  yaooc_rbtree_index_array_container_pointer this=p;
	yaooc_rbnode_t *x, *y;

	if (z->left_ == yaooc_rbtree_index_array_container_rbnil(this) || z->right_ == yaooc_rbtree_index_array_container_rbnil(this))
		y = z;
	else
		y = yaooc_rbtree_index_array_container_rbsuccessor(this, z);
	x = (y->left_ == yaooc_rbtree_index_array_container_rbnil(this)) ? y->right_ : y->left_;

	if ((x->parent_ = y->parent_) == yaooc_rbtree_index_array_container_rbroot(this)) {
		yaooc_rbtree_index_array_container_rbfirst(this) = x;
	} else {
		if (y == y->parent_->left_)
		y->parent_->left_ = x;
		else
		y->parent_->right_ = x;
	}
	if (y->color_ == black)
		yaooc_rbtree_index_array_container_rbrepair(this, x);
	if (y != z) {
		y->left_ = z->left_;
		y->right_ = z->right_;
		y->parent_ = z->parent_;
		y->color_ = z->color_;
		z->left_->parent_ = z->right_->parent_ = y;
		if (z == z->parent_->left_)
		z->parent_->left_ = y;
		else
		z->parent_->right_ = y;
	}
	FREE(z);
}


/* Table implementation for yaooc_rbtree_index_array_container */
void yaooc_rbtree_index_array_container_swap(pointer p,pointer p2)
{
	yaooc_rbtree_index_array_container_pointer this=p;
	yaooc_rbtree_index_array_container_pointer other=p2;
	yaooc_array_container_swap(this,other);

}


/* Class table definition for yaooc_rbtree_index_array_container */
yaooc_rbtree_index_array_container_class_table_t yaooc_rbtree_index_array_container_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_array_container_class_table,
  .type_name_ = (const char*) "yaooc_rbtree_index_array_container_t",
  .swap = (void(*)(pointer, pointer)) yaooc_rbtree_index_array_container_swap,
  .increase_capacity = (bool(*)(pointer, size_t)) yaooc_rbtree_index_array_container_increase_capacity,
  .size_needed = (size_t(*)(const_pointer, size_t)) yaooc_rbtree_index_array_container_size_needed,
  .size = (size_t(*)(const_pointer)) yaooc_rbtree_index_array_container_size,
  .capacity = (size_t(*)(const_pointer)) yaooc_rbtree_index_array_container_capacity,
  .empty = (bool(*)(const_pointer)) yaooc_rbtree_index_array_container_empty,
  .begin = (iterator(*)(pointer)) yaooc_rbtree_index_array_container_begin,
  .end = (iterator(*)(pointer)) yaooc_rbtree_index_array_container_end,
  .cbegin = (const_iterator(*)(const_pointer)) yaooc_rbtree_index_array_container_cbegin,
  .cend = (const_iterator(*)(const_pointer)) yaooc_rbtree_index_array_container_cend,
};

/* Type info structure for yaooc_rbtree_index_array_container */
DEFINE_TYPE_INFO(yaooc_rbtree_index_array_container,N,Y,Y,Y,N,N,N,Y,yaooc_array_container);

/* End YAOOCPP output */

