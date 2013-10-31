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
#include "libs/types.h"
#include "libs/DomoZWave.h"
#include "devices/TinyController.h"

#include "Options.h"
#include "Manager.h"
#include "Node.h"
#include "Group.h"
#include "Notification.h"
#include "Log.h"

using namespace TinyOpenZWaveApi;

pthread_mutex_t nlock = PTHREAD_MUTEX_INITIALIZER;

uint8 Device::COMMAND_CLASS = COMMAND_CLASS_NO_OPERATION;
uint8 BinarySwitch::COMMAND_CLASS = COMMAND_CLASS_SWITCH_BINARY;
TinyController* TinyController::s_instance = NULL;

void OnNotification (Notification const* _notification, void* _context)
{

  ValueID id = _notification->GetValueID();
  switch (_notification->GetType()) {
	  case Notification::Type_ValueAdded:
		Log::Write(LogLevel_Info, "Notification: Value Added Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), valueTypeStr(id.GetType()));
		pthread_mutex_lock(&nlock);;
		ZNode::addValue(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_ValueRemoved:
		Log::Write(LogLevel_Info, "Notification: Value Removed Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), valueTypeStr(id.GetType()));
		pthread_mutex_lock(&nlock);
		ZNode::removeValue(_notification);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_ValueChanged:
		Log::Write(LogLevel_Info, "Notification: Value Changed Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), valueTypeStr(id.GetType()));
		pthread_mutex_lock(&nlock);
		ZNode::changeValue(_notification);
		pthread_mutex_unlock(&nlock);
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
	    ZNode::addNode(_notification);
	    pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_NodeRemoved:
		Log::Write(LogLevel_Info, "Notification: Node Removed Home %08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), valueTypeStr(id.GetType()));
		pthread_mutex_lock(&nlock);
		ZNode::removeNode(_notification);
		pthread_mutex_unlock(&nlock);
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
		break;
	  case Notification::Type_AllNodesQueried:
		Log::Write(LogLevel_Info, "Notification: All Nodes Queried");

		TinyController::testOnOff();

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

BinarySwitch* s;
int main(int argc, char* argv[]){
	const char* port = "/dev/ttyUSB0";
	TinyController::notification = OnNotification;
	TinyController::Init();
	TinyController::AddController(port);

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
			//Log::Write(LogLevel_Info, "BinarySwitch: is value polled %d ...", Manager::Get()->isPolled(s->getValueToPull()->getId()));
			Log::Write(LogLevel_Info, "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! init");
			TinyController::Get()->setCurrentController("/dev/ttyUSB0");
			s = new BinarySwitch();
			s = s->BinarySwitch::Init(TinyController::Get(),4,1,0);
		}
		if(ch == 'g'){
			Log::Write(LogLevel_Info, "BinarySwitch: the poll interval is  %d ...", Manager::Get()->GetPollInterval());
		}
		if(ch == 'e'){
			Log::Write(LogLevel_Info, "BinarySwitch: enabling  poll");
			//Manager::Get()->EnablePoll(s->getValueToPull()->getId(), 1);
		}
		if(ch == 's'){
			Log::Write(LogLevel_Info, "BinarySwitch: setting poll interval");
			Manager::Get()->SetPollInterval(5000, false);
		}
	}
	return 0;
}

void ZNode::addNode(Notification const* _notification){
	NodeInfo* nodeInfo = new NodeInfo();
	nodeInfo->m_nodeId = _notification->GetNodeId();
	nodeInfo->m_homeId = _notification->GetHomeId();
	nodeInfo->m_DeviceState = DZType_Unknown;
	nodeInfo->m_LastSeen = 0;
	DomoZWave_GetGNodes().push_back(nodeInfo);
	Log::Write(LogLevel_Info, "ZNode(): adding node value %d", nodeInfo->m_nodeId);
}

int32 ZNode::getNodeCount(){
	return DomoZWave_GetGNodes().size();
}

NodeInfo *ZNode::getNodeInfo(Notification const* _data){
	return DomoZWave_GetNodeInfo(_data);
}

void ZNode::addValue(Notification const* _data){
	NodeInfo *nodeInfo = getNodeInfo(_data);
	if(nodeInfo != NULL){
		nodeInfo->m_values.push_back(_data->GetValueID());
	}
	DomoZWave_RPC_ValueChanged( (int)_data->GetHomeId(), (int)_data->GetNodeId(), _data->GetValueID(), true );
}

void ZNode::removeNode(Notification const* _data){
	uint32 const homeId = _data->GetHomeId();
	uint8 const nodeId = _data->GetNodeId();
	list<NodeInfo*>& g_nodes = DomoZWave_GetGNodes();

	for ( list<NodeInfo*>::iterator it = g_nodes.begin(); it != g_nodes.end(); ++it ) {
		NodeInfo* nodeInfo = *it;
		if ( ( nodeInfo->m_homeId == homeId ) && ( nodeInfo->m_nodeId == nodeId ) ){
			g_nodes.erase( it );
			break;
		}
	}
	DomoZWave_RPC_NodeRemoved( (int)_data->GetHomeId(), (int)_data->GetNodeId() );
}

void ZNode::removeValue(Notification const* _data){
	NodeInfo* nodeInfo = ZNode::getNodeInfo(_data);
	if (nodeInfo != NULL){
		// Remove the value from out list
		for (list<ValueID>::iterator it = nodeInfo->m_values.begin(); it != nodeInfo->m_values.end(); ++it) {
			if ((*it) == _data->GetValueID())
			{
				nodeInfo->m_values.erase( it );
				break;
			}
		}
	}
	DomoZWave_RPC_ValueRemoved((int)_data->GetHomeId(), (int)_data->GetNodeId(), _data->GetValueID());
}

void ZNode::changeValue(Notification const* _data){
	DomoZWave_RPC_ValueChanged((int)_data->GetHomeId(), (int)_data->GetNodeId(), _data->GetValueID(), false);

	NodeInfo* nodeInfo = ZNode::getNodeInfo(_data);
	// Update LastSeen and DeviceState
	if (nodeInfo != NULL){
		nodeInfo->m_LastSeen = time(NULL);
		nodeInfo->m_DeviceState = DZType_Alive;
	}

	// Check if zwcfg*xml has been written 3600+ sec, then flush to disk
	m_structCtrl* ctrl = DomoZWave_GetControllerInfo((int)_data->GetHomeId());
	if ( ctrl->m_lastWriteXML > 0 ){
		double seconds;
		seconds = difftime( time( NULL ), ctrl->m_lastWriteXML );

		if ( seconds > 3600 ){
			Manager::Get()->WriteConfig((int)_data->GetHomeId());
			DomoZWave_WriteLog(LogLevel_Debug, true, "DomoZWave_WriteConfig: HomeId=%d (%.f seconds)", (int)_data->GetHomeId(), seconds);
			ctrl->m_lastWriteXML = time(NULL);
		}
	}
}

void ZNode::controllerReady(Notification const* _data){
	DomoZWave_RPC_DriverReady(_data->GetHomeId(), _data->GetNodeId());
}

m_structCtrl* ZNode::getControllerInfo(uint32 const homeId){
	return DomoZWave_GetControllerInfo(homeId);
}


Device* Device::Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index) {
	this->node = NULL;
	this->value = NULL;
	this->controller = controller;
	this->nodeId = _nodeId;
	this->instance = _instance;
	this->index = _index;
	list<NodeInfo*>& g_nodes = DomoZWave_GetGNodes();
	for(list<NodeInfo*>::iterator it=g_nodes.begin(); it!=g_nodes.end(); ++it){
		uint8 nodeId = (*it)->m_nodeId;
		uint32 homeId = (*it)->m_homeId;
		if(nodeId == _nodeId && homeId == controller->currentControllerHomeId){
			this->node = *it;
			break;
		}
	}
	if(this->node == NULL){
		Log::Write(LogLevel_Info, "DEVICE INIT: can not find node with id %d", this->nodeId);
	}
	return this;
}

uint8 Device::getComandClass(){
	return COMMAND_CLASS;
}

Device::~Device() {
	delete this;
}

//-----------------------------------------------------------------------------
//	<BinarySwitch::Destroy>
//	Static method to destroy the singleton.
//-----------------------------------------------------------------------------
void BinarySwitch::Destroy() {
	delete this;
}

//-----------------------------------------------------------------------------
// <BinarySwitch::BinarySwitch>
// Constructor
//-----------------------------------------------------------------------------
BinarySwitch::BinarySwitch() {}

//-----------------------------------------------------------------------------
// <BinarySwitch::BinarySwitch>
// Destructor
//-----------------------------------------------------------------------------
BinarySwitch::~BinarySwitch() {
	BinarySwitch::Destroy();
}

uint8 BinarySwitch::getComandClass(){
	return COMMAND_CLASS;
}

void BinarySwitch::turnOn(){
	Log::Write(LogLevel_Info, "BinarySwitch::turnOn(): turning on...");
	//DomoZWave_SetValue(currentControllerHomeId, this->nodeId, this->instance, 0);
	if(this->node != NULL){
		list<ValueID> values = this->node->m_values;
		for(list<ValueID>::iterator it=values.begin(); it!=values.end(); ++it){
			if((*it).GetCommandClassId() == getComandClass() &&
					(*it).GetInstance() == this->instance &&
					(*it).GetIndex() == this->index &&
					(*it).GetHomeId() == controller->currentControllerHomeId){
				this->value = &(*it);
				ValueID valueId = *this->value;
				if (ValueID::ValueType_Bool == valueId.GetType()){
					Log::Write(LogLevel_Info, "Value: Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
															valueId.GetHomeId(), valueId.GetNodeId(), valueGenreStr(valueId.GetGenre()),
															cclassStr(valueId.GetCommandClassId()), valueId.GetInstance(),
															valueId.GetIndex(), valueTypeStr(valueId.GetType()));
					bool bool_value = true;
					Manager::Get()->SetValue(valueId, bool_value);
				}else{
					Log::Write(LogLevel_Info, "BinarySwitch::turnOn(): command value is not of the bool type, ignoring..."
							"Value: Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s", valueId,
												valueId.GetHomeId(), valueId.GetNodeId(), valueGenreStr(valueId.GetGenre()),
												cclassStr(valueId.GetCommandClassId()), valueId.GetInstance(),
												valueId.GetIndex(), valueTypeStr(valueId.GetType()));
				}
				break;
			}
		}
		if(this->value == NULL){
			Log::Write(LogLevel_Info, "BinarySwitch::turnOn(): node with id %d does not implement command %s with instance %d and index %d",
					this->nodeId, cclassStr(getComandClass()), this->instance, this->index);
		}
	}else{
		Log::Write(LogLevel_Info, "BinarySwitch::turnOn(): node is NULL, ignoring...");
	};
}

void BinarySwitch::turnOff(){
	Log::Write(LogLevel_Info, "BinarySwitch::turnOff(): turning off...");
	if(this->node != NULL){
		list<ValueID> values = this->node->m_values;
		for(list<ValueID>::iterator it=values.begin(); it!=values.end(); ++it){
			if((*it).GetCommandClassId() == getComandClass() &&
					(*it).GetInstance() == this->instance &&
					(*it).GetIndex() == this->index &&
					(*it).GetHomeId() == controller->currentControllerHomeId){
				this->value = &(*it);
				ValueID valueId = *this->value;
				if (ValueID::ValueType_Bool == valueId.GetType()){
					bool bool_value = false;
					Manager::Get()->SetValue(valueId, bool_value);
				}else{
					Log::Write(LogLevel_Info, "BinarySwitch::turnOff(): command value is not of the bool type, ignoring..."
							"Value: Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s", valueId,
												valueId.GetHomeId(), valueId.GetNodeId(), valueGenreStr(valueId.GetGenre()),
												cclassStr(valueId.GetCommandClassId()), valueId.GetInstance(),
												valueId.GetIndex(), valueTypeStr(valueId.GetType()));
				}
				break;
			}
		}
		if(this->value == NULL){
			Log::Write(LogLevel_Info, "BinarySwitch::turnOff(): node with id %d does not implement command %s with instance %d and index %d",
					this->nodeId, cclassStr(getComandClass()), this->instance, this->index);
		}
	}else{
		Log::Write(LogLevel_Info, "BinarySwitch::turnOff(): node is NULL, ignoring...");
	};
}
