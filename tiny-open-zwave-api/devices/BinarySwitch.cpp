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
	Log::Write(LogLevel_Info, "BinarySwitch::callback_turnOnOff(): ...");
}


