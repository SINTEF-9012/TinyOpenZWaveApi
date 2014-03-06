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
#include "../observer/ControllerSubject.h"
#include "../observer/ControllerObserver.h"


using namespace OpenZWave;


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
		ZNode::AddValue(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_ValueRemoved:
		Log::Write(LogLevel_Info, "Notification: Value Removed Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   genreToStr(id.GetGenre()), cclassToStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), typeToStr(id.GetType()));
		pthread_mutex_lock(&nlock);
		ZNode::RemoveValue(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_ValueChanged:
		Log::Write(LogLevel_Info, "Notification: Value Changed Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   genreToStr(id.GetGenre()), cclassToStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), typeToStr(id.GetType()));
		pthread_mutex_lock(&nlock);
		ZNode::ChangeValue(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_ValueRefreshed:
		Log::Write(LogLevel_Info, "Notification: Value Refreshed Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   genreToStr(id.GetGenre()), cclassToStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), typeToStr(id.GetType()));
		pthread_mutex_lock(&nlock);
		ZNode::RefreshedValue(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_Group:
		{
		  Log::Write(LogLevel_Info, "Notification: Group Home 0x%08x Node %d Group %d",
			 _notification->GetHomeId(), _notification->GetNodeId(), _notification->GetGroupIdx());
		}
		pthread_mutex_lock(&nlock);
		ZNode::TypeGroup(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_NodeNew:
		Log::Write(LogLevel_Info, "Notification: Node New Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   genreToStr(id.GetGenre()), cclassToStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), typeToStr(id.GetType()));
		pthread_mutex_lock(&nlock);
		ZNode::NewNode(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_NodeAdded:
		Log::Write(LogLevel_Info, "Notification: Node Added Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   genreToStr(id.GetGenre()), cclassToStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), typeToStr(id.GetType()));
	    pthread_mutex_lock(&nlock);
	    ZNode::AddNode(_notification);
	    pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_NodeRemoved:
		Log::Write(LogLevel_Info, "Notification: Node Removed Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   genreToStr(id.GetGenre()), cclassToStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), typeToStr(id.GetType()));
		pthread_mutex_lock(&nlock);
		ZNode::RemoveNode(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_NodeProtocolInfo:
		Log::Write(LogLevel_Info, "Notification: Node Protocol Info Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   genreToStr(id.GetGenre()), cclassToStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), typeToStr(id.GetType()));
		pthread_mutex_lock(&nlock);
		ZNode::UpdateNodeProtocolInfo(_notification->GetHomeId(), _notification->GetNodeId());
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
		ZNode::UpdateNodeEvent(_notification);
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
		ZNode::ControllerReady(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_DriverFailed:
		Log::Write(LogLevel_Info, "Notification: Driver Failed, homeId %08x", _notification->GetHomeId());
		pthread_mutex_lock(&nlock);
		ZNode::ControllerFailed(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_DriverReset:
		Log::Write(LogLevel_Info, "Notification: Driver Reset, homeId %08x", _notification->GetHomeId());
		pthread_mutex_lock(&nlock);
		ZNode::ControllerReset(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_EssentialNodeQueriesComplete:
		Log::Write(LogLevel_Info, "Notification: Essential Node %d Queries Complete", _notification->GetNodeId());
		break;
	  case Notification::Type_NodeQueriesComplete:
		Log::Write(LogLevel_Info, "Notification: Node %d Queries Complete", _notification->GetNodeId());
		pthread_mutex_lock(&nlock);
		ZNode::NodeQueriesComplete(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_AwakeNodesQueried:
		Log::Write(LogLevel_Info, "Notification: Awake Nodes Queried");
		pthread_mutex_lock(&nlock);
		ZNode::AwakeNodesQueried(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_AllNodesQueriedSomeDead:
		Log::Write(LogLevel_Info, "Notification: Awake Nodes Queried Some Dead");
		pthread_mutex_lock(&nlock);
		ZNode::AllNodeQueriedSomeDead(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_AllNodesQueried:
		Log::Write(LogLevel_Info, "Notification: All Nodes Queried");
		pthread_mutex_lock(&nlock);
		ZNode::AllNodeQueried(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_Notification:
		switch (_notification->GetNotification()) {
			case Notification::Code_MsgComplete:
			  Log::Write(LogLevel_Info, "Notification: Notification home %08x node %d Message Complete",
				_notification->GetHomeId(), _notification->GetNodeId(), _notification->GetNotification());
			  pthread_mutex_lock(&nlock);
			  ZNode::MessageComplete(_notification);
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
			  ZNode::MessageAwake(_notification);
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
				ZNode::MessageAlive(_notification);
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

Manager::pfnOnNotification_t TinyController::OnNotificationCallback = OnNotification;

//-----------------------------------------------------------------------------
//	<TinyController::Destroy>
//	Static method to destroy the singleton.
//-----------------------------------------------------------------------------
void TinyController::Destroy() {
	delete this;
}

//-----------------------------------------------------------------------------
// <TinyController::TinyController>
// Constructor
//-----------------------------------------------------------------------------
TinyController::TinyController(char const* _port) {
	Log::Write(LogLevel_Info, "TinyController::TinyController() : initializing...");

	port = _port;
	controllerHomeId = 0;
	controllerNodeId = 0;
	isLaunched = false;

	controllerInfo = NULL;
	controllerReadyCallback = NULL;
	controllerFailedCallback = NULL;
	controllerResetCallback = NULL;
	allNodeQueriedCallback = NULL;
	awakedNodesQueriedCallback = NULL;
	allNodesQueriedSomeDeadCallback = NULL;
	nodeQueriesCompleteCallback = NULL;
}

//-----------------------------------------------------------------------------
// <TinyController::start>
// Create manager and begin node interviewing
//-----------------------------------------------------------------------------

void TinyController::start(){
	if(isLaunched){
		Log::Write(LogLevel_Info, "TinyController::start() : the serial port %s is already added...", port);
		return;
	}
	isLaunched = true;
	Log::Write(LogLevel_Info, "TinyController::start() : adding serial port %s...", port);
	ZWave_AddSerialPort(port);
}

//-----------------------------------------------------------------------------
// <TinyController::addDevice>
//add device to the list
//-----------------------------------------------------------------------------

void TinyController::addDevice(Device* device){
	devices.push_back(device);
	pthread_mutex_lock(&nlock);
	ZNode::DeviceAdded(device);
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
}

//-----------------------------------------------------------------------------
// <TinyController::update>
// observer update
//-----------------------------------------------------------------------------
void TinyController::update(ControllerSubject* subject){
	Notification const* notification = subject->getNotification();
	switch(notification->GetType()){
		case Notification::Type_DriverReady:
			Log::Write(LogLevel_Info, "TinyController::update() : Type_DriverReady...");
			this->setUp(subject->getControllerInfo());
			if(controllerReadyCallback)
				controllerReadyCallback->fn_callback(controllerReadyCallback->instance);
			break;
		case Notification::Type_DriverFailed:
			Log::Write(LogLevel_Info, "TinyController::update() : Type_DriverFailed...");
			if(controllerFailedCallback)
				controllerFailedCallback->fn_callback(controllerFailedCallback->instance);
			break;
		case Notification::Type_DriverReset:
			Log::Write(LogLevel_Info, "TinyController::update() : Type_DriverReset...");
			if(controllerResetCallback)
				controllerResetCallback->fn_callback(controllerResetCallback->instance);
			break;
		case Notification::Type_AllNodesQueried:
			Log::Write(LogLevel_Info, "TinyController::update() : Type_AllNodesQueried...");
			if(allNodeQueriedCallback)
				allNodeQueriedCallback->fn_callback(allNodeQueriedCallback->instance);
			break;
		case Notification::Type_AllNodesQueriedSomeDead:
			Log::Write(LogLevel_Info, "TinyController::update() : Type_AllNodesQueriedSomeDead...");
			if(allNodesQueriedSomeDeadCallback)
				allNodesQueriedSomeDeadCallback->fn_callback(allNodesQueriedSomeDeadCallback->instance);
			break;
		case Notification::Type_AwakeNodesQueried:
			Log::Write(LogLevel_Info, "TinyController::update() : Type_AwakeNodesQueried...");
			if(awakedNodesQueriedCallback)
				awakedNodesQueriedCallback->fn_callback(awakedNodesQueriedCallback->instance);
			break;
		case Notification::Type_NodeQueriesComplete:
			Log::Write(LogLevel_Info, "TinyController::update() : Type_NodeQueriesComplete...");
			if(nodeQueriesCompleteCallback)
				nodeQueriesCompleteCallback->fn_callback(nodeQueriesCompleteCallback->instance, notification->GetNodeId());
			break;
		default:
			Log::Write(LogLevel_Info, "TinyController::update() : not handled case...");
			break;
	}
}

//-----------------------------------------------------------------------------
// <TinyController::setUp>
//-----------------------------------------------------------------------------
void TinyController::setUp(m_structCtrl* _ctrInfo){
	controllerInfo = _ctrInfo;
	controllerHomeId = _ctrInfo->m_homeId;
	controllerNodeId = _ctrInfo->m_nodeId;
}


