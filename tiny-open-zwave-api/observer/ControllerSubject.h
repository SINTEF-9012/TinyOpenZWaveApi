/*
 * ControllerSubject.h
 *
 *  Created on: Mar 4, 2014
 *      Author: vassik
 */

#ifndef CONTROLLERSUBJECT_H_
#define CONTROLLERSUBJECT_H_

#include "openzwave/Notification.h"
#include "openzwave/Defs.h"

#include "ControllerObserver.h"
#include "../libs/Utility.h"

using namespace OpenZWave;

class ControllerSubject {

	private:
		m_structCtrl* ctrlInfo;
		Notification const* notification;
		list<ControllerObserver*> observers;

	public:
		ControllerSubject(m_structCtrl* _ctrlInfo, Notification const* _notification);
		~ControllerSubject();

		void attach(ControllerObserver* observer);
		void detach(ControllerObserver* observer);
		void notify();

		void setControllerInfo(m_structCtrl* _ctrlInfo);
		m_structCtrl* getControllerInfo();
		void setNotification(Notification const* notification);
		Notification const* getNotification();
};


#endif /* CONTROLLERSUBJECT_H_ */