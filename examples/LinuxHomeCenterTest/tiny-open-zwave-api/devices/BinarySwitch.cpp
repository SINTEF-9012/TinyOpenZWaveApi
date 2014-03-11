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
	callbacks.push_back(new ValueCallback(BinarySwitch::callback_turn_on_off, this));
	this->turnedOnCallback = turnedOnCallback;
	this->turnedOffCallback = turnedOffCallback;
	this->noChangeCallback = noChangeCallback;
}

BinarySwitch::BinarySwitch(){
	isTurnedOn = false;
	callbacks.push_back(new ValueCallback(BinarySwitch::callback_turn_on_off, this));
	this->turnedOnCallback = NULL;
	this->turnedOffCallback = NULL;
	this->noChangeCallback = NULL;
}

BinarySwitch* BinarySwitch::Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index){
	BinarySwitch* bswitch = (BinarySwitch*)Device::Init(controller, _nodeId, _instance, _index);
	ValueID valueId = DomoZWave_GetValueID(controller->homeId, getComandClass(), this->node->m_nodeId, this->instance, this->index);
	DummyValueID dummy;
	if(valueId != *dummy.valueID){
		bool result = Manager::Get()->GetValueAsBool(valueId, &isTurnedOn);
		if(!result){
			Log::Write(LogLevel_Error, "BinarySwitch::BinarySwitch(): default value is not requested...");
		}
	}else{
		Log::Write(LogLevel_Error, "BinarySwitch::BinarySwitch(): can not find ValueID for"
				"Home 0x%08x Node %d Class %s Instance %d Index %d",
				controller->homeId, this->node->m_nodeId,
				getComandClass(), this->instance, this->index);
	}
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
		DomoZWave_SetValue((int) controller->homeId, (int) this->node->m_nodeId, this->instance, 255, callbacks);
	}else{
		Log::Write(LogLevel_Info, "BinarySwitch::turnOn(): node is NULL, ignoring...");
	};
}

void BinarySwitch::turnOff(){
	Log::Write(LogLevel_Info, "BinarySwitch::turnOff(): turning off...");
	if(this->node != NULL){
		DomoZWave_SetValue((int) controller->homeId, (int) this->node->m_nodeId, this->instance, 0, callbacks);
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
		DomoZWave_WriteLog(LogLevel_Debug, true, "BinarySwitch::callback_turnOnOff(): check value : "
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


