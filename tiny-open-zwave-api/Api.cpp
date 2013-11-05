#include <string>
#include <iostream>

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <getopt.h>
#include <time.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>


#include "Api.h"
#include "libs/Utility.h"
#include "libs/DomoZWave.h"
#include "devices/TinyController.h"
#include "devices/Device.h"
#include "devices/BinarySwitch.h"

#include "Options.h"
#include "Manager.h"
#include "Node.h"
#include "Group.h"
#include "Notification.h"
#include "Log.h"

using namespace TinyOpenZWaveApi;

pthread_mutex_t nlock = PTHREAD_MUTEX_INITIALIZER;


//START: this should be removed in final version just for testing
BinarySwitch* s;
const char* port = "/dev/ttyUSB0";
char const* config = "./config/";
char const* zwdir = "";
char const* domo_log = "./DomoZWave_Log";
bool const enableLog = true;
bool const enableZWLog = false;
int const polltime = 0;
//END: this should be removed in final version just for testing

void OnNotification (Notification const* _notification, void* _context)
{

  ValueID id = _notification->GetValueID();
  switch (_notification->GetType()) {
	  case Notification::Type_ValueAdded:
		Log::Write(LogLevel_Info, "Notification: Value Added Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   genreToStr(id.GetGenre()), cclassToStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), typeToStr(id.GetType()));
		pthread_mutex_lock(&nlock);;
		ZNode::addValue(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_ValueRemoved:
		Log::Write(LogLevel_Info, "Notification: Value Removed Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   genreToStr(id.GetGenre()), cclassToStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), typeToStr(id.GetType()));
		pthread_mutex_lock(&nlock);
		ZNode::removeValue(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_ValueChanged:
		Log::Write(LogLevel_Info, "Notification: Value Changed Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   genreToStr(id.GetGenre()), cclassToStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), typeToStr(id.GetType()));
		pthread_mutex_lock(&nlock);
		ZNode::changeValue(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_ValueRefreshed:
		Log::Write(LogLevel_Info, "Notification: Value Refreshed Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   genreToStr(id.GetGenre()), cclassToStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), typeToStr(id.GetType()));
		break;
	  case Notification::Type_Group:
		{
		  Log::Write(LogLevel_Info, "Notification: Group Home 0x%08x Node %d Group %d",
			 _notification->GetHomeId(), _notification->GetNodeId(), _notification->GetGroupIdx());
		}
		break;
	  case Notification::Type_NodeNew:
		Log::Write(LogLevel_Info, "Notification: Node New Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   genreToStr(id.GetGenre()), cclassToStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), typeToStr(id.GetType()));
		break;
	  case Notification::Type_NodeAdded:
		Log::Write(LogLevel_Info, "Notification: Node Added Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   genreToStr(id.GetGenre()), cclassToStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), typeToStr(id.GetType()));
	    pthread_mutex_lock(&nlock);
	    ZNode::addNode(_notification);
	    pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_NodeRemoved:
		Log::Write(LogLevel_Info, "Notification: Node Removed Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   genreToStr(id.GetGenre()), cclassToStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), typeToStr(id.GetType()));
		pthread_mutex_lock(&nlock);
		ZNode::removeNode(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_NodeProtocolInfo:
		Log::Write(LogLevel_Info, "Notification: Node Protocol Info Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   genreToStr(id.GetGenre()), cclassToStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), typeToStr(id.GetType()));
		pthread_mutex_lock(&nlock);
		ZNode::updateNodeProtocolInfo(_notification->GetHomeId(), _notification->GetNodeId());
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_NodeNaming:
		Log::Write(LogLevel_Info, "Notification: Node Naming Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   genreToStr(id.GetGenre()), cclassToStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), typeToStr(id.GetType()));
		break;
	  case Notification::Type_NodeEvent:
		Log::Write(LogLevel_Info, "Notification: Node Event Home %08x Node %d Status %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(), _notification->GetEvent(),
			   genreToStr(id.GetGenre()), cclassToStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), typeToStr(id.GetType()));
		pthread_mutex_lock(&nlock);
		ZNode::updateNodeEvent(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_PollingDisabled:
		Log::Write(LogLevel_Info, "Notification: Polling Disabled Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   genreToStr(id.GetGenre()), cclassToStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), typeToStr(id.GetType()));
		break;
	  case Notification::Type_PollingEnabled:
		Log::Write(LogLevel_Info, "Notification: Polling Enabled Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   genreToStr(id.GetGenre()), cclassToStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), typeToStr(id.GetType()));
		break;
	  case Notification::Type_SceneEvent:
		Log::Write(LogLevel_Info, "Notification: Scene Event Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s Scene Id %d",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   genreToStr(id.GetGenre()), cclassToStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), typeToStr(id.GetType()), _notification->GetSceneId());
		break;
	  case Notification::Type_CreateButton:
		Log::Write(LogLevel_Info, "Notification: Create button Home %08x Node %d Button %d",
			   _notification->GetHomeId(), _notification->GetNodeId(), _notification->GetButtonId());
		break;
	  case Notification::Type_DeleteButton:
		Log::Write(LogLevel_Info, "Notification: Delete button Home %08x Node %d Button %d",
			   _notification->GetHomeId(), _notification->GetNodeId(), _notification->GetButtonId());
		break;
	  case Notification::Type_ButtonOn:
		Log::Write(LogLevel_Info, "Notification: Button On Home %08x Node %d Button %d",
			   _notification->GetHomeId(), _notification->GetNodeId(), _notification->GetButtonId());
		break;
	  case Notification::Type_ButtonOff:
		Log::Write(LogLevel_Info, "Notification: Button Off Home %08x Node %d Button %d",
			   _notification->GetHomeId(), _notification->GetNodeId(), _notification->GetButtonId());
		break;
	  case Notification::Type_DriverReady:
		Log::Write(LogLevel_Info, "Notification: Driver Ready, homeId %08x, nodeId %d", _notification->GetHomeId(),
			   _notification->GetNodeId());
		pthread_mutex_lock(&nlock);
		ZNode::controllerReady(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_DriverFailed:
		Log::Write(LogLevel_Info, "Notification: Driver Failed, homeId %08x", _notification->GetHomeId());
		break;
	  case Notification::Type_DriverReset:
		Log::Write(LogLevel_Info, "Notification: Driver Reset, homeId %08x", _notification->GetHomeId());
		break;
	  case Notification::Type_EssentialNodeQueriesComplete:
		Log::Write(LogLevel_Info, "Notification: Essential Node %d Queries Complete", _notification->GetNodeId());
		break;
	  case Notification::Type_NodeQueriesComplete:
		Log::Write(LogLevel_Info, "Notification: Node %d Queries Complete", _notification->GetNodeId());
		break;
	  case Notification::Type_AwakeNodesQueried:
		Log::Write(LogLevel_Info, "Notification: Awake Nodes Queried");
		break;
	  case Notification::Type_AllNodesQueriedSomeDead:
		Log::Write(LogLevel_Info, "Notification: Awake Nodes Queried Some Dead");
		pthread_mutex_lock(&nlock);
		ZNode::allNodeQueriedSomeDead(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_AllNodesQueried:
		Log::Write(LogLevel_Info, "Notification: All Nodes Queried");
		pthread_mutex_lock(&nlock);
		ZNode::allNodeQueried(_notification);
		pthread_mutex_unlock(&nlock);
		OpenZWaveFacade::ready();
		break;
	  case Notification::Type_Notification:
		switch (_notification->GetNotification()) {
			case Notification::Code_MsgComplete:
			  Log::Write(LogLevel_Info, "Notification: Notification home %08x node %d Message Complete",
				_notification->GetHomeId(), _notification->GetNodeId(), _notification->GetNotification());
			  pthread_mutex_lock(&nlock);
			  ZNode::messageComplete(_notification);
			  pthread_mutex_unlock(&nlock);
			  break;
			case Notification::Code_Timeout:
			  Log::Write(LogLevel_Info, "Notification: Notification home %08x node %d Timeout",
				_notification->GetHomeId(), _notification->GetNodeId(), _notification->GetNotification());
			  break;
			case Notification::Code_NoOperation:
			  Log::Write(LogLevel_Info, "Notification: Notification home %08x node %d No Operation Message Complete",
				_notification->GetHomeId(), _notification->GetNodeId(), _notification->GetNotification());
			  break;
			case Notification::Code_Awake:
			  Log::Write(LogLevel_Info, "Notification: Notification home %08x node %d Awake",
				_notification->GetHomeId(), _notification->GetNodeId(), _notification->GetNotification());
			  pthread_mutex_lock(&nlock);
			  ZNode::messageAwake(_notification);
			  pthread_mutex_unlock(&nlock);
			  break;
			case Notification::Code_Sleep:
			  Log::Write(LogLevel_Info, "Notification: Notification home %08x node %d Sleep",
				_notification->GetHomeId(), _notification->GetNodeId(), _notification->GetNotification());
			  break;
			case Notification::Code_Dead:
			  Log::Write(LogLevel_Info, "Notification: Notification home %08x node %d Dead",
				_notification->GetHomeId(), _notification->GetNodeId(), _notification->GetNotification());
			  break;
			case Notification::Code_Alive:
				Log::Write(LogLevel_Info, "Notification: Notification home %08x node %d Alive",
								_notification->GetHomeId(), _notification->GetNodeId(), _notification->GetNotification());
				pthread_mutex_lock(&nlock);
				ZNode::messageAlive(_notification);
				pthread_mutex_unlock(&nlock);
				break;
			default:
			  Log::Write(LogLevel_Info, "Notification: Notification home %08x node %d Unknown %d",
				 _notification->GetHomeId(), _notification->GetNodeId(), _notification->GetNotification());
			  break;
		}
		break;
	  default:
		Log::Write(LogLevel_Info, "Notification: type %d home %08x node %d genre %d class %d instance %d index %d type %d",
			   _notification->GetType(), _notification->GetHomeId(),
			   _notification->GetNodeId(), id.GetGenre(), id.GetCommandClassId(),
			   id.GetInstance(), id.GetIndex(), id.GetType());
		break;
  }
}

void exit_main_handler(int s){
	Log::Write(LogLevel_Info, "Caught signal %d",s);
	Log::Write(LogLevel_Info, "We have registered %d nodes", ZNode::getNodeCount());


	TinyController* api = TinyController::Get();
	api->Destroy();
    exit(1);
}

int main(int argc, char* argv[]){

	OpenZWaveFacade::Init(config, zwdir, domo_log, enableLog, enableZWLog, polltime);
	OpenZWaveFacade::Get()->AddController(port);

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
		if(ch == 'i'){
			Log::Write(LogLevel_Info, "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! init");
			OpenZWaveFacade::Get()->setCurrentController(port);
			s = new BinarySwitch();
			s = s->BinarySwitch::Init(OpenZWaveFacade::Get(),4,1,0);
		}
		if(ch == 'g'){
			Log::Write(LogLevel_Info, "BinarySwitch: the poll interval is  %d ...", Manager::Get()->GetPollInterval());
		}
		if(ch == 'e'){
			Log::Write(LogLevel_Info, "BinarySwitch: enabling  poll");
			ValueID valueId = DomoZWave_GetValueID(s->controller->currentControllerHomeId, s->getComandClass(), s->node->m_nodeId, s->instance, s->index);
			Manager::Get()->EnablePoll(valueId, 1);
		}
		if(ch == 's'){
			Log::Write(LogLevel_Info, "BinarySwitch: setting poll interval");
			Manager::Get()->SetPollInterval(5000, false);
		}
		if(ch == 'q'){
			ValueID valueId = DomoZWave_GetValueID(s->controller->currentControllerHomeId, s->getComandClass(), s->node->m_nodeId, s->instance, s->index);
			DummyValueID dummy;
			if(valueId != *dummy.valueId){
				bool isTurnedOn;
				bool result = Manager::Get()->GetValueAsBool(valueId, &isTurnedOn);
				if(!result){
					Log::Write(LogLevel_Error, "default value is not requested...");
				}else{
					Log::Write(LogLevel_Error, "the value is %i...", isTurnedOn);
				}
			}else{
				Log::Write(LogLevel_Error, "can not find ValueID for"
						"Home 0x%08x Node %d Class %s Instance %d Index %d",
						s->controller->currentControllerHomeId, s->node->m_nodeId,
						s->getComandClass(), s->instance, s->index);
			}
		}
	}
	return 0;
}

void OpenZWaveFacade::ready(){
	cout << "READY!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
}

TinyController* OpenZWaveFacade::Init(char const* config_name, char const* zw_dir,
		char const* domo_log, bool const enableLog,
		bool const enableOZdebug, int polltime){
	return TinyController::Init(OnNotification, config_name, zw_dir, domo_log, enableLog, enableOZdebug, polltime);
}

TinyController* OpenZWaveFacade::Get(){
	TinyController *controller = TinyController::Get();
	if(controller == NULL){
		Log::Write(LogLevel_Info, "OpenZWaveFacade::Get(): controller is not initialized, call OpenZWaveFacade::Init first");
	}
	return controller;
}
