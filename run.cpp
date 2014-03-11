#include <stdio.h>
#include <string>
#include <iostream>

#include <cstdarg>

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <getopt.h>
#include <time.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>

#include "tiny-open-zwave-api/TinyZWaveFacade.h"

#include "tiny-open-zwave-api/devices/BinarySwitch.h"
#include "tiny-open-zwave-api/devices/MultiLevel.h"
#include "tiny-open-zwave-api/devices/BinarySensor.h"
#include "tiny-open-zwave-api/libs/DomoZWave.h"

#include "tiny-open-zwave-api/libs/Utility.h"


using namespace TinyOpenZWaveApi;

BinarySwitch* s;
MultiLevel* m;
BinarySensor* bs;
const char* port = "/dev/ttyUSB0";
const char* config = "./tiny-open-zwave-api/config/";
const char* zwdir = "";
const char* domo_log = "./DomoZWave_Log";
const bool enableLog = true;
const bool enableZWLog = true;
const int polltime = 0;

void turned_on_callback(void *_instance, ...) {
	printf("THINGML: -> FibaroPlug_send_switch_turned_on\n");
}

// Definition of function turned_off_callback
void turned_off_callback(void *_instance, ...) {
	printf("THINGML: -> FibaroPlug_send_switch_turned_off\n");
}

// Definition of function no_change_callback
void no_change_callback(void *_instance, ...) {
	printf("THINGML: -> FibaroPlug_send_switch_no_change\n");
}

void init_callback(void *_instance, ...) {
	printf("?????????????????????????????????THINGML: -> BinarySwitsh is initialized\n");
}

void init_callback_multilevel(void *_instance, ...) {
	printf("********************************THINGML: -> MultiLevel is initialized\n");
}

void init_callback_binarysensor(void *_instance, ...) {
	printf("********************************THINGML: -> BinarySensor is initialized\n");
}

void value_change_callback_binarysensor(void *_instance, ...) {
    va_list arguments;
    va_start(arguments, _instance);
    int value = va_arg(arguments, int);
    va_end(arguments);
	cout<< "!!!!!!!!!!!!!! value_change_callback_binarysensor is " << value << endl;
}

void value_change_callback_multilevel(void *_instance, ...) {
    va_list arguments;
    va_start(arguments, _instance);
    const char* value = va_arg(arguments, const char*);
    va_end(arguments);
	cout<< "!!!!!!!!!!!!!! value_change_callback_multilevel is " << value << endl;
}

void exit_main_handler(int s){
	cout << "Caught signal on exit" <<endl;
	OpenZWaveFacade::Quite();
    exit(1);
}

void controller_ready(void *param, ...){
	cout<< "!!!!!!!!!!!!!! controller_ready is ready" << endl;
}

void all_nodes_quiried(void *param, ...){
	cout<< "!!!!!!!!!!!!!! all_nodes_quiried" << endl;
}

void node_quiries_completed(void *param, ...){
    va_list arguments;
    va_start(arguments, param);
    int node_id = va_arg(arguments, int);
    va_end(arguments);
	cout<< "!!!!!!!!!!!!!! node_quiries_completed " << node_id << endl;
}

int main(int argc, char* argv[]){
	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = exit_main_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);

	string ch;
	bool loop = true;
	while (loop){
		getline(cin, ch);
		if(ch == "o"){
			s->turnOn();
		}
		if(ch == "f"){
			s->turnOff();
		}
		if(ch == "s"){
			cout << "Start controller" <<endl;
			TinyController* controller = OpenZWaveFacade::GetController(port);
			controller->start();
		}
		if(ch == "c"){
			cout << "Controller init" <<endl;
			ThingMLCallback* controller_ready_callback = new ThingMLCallback(controller_ready, NULL);
			ThingMLCallback* all_nodes_quiried_callback = new ThingMLCallback(all_nodes_quiried, NULL);
			ThingMLCallback* node_quiries_complete_callback = new ThingMLCallback(node_quiries_completed, NULL);
			TinyController* controller = OpenZWaveFacade::CreateController(port);
			controller->setControllerReadyCallback(controller_ready_callback);
			controller->setAllNodeQueriedCallback(all_nodes_quiried_callback);
			controller->setNodeQueriesCompleteCallback(node_quiries_complete_callback);
		}
		if(ch == "i"){
			cout << "OpenZWave init" <<endl;
			/*char value[1024] = "hello";
			char* value_char;
			value_char = (char*) malloc((strlen(value) +1)*sizeof(char));
			snprintf(value_char, strlen(value) +1, "%s\0", value);
			cout << strlen(value_char)  << endl;
			cout << value_char  << endl;
			char dev_value[1024];
			snprintf(dev_value, 1024, "%s", strdup(value));
			cout << strlen(dev_value)  << endl;
			cout << dev_value  << endl;*/
			 /*char szOrbits[] = "686.97 365.24";
			  char* pEnd;
			  float f1, f2;
			  f1 = strtof (szOrbits, NULL);
			  f2 = strtof (pEnd, NULL);
			  printf ("One martian year takes %.2f %.2f Earth years.\n", f1, f2);*/
			OpenZWaveFacade::Init(config, zwdir, domo_log, enableLog, enableZWLog, polltime);

		}
		if(ch == "b"){
			cout << "A binary switch created" <<endl;
			ThingMLCallback* turned_on = new ThingMLCallback(turned_on_callback, NULL);
			ThingMLCallback* turned_off = new ThingMLCallback(turned_off_callback, NULL);
			ThingMLCallback* no_change = new ThingMLCallback(no_change_callback, NULL);

			ThingMLCallback* device_init = new ThingMLCallback(init_callback, NULL);

			s = new BinarySwitch();
			s->setDeviceInitCallback(device_init);
			s->setTurnedOnCallback(turned_on);
			s->setTurnedOffCallback(turned_off);
			s->setNoChangeCallback(no_change);
			s = s->Init(OpenZWaveFacade::GetController(port),2,1,0);
		}
		if(ch == "m"){
			cout << "A multisensor created" <<endl;
			ThingMLCallback* device_init = new ThingMLCallback(init_callback_multilevel, NULL);
			ThingMLCallback* value_change = new ThingMLCallback(value_change_callback_multilevel, NULL);

			m = new MultiLevel();
			m->setDeviceInitCallback(device_init);
			m->setValueUpdatedCallback(value_change);
			m = m->Init(OpenZWaveFacade::GetController(port),2,1,4);
		}
		if(ch == "g"){
			cout << "A multisensor data" <<endl;
			cout << "the value is " << m->getCurrentValue() << endl;
		}
		if(ch == "r"){
			cout << "A multisensor data refresh" <<endl;
			m->refresh();
		}
		if(ch == "bs"){
			cout << "A binary sensor created" <<endl;
			ThingMLCallback* device_init = new ThingMLCallback(init_callback_binarysensor, NULL);
			ThingMLCallback* value_change = new ThingMLCallback(value_change_callback_binarysensor, NULL);

			bs = new BinarySensor();
			bs->setDeviceInitCallback(device_init);
			bs->setValueUpdatedCallback(value_change);
			bs = bs->Init(OpenZWaveFacade::GetController(port),3,1,0);
		}
		if(ch == "bsg"){
			cout << "A binary sensor data" <<endl;
			cout << "the value is " << bs->getCurrentValue() << endl;
		}
		if(ch == "bsr"){
			cout << "A binary sensor data refresh" <<endl;
			bs->refresh();
		}
		if(ch == "q"){
			OpenZWaveFacade::Quite();
			loop = false;
		}
	}
	return 0;
}
