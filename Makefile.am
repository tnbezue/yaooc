#SUBDIRS = lib yaoocpp doc doc/yaooc/tutorial doc/yaooc/tutorial/examples

YAOOC_MAJOR_VERSION=1
YAOOC_MINOR_VERSION=3
YAOOC_PATCH_VERSION=1

AM_CFLAGS=-I$(top_srcdir)/include
AM_LDFLAGS=-L$(top_srcdir)/lib -pthread
ACLOCAL_AMFLAGS=-I m4

DOC_FILES=doc/yaooc/tutorial/map.html \
doc/yaooc/tutorial/type_info.html \
doc/yaooc/tutorial/pointer_bag.html \
doc/yaooc/tutorial/streams.html \
doc/yaooc/tutorial/vector.html \
doc/yaooc/tutorial/memory_layout.html \
doc/yaooc/tutorial/placement_new_delete.html \
doc/yaooc/tutorial/new_delete.html \
doc/yaooc/tutorial/constructors.html \
doc/yaooc/tutorial/inheritance.html \
doc/yaooc/tutorial/examples/ch17/my_string_vector.c \
doc/yaooc/tutorial/examples/ch17/my_string_vector.h \
doc/yaooc/tutorial/examples/ch06/my_string_ch06.c \
doc/yaooc/tutorial/examples/ch07/my_string_ch07.c \
doc/yaooc/tutorial/examples/ch02/hello_world.c \
doc/yaooc/tutorial/examples/ch08/my_string_ch08.c \
doc/yaooc/tutorial/examples/ch18/my_string_map.h \
doc/yaooc/tutorial/examples/ch18/my_string_map.c \
doc/yaooc/tutorial/examples/ch08/my_string_ch08.c \
doc/yaooc/tutorial/examples/ch09/my_string_ch09.c \
doc/yaooc/tutorial/examples/ch10/my_string_ch10.c \
doc/yaooc/tutorial/examples/ch11/my_string_ch11.c \
doc/yaooc/tutorial/examples/ch12/my_string_ch12.c \
doc/yaooc/tutorial/examples/ch13/my_string_ch13.c \
doc/yaooc/tutorial/examples/ch13/my_string_ch13.h \
doc/yaooc/tutorial/examples/ch14/my_string_ch14.c \
doc/yaooc/tutorial/examples/ch14/my_string_ch14.h \
doc/yaooc/tutorial/examples/ch15/my_string_ch15.c \
doc/yaooc/tutorial/examples/ch15/my_string_ch15.h \
doc/yaooc/tutorial/containers.html \
doc/yaooc/tutorial/custom_type_info.html \
doc/yaooc/tutorial/type_info_revisited.html \
doc/yaooc/tutorial/custom_class.html \
doc/yaooc/tutorial/exceptions.html \
doc/yaooc/tutorial/hello_world.html \
doc/yaooc/tutorial/yaoocpp.html \
doc/yaooc/tutorial/index.html \
doc/yaooc/tutorial/class_table_instance.html \
doc/yaooc/tutorial/yaooc.js \
doc/yaooc/tutorial/yaooc.css

EXTRA_DIST=yaooc-config.in ${DOC_FILES} tests/test_harness.h tests/demo_def.inc \
  tests/shape.inc tests/simple_object.inc tests/test_utils.inc


lib_LTLIBRARIES = lib/libyaooc.la
lib_libyaooc_la_SOURCES=src/algorithm.c \
src/array_container.c \
src/base_parser.c \
src/date_time.c \
src/dir.c \
src/exception.c \
src/file.c \
src/fstream.c \
src/index_array_container.c \
src/integer.c \
src/ipaddress.c \
src/json.c \
src/json_parser.c \
src/memory.c \
src/new.c \
src/object.c \
src/odbc.c \
src/ordered_array_container.c \
src/pair.c \
src/pointer_bag.c \
src/queue.c \
src/real.c \
src/regex.c \
src/socket.c \
src/sstream.c \
src/stack.c \
src/stream.c \
src/string.c \
src/thread.c \
src/types.c \
src/unique_array_container.c \
src/unique_index_array_container.c \
src/unique_ordered_array_container.c \
src/utils.c \
src/variant.c \
src/vector.c

lib_libyaooc_la_LDFLAGS=-version-info $(YAOOC_MAJOR_VERSION):$(YAOOC_MINOR_VERSION):$(YAOOC_PATCH_VERSION)

pkginclude_HEADERS=include/yaooc/algorithm.h \
include/yaooc/array_container.h \
include/yaooc/base_parser.h \
include/yaooc/date_time.h \
include/yaooc/dir.h \
include/yaooc/exception.h \
include/yaooc/file.h \
include/yaooc/fstream.h \
include/yaooc/index_array_container.h \
include/yaooc/integer.h \
include/yaooc/ipaddress.h \
include/yaooc/json.h \
include/yaooc/json_parser.h \
include/yaooc/macros.h \
include/yaooc/map.h \
include/yaooc/memory.h \
include/yaooc/new.h \
include/yaooc/object.h \
include/yaooc/odbc.h \
include/yaooc/ordered_array_container.h \
include/yaooc/ordered_map.h \
include/yaooc/ordered_set.h \
include/yaooc/pair.h \
include/yaooc/pointer_bag.h \
include/yaooc/queue.h \
include/yaooc/real.h \
include/yaooc/regex.h \
include/yaooc/set.h \
include/yaooc/socket.h \
include/yaooc/sstream.h \
include/yaooc/stack.h \
include/yaooc/stream.h \
include/yaooc/string.h \
include/yaooc/thread.h \
include/yaooc/types.h \
include/yaooc/unique_array_container.h \
include/yaooc/unique_index_array_container.h \
include/yaooc/unique_ordered_array_container.h \
include/yaooc/utils.h \
include/yaooc/vector.h \
include/yaooc/variant.h \
include/yaooc/yaooc_debug.h


check_PROGRAMS=tests/test_algorithm \
tests/test_array_container \
tests/test_base_parser \
tests/test_date_time \
tests/test_dir \
tests/test_exception \
tests/test_file \
tests/test_index_array_container \
tests/test_ipaddress \
tests/test_json \
tests/test_json_parser \
tests/test_map \
tests/test_memory \
tests/test_new \
tests/test_number \
tests/test_object \
tests/test_odbc \
tests/test_ordered_array_container \
tests/test_ordered_map \
tests/test_ordered_set \
tests/test_pair \
tests/test_pointer_bag \
tests/test_queue \
tests/test_regex \
tests/test_set \
tests/test_stack \
tests/test_stream \
tests/test_socket \
tests/test_string \
tests/test_thread \
tests/test_union \
tests/test_unique_array_container \
tests/test_unique_index_array_container \
tests/test_unique_ordered_array_container \
tests/test_utils \
tests/test_variant \
tests/test_vector

LDADD=-L$(top_srcdir)/lib -lyaooc

bin_PROGRAMS=yaoocpp/yaoocpp

yaoocpp_yaoocpp_DEPENDENCIES = $(lib_LTLIBRARIES)

bin_SCRIPTS=yaooc-config

yaoocpp_yaoocpp_SOURCES=yaoocpp/yaoocpp.c yaoocpp/parser.c \
        yaoocpp/template_objects.c  yaoocpp/parser.h \
        yaoocpp/template_objects.h

yaoocpp_yaoocpp_LDFLAGS=-L$(top_srcdir)/lib -lyaooc -pthread

