/*
 * BinarySwitch.h
 *
 *  Created on: Nov 1, 2013
 *      Author: vassik
 */

#ifndef BINARYSWITCH_H_
#define BINARYSWITCH_H_

#include "ValueID.h"
#include "Node.h"

#include "TinyController.h"
#include "../libs/Utility.h"
#include "Device.h"

using namespace OpenZWave;

	class BinarySwitch: public Device
	{
		protected:
			virtual uint8 getComandClass();

		public:
			static uint8 COMMAND_CLASS;
			list<ValueCallback*> callbacksOnOff;

		public:
			virtual ValueID* getValueId() {return value;};

			BinarySwitch* Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index) {return (BinarySwitch*)Device::Init(controller, _nodeId, _instance, _index);};
			BinarySwitch();
			void Destroy();
			virtual ~BinarySwitch();

			//commands
			void turnOn();
			void turnOff();

			//commands callback
			static void callback_turnOnOff(Device* _context, Notification const* _data);
	};

#endif /* BINARYSWITCH_H_ */
