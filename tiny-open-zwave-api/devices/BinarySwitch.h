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
#include "../observer/NodeSubject.h"

using namespace OpenZWave;

	class BinarySwitch: public Device {
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
			virtual ValueID getValueID() {return *valueID;};
			virtual void setUp(NodeInfo* nodeInfo);

			BinarySwitch* Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index);

			BinarySwitch();
			virtual void Destroy();
			virtual ~BinarySwitch();

			//callbacks
			void setTurnedOnCallback(ThingMLCallback* _callback){turnedOnCallback = _callback;};
			void setTurnedOffCallback(ThingMLCallback* _callback){turnedOffCallback = _callback;};
			void setNoChangeCallback(ThingMLCallback* _callback){noChangeCallback = _callback;};

			//commands
			void turnOn();
			void turnOff();

			//commands callback
			static void callback_turnOnOff(Device* _context, Notification const* _data);

			virtual void update(NodeSubject* subject);
	};

#endif /* BINARYSWITCH_H_ */
