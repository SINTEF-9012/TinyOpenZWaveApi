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

	typedef void (*CallbackType)(void*);  

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
			static void execute(string const command, void* device, CallbackType callback);

	};

	class Device
	{
		protected:
			uint8 _nodeId;
			uint8 _instance;
			uint8 _index;
			TinyController* controller;

		public:
			Device* Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index);
	};

	class BinarySwitch: public Device
	{

			
		public:
			BinarySwitch* Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index) {return (BinarySwitch*)Device::Init(controller, _nodeId, _instance, _index);};
			BinarySwitch();
			void Destroy();
			virtual ~BinarySwitch();
			
			//commands
			void turnOn();
			void turnOff();

			//instance callbacks
			static void turnedOn_i();
			static void turnedOff_i();			

			//callbacks
			static void turnedOn(void* device) {((BinarySwitch*)device)->turnedOn_i();};
			static void turnedOff(void* device) {((BinarySwitch*)device)->turnedOff_i();};

			
	};
};


#endif /* API_H_ */
