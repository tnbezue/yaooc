#include <yaooc/rbtree_index_array_container.h>
static bool yaooc_rbnode_is_red(const_pointer);
static const yaooc_rbnode_t* yaooc_rbnode_find_node(const_pointer,yaooc_rbtree_index_array_container_const_pointer,const_pointer);
static yaooc_rbnode_t* yaooc_rbnode_rotate(pointer,int);
static yaooc_rbnode_t* yaooc_rbnode_rotate2(pointer,int);
static void yaooc_rbnode_decrement_index(pointer,unsigned int,unsigned int,unsigned int*);
static bool yaooc_rbnode_is_red(const_pointer __pthis__)
{
yaooc_rbnode_const_pointer this=__pthis__;(void)this;
#define super() yaooc_rbnode_parent_class_table->is_red(this)
#define PM(method,...) CTM((*yaooc_rbnode_parent_class_table),this,method,## __VA_ARGS__)


      return this && this->color_==RED;
    
#undef PM
#undef super
}
static const yaooc_rbnode_t* yaooc_rbnode_find_node(const_pointer __pthis__,yaooc_rbtree_index_array_container_const_pointer rbtree,const_pointer value)
{
yaooc_rbnode_const_pointer this=__pthis__;(void)this;
#define super() yaooc_rbnode_parent_class_table->find_node(this,rbtree,value)
#define PM(method,...) CTM((*yaooc_rbnode_parent_class_table),this,method,## __VA_ARGS__)


      if(this) {

        int rc=__op_rich_compare__(value,AT(rbtree,this->index_),get_rich_compare(TYPE_INFO(rbtree)));

        if(rc == 0)
          return this;
        if(rc < 0)
          return yaooc_rbnode_find_node(this->link_[0],rbtree,value);
        else
          return yaooc_rbnode_find_node(this->link_[1],rbtree,value);
      }
      return NULL;
    
#undef PM
#undef super
}
static yaooc_rbnode_t* yaooc_rbnode_rotate(pointer __pthis__,int dir)
{
yaooc_rbnode_pointer this=__pthis__;(void)this;
#define super() yaooc_rbnode_parent_class_table->rotate(this,dir)
#define PM(method,...) CTM((*yaooc_rbnode_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_rbnode_t *result = NULL;
      if (this) {
          result = this->link_[!dir];
          this->link_[!dir] = result->link_[dir];
          result->link_[dir] = this;
          this->color_=RED;
          result->color_=BLACK;
      }
      return result;
    
#undef PM
#undef super
}
static yaooc_rbnode_t* yaooc_rbnode_rotate2(pointer __pthis__,int dir)
{
yaooc_rbnode_pointer this=__pthis__;(void)this;
#define super() yaooc_rbnode_parent_class_table->rotate2(this,dir)
#define PM(method,...) CTM((*yaooc_rbnode_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_rbnode_t *result = NULL;
      if (this) {
          this->link_[!dir] = yaooc_rbnode_rotate(this->link_[!dir], !dir);
          result = yaooc_rbnode_rotate(this, dir);
      }
      return result;
    
#undef PM
#undef super
}
static void yaooc_rbnode_decrement_index(pointer __pthis__,unsigned int index,unsigned int n,unsigned int* remaining)
{
yaooc_rbnode_pointer this=__pthis__;(void)this;
#define super() yaooc_rbnode_parent_class_table->decrement_index(this,index,n,remaining)
#define PM(method,...) CTM((*yaooc_rbnode_parent_class_table),this,method,## __VA_ARGS__)


      if(this) {
        if(this->index_ > index) {
          this->index_ -= n;
          (*remaining)--;
        }
        if(*remaining == 0)
          return;
        yaooc_rbnode_decrement_index(this->link_[0],index,n,remaining);
        if(*remaining == 0)
          return;
        yaooc_rbnode_decrement_index(this->link_[1],index,n,remaining);
      }
    
#undef PM
#undef super
}
void yaooc_rbnode_default_ctor(pointer __pthis__)
{
yaooc_rbnode_pointer this=__pthis__;(void)this;



    this->link_[0]=this->link_[1]=NULL;
    this->index_=0; this->color_=BLACK;
  
}
void yaooc_rbnode_dtor(pointer __pthis__)
{
yaooc_rbnode_pointer this=__pthis__;(void)this;


    if(this) {
      delete(this->link_[0]);
      delete(this->link_[1]);
    }
  
}
void yaooc_rbnode_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaooc_rbnode_pointer this=__pthis__;(void)this;
yaooc_rbnode_const_pointer src=__psrc__;(void)src;


