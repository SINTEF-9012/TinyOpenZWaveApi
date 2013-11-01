/*
 * Device.cpp
 *
 *  Created on: Nov 1, 2013
 *      Author: vassik
 */

#include "Log.h"
#include "Node.h"

#include "TinyController.h"
#include "Device.h"
#include "../libs/DomoZWave.h"
#include "../libs/types.h"

using namespace OpenZWave;


Device* Device::Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index) {
	this->node = NULL;
	this->value = NULL;
	this->controller = controller;
	this->nodeId = _nodeId;
	this->instance = _instance;
	this->index = _index;
	list<NodeInfo*>& g_nodes = DomoZWave_GetGNodes();
	for(list<NodeInfo*>::iterator it=g_nodes.begin(); it!=g_nodes.end(); ++it){
		uint8 nodeId = (*it)->m_nodeId;
		uint32 homeId = (*it)->m_homeId;
		if(nodeId == _nodeId && homeId == controller->currentControllerHomeId){
			this->node = *it;
			break;
		}
	}
	if(this->node == NULL){
		Log::Write(LogLevel_Info, "Device::Init(): can not find node with id %d", this->nodeId);
	}
	return this;
}

uint8 Device::getComandClass(){
	return COMMAND_CLASS;
}

Device::~Device() {
	delete this;
}