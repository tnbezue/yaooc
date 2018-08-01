#ifndef __SHAPE_INCLUDED__
#define __SHAPE_INCLUDED__

/*
  Shape is base class
*/
yaooc_class_table(shape)
{
  void (*virtual_dtor)(pointer);
  void (*virtual_copy_ctor)(pointer,const_pointer);
  void (*virtual_assign)(pointer,const_pointer);
  bool (*virtual_less_than_compare)(const_pointer,const_pointer);
  double (*area)(const_pointer);
};

yaooc_class_instance(shape)
{
};

yaooc_class(shape);

void shape_default_ctor(pointer p)
{
  if(optr)
    optr+=sprintf(optr,"SDC:");
  /* For this case, does nothing */
}

void shape_dtor(pointer p)
{
  if(optr)
    optr+=sprintf(optr,"SVD:");
  M(((shape_pointer)p),virtual_dtor);
}

void shape_copy_ctor(pointer d,const_pointer s)
{
  if(optr)
    optr+=sprintf(optr,"SCC:");
  M(((shape_pointer)d),virtual_copy_ctor,s);
}

void shape_assign(pointer d,const_pointer s)
{
  if(optr)
    optr+=sprintf(optr,"SA:");
  M(((shape_pointer)d),virtual_assign,s);
}

bool shape_less_than_compare(const_pointer p1,const_pointer p2)
{
  if(optr)
    optr+=sprintf(optr,"SLT:");
  return M((shape_const_pointer)p1,virtual_less_than_compare,p2);
}

/*
  Class table for shape is NULL because no items of type shape will be called.
*/

DEFINE_TYPE_INFO(shape,Y,Y,Y,Y,Y,N,N,N,NULL)
/*
  Circle is derived from shape
*/
yaooc_class_table(circle)
{
  shape_class_table_t;
  void (*set_radius)(pointer p,double v);
};

yaooc_class_instance(circle)
{
  double radius_;
};

yaooc_class(circle);

/*
  Need a default constructor for derived classes
*/
void circle_default_ctor(pointer p)
{
  circle_pointer this=p;
  this->radius_=0;
  if(optr)
    optr+=sprintf(optr,"CDC:");
}

void circle_virtual_dtor(pointer p)
{
  if(optr)
    optr+=sprintf(optr,"CVD:");
}

void circle_virtual_copy_ctor(pointer d,const_pointer s)
{
  ((circle_pointer)d)->radius_=((circle_const_pointer)s)->radius_;
  if(optr)
    optr+=sprintf(optr,"CVCC:");
}

void circle_virtual_assign(pointer d,const_pointer s)
{
  ((circle_pointer)d)->radius_=((circle_const_pointer)s)->radius_;
  if(optr)
    optr+=sprintf(optr,"CVA:");
}

double circle_area(const_pointer p)
{
  if(optr)
    optr+=sprintf(optr,"Circle Area=%lg : ",(((circle_const_pointer)p)->radius_*((circle_const_pointer)p)->radius_)*3.1415927);
  return (((circle_const_pointer)p)->radius_*((circle_const_pointer)p)->radius_)*3.1415927;
}

void circle_dtor(pointer p)
{
  if(optr)
    optr+=sprintf(optr,"CD:");
}

void circle_copy_ctor(pointer d,const_pointer s)
{
  ((circle_pointer)d)->radius_=((circle_const_pointer)s)->radius_;
  if(optr)
    optr+=sprintf(optr,"CCC:");
}

void circle_assign(pointer d,const_pointer s)
{
  ((circle_pointer)d)->radius_=((circle_const_pointer)s)->radius_;
  if(optr)
    optr+=sprintf(optr,"CA:");
}

void circle_set_radius(pointer p,double value)
{
  if(optr)
    optr+=sprintf(optr,"CSR:");
  ((circle_pointer)p)->radius_=value;
}

void circle_ctor_radius(pointer p,va_list args)
{
  if(optr)
    optr+=sprintf(optr,"CCR:");
  circle_set_radius(p,va_arg(args,double));
}

bool circle_less_than_compare(const_pointer p1,const_pointer p2)
{
  if(optr)
    optr+=sprintf(optr,"CIRLT:");
  return M((shape_const_pointer)p1,area) < M((shape_const_pointer)p2,area);
}

circle_class_table_t circle_class_table=
{
  .virtual_dtor = circle_virtual_dtor,
  .virtual_copy_ctor = circle_virtual_copy_ctor,
  .virtual_assign = circle_virtual_assign,
  .virtual_less_than_compare = circle_less_than_compare,
  .area = circle_area,
  .set_radius = circle_set_radius
};

DEFINE_TYPE_INFO(circle,Y,N,N,N,N,N,N,Y,shape)

/*
  Square is derived from shape
*/
yaooc_class_table(square)
{
  shape_class_table_t;
  void (*set_length)(pointer,double);
};

