#include <yaooc/matrix.h>
yaooc_matrix_exception_class_table_t yaooc_matrix_exception_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_exception_class_table,
.type_name_ = (const char*)"yaooc_matrix_exception_t",
.swap = (void(*)(pointer,pointer)) yaooc_matrix_exception_swap,
.what = (const char*(*)(const_pointer)) yaooc_matrix_exception_what,
.error_code = (int(*)(const_pointer)) yaooc_matrix_exception_error_code,
};
const type_info_t __yaooc_matrix_exception_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_matrix_exception_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=NULL,
.dtor_=NULL,
.copy_ctor_=NULL,
.assign_=NULL,
.class_table_=(const class_table_t*) &yaooc_matrix_exception_class_table,
.parent_=&__yaooc_exception_ti
};
const type_info_t* const yaooc_matrix_exception_ti=&__yaooc_matrix_exception_ti;
#include <string.h>


void yaooc_matrix_default_ctor(pointer __pthis__)
{
yaooc_matrix_pointer this=__pthis__;(void)this;
call_parent_default_ctor_static(this,yaooc_matrix);


this->data_=NULL;
this->rows_=(unsigned int)0;
this->cols_=(unsigned int)0;

}
void yaooc_matrix_dtor(pointer __pthis__)
{
yaooc_matrix_pointer this=__pthis__;(void)this;


      if(this->data_ != NULL) {
        free(this->data_[0]);
        free(this->data_);
      }
    
}
void yaooc_matrix_copy_ctor(pointer __pthis__,const_pointer __psrc__)
{
yaooc_matrix_pointer this=__pthis__;(void)this;
yaooc_matrix_const_pointer src=__psrc__;(void)src;

call_default_ctor_static(this,yaooc_matrix);


      assign_static(this,src,yaooc_matrix);
    
}
void yaooc_matrix_assign(pointer __pthis__,const_pointer __psrc__)
{
yaooc_matrix_pointer this=__pthis__;(void)this;
yaooc_matrix_const_pointer src=__psrc__;(void)src;


      yaooc_matrix_dtor(this);
      if(src->data_) {
        this->rows_=src->rows_;
        this->cols_=src->cols_;
        yaooc_matrix_allocate(this);
        memcpy(this->data_[0],src->data_[0],this->rows_*this->cols_*sizeof(double));
      } else
        this->data_=NULL;
    
}
void yaooc_matrix_ctor_rows_cols(pointer __pthis,va_list __con_args__){
yaooc_matrix_pointer this=__pthis;(void)this;
unsigned int rows = va_arg(__con_args__,unsigned int);
unsigned int cols = va_arg(__con_args__,unsigned int);
double* data = va_arg(__con_args__,double*);

call_default_ctor_static(this,yaooc_matrix);


      this->rows_=rows;
      this->cols_=cols;
      yaooc_matrix_allocate(this);
      if(data) {
        unsigned int r,c;
        for(r=0;r<this->rows_;r++)
          for(c=0;c<this->cols_;c++)
            this->data_[r][c] = *data++;
      }
    
}
void yaooc_matrix_allocate(pointer __pthis__)
{
yaooc_matrix_pointer this=__pthis__;(void)this;

      int r;
      this->data_=(double**)MALLOC(this->rows_*sizeof(double*));
      this->data_[0]=(double*)MALLOC(this->rows_*this->cols_*sizeof(double));
      for(r=1;r<this->rows_;r++) {
        this->data_[r]=this->data_[r-1]+this->cols_;
      }
    
}
void yaooc_matrix_swap(pointer __pthis__,pointer o)
{
yaooc_matrix_pointer this=__pthis__;(void)this;
#define super() yaooc_matrix_parent_class_table->swap(this,o)
#define PM(method,...) CTM((*yaooc_matrix_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_matrix_pointer other=o;
      SWAP(unsigned int,this->rows_,other->rows_);
      SWAP(unsigned int,this->cols_,other->cols_);
      SWAP(double**,this->data_,other->data_);
    
#undef PM
#undef super
}
double yaooc_matrix_at(pointer __pthis__,unsigned int r,unsigned int c)
{
yaooc_matrix_pointer this=__pthis__;(void)this;
#define super() yaooc_matrix_parent_class_table->at(this,r,c)
#define PM(method,...) CTM((*yaooc_matrix_parent_class_table),this,method,## __VA_ARGS__)


      return this->data_[r][c];
    
#undef PM
#undef super
}
void yaooc_matrix_set(pointer __pthis__,unsigned int r,unsigned int c,double v)
{
yaooc_matrix_pointer this=__pthis__;(void)this;
#define super() yaooc_matrix_parent_class_table->set(this,r,c,v)
#define PM(method,...) CTM((*yaooc_matrix_parent_class_table),this,method,## __VA_ARGS__)


      this->data_[r][c]=v;
    
#undef PM
#undef super
}
yaooc_matrix_pointer yaooc_matrix_transpose(const_pointer __pthis__)
{
yaooc_matrix_const_pointer this=__pthis__;(void)this;
#define super() yaooc_matrix_parent_class_table->transpose(this)
#define PM(method,...) CTM((*yaooc_matrix_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_matrix_pointer mat=new(yaooc_matrix);
      mat->rows_=this->cols_;
      mat->cols_=this->rows_;
      yaooc_matrix_allocate(mat);
      int r,c;
      for(r=0;r<this->rows_;r++)
        for(c=0;c<this->cols_;c++)
          mat->data_[r][c] = this->data_[c][r];
      return mat;
    
#undef PM
#undef super
}
void yaooc_matrix_transpose_(pointer __pthis__)
{
yaooc_matrix_pointer this=__pthis__;(void)this;
#define super() yaooc_matrix_parent_class_table->transpose_(this)
#define PM(method,...) CTM((*yaooc_matrix_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_matrix_t* temp = M(this,transpose);
      M(this,swap,temp);
      delete(temp);
    
#undef PM
#undef super
}
yaooc_matrix_pointer yaooc_matrix_inverse(const_pointer __pthis__)
{
yaooc_matrix_const_pointer this=__pthis__;(void)this;
#define super() yaooc_matrix_parent_class_table->inverse(this)
#define PM(method,...) CTM((*yaooc_matrix_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_matrix_pointer mat=new_copy_static(yaooc_matrix,this);
      M(mat,inverse_);
      return mat;
    
#undef PM
#undef super
}
void yaooc_matrix_inverse_(pointer __pthis__)
{
yaooc_matrix_pointer this=__pthis__;(void)this;
#define super() yaooc_matrix_parent_class_table->inverse_(this)
#define PM(method,...) CTM((*yaooc_matrix_parent_class_table),this,method,## __VA_ARGS__)


      if(this->rows_ != this->cols_)
        THROW(new_ctor(yaooc_matrix_exception,yaooc_matrix_exception_ctor_v,
              33,"Can't calculate inverse for non square matrix"));
      yaooc_matrix_pointer identity = yaooc_matrix_identity(this->rows_);
      unsigned int pivot,r,c;
      for(pivot=0;pivot<this->rows_;pivot++) {
        for(r=0;r<this->rows_;r++) {
          if(pivot != r) {
            double multiplier=-this->data_[r][pivot]/this->data_[pivot][pivot];
            for(c=0;c<this->cols_;c++) {
              this->data_[r][c]+=multiplier*this->data_[pivot][c];
              identity->data_[r][c]+=multiplier*identity->data_[pivot][c];
            }
          }
        }
      }

      for(pivot=0;pivot<this->rows_;pivot++) {
        for(c=0;c<this->cols_;c++) {
          identity->data_[pivot][c] /= this->data_[pivot][pivot];
        }
        this->data_[pivot][pivot] /= this->data_[pivot][pivot];
      }
      M(this,swap,identity);
      delete(identity);

    
#undef PM
#undef super
}
yaooc_matrix_pointer yaooc_matrix_times(const_pointer __pthis__,yaooc_matrix_const_pointer mat)
{
yaooc_matrix_const_pointer this=__pthis__;(void)this;
#define super() yaooc_matrix_parent_class_table->times(this,mat)
#define PM(method,...) CTM((*yaooc_matrix_parent_class_table),this,method,## __VA_ARGS__)


      if(this->cols_ != mat->rows_)
        THROW(new_ctor(yaooc_matrix_exception,yaooc_matrix_exception_ctor_v,33,
              "Cols of first matrix not equals rows of second matrix for matrix multiplication"));
      yaooc_matrix_pointer ret = new_ctor(yaooc_matrix,yaooc_matrix_ctor_rows_cols,this->rows_,mat->cols_,NULL);
      unsigned int r,r2,c,c2;
      for(r=0;r<ret->rows_;r++) {
        for(c=0;c<ret->cols_;c++) {
          double sum=0;
          for(r2=0,c2=0;c2<this->cols_;r2++,c2++)
            sum += this->data_[r][c2]*mat->data_[r2][c];
          ret->data_[r][c]=sum;
        }
      }
      return ret;
    
#undef PM
#undef super
}
yaooc_matrix_pointer yaooc_matrix_plus(const_pointer __pthis__,yaooc_matrix_const_pointer mat)
{
yaooc_matrix_const_pointer this=__pthis__;(void)this;
#define super() yaooc_matrix_parent_class_table->plus(this,mat)
#define PM(method,...) CTM((*yaooc_matrix_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_matrix_pointer ret=new_copy_static(yaooc_matrix,this);
      M(ret,plus_,mat);
      return ret;
    
#undef PM
#undef super
}
void yaooc_matrix_plus_(pointer __pthis__,yaooc_matrix_const_pointer mat)
{
yaooc_matrix_pointer this=__pthis__;(void)this;
#define super() yaooc_matrix_parent_class_table->plus_(this,mat)
#define PM(method,...) CTM((*yaooc_matrix_parent_class_table),this,method,## __VA_ARGS__)


      if(this->rows_ != mat->rows_ || this->cols_ != mat->cols_)
        THROW(new_ctor(yaooc_matrix_exception,yaooc_matrix_exception_ctor_v,33,"Rows/cols not equal for matrix addition"));
      int i,j;
      for(i=0;i<this->rows_;i++)
        for(j=0;j<this->cols_;j++)
          this->data_[i][j] += mat->data_[i][j];
    
#undef PM
#undef super
}
yaooc_matrix_pointer yaooc_matrix_minus(const_pointer __pthis__,yaooc_matrix_const_pointer mat)
{
yaooc_matrix_const_pointer this=__pthis__;(void)this;
#define super() yaooc_matrix_parent_class_table->minus(this,mat)
#define PM(method,...) CTM((*yaooc_matrix_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_matrix_pointer ret=new_copy_static(yaooc_matrix,this);
      M(ret,minus_,mat);
      return ret;
    
#undef PM
#undef super
}
void yaooc_matrix_minus_(pointer __pthis__,yaooc_matrix_const_pointer mat)
{
yaooc_matrix_pointer this=__pthis__;(void)this;
#define super() yaooc_matrix_parent_class_table->minus_(this,mat)
#define PM(method,...) CTM((*yaooc_matrix_parent_class_table),this,method,## __VA_ARGS__)


      if(this->rows_ != mat->rows_ || this->cols_ != mat->cols_)
        THROW(new_ctor(yaooc_matrix_exception,yaooc_matrix_exception_ctor_v,33,"Rows/cols not equal for matrix subtraction"));
      int i,j;
      for(i=0;i<this->rows_;i++)
        for(j=0;j<this->cols_;j++)
          this->data_[i][j] -= mat->data_[i][j];
    
#undef PM
#undef super
}
double yaooc_matrix_determinant(const_pointer __pthis__)
{
yaooc_matrix_const_pointer this=__pthis__;(void)this;
#define super() yaooc_matrix_parent_class_table->determinant(this)
#define PM(method,...) CTM((*yaooc_matrix_parent_class_table),this,method,## __VA_ARGS__)


      double ret=0.0;
      if(this->rows_ == this->cols_) {
        if(this->rows_==2) {
          ret=this->data_[0][0]*this->data_[1][1] - this->data_[1][0]*this->data_[0][1];
        } else {
          int sign=1;
          unsigned int c;
          ret=0;
          for(c=0;c<this->cols_;c++) {
            yaooc_matrix_t* sub=M(this,sub_matrix,0,c);
            ret = ret + sign*(this->data_[0][c])*M(sub,determinant);
            delete(sub);
            sign=-sign;
          }
        }
      } else {
        THROW(new_ctor(yaooc_matrix_exception,yaooc_matrix_exception_ctor_v,33,"Cannot computer determinant of non squae matrix"));
      }
      return ret;
    
#undef PM
#undef super
}
yaooc_matrix_pointer yaooc_matrix_sub_matrix(const_pointer __pthis__,unsigned int row,unsigned int col)
{
yaooc_matrix_const_pointer this=__pthis__;(void)this;
#define super() yaooc_matrix_parent_class_table->sub_matrix(this,row,col)
#define PM(method,...) CTM((*yaooc_matrix_parent_class_table),this,method,## __VA_ARGS__)


      yaooc_matrix_t* ret=new_ctor(yaooc_matrix,yaooc_matrix_ctor_rows_cols,this->rows_-1,this->cols_-1);
      unsigned int r,c,ir,ic;
      ir=0;
      for(r=0;r<this->rows_;r++) {
        if(r!= row) {
          ic=0;
          for(c=0;c<this->cols_;c++) {
            if(c != col)
              ret->data_[ir][ic++]=this->data_[r][c];
          }
          ir++;
        }
      }
      return ret;
    
#undef PM
#undef super
}
yaooc_matrix_class_table_t yaooc_matrix_class_table ={
.parent_class_table_ = (const class_table_t*)&yaooc_object_class_table,
.type_name_ = (const char*)"yaooc_matrix_t",
.swap = (void(*)(pointer,pointer)) yaooc_matrix_swap,
.at = (double(*)(pointer,unsigned int,unsigned int)) yaooc_matrix_at,
.set = (void(*)(pointer,unsigned int,unsigned int,double)) yaooc_matrix_set,
.transpose = (yaooc_matrix_pointer(*)(const_pointer)) yaooc_matrix_transpose,
.transpose_ = (void(*)(pointer)) yaooc_matrix_transpose_,
.inverse = (yaooc_matrix_pointer(*)(const_pointer)) yaooc_matrix_inverse,
.inverse_ = (void(*)(pointer)) yaooc_matrix_inverse_,
.times = (yaooc_matrix_pointer(*)(const_pointer,yaooc_matrix_const_pointer)) yaooc_matrix_times,
.plus = (yaooc_matrix_pointer(*)(const_pointer,yaooc_matrix_const_pointer)) yaooc_matrix_plus,
.plus_ = (void(*)(pointer,yaooc_matrix_const_pointer)) yaooc_matrix_plus_,
.minus = (yaooc_matrix_pointer(*)(const_pointer,yaooc_matrix_const_pointer)) yaooc_matrix_minus,
.minus_ = (void(*)(pointer,yaooc_matrix_const_pointer)) yaooc_matrix_minus_,
.determinant = (double(*)(const_pointer)) yaooc_matrix_determinant,
.sub_matrix = (yaooc_matrix_pointer(*)(const_pointer,unsigned int,unsigned int)) yaooc_matrix_sub_matrix,
};
const type_info_t __yaooc_matrix_ti = {
.min_flag_=0,
.pod_flag_=0,
.type_size_=sizeof(yaooc_matrix_t),
.rich_compare_=NULL,
.to_stream_=NULL,
.from_stream_=NULL,
.default_ctor_=yaooc_matrix_default_ctor,
.dtor_=yaooc_matrix_dtor,
.copy_ctor_=yaooc_matrix_copy_ctor,
.assign_=yaooc_matrix_assign,
.class_table_=(const class_table_t*) &yaooc_matrix_class_table,
.parent_=&__yaooc_object_ti
};
const type_info_t* const yaooc_matrix_ti=&__yaooc_matrix_ti;
yaooc_matrix_pointer yaooc_matrix_identity(unsigned int rows)
{
  yaooc_matrix_pointer mat=new(yaooc_matrix);
  mat->rows_=mat->cols_=rows;
  yaooc_matrix_allocate(mat);
  memset(mat->data_[0],0,rows*rows*sizeof(double));
  unsigned int r;
  for(r=0;r<rows;r++)
    mat->data_[r][r] = 1.0;
  return mat;
}


