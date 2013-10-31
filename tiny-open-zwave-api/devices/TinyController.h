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

typedef void (*pfnOnNotification_t)( Notification const* _pNotification, void* _context );

	class TinyController
	{
		private:
			TinyController();
			virtual ~TinyController();
			static TinyController* s_instance;


		public:
			static uint32 currentControllerHomeId;
			static uint8 currentControllerNodeId;
			static pfnOnNotification_t notification;

		public:
			static TinyController* Init();
			static TinyController* Get() {return s_instance;};
			static void AddController(char const* port);
			static void setCurrentController(char const* port);
			static void Destroy();

			//this should be deleted: just for initial testing
			static void testOnOff();

	};


#endif /* TINYCONTROLLER_H_ */
