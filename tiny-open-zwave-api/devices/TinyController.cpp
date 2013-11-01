/*
 * TinyController.cpp
 *
 *  Created on: Oct 31, 2013
 *      Author: vassik
 */

#include <string>
#include <iostream>

#include "Options.h"
#include "Manager.h"
#include "Node.h"
#include "Group.h"
#include "Notification.h"
#include "Log.h"

#include "TinyController.h"
#include "../libs/DomoZWave.h"
#include "../libs/Utility.h"

using namespace OpenZWave;

TinyController* TinyController::s_instance = NULL;
uint32 TinyController::currentControllerHomeId = 0;
uint8 TinyController::currentControllerNodeId = 0;
Manager::pfnOnNotification_t TinyController::callback = NULL;

//-----------------------------------------------------------------------------
//	<TinyController::Init>
//	Static method to init the singleton.
//-----------------------------------------------------------------------------
TinyController* TinyController::Init(Manager::pfnOnNotification_t _callback,
		char const* config_name, char const* zw_dir,
		char const* domo_log, bool const enableLog,
		bool const enableOZdebug, int polltime){
	if(s_instance == NULL){
		TinyController::callback = _callback;
		Log::Write(LogLevel_Info, "TinyController::Init() : initializing TinyController");
		s_instance = new TinyController(config_name, zw_dir, domo_log, enableLog, enableOZdebug, polltime);
	}
	return s_instance;
}

//-----------------------------------------------------------------------------
//	<TinyController::AddController>
//	Static method to add controller and complete initialization
//-----------------------------------------------------------------------------
void TinyController::AddController(char const* port){
	DomoZWave_AddSerialPort(port);
}


//-----------------------------------------------------------------------------
//	<TinyController::setCurrentController>
//	Static method to set current controller
//-----------------------------------------------------------------------------
void TinyController::setCurrentController(char const* port){
	list<m_structCtrl*>& g_allControllers = DomoZWave_GetGControllers();
	for(list<m_structCtrl*>::iterator it = g_allControllers.begin(); it != g_allControllers.end(); ++it){
		uint32 homeId = (*it)->m_homeId;
		string controllerPath = Manager::Get()->GetControllerPath(homeId);
		string portName = port;
		if(portName == controllerPath){
			TinyController::currentControllerHomeId = homeId;
			TinyController::currentControllerNodeId = (*it)->m_nodeId;
			Log::Write(LogLevel_Info, "TinyController::setCurrentController : %s controller with homeId %08x is set as default", port, currentControllerHomeId);
			break;
		}
	}
	if(currentControllerHomeId == 0){
		Log::Write(LogLevel_Info, "TinyController::setCurrentController : %s controller is not found", port);
	}
}

//-----------------------------------------------------------------------------
//	<TinyController::Destroy>
//	Static method to destroy the singleton.
//-----------------------------------------------------------------------------
void TinyController::Destroy()
{
	delete s_instance;
	s_instance = NULL;
}

//-----------------------------------------------------------------------------
// <TinyController::TinyController>
// Constructor
//-----------------------------------------------------------------------------
TinyController::TinyController(char const* config_name, char const* zw_dir,
		char const* domo_log, bool const enableLog,
		bool const enableOZdebug, int polltime) {
	DomoZWave_Init(domo_log, enableLog);
	Options::Create(config_name, zw_dir, "");

	if (enableOZdebug)
	{
		Options::Get()->AddOptionInt("SaveLogLevel", LogLevel_Detail);
	  	Options::Get()->AddOptionInt("QueueLogLevel", LogLevel_Debug);
	   	Options::Get()->AddOptionInt("DumpTriggerLevel", LogLevel_Error);
	}

	if(polltime != 0){
		Options::Get()->AddOptionInt("PollInterval", polltime);
		Options::Get()->AddOptionBool("IntervalBetweenPolls", true);
		Options::Get()->AddOptionBool("SuppressValueRefresh", false);
		Options::Get()->AddOptionBool("PerformReturnRoutes", false);
	}
	Options::Get()->Lock();

	Manager::Create();
	Manager::Get()->AddWatcher(TinyController::callback, NULL);
	s_instance = this;
}

//-----------------------------------------------------------------------------
// <TinyController::TinyController>
// Destructor
//-----------------------------------------------------------------------------
TinyController::~TinyController() {
	Log::Write(LogLevel_Info, "destroying TinyController object");
	DomoZWave_Destroy();
	Manager::Get()->RemoveWatcher(TinyController::callback, NULL);
	Manager::Get()->Destroy();
	Options::Get()->Destroy();
}



