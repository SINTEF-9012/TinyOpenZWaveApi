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
