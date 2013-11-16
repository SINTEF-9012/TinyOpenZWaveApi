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

#include "tiny-open-zwave-api/Api.h"
#include "tiny-open-zwave-api/libs/Utility.h"
#include "tiny-open-zwave-api/libs/DomoZWave.h"
#include "tiny-open-zwave-api/devices/TinyController.h"
#include "tiny-open-zwave-api/devices/Device.h"
#include "tiny-open-zwave-api/devices/BinarySwitch.h"

#include "Options.h"
#include "Manager.h"
#include "Node.h"
#include "Group.h"
#include "Notification.h"
#include "Log.h"


using namespace TinyOpenZWaveApi;

BinarySwitch* s;
const char* port = "/dev/ttyUSB0";
char const* config = "./tiny-open-zwave-api/config/";
char const* zwdir = "";
char const* domo_log = "./DomoZWave_Log";
bool const enableLog = true;
bool const enableZWLog = false;
int const polltime = 0;


void exit_main_handler(int s){
	cout << "Caught signal on exit" <<endl;
	//Log::Write(LogLevel_Info, "Caught signal %d",s);
	//Log::Write(LogLevel_Info, "We have registered %d nodes", ZNode::getNodeCount());

	TinyController* api = TinyController::Get();
	api->Destroy();
    exit(1);
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
			OpenZWaveFacade::Init(config, zwdir, domo_log, enableLog, enableZWLog, polltime);
			OpenZWaveFacade::Get()->AddController(port);
		}
		if(ch == 'i'){
			cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! init" <<endl;
			OpenZWaveFacade::Get()->setCurrentController(port);
			s = new BinarySwitch();
			s = s->BinarySwitch::Init(OpenZWaveFacade::Get(),5,1,0);
		}
		if(ch == 'g'){
			cout << "BinarySwitch: the poll interval is " << Manager::Get()->GetPollInterval() <<endl;
			//Log::Write(LogLevel_Info, "BinarySwitch: the poll interval is  %d ...", Manager::Get()->GetPollInterval());
		}
		if(ch == 'e'){
			cout << "BinarySwitch: enabling  poll" <<endl;
			//Log::Write(LogLevel_Info, "BinarySwitch: enabling  poll");
			ValueID valueId = DomoZWave_GetValueID(s->controller->currentControllerHomeId, s->getComandClass(), s->node->m_nodeId, s->instance, s->index);
			Manager::Get()->EnablePoll(valueId, 1);
		}
		if(ch == 's'){
			cout << "BinarySwitch: setting poll interval" <<endl;
			//Log::Write(LogLevel_Info, "BinarySwitch: setting poll interval");
			Manager::Get()->SetPollInterval(5000, false);
		}
		if(ch == 'q'){
			ValueID valueId = DomoZWave_GetValueID(s->controller->currentControllerHomeId, s->getComandClass(), s->node->m_nodeId, s->instance, s->index);
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
