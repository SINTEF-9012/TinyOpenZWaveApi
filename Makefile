#
# Makefile for TinyOpenzWaveLib
# Anatoly Vasilevskiy and Brice Morin (SINTEF)

# GNU make only

.SUFFIXES:	.cpp .o .a .s

CXX    := $(CROSS_COMPILE)g++

DEBUG_CFLAGS    := -Wall -Wno-unknown-pragmas -Wno-inline -Wno-format -g -DDEBUG
RELEASE_CFLAGS  := -Wall -Wno-unknown-pragmas -Wno-format -O3 -DNDEBUG

DEBUG_LDFLAGS	:= -g

# Change for DEBUG or RELEASE
CFLAGS	:= -c $(DEBUG_CFLAGS) -fPIC
LDFLAGS	:= $(DEBUG_LDFLAGS)

OPENZWAVE := ./open-zwave
TINYOPENZWAVE := ./tiny-open-zwave-api

STATIC_LIB_LOCATION = $(TINYOPENZWAVE)/libtinyozw.a
DYNAMIC_LIB_LOCATION = $(TINYOPENZWAVE)/libtinyozw.so

SRC := $(TINYOPENZWAVE)/libs/ZNode.cpp $(TINYOPENZWAVE)/TinyZWaveFacade.cpp $(TINYOPENZWAVE)/libs/Utility.cpp $(TINYOPENZWAVE)/libs/DomoZWave.cpp \
	$(TINYOPENZWAVE)/devices/TinyController.cpp $(TINYOPENZWAVE)/devices/Device.cpp $(TINYOPENZWAVE)/devices/BinarySwitch.cpp \
	$(TINYOPENZWAVE)/observer/NodeSubject.cpp $(TINYOPENZWAVE)/observer/ControllerSubject.cpp

OBJ := $(TINYOPENZWAVE)/libs/ZNode.o $(TINYOPENZWAVE)/TinyZWaveFacade.o $(TINYOPENZWAVE)/libs/Utility.o $(TINYOPENZWAVE)/libs/DomoZWave.o \
	$(TINYOPENZWAVE)/devices/TinyController.o $(TINYOPENZWAVE)/devices/Device.o $(TINYOPENZWAVE)/devices/BinarySwitch.o \
	$(TINYOPENZWAVE)/observer/NodeSubject.o $(TINYOPENZWAVE)/observer/ControllerSubject.o

LIBUSB := -ludev
LIBS := $(GNUTLS) $(LIBMICROHTTPD) -pthread -lopenzwave $(LIBUSB)

all : run staticlib dynamiclib

%.o : %.cpp
	$(CXX) $(CFLAGS) -o $@ $<

run : run.o $(OBJ)
		$(CXX) -o $@ $(LDFLAGS) run.o $(OBJ) $(LIBS)

staticlib : $(OBJS)
	$(AR) rvs $(STATIC_LIB_LOCATION) $(OBJ)

dynamiclib : $(OBJS)
	$(CXX) -shared -o $(DYNAMIC_LIB_LOCATION) $(OBJ)

install: staticlib dynamiclib
	install -d /usr/local
	install -d /usr/local/lib
	install -d /usr/local/include/tinyozw
	install -d /usr/local/include/tinyozw/devices
	install -d /usr/local/include/tinyozw/libs
	install $(DYNAMIC_LIB_LOCATION) /usr/local/lib
	install $(STATIC_LIB_LOCATION) /usr/local/lib
	cp -r $(TINYOPENZWAVE)/*.h /usr/local/include/tinyozw
	cp -r $(TINYOPENZWAVE)/devices/*.h /usr/local/include/tinyozw/devices
	cp -r $(TINYOPENZWAVE)/libs/*.h /usr/local/include/tinyozw/libs

clean :
	rm -rf run *.o $(TINYOPENZWAVE)/*.o $(TINYOPENZWAVE)/libs/*.o $(TINYOPENZWAVE)/devices/*.o $(TINYOPENZWAVE)/observer/*.o \
		$(TINYOPENZWAVE)/*.xml  $(TINYOPENZWAVE)/*.txt $(TINYOPENZWAVE)/*.log *.xml *.txt *.log \