call_default_ctor_static(this,yaooc_rbnode);
assign_static(this,src,yaooc_rbnode);

}
void yaooc_rbnode_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_rbnode_pointer this=__pthis__;(void)this;
yaooc_rbnode_const_pointer src=__psrc__;(void)src;



  
}
void yaooc_rbnode_ctor_index(pointer __pthis,va_list __con_args__){
yaooc_rbnode_pointer this=__pthis;(void)this;
unsigned int index = va_arg(__con_args__,unsigned int);

call_default_ctor_static(this,yaooc_rbnode);


    this->index_=index;
    this->color_=RED;
  
}
const type_info_t __yaooc_rbnode_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_rbnode_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_rbnode_default_ctor,
.dtor_=yaooc_rbnode_dtor,
.copy_ctor_=yaooc_rbnode_copy_ctor,
.assign_=yaooc_rbnode_assign,
.class_table_=NULL,
.parent_=NULL
};
const type_info_t* const yaooc_rbnode_ti=(const type_info_t* const)&__yaooc_rbnode_ti;
static void yaooc_rbtree_index_array_container_insert_node(pointer,int);
static void yaooc_rbtree_index_array_container_erase_node(pointer,int);
static void yaooc_rbtree_index_array_container_insert_node(pointer __pthis__,int idx)
{
yaooc_rbtree_index_array_container_pointer this=__pthis__;(void)this;
#define super() yaooc_rbtree_index_array_container_parent_class_table->insert_node(this,idx)
#define PM(method,...) CTM((*yaooc_rbtree_index_array_container_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_rbnode_t* node=yaooc_rbnode_create(idx);
      if (this->root_ == NULL) {
          this->root_ = node;
      } else {
          yaooc_rbnode_t head = { .link_[0]=NULL,.link_[1]=NULL, .color_=BLACK, .index_=0 };
          yaooc_rbnode_t *g, *t;
          yaooc_rbnode_t *p, *q;
          int dir = 0, last = 0;


          t = &head;
          g = p = NULL;
          q = t->link_[1] = this->root_;


          while (true) {
              if (q == NULL) {


                  p->link_[dir] = q = node;
              } else if (yaooc_rbnode_is_red(q->link_[0]) && yaooc_rbnode_is_red(q->link_[1])) {


                  q->color_=RED;
                  q->link_[0]->color_=BLACK;
                  q->link_[1]->color_=BLACK;
              }

              if (yaooc_rbnode_is_red(q) && yaooc_rbnode_is_red(p)) {


                  int dir2 = t->link_[1] == g;
                  if (q == p->link_[last]) {
                      t->link_[dir2] = yaooc_rbnode_rotate(g, !last);
                  } else {
                      t->link_[dir2] = yaooc_rbnode_rotate2(g, !last);
                  }
              }



              int rc=__op_rich_compare__(AT(this,q->index_),AT(this,node->index_),get_rich_compare(TYPE_INFO(this)));
              if(rc == 0)
                break;

              last = dir;
              dir = rc < 0;


              if (g != NULL) {
                  t = g;
              }

              g = p, p = q;
              q = q->link_[dir];
          }


          this->root_ = head.link_[1];
      }


      this->root_->color_ = BLACK;
    
#undef PM
#undef super
}
static void yaooc_rbtree_index_array_container_erase_node(pointer __pthis__,int index)
{
yaooc_rbtree_index_array_container_pointer this=__pthis__;(void)this;
#define super() yaooc_rbtree_index_array_container_parent_class_table->erase_node(this,index)
#define PM(method,...) CTM((*yaooc_rbtree_index_array_container_parent_class_table),this,method,## __VA_ARGS__)


        yaooc_rbnode_t head = { .link_[0]=NULL,.link_[1]=NULL, .color_=BLACK, .index_=0 };
        yaooc_rbnode_t *q, *p, *g;
        yaooc_rbnode_t *f = NULL;
        int dir = 1;


        q = &head;
        g = p = NULL;
        q->link_[1] = this->root_;



        while (q->link_[dir] != NULL) {
            int last = dir;


            g = p, p = q;
            q = q->link_[dir];

            int rc=__op_rich_compare__(AT(this,q->index_),AT(this,index),get_rich_compare(TYPE_INFO(this)));

            dir = rc < 0;



            if (rc == 0) {
                f = q;
            }


            if (!yaooc_rbnode_is_red(q) && !yaooc_rbnode_is_red(q->link_[dir])) {
                if (yaooc_rbnode_is_red(q->link_[!dir])) {
                    p = p->link_[last] = yaooc_rbnode_rotate(q, dir);
                } else if (!yaooc_rbnode_is_red(q->link_[!dir])) {
                    yaooc_rbnode_t *s = p->link_[!last];
                    if (s) {
                        if (!yaooc_rbnode_is_red(s->link_[!last]) && !yaooc_rbnode_is_red(s->link_[last])) {


                            p->color_ = BLACK;
                            s->color_ = RED;
                            q->color_ = RED;
                        } else {
                            int dir2 = g->link_[1] == p;
                            if (yaooc_rbnode_is_red(s->link_[last])) {
                                g->link_[dir2] = yaooc_rbnode_rotate2(p, last);
                            } else if (yaooc_rbnode_is_red(s->link_[!last])) {
                                g->link_[dir2] = yaooc_rbnode_rotate(p, last);
                            }


                            q->color_ = g->link_[dir2]->color_=RED;
                            g->link_[dir2]->link_[0]->color_=BLACK;
                            g->link_[dir2]->link_[1]->color_=BLACK;
                        }
                    }
                }
            }
        }


        if (f) {
            unsigned int tmp = f->index_;
            f->index_ = q->index_;
            q->index_ = tmp;

            p->link_[p->link_[1] == q] = q->link_[q->link_[0] == NULL];




            q = NULL;
        }


        this->root_ = head.link_[1];


        if (this->root_ != NULL) {
            this->root_->color_=BLACK;
        }


    
#undef PM
#undef super
}
void yaooc_rbtree_index_array_container_dtor(pointer __pthis__)
{
yaooc_rbtree_index_array_container_pointer this=__pthis__;(void)this;


      delete(this->root_);
    
}
void yaooc_rbtree_index_array_container_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaooc_rbtree_index_array_container_pointer this=__pthis__;(void)this;
yaooc_rbtree_index_array_container_const_pointer src=__psrc__;(void)src;

