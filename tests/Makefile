ifndef YAOOC_ROOT
	YAOOC_ROOT=$(shell pwd)/..
endif
include $(YAOOC_ROOT)/config.mk
TARGETS=test_new test_object test_garbage_bag test_exception test_algorithm test_container test_string \
  test_vector test_unique_container test_ordered_container test_unique_ordered_container \
  test_index_container test_unique_index_container test_map test_set test_ordered_map test_ordered_set \
  test_stack test_queue test_unique_ptr test_shared_ptr test_base_parser test_json \
  test_json_parser test_regex test_thread

all: ${TARGETS}

test_thread: test_thread.o
	${LD} -pthread -o $@ $^ ${LDFLAGS} ${LDLIBS}

clean:
	rm -f ${TARGETS} *.o

test_new.o: test_new.c ../include/yaooc/new.h test_harness.h
test_object.o: test_object.c ../include/yaooc/object.h \
 ../include/yaooc/new.h test_harness.h demo_def.inc
test_garbage_bag.o: test_garbage_bag.c ../include/yaooc/garbage_bag.h \
 ../include/yaooc/object.h ../include/yaooc/new.h test_harness.h \
 demo_def.inc
test_exception.o: test_exception.c ../include/yaooc/exception.h \
 ../include/yaooc/object.h ../include/yaooc/new.h \
 ../include/yaooc/garbage_bag.h test_harness.h demo_def.inc
test_algorithm.o: test_algorithm.c ../include/yaooc/algorithm.h \
 ../include/yaooc/new.h test_harness.h
test_container.o: test_container.c ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h test_harness.h \
 simple_object.inc
test_string.o: test_string.c ../include/yaooc/string.h \
 ../include/yaooc/container.h ../include/yaooc/object.h \
 ../include/yaooc/new.h test_harness.h
test_vector.o: test_vector.c ../include/yaooc/vector.h \
 ../include/yaooc/container.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/algorithm.h \
 ../include/yaooc/string.h demo_def.inc test_harness.h
test_unique_container.o: test_unique_container.c \
 ../include/yaooc/unique_container.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h test_harness.h \
 simple_object.inc
test_ordered_container.o: test_ordered_container.c \
 ../include/yaooc/ordered_container.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h test_harness.h \
 simple_object.inc
test_unique_ordered_container.o: test_unique_ordered_container.c \
 ../include/yaooc/unique_ordered_container.h \
 ../include/yaooc/ordered_container.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h test_harness.h \
 simple_object.inc
test_index_container.o: test_index_container.c \
 ../include/yaooc/index_container.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h test_harness.h \
 simple_object.inc
test_unique_index_container.o: test_unique_index_container.c \
 ../include/yaooc/unique_index_container.h \
 ../include/yaooc/index_container.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h test_harness.h \
 simple_object.inc
test_map.o: test_map.c ../include/yaooc/object.h ../include/yaooc/new.h \
 ../include/yaooc/map.h ../include/yaooc/unique_index_container.h \
 ../include/yaooc/index_container.h ../include/yaooc/container.h \
 ../include/yaooc/pair.h ../include/yaooc/string.h demo_def.inc \
 test_harness.h
test_set.o: test_set.c ../include/yaooc/set.h \
 ../include/yaooc/unique_index_container.h \
 ../include/yaooc/index_container.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h demo_def.inc \
 test_harness.h
test_ordered_map.o: test_ordered_map.c ../include/yaooc/ordered_map.h \
 ../include/yaooc/unique_ordered_container.h \
 ../include/yaooc/ordered_container.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h ../include/yaooc/pair.h \
 ../include/yaooc/string.h demo_def.inc test_harness.h
test_ordered_set.o: test_ordered_set.c ../include/yaooc/ordered_set.h \
 ../include/yaooc/unique_ordered_container.h \
 ../include/yaooc/ordered_container.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h demo_def.inc \
 test_harness.h
test_stack.o: test_stack.c ../include/yaooc/stack.h \
 ../include/yaooc/container.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/string.h test_harness.h
test_queue.o: test_queue.c ../include/yaooc/queue.h \
 ../include/yaooc/container.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/string.h test_harness.h
test_unique_ptr.o: test_unique_ptr.c ../include/yaooc/memory.h \
 ../include/yaooc/object.h ../include/yaooc/new.h \
 ../include/yaooc/vector.h ../include/yaooc/container.h test_harness.h \
 shape.inc
test_shared_ptr.o: test_shared_ptr.c ../include/yaooc/garbage_bag.h \
 ../include/yaooc/object.h ../include/yaooc/new.h \
 ../include/yaooc/vector.h ../include/yaooc/container.h test_harness.h \
 shape.inc
test_base_parser.o: test_base_parser.c ../include/yaooc/base_parser.h \
 ../include/yaooc/string.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h \
 ../include/yaooc/stack.h test_harness.h
test_json.o: test_json.c ../include/yaooc/json.h \
 ../include/yaooc/string.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h ../include/yaooc/map.h \
 ../include/yaooc/unique_index_container.h \
 ../include/yaooc/index_container.h ../include/yaooc/pair.h \
 ../include/yaooc/vector.h test_harness.h
test_json_parser.o: test_json_parser.c ../include/yaooc/json_parser.h \
 ../include/yaooc/string.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h \
 ../include/yaooc/base_parser.h ../include/yaooc/stack.h \
 ../include/yaooc/json.h ../include/yaooc/map.h \
 ../include/yaooc/unique_index_container.h \
 ../include/yaooc/index_container.h ../include/yaooc/pair.h \
 ../include/yaooc/vector.h test_harness.h
test_regex.o: test_regex.c ../include/yaooc/regex.h \
 ../include/yaooc/object.h ../include/yaooc/new.h \
 ../include/yaooc/string.h ../include/yaooc/container.h \
 ../include/yaooc/garbage_bag.h test_harness.h
test_thread.o: test_thread.c ../include/yaooc/thread.h \
 ../include/yaooc/object.h ../include/yaooc/new.h \
 ../include/yaooc/exception.h ../include/yaooc/garbage_bag.h \
 test_harness.h
