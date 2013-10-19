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

	class Api
	{
		private:
			Api();
			virtual ~Api();
			static Api* s_instance;
			static string port;

		public:
			static Api* Init(string port);
			static Api* Get() {return s_instance;};
			static void Destroy();

		public:
			//commands
			void turnOn(uint8 const _nodeId, uint8 const _instance, uint8 const _index);
			void turnOff(uint8 const _nodeId, uint8 const _instance, uint8 const _index);
	};
};


#endif /* API_H_ */
