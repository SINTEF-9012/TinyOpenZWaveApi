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

namespace TinyOpenZWaveApi{
	using namespace OpenZWave;

	class OpenZWaveFacade {
		public:
			static TinyController* Init(char const* config_name, char const* zw_dir,
					char const* domo_log, bool const enableLog,
					bool const enableOZdebug, int polltime, ThingMLCallback* callback);
			static TinyController* Get();
	};

};


#endif /* API_H_ */
