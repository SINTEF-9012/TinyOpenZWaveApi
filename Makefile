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

DEBUG_CFLAGS    := -Wall -Wno-unknown-pragmas -Wno-inline -Wno-format -fpermissive -g -DDEBUG
RELEASE_CFLAGS  := -Wall -Wno-unknown-pragmas -Wno-format -fpermissive -O3 -DNDEBUG

DEBUG_LDFLAGS	:= -g

# Change for DEBUG or RELEASE
CFLAGS	:= -c $(DEBUG_CFLAGS)
LDFLAGS	:= $(DEBUG_LDFLAGS)

OPENZWAVE := ./open-zwave
TINYOPENZWAVE := ./tiny-open-zwave-api

INCLUDES := -I $(OPENZWAVE)/cpp/src -I $(OPENZWAVE)/cpp/src/command_classes/ \
	-I $(OPENZWAVE)/cpp/src/value_classes/ -I $(OPENZWAVE)/cpp/src/platform/ \
	-I $(OPENZWAVE)/cpp/src/platform/unix -I $(OPENZWAVE)/cpp/tinyxml/ \

# Remove comment below for gnutls support
GNUTLS := #-lgnutls

LIBZWAVE := $(wildcard $(OPENZWAVE)/cpp/lib/linux/*.a)
LIBUSB := -ludev
LIBS := $(LIBZWAVE) $(GNUTLS) $(LIBMICROHTTPD) -pthread $(LIBUSB)

all : run

%.o : %.cpp
	$(CXX) $(CFLAGS) $(INCLUDES) -o $@ $<

%.o : %.c
	$(CXX) $(CFLAGS) $(INCLUDES) -o $@ $<

$(TINYOPENZWAVE)/Api.o : $(TINYOPENZWAVE)/Api.h $(TINYOPENZWAVE)/libs/Utility.h $(TINYOPENZWAVE)/libs/DomoZWave.h \
	$(TINYOPENZWAVE)/devices/TinyController.h $(TINYOPENZWAVE)/devices/Device.h \
	$(TINYOPENZWAVE)/devices/BinarySwitch.h $(OPENZWAVE)/cpp/src/Options.h $(OPENZWAVE)/cpp/src/Manager.h \
	$(OPENZWAVE)/cpp/src/Node.h $(OPENZWAVE)/cpp/src/Group.h \
	$(OPENZWAVE)/cpp/src/Notification.h $(OPENZWAVE)/cpp/src/platform/Log.h \

$(TINYOPENZWAVE)/libs/Utility.o : $(TINYOPENZWAVE)/libs/Utility.h \
	$(OPENZWAVE)/cpp/src/Options.h $(OPENZWAVE)/cpp/src/Manager.h \
	$(OPENZWAVE)/cpp/src/Node.h $(OPENZWAVE)/cpp/src/Group.h \
	$(OPENZWAVE)/cpp/src/Notification.h $(OPENZWAVE)/cpp/src/platform/Log.h \
	
$(TINYOPENZWAVE)/libs/DomoZWave.o : $(TINYOPENZWAVE)/libs/DomoZWave.h \
	$(TINYOPENZWAVE)/libs/Utility.h $(TINYOPENZWAVE)/devices/Device.h \
	$(OPENZWAVE)/cpp/src/Options.h $(OPENZWAVE)/cpp/src/Manager.h \
	$(OPENZWAVE)/cpp/src/Node.h $(OPENZWAVE)/cpp/src/Group.h \
	$(OPENZWAVE)/cpp/src/Notification.h $(OPENZWAVE)/cpp/src/platform/Log.h \
	
$(TINYOPENZWAVE)/devices/TinyController.o : $(TINYOPENZWAVE)/devices/TinyController.h \
	$(TINYOPENZWAVE)/libs/Utility.h $(TINYOPENZWAVE)/libs/DomoZWave.h \
	$(TINYOPENZWAVE)/devices/Device.h $(OPENZWAVE)/cpp/src/Options.h $(OPENZWAVE)/cpp/src/Manager.h \
	$(OPENZWAVE)/cpp/src/Node.h $(OPENZWAVE)/cpp/src/Group.h \
	$(OPENZWAVE)/cpp/src/Notification.h $(OPENZWAVE)/cpp/src/platform/Log.h \
	
$(TINYOPENZWAVE)/devices/Device.o : $(TINYOPENZWAVE)/devices/Device.h \
	$(TINYOPENZWAVE)/devices/TinyController.h $(TINYOPENZWAVE)/libs/Utility.h $(TINYOPENZWAVE)/libs/DomoZWave.h \
	$(OPENZWAVE)/cpp/src/value_classes/ValueID.h $(OPENZWAVE)/cpp/src/Node.h $(OPENZWAVE)/cpp/src/platform/Log.h \

$(TINYOPENZWAVE)/devices/BinarySwitch.o : $(TINYOPENZWAVE)/devices/BinarySwitch.h $(TINYOPENZWAVE)/devices/TinyController.h \
	$(TINYOPENZWAVE)/libs/Utility.h $(TINYOPENZWAVE)/libs/DomoZWave.h $(OPENZWAVE)/cpp/src/Options.h $(OPENZWAVE)/cpp/src/Manager.h \
	$(OPENZWAVE)/cpp/src/Node.h $(OPENZWAVE)/cpp/src/Group.h $(OPENZWAVE)/cpp/src/Notification.h $(OPENZWAVE)/cpp/src/platform/Log.h \


run : run.o $(TINYOPENZWAVE)/Api.o $(TINYOPENZWAVE)/libs/Utility.o $(TINYOPENZWAVE)/libs/DomoZWave.o $(TINYOPENZWAVE)/devices/TinyController.o \
	$(TINYOPENZWAVE)/devices/Device.o $(TINYOPENZWAVE)/devices/BinarySwitch.o
		$(LD) -o $@ $(LDFLAGS) run.o $(TINYOPENZWAVE)/Api.o  $(TINYOPENZWAVE)/libs/Utility.o $(TINYOPENZWAVE)/libs/DomoZWave.o \
			$(TINYOPENZWAVE)/devices/TinyController.o $(TINYOPENZWAVE)/devices/Device.o $(TINYOPENZWAVE)/devices/BinarySwitch.o $(LIBS) \
	
clean:
	rm -rf run *.o $(TINYOPENZWAVE)/*.o $(TINYOPENZWAVE)/libs/*.o $(TINYOPENZWAVE)/devices/*.o \
		$(TINYOPENZWAVE)/*.xml  $(TINYOPENZWAVE)/*.txt $(TINYOPENZWAVE)/*.log *.xml *.txt *.log \
