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
#include "../observer/ControllerObserver.h"
#include "../observer/ControllerSubject.h"

using namespace OpenZWave;

	class Device;

	class TinyController : public ControllerObserver {
		private:
			list<Device*> devices;
			m_structCtrl* controllerInfo;
			bool isLaunched;

		public:
			static Manager::pfnOnNotification_t OnNotificationCallback;

			uint32 controllerHomeId;
			uint8 controllerNodeId;
			char const* port;

			ThingMLCallback* controllerReadyCallback;
			ThingMLCallback* controllerResetCallback;
			ThingMLCallback* controllerFailedCallback;
			ThingMLCallback* nodeQueriesCompleteCallback;
			ThingMLCallback* allNodeQueriedCallback;
			ThingMLCallback* awakedNodesQueriedCallback;
			ThingMLCallback* allNodesQueriedSomeDeadCallback;

		public:
			TinyController(char const* _port);
			virtual ~TinyController();

			void start();
			list<Device*> getDevices();
			void addDevice(Device* device);
			void setUp(m_structCtrl* _controllerInfo);

			//callbacks
			void setControllerReadyCallback(ThingMLCallback* callback) {controllerReadyCallback = callback;};
			void setControllerResetCallback(ThingMLCallback* callback) {controllerResetCallback = callback;};
			void setControllerFailedCallback(ThingMLCallback* callback) {controllerFailedCallback = callback;};
			void setAllNodeQueriedCallback(ThingMLCallback* callback) {allNodeQueriedCallback = callback;};
			void setAwakedNodesQueriedCallback(ThingMLCallback* callback) {awakedNodesQueriedCallback = callback;};
			void setAllNodesQueriedSomeDeadCallback(ThingMLCallback* callback) {allNodesQueriedSomeDeadCallback = callback;};
			void setNodeQueriesCompleteCallback(ThingMLCallback* callback) {nodeQueriesCompleteCallback = callback;};

			void addController(char const* _port);
			void Destroy();

			//observer
			virtual void update(ControllerSubject* subject);
	};


#endif /* TINYCONTROLLER_H_ */
