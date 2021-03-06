/*
 * BinarySwitch.h
 *
 *  Created on: Nov 1, 2013
 *      Author: vassik
 */

#ifndef BINARYSWITCH_H_
#define BINARYSWITCH_H_

#include "../libs/Utility.h"
#include "Device.h"

namespace TinyOpenZWaveApi {

	class NodeSubject;
	class TinyController;

	class BinarySwitch: public Device {
		private:
			ThingMLCallback* turnedOnCallback;
			ThingMLCallback* turnedOffCallback;
			ThingMLCallback* noChangeCallback;
			bool isTurnedOn;

		public:
			static uint8 COMMAND_CLASS;

		public:
			BinarySwitch();
			virtual ~BinarySwitch();

			virtual uint8 getComandClass();
			virtual int setUp(NodeInfo* nodeInfo);
			virtual void finalizeSetUp();

			BinarySwitch* Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index);
			bool isOn() {return isTurnedOn;};

			virtual void Destroy();

			//callbacks
			void setTurnedOnCallback(ThingMLCallback* _callback){turnedOnCallback = _callback;};
			void setTurnedOffCallback(ThingMLCallback* _callback){turnedOffCallback = _callback;};
			void setNoChangeCallback(ThingMLCallback* _callback){noChangeCallback = _callback;};

			//commands
			void turnOn();
			void turnOff();
			virtual void refresh();

			//commands callback
			static void callback_turn_on_off(Device* _context, Notification const* _data);

			virtual void update(NodeSubject* subject);
		};
	}

#endif /* BINARYSWITCH_H_ */
