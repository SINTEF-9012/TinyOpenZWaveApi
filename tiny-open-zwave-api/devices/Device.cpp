/*
 * Device.cpp
 *
 *  Created on: Nov 1, 2013
 *      Author: vassik
 */

#include <iostream>

#include "openzwave/Log.h"
#include "openzwave/Node.h"

#include "TinyController.h"
#include "Device.h"
#include "../libs/DomoZWave.h"
#include "../libs/Utility.h"

using namespace OpenZWave;

uint8 Device::COMMAND_CLASS = COMMAND_CLASS_NON_UNKNOWN;

Device* Device::Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index) {
	this->node = NULL;
	this->value = NULL;
	this->controller = controller;
	this->nodeId = _nodeId;
	this->instance = _instance;
	this->index = _index;
	controller->addDevice(this);
	return this;
}

uint8 Device::getComandClass(){
	return COMMAND_CLASS;
}

void Device::Destroy(){
	delete this;
}

Device::~Device(){
	Log::Write(LogLevel_Info, "Device::~Device(): 0x%08x", this);
}

void Device::update(NObInfo* nobInfo){

}

void Device::setUp(NodeInfo* nodeInfo){
	this->node = nodeInfo;
}

void Device::TestValueIDCallback(NodeInfo *nodeInfo, ValueID valueID, list<ValueCallback*> callbacks){
	if(nodeInfo->m_value_callback.find(valueID) != nodeInfo->m_value_callback.end()){
		for(list<ValueCallback*>::iterator it = callbacks.begin(); it != callbacks.end(); ++it){
			bool found = false;
			list<ValueCallback*> c_list = nodeInfo->m_value_callback[valueID];
			for(list<ValueCallback*>::iterator iti = c_list.begin(); iti != c_list.end(); ++iti){
				if(*iti == *it){
					found = true;
					break;
				}
			}
			if(found == false){
				nodeInfo->m_value_callback[valueID].push_back((*it));
				Log::Write(LogLevel_Info, true, "Device::TestValueIDCallback() : Appending the callback for a value : "
						"Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
						valueID.GetHomeId(), valueID.GetNodeId(),
						genreToStr(valueID.GetGenre()), cclassToStr(valueID.GetCommandClassId()), valueID.GetInstance(),
						valueID.GetIndex(), typeToStr(valueID.GetType()));
			}
		}
	}else{
		nodeInfo->m_value_callback[valueID] = callbacks;
		Log::Write(LogLevel_Info, "Device::TestValueIDCallback() : Adding %d callbacks for a value :"
				"Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
				callbacks.size(), valueID.GetHomeId(), valueID.GetNodeId(),
				genreToStr(valueID.GetGenre()), cclassToStr(valueID.GetCommandClassId()), valueID.GetInstance(),
				valueID.GetIndex(), typeToStr(valueID.GetType()));
	}
}

void  Device::CallValueCallback(NodeInfo *nodeInfo, ValueID valueId, Notification const* notification){
	if(nodeInfo->m_value_callback.find(valueId) != nodeInfo->m_value_callback.end()){
		for(list<ValueCallback*>::iterator it = nodeInfo->m_value_callback[valueId].begin(); it != nodeInfo->m_value_callback[valueId].end(); ++it){
			Log::Write(LogLevel_Info, "Device::CallValueCallback() : calling callback for a value : "
					"Node %d Genre %s Class %s Instance %d Index %d Type %s",
					 nodeInfo->m_nodeId, genreToStr(valueId.GetGenre()), cclassToStr(valueId.GetCommandClassId()), valueId.GetInstance(),
					valueId.GetIndex(), typeToStr(valueId.GetType()));
			(*it)->fn_callback((*it)->fn_device, notification);
		}
	}else{
		Log::Write(LogLevel_Info,"Device::TestValueIDCallback() : can not find any callback for the given value");
	}
}
