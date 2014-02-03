/*
 * BinarySwitch.h
 *
 *  Created on: Nov 1, 2013
 *      Author: vassik
 */

#ifndef BINARYSWITCH_H_
#define BINARYSWITCH_H_

#include "openzwave/ValueID.h"
#include "openzwave/Node.h"

#include "TinyController.h"
#include "../libs/Utility.h"
#include "Device.h"

using namespace OpenZWave;

	class BinarySwitch: public Device
	{
		private:
			ThingMLCallback* turnedOnCallback;
			ThingMLCallback* turnedOffCallback;
			ThingMLCallback* noChangeCallback;

		public:
			static uint8 COMMAND_CLASS;
			list<ValueCallback*> callbacksOnOff;
			bool isTurnedOn;

		public:
			virtual uint8 getComandClass();
			virtual ValueID* getValueId() {return value;};

			BinarySwitch* Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index);

			BinarySwitch();
			BinarySwitch(ThingMLCallback* turnedOnCallback, ThingMLCallback* turnedOffCallback, ThingMLCallback* noChangeCallback);
			virtual void Destroy();
			virtual ~BinarySwitch();

			//commands
			void turnOn();
			void turnOff();

			//commands callback
			static void callback_turnOnOff(Device* _context, Notification const* _data);
	};

#endif /* BINARYSWITCH_H_ */
