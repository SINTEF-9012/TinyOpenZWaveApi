/*****************************************************
 *      THIS IS A GENERATED FILE. DO NOT EDIT.
 *           Header for Thing ZWaveController
 *  Generated from ThingML (http://www.thingml.org)
 *****************************************************/

#ifndef ZWaveController_H_
#define ZWaveController_H_


#include "thingml_typedefs.h"

/*****************************************************************************
 * Headers for type : ZWaveController
 *****************************************************************************/


// BEGIN: Code from the c_header annotation ZWaveController

#include <stdlib.h>
#include <cstdarg>
#include "tinyozw/TinyZWaveFacade.h"
#include "tinyozw/devices/TinyController.h"
#include "tinyozw/libs/Utility.h"

using namespace TinyOpenZWaveApi;

// END: Code from the c_header annotation ZWaveController

// Definition of the instance stuct:
struct ZWaveController_Instance {
// Variables for the ID of the instance
int id;
// Variables for the current instance state
int Controller_behavior_State;
// Variables for the properties of the instance
TinyController* Controller_controller_var;
const char* Config_pport_var;
const char* Config_config_var;
const char* Config_zwdir_var;
const char* Config_domo_log_var;
uint8_t Config_enableLog_var;
uint8_t Config_enableZWLog_var;
int Config_polltime_var;
};

// Declaration of prototypes outgoing messages:
void Controller_behavior_OnEntry(int state, struct ZWaveController_Instance *_instance);
void ZWaveController_handle_ctrlport_start(struct ZWaveController_Instance *_instance);
void ZWaveController_handle_ctrlport_initialize(struct ZWaveController_Instance *_instance);
// Declaration of callbacks for incomming messages:
void register_ZWaveController_send_ctrlport_initialized_listener(void (*_listener)(struct ZWaveController_Instance*));
void register_ZWaveController_send_ctrlport_controller_ready_listener(void (*_listener)(struct ZWaveController_Instance*));
void register_ZWaveController_send_ctrlport_started_listener(void (*_listener)(struct ZWaveController_Instance*));
void register_ZWaveController_send_ctrlport_node_quiried_listener(void (*_listener)(struct ZWaveController_Instance*, int));
void register_ZWaveController_send_ctrlport_all_nodes_quiried_listener(void (*_listener)(struct ZWaveController_Instance*));

// Definition of the states:
#define CONTROLLER_BEHAVIOR_STATE 0
#define CONTROLLER_BEHAVIOR_START_STATE 1
#define CONTROLLER_BEHAVIOR_INIT_STATE 2
#define CONTROLLER_BEHAVIOR_RUN_STATE 3




#endif //ZWaveController_H_