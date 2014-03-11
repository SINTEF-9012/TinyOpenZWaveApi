/*
 * MultiLevel.cpp
 *
 *  Created on: Mar 6, 2014
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
#include "../libs/ZNode.h"
#include "MultiLevel.h"
#include "../observer/NodeSubject.h"


using namespace OpenZWave;


uint8 MultiLevel::COMMAND_CLASS = COMMAND_CLASS_SENSOR_MULTILEVEL;

void MultiLevel::Destroy(){
	delete this;
}

MultiLevel::MultiLevel() : Device() {
	DEVICE_NAME = "MultiLevel";
	currentValue = NULL;
	valueUpdatedCallback = NULL;
	callbacks.push_back(new ValueCallback(MultiLevel::callback_value_updated, this));
}

MultiLevel* MultiLevel::Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index){
	MultiLevel* multilevel = (MultiLevel*) Device::Init(controller, _nodeId, _instance, _index);
	return multilevel;
}

MultiLevel::~MultiLevel() {
	Log::Write(LogLevel_Info, "MultiLevel::~MultiLevel(): 0x%08x", this);
}

uint8 MultiLevel::getComandClass(){
	return COMMAND_CLASS;
}

char* MultiLevel::getCurrentValue(){
	return currentValue;
}

void MultiLevel::refresh(){
	if(NullValueID::IsNull(*this->valueID)){
		Log::Write(LogLevel_Info, "MultiLevel::refresh(): can not refresh value since ValuiID is null");
		return;
	}
	Manager::Get()->RefreshValue(*this->valueID);
}

void MultiLevel::callback_value_updated(Device* _context, Notification const* _data){
	Log::Write(LogLevel_Info, "MultiLevel::callback_value_updated(): is called");
	MultiLevel *ml = (MultiLevel*) _context;
	ValueID valueID = *ml->valueID;
	if(NullValueID::IsNull(valueID)){
		Log::Write(LogLevel_Info, "MultiLevel::callback_value_updated() : ValuiID is null, skipping...");
		return;
	}
	ValueID passedValueID = _data->GetValueID();
	if(passedValueID != valueID){
		Log::Write(LogLevel_Info, "MultiLevel::callback_value_updated() : the passed valueID and MultiLevel's valueID do not match, skipping...\n"
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
	ml->valueLastSeen = time(NULL);
	ml->currentValue = ZNode::GetValueIDValue(valueID);
	if(ml->valueUpdatedCallback){
		Log::Write(LogLevel_Info, "MultiLevel::callback_value_updated(): calling value update callback ");
		ml->valueUpdatedCallback->fn_callback(ml->valueUpdatedCallback->instance, ml->currentValue);
	}
}

void MultiLevel::update(NodeSubject* subject){
	Device::update(subject);
}

int MultiLevel::setUp(NodeInfo* nodeInfo){
	int result = Device::setUp(nodeInfo);
	if(result != 0)
		return result;

	currentValue = ZNode::GetValueIDValue(*this->valueID);
	Device::TestValueIDCallback(this->node, *this->valueID, callbacks);
	return result;
}
