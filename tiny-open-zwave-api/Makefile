#
# Makefile for TinyOpenzWaveLib
# Anatoly Vasilevskiy and Brice Morin (SINTEF)

# GNU make only

.SUFFIXES:	.cpp .o .a .s

CC     := $(CROSS_COMPILE)gcc
CXX    := $(CROSS_COMPILE)g++
LD     := $(CROSS_COMPILE)g++
AR     := $(CROSS_COMPILE)ar rc
RANLIB := $(CROSS_COMPILE)ranlib

DEBUG_CFLAGS    := -Wall -Wno-unknown-pragmas -Wno-inline -Werror -Wno-format -g -DDEBUG
RELEASE_CFLAGS  := -Wall -Wno-unknown-pragmas -Werror -Wno-format -O3 -DNDEBUG

DEBUG_LDFLAGS	:= -g

# Change for DEBUG or RELEASE
CFLAGS	:= -c $(DEBUG_CFLAGS)
LDFLAGS	:= $(DEBUG_LDFLAGS)

OPENZWAVE := ../open-zwave

INCLUDES := -I $(OPENZWAVE)/cpp/src -I $(OPENZWAVE)/cpp/src/command_classes/ \
	-I $(OPENZWAVE)/cpp/src/value_classes/ -I $(OPENZWAVE)/cpp/src/platform/ \
	-I $(OPENZWAVE)/cpp/src/platform/unix -I $(OPENZWAVE)/cpp/tinyxml/ \

# Remove comment below for gnutls support
GNUTLS := #-lgnutls

LIBZWAVE := $(wildcard $(OPENZWAVE)/cpp/lib/linux/*.a)
LIBUSB := -ludev
LIBS := $(LIBZWAVE) $(GNUTLS) $(LIBMICROHTTPD) -pthread $(LIBUSB)

all : api

%.o : %.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -o $@ $<

%.o : %.c
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $<

Api.o : Api.h ./libs/Utility.h ./libs/DomoZWave.h ./devices/TinyController.h ./devices/Device.h \
	./devices/BinarySwitch.h $(OPENZWAVE)/cpp/src/Options.h $(OPENZWAVE)/cpp/src/Manager.h \
	$(OPENZWAVE)/cpp/src/Node.h $(OPENZWAVE)/cpp/src/Group.h \
	$(OPENZWAVE)/cpp/src/Notification.h $(OPENZWAVE)/cpp/src/platform/Log.h \

./libs/Utility.o : ./libs/Utility.h $(OPENZWAVE)/cpp/src/Options.h $(OPENZWAVE)/cpp/src/Manager.h \
	$(OPENZWAVE)/cpp/src/Node.h $(OPENZWAVE)/cpp/src/Group.h \
	$(OPENZWAVE)/cpp/src/Notification.h $(OPENZWAVE)/cpp/src/platform/Log.h \
	
./libs/DomoZWave.o : ./libs/DomoZWave.h ./libs/Utility.h $(OPENZWAVE)/cpp/src/Options.h $(OPENZWAVE)/cpp/src/Manager.h \
	$(OPENZWAVE)/cpp/src/Node.h $(OPENZWAVE)/cpp/src/Group.h \
	$(OPENZWAVE)/cpp/src/Notification.h $(OPENZWAVE)/cpp/src/platform/Log.h \
	
./devices/TinyController.o : ./devices/TinyController.h ./libs/Utility.h ./libs/DomoZWave.h \
	$(OPENZWAVE)/cpp/src/Options.h $(OPENZWAVE)/cpp/src/Manager.h \
	$(OPENZWAVE)/cpp/src/Node.h $(OPENZWAVE)/cpp/src/Group.h \
	$(OPENZWAVE)/cpp/src/Notification.h $(OPENZWAVE)/cpp/src/platform/Log.h \
	
./devices/Device.o : ./devices/Device.h ./devices/TinyController.h ./libs/Utility.h ./libs/DomoZWave.h \
	$(OPENZWAVE)/cpp/src/value_classes/ValueID.h $(OPENZWAVE)/cpp/src/Node.h $(OPENZWAVE)/cpp/src/platform/Log.h \

./devices/BinarySwitch.o : ./devices/BinarySwitch.h ./devices/TinyController.h ./libs/Utility.h ./libs/DomoZWave.h \
	$(OPENZWAVE)/cpp/src/Options.h $(OPENZWAVE)/cpp/src/Manager.h $(OPENZWAVE)/cpp/src/Node.h $(OPENZWAVE)/cpp/src/Group.h \
	$(OPENZWAVE)/cpp/src/Notification.h $(OPENZWAVE)/cpp/src/platform/Log.h \

api : Api.o ./libs/Utility.o ./libs/DomoZWave.o ./devices/TinyController.o ./devices/Device.o ./devices/BinarySwitch.o
	$(LD) -o $@ $(LDFLAGS) Api.o  ./libs/Utility.o ./libs/DomoZWave.o ./devices/TinyController.o ./devices/Device.o ./devices/BinarySwitch.o $(LIBS)
	
clean:
	rm -rf api *.o ./libs/*.o ./devices/*.o *.xml *.txt *.log
