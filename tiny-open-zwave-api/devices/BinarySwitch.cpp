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
BinarySwitch::BinarySwitch() {}

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
	//DomoZWave_SetValue(currentControllerHomeId, this->nodeId, this->instance, 0);
	if(this->node != NULL){
		list<ValueID> values = this->node->m_values;
		for(list<ValueID>::iterator it=values.begin(); it!=values.end(); ++it){
			if((*it).GetCommandClassId() == getComandClass() &&
					(*it).GetInstance() == this->instance &&
					(*it).GetIndex() == this->index &&
					(*it).GetHomeId() == controller->currentControllerHomeId){
				this->value = &(*it);
				ValueID valueId = *this->value;
				if (ValueID::ValueType_Bool == valueId.GetType()){
					Log::Write(LogLevel_Info, "Value: Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
															valueId.GetHomeId(), valueId.GetNodeId(), genreToStr(valueId.GetGenre()),
															cclassToStr(valueId.GetCommandClassId()), valueId.GetInstance(),
															valueId.GetIndex(), typeToStr(valueId.GetType()));
					bool bool_value = true;
					Manager::Get()->SetValue(valueId, bool_value);
				}else{
					Log::Write(LogLevel_Info, "BinarySwitch::turnOn(): command value is not of the bool type, ignoring..."
							"Value: Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s", valueId,
												valueId.GetHomeId(), valueId.GetNodeId(), genreToStr(valueId.GetGenre()),
												cclassToStr(valueId.GetCommandClassId()), valueId.GetInstance(),
												valueId.GetIndex(), typeToStr(valueId.GetType()));
				}
				break;
			}
		}
		if(this->value == NULL){
			Log::Write(LogLevel_Info, "BinarySwitch::turnOn(): node with id %d does not implement command %s with instance %d and index %d",
					this->nodeId, cclassToStr(getComandClass()), this->instance, this->index);
		}
	}else{
		Log::Write(LogLevel_Info, "BinarySwitch::turnOn(): node is NULL, ignoring...");
	};
}

void BinarySwitch::turnOff(){
	Log::Write(LogLevel_Info, "BinarySwitch::turnOff(): turning off...");
	if(this->node != NULL){
		list<ValueID> values = this->node->m_values;
		for(list<ValueID>::iterator it=values.begin(); it!=values.end(); ++it){
			if((*it).GetCommandClassId() == getComandClass() &&
					(*it).GetInstance() == this->instance &&
					(*it).GetIndex() == this->index &&
					(*it).GetHomeId() == controller->currentControllerHomeId){
				this->value = &(*it);
				ValueID valueId = *this->value;
				if (ValueID::ValueType_Bool == valueId.GetType()){
					bool bool_value = false;
					Manager::Get()->SetValue(valueId, bool_value);
				}else{
					Log::Write(LogLevel_Info, "BinarySwitch::turnOff(): command value is not of the bool type, ignoring..."
							"Value: Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s", valueId,
												valueId.GetHomeId(), valueId.GetNodeId(), genreToStr(valueId.GetGenre()),
												cclassToStr(valueId.GetCommandClassId()), valueId.GetInstance(),
												valueId.GetIndex(), typeToStr(valueId.GetType()));
				}
				break;
			}
		}
		if(this->value == NULL){
			Log::Write(LogLevel_Info, "BinarySwitch::turnOff(): node with id %d does not implement command %s with instance %d and index %d",
					this->nodeId, cclassToStr(getComandClass()), this->instance, this->index);
		}
	}else{
		Log::Write(LogLevel_Info, "BinarySwitch::turnOff(): node is NULL, ignoring...");
	};
}


