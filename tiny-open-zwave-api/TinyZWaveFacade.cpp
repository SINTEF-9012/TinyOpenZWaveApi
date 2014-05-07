
#include "TinyZWaveFacade.h"
#include "devices/TinyController.h"
#include "libs/Utility.h"
#include "libs/ZNode.h"

#include "openzwave/Options.h"
#include "openzwave/Manager.h"
#include "openzwave/Node.h"
#include "openzwave/Group.h"
#include "openzwave/Notification.h"
#include "openzwave/Log.h"


namespace TinyOpenZWaveApi {

bool OpenZWaveFacade::isInitialized = false;

void OpenZWaveFacade::Init(char const* config_name, char const* zw_dir,
		char const* domo_log, bool const enableLog,
		bool const enableOZdebug, int polltime) {
	if(OpenZWaveFacade::isInitialized){
		Log::Write(LogLevel_Info, "OpenZWaveFacade::Init() : OpenZWave is already initialized");
		return;
	}

	Log::Write(LogLevel_Info, "OpenZWaveFacade::Init() : initializing OpenZWave ...");
	ZNode::Init(domo_log, enableLog);
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
	Manager::Get()->AddWatcher(TinyController::OnNotificationCallback, NULL);
	isInitialized = true;
}

void OpenZWaveFacade::Quite(){
	if(!isInitialized)
		return;
	Log::Write(LogLevel_Info, "OpenZWaveFacade::Quite() : destroying OpenZWave ...");
	for(std::map<char const*, TinyController*>::iterator it = ZNode::controllers.begin(); it != ZNode::controllers.end(); ++it)
		it->second->Destroy();
	ZNode::Destroy();
	Manager::Get()->RemoveWatcher(TinyController::OnNotificationCallback, NULL);
	Manager::Get()->Destroy();
	Options::Get()->Destroy();
	isInitialized = false;
	NullValueID::Destroy();
}

TinyController* OpenZWaveFacade::CreateController(char const* port){
	if(!isInitialized){
		Log::Write(LogLevel_Info, "OpenZWaveFacade::CreateController() : init OpenZWave first, aborting...");
		return NULL;
	}

	TinyController *controller = new TinyController(port);
	ZNode::controllers[port] = controller;
	return controller;
}

TinyController* OpenZWaveFacade::GetController(char const* port){
	TinyController* controller = ZNode::FindController(port);
	if(controller == NULL)
		Log::Write(LogLevel_Info, "OpenZWaveFacade::GetController(): can not find controller for %s", port);
	return controller;
}

}