call_constructor(this,yaooc_rbtree_index_array_container_ctor_ti,TYPE_INFO(src));


      assign_static(this,src,yaooc_rbtree_index_array_container);
    
}
void yaooc_rbtree_index_array_container_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_rbtree_index_array_container_pointer this=__pthis__;(void)this;
yaooc_rbtree_index_array_container_const_pointer src=__psrc__;(void)src;


      yaooc_array_container_assign(this,src);
      delete(this->root_);
      this->root_=NULL;
      size_t i;
      for(i=0;i!=M(src,size);i++) {
        yaooc_rbtree_index_array_container_insert_node(this,i);
      }
    
}
void yaooc_rbtree_index_array_container_ctor_ti(pointer __pthis,va_list __con_args__){
yaooc_rbtree_index_array_container_pointer this=__pthis;(void)this;
const type_info_t* ti = va_arg(__con_args__,const type_info_t*);

call_constructor(this,yaooc_array_container_ctor_ti,ti);


      this->root_=NULL;
    
}
iterator yaooc_rbtree_index_array_container_find(pointer __pthis__,const_pointer value)
{
yaooc_rbtree_index_array_container_pointer this=__pthis__;(void)this;

      const yaooc_rbnode_t* node=yaooc_rbnode_find_node(this->root_,this,value);
      return node ? AT(this,node->index_) : END(this);
    
}
iterator yaooc_rbtree_index_array_container_insert(pointer __pthis__,const_iterator pos,const_pointer value)
{
yaooc_rbtree_index_array_container_pointer this=__pthis__;(void)this;


      if(yaooc_rbtree_index_array_container_find(this,value) == END(this)) {
        yaooc_array_container_insert(this,END(this),value);
        yaooc_rbtree_index_array_container_insert_node(this,SIZE(this)-1);
      }
      return SIZE(this) > 0 ? AT(this,this->size_-1) : AT(this,0);
    
}
iterator yaooc_rbtree_index_array_container_insertn(pointer __pthis__,const_iterator pos,size_t n,const_pointer value)
{
yaooc_rbtree_index_array_container_pointer this=__pthis__;(void)this;


      return yaooc_rbtree_index_array_container_insert(this,END(this),value);
    
}
iterator yaooc_rbtree_index_array_container_insert_range(pointer __pthis__,const_iterator pos,const_iterator f,const_iterator l)
{
yaooc_rbtree_index_array_container_pointer this=__pthis__;(void)this;

      yaooc_private_const_iterator first=f;
      yaooc_private_const_iterator last=l;
      for(;first!=last;first+=TYPE_SIZE(this)) {
        yaooc_rbtree_index_array_container_insert(this,END(this),first);
      }
      return SIZE(this) > 0 ? AT(this,this->size_-1) : AT(this,0);
    
}
iterator yaooc_rbtree_index_array_container_erase(pointer __pthis__,const_iterator pos)
{
yaooc_rbtree_index_array_container_pointer this=__pthis__;(void)this;

      return yaooc_rbtree_index_array_container_erase_range(this,pos,((yaooc_private_const_pointer)pos)+TYPE_SIZE(this));
    
}
iterator yaooc_rbtree_index_array_container_erase_range(pointer __pthis__,const_iterator f,const_iterator l)
{
yaooc_rbtree_index_array_container_pointer this=__pthis__;(void)this;

      size_t start_idx=DISTANCE(TYPE_INFO(this),BEGIN(this),f);
      size_t end_idx=DISTANCE(TYPE_INFO(this),BEGIN(this),l);
      unsigned int n = end_idx-start_idx;
      unsigned int remaining=SIZE(this)-end_idx;
      size_t idx;
      for(idx=start_idx;idx<end_idx;idx++)
        yaooc_rbtree_index_array_container_erase_node(this,idx);
      yaooc_rbnode_decrement_index(this->root_,start_idx,n,&remaining);
      return yaooc_array_container_erase_range(this,f,l);
    
}
size_t yaooc_rbtree_index_array_container_erase_value(pointer __pthis__,const_pointer value)
{
yaooc_rbtree_index_array_container_pointer this=__pthis__;(void)this;

      size_t ret=0;
      const_iterator pos=yaooc_rbtree_index_array_container_find(this,value);
      if(pos != M(this,cend)) {
        yaooc_rbtree_index_array_container_erase(this,pos);
        ret=1;
      }
      return ret;
    
}
void yaooc_rbtree_index_array_container_resize(pointer __pthis__,size_t n)
{
yaooc_rbtree_index_array_container_pointer this=__pthis__;(void)this;

      pointer temp=__new_array(TYPE_INFO(this),1);
      yaooc_rbtree_index_array_container_resize_value(this,n,temp);
      delete(temp);
    
}
void yaooc_rbtree_index_array_container_resize_value(pointer __pthis__,size_t n,const_pointer value)
{
yaooc_rbtree_index_array_container_pointer this=__pthis__;(void)this;

      if(n < M(this,size))
        yaooc_rbtree_index_array_container_erase_range(this,((yaooc_private_const_iterator)BEGIN(this))+n*TYPE_SIZE(this),END(this));
      else if(n > M(this,size))
        yaooc_rbtree_index_array_container_insert(this,END(this),value);
    
}
void yaooc_rbtree_index_array_container_clear(pointer __pthis__)
{
yaooc_rbtree_index_array_container_pointer this=__pthis__;(void)this;

      yaooc_array_container_clear(this);
      delete(this->root_);
      this->root_=NULL;
    
}
void yaooc_rbtree_index_array_container_swap(pointer __pthis__,pointer o)
{
yaooc_rbtree_index_array_container_pointer this=__pthis__;(void)this;
#define super() yaooc_rbtree_index_array_container_parent_class_table->swap(this,o)
#define PM(method,...) CTM((*yaooc_rbtree_index_array_container_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_rbtree_index_array_container_pointer other=0;
      SWAP(yaooc_rbnode_t*,this->root_,other->root_);
    
#undef PM
#undef super
}
yaooc_rbtree_index_array_container_class_table_t yaooc_rbtree_index_array_container_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_array_container_class_table,
.type_name_ = (const char*)"yaooc_rbtree_index_array_container_t",
.swap = (void(*)(pointer,pointer)) yaooc_rbtree_index_array_container_swap,
.increase_capacity = (bool(*)(pointer,size_t)) yaooc_rbtree_index_array_container_increase_capacity,
.size_needed = (size_t(*)(const_pointer,size_t)) yaooc_rbtree_index_array_container_size_needed,
.size = (size_t(*)(const_pointer)) yaooc_rbtree_index_array_container_size,
.capacity = (size_t(*)(const_pointer)) yaooc_rbtree_index_array_container_capacity,
.empty = (bool(*)(const_pointer)) yaooc_rbtree_index_array_container_empty,
.begin = (iterator(*)(pointer)) yaooc_rbtree_index_array_container_begin,
.end = (iterator(*)(pointer)) yaooc_rbtree_index_array_container_end,
.cbegin = (const_iterator(*)(const_pointer)) yaooc_rbtree_index_array_container_cbegin,
.cend = (const_iterator(*)(const_pointer)) yaooc_rbtree_index_array_container_cend,
};
const type_info_t __yaooc_rbtree_index_array_container_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_rbtree_index_array_container_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=yaooc_rbtree_index_array_container_dtor,
.copy_ctor_=yaooc_rbtree_index_array_container_copy_ctor,
.assign_=yaooc_rbtree_index_array_container_assign,
.class_table_=(const class_table_t*) &yaooc_rbtree_index_array_container_class_table,
.parent_=&__yaooc_array_container_ti
};
const type_info_t* const yaooc_rbtree_index_array_container_ti=&__yaooc_rbtree_index_array_container_ti;
