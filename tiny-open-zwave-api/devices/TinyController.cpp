/*
 * TinyController.cpp
 *
 *  Created on: Oct 31, 2013
 *      Author: vassik
 */

#include <string>
#include <iostream>

#include "openzwave/Options.h"
#include "openzwave/Manager.h"
#include "openzwave/Node.h"
#include "openzwave/Group.h"
#include "openzwave/Notification.h"
#include "openzwave/Log.h"

#include "TinyController.h"
#include "../libs/DomoZWave.h"
#include "../libs/Utility.h"
#include "../devices/Device.h"

#include "../libs/ZNode.h"


using namespace OpenZWave;

TinyController* TinyController::s_instance = NULL;
uint32 TinyController::currentControllerHomeId = 0;
uint8 TinyController::currentControllerNodeId = 0;

pthread_mutex_t nlock = PTHREAD_MUTEX_INITIALIZER;

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
		pthread_mutex_lock(&nlock);
		ZNode::refreshedValue(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_Group:
		{
		  Log::Write(LogLevel_Info, "Notification: Group Home 0x%08x Node %d Group %d",
			 _notification->GetHomeId(), _notification->GetNodeId(), _notification->GetGroupIdx());
		}
		pthread_mutex_lock(&nlock);
		ZNode::typeGroup(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_NodeNew:
		Log::Write(LogLevel_Info, "Notification: Node New Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   genreToStr(id.GetGenre()), cclassToStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), typeToStr(id.GetType()));
		pthread_mutex_lock(&nlock);
		ZNode::newNode(_notification);
		pthread_mutex_unlock(&nlock);
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
		TinyController::Get()->controllerReadyCallback->fn_callback(TinyController::Get()->controllerReadyCallback->instance);
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
		//TinyController::Get()->controllerReadyCallback->fn_callback(TinyController::Get()->controllerReadyCallback->instance);
		pthread_mutex_unlock(&nlock);
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
		Log::Write(LogLevel_Info, "Notification: Unhandled Notification (type %d home %08x node %d) ValueID (genre %d class %d instance %d index %d type %d)",
			   _notification->GetType(), _notification->GetHomeId(),
			   _notification->GetNodeId(), id.GetGenre(), id.GetCommandClassId(),
			   id.GetInstance(), id.GetIndex(), id.GetType());
		break;
  }
}


//-----------------------------------------------------------------------------
//	<TinyController::SetConfiguration>
//	Static method to init the singleton.
//-----------------------------------------------------------------------------
TinyController* TinyController::SetConfiguration(
		char const* config_name, char const* zw_dir,
		char const* domo_log, bool const enableLog,
		bool const enableOZdebug, int polltime){
	if(s_instance == NULL){
		Log::Write(LogLevel_Info, "TinyController::Init() : initializing TinyController");
		s_instance = new TinyController(config_name, zw_dir, domo_log, enableLog, enableOZdebug, polltime);
	}
	return s_instance;
}

//-----------------------------------------------------------------------------
//	<TinyController::AddController>
//	Static method to add controller and complete initialization
//-----------------------------------------------------------------------------
void TinyController::AddController(char const* port){
	ZWave_AddSerialPort(port);
}


//-----------------------------------------------------------------------------
//	<TinyController::setCurrentController>
//	Static method to set current controller
//-----------------------------------------------------------------------------
void TinyController::setCurrentController(char const* port){
	list<m_structCtrl*>& g_allControllers = ZWave_GetGControllers();
	for(list<m_structCtrl*>::iterator it = g_allControllers.begin(); it != g_allControllers.end(); ++it){
		uint32 homeId = (*it)->m_homeId;
		string controllerPath = Manager::Get()->GetControllerPath(homeId);
		string portName = port;
		if(portName == controllerPath){
			TinyController::currentControllerHomeId = homeId;
			TinyController::currentControllerNodeId = (*it)->m_nodeId;
			Log::Write(LogLevel_Info, "TinyController::setCurrentController : %s controller with homeId %08x is set as default", port, currentControllerHomeId);
			break;
		}
	}
	if(currentControllerHomeId == 0){
		Log::Write(LogLevel_Info, "TinyController::setCurrentController : %s controller is not found", port);
	}
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
TinyController::TinyController(char const* config_name, char const* zw_dir,
		char const* domo_log, bool const enableLog,
		bool const enableOZdebug, int polltime) {
	ZWave_Init(domo_log, enableLog);
	Options::Create(config_name, zw_dir, "");

	if (enableOZdebug)
	{
		Options::Get()->AddOptionInt("SaveLogLevel", LogLevel_Detail);
	  	Options::Get()->AddOptionInt("QueueLogLevel", LogLevel_Debug);
	   	Options::Get()->AddOptionInt("DumpTriggerLevel", LogLevel_Error);
	}

	if(polltime != 0){
		Options::Get()->AddOptionInt("PollInterval", polltime);
		Options::Get()->AddOptionBool("IntervalBetweenPolls", true);
		Options::Get()->AddOptionBool("SuppressValueRefresh", false);
		Options::Get()->AddOptionBool("PerformReturnRoutes", false);
	}
	Options::Get()->Lock();

	controllerReadyCallback = NULL;
	controllerFailedCallback = NULL;
	controllerResetCallback = NULL;
	allNodeQueriedCallback = NULL;
	awakedNodesQueriedCallback = NULL;
	allNodesQueriedSomeDeadCallback = NULL;
	s_instance = this;
}

//-----------------------------------------------------------------------------
// <TinyController::start>
// Create manager and begin node interviewing
//-----------------------------------------------------------------------------

void TinyController::start(){
	Manager::Create();
	Manager::Get()->AddWatcher(OnNotification, NULL);
}

//-----------------------------------------------------------------------------
// <TinyController::addDevice>
//add device to the list
//-----------------------------------------------------------------------------

void TinyController::addDevice(Device* device){
	devices.push_back(device);
	pthread_mutex_lock(&nlock);
	ZNode::deviceAdded(device);
	pthread_mutex_unlock(&nlock);
}

//-----------------------------------------------------------------------------
// <TinyController::getDevices>
//get devices from the list
//-----------------------------------------------------------------------------

list<Device*> TinyController::getDevices(){
	return devices;
}

//-----------------------------------------------------------------------------
// <TinyController::~TinyController>
// Destructor
//-----------------------------------------------------------------------------
TinyController::~TinyController() {
	Log::Write(LogLevel_Info, "destroying TinyController object");
	for(list<Device*>::iterator it = devices.begin(); it != devices.end(); ++it){
		(*it)->Destroy();
	}
	ZWave_Destroy();
	Manager::Get()->RemoveWatcher(OnNotification, NULL);
	Manager::Get()->Destroy();
	Options::Get()->Destroy();
}



