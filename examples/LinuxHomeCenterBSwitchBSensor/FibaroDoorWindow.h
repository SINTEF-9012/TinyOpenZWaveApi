/*****************************************************
 *      THIS IS A GENERATED FILE. DO NOT EDIT.
 *           Header for Thing FibaroDoorWindow
 *  Generated from ThingML (http://www.thingml.org)
 *****************************************************/

#ifndef FibaroDoorWindow_H_
#define FibaroDoorWindow_H_


#include "thingml_typedefs.h"

/*****************************************************************************
 * Headers for type : FibaroDoorWindow
 *****************************************************************************/


// BEGIN: Code from the c_header annotation FibaroDoorWindow

#include <stdlib.h>
#include <cstdarg>
#include "tinyozw/TinyZWaveFacade.h"
#include "tinyozw/devices/BinarySensor.h"
#include "tinyozw/libs/Utility.h"

using namespace TinyOpenZWaveApi;

// END: Code from the c_header annotation FibaroDoorWindow

// Definition of the instance stuct:
struct FibaroDoorWindow_Instance {
// Variables for the ID of the instance
int id;
// Variables for the current instance state
int DoorWindow_behavior_State;
// Variables for the properties of the instance
int DoorWindow_nodeId_var;
int DoorWindow_cInstance_var;
int DoorWindow_cIndex_var;
BinarySensor* DoorWindow_bs_var;
int DoorWindow_dwstate_var;
const char* Config_pport_var;
const char* Config_config_var;
const char* Config_zwdir_var;
const char* Config_domo_log_var;
uint8_t Config_enableLog_var;
uint8_t Config_enableZWLog_var;
int Config_polltime_var;
};

// Declaration of prototypes outgoing messages:
void DoorWindow_behavior_OnEntry(int state, struct FibaroDoorWindow_Instance *_instance);
void FibaroDoorWindow_handle_dwintrecport_dw_ready(struct FibaroDoorWindow_Instance *_instance);
void FibaroDoorWindow_handle_dwintrecport_dw_changed(struct FibaroDoorWindow_Instance *_instance, int dwstate);
void FibaroDoorWindow_handle_doorwindowport_start_monitoring(struct FibaroDoorWindow_Instance *_instance);
void FibaroDoorWindow_handle_doorwindowport_init_dw(struct FibaroDoorWindow_Instance *_instance);
// Declaration of callbacks for incomming messages:
void register_FibaroDoorWindow_send_doorwindowport_dw_closed_listener(void (*_listener)(struct FibaroDoorWindow_Instance*));
void register_FibaroDoorWindow_send_doorwindowport_dw_opened_listener(void (*_listener)(struct FibaroDoorWindow_Instance*));
void register_FibaroDoorWindow_send_doorwindowport_dw_init_listener(void (*_listener)(struct FibaroDoorWindow_Instance*));
void register_FibaroDoorWindow_send_doorwindowport_ready_to_monitor_listener(void (*_listener)(struct FibaroDoorWindow_Instance*));
void register_FibaroDoorWindow_send_dwintsendport_dw_changed_listener(void (*_listener)(struct FibaroDoorWindow_Instance*, int));
void register_FibaroDoorWindow_send_dwintsendport_dw_ready_listener(void (*_listener)(struct FibaroDoorWindow_Instance*));

// Definition of the states:
#define DOORWINDOW_BEHAVIOR_STATE 0
#define DOORWINDOW_BEHAVIOR_START_STATE 1
#define DOORWINDOW_BEHAVIOR_INIT_STATE 2
#define DOORWINDOW_BEHAVIOR_READY_STATE 3
#define DOORWINDOW_BEHAVIOR_CLOSED_STATE 4
#define DOORWINDOW_BEHAVIOR_OPENED_STATE 5




#endif //FibaroDoorWindow_H_