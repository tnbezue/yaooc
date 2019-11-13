# Yet Another Object Oriented C (yaooc)

As the name suggests, YAOOC is another framework to make C a bit more like C++ -- new,
delete, string class, vector, map, iterators, etc.

It also adds features that are found in scripting languages.  For example, the string class has
methods such as split and chomp.

To get an idea of the features, review the tutorial (doc/yaooc/tutorial).  Each lesson is
only one or two pages.  The entire tutorial should take 30-45 minutes to complete.

## Example

    %include <yaooc/object.yod>
    #include <yaooc/stream.h>
    #include <stdio.h>
    #include <string.h>
    %class my_string : yaooc_object
    {
        // Constructor
        my_string() : str(NULL) { }
        // Destructor
        ~my_string() { if(this->str) free(this->str) }
        // Copy Constructor
        my_string(src) { my_string_assign(this,src); }
        // Assigment
        operator=(src) { M(this,set,src->str); }
        // Rich compare
        int operator<=>(lhs,rhs) {
          if(lhs->str == NULL) {
            if(rhs->str == NULL)
              return 0; /* both NULL, equal */
            else
              return -1; /* lhs is NULL, rhs is not.  NULL is less than not NULL */
          } else if(rhs->str == NULL)
            return 1; /* lhs is not NULL, rhs is NULL. non NULL greater than NULL */
          return strcmp(lhs->str,rhs->str); /* Both not null, compare the strings */
        }
        // To stream
        operator<<(ostrm)
        {
          M(ostrm,printf,"%s",this->str);
        }
        // From stream
        operator>>(istrm)
        {
          char temp[256];
          M(istrm,scanf,"%s",temp);
          if(this->str)
            free(this->str);
          this->str=strdup(temp);
        }
        // Constructors
        my_string_ctor_ccs_size(const char* str,size_t n)
        {
          if(str != NULL) {
            if(n > strlen(str))
              n=strlen(str);
            if(n > 0) {
              this->str=malloc(n+1);
              strncpy(this->str,str,n);
              this->str[n]=0;
            }
          }
        }
        my_string_ctor_ccs(const char* str) : my_string_ctor_ccs_size(str,SIZE_MAX)
        {
        }
        my_string_ctor_chr_size(int c,size_t n)
        {
          if(c && n > 0) {
            this->str=malloc(n+1);
            memset(this->str,c,n);
            this->str[n]=0;
          }
        }
    // Table members
      table:
        void swap(pointer o)
        {
          my_string_pointer other=o;
          char* temp=this->str;
          this->str=other->str;
          other->str=temp;
        }
        const char* get() const
        {
          return this->str;
        }
        void set(const char* str)
        {
          my_string_dtor(this);
          this->str = str==NULL ? NULL : strdup(str);
        }
      // Instance members
      instance:
        char *str;
    };
    int main(int argc,char* argv[])
    {
      // My string using default constructor
      my_string_t* ms1=new(my_string);
      // My string using constructor my_string_ctor_ccs_size
      my_string_t* ms2=new_ctor(my_string,my_string_ctor_ccs_size,"This is string 2. Will not be included",17);
      // My string using constructor my_string_ctor_ccs
      my_string_t* ms3=new_ctor(my_string,my_string_ctor_ccs_size,"This is string 3.");
      // My string using constructor my_string_chr_size
      my_string_t* ms4=new_ctor(my_string,my_string_ctor_ccs_size,'A',26);
      // Set value for ms1
      M(ms1,set,"This is string 1");
      STREAM(cout,ms1,endl,ms2,endl,ms3,endl,ms4,endl);
      delete(ms1);
      delete(ms2);
      delete(ms3);
      delete(ms4);
    }

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
    for(ilv=M(lv,cbegin);ilv!=M(lv,cend);ilv++)
      printf("%ld ",*ilv);
    delete(lv);

    /* Custom class */
    yaooc_struct(custom) {
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
    CFOR_EACH(i,mymap) { /* same as for (i=M(mymap,cbegin);i!=M(mymap,cend);i++) */
      printf("%s %d %lf %s\n",M(i->first,c_str),i->second.x,i->second.y,i->second.string);
    }
    delete(mymap);

## Goals

* Custom classes with default constructor, destructor, copy constructor, and assignment
* new/delete for POD and custom classes
* Capable of using alternative constructors to initialize class
* Inheritance
* Polymorphism
* String class
* Containers (vector, map, etc)
* Exceptions
* Streams (cout, cin, cerr)
