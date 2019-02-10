/*
		Copyright (C) 2016-2019  by Terry N Bezue

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

#ifndef __YAOOC_MACROS_INCLUDED__
#define __YAOOC_MACROS_INCLUDED__


/*
	Forward declaration of a class
*/
#define yaooc_class_forward(name) \
typedef struct name ## _s name ## _t; \
typedef struct name ## _s * const name ## _pointer; \
typedef const struct name ## _s * const name ## _const_pointer; \
extern const type_info_t* const name ## _ti;

/*
	Forward declaration of a struct. Same as class
*/
#define yaooc_struct_forward(name) yaooc_class_forward(name)

/*
	Forward declaration of a union
*/
#define yaooc_union_forward(name) \
typedef union name ## _s name ## _t; \
typedef union name ## _s * const name ## _pointer; \
typedef const union name ## _s * const name ## _const_pointer; \
extern const type_info_t* const name ## _ti;

/*
  Structure definition.
*/
#define yaooc_struct(name) \
typedef struct name ## _s name ## _t; \
typedef struct name ## _s * const name ## _pointer; \
typedef const struct name ## _s * const name ## _const_pointer; \
extern const type_info_t __ ## name ## _ti; \
extern const type_info_t* const name ## _ti; \
struct name ## _s

/*
  Structure definition for POD.
*/
#define yaooc_pod_struct(name) \
typedef struct name ## _s name ## _t; \
typedef struct name ## _s * const name ## _pointer; \
typedef const struct name ## _s * const name ## _const_pointer; \
extern const pod_type_info_t __ ## name ## _ti; \
extern const type_info_t* const name ## _ti; \
struct name ## _s

/*
  Defines class table for an object
*/
#define yaooc_class_table(name) \
typedef struct name ## _s name ## _t; \
typedef struct name ## _s * const name ## _pointer; \
typedef const struct name ## _s * const name ## _const_pointer; \
typedef struct name ## _class_table_s name ## _class_table_t; \
struct name ## _class_table_s

/*
  Define the instance members for an object
*/
#define yaooc_class_instance(name) \
typedef struct name ## _s name ## _t; \
typedef struct name ## _s * const name ## _pointer; \
typedef const struct name ## _s * const name ## _const_pointer; \
typedef struct name ## _class_instance_s name ## _class_instance_t; \
struct name ## _class_instance_s

/*
  Combines class table and instance members to make the class object;
*/
#define yaooc_class(name) \
typedef struct name ## _s name ## _t; \
typedef struct name ## _s * const name ## _pointer; \
typedef const struct name ## _s * const name ## _const_pointer; \
extern name ## _class_table_t name ## _class_table; \
extern const type_info_t __ ## name ## _ti; \
extern const type_info_t* const name ## _ti; \
struct name ## _s \
{ \
	const name ## _class_table_t* class_table_; \
	name ## _class_instance_t; \
};

/*
  Defines class table for a union.  Same as class table
*/
#define yaooc_union_table(name) yaooc_class_table(name)

/*
  Define the instance members for a union
*/
#define yaooc_union_instance(name) \
typedef struct name ## _s name ## _t; \
typedef struct name ## _s * const name ## _pointer; \
typedef const struct name ## _s * const name ## _const_pointer; \
typedef union name ## _class_instance_s name ## _class_instance_t; \
union name ## _class_instance_s

/*
  Combines class table and instance members to make the class object;
*/
#define yaooc_union(name) yaooc_class(name)

/*
	Union definition

#define yaooc_union(name) \
typedef union name ## _s name ## _t; \
typedef union name ## _s * const name ## _pointer; \
typedef const union name ## _s * const name ## _const_pointer; \
extern const type_info_t __ ## name ## _ti; \
extern const type_info_t* const name ## _ti; \
union name ## _s
*/

#define DEF_CTOR_Y(T) T ## _default_ctor
#define DEF_CTOR_N(T) NULL
#define DTOR_Y(T) T ## _dtor
#define DTOR_N(T) NULL
#define COPY_CTOR_Y(T) T ## _copy_ctor
#define COPY_CTOR_N(T) NULL
#define ASSIGN_Y(T) T ## _assign
#define ASSIGN_N(T) NULL
#define LT_Y(T) T ## _less_than_compare
#define LT_N(T) NULL
#define TOS_Y(T) T ## _to_stream
#define TOS_N(T) NULL
#define FROMS_Y(T) T ## _from_stream
#define FROMS_N(T) NULL
#define CT_Y(T) &T ## _class_table
#define CT_N(T) NULL
/* For when parent is specified as NULL */
#define __NULL_ti *(char*)NULL

