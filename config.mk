YAOOC_INCLUDE=${YAOOC_ROOT}/include
YAOOC_LIB=${YAOOC_ROOT}/lib

CC=gcc
LD=${CC}
#CFLAGS=-fms-extensions -I${YAOOC_INCLUDE} -Wall  -D__YAOOC_USE_GC__ -g # -O2 #-D__DEBUG__ #
CFLAGS=-fms-extensions -I${YAOOC_INCLUDE} -Wall -g # -O2 #-D__DEBUG__ #
LDLIBS=-lyaooc -lpcre2-8
LDFLAGS=-L${YAOOC_ROOT}/lib # -s

PLATFORM=$(shell uname -s)
ifeq (MINGW,$(findstring MINGW,${PLATFORM}))
CC+=-DWIN32_WINNT=0x0601 -D_WIN32_WINNT=0x0601
CFLAGS+=-Id:/local/include -D_POSIX_C_SOURCE
LDFLAGS+=-Ld:/local/lib -D_POSIX_C_SOURCE
LDLIBS+=-lws2_32
EXT=.exe
else
EXT=
ifeq (AIX,$(PLATFORM))
CC =gcc -maix64
CXX =g++ -maix64
LD_OBJECT_MODE=64 ${CXX}
endif
endif
