/*
 * Api.h
 *
 *  Created on: Oct 17, 2013
 *      Author: vassik
 */

#ifndef API_H_
#define API_H_

#include "Driver.h"
#include "Notification.h"
#include "ValueStore.h"
#include "Value.h"
#include "ValueBool.h"
#include "ValueByte.h"
#include "ValueDecimal.h"
#include "ValueInt.h"
#include "ValueList.h"
#include "ValueShort.h"
#include "ValueString.h"

#include "libs/types.h"
#include "devices/TinyController.h"
#include "devices/Device.h"


using namespace OpenZWave;

extern const char *valueGenreStr(ValueID::ValueGenre);
extern ValueID::ValueGenre valueGenreNum(char const *);
extern const char *valueTypeStr(ValueID::ValueType);
extern ValueID::ValueType valueTypeNum(char const *);
extern const char *nodeBasicStr(uint8);
extern const char *cclassStr(uint8);
extern uint8 cclassNum(char const *str);
extern const char *controllerErrorStr(Driver::ControllerError err);

namespace TinyOpenZWaveApi{
	using namespace std;

	class ZNode {
		public:
			static int32 getNodeCount();
			static ZNode* getNode(int32 const _node_id);
			static NodeInfo* getNodeInfo(Notification const* _data);
			static void addNode(Notification const* _data);
			static void addValue(Notification const* _data);
			static void removeNode(Notification const* _data);
			static void removeValue(Notification const* _data);
			static void changeValue(Notification const* _data);
			static void controllerReady(Notification const* _data);
			static m_structCtrl* getControllerInfo(uint32 const homeId);
	};


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
			
			//ZValue* getValueToPull();

	};
};


#endif /* API_H_ */
