/*
 * BinarySwitch.cpp
 *
 *  Created on: Nov 1, 2013
 *      Author: vassik
 */

#include <stdlib.h>
#include <typeinfo>

#include "openzwave/Options.h"
#include "openzwave/Manager.h"
#include "openzwave/Node.h"
#include "openzwave/Group.h"
#include "openzwave/Notification.h"
#include "openzwave/Log.h"

#include "TinyController.h"
#include "BinarySwitch.h"
#include "../libs/Utility.h"
#include "../libs/DomoZWave.h"
#include "../libs/ZNode.h"
#include "../observer/NodeSubject.h"


using namespace OpenZWave;


uint8 BinarySwitch::COMMAND_CLASS = COMMAND_CLASS_SWITCH_BINARY;
//-----------------------------------------------------------------------------
//	<BinarySwitch::Destroy>
//	method to destroy
//-----------------------------------------------------------------------------
void BinarySwitch::Destroy() {
	Log::Write(LogLevel_Info, "BinarySwitch::Destroy() : 0x%08x", this);
	delete this;
}

//-----------------------------------------------------------------------------
// <BinarySwitch::BinarySwitch>
// Constructor
//-----------------------------------------------------------------------------

BinarySwitch::BinarySwitch() : Device() {
	DEVICE_NAME = "BinarySwitch";
	isTurnedOn = false;
	noChangeCallback = NULL;
	turnedOnCallback = NULL;
	turnedOffCallback = NULL;
	callbacks.push_back(new ValueCallback(BinarySwitch::callback_turn_on_off, this));
}

BinarySwitch* BinarySwitch::Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index){
	BinarySwitch* bswitch = (BinarySwitch*) Device::Init(controller, _nodeId, _instance, _index);
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
		//ZWave_SetValue((int) controller->controllerHomeId, (int) this->node->m_nodeId, this->instance, 255);
		ZNode::SetValueIDValue(*this->valueID, 255);
	}else{
		Log::Write(LogLevel_Info, "BinarySwitch::turnOn(): node is NULL, ignoring...");
	};
}

void BinarySwitch::turnOff(){
	Log::Write(LogLevel_Info, "BinarySwitch::turnOff(): turning off...");
	if(this->node != NULL){
		//ZWave_SetValue((int) controller->controllerHomeId, (int) this->node->m_nodeId, this->instance, 0);
		ZNode::SetValueIDValue(*this->valueID, 0);
	}else{
		Log::Write(LogLevel_Info, "BinarySwitch::turnOff(): node is NULL, ignoring...");
	};
}

void BinarySwitch::callback_turn_on_off(Device* _context, Notification const* _data){
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
	Device::update(subject);
}

int BinarySwitch::setUp(NodeInfo* nodeInfo){
	int result = Device::setUp(nodeInfo);
	if(result != 0)
		return result;

	isTurnedOn = (bool) atoi(ZNode::GetValueIDValue(*this->valueID));
	Device::TestValueIDCallback(this->node, *this->valueID, callbacks);
	return result;
}