#define __DEFINE_TYPE_INFO__(T,DEF_CTOR,DTOR,COPY_CTOR,ASSIGN,LT_COMPARE,TO_STREAM,FROM_STREAM,CLASS_TABLE,PARENT) \
const type_info_t __ ## T ## _ti ={ \
	.type_size_ = sizeof(T ## _t),\
	.default_ctor_ = (default_constructor) DEF_CTOR, \
	.dtor_ = (destructor) DTOR, \
	.copy_ctor_ = (copy_constructor)COPY_CTOR, \
  .assign_ = (assignment) ASSIGN, \
	.less_than_compare_ = (less_than_compare) LT_COMPARE, \
	.to_stream_ = (to_stream) TO_STREAM, \
	.from_stream_ = (from_stream) FROM_STREAM, \
	.class_table_ = (const class_table_t*) CLASS_TABLE, \
	.parent_ = (const type_info_t*) PARENT \
}; \
const type_info_t* const T ## _ti = &__ ## T ## _ti;

#define DEFINE_TYPE_INFO(T,HAS_DEF_CTOR,HAS_DTOR,HAS_COPY_CTOR,HAS_ASSIGN,HAS_LT_COMPARE,HAS_TO_STREAM,HAS_FROM_STREAM,HAS_CLASS_TABLE,PARENT) \
	__DEFINE_TYPE_INFO__(T,\
	DEF_CTOR_ ## HAS_DEF_CTOR(T),\
	DTOR_ ## HAS_DTOR(T),\
	COPY_CTOR_ ## HAS_COPY_CTOR(T),\
	ASSIGN_ ## HAS_ASSIGN(T),\
	LT_ ## HAS_LT_COMPARE(T),\
	TOS_ ## HAS_TO_STREAM(T),\
	FROMS_ ## HAS_FROM_STREAM(T),\
	CT_ ## HAS_CLASS_TABLE(T),\
	&__ ## PARENT ## _ti \
)

#define __DEFINE_POD_TYPE_INFO__(T,LT_COMPARE,TO_STREAM,FROM_STREAM) \
const pod_type_info_t __ ## T ## _ti ={ \
	.type_size_ = sizeof(T ## _t) | POD_FLAG,\
	.less_than_compare_ = (less_than_compare) LT_COMPARE, \
	.to_stream_ = (to_stream) TO_STREAM, \
	.from_stream_ = (from_stream) FROM_STREAM \
}; \
const type_info_t* const T ## _ti = (const type_info_t*)&__ ## T ## _ti;

#define DEFINE_POD_TYPE_INFO(T,HAS_LT_COMPARE,HAS_TO_STREAM,HAS_FROM_STREAM) \
	__DEFINE_POD_TYPE_INFO__(T,\
	LT_ ## HAS_LT_COMPARE(T),\
	TOS_ ## HAS_TO_STREAM(T),\
	FROMS_ ## HAS_FROM_STREAM(T)\
)


#define SWAP(T,x,y) { T __temp__=x; x=y; y=__temp__; }

#define STACK_PTR(T,P) char P ## _stack[sizeof(T ## _t)]; T ## _pointer P=__newp_array(P ## _stack,T ## _ti,1)
#define STACK_PTR_CTOR(T,P,CTOR,...) char P ## _stack[sizeof(T ## _t)]; T ## _pointer P=__newp_array_ctor(P ## _stack,T ## _ti,1,CTOR,## __VA_ARGS__)
#define STACK_VAR(T,V) T ##_t V; __newp_array(&V,T ## _ti,1)
#define STACK_VAR_CTOR(T,V,CTOR,...) T ## _t V; __newp_array_ctor(&V,T ## _ti,1,CTOR, ## __VA_ARGS__)
#define STACK_VAR_ARRAY(T,V,N) T ## _t V[N]; __newp_array(V,T ## _ti,N)
#define STACK_VAR_ARRAY_CTOR(T,V,N,CTOR,...) T ## _t V[N]; __newp_array_ctor(V,T ## _ti,N,CTOR, ## __VA_ARGS__)

#define DISTANCE(ti,first,last) ((((yaooc_private_const_iterator)last) - ((yaooc_private_const_iterator)first))/yaooc_sizeof(ti))

#endif
