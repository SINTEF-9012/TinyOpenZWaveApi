/*
 * NodeSubject.h
 *
 *  Created on: Feb 28, 2014
 *      Author: vassik
 */

#ifndef NODESUBJECT_H_
#define NODESUBJECT_H_


#include "openzwave/Defs.h"

#include "NodeObserver.h"
#include "../libs/Utility.h"

using namespace OpenZWave;

class NodeSubject {

	private:
		NodeInfo* nodeInfo;
		list<NodeObserver*> observers;

	public:
		NodeSubject(NodeInfo* nodeInfo);
		~NodeSubject(){};

		void attach(NodeObserver* observer);
		void detach(NodeObserver* observer);
		void notify(NObInfo* info);

		NodeInfo* getNodeInfo();
};


#endif /* NODESUBJECT_H_ */
