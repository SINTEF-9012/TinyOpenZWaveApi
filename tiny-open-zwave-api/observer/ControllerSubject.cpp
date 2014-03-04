/*
 * ControllerSubject.cpp
 *
 *  Created on: Mar 4, 2014
 *      Author: vassik
 */

#include "openzwave/Notification.h"

#include "ControllerSubject.h"
#include "ControllerObserver.h"
#include "../libs/Utility.h"


using namespace OpenZWave;


ControllerSubject::ControllerSubject(m_structCtrl* _ctrlInfo, Notification const* _notification){
	ctrlInfo = _ctrlInfo;
	notification = _notification;
}

void ControllerSubject::attach(ControllerObserver* observer){
	this->observers.push_back(observer);
}

void ControllerSubject::detach(ControllerObserver* observer){
	for(list<ControllerObserver*>::iterator it = observers.begin(); it != observers.end(); ++it){
		if(observer == *it){
			observers.erase(it);
			break;
		}
	}
}

void ControllerSubject::notify(){
	for(list<ControllerObserver*>::iterator it = observers.begin(); it != observers.end(); ++it){
		(*it)->update(this);
	}
}

void ControllerSubject::setControllerInfo(m_structCtrl* _ctrlInfo){
	ctrlInfo = _ctrlInfo;
}

m_structCtrl* ControllerSubject::getControllerInfo(){
	return ctrlInfo;
}

void ControllerSubject::setNotification(Notification const* _notification){
	notification = _notification;
}

Notification const* ControllerSubject::getNotification(){
	return notification;
}
