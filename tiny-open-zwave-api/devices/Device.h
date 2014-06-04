/*
 * Device.h
 *
 *  Created on: Nov 1, 2013
 *      Author: vassik
 */

#ifndef DEVICE_H_
#define DEVICE_H_

#include "../libs/Utility.h"
#include "../observer/NodeObserver.h"

namespace TinyOpenZWaveApi {

	class NodeSubject;
	class TinyController;

	class Device : public NodeObserver
	{
		protected:
			ThingMLCallback* deviceInitCallback;
			const char* DEVICE_NAME;
			uint8 nodeId;
			uint8 instance;
			uint8 index;
			TinyController* controller;
			NodeInfo* node;
			ValueID* valueID;
			list<ValueCallback*> callbacks;
			time_t valueLastSeen;

		public:
			static uint8 COMMAND_CLASS;

		public:
			Device();
			virtual ~Device();

			virtual uint8 getNodeId() {return nodeId;};
			virtual uint8 getInstance() {return instance;};
			virtual uint8 getIndex() {return index;};
			virtual NodeInfo* getNodeInfo() {return node;};
			virtual TinyController* getController() {return controller;};
			virtual const char* getDeviceName() {return DEVICE_NAME;};
			virtual ValueID getValueID() {return *valueID;};
			virtual uint8 getComandClass();
			virtual int setUp(NodeInfo* nodeInfo);
			virtual void finalizeSetUp();
			Device* Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index);

			//callbacks
			virtual void setDeviceInitCallback(ThingMLCallback* _callback) {deviceInitCallback = _callback;}; //called when a valueID is added with the corresponds COMMAND CLASS

			virtual void Destroy();

			virtual void update(NodeSubject* subject);
			virtual void refresh() = 0;

			static void TestValueIDCallback(NodeInfo *nodeInfo, ValueID valueID, list<ValueCallback*> callbacks);
			static void CallValueCallback(NodeInfo *nodeInfo, ValueID valueId, Notification const* notification);
			static void RemoveValueIDCallback(NodeInfo *nodeInfo, ValueID valueID);
	};
}

#endif /* DEVICE_H_ */
