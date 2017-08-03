#ifndef __JSON_INCLUDED__
#define __JSON_INCLUDED__

#include <yaooc/string.h>
#include <yaooc/map.h>
#include <yaooc/vector.h>

typedef enum { JSON_UNDEFINED=0, JSON_NULL, JSON_BOOL, JSON_INTEGER, JSON_REAL, JSON_STRING, JSON_ARRAY, JSON_OBJECT } json_type_t;

class_forward(json_value_vector)
class_forward(json_string_json_value_map)

typedef union {
  bool    bool_;
  int64_t int_;
  double  real_;
  char*   string_;
  json_value_vector_t* array_;
  json_string_json_value_map_t* object_;
} json_data_t;

#include <yaooc/json.h>

class_table(json_value) {
  yaooc_object_class_members_t;
  void (*virtual_destructor)(pointer);
  void (*virtual_copy_ctor)(pointer,const_pointer);
  void (*virtual_assign)(pointer,const_pointer);
  bool (*virtual_less_than_compare)(const_pointer,const_pointer);
  json_type_t (*type)(const_pointer);
  int (*print_to_string)(const_pointer,char *,int);
  void (*clear)(pointer);
};

class_instance(json_value) {
  yaooc_object_instance_members_t;
  json_data_t;
  json_type_t type_;
};

class(json_value);
ISA_DEFINITION(json_value,yaooc_object)
void json_value_swap(pointer,pointer);

/* Type info */
void json_value_default_ctor(pointer);
void json_value_dtor(pointer);
void json_value_copy_ctor(pointer,const_pointer);
void json_value_assign(pointer,const_pointer);
bool json_value_less_than_compare(const_pointer,const_pointer);


/* Class member functions */
void json_value_virtual_destructor(pointer);
void json_value_virtual_copy_ctor(pointer,const_pointer);
void json_value_virtual_assign(pointer,const_pointer);
bool json_value_virtual_less_than_compare(const_pointer,const_pointer);
json_type_t json_value_type(const_pointer);
int json_value_print_to_string(const_pointer,char *,int);
void json_value_clear(pointer);

/* Protected members */

#define JSON_VALUE_CLASS_MEMBERS \
  { \
    json_value_isa, \
    json_value_is_descendent, \
    json_value_swap \
  }, \
  (void (*)(pointer)) json_value_virtual_destructor,\
  (void (*)(pointer,const_pointer)) json_value_virtual_copy_ctor,\
  (void (*)(pointer,const_pointer)) json_value_virtual_assign,\
  (bool (*)(const_pointer,const_pointer)) json_value_virtual_less_than_compare,\
  (json_type_t (*)(const_pointer)) json_value_type,\
  (int (*)(const_pointer,char *,int)) json_value_print_to_string,\
  (void (*)(pointer)) json_value_clear,\

class_table(json_null) {
  json_value_class_members_t;
};

class_instance(json_null) {
  json_value_instance_members_t;
};

class(json_null);
ISA_DEFINITION(json_null,json_value)

/* Type info */
void json_null_default_ctor(pointer);


/* Class member functions */
void json_null_virtual_copy_ctor(pointer,const_pointer);
void json_null_virtual_assign(pointer,const_pointer);
bool json_null_virtual_less_than_compare(const_pointer,const_pointer);
int json_null_print_to_string(const_pointer,char *,int);
void json_null_clear(pointer);

/* Protected members */

#define JSON_NULL_CLASS_MEMBERS \
  { JSON_VALUE_CLASS_MEMBERS }, \

class_table(json_bool) {
  json_value_class_members_t;
  bool (*get)(const_pointer);
  void (*set)(pointer,bool);
};

class_instance(json_bool) {
  json_value_instance_members_t;
};

class(json_bool);
ISA_DEFINITION(json_bool,json_value)

/* Type info */
void json_bool_default_ctor(pointer);

/* Constructors */
void json_bool_ctor_bool(pointer,va_list);

/* Class member functions */
void json_bool_virtual_copy_ctor(pointer,const_pointer);
void json_bool_virtual_assign(pointer,const_pointer);
bool json_bool_virtual_less_than_compare(const_pointer,const_pointer);
int json_bool_print_to_string(const_pointer,char *,int);
void json_bool_clear(pointer);
bool json_bool_get(const_pointer);
void json_bool_set(pointer,bool);

