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
#include "./libs/znode.h"

#include "Options.h"
#include "Manager.h"
#include "Node.h"
#include "Group.h"
#include "Notification.h"
#include "Log.h"

using namespace TinyOpenZWaveApi;
using namespace OpenZWave;

uint32 homeId = 0;
uint8 nodeId = 0;
pthread_mutex_t nlock = PTHREAD_MUTEX_INITIALIZER;
//static pthread_mutex_t g_criticalSection;

void OnNotification (Notification const* _notification, void* _context)
{

  ValueID id = _notification->GetValueID();
  switch (_notification->GetType()) {
	  case Notification::Type_ValueAdded:
		Log::Write(LogLevel_Info, "Notification: Value Added Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), valueTypeStr(id.GetType()));
		break;
	  case Notification::Type_ValueRemoved:
		Log::Write(LogLevel_Info, "Notification: Value Removed Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), valueTypeStr(id.GetType()));
		break;
	  case Notification::Type_ValueChanged:
		Log::Write(LogLevel_Info, "Notification: Value Changed Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), valueTypeStr(id.GetType()));
		break;
	  case Notification::Type_ValueRefreshed:
		Log::Write(LogLevel_Info, "Notification: Value Refreshed Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), valueTypeStr(id.GetType()));
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
			   valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), valueTypeStr(id.GetType()));
		break;
	  case Notification::Type_NodeAdded:
		Log::Write(LogLevel_Info, "Notification: Node Added Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), valueTypeStr(id.GetType()));
	    pthread_mutex_lock(&nlock);
	    new ZNode(_notification->GetNodeId());
	    pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_NodeRemoved:
		Log::Write(LogLevel_Info, "Notification: Node Removed Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), valueTypeStr(id.GetType()));
		break;
	  case Notification::Type_NodeProtocolInfo:
		Log::Write(LogLevel_Info, "Notification: Node Protocol Info Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), valueTypeStr(id.GetType()));
		break;
	  case Notification::Type_NodeNaming:
		Log::Write(LogLevel_Info, "Notification: Node Naming Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), valueTypeStr(id.GetType()));
		break;
	  case Notification::Type_NodeEvent:
		Log::Write(LogLevel_Info, "Notification: Node Event Home %08x Node %d Status %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(), _notification->GetEvent(),
			   valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), valueTypeStr(id.GetType()));
		break;
	  case Notification::Type_PollingDisabled:
		Log::Write(LogLevel_Info, "Notification: Polling Disabled Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), valueTypeStr(id.GetType()));
		break;
	  case Notification::Type_PollingEnabled:
		Log::Write(LogLevel_Info, "Notification: Polling Enabled Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), valueTypeStr(id.GetType()));
		break;
	  case Notification::Type_SceneEvent:
		Log::Write(LogLevel_Info, "Notification: Scene Event Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s Scene Id %d",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), valueTypeStr(id.GetType()), _notification->GetSceneId());
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
	    homeId = _notification->GetHomeId();
	    nodeId = _notification->GetNodeId();
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
		break;
	  case Notification::Type_AllNodesQueried:
		Log::Write(LogLevel_Info, "Notification: All Nodes Queried");
		break;
	  case Notification::Type_Notification:
		switch (_notification->GetNotification()) {
			case Notification::Code_MsgComplete:
			  Log::Write(LogLevel_Info, "Notification: Notification home %08x node %d Message Complete",
				_notification->GetHomeId(), _notification->GetNodeId(), _notification->GetNotification());
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
			  break;
			case Notification::Code_Sleep:
			  Log::Write(LogLevel_Info, "Notification: Notification home %08x node %d Sleep",
				_notification->GetHomeId(), _notification->GetNodeId(), _notification->GetNotification());
			  break;
			case Notification::Code_Dead:
			  Log::Write(LogLevel_Info, "Notification: Notification home %08x node %d Dead",
				_notification->GetHomeId(), _notification->GetNodeId(), _notification->GetNotification());
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

TinyController* TinyController::s_instance = NULL;
string TinyController::port = "";

int main(int argc, char* argv[]){
	string port = "/dev/ttyUSB0";
	TinyController* api = TinyController::Init(port);

	BinarySwitch* s = new BinarySwitch();
	s = s->BinarySwitch::Init(api,0,0,0);
	s->turnOn();

	//wait for 2 seconds
	struct timeval tv;
        tv.tv_sec = 2;
        tv.tv_usec = 0;
        select(0, NULL, NULL, NULL, &tv);

	s->turnOff();

	struct sigaction sigIntHandler;
	sigIntHandler.sa_handler = exit_main_handler;
	sigemptyset(&sigIntHandler.sa_mask);
	sigIntHandler.sa_flags = 0;
	sigaction(SIGINT, &sigIntHandler, NULL);
	while (1);
	return 0;
}

//TinyController

TinyController* TinyController::Init(string port){
	TinyController::port = port;
	if(s_instance == NULL){
		Log::Write(LogLevel_Info, "initializing TinyController");
		cout << "initializing TinyController" << endl;
		s_instance = new TinyController();
	}
	return s_instance;
}

//-----------------------------------------------------------------------------
//	<TinyController::Destroy>
//	Static method to destroy the singleton.
//-----------------------------------------------------------------------------
void TinyController::Destroy()
{
	delete s_instance;
	s_instance = NULL;
}

//-----------------------------------------------------------------------------
// <TinyController::TinyController>
// Constructor
//-----------------------------------------------------------------------------
TinyController::TinyController() {

	Options::Create("./config/", "", "--SaveConfiguration=true --DumpTriggerLevel=0");
	Options::Get()->Lock();

	Manager::Create();
	Log::Write(LogLevel_Info, "initializing TinyController");
	Manager::Get()->AddWatcher(OnNotification, NULL);

	if(strcasecmp(port.c_str(), "usb") == 0) {
		Manager::Get()->AddDriver("HID TinyController", Driver::ControllerInterface_Hid);
	}else{
		Manager::Get()->AddDriver(port);
	}

	s_instance = this;
}

//-----------------------------------------------------------------------------
// <TinyController::TinyController>
// Destructor
//-----------------------------------------------------------------------------
TinyController::~TinyController() {
	Log::Write(LogLevel_Info, "destroying TinyController object");
	if(strcasecmp(port.c_str(), "usb") == 0){
		Manager::Get()->RemoveDriver("HID TinyController");
	}else{
		Manager::Get()->RemoveDriver(port);
	}
	Manager::Get()->RemoveWatcher(OnNotification, NULL);
	Manager::Destroy();
	Options::Destroy();
}

//BinarySwitch

Device* Device::Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index){
	this->controller = controller;	
	this->_nodeId = _nodeId;
	this->_instance = _instance;
	this->_index = _index;
	return this;
}

//-----------------------------------------------------------------------------
//	<BinarySwitch::Destroy>
//	Static method to destroy the singleton.
//-----------------------------------------------------------------------------
void BinarySwitch::Destroy()
{
	delete this;
}

//-----------------------------------------------------------------------------
// <BinarySwitch::BinarySwitch>
// Constructor
//-----------------------------------------------------------------------------
BinarySwitch::BinarySwitch() {

}

//-----------------------------------------------------------------------------
// <BinarySwitch::BinarySwitch>
// Destructor
//-----------------------------------------------------------------------------
BinarySwitch::~BinarySwitch() {
	BinarySwitch::Destroy();
}

void BinarySwitch::turnOn(){	
	/*pthread_mutex_lock(&g_criticalSection);
	Manager::Get()->SetNodeOn(_index, _nodeId);
	pthread_mutex_unlock(&g_criticalSection);*/

	cout << "turn on" << endl;
}

void BinarySwitch::turnOff(){
	/*pthread_mutex_lock(&g_criticalSection);
	Manager::Get()->SetNodeOff(_index, _nodeId);
	pthread_mutex_unlock(&g_criticalSection);*/

	cout << "turn off" << endl;
}
