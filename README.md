# Yet Another Object Oriented C (yaooc)

As the name suggests, YAOOC is another framework to make C a bit more like C++ -- new, delete, string class, vector, map, iterators, etc.

## Examples

    /* Plain old data */
    char* string=new_array(char,128);
    strcpy(string,"Testing");
    /* and any other string functions (strcat, strchr, etc) */
    delete(string);

    /* Containers */
    VECTOR(long,long_vector);  /*  Vector of longs */
    long_vector_pointer lv=new(long_vector);
    long_t i;
    for(i=0;i<100;i++)
      M(lv,push_back,&i)
    long_vector_const_iterator ilv; /* const iterator for long vector */
    for(ilv=M(lv,begin);ilv!=M(lv,end);ilv++)
      printf("%ld ",*ilv);
    delete(lv);

    /* Custom class */
    class_(custom) {
      int x;
      double d;
      char* string;
    };
		/* Can be used in container */
    MAP(yaooc_string,custom,yaooc_string_custom_map);
    yaooc_string_custom_map_pointer mymap=new(yaooc_string_custom_map);
    custom_pointer cp=new(custom);
    ....
    M(mymap,insert,str,cp);
    ...
    yaooc_string_custom_map_const_iterator i;
    FOR_EACH(i,mymap) { /* same as for (i=M(mymap,begin);i!=M(mymap,end);i++) */
      printf("%s %d %lf %s\n",M(i->first,c_str),i->second.x,i->second.y,i->second.string);
    }
    delete(mymap);

## Goals

* Custom classes
* new/delete for POD and custom classes
* Multiple constructors
* Inheritance
* Polymorphism
* String class
* Containers (vector, map, etc)
* Exceptions
* Streams (cout, cin, cerr)
