ifndef YAOOC_ROOT
	YAOOC_ROOT=$(shell pwd)/..
endif

include ${YAOOC_ROOT}/config.mk

OBJS=new.o object.o garbage_bag.o exception.o algorithm.o memory.o array_container.o vector.o string.o \
  unique_array_container.o ordered_array_container.o unique_ordered_array_container.o index_array_container.o \
  unique_index_array_container.o \
  map.o set.o ordered_map.o ordered_set.o stack.o queue.o regex.o thread.o \
  base_parser.o json.o json_parser.o

TARGET=${YAOOC_LIB}/libyaooc.a

all: ${TARGET}

${TARGET}: ${OBJS}
	rm -f $@
	ar rv $@ ${OBJS}

clean:
	rm -f $(TARGET) *.o

new.o: new.c ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h
object.o: object.c ../include/yaooc/object.h ../include/yaooc/new.h \
 ../include/yaooc/yaooc_debug.h
garbage_bag.o: garbage_bag.c ../include/yaooc/garbage_bag.h \
 ../include/yaooc/object.h ../include/yaooc/new.h \
 ../include/yaooc/yaooc_debug.h ../include/yaooc/simple_array.h
exception.o: exception.c ../include/yaooc/exception.h \
 ../include/yaooc/object.h ../include/yaooc/new.h \
 ../include/yaooc/yaooc_debug.h ../include/yaooc/garbage_bag.h \
 ../include/yaooc/simple_array.h
algorithm.o: algorithm.c ../include/yaooc/algorithm.h \
 ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h
memory.o: memory.c ../include/yaooc/memory.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h
array_container.o: array_container.c ../include/yaooc/array_container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h \
 ../include/yaooc/yaooc_debug.h ../include/yaooc/algorithm.h
vector.o: vector.c ../include/yaooc/vector.h \
 ../include/yaooc/array_container.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h
string.o: string.c ../include/yaooc/string.h \
 ../include/yaooc/array_container.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h
unique_array_container.o: unique_array_container.c \
 ../include/yaooc/unique_array_container.h \
 ../include/yaooc/array_container.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h
ordered_array_container.o: ordered_array_container.c \
 ../include/yaooc/ordered_array_container.h \
 ../include/yaooc/array_container.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h
unique_ordered_array_container.o: unique_ordered_array_container.c \
 ../include/yaooc/unique_ordered_array_container.h \
 ../include/yaooc/ordered_array_container.h \
 ../include/yaooc/array_container.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h
index_array_container.o: index_array_container.c \
 ../include/yaooc/index_array_container.h \
 ../include/yaooc/array_container.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h
unique_index_array_container.o: unique_index_array_container.c \
 ../include/yaooc/unique_index_array_container.h \
 ../include/yaooc/index_array_container.h \
 ../include/yaooc/array_container.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h
map.o: map.c ../include/yaooc/map.h \
 ../include/yaooc/unique_index_array_container.h \
 ../include/yaooc/index_array_container.h \
 ../include/yaooc/array_container.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h \
 ../include/yaooc/pair.h
set.o: set.c ../include/yaooc/set.h \
 ../include/yaooc/unique_index_array_container.h \
 ../include/yaooc/index_array_container.h \
 ../include/yaooc/array_container.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h
ordered_map.o: ordered_map.c ../include/yaooc/ordered_map.h \
 ../include/yaooc/unique_ordered_array_container.h \
 ../include/yaooc/ordered_array_container.h \
 ../include/yaooc/array_container.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h \
 ../include/yaooc/pair.h
ordered_set.o: ordered_set.c ../include/yaooc/ordered_set.h \
 ../include/yaooc/unique_ordered_array_container.h \
 ../include/yaooc/ordered_array_container.h \
 ../include/yaooc/array_container.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h
stack.o: stack.c ../include/yaooc/stack.h \
 ../include/yaooc/array_container.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h
queue.o: queue.c ../include/yaooc/queue.h \
 ../include/yaooc/array_container.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h
regex.o: regex.c ../include/yaooc/regex.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h \
 ../include/yaooc/string.h ../include/yaooc/array_container.h
thread.o: thread.c ../include/yaooc/thread.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h \
 ../include/yaooc/exception.h ../include/yaooc/garbage_bag.h \
 ../include/yaooc/simple_array.h
base_parser.o: base_parser.c ../include/yaooc/base_parser.h \
 ../include/yaooc/string.h ../include/yaooc/array_container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h \
 ../include/yaooc/yaooc_debug.h ../include/yaooc/stack.h
json.o: json.c ../include/yaooc/json.h ../include/yaooc/string.h \
 ../include/yaooc/array_container.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h \
 ../include/yaooc/map.h ../include/yaooc/unique_index_array_container.h \
 ../include/yaooc/index_array_container.h ../include/yaooc/pair.h \
 ../include/yaooc/vector.h
json_parser.o: json_parser.c ../include/yaooc/json_parser.h \
 ../include/yaooc/string.h ../include/yaooc/array_container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h \
 ../include/yaooc/yaooc_debug.h ../include/yaooc/base_parser.h \
 ../include/yaooc/stack.h ../include/yaooc/json.h ../include/yaooc/map.h \
 ../include/yaooc/unique_index_array_container.h \
 ../include/yaooc/index_array_container.h ../include/yaooc/pair.h \
 ../include/yaooc/vector.h
