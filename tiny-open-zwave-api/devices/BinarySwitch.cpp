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


namespace TinyOpenZWaveApi {


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
		ZNode::SetValueIDValue(*this->valueID, 255);
	}else{
		Log::Write(LogLevel_Info, "BinarySwitch::turnOn(): node is NULL, ignoring...");
	};
}

void BinarySwitch::turnOff(){
	Log::Write(LogLevel_Info, "BinarySwitch::turnOff(): turning off...");
	if(this->node != NULL){
		ZNode::SetValueIDValue(*this->valueID, 0);
	}else{
		Log::Write(LogLevel_Info, "BinarySwitch::turnOff(): node is NULL, ignoring...");
	};
}

void BinarySwitch::refresh(){
	if(NullValueID::IsNull(*this->valueID)){
		Log::Write(LogLevel_Info, "BinarySwitch::refresh(): can not refresh value since ValuiID is null");
		return;
	}
	Manager::Get()->RefreshValue(*this->valueID);
}

void BinarySwitch::callback_turn_on_off(Device* _context, Notification const* _data){
	Log::Write(LogLevel_Info, "BinarySwitch::callback_turn_on_off(): is called");
	BinarySwitch *bs = (BinarySwitch*) _context;
	ValueID valueID = *bs->valueID;
	if(NullValueID::IsNull(valueID)){
		Log::Write(LogLevel_Info, "BinarySwitch::callback_turn_on_off: ValuiID is null, skipping...");
		return;
	}
	ValueID passedValueID = _data->GetValueID();
	if(passedValueID != valueID){
		Log::Write(LogLevel_Info, "BinarySwitch::callback_turn_on_off: the passed valueID and BinarySwitch's valueID do not match, skipping...\n"
			"-->Passed valueID: Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s\n"
			"-->MultiLevel's valueID: Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			passedValueID.GetHomeId(), passedValueID.GetNodeId(), genreToStr(passedValueID.GetGenre()),
			cclassToStr(passedValueID.GetCommandClassId()), passedValueID.GetInstance(),
			passedValueID.GetIndex(), typeToStr(passedValueID.GetType()),
			valueID.GetHomeId(), valueID.GetNodeId(), genreToStr(valueID.GetGenre()),
			cclassToStr(valueID.GetCommandClassId()), valueID.GetInstance(),
			valueID.GetIndex(), typeToStr(valueID.GetType()));
		return;
	}
	bs->valueLastSeen = time(NULL);
	bool result = (strcmp(ZNode::GetValueIDValue(valueID), "0") == 0) ? false : true;
	Log::Write(LogLevel_Info, "BinarySwitch::callback_turn_on_off(): check value : "
			"Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s IS %i",
			valueID.GetHomeId(), valueID.GetNodeId(), genreToStr(valueID.GetGenre()),
			cclassToStr(valueID.GetCommandClassId()), valueID.GetInstance(),
			valueID.GetIndex(), typeToStr(valueID.GetType()), result);
	if(bs->isTurnedOn != result){
		if(result){
			if(bs->turnedOnCallback != NULL){
				Log::Write(LogLevel_Info, "BinarySwitch::callback_turn_on_off(): calling ThingML_binary_switch_turned_on()");
				bs->turnedOnCallback->fn_callback(bs->turnedOnCallback->instance);
			}
		}else{
			if(bs->turnedOffCallback != NULL){
				Log::Write(LogLevel_Info, "BinarySwitch::callback_turnOnOff(): calling ThingML_binary_switch_turned_off()");
				bs->turnedOffCallback->fn_callback(bs->turnedOffCallback->instance);
			}
		}
		Log::Write(LogLevel_Info, "BinarySwitch::callback_turn_on_off(): updating currentValue with value %d of the type %s\n", bs->isTurnedOn, typeid(bs->isTurnedOn).name());
		bs->isTurnedOn = result;
	}else{
		if(bs->noChangeCallback != NULL){
			Log::Write(LogLevel_Info, "BinarySwitch::callback_turn_on_off(): calling ThingML_binary_switch_nochange()");
			bs->noChangeCallback->fn_callback(bs->noChangeCallback->instance);
		}
	}
}

void BinarySwitch::update(NodeSubject* subject){
	Device::update(subject);
}

int BinarySwitch::setUp(NodeInfo* nodeInfo){
	int result = Device::setUp(nodeInfo);
	if(result != 0)
		return result;

	this->finalizeSetUp();
	return result;
}

void BinarySwitch::finalizeSetUp(){
	isTurnedOn = (strcmp(ZNode::GetValueIDValue(*this->valueID), "0") == 0) ? false : true;
	Log::Write(LogLevel_Info, "BinarySwitch::finalizeSetUp(): updating currentValue with value %d of the type %s\n", isTurnedOn, typeid(isTurnedOn).name());
	Device::finalizeSetUp();
}

}
