/*
 * NodeObserver.h
 *
 *  Created on: Feb 28, 2014
 *      Author: vassik
 */

#ifndef NODEOBSERVER_H_
#define NODEOBSERVER_H_

#include "openzwave/Defs.h"
#include "openzwave/Notification.h"

#include "../libs/Utility.h"

using namespace OpenZWave;

class NodeObserver {

	public:
		virtual void update(NObInfo* info){};

		virtual ~NodeObserver(){};
};


#endif /* NODEOBSERVER_H_ */
