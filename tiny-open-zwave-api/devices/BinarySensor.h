/*
 * BinarySensor.h
 *
 *  Created on: Mar 11, 2014
 *      Author: vassik
 */

#ifndef BINARYSENSOR_H_
#define BINARYSENSOR_H_

#include "../libs/Utility.h"
#include "Device.h"

namespace TinyOpenZWaveApi {

class NodeSubject;
class TinyController;

class BinarySensor: public Device {
	private:
		ThingMLCallback* valueUpdatedCallback;
		int currentValue;

	public:
		static uint8 COMMAND_CLASS;

	public:
		BinarySensor();
		virtual ~BinarySensor();

		virtual uint8 getComandClass();
		virtual int setUp(NodeInfo* nodeInfo);
		virtual void finalizeSetUp();

		BinarySensor* Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index);
		int getCurrentValue();

		virtual void Destroy();

		//callback
		void setValueUpdatedCallback(ThingMLCallback* _callback){valueUpdatedCallback = _callback;};

		//commands
		virtual void refresh();

		//commands callback
		static void callback_value_updated(Device* _context, Notification const* _data);

		virtual void update(NodeSubject* subject);
};
}
#endif /* BINARYSENSOR_H_ */
