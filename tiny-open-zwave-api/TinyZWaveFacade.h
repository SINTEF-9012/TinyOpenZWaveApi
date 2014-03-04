/*
 * Api.h
 *
 *  Created on: Oct 17, 2013
 *      Author: vassik
 */

#ifndef API_H_
#define API_H_

#include "openzwave/Driver.h"
#include "openzwave/Notification.h"
#include "openzwave/ValueStore.h"
#include "openzwave/Value.h"
#include "openzwave/ValueBool.h"
#include "openzwave/ValueByte.h"
#include "openzwave/ValueDecimal.h"
#include "openzwave/ValueInt.h"
#include "openzwave/ValueList.h"
#include "openzwave/ValueShort.h"
#include "openzwave/ValueString.h"

#include "libs/Utility.h"
#include "devices/TinyController.h"

namespace TinyOpenZWaveApi {

	using namespace OpenZWave;

	class OpenZWaveFacade {
		public:
			static bool isInitialized;
			static std::map<char const*, TinyController*> controllers;

		public:
			static void Init(char const* config_name, char const* zw_dir,
					char const* domo_log, bool const enableLog,
					bool const enableOZdebug, int polltime);
			static void Quite();

			static TinyController* CreateController(char const* port);
			static TinyController* GetController(char const* port);

	};

};


#endif /* API_H_ */
