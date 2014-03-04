#include <stdio.h>
#include <string>
#include <iostream>


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
#include "tiny-open-zwave-api/libs/DomoZWave.h"

#include "tiny-open-zwave-api/libs/Utility.h"


using namespace TinyOpenZWaveApi;

BinarySwitch* s;
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


void exit_main_handler(int s){
	cout << "Caught signal on exit" <<endl;
	//Log::Write(LogLevel_Info, "Caught signal %d",s);
	//Log::Write(LogLevel_Info, "We have registered %d nodes", ZNode::getNodeCount());

	//TinyController* api = TinyController::Get();
	//api->Destroy();
	OpenZWaveFacade::Quite();
    exit(1);
}

void f_function(void *param, ...){
	cout<< "f_function network is ready" << endl;
	//OpenZWaveFacade::Get()->setCurrentController(port);
}

int main(int argc, char* argv[]){
	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = exit_main_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);

	char ch;
	while (1){
		cin >> ch;
		if(ch == 'o'){
			s->turnOn();
		}
		if(ch == 'f'){
			s->turnOff();
		}
		if(ch == 'k'){
			//ThingMLCallback *callback = new ThingMLCallback(f_function, NULL);
			//OpenZWaveFacade::Init(config, zwdir, domo_log, enableLog, enableZWLog, polltime, callback);
			//OpenZWaveFacade::Get()->start();
			//OpenZWaveFacade::Get()->AddController(port);
			TinyController* controller = OpenZWaveFacade::CreateController(port);
			controller->start();

		}
		if(ch == 'i'){
			cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! init" <<endl;
			//OpenZWaveFacade::Get()->setCurrentController(port);
			ThingMLCallback* turned_on = new ThingMLCallback(turned_on_callback, NULL);
			ThingMLCallback* turned_off = new ThingMLCallback(turned_off_callback, NULL);
			ThingMLCallback* no_change = new ThingMLCallback(no_change_callback, NULL);
			s = new BinarySwitch(turned_on, turned_off, no_change);

			//ThingMLCallback *callback = new ThingMLCallback(f_function, NULL);
			OpenZWaveFacade::Init(config, zwdir, domo_log, enableLog, enableZWLog, polltime);

			//s = s->Init(OpenZWaveFacade::Get(),2,1,0);
		}
		if(ch == 'b'){
			cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! another binary switch" <<endl;
			ThingMLCallback* turned_on = new ThingMLCallback(turned_on_callback, NULL);
			ThingMLCallback* turned_off = new ThingMLCallback(turned_off_callback, NULL);
			ThingMLCallback* no_change = new ThingMLCallback(no_change_callback, NULL);
			s = new BinarySwitch(turned_on, turned_off, no_change);
			s = s->Init(OpenZWaveFacade::GetController(port),2,1,0);
		}
		if(ch == 'g'){
			cout << "BinarySwitch: the poll interval is " << Manager::Get()->GetPollInterval() <<endl;
			//Log::Write(LogLevel_Info, "BinarySwitch: the poll interval is  %d ...", Manager::Get()->GetPollInterval());
		}
		if(ch == 'e'){
			cout << "BinarySwitch: enabling  poll" <<endl;
			//Log::Write(LogLevel_Info, "BinarySwitch: enabling  poll");
			ValueID valueId = ZWave_GetValueID(s->controller->controllerHomeId, s->getComandClass(), s->node->m_nodeId, s->instance, s->index);
			Manager::Get()->EnablePoll(valueId, 1);
		}
		if(ch == 's'){
			cout << "BinarySwitch: setting poll interval" <<endl;
			//Log::Write(LogLevel_Info, "BinarySwitch: setting poll interval");
			Manager::Get()->SetPollInterval(5000, false);
		}
		if(ch == 'q'){
			ValueID valueId = ZWave_GetValueID(s->controller->controllerHomeId, s->getComandClass(), s->node->m_nodeId, s->instance, s->index);
			DummyValueID dummy;
			if(valueId != *dummy.valueId){
				bool isTurnedOn;
				bool result = Manager::Get()->GetValueAsBool(valueId, &isTurnedOn);
				if(!result){
					cout << "default value is not requested..." <<endl;
					//Log::Write(LogLevel_Error, "default value is not requested...");
				}else{
					cout << "the value is..." << isTurnedOn <<endl;
					//Log::Write(LogLevel_Error, "the value is %i...", isTurnedOn);
				}
			}else{
				cout << "can not find ValueID for" << endl;
				/*Log::Write(LogLevel_Error, "can not find ValueID for"
						"Home 0x%08x Node %d Class %s Instance %d Index %d",
						s->controller->currentControllerHomeId, s->node->m_nodeId,
						s->getComandClass(), s->instance, s->index);*/
			}
		}
	}
	return 0;
}
