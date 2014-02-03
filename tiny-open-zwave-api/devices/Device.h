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

using namespace OpenZWave;

	class Device
	{
		public:
			uint8 nodeId;
			uint8 instance;
			uint8 index;
			TinyController* controller;
			NodeInfo* node;
			ValueID* value;
			virtual uint8 getComandClass();

		public:
			virtual ValueID* getValueId() {return value;};
			static uint8 COMMAND_CLASS;
			Device* Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index);

			virtual void Destroy();
			virtual ~Device();
	};

	//-------------------------------------------------------------------------
	//Structures for a valueID callback
	//-------------------------------------------------------------------------

	typedef void (*pvfCallback)(Device *_device, Notification const* _data);

	struct ValueCallback {
		pvfCallback fn_callback;
		Device *fn_device;

		ValueCallback(pvfCallback _callback, Device *_device):
			fn_callback(_callback),
			fn_device(_device){
		};
	};


#endif /* DEVICE_H_ */
