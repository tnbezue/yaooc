# Yet Another Object Oriented C (yaooc)

As the name suggests, YAOOC is another framework to make C a bit more like C++ -- new, delete, string class, vector, map, iterators, etc.

## Examples

    /* Plain old data */
    char* string=new_array(char,128);
    strcpy(string,"Testing");
    /* and any other string functions (strcat, strdup, etc) */
    delete(string);

    /* Containers */
    VECTOR(long); /* Vector of longs */
    long_vector lv=new(long_vector);
    long i;
    for(i=0;i<100;i++)
      M(lv,push_back_v,i)
    long_vector_const_iterator ilv; /* const iterator for long vector */
    for(ilv=M(lv,cbegin);ilv!=M(lv,cend);ilv++)
      printf("%ld ",*ilv);
    delete(lv);

    /* Custom class */
    class_(custom) {
      int x;
      double d;
      char* string;
    };
    MAP(yaooc_string,custom); /* Can be used in container */
    yaooc_string_custom_map_pointer mymap=new(yaooc_string_custom_map);
    M(mymap,insert,str,new(custom));
    ...
    yaooc_string_custom_map_const_iterator i;
    CFOR_EACH(i,mymap) { /* same as for (i=M(mymap,cbegin);i!=M(mymap,cend);i++) */
      printf("%s %d %lf %s\n",M(i->first,c_str),i->second.x,i->second.y,i->second.string);
    }
    delete(mymap);

## Goals

* Custom classes
* new/delete for POD and custom classes
* Multiple constructors
* Inheritance
* Polymorphism
* Containers (string, vector, map, etc)
* Exceptions
