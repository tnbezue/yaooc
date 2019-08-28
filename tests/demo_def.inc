#include <yaooc/object.h>

char* numbers[]={ "zero", "one","two","three","four","five","six","seven","eight","nine","ten",
	"eleven","twelve","thirteen","fourteen","fifteen","sixteen","seventeen","eighteen","nineteen"};
char* tens[] = { "", "", "twenty","thirty","forty","fifty","sixty","seventy","eighty","ninety"};

static char* make_string_from_number(int x)
{
	char* ptr=new_array(char,64);
	char* sign="";
	if(x < 0) {
		sign="negative";
		x=-x;
	}
	if(x < 20) {
		sprintf(ptr,"%s %s",sign,numbers[x]);
	} else if (x < 100 ){
		char* ones="";
		div_t y = div(x,10);
		if(y.rem != 0)
			ones=numbers[y.rem];
		sprintf(ptr,"%s %s %s",sign,tens[y.quot],ones);
	} else {
		sprintf(ptr,"%d",x);
	}
	return ptr;
}

yaooc_class_table(demo) {
  yaooc_object_class_table_t;
	void(*say)(demo_const_pointer);
	void(*setx)(demo_pointer,int);
};

yaooc_class_instance(demo)
{
	char* str;
	int x;
};

yaooc_class(demo);

int demo_counter=12;
void demo_default_ctor(pointer p)
{
	demo_pointer this=p;
	this->x=demo_counter++;
	this->str=make_string_from_number(this->x);
}

/*
  If only memory needs to be freed, then a destructor is not needed.
  Shown here just as an example
*/
void demo_dtor(pointer p)
{
	demo_pointer this=p;
  if(this->str)
    delete(this->str);
	this->str=NULL;
}

void demo_ctor(pointer p,va_list args)
{
	demo_pointer this=p;
	this->x=va_arg(args,int);
	this->str=make_string_from_number(this->x);
}

void demo_assign(pointer d,const_pointer s)
{
	demo_pointer dst=d;
	demo_const_pointer src=s;
  dst->x=src->x;
  if(dst->str)
    delete(dst->str);
  dst->str=src->str?yaooc_strdup(src->str):NULL;
}

void demo_copy_ctor(pointer d,const_pointer s)
{
  demo_default_ctor(d);
  demo_assign(d,s);
}

bool demo_less_than_compare(const_pointer v1,const_pointer v2)
{
	return ((demo_const_pointer)v1)->x < ((demo_const_pointer)v2)->x;
}

void demo_say(demo_const_pointer this)
{
	printf("X is: %d In words: %s\n",((demo_const_pointer)this)->x,((demo_const_pointer)this)->str);
}

void demo_setx(demo_pointer this,int val)
{
	this->x=val;
  if(this->str)
    delete(this->str);
	this->str=make_string_from_number(val);
}

void demo_swap(pointer p1,pointer p2)
{
  demo_pointer this1=p1;
  demo_pointer this2=p2;
  SWAP(char*,this1->str,this2->str)
  SWAP(int,this1->x,this2->x)
}

demo_class_table_t demo_class_table=
{
  .parent_class_table_ = (const class_table_t*)&yaooc_object_class_table,
  .type_name_ = (const char*) "demo_t",
  .swap = demo_swap,
  .say = demo_say,
  .setx = demo_setx
};

DEFINE_TYPE_INFO(demo,Y,Y,Y,Y,Y,N,N,Y,yaooc_object);

