/*
 * Device.h
 *
 *  Created on: Nov 1, 2013
 *      Author: vassik
 */

#ifndef DEVICE_H_
#define DEVICE_H_

#include "openzwave/ValueID.h"
#include "openzwave/Node.h"

#include "TinyController.h"
#include "../libs/Utility.h"
#include "../observer/NodeObserver.h"
#include "../observer/NodeSubject.h"

using namespace OpenZWave;

	class Device : public NodeObserver
	{
		protected:
			ThingMLCallback* deviceInitCallback;

		public:
			static uint8 COMMAND_CLASS;
			uint8 nodeId;
			uint8 instance;
			uint8 index;
			TinyController* controller;
			NodeInfo* node;
			ValueID* value;

		public:
			Device();
			virtual ~Device();

			virtual ValueID* getValueId() {return value;};
			virtual uint8 getComandClass();
			virtual void setUp(NodeInfo* nodeInfo);
			Device* Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index);

			//callbacks
			virtual void setDeviceInitCallback(ThingMLCallback* _callback) {deviceInitCallback = _callback;}; //called when a valueID is added with the corresponds COMMAND CLASS

			virtual void Destroy();

			virtual void update(NodeSubject* subject);

			static void TestValueIDCallback(NodeInfo *nodeInfo, ValueID valueID, list<ValueCallback*> callbacks);
			static void CallValueCallback(NodeInfo *nodeInfo, ValueID valueId, Notification const* notification);
			static void RemoveValueIDCallback(NodeInfo *nodeInfo, ValueID valueID);
	};


#endif /* DEVICE_H_ */
