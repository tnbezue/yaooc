/* Begin YAOOCPP output */

#include <yaooc/matrix.h>
#include <string.h>
#include <stdio.h>
/* Private variables implementation for yaooc_matrix_exception */

/* Private methods prototypes for yaooc_matrix_exception */

/* Type Info implemmentation for yaooc_matrix_exception */
/* Constructors implementation for yaooc_matrix_exception */

/* Private methods implementation for yaooc_matrix_exception */

/* Protected implementation for yaooc_matrix_exception */

/* Table implementation for yaooc_matrix_exception */

/* Class table definition for yaooc_matrix_exception */
yaooc_matrix_exception_class_table_t yaooc_matrix_exception_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_exception_class_table,
  .type_name_ = (const char*) "yaooc_matrix_exception_t",
  .swap = (void(*)(pointer, pointer)) yaooc_matrix_exception_swap,
  .what = (const char*(*)(const_pointer)) yaooc_matrix_exception_what,
};

/* Type info structure for yaooc_matrix_exception */
DEFINE_TYPE_INFO(yaooc_matrix_exception,N,N,N,N,N,N,N,Y,yaooc_exception);

/* Private variables implementation for yaooc_matrix */

/* Private methods prototypes for yaooc_matrix */

/* Type Info implemmentation for yaooc_matrix */
void yaooc_matrix_default_ctor(pointer p)
{
  yaooc_matrix_pointer this=p;
  this->rows_ = 0;
  this->cols_ = 0;
  this->data_ = NULL;
}

void yaooc_matrix_dtor(pointer p)
{
  yaooc_matrix_pointer this=p;
  if(this->data_) {
     FREE(this->data_[0]);
     FREE(this->data_);
  }
  this->data_ = NULL;
}

void yaooc_matrix_copy_ctor(pointer p,const_pointer s)
{
  yaooc_matrix_default_ctor(p);
  yaooc_matrix_assign(p,s);
}

void yaooc_matrix_assign(pointer p,const_pointer s)
{
  yaooc_matrix_pointer this=p;
  yaooc_matrix_const_pointer src=s;
  yaooc_matrix_dtor(this);
  call_constructor(this,yaooc_matrix_ctor_rows_cols,src->rows_,src->cols_);
  memcpy(this->data_[0],src->data_[0],this->rows_*this->cols_*sizeof(double));
}

/* Constructors implementation for yaooc_matrix */
void yaooc_matrix_ctor_rows_cols(pointer p,va_list args)
{
  yaooc_matrix_pointer this=p;
  this->rows_ = va_arg(args, unsigned int);
  this->cols_ = va_arg(args, unsigned int);
  this->data_ = (double**)malloc(this->rows_*sizeof(double*));
  this->data_[0]=(double*)malloc(this->rows_*this->cols_*sizeof(double));
  unsigned int j;
  for(j=1;j<this->rows_;j++)
    this->data_[j]=this->data_[0]+j*this->cols_;
}


/* Private methods implementation for yaooc_matrix */

/* Protected implementation for yaooc_matrix */

/* Table implementation for yaooc_matrix */
void yaooc_matrix_swap(pointer p,pointer p2)
{
  yaooc_matrix_pointer this=p;
  yaooc_matrix_pointer other=p2;
  SWAP(unsigned int,this->rows_,other->rows_);
  SWAP(unsigned int,this->cols_,other->cols_);
  SWAP(double**,this->data_,other->data_);
}

unsigned int yaooc_matrix_rows(const_pointer p)
{
  return ((yaooc_matrix_const_pointer)p)->rows_;
}

unsigned int yaooc_matrix_cols(const_pointer p)
{
  return ((yaooc_matrix_const_pointer)p)->cols_;
}

double yaooc_matrix_at(pointer p,unsigned int row,unsigned int col)
{
  yaooc_matrix_pointer this=p;
  return this->data_[row][col];
}

void yaooc_matrix_set(pointer p,unsigned int row,unsigned int col,double value)
{
  yaooc_matrix_pointer this=p;
  this->data_[row][col]=value;
}

yaooc_matrix_pointer yaooc_matrix_transpose(const_pointer p)
{
  yaooc_matrix_const_pointer this=p;
  yaooc_matrix_t* ret = new_ctor(yaooc_matrix,yaooc_matrix_ctor_rows_cols,this->cols_,this->rows_);
  unsigned int r,c;
  for(r=0;r<ret->rows_;r++)
    for(c=0;c<ret->cols_;c++)
      ret->data_[r][c]=this->data_[c][r];
  return ret;
}

void yaooc_matrix_transpose_(pointer p)
{
  yaooc_matrix_pointer this=p;
  yaooc_matrix_t* temp = M(this,transpose);
  M(this,swap,temp);
  delete(temp);
}

yaooc_matrix_pointer yaooc_matrix_inverse(const_pointer p)
{
  yaooc_matrix_pointer ret=new_copy_static(yaooc_matrix,p);
  M(ret,inverse_);
  return ret;
}

void yaooc_matrix_inverse_(pointer p)
{
  yaooc_matrix_pointer this=p;
  yaooc_matrix_pointer identity = yaooc_matrix_yaooc_matrix_identity(this->rows_);
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
}

