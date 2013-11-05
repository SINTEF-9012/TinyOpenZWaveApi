/*
 * BinarySwitch.cpp
 *
 *  Created on: Nov 1, 2013
 *      Author: vassik
 */

#include "Options.h"
#include "Manager.h"
#include "Node.h"
#include "Group.h"
#include "Notification.h"
#include "Log.h"

#include "TinyController.h"
#include "../libs/Utility.h"
#include "../libs/DomoZWave.h"
#include "BinarySwitch.h"
#include "../thingMLcallbacks/TMLcallback.h"

using namespace OpenZWave;


uint8 BinarySwitch::COMMAND_CLASS = COMMAND_CLASS_SWITCH_BINARY;
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
BinarySwitch::BinarySwitch() {
	callbacksOnOff.push_back(new ValueCallback(BinarySwitch::callback_turnOnOff, this));
	isTurnedOn = false;
}

BinarySwitch* BinarySwitch::Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index){
	BinarySwitch* bswitch = (BinarySwitch*)Device::Init(controller, _nodeId, _instance, _index);
	ValueID valueId = DomoZWave_GetValueID(controller->currentControllerHomeId, getComandClass(), this->node->m_nodeId, this->instance, this->index);
	DummyValueID dummy;
	if(valueId != *dummy.valueId){
		bool result = Manager::Get()->GetValueAsBool(valueId, &isTurnedOn);
		if(!result){
			Log::Write(LogLevel_Error, "BinarySwitch::BinarySwitch(): default value is not requested...");
		}
	}else{
		Log::Write(LogLevel_Error, "BinarySwitch::BinarySwitch(): can not find ValueID for"
				"Home 0x%08x Node %d Class %s Instance %d Index %d",
				controller->currentControllerHomeId, this->node->m_nodeId,
				getComandClass(), this->instance, this->index);
	}
	return bswitch;
}

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
	if(this->node != NULL){
		DomoZWave_SetValue((int) controller->currentControllerHomeId, (int) this->node->m_nodeId, this->instance, 255, callbacksOnOff);
	}else{
		Log::Write(LogLevel_Info, "BinarySwitch::turnOn(): node is NULL, ignoring...");
	};
}

void BinarySwitch::turnOff(){
	Log::Write(LogLevel_Info, "BinarySwitch::turnOff(): turning off...");
	if(this->node != NULL){
		DomoZWave_SetValue((int) controller->currentControllerHomeId, (int) this->node->m_nodeId, this->instance, 0, callbacksOnOff);
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
		DomoZWave_WriteLog(LogLevel_Debug, true, "BinarySwitch::callback_turnOnOff(): check value : "
				"Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s IS %i",
				valueID.GetHomeId(), valueID.GetNodeId(), genreToStr(valueID.GetGenre()),
				cclassToStr(valueID.GetCommandClassId()), valueID.GetInstance(),
				valueID.GetIndex(), typeToStr(valueID.GetType()), result);
		if(bs->isTurnedOn != result){
			if(result){
				Log::Write(LogLevel_Info, "BinarySwitch::callback_turnOnOff(): calling ThingML_binary_switch_turned_on()");
				ThingML_binary_switch_turned_on();
			}else{
				Log::Write(LogLevel_Info, "BinarySwitch::callback_turnOnOff(): calling ThingML_binary_switch_turned_off()");
				ThingML_binary_switch_turned_off();
			}
			bs->isTurnedOn = result;
		}else{
			Log::Write(LogLevel_Info, "BinarySwitch::callback_turnOnOff(): calling ThingML_binary_switch_nochange()");
			ThingML_binary_switch_nochange();
		}
	}else{
		Log::Write(LogLevel_Error, "BinarySwitch::callback_turnOnOff(): there must be a error, value should be of the bool type..."
				"Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
				valueID.GetHomeId(), valueID.GetNodeId(),
				genreToStr(valueID.GetGenre()), cclassToStr(valueID.GetCommandClassId()), valueID.GetInstance(),
				valueID.GetIndex(), typeToStr(valueID.GetType()));
	}
}


