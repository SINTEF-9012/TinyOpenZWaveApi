
#include "TinyZWaveFacade.h"
#include "devices/TinyController.h"

#include "openzwave/Log.h"


using namespace TinyOpenZWaveApi;


TinyController* OpenZWaveFacade::Init(char const* config_name, char const* zw_dir,
		char const* domo_log, bool const enableLog,
		bool const enableOZdebug, int polltime, ThingMLCallback* callback){
	TinyController* controller = TinyController::SetConfiguration(config_name, zw_dir, domo_log, enableLog, enableOZdebug, polltime);
	controller->setControllerReadyCallback(callback);
	return controller;
}

TinyController* OpenZWaveFacade::Get(){
	TinyController *controller = TinyController::Get();
	if(controller == NULL){
		Log::Write(LogLevel_Info, "OpenZWaveFacade::Get(): controller is not initialized, call OpenZWaveFacade::Init first");
	}
	return controller;
}