/* Protected members */

#define JSON_BOOL_CLASS_MEMBERS \
  { JSON_VALUE_CLASS_MEMBERS }, \
  (bool (*)(const_pointer)) json_bool_get,\
  (void (*)(pointer,bool)) json_bool_set,\

class_table(json_integer) {
  json_value_class_members_t;
  int64_t (*get)(const_pointer);
  void (*set)(pointer,int64_t);
};

class_instance(json_integer) {
  json_value_instance_members_t;
};

class(json_integer);
ISA_DEFINITION(json_integer,json_value)

/* Type info */
void json_integer_default_ctor(pointer);

/* Constructors */
void json_integer_ctor_int(pointer,va_list);

/* Class member functions */
void json_integer_virtual_copy_ctor(pointer,const_pointer);
void json_integer_virtual_assign(pointer,const_pointer);
bool json_integer_virtual_less_than_compare(const_pointer,const_pointer);
int json_integer_print_to_string(const_pointer,char *,int);
void json_integer_clear(pointer);
int64_t json_integer_get(const_pointer);
void json_integer_set(pointer,int64_t);

/* Protected members */

#define JSON_INTEGER_CLASS_MEMBERS \
  { JSON_VALUE_CLASS_MEMBERS }, \
  (int64_t (*)(const_pointer)) json_integer_get,\
  (void (*)(pointer,int64_t)) json_integer_set,\

class_table(json_real) {
  json_value_class_members_t;
  double (*get)(const_pointer);
  void (*set)(pointer,double);
};

class_instance(json_real) {
  json_value_instance_members_t;
};

class(json_real);
ISA_DEFINITION(json_real,json_value)

/* Type info */
void json_real_default_ctor(pointer);

/* Constructors */
void json_real_ctor_real(pointer,va_list);

/* Class member functions */
void json_real_virtual_copy_ctor(pointer,const_pointer);
void json_real_virtual_assign(pointer,const_pointer);
bool json_real_virtual_less_than_compare(const_pointer,const_pointer);
int json_real_print_to_string(const_pointer,char *,int);
void json_real_clear(pointer);
double json_real_get(const_pointer);
void json_real_set(pointer,double);

/* Protected members */

#define JSON_REAL_CLASS_MEMBERS \
  { JSON_VALUE_CLASS_MEMBERS }, \
  (double (*)(const_pointer)) json_real_get,\
  (void (*)(pointer,double)) json_real_set,\

class_table(json_string) {
  json_value_class_members_t;
  const char * (*get)(const_pointer);
  void (*set)(pointer,const char *);
};

class_instance(json_string) {
  json_value_instance_members_t;
};

class(json_string);
ISA_DEFINITION(json_string,json_value)

/* Type info */
void json_string_default_ctor(pointer);

/* Constructors */
void json_string_ctor_ccs(pointer,va_list);

/* Class member functions */
void json_string_virtual_copy_ctor(pointer,const_pointer);
void json_string_virtual_assign(pointer,const_pointer);
bool json_string_virtual_less_than_compare(const_pointer,const_pointer);
int json_string_print_to_string(const_pointer,char *,int);
void json_string_clear(pointer);
const char * json_string_get(const_pointer);
void json_string_set(pointer,const char *);

/* Protected members */

#define JSON_STRING_CLASS_MEMBERS \
  { JSON_VALUE_CLASS_MEMBERS }, \
  (const char * (*)(const_pointer)) json_string_get,\
  (void (*)(pointer,const char *)) json_string_set,\

VECTOR_DEFINITION(json_value)
typedef json_value_vector_iterator json_array_iterator;
typedef json_value_vector_const_iterator json_array_const_iterator;


class_table(json_array) {
  json_value_class_members_t;
  void (*add)(pointer,const_pointer);
  json_value_pointer (*at)(pointer,size_t);
  json_value_const_pointer (*cat)(const_pointer,size_t);
  size_t (*size)(pointer);
  json_array_iterator (*begin)(pointer);
  json_array_iterator (*end)(pointer);
  json_array_const_iterator (*cbegin)(const_pointer);
  json_array_const_iterator (*cend)(const_pointer);
};

