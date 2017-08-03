ifndef YAOOC_ROOT
	YAOOC_ROOT=$(shell pwd)/..
endif
include $(YAOOC_ROOT)/config.mk
OBJS=yaoocpp.o yaooc_definition_parser.o template_objects.o
TARGETS=yaoocpp${EXT}

all: ${TARGETS}


yaoocpp${EXT}: ${OBJS}
	${LD} -o $@ $^ ${LDFLAGS} ${LDLIBS}

clean:
	rm -f ${TARGETS} *.o

yaoocpp.o: yaoocpp.c ../include/yaooc/vector.h \
 ../include/yaooc/container.h ../include/yaooc/object.h \
 ../include/yaooc/new.h ../include/yaooc/map.h \
 ../include/yaooc/unique_index_container.h \
 ../include/yaooc/index_container.h ../include/yaooc/pair.h \
 yaooc_definition_parser.h ../include/yaooc/base_parser.h \
 ../include/yaooc/string.h ../include/yaooc/stack.h template_objects.h \
 ../include/yaooc/memory.h ../include/yaooc/garbage_bag.h
yaooc_definition_parser.o: yaooc_definition_parser.c \
 yaooc_definition_parser.h ../include/yaooc/base_parser.h \
 ../include/yaooc/string.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h \
 ../include/yaooc/stack.h template_objects.h ../include/yaooc/vector.h \
 ../include/yaooc/memory.h ../include/yaooc/garbage_bag.h
template_objects.o: template_objects.c template_objects.h \
 ../include/yaooc/vector.h ../include/yaooc/container.h \
 ../include/yaooc/object.h ../include/yaooc/new.h \
 ../include/yaooc/string.h ../include/yaooc/memory.h \
 ../include/yaooc/garbage_bag.h
