/* Begin YAOOCPP output */

#include <yaooc/rbtree_index_array_container.h>
#include <sys/types.h>
#include <sys/param.h>

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
yaooc_rbnode_t* yaooc_rbnode_new();
/*
	If the index value for this node is >= index, increment it and decrement count.
	If count is zero, return 1 to terminate iteration
*/
int yaooc_rbnode_increment_index(yaooc_rbnode_t* node, unsigned int index,unsigned int n,unsigned int* count)
{
	if(node->index_ >= index) {
		node->index_+=n;
		(*count)--;
		return *count == 0;
	}
	return 0;
}

/*
	If the index value for this node is >= index, decrement it and decrement count.
	If count is zero, return 1 to terminate iteration
*/
int yaooc_rbnode_decrement_index(yaooc_rbnode_t* node, unsigned int index,unsigned int n,unsigned int* count)
{
	if(node->index_ >= index) {
		node->index_-=n;
		(*count)--;
		return *count == 0;
	}
	return 0;
}

/* Private variables implementation for yaooc_rbtree_index_array_container */

/* Private methods prototypes for yaooc_rbtree_index_array_container */
static void yaooc_rbtree_index_array_container_rotate_left(yaooc_rbnode_t*);
static void yaooc_rbtree_index_array_container_rotate_right( yaooc_rbnode_t*);
static yaooc_rbnode_t* yaooc_rbtree_index_array_container_rbsuccessor(pointer, yaooc_rbnode_t*);
static void yaooc_rbtree_index_array_container_rbdestroy_private(pointer, yaooc_rbnode_t*);
static void yaooc_rbtree_index_array_container_rbrepair(yaooc_rbnode_t*);

/* Type Info implemmentation for yaooc_rbtree_index_array_container */
void yaooc_rbtree_index_array_container_dtor(pointer p)
{
  yaooc_rbtree_index_array_container_pointer this=p;
	yaooc_rbtree_index_array_container_rbdestroy_private(this,yaooc_rbtree_index_array_container_rbfirst(this));
	FREE(this->root_);
}

void yaooc_rbtree_index_array_container_copy_ctor(pointer p,const_pointer s)
{
  call_constructor(p,yaooc_rbtree_index_array_container_ctor_ti,TYPE_INFO(s));
  yaooc_rbtree_index_array_container_assign(p,s);
}

yaooc_rbnode_t* yaooc_rbtree_clone_node(yaooc_rbnode_t* node)
{
	yaooc_rbnode_t* dup=yaooc_rbnode_rbnil;
	if(node != yaooc_rbnode_rbnil) {
		dup=yaooc_rbnode_new();
		dup->index_ = node->index_;
		dup->left_=yaooc_rbtree_clone_node(node->left_);
		if(dup->left_ != yaooc_rbnode_rbnil)
			dup->left_->parent_=dup;
		dup->right_=yaooc_rbtree_clone_node(node->right_);
		if(dup->right_ != yaooc_rbnode_rbnil)
			dup->right_->parent_=dup;
	}
	return dup;
}

void yaooc_rbtree_delete_node(yaooc_rbnode_t* node)
{
	if(node != yaooc_rbnode_rbnil) {
		yaooc_rbtree_delete_node(node->left_);
		yaooc_rbtree_delete_node(node->right_);
		FREE(node);
	}
}

void yaooc_rbtree_index_array_container_assign(pointer p,const_pointer s)
{
  yaooc_rbtree_index_array_container_pointer this=p;
  yaooc_rbtree_index_array_container_const_pointer src=s;
	yaooc_rbtree_index_array_container_clear(this);
//	yaooc_rbtree_index_array_container_rbdestroy_private(this,yaooc_rbtree_index_array_container_rbfirst(this));
  yaooc_array_container_assign(this,src);
	if(this->root_ != yaooc_rbnode_rbnil)
		yaooc_rbtree_delete_node(this->root_);
	this->root_=yaooc_rbtree_clone_node(src->root_);
}

static yaooc_rbnode_t __yaooc_rbnode_rbnil = { .left_ = &__yaooc_rbnode_rbnil, .right_=&__yaooc_rbnode_rbnil, .parent_=&__yaooc_rbnode_rbnil };
yaooc_rbnode_t* yaooc_rbnode_rbnil = &__yaooc_rbnode_rbnil;

