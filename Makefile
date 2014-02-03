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

SRC := $(TINYOPENZWAVE)/Api.cpp $(TINYOPENZWAVE)/libs/Utility.cpp $(TINYOPENZWAVE)/libs/DomoZWave.cpp \
	$(TINYOPENZWAVE)/devices/TinyController.cpp $(TINYOPENZWAVE)/devices/Device.cpp $(TINYOPENZWAVE)/devices/BinarySwitch.cpp
OBJ := $(TINYOPENZWAVE)/Api.o $(TINYOPENZWAVE)/libs/Utility.o $(TINYOPENZWAVE)/libs/DomoZWave.o \
	$(TINYOPENZWAVE)/devices/TinyController.o $(TINYOPENZWAVE)/devices/Device.o $(TINYOPENZWAVE)/devices/BinarySwitch.o

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

clean :
	rm -rf run *.o $(TINYOPENZWAVE)/*.o $(TINYOPENZWAVE)/libs/*.o $(TINYOPENZWAVE)/devices/*.o \
		$(TINYOPENZWAVE)/*.xml  $(TINYOPENZWAVE)/*.txt $(TINYOPENZWAVE)/*.log *.xml *.txt *.log \
