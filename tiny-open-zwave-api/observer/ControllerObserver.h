/*
 * ControllerObserver.h
 *
 *  Created on: Mar 4, 2014
 *      Author: vassik
 */

#ifndef CONTROLLEROBSERVER_H_
#define CONTROLLEROBSERVER_H_

#include "openzwave/Defs.h"

using namespace OpenZWave;

class ControllerSubject;

class ControllerObserver {

	public:
		ControllerObserver() {};
		virtual ~ControllerObserver() {};

		virtual void update(ControllerSubject* subject) {};
};



#endif /* CONTROLLEROBSERVER_H_ */
