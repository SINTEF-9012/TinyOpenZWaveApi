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


NodeSubject::NodeSubject(NodeInfo* nodeInfo){
	this->nodeInfo = nodeInfo;
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

void NodeSubject::notify(NObInfo* info){
	for(list<NodeObserver*>::iterator it = observers.begin(); it != observers.end(); ++it){
		(*it)->update(info);
	}
}

NodeInfo* NodeSubject::getNodeInfo(){
	return this->nodeInfo;
}


