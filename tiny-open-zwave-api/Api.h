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

	#define MAX_NODES 255
	#define SWITCH_BINARY "SWITCH BINARY"

	class ZValue {
	  friend class ZNode;

	 public:
	  ZValue(ValueID _id);
	  ~ZValue();
	  ValueID getId();
	 private:
	  ValueID id;
	};

	class ZNode {
		public:
			ZNode(int32 const _node_id);
			~ZNode();
			static void Destroy();

		private:
			static int32 nodecount;
			int32 node_id;
			vector<ZValue*> values;

		public:
			static int32 getNodeCount();
			static ZNode* getNode(int32 const _node_id);
			void dropZValueAt(uint8 n);
			void dropZValue(ValueID id);
			void addZValue(ValueID id);
			int32 getValueCount();
			ZValue *getValueAt(uint8 n);
			int32 getNodeId();

			//delete this
			vector<ZValue*> getValueValues();
	};

	class TinyController
	{
		private:
			TinyController();
			virtual ~TinyController();
			static TinyController* s_instance;
			static string port;

		public:
			static TinyController* Init(string port);
			static TinyController* Get() {return s_instance;};
			static void Destroy();
			
			//this should be deleted: just for initial testing
			static void testOnOff();

	};

	class Device
	{
		protected:
			uint8 nodeId;
			uint8 instance;
			uint8 index;
			TinyController* controller;
			ZNode* node;
			ZValue* value;
			virtual uint8 getComandClass();

		public:
			static const char *COMMAND_CLASS;
			Device* Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index);

			virtual ~Device();
	};

	class BinarySwitch: public Device
	{
		protected:
			virtual uint8 getComandClass();

		public:
			static const char *COMMAND_CLASS;

			BinarySwitch* Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index) {return (BinarySwitch*)Device::Init(controller, _nodeId, _instance, _index);};
			BinarySwitch();
			void Destroy();
			virtual ~BinarySwitch();
			
			//commands
			void turnOn();
			void turnOff();
			
	};
};


#endif /* API_H_ */
