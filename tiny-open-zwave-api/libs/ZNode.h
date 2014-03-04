/*
 * ZNode.h
 *
 *  Created on: Feb 27, 2014
 *      Author: vassik
 */

#ifndef ZNODE_H_
#define ZNODE_H_


#include "openzwave/Notification.h"

#include "Utility.h"

using namespace OpenZWave;

class ZNode {
	public:
		static void zwaveInit(const char* logname, bool enableLog);
		static void zwaveDetroy();
		static int32 getNodeCount();
		static ZNode* getNode(int32 const _node_id);
		static NodeInfo* getNodeInfo(Notification const* _data);
		static void addNode(Notification const* _data);
		static void removeNode(Notification const* _data);
		static void newNode(Notification const* _data);

		static void addValue(Notification const* _data);
		static void removeValue(Notification const* _data);
		static void changeValue(Notification const* _data);
		static void refreshedValue(Notification const* _data);

		static void controllerReady(Notification const* _data);
		static m_structCtrl* getControllerInfo(uint32 const homeId);
		static void updateNodeProtocolInfo(uint32 const homeId, uint8 const nodeId);
		static void updateNodeEvent(Notification const* _data);
		static void allNodeQueriedSomeDead(Notification const* _data);
		static void allNodeQueried(Notification const* _data);

		static void messageComplete(Notification const* _data);
		static void messageAwake(Notification const* _data);
		static void messageAlive(Notification const* _data);

		static void typeGroup(Notification const* _data);

		static void deviceAdded(Device* device);
	};


#endif /* ZNODE_H_ */
