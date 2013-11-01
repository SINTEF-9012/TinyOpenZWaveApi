/*
 * TinyController.h
 *
 *  Created on: Oct 31, 2013
 *      Author: vassik
 */

#ifndef TINYCONTROLLER_H_
#define TINYCONTROLLER_H_

#include "Notification.h"
#include "Manager.h"
#include "Defs.h"
#include "Driver.h"
#include "ValueID.h"

using namespace OpenZWave;

	class TinyController
	{
		private:
			TinyController(char const* config_name, char const* zw_dir,
					char const* domo_log, bool const enableLog,
					bool const enableOZdebug, int polltime);
			virtual ~TinyController();
			static TinyController* s_instance;


		public:
			static uint32 currentControllerHomeId;
			static uint8 currentControllerNodeId;
			static Manager::pfnOnNotification_t callback;

		public:
			static TinyController* Init(Manager::pfnOnNotification_t callback,
					char const* config_name, char const* zw_dir,
					char const* domo_log, bool const enableLog,
					bool const enableOZdebug, int polltime);
			static TinyController* Get() {return s_instance;};
			static void AddController(char const* port);
			static void setCurrentController(char const* port);
			static void Destroy();
	};


#endif /* TINYCONTROLLER_H_ */
