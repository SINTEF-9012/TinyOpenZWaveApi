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
			virtual ValueID* getValueId() {return value;};
			static uint8 COMMAND_CLASS;

			BinarySwitch* Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index) {return (BinarySwitch*)Device::Init(controller, _nodeId, _instance, _index);};
			BinarySwitch();
			void Destroy();
			virtual ~BinarySwitch();

			//commands
			void turnOn();
			void turnOff();
	};

#endif /* BINARYSWITCH_H_ */