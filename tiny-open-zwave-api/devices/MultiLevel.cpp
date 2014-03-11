/*
 * MultiLevel.cpp
 *
 *  Created on: Mar 6, 2014
 *      Author: vassik
 */

#include <typeinfo>

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
	valueLastSeen = 0;
	currentValue = NULL;
	valueUpdatedCallback = NULL;
	callbacks.push_back(new ValueCallback(MultiLevel::callback_value_refresh, this));
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

void MultiLevel::callback_value_refresh(Device* _context, Notification const* _data){
	Log::Write(LogLevel_Info, "MultiLevel::callback_value_refresh(): is called");
	MultiLevel *ml = (MultiLevel*) _context;
	ml->valueLastSeen = time(NULL);
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
