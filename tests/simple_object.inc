
/*
	A simple object used for testing
*/

/*
	optr used to output information about object creation, deletion, etc information to a string.
  If null, no output is generated.
*/

extern char* optr;

typedef struct {
	int x;
} simple_object_t;

void simple_object_default_ctor(pointer p)
{
	((simple_object_t*)p)->x=0;
	if(optr)
		optr+=sprintf(optr,"SODC ");
}

void simple_object_dtor(pointer p)
{
	if(optr)
		optr+=sprintf(optr,"SODT:%d ",((const simple_object_t*)p)->x);
}

void simple_object_assign(pointer d,const_pointer s)
{
	simple_object_t* dst=d;
	const simple_object_t* src=s;
	if(optr)
		optr+=sprintf(optr,"SOA:X:%d ",src->x);
	dst->x=src->x;
}

void simple_object_copy_ctor(pointer d,const_pointer s)
{
	simple_object_t* dst=d;
	const simple_object_t* src=s;
	if(optr)
		optr+=sprintf(optr,"SOCC:X:%d ",src->x);
	dst->x=src->x;
}

bool simple_object_less_than_compare(const_pointer v1,const_pointer v2)
{
	const simple_object_t* so1=v1;
	const simple_object_t* so2=v2;
/*	if(optr)
		optr+=sprintf(optr,"SOLC:%d:%d",so1->x,so2->x);*/
	return so1->x<so2->x;
}

DEFINE_TYPE_INFO(simple_object,Y,Y,Y,Y,Y,N,N,N,NULL);


void simple_object_ctor(pointer p,va_list args)
{
	simple_object_t* this=p;
	this->x=va_arg(args,int);
	if(optr)
		optr+=sprintf(optr,"SOCT:%d ",this->x);
}
