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

#include "Options.h"
#include "Manager.h"
#include "Node.h"
#include "Group.h"
#include "Notification.h"
#include "Log.h"

using namespace TinyOpenZWaveApi;

uint32 homeId = 0;
uint8 nodeId = 0;
pthread_mutex_t nlock = PTHREAD_MUTEX_INITIALIZER;
//static pthread_mutex_t g_criticalSection;

int32 ZNode::nodecount = 0;
ZNode *nodes[MAX_NODES];

const char *Device::COMMAND_CLASS = "";
const char *BinarySwitch::COMMAND_CLASS = SWITCH_BINARY;

void OnNotification (Notification const* _notification, void* _context)
{

  ValueID id = _notification->GetValueID();
  ZNode *node = NULL;
  switch (_notification->GetType()) {
	  case Notification::Type_ValueAdded:
		Log::Write(LogLevel_Info, "Notification: Value Added Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), valueTypeStr(id.GetType()));
		pthread_mutex_lock(&nlock);
		node = ZNode::getNode(_notification->GetNodeId());
		node->addZValue(id);
		pthread_mutex_unlock(&nlock);
		break;
	  case Notification::Type_ValueRemoved:
		Log::Write(LogLevel_Info, "Notification: Value Removed Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			   _notification->GetHomeId(), _notification->GetNodeId(),
			   valueGenreStr(id.GetGenre()), cclassStr(id.GetCommandClassId()), id.GetInstance(),
			   id.GetIndex(), valueTypeStr(id.GetType()));
		pthread_mutex_lock(&nlock);
		node = ZNode::getNode(_notification->GetNodeId());
		node->dropZValue(id);
		pthread_mutex_unlock(&nlock);
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


TinyController* TinyController::s_instance = NULL;
string TinyController::port = "";

BinarySwitch* s;
int main(int argc, char* argv[]){
	string port = "/dev/ttyUSB0";
	TinyController::Init(port);

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
			Log::Write(LogLevel_Info, "BinarySwitch: is value polled %d ...", Manager::Get()->isPolled(s->getValueToPull()->getId()));
		}
		if(ch == 'g'){
			Log::Write(LogLevel_Info, "BinarySwitch: the poll interval is  %d ...", Manager::Get()->GetPollInterval());
		}
		if(ch == 'e'){
			Log::Write(LogLevel_Info, "BinarySwitch: enabling  poll");
			Manager::Get()->EnablePoll(s->getValueToPull()->getId(), 1);
		}
		if(ch == 's'){
			Log::Write(LogLevel_Info, "BinarySwitch: setting poll interval");
			Manager::Get()->SetPollInterval(5000, false);
		}
	}
	return 0;
}


//


ZValue::ZValue(ValueID _id) : id(_id) {};

ValueID ZValue::getId(){
	return id;
}

ZValue::~ZValue(){}

void ZNode::Destroy(){
	for(int i=0; i<MAX_NODES; i++){
		delete nodes[i];
	}
}

ZNode::~ZNode(){
	Log::Write(LogLevel_Info, "~ZNode(): clearing data for the node %d...", this->getNodeId());
	while (!values.empty()) {
		ZValue *v = values.back();
		values.pop_back();
		ValueID valueId =  v->getId();
	    Log::Write(LogLevel_Info, "Dropping value: Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
	    					valueId.GetHomeId(), valueId.GetNodeId(), valueGenreStr(valueId.GetGenre()),
	    					cclassStr(valueId.GetCommandClassId()), valueId.GetInstance(),
	    					valueId.GetIndex(), valueTypeStr(valueId.GetType()));
	    delete v;
	}
}

ZNode::ZNode(int32 const _node_id){
	node_id = _node_id;
	if (_node_id < 1 || _node_id >= MAX_NODES) {
		Log::Write(LogLevel_Info, "ZNode(): bad node value %d, ignoring...", _node_id);
		delete this;
		return;
	}
	Log::Write(LogLevel_Info, "ZNode(): adding node value %d", _node_id);
	nodes[node_id] = this;
	nodecount ++;
}

int32 ZNode::getNodeCount(){
	return nodecount;
}

ZNode *ZNode::getNode(int32 const _nodeId){
	return nodes[_nodeId];
}

void ZNode::addZValue(ValueID _valueId){
	ZValue *zvalue = new ZValue(_valueId);
	values.push_back(zvalue);
}

void ZNode::dropZValueAt(uint8 n){
	uint8 size = values.size();
	if(size > n){
		Log::Write(LogLevel_Info, "cannot drop value at %d, current size is %d ignoring...", n, size);
		return;
	}
	vector<ZValue*>::iterator it;
	uint8 i = 0;
	while(it!=values.end() && i != n){
		if(i == size){
			values.erase(it);
			break;
		}
		it++;
		i++;
	}
}

void ZNode::dropZValue(ValueID valueId){
	vector<ZValue*>::iterator it;
	bool deleted = false;
	for(it = values.begin(); it != values.end(); it++){
		if((*it)->getId() == valueId){
			delete *it;
			values.erase(it);
			deleted = true;
			break;
		}
	}
	if(!deleted){
		Log::Write(LogLevel_Info, "valueId %d does not exist in the values list..."
				"Value: Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s", valueId,
					valueId.GetHomeId(), valueId.GetNodeId(), valueGenreStr(valueId.GetGenre()),
					cclassStr(valueId.GetCommandClassId()), valueId.GetInstance(),
					valueId.GetIndex(), valueTypeStr(valueId.GetType()));
	}
}

ZValue* ZNode::getValueAt(uint8 n){
	uint8 size = values.size();
	if(size > n){
		Log::Write(LogLevel_Info, "cannot get value at %d, current size is %d ignoring...", n, size);
		return NULL;
	}
	return values[n];
}

int32 ZNode::getNodeId(){
	return node_id;
}

vector<ZValue*> ZNode::getValueValues(){
	return values;
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
	ZNode::Destroy();
	delete s_instance;
	s_instance = NULL;
}

//-----------------------------------------------------------------------------
// <TinyController::TinyController>
// Constructor
//-----------------------------------------------------------------------------
TinyController::TinyController() {

	Options::Create("./config/", "", "--SaveConfiguration=true --DumpTriggerLevel=0");
    Options::Get()->AddOptionInt("PollInterval", 5000);
    Options::Get()->AddOptionBool("IntervalBetweenPolls", true);
    Options::Get()->AddOptionBool( "SuppressValueRefresh", false );
    Options::Get()->AddOptionBool( "PerformReturnRoutes", false );


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

Device* Device::Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index) {
	this->value = NULL;
	this->controller = controller;
	this->nodeId = _nodeId;
	this->instance = _instance;
	this->index = _index;
	this->node = nodes[this->nodeId];
	vector<ZValue*>::iterator it;
	if(this->node != NULL){
		vector<ZValue*> values = this->node->getValueValues();
		for(it = values.begin(); it != values.end(); it++){
			ValueID id = (*it)->getId();
			if(id.GetCommandClassId() == getComandClass() &&
					id.GetInstance() == this->instance &&
					id.GetIndex() == this->index){
				this->value = (*it);
				break;
			}
		}
		if(this->value == NULL){
			Log::Write(LogLevel_Info, "DEVICE INIT: node with id %d does not implement command %s with instance %d and index %d",
					this->nodeId, cclassStr(getComandClass()), this->instance, this->index);
		}
	}else{
		Log::Write(LogLevel_Info, "DEVICE INIT: can not find node with id %d", this->nodeId);
	}
	return this;
}

void TinyController::testOnOff(){
	Log::Write(LogLevel_Info, "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! testOnOff TEST");
	s = new BinarySwitch();
	s = s->BinarySwitch::Init(TinyController::Get(),4,1,0);

	//s->turnOn();
}

uint8 Device::getComandClass(){
	return cclassNum(COMMAND_CLASS);
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
	return cclassNum(COMMAND_CLASS);
}

void BinarySwitch::turnOn(){
	Log::Write(LogLevel_Info, "BinarySwitch::turnOn(): turning on...");
	if(this->node != NULL && this->value != NULL){
		ValueID valueId = this->value->getId();
		if (ValueID::ValueType_Bool == valueId.GetType()){
			bool bool_value = true;
			Manager::Get()->SetValue(valueId, bool_value);
		}else{
			Log::Write(LogLevel_Info, "BinarySwitch::turnOn(): command value is not of the bool type, ignoring..."
					"Value: Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s", valueId,
										valueId.GetHomeId(), valueId.GetNodeId(), valueGenreStr(valueId.GetGenre()),
										cclassStr(valueId.GetCommandClassId()), valueId.GetInstance(),
										valueId.GetIndex(), valueTypeStr(valueId.GetType()));
		}
	}else{
		Log::Write(LogLevel_Info, "BinarySwitch::turnOn(): node or valueid for turn on/off command is NULL, ignoring...");
	};
}

void BinarySwitch::turnOff(){
	Log::Write(LogLevel_Info, "BinarySwitch::turnOff(): turning off...");
	if(this->node != NULL && this->value != NULL){
		ValueID valueId = this->value->getId();
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
	}else{
		Log::Write(LogLevel_Info, "BinarySwitch::turnOff(): node or valueid for turn on/off command is NULL, ignoring...");
	};
}

ZValue* BinarySwitch::getValueToPull(){
	return this->value;
}
