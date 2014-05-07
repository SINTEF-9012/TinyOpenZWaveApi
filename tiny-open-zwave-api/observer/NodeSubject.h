/*
 * NodeSubject.h
 *
 *  Created on: Feb 28, 2014
 *      Author: vassik
 */

#ifndef NODESUBJECT_H_
#define NODESUBJECT_H_

#include "../libs/Utility.h"

namespace TinyOpenZWaveApi {

class NodeObserver;

class NodeSubject {

	private:
		NodeInfo* nodeInfo;
		list<NodeObserver*> observers;
		Notification const* notification;

	public:
		NodeSubject(NodeInfo* _nodeInfo, Notification const* _notification);
		~NodeSubject(){};

		void attach(NodeObserver* observer);
		void detach(NodeObserver* observer);
		void notify();

		void setNodeInfo(NodeInfo* _nodeInfo);
		NodeInfo* getNodeInfo();
		void setNotification(Notification const* _notification);
		Notification const* getNotification();
};
}
#endif /* NODESUBJECT_H_ */
