GPP = g++
LIBS = -lpthread -ltinyozw -lopenzwave -lpthread -ludev
CFLAGS = -DDEBUG
SRCS = FibaroDoorWindow.cpp ZWaveHomeCenter.cpp FibaroPlug.cpp ZWaveController.cpp LinuxHomeCenterBSwitchBSensor.cpp runtime.cpp
OBJS = FibaroDoorWindow.o ZWaveHomeCenter.o FibaroPlug.o ZWaveController.o LinuxHomeCenterBSwitchBSensor.o runtime.o

all : LinuxHomeCenterBSwitchBSensor

.cpp.o :
	${GPP} ${CFLAGS} -c $< 

LinuxHomeCenterBSwitchBSensor : $(OBJS)
	$(GPP) -g -o $@ $(OBJS) $(LIBS) -lm

clean:
	rm -f *.o *~ LinuxHomeCenterBSwitchBSensor