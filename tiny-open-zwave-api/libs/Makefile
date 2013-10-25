#
# Makefile for OpenzWave Linux applications
# Greg Satz

# GNU make only

.SUFFIXES:	.cpp .o .a .s

CC     := gcc
CXX    := g++
LD     := g++
AR     := ar rc
RANLIB := ranlib

DEBUG_CFLAGS    := -Wall -Wno-format -g -DDEBUG -fPIC
RELEASE_CFLAGS  := -Wall -Wno-unknown-pragmas -Wno-format -O3

DEBUG_LDFLAGS	:= -g

# Change for DEBUG or RELEASE
CFLAGS	:= -c $(DEBUG_CFLAGS)
LDFLAGS	:= $(DEBUG_LDFLAGS)

OPENZWAVE := ../../open-zwave

INCLUDES	:= -I $(OPENZWAVE)/cpp/src -I $(OPENZWAVE)/cpp/src/command_classes/ -I $(OPENZWAVE)/cpp/src/value_classes/ \
	-I $(OPENZWAVE)/cpp/src/platform/ -I $(OPENZWAVE)/cpp/src/platform/unix -I $(OPENZWAVE)/cpp/tinyxml/ -I $(OPENZWAVE)/cpp/build/linux/
LIBS := $(wildcard $(OPENZWAVE)/cpp/lib/linux/*.a) -lxmlrpc -lxmlrpc_client -lxmlrpc_xmlparse -lxmlrpc_util -lxmlrpc_xmltok

%.o : %.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -o $@ $<

DomoZWave.o : DomoZWave.h $(OPENZWAVE)/cpp/src/Options.h $(OPENZWAVE)/cpp/src/Manager.h \
	$(OPENZWAVE)/cpp/src/Node.h $(OPENZWAVE)/cpp/src/Group.h \
	$(OPENZWAVE)/cpp/src/Notification.h $(OPENZWAVE)/cpp/src/platform/Log.h \

all: libdomozwave.so

libdomozwave.so: DomoZWave.o
	$(LD) -o $@ $(LDFLAGS) $< $(LIBS) -pthread -shared -ludev

clean:
	rm -f libdomozwave.so DomoZWave.o
install:
	cp libdomozwave.so /usr/local/lib
	ldconfig
