# Yet Another Object Oriented C (yaooc)

In the beginning, YAOOC was a collection of macros (and a bit of code) to make C a bit more like C++ -- new,
delete, string class, vector, map, iterators, exceptions, etc.

It has morphed into a "compiler".
It translates a YAOOC file (syntax is a cross between C and C++) into a C source and header file.
In the future (distant future), it will be capable of "compiling" C++ code into C (similar to cfront).
This will be useful to C compilers that don't support C++ (i.e., tiny C compiler).

To get an idea of the features, review the tutorial (doc/yaooc/tutorial).  Each lesson is
only one or two pages.  The entire tutorial should take 30-45 minutes to complete.

## Example

    /* Code parsed by YAOOC begins with percent sign (%) */
    %include <yaooc/object.yaooh>
    %include <yaooc/exception.yaooh>

    /* Normal C code is passed to C compiler */
    #include <yaooc/stream.h>
    #include <stdio.h>
    #include <string.h>

    %class my_string_exception : yaooc_exception {
      my_string_exception() : yaooc_exception() { }
      my_string_exception_ctor_v(const char* fmt,...) = yaooc_exception_ctor_v;
    };

    %class my_string : yaooc_object
    {
        // Constructor
        my_string() : str(NULL) { }
        // Destructor
        ~my_string() { if(this->str) free(this->str); }
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
              return -1; /* lhs is NULL, rhs is not.  NULL is less than non NULL */
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
    // Table members (shared by all instances of my_string)
      table:
        size_t npos = -1;

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
          if(str==NULL)
            THROW(new_ctor(my_string,my_string_ctor_v,"Cannot set string to be NULL"));
          my_string_dtor(this);
          this->str = str==NULL ? NULL : strdup(str);
        }
      // Instance members (unique to each instance)
      instance:
        char *str;
    };

    int main(int argc,char* argv[])
    {
      my_string_t *ms1=NULL,*ms2=NULL,*ms3=NULL,*ms4=NULL,*ms5=NULL;
      TRY {
        // My string using default constructor
        my_string_t* ms1=new(my_string);
        // My string using constructor my_string_ctor_ccs_size
        my_string_t* ms2=new_ctor(my_string,my_string_ctor_ccs_size,"This is string 2. Will not be included",17);
        // My string using constructor my_string_ctor_ccs
        my_string_t* ms3=new_ctor(my_string,my_string_ctor_ccs,"This is string 3.");
        // My string using constructor my_string_chr_size
        my_string_t* ms4=new_ctor(my_string,my_string_ctor_chr_size,'A',26);
        // Set value for ms1
        M(ms1,set,"This is string 1");
        // My string using copy constructor
        my_string_t* ms5 = new_copy(ms1);
        M(ms5,set,"This is string 5");
        // Output to cout stream
        STREAM(cout,ms1,endl,ms2,endl,ms3,endl,ms4,endl,ms5,endl);
        // Less than compare of two strings
        if(op_lt(ms2,ms4)) {
          printf("'%s' is less than '%s'.\n",ms2->str,ms4->str);
        }
      } CATCH(my_string_exception,mse) {
        M(cout,printf,"My string exception ocurred: %s\n",M(mse,what));
      } CATCH(yaooc_exception,e) {
        M(cout,printf,"Exception occured: %s\n",M(e,what));
      }
      // Delete objects created
      if (ms1) delete(ms1);
      if (ms2) delete(ms2);
      if (ms3) delete(ms3);
      if (ms4) delete(ms4);
      if (ms5) delete(ms5);
    }

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