/* Constructors implementation for yaooc_rbtree_index_array_container */
void yaooc_rbtree_index_array_container_ctor_ti(pointer p,va_list args)
{
  yaooc_rbtree_index_array_container_pointer this=p;
  call_constructor(p,yaooc_array_container_ctor_ti,va_arg(args,const type_info_t*));
	this->root_=yaooc_rbnode_new();
	/*
	 * We use a self-referencing sentinel node called nil to simplify the
	 * code by avoiding the need to check for NULL pointers.
	 *
	this->nil_.left_ = this->nil_.right_ = this->nil_.parent_ = &this->nil_;
	this->nil_.color_ = black;
	this->nil_.index_ = 0;

	this->nil_=&nil;*/
	/*
	 * Similarly, the fake root node keeps us from having to worry
	 * about splitting the root.

	this->root_=MALLOC(sizeof(yaooc_rbnode_t));
	this->root_->left_ = this->root_->right_ = this->root_->parent_ = yaooc_rbnode_rbnil;
	this->root_->color_ = black;
	this->root_->index_ = 0;*/
}


/* Private methods implementation for yaooc_rbtree_index_array_container */
/*
 * Perform a left rotation starting at node.
 */
static void yaooc_rbtree_index_array_container_rotate_left(yaooc_rbnode_t* node)
{
	yaooc_rbnode_t *child;

	child = node->right_;
	node->right_ = child->left_;

	if (child->left_ != yaooc_rbnode_rbnil)
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
static void yaooc_rbtree_index_array_container_rotate_right(yaooc_rbnode_t* node)
{
	yaooc_rbnode_t *child;

	child = node->left_;
	node->left_ = child->right_;

	if (child->right_ != yaooc_rbnode_rbnil)
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

	if ((ret = node->right_) != yaooc_rbnode_rbnil) {
		while (ret->left_ != yaooc_rbnode_rbnil)
		ret = ret->left_;
	} else {
		/* No right child, move up until we find it or hit the root */
		for (ret = node->parent_; node == ret->right_; ret = ret->parent_)
			node = ret;
		if (ret == yaooc_rbtree_index_array_container_rbroot(this))
		ret = yaooc_rbnode_rbnil;
	}
	return ret;
}

static void yaooc_rbtree_index_array_container_rbdestroy_private(pointer p,yaooc_rbnode_t* node)
{
  yaooc_rbtree_index_array_container_pointer this=p;
	if (node != yaooc_rbnode_rbnil) {
		yaooc_rbtree_index_array_container_rbdestroy_private(this, node->left_);
		yaooc_rbtree_index_array_container_rbdestroy_private(this, node->right_);
		FREE(node);
	}
}

static void yaooc_rbtree_index_array_container_rbrepair(yaooc_rbnode_t* node)
{
	yaooc_rbnode_t *sibling;

	while (node->color_ == yaooc_rbblack) {
		if (node == node->parent_->left_) {
			sibling = node->parent_->right_;
			if (sibling->color_ == yaooc_rbred) {
				sibling->color_ = yaooc_rbblack;
				node->parent_->color_ = yaooc_rbred;
				yaooc_rbtree_index_array_container_rotate_left( node->parent_);
				sibling = node->parent_->right_;
			}
			if (sibling->right_->color_ == yaooc_rbblack && sibling->left_->color_ == yaooc_rbblack) {
				sibling->color_ = yaooc_rbred;
				node = node->parent_;
			} else {
				if (sibling->right_->color_ == yaooc_rbblack) {
					sibling->left_->color_ = yaooc_rbblack;
					sibling->color_ = yaooc_rbred;
					yaooc_rbtree_index_array_container_rotate_right( sibling);
					sibling = node->parent_->right_;
				}
				sibling->color_ = node->parent_->color_;
				node->parent_->color_ = yaooc_rbblack;
				sibling->right_->color_ = yaooc_rbblack;
				yaooc_rbtree_index_array_container_rotate_left(node->parent_);
				break;
			}
		} else { /* if (node == node->parent_->right_) */
			sibling = node->parent_->left_;
			if (sibling->color_ == yaooc_rbred) {
				sibling->color_ = yaooc_rbblack;
				node->parent_->color_ = yaooc_rbred;
				yaooc_rbtree_index_array_container_rotate_right(node->parent_);
				sibling = node->parent_->left_;
			}
			if (sibling->right_->color_ == yaooc_rbblack && sibling->left_->color_ == yaooc_rbblack) {
				sibling->color_ = yaooc_rbred;
				node = node->parent_;
			} else {
				if (sibling->left_->color_ == yaooc_rbblack) {
					sibling->right_->color_ = yaooc_rbblack;
					sibling->color_ = yaooc_rbred;
					yaooc_rbtree_index_array_container_rotate_left(sibling);
					sibling = node->parent_->left_;
				}
				sibling->color_ = node->parent_->color_;
				node->parent_->color_ = yaooc_rbblack;
				sibling->left_->color_ = yaooc_rbblack;
				yaooc_rbtree_index_array_container_rotate_right(node->parent_);
				break;
			}
		}
	}
}

yaooc_rbnode_t* yaooc_rbnode_new()
{
	yaooc_rbnode_t* node=MALLOC(sizeof(yaooc_rbnode_t));
	node->left_=node->right_=node->parent_=yaooc_rbnode_rbnil;
	node->index_=0; node->color_=yaooc_rbblack;
	return node;
}

void yaooc_rbtree_index_array_container_insert_index(pointer p,yaooc_rbnode_t** parent,unsigned int index);
/* Protected implementation for yaooc_rbtree_index_array_container */
iterator yaooc_rbtree_index_array_container_insert(pointer p,const_iterator pos,const_pointer value)
{
	yaooc_rbtree_index_array_container_pointer this=p;
/*	yaooc_rbnode_t *node = yaooc_rbtree_index_array_container_rbfirst(this);
	yaooc_rbnode_t *parent = yaooc_rbtree_index_array_container_rbroot(this);*/

	yaooc_rbtree_index_array_container_find_result_t fr = yaooc_rbtree_index_array_container_rbfind(this,value);
	if(fr.found_)
		return AT(p,(*fr.node_)->index_);
	// Not found, insert value into array
	iterator ppos=yaooc_array_container_insert(p,pos,value);
	yaooc_rbtree_index_array_container_insert_index(p,fr.node_,INDEX(p,ppos));
	return ppos;
}

void yaooc_rbtree_index_array_container_insert_index(pointer p,yaooc_rbnode_t** parent,unsigned int index)
{
	yaooc_rbtree_index_array_container_pointer this=p;
	// Renumber indexes
	unsigned int n_gt_index=SIZE(this)-index-1;
	if(n_gt_index > 0)
		yaooc_rbtree_index_array_container_rbapply(this,yaooc_rbnode_increment_index,index,1,&n_gt_index);
	yaooc_rbnode_t* node;

	rich_compare rich_cmp=get_rich_compare(TYPE_INFO(p));
	if (*parent == yaooc_rbtree_index_array_container_rbroot(this) ||
						(rich_cmp(AT(this,index),AT(this,(*parent)->index_)) < 0)) {
		node = (*parent)->left_ = yaooc_rbnode_new();
	} else {
		node = (*parent)->right_ = yaooc_rbnode_new();
	}
	node->index_ = index;
	node->parent_ = *parent;
	node->color_ = yaooc_rbred;

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
	while (node->parent_->color_ == yaooc_rbred) {
		yaooc_rbnode_t *uncle;
		if (node->parent_ == node->parent_->parent_->left_) {
			uncle = node->parent_->parent_->right_;
			if (uncle->color_ == yaooc_rbred) {
				node->parent_->color_ = yaooc_rbblack;
				uncle->color_ = yaooc_rbblack;
				node->parent_->parent_->color_ = yaooc_rbred;
				node = node->parent_->parent_;
			} else /* if (uncle->color_ == black) */ {
				if (node == node->parent_->right_) {
					node = node->parent_;
					yaooc_rbtree_index_array_container_rotate_left(node);
				}
				node->parent_->color_ = yaooc_rbblack;
				node->parent_->parent_->color_ = yaooc_rbred;
				yaooc_rbtree_index_array_container_rotate_right(node->parent_->parent_);
			}
		} else { /* if (node->parent_ == node->parent_->parent_->right_) */
			uncle = node->parent_->parent_->left_;
			if (uncle->color_ == yaooc_rbred) {
				node->parent_->color_ = yaooc_rbblack;
				uncle->color_ = yaooc_rbblack;
				node->parent_->parent_->color_ = yaooc_rbred;
				node = node->parent_->parent_;
			} else /* if (uncle->color_ == black) */ {
				if (node == node->parent_->left_) {
					node = node->parent_;
					yaooc_rbtree_index_array_container_rotate_right(node);
				}
				node->parent_->color_ = yaooc_rbblack;
				node->parent_->parent_->color_ = yaooc_rbred;
				yaooc_rbtree_index_array_container_rotate_left(node->parent_->parent_);
			}
		}
	}
	yaooc_rbtree_index_array_container_rbfirst(this)->color_ = yaooc_rbblack;	/* first node is always black */
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
	yaooc_rbtree_index_array_container_find_result_t fr=yaooc_rbtree_index_array_container_rbfind(p,value);
  return fr.found_ ? AT(p,(*fr.node_)->index_) : END(p);
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
	yaooc_rbtree_index_array_container_find_result_t fr=yaooc_rbtree_index_array_container_rbfind(p,value);
	if(fr.found_) {
		yaooc_array_container_erase(p,AT(p,(*fr.node_)->index_));
		unsigned int index=(*fr.node_)->index_;
		unsigned int n_gt_index=SIZE(p)-index;
		yaooc_rbtree_index_array_container_rbdelete(p,*fr.node_);
		if(n_gt_index > 0)
			yaooc_rbtree_index_array_container_rbapply(this,yaooc_rbnode_decrement_index,index,1,&n_gt_index);
		ret++;
	}
  return ret;
}

iterator yaooc_rbtree_index_array_container_erase_range(pointer p,const_iterator f,const_iterator l)
{
  yaooc_rbtree_index_array_container_pointer this=p;
	yaooc_private_const_iterator last=l;
	yaooc_private_const_iterator first=f;
	for(;first!=last;first+=TYPE_SIZE(this)) {
		yaooc_rbtree_index_array_container_find_result_t fr=yaooc_rbtree_index_array_container_rbfind(p,first);
		yaooc_rbtree_index_array_container_rbdelete(p,*fr.node_);
	}
//	first=f;
	iterator ret = yaooc_array_container_erase_range(p,f,l);
	unsigned int n_gt_index=this->size_-DISTANCE(TYPE_INFO(p),this->array_,f);
	yaooc_rbtree_index_array_container_rbapply(this,yaooc_rbnode_decrement_index,DISTANCE(TYPE_INFO(p),this->array_,f),DISTANCE(TYPE_INFO(p),f,l),&n_gt_index);
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
	this->root_->left_ = this->root_->right_ = this->root_->parent_ = yaooc_rbnode_rbnil;
	this->root_->color_ = yaooc_rbblack;
	this->root_->index_ = 0;
	yaooc_array_container_clear(p);
}

int yaooc_rbtree_index_array_container_rbapply_node(yaooc_rbnode_t* node,action_func func,unsigned int index,unsigned int n,unsigned int* count)
{
//  yaooc_rbtree_index_array_container_pointer this=p;
  int ret=0;
	if(node != yaooc_rbnode_rbnil) {
		if((ret = yaooc_rbtree_index_array_container_rbapply_node(node->left_,func,index,n,count)) != 0)
			return ret;
		if((ret = func(node,index,n,count)) != 0)
			return ret;
		if((ret = yaooc_rbtree_index_array_container_rbapply_node(node->right_,func,index,n,count)) != 0)
			return ret;
	}
	return ret;
}

yaooc_rbtree_index_array_container_find_result_t
yaooc_rbtree_index_array_container_rbfind(const_pointer p,const_pointer value)
{
  yaooc_rbtree_index_array_container_const_pointer this=p;
	yaooc_rbnode_t* node=this->root_->left_;
	yaooc_rbnode_t** anode = &this->root_->left_;
	yaooc_rbnode_t** aparent=(yaooc_rbnode_t**)&this->root_;

	rich_compare rich_cmp=get_rich_compare(TYPE_INFO(p));  // lt_cmp should always be defined
	while (node != yaooc_rbnode_rbnil) {
		aparent=anode;
    int rc = rich_cmp(value,AT(this,node->index_));
    if(rc < 0) {
      node=node->left_;
      anode=&(*anode)->left_;
    } else if(rc > 0) {
      node=node->right_;
      anode=&(*anode)->right_;
    } else
      return (yaooc_rbtree_index_array_container_find_result_t){ anode, true };
	}
	return (yaooc_rbtree_index_array_container_find_result_t){ aparent, false};
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

	if (z->left_ == yaooc_rbnode_rbnil || z->right_ == yaooc_rbnode_rbnil)
		y = z;
	else
		y = yaooc_rbtree_index_array_container_rbsuccessor(this, z);
	x = (y->left_ == yaooc_rbnode_rbnil) ? y->right_ : y->left_;

	if ((x->parent_ = y->parent_) == yaooc_rbtree_index_array_container_rbroot(this)) {
		yaooc_rbtree_index_array_container_rbfirst(this) = x;
	} else {
		if (y == y->parent_->left_)
		y->parent_->left_ = x;
		else
		y->parent_->right_ = x;
	}
	if (y->color_ == yaooc_rbblack)
		yaooc_rbtree_index_array_container_rbrepair( x);
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

