/*
 * Api.h
 *
 *  Created on: Oct 17, 2013
 *      Author: vassik
 */

#ifndef API_H_
#define API_H_

#include "devices/TinyController.h"

namespace TinyOpenZWaveApi {


	class OpenZWaveFacade {
		public:
			static bool isInitialized;

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
