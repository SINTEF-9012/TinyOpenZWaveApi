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
#include "../devices/TinyController.h"
#include "../observer/NodeSubject.h"
#include "../observer/ControllerSubject.h"

using namespace OpenZWave;

class ZNode {
	public:
		static map<char const*, TinyController*> controllers;
		static map<uint8, NodeSubject*> m_nodeSub;
		static map<uint32, ControllerSubject*> m_ctrlSub;

		static void Init(const char* logname, bool enableLog);
		static void Destroy();
		static TinyController* FindController(char const* port);
		static int32 GetNodeCount();
		static ZNode* GetNode(int32 const _node_id);
		static NodeInfo* GetNodeInfo(Notification const* _data);
		static void AddNode(Notification const* _data);
		static void RemoveNode(Notification const* _data);
		static void NewNode(Notification const* _data);

		static void AddValue(Notification const* _data);
		static void RemoveValue(Notification const* _data);
		static void ChangeValue(Notification const* _data);
		static void RefreshedValue(Notification const* _data);

		static void ControllerReady(Notification const* _data);
		static void ControllerReset(Notification const* _data);
		static void ControllerFailed(Notification const* _data);

		static m_structCtrl* GetControllerInfo(uint32 const homeId);
		static void UpdateNodeProtocolInfo(uint32 const homeId, uint8 const nodeId);
		static void UpdateNodeEvent(Notification const* _data);
		static void AllNodeQueriedSomeDead(Notification const* _data);
		static void AllNodeQueried(Notification const* _data);
		static void AwakeNodesQueried(Notification const* _data);
		static void NodeQueriesComplete(Notification const* _data);

		static void MessageComplete(Notification const* _data);
		static void MessageAwake(Notification const* _data);
		static void MessageAlive(Notification const* _data);

		static void TypeGroup(Notification const* _data);

		static void DeviceAdded(Device* device);
		static char* GetValueIDValue(ValueID valueID);
		static void SetValueIDValue(ValueID valueID, int32 value);
	};


#endif /* ZNODE_H_ */