yaooc_matrix_t* yaooc_matrix_times(const_pointer p,const_pointer o)
{
  yaooc_matrix_const_pointer this=p;
  yaooc_matrix_const_pointer other=o;
  yaooc_matrix_t* ret=NULL;
  if(this->cols_ == other->rows_) {
    ret=new_ctor(yaooc_matrix,yaooc_matrix_ctor_rows_cols,this->rows_,other->cols_);
    unsigned int r,r2,c,c2;
    for(r=0;r<ret->rows_;r++) {
      for(c=0;c<ret->cols_;c++) {
        double sum=0;
        for(r2=0,c2=0;c2<this->cols_;r2++,c2++)
          sum += this->data_[r][c2]*other->data_[r2][c];
        ret->data_[r][c]=sum;
      }
    }
  } else {
    THROW(new_ctor(yaooc_matrix_exception,yaooc_matrix_exception_ctor_v,"Columns and rows mismatch in matrix multiply"));
  }
  return ret;
}

yaooc_matrix_t* yaooc_matrix_plus(const_pointer p,const_pointer o)
{
  yaooc_matrix_t* ret=new_copy_static(yaooc_matrix,p);
  M(ret,plus_,o);
  return ret;
}

void yaooc_matrix_plus_(pointer p,const_pointer o)
{
  yaooc_matrix_const_pointer this=p;
  yaooc_matrix_const_pointer other=o;
  if(this->rows_==other->rows_ && this->cols_==other->cols_) {
    unsigned int r,c;
    for(r=0;r<this->rows_;r++) {
      for(c=0;c<this->cols_;c++) {
        this->data_[r][c]+=other->data_[r][c];
      }
    }
  } else
    THROW(new_ctor(yaooc_matrix_exception,yaooc_matrix_exception_ctor_v,"Columns and rows mismatch in matrix addition"));
}

yaooc_matrix_t* yaooc_matrix_minus(const_pointer p,const_pointer o)
{
  yaooc_matrix_t* ret=new_copy_static(yaooc_matrix,p);
  M(ret,minus_,o);
  return ret;
}

void yaooc_matrix_minus_(pointer p,const_pointer o)
{
  yaooc_matrix_const_pointer this=p;
  yaooc_matrix_const_pointer other=o;
  if(this->rows_==other->rows_ && this->cols_==other->cols_) {
    unsigned int r,c;
    for(r=0;r<this->rows_;r++) {
      for(c=0;c<this->cols_;c++) {
        this->data_[r][c]-=other->data_[r][c];
      }
    }
  } else
    THROW(new_ctor(yaooc_matrix_exception,yaooc_matrix_exception_ctor_v,"Columns and rows mismatch in matrix subtraction"));
}

double yaooc_matrix_determinant(const_pointer p)
{
  yaooc_matrix_const_pointer this=p;
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
    THROW(new_ctor(yaooc_matrix_exception,yaooc_matrix_exception_ctor_v,"Cannot computer determinant of non squae matrix"));
  }
  return ret;
}

yaooc_matrix_t* yaooc_matrix_sub_matrix(const_pointer p,unsigned int row,unsigned int col)
{
  yaooc_matrix_const_pointer this=p;
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
}

/* Class table definition for yaooc_matrix */
yaooc_matrix_class_table_t yaooc_matrix_class_table =
{
  .parent_class_table_ = (const class_table_t*) &yaooc_object_class_table,
  .type_name_ = (const char*) "yaooc_matrix_t",
  .swap = (void(*)(pointer, pointer)) yaooc_matrix_swap,
  .rows = (unsigned int(*)(const_pointer)) yaooc_matrix_rows,
  .cols = (unsigned int(*)(const_pointer)) yaooc_matrix_cols,
  .at = (double(*)(pointer, unsigned int, unsigned int)) yaooc_matrix_at,
  .set = (void(*)(pointer, unsigned int, unsigned int, double)) yaooc_matrix_set,
  .transpose = (yaooc_matrix_pointer(*)(const_pointer)) yaooc_matrix_transpose,
  .transpose_ = (void(*)(pointer)) yaooc_matrix_transpose_,
  .inverse = (yaooc_matrix_pointer(*)(const_pointer)) yaooc_matrix_inverse,
  .inverse_ = (void(*)(pointer)) yaooc_matrix_inverse_,
  .times = (yaooc_matrix_t*(*)(const_pointer, const_pointer)) yaooc_matrix_times,
  .plus = (yaooc_matrix_t*(*)(const_pointer, const_pointer)) yaooc_matrix_plus,
  .plus_ = (void(*)(pointer, const_pointer)) yaooc_matrix_plus_,
  .minus = (yaooc_matrix_t*(*)(const_pointer, const_pointer)) yaooc_matrix_minus,
  .minus_ = (void(*)(pointer, const_pointer)) yaooc_matrix_minus_,
  .determinant = (double(*)(const_pointer)) yaooc_matrix_determinant,
  .sub_matrix = (yaooc_matrix_t*(*)(const_pointer,unsigned int,unsigned int)) yaooc_matrix_sub_matrix,
};

/* Type info structure for yaooc_matrix */
DEFINE_TYPE_INFO(yaooc_matrix,Y,Y,Y,Y,N,N,N,Y,yaooc_object);

/* End YAOOCPP output */

yaooc_matrix_pointer yaooc_matrix_yaooc_matrix_identity(unsigned int rows)
{
  yaooc_matrix_pointer this=new_ctor(yaooc_matrix,yaooc_matrix_ctor_rows_cols,rows,rows);
  memset(this->data_[0],0,this->rows_*this->cols_*sizeof(double));
  unsigned int i;
  for(i=0;i<rows;i++)
    this->data_[i][i]=1.0;
  return this;
}
