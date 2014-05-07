/*
 * BinarySensor.cpp
 *
 *  Created on: Mar 11, 2014
 *      Author: vassik
 */

#include <typeinfo>

#include "openzwave/Options.h"
#include "openzwave/Manager.h"
#include "openzwave/Node.h"
#include "openzwave/Group.h"
#include "openzwave/Notification.h"
#include "openzwave/Log.h"

#include "Device.h"
#include "TinyController.h"
#include "../libs/Utility.h"
#include "../libs/DomoZWave.h"
#include "../libs/ZNode.h"
#include "BinarySensor.h"
#include "../observer/NodeSubject.h"

namespace TinyOpenZWaveApi {

uint8 BinarySensor::COMMAND_CLASS = COMMAND_CLASS_SENSOR_BINARY;

void BinarySensor::Destroy(){
	delete this;
}

BinarySensor::BinarySensor() : Device() {
	DEVICE_NAME = "BinarySensor";
	currentValue = -1;
	valueUpdatedCallback = NULL;
	callbacks.push_back(new ValueCallback(BinarySensor::callback_value_updated, this));
}

BinarySensor* BinarySensor::Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index){
	BinarySensor* bs = (BinarySensor*) Device::Init(controller, _nodeId, _instance, _index);
	return bs;
}

BinarySensor::~BinarySensor() {
	Log::Write(LogLevel_Info, "BinarySensor::~BinarySensor(): 0x%08x", this);
}

uint8 BinarySensor::getComandClass(){
	return COMMAND_CLASS;
}

int BinarySensor::getCurrentValue(){
	return currentValue;
}

void BinarySensor::refresh(){
	if(NullValueID::IsNull(*this->valueID)){
		Log::Write(LogLevel_Info, "BinarySensor::refresh(): can not refresh value since ValuiID is null");
		return;
	}
	Manager::Get()->RefreshValue(*this->valueID);
}

void BinarySensor::callback_value_updated(Device* _context, Notification const* _data){
	Log::Write(LogLevel_Info, "BinarySensor::callback_value_updated(): is called");
	BinarySensor *bs = (BinarySensor*) _context;
	ValueID valueID = *bs->valueID;
	if(NullValueID::IsNull(valueID)){
		Log::Write(LogLevel_Info, "BinarySensor::callback_value_updated() : ValuiID is null, skipping...");
		return;
	}
	ValueID passedValueID = _data->GetValueID();
	if(passedValueID != valueID){
		Log::Write(LogLevel_Info, "BinarySensor::callback_value_updated() : the passed valueID and BinarySensor's valueID do not match, skipping...\n"
			"-->Passed valueID: Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s\n"
			"-->BinarySensor's valueID: Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
			passedValueID.GetHomeId(), passedValueID.GetNodeId(), genreToStr(passedValueID.GetGenre()),
			cclassToStr(passedValueID.GetCommandClassId()), passedValueID.GetInstance(),
			passedValueID.GetIndex(), typeToStr(passedValueID.GetType()),
			valueID.GetHomeId(), valueID.GetNodeId(), genreToStr(valueID.GetGenre()),
			cclassToStr(valueID.GetCommandClassId()), valueID.GetInstance(),
			valueID.GetIndex(), typeToStr(valueID.GetType()));
		return;
	}
	bs->valueLastSeen = time(NULL);
	bs->currentValue = (strcmp(ZNode::GetValueIDValue(valueID), "1") == 0) ? 1 : 0;
	Log::Write(LogLevel_Info, "BinarySensor::callback_value_updated(): updating currentValue with value %d of the type %s\n", bs->currentValue, typeid(bs->currentValue).name());
	if(bs->valueUpdatedCallback){
		Log::Write(LogLevel_Info, "BinarySensor::callback_value_updated(): calling value update callback ");
		bs->valueUpdatedCallback->fn_callback(bs->valueUpdatedCallback->instance, bs->currentValue);
	}
}

void BinarySensor::update(NodeSubject* subject){
	Device::update(subject);
}

int BinarySensor::setUp(NodeInfo* nodeInfo){
	int result = Device::setUp(nodeInfo);
	if(result != 0)
		return result;

	this->finalizeSetUp();
	return result;
}

void BinarySensor::finalizeSetUp(){
	currentValue = (strcmp(ZNode::GetValueIDValue(*this->valueID), "1") == 0) ? 1 : 0;
	Log::Write(LogLevel_Info, "BinarySensor::finalizeSetUp(): updating currentValue with value %d of the type %s\n", currentValue, typeid(currentValue).name());
	Device::finalizeSetUp();
}
}
