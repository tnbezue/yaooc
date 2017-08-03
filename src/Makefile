ifndef YAOOC_ROOT
	YAOOC_ROOT=$(shell pwd)/..
endif

include ${YAOOC_ROOT}/config.mk

# 25
OBJS=new.o object.o garbage_bag.o exception.o algorithm.o container.o string.o vector.o unique_container.o \
  ordered_container.o unique_ordered_container.o index_container.o unique_index_container.o \
  map.o set.o \
  ordered_map.o ordered_set.o stack.o queue.o memory.o base_parser.o json.o json_parser.o \
  regex.o thread.o

TARGET=${YAOOC_LIB}/libyaooc.a

all: ${TARGET}

${TARGET}: ${OBJS}
	[ -d ${YAOOC_LIB} ] || mkdir ${YAOOC_LIB}
	rm -f $@
	ar rv $@ ${OBJS}

clean:
	rm -f $(TARGET) *.o

new.o: new.c ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h
object.o: object.c ../include/yaooc/object.h ../include/yaooc/new.h
garbage_bag.o: garbage_bag.c ../include/yaooc/garbage_bag.h \
 ../include/yaooc/object.h ../include/yaooc/new.h
exception.o: exception.c ../include/yaooc/exception.h \
 ../include/yaooc/object.h ../include/yaooc/new.h \
 ../include/yaooc/garbage_bag.h
algorithm.o: algorithm.c ../include/yaooc/algorithm.h \
 ../include/yaooc/new.h
container.o: container.c ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h \
 ../include/yaooc/algorithm.h ../include/yaooc/yaooc_debug.h
string.o: string.c ../include/yaooc/string.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h
vector.o: vector.c ../include/yaooc/vector.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h
unique_container.o: unique_container.c \
 ../include/yaooc/unique_container.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h
ordered_container.o: ordered_container.c \
 ../include/yaooc/ordered_container.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h
unique_ordered_container.o: unique_ordered_container.c \
 ../include/yaooc/unique_ordered_container.h \
 ../include/yaooc/ordered_container.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h
index_container.o: index_container.c ../include/yaooc/index_container.h \
 ../include/yaooc/container.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h
unique_index_container.o: unique_index_container.c \
 ../include/yaooc/unique_index_container.h \
 ../include/yaooc/index_container.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h
map.o: map.c ../include/yaooc/map.h \
 ../include/yaooc/unique_index_container.h \
 ../include/yaooc/index_container.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h ../include/yaooc/pair.h \
 ../include/yaooc/yaooc_debug.h
set.o: set.c ../include/yaooc/set.h \
 ../include/yaooc/unique_index_container.h \
 ../include/yaooc/index_container.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h
ordered_map.o: ordered_map.c ../include/yaooc/ordered_map.h \
 ../include/yaooc/unique_ordered_container.h \
 ../include/yaooc/ordered_container.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h ../include/yaooc/pair.h
ordered_set.o: ordered_set.c ../include/yaooc/ordered_set.h \
 ../include/yaooc/unique_ordered_container.h \
 ../include/yaooc/ordered_container.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h
stack.o: stack.c ../include/yaooc/stack.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h
queue.o: queue.c ../include/yaooc/queue.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h
memory.o: memory.c ../include/yaooc/memory.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/yaooc_debug.h
base_parser.o: base_parser.c ../include/yaooc/base_parser.h \
 ../include/yaooc/string.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h \
 ../include/yaooc/stack.h
json.o: json.c ../include/yaooc/json.h ../include/yaooc/string.h \
 ../include/yaooc/container.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/map.h \
 ../include/yaooc/unique_index_container.h \
 ../include/yaooc/index_container.h ../include/yaooc/pair.h \
 ../include/yaooc/vector.h
json_parser.o: json_parser.c ../include/yaooc/json_parser.h \
 ../include/yaooc/string.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h \
 ../include/yaooc/base_parser.h ../include/yaooc/stack.h \
 ../include/yaooc/json.h ../include/yaooc/map.h \
 ../include/yaooc/unique_index_container.h \
 ../include/yaooc/index_container.h ../include/yaooc/pair.h \
 ../include/yaooc/vector.h
regex.o: regex.c ../include/yaooc/regex.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/string.h \
 ../include/yaooc/container.h
thread.o: thread.c ../include/yaooc/thread.h ../include/yaooc/object.h \
 ../include/yaooc/new.h