class_instance(json_array) {
  json_value_instance_members_t;
};

class(json_array);
ISA_DEFINITION(json_array,json_value)

/* Type info */
void json_array_default_ctor(pointer);


/* Class member functions */
void json_array_virtual_copy_ctor(pointer,const_pointer);
void json_array_virtual_assign(pointer,const_pointer);
bool json_array_virtual_less_than_compare(const_pointer,const_pointer);
int json_array_print_to_string(const_pointer,char *,int);
void json_array_clear(pointer);
void json_array_add(pointer,const_pointer);
json_value_pointer json_array_at(pointer,size_t);
size_t json_array_size(const_pointer);
json_array_iterator json_array_begin(pointer);
json_array_iterator json_array_end(pointer);
json_array_const_iterator json_array_cbegin(const_pointer);
json_array_const_iterator json_array_cend(const_pointer);

/* Protected members */

#define JSON_ARRAY_CLASS_MEMBERS \
  { JSON_VALUE_CLASS_MEMBERS }, \
  (void (*)(pointer,const_pointer)) json_array_add,\
  (json_value_pointer (*)(pointer,size_t)) json_array_at,\
  (json_value_const_pointer (*)(pointer,size_t)) json_array_at,\
  (size_t (*)(const_pointer)) json_array_size,\
  (json_array_iterator (*)(pointer)) json_array_begin,\
  (json_array_iterator (*)(pointer)) json_array_end,\
  (json_array_const_iterator (*)(const_pointer)) json_array_cbegin,\
  (json_array_const_iterator (*)(const_pointer)) json_array_cend,\

MAP_DEFINITION(json_string,json_value)
typedef json_string_json_value_map_iterator json_object_iterator;
typedef json_string_json_value_map_const_iterator json_object_const_iterator;

class_table(json_object) {
  json_value_class_members_t;
  void (*insert)(pointer,const_pointer,const_pointer);
  json_value_pointer (*at)(pointer,const_pointer);
  json_value_const_pointer (*cat)(const_pointer,const_pointer);
  size_t (*size)(const_pointer);
  json_object_iterator (*begin)(pointer);
  json_object_iterator (*end)(pointer);
  json_object_const_iterator (*cbegin)(const_pointer);
  json_object_const_iterator (*cend)(const_pointer);
};

class_instance(json_object) {
  json_value_instance_members_t;
};

class(json_object);
ISA_DEFINITION(json_object,json_value)

/* Type info */
void json_object_default_ctor(pointer);


/* Class member functions */
void json_object_virtual_copy_ctor(pointer,const_pointer);
void json_object_virtual_assign(pointer,const_pointer);
bool json_object_virtual_less_than_compare(const_pointer,const_pointer);
int json_object_print_to_string(const_pointer,char *,int);
void json_object_clear(pointer);
void json_object_insert(pointer,const_pointer,const_pointer);
json_value_pointer json_object_at(pointer,const_pointer);
size_t json_object_size(const_pointer);
json_object_iterator json_object_begin(pointer);
json_object_iterator json_object_end(pointer);
json_object_const_iterator json_object_cbegin(const_pointer);
json_object_const_iterator json_object_cend(const_pointer);

/* Protected members */

#define JSON_OBJECT_CLASS_MEMBERS \
  { JSON_VALUE_CLASS_MEMBERS }, \
  (void (*)(pointer,const_pointer,const_pointer)) json_object_insert,\
  (json_value_pointer (*)(pointer,const_pointer)) json_object_at,\
  (json_value_const_pointer (*)(const_pointer,const_pointer)) json_object_at,\
  (size_t (*)(pointer)) json_object_size,\
  (json_object_iterator (*)(pointer)) json_object_begin,\
  (json_object_iterator (*)(pointer)) json_object_end,\
  (json_object_const_iterator (*)(const_pointer)) json_object_cbegin,\
  (json_object_const_iterator (*)(const_pointer)) json_object_cend,\


#endif
