/*
 * MultiLevel.h
 *
 *  Created on: Mar 6, 2014
 *      Author: vassik
 */

#ifndef MULTILEVEL_H_
#define MULTILEVEL_H_

#include "../libs/Utility.h"
#include "Device.h"

namespace TinyOpenZWaveApi {

	class TinyController;
	class NodeSubject;

	class MultiLevel : public Device {
		private:
			ThingMLCallback* valueUpdatedCallback;
			char* currentValue;

		public:
			static uint8 COMMAND_CLASS;

		public:
			MultiLevel();
			virtual ~MultiLevel();

			virtual uint8 getComandClass();
			virtual int setUp(NodeInfo* nodeInfo);
			virtual void finalizeSetUp();

			MultiLevel* Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index);
			char* getCurrentValue();

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
#endif /* MULTILEVEL_H_ */
