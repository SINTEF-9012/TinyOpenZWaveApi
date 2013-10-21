/*
 * znode.cpp
 *
 *  Created on: Oct 19, 2013
 *      Author: vassik
 */

#include "znode.h"
#include "Log.h"

using namespace TinyOpenZWaveApi;

ZNode *nodes[MAX_NODES];
int32 ZNode::nodecount = 0;

ZValue::ZValue(ValueID _id) : id(_id) {};

ValueID ZValue::getId(){
	return id;
}

ZValue::~ZValue(){
	delete this;
}

void ZNode::Destroy(){
	for(int i=0; i<MAX_NODES; i++){
		delete nodes[i];
	}
}

ZNode::~ZNode(){
	Log::Write(LogLevel_Info, "~ZNode(): clearing data for the node %d...", this->getNodeId());
	while (!values.empty()) {
		ZValue *v = values.back();
	    values.pop_back();
	    delete v;
	}
}

ZNode::ZNode(int32 const _node_id){
	node_id = _node_id;
	if (_node_id < 1 || _node_id >= MAX_NODES) {
		Log::Write(LogLevel_Info, "ZNode(): bad node value %d, ignoring...", _node_id);
		delete this;
		return;
	}
	Log::Write(LogLevel_Info, "ZNode(): adding node value %d, ignoring...", _node_id);
	nodes[node_id] = this;
	nodecount ++;
}

int32 ZNode::getNodeCount(){
	return nodecount;
}

void ZNode::addZValue(ValueID _valueId){
	ZValue *zvalue = new ZValue(_valueId);
	values.push_back(zvalue);
}

void ZNode::dropZValueAt(uint8 n){
	uint8 size = values.size();
	if(size > n){
		Log::Write(LogLevel_Info, "cannot drop value at %d, current size is %d ignoring...", n, size);
		return;
	}
	vector<ZValue*>::iterator it;
	uint8 i = 0;
	while(it!=values.end() && i != n){
		if(i == size){
			values.erase(it);
			break;
		}
		it++;
		i++;
	}
}

ZValue* ZNode::getValueAt(uint8 n){
	uint8 size = values.size();
	if(size > n){
		Log::Write(LogLevel_Info, "cannot get value at %d, current size is %d ignoring...", n, size);
		return NULL;
	}
	return values[n];
}

int32 ZNode::getNodeId(){
	return node_id;
}



