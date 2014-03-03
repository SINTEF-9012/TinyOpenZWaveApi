/*
 * TinyController.h
 *
 *  Created on: Oct 31, 2013
 *      Author: vassik
 */

#ifndef TINYCONTROLLER_H_
#define TINYCONTROLLER_H_

#include "openzwave/Notification.h"
#include "openzwave/Manager.h"
#include "openzwave/Defs.h"
#include "openzwave/Driver.h"
#include "openzwave/ValueID.h"
#include "../libs/Utility.h"


using namespace OpenZWave;

	class Device;

	class TinyController
	{
		private:
			TinyController(char const* config_name, char const* zw_dir,
					char const* domo_log, bool const enableLog,
					bool const enableOZdebug, int polltime);
			virtual ~TinyController();
			static TinyController* s_instance;
			list<Device*> devices;


		public:
			static uint32 currentControllerHomeId;
			static uint8 currentControllerNodeId;
			static Manager::pfnOnNotification_t callback;
			ThingMLCallback* controllerReadyCallback;
			ThingMLCallback* controllerResetCallback;
			ThingMLCallback* controllerFailedCallback;
			ThingMLCallback* allNodeQueriedCallback;
			ThingMLCallback* awakedNodesQueriedCallback;
			ThingMLCallback* allNodesQueriedSomeDeadCallback;

		public:
			static TinyController* Get() {return s_instance;};
			static TinyController* SetConfiguration(char const* config_name, char const* zw_dir,
					char const* domo_log, bool const enableLog,
					bool const enableOZdebug, int polltime);

			void start();
			list<Device*> getDevices();
			void addDevice(Device* device);

			//callbacks
			void setControllerReadyCallback(ThingMLCallback* callback) {controllerReadyCallback = callback;};
			void setControllerResetCallback(ThingMLCallback* callback) {controllerResetCallback = callback;};
			void setControllerFailedCallback(ThingMLCallback* callback) {controllerFailedCallback = callback;};
			void setAllNodeQueriedCallback(ThingMLCallback* callback) {allNodeQueriedCallback = callback;};
			void setAwakedNodesQueriedCallback(ThingMLCallback* callback) {awakedNodesQueriedCallback = callback;};
			void setAllNodesQueriedSomeDeadCallback(ThingMLCallback* callback) {allNodesQueriedSomeDeadCallback = callback;};

			static void AddController(char const* port);
			static void setCurrentController(char const* port);
			static void Destroy();
	};


#endif /* TINYCONTROLLER_H_ */