yaooc_class_instance(square)
{
  double length_;
};

yaooc_class(square);

void square_default_ctor(pointer p)
{
  if(optr)
    optr+=sprintf(optr,"SQDC:");
  ((square_pointer)p)->length_=0;
}

void square_virtual_dtor(pointer p)
{
  if(optr)
    optr+=sprintf(optr,"SQVD:");
}

void square_virtual_copy_ctor(pointer d,const_pointer s)
{
  if(optr)
    optr+=sprintf(optr,"SQVCC:");
  ((square_pointer)d)->length_=((square_const_pointer)s)->length_;
}

void square_virtual_assign(pointer d,const_pointer s)
{
  if(optr)
    optr+=sprintf(optr,"SQVA:");
  ((square_pointer)d)->length_=((square_const_pointer)s)->length_;
}

double square_area(const_pointer p)
{
  if(optr)
    optr+=sprintf(optr,"Square area=%lg : ",((square_const_pointer)p)->length_*((square_const_pointer)p)->length_);
  return ((square_const_pointer)p)->length_*((square_const_pointer)p)->length_;
}

void square_set_length(pointer p,double value)
{
  if(optr)
    optr+=sprintf(optr,"SQSL:");
  ((square_pointer)p)->length_=value;
}

void square_ctor_length(pointer p,va_list args)
{
  if(optr)
    optr+=sprintf(optr,"SQCL:");
  square_set_length(p,va_arg(args,double));
}

bool square_less_than_compare(const_pointer p1,const_pointer p2)
{
  if(optr)
    optr+=sprintf(optr,"SQLT:");
  return M((shape_const_pointer)p1,area) < M((shape_const_pointer)p2,area);
}

square_class_table_t square_class_table=
{
  .virtual_dtor = square_virtual_dtor,
  .virtual_copy_ctor = square_virtual_copy_ctor,
  .virtual_assign = square_virtual_assign,
  .virtual_less_than_compare = square_less_than_compare,
  .area = square_area,
  .set_length = square_set_length
};

DEFINE_TYPE_INFO(square,Y,N,N,N,N,N,N,Y,shape)

/*
  Rectangle is derived from square
*/
yaooc_class_table(rectangle)
{
  square_class_table_t;
  void (*set_width)(pointer,double);
};

yaooc_class_instance(rectangle)
{
  square_class_instance_t;
  double width_;
};

yaooc_class(rectangle);

void rectangle_default_ctor(pointer p)
{
  if(optr)
    optr+=sprintf(optr,"RDC:");
  ((rectangle_pointer)p)->length_=0;
  ((rectangle_pointer)p)->width_=0;
}

void rectangle_virtual_dtor(pointer p)
{
  if(optr)
    optr+=sprintf(optr,"RVD:");
}

void rectangle_virtual_copy_ctor(pointer d,const_pointer s)
{
  if(optr)
    optr+=sprintf(optr,"RVCC:");
  square_virtual_copy_ctor(d,s);
  ((rectangle_pointer)d)->width_=((rectangle_const_pointer)s)->width_;
}

void rectangle_virtual_assign(pointer d,const_pointer s)
{
  if(optr)
    optr+=sprintf(optr,"RVA:");
  square_virtual_assign(d,s);
  ((rectangle_pointer)d)->width_=((rectangle_const_pointer)s)->width_;
}

double rectangle_area(const_pointer p)
{
  if(optr)
    optr+=sprintf(optr,"Rectangle Area=%lg : ",((rectangle_const_pointer)p)->length_*((rectangle_const_pointer)p)->width_);
  return ((rectangle_const_pointer)p)->length_*((rectangle_const_pointer)p)->width_;
}

void rectangle_set_width(pointer p,double value)
{
  if(optr)
    optr+=sprintf(optr,"RSW:");
  ((rectangle_pointer)p)->width_=value;
}

void rectangle_ctor_length_width(pointer p,va_list args)
{
  if(optr)
    optr+=sprintf(optr,"RCLW:");
  double length=va_arg(args,double);
  double width=va_arg(args,double);
  square_set_length(p,length);
  rectangle_set_width(p,width);
}

bool rectangle_less_than_compare(const_pointer p1,const_pointer p2)
{
  if(optr)
    optr+=sprintf(optr,"RLT:");
  return M((shape_const_pointer)p1,area) < M((shape_const_pointer)p2,area);
}

rectangle_class_table_t rectangle_class_table =
{
  .virtual_dtor = rectangle_virtual_dtor,
  .virtual_copy_ctor = rectangle_virtual_copy_ctor,
  .virtual_assign = rectangle_virtual_assign,
  .virtual_less_than_compare = rectangle_less_than_compare,
  .area = rectangle_area,
  .set_length = square_set_length,
  .set_width = rectangle_set_width
};

DEFINE_TYPE_INFO(rectangle,Y,N,N,N,N,N,N,Y,square)

#endif
