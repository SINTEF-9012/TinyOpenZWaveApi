/*
 * BinarySwitch.cpp
 *
 *  Created on: Nov 1, 2013
 *      Author: vassik
 */

#include "openzwave/Options.h"
#include "openzwave/Manager.h"
#include "openzwave/Node.h"
#include "openzwave/Group.h"
#include "openzwave/Notification.h"
#include "openzwave/Log.h"

#include "TinyController.h"
#include "../libs/Utility.h"
#include "../libs/DomoZWave.h"
#include "BinarySwitch.h"
#include "../observer/NodeSubject.h"


using namespace OpenZWave;


uint8 BinarySwitch::COMMAND_CLASS = COMMAND_CLASS_SWITCH_BINARY;
//-----------------------------------------------------------------------------
//	<BinarySwitch::Destroy>
//	method to destroy
//-----------------------------------------------------------------------------
void BinarySwitch::Destroy() {
	delete this;
}

//-----------------------------------------------------------------------------
// <BinarySwitch::BinarySwitch>
// Constructor
//-----------------------------------------------------------------------------
BinarySwitch::BinarySwitch(ThingMLCallback* turnedOnCallback, ThingMLCallback* turnedOffCallback, ThingMLCallback* noChangeCallback) {
	isTurnedOn = false;
	callbacksOnOff.push_back(new ValueCallback(BinarySwitch::callback_turnOnOff, this));
	this->turnedOnCallback = turnedOnCallback;
	this->turnedOffCallback = turnedOffCallback;
	this->noChangeCallback = noChangeCallback;
}

BinarySwitch::BinarySwitch(){
	isTurnedOn = false;
	callbacksOnOff.push_back(new ValueCallback(BinarySwitch::callback_turnOnOff, this));
	this->turnedOnCallback = NULL;
	this->turnedOffCallback = NULL;
	this->noChangeCallback = NULL;
}

BinarySwitch* BinarySwitch::Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index){
	BinarySwitch* bswitch = (BinarySwitch*)Device::Init(controller, _nodeId, _instance, _index);
	return bswitch;
}

//-----------------------------------------------------------------------------
// <BinarySwitch::BinarySwitch>
// Destructor
//-----------------------------------------------------------------------------
BinarySwitch::~BinarySwitch() {
	Log::Write(LogLevel_Info, "BinarySwitch::~BinarySwitch(): 0x%08x", this);
}

uint8 BinarySwitch::getComandClass(){
	return COMMAND_CLASS;
}

void BinarySwitch::turnOn(){
	Log::Write(LogLevel_Info, "BinarySwitch::turnOn(): turning on...");
	if(this->node != NULL){
		ZWave_SetValue((int) controller->currentControllerHomeId, (int) this->node->m_nodeId, this->instance, 255);
	}else{
		Log::Write(LogLevel_Info, "BinarySwitch::turnOn(): node is NULL, ignoring...");
	};
}

void BinarySwitch::turnOff(){
	Log::Write(LogLevel_Info, "BinarySwitch::turnOff(): turning off...");
	if(this->node != NULL){
		ZWave_SetValue((int) controller->currentControllerHomeId, (int) this->node->m_nodeId, this->instance, 0);
	}else{
		Log::Write(LogLevel_Info, "BinarySwitch::turnOff(): node is NULL, ignoring...");
	};
}

void BinarySwitch::callback_turnOnOff(Device* _context, Notification const* _data){
	Log::Write(LogLevel_Info, "BinarySwitch::callback_turnOnOff(): is called");
	ValueID valueID = _data->GetValueID();
	BinarySwitch *bs = (BinarySwitch*) _context;
	if(ValueID::ValueType_Bool == valueID.GetType()){
		bool result;
		Manager::Get()->GetValueAsBool(valueID, &result);
		ZWave_WriteLog(LogLevel_Debug, true, "BinarySwitch::callback_turnOnOff(): check value : "
				"Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s IS %i",
				valueID.GetHomeId(), valueID.GetNodeId(), genreToStr(valueID.GetGenre()),
				cclassToStr(valueID.GetCommandClassId()), valueID.GetInstance(),
				valueID.GetIndex(), typeToStr(valueID.GetType()), result);
		if(bs->isTurnedOn != result){
			if(result){
				if(bs->turnedOnCallback != NULL){
					Log::Write(LogLevel_Info, "BinarySwitch::callback_turnOnOff(): calling ThingML_binary_switch_turned_on()");
					bs->turnedOnCallback->fn_callback(bs->turnedOnCallback->instance);
				}
			}else{
				if(bs->turnedOffCallback != NULL){
					Log::Write(LogLevel_Info, "BinarySwitch::callback_turnOnOff(): calling ThingML_binary_switch_turned_off()");
					bs->turnedOffCallback->fn_callback(bs->turnedOffCallback->instance);
				}
			}
			bs->isTurnedOn = result;
		}else{
			if(bs->noChangeCallback != NULL){
				Log::Write(LogLevel_Info, "BinarySwitch::callback_turnOnOff(): calling ThingML_binary_switch_nochange()");
				bs->noChangeCallback->fn_callback(bs->noChangeCallback->instance);
			}
		}
	}else{
		Log::Write(LogLevel_Error, "BinarySwitch::callback_turnOnOff(): there must be a error, value should be of the bool type..."
				"Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
				valueID.GetHomeId(), valueID.GetNodeId(),
				genreToStr(valueID.GetGenre()), cclassToStr(valueID.GetCommandClassId()), valueID.GetInstance(),
				valueID.GetIndex(), typeToStr(valueID.GetType()));
	}
}

void BinarySwitch::update(NodeSubject* subject){
	Log::Write(LogLevel_Info, "BinarySwitch::update(): is called for the node %d 0x%08x", this->nodeId, this);
	Device::update(subject);
	Notification const* notification = subject->getNotification();
	if(notification->GetValueID().GetCommandClassId() != getComandClass())
		return;

	ValueID valueId = notification->GetValueID();
	switch (notification->GetType()) {
		case Notification::Type_ValueAdded:
			this->setUp(subject->getNodeInfo());
			break;
		case Notification::Type_ValueChanged:
			Log::Write(LogLevel_Info, "BinarySwitch::update(): value changed, calling callback...");
			Device::CallValueCallback(this->node, valueId, notification);
			break;
		default:
			Log::Write(LogLevel_Info, "BinarySwitch::update(): not handled case...");
			break;
	}
}

void BinarySwitch::setUp(NodeInfo* nodeInfo){
	Log::Write(LogLevel_Info, "BinarySwitch::setUp(): is called for the node %d 0x%08x", this->nodeId, this);
	Device::setUp(nodeInfo);
	list<ValueID> values = node->m_values;
	ValueID valueId = findValueID(node->m_values, getComandClass(), this->instance, this->index);
	DummyValueID dummy;
	if(valueId != *dummy.valueId){
		bool result = Manager::Get()->GetValueAsBool(valueId, &isTurnedOn);
		if(!result) Log::Write(LogLevel_Info, "BinarySwitch::setUp(): default value is not requested yet...");
		this->value = &valueId;
		Device::TestValueIDCallback(this->node, valueId, callbacksOnOff);
	}else{
		Log::Write(LogLevel_Info, "BinarySwitch::setUp(): ValueID is not known yet for"
				"Home 0x%08x Node %d Class %s Instance %d Index %d",
				controller->currentControllerHomeId, this->node->m_nodeId,
				getComandClass(), this->instance, this->index);
	}
}


