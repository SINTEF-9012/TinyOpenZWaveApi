/*
 * NodeSubject.cpp
 *
 *  Created on: Feb 28, 2014
 *      Author: vassik
 */


#include "openzwave/Defs.h"

#include "NodeSubject.h"
#include "NodeObserver.h"

#include "../libs/Utility.h"

using namespace OpenZWave;


NodeSubject::NodeSubject(NodeInfo* _nodeInfo, Notification const* _notification){
	nodeInfo = _nodeInfo;
	notification = _notification;
}

void NodeSubject::attach(NodeObserver* observer){
	this->observers.push_back(observer);
}

void NodeSubject::detach(NodeObserver* observer){
	for(list<NodeObserver*>::iterator it = observers.begin(); it != observers.end(); ++it){
		if(observer == *it){
			observers.erase(it);
			break;
		}
	}
}

void NodeSubject::notify(){
	for(list<NodeObserver*>::iterator it = observers.begin(); it != observers.end(); ++it){
		(*it)->update(this);
	}
}

void NodeSubject::setNodeInfo(NodeInfo* _nodeInfo){
	nodeInfo = _nodeInfo;
}

NodeInfo* NodeSubject::getNodeInfo(){
	return nodeInfo;
}

void NodeSubject::setNotification(Notification const* _notification){
	notification = _notification;
}

Notification const* NodeSubject::getNotification(){
	return notification;
}


