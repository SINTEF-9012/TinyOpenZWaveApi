/*****************************************************
 *      THIS IS A GENERATED FILE. DO NOT EDIT.
 *           Header for Thing FibaroPlug
 *  Generated from ThingML (http://www.thingml.org)
 *****************************************************/

#ifndef FibaroPlug_H_
#define FibaroPlug_H_


#include "thingml_typedefs.h"

/*****************************************************************************
 * Headers for type : FibaroPlug
 *****************************************************************************/


// BEGIN: Code from the c_header annotation FibaroPlug

#include "tinyozw/TinyZWaveFacade.h"
#include "tinyozw/devices/BinarySwitch.h"
#include "tinyozw/libs/Utility.h"

using namespace TinyOpenZWaveApi;

// END: Code from the c_header annotation FibaroPlug

// Definition of the instance stuct:
struct FibaroPlug_Instance {
// Variables for the ID of the instance
int id;
// Variables for the current instance state
int Plug_behavior_State;
// Variables for the properties of the instance
int Plug_nodeId_var;
int Plug_cInstance_var;
int Plug_cIndex_var;
BinarySwitch* Plug_bs_var;
int Plug_attempts_var;
int Plug_exit_after_tries_var;
int Plug_MAX_ATTEMPTS_var;
int Plug_MAX_EXIT_AFTER_var;
const char* Config_pport_var;
const char* Config_config_var;
const char* Config_zwdir_var;
const char* Config_domo_log_var;
uint8_t Config_enableLog_var;
uint8_t Config_enableZWLog_var;
int Config_polltime_var;
};

// Declaration of prototypes outgoing messages:
void Plug_behavior_OnEntry(int state, struct FibaroPlug_Instance *_instance);
void FibaroPlug_handle_switchport_turn_off(struct FibaroPlug_Instance *_instance);
void FibaroPlug_handle_switchport_turn_on(struct FibaroPlug_Instance *_instance);
void FibaroPlug_handle_swintrecport_turned_off(struct FibaroPlug_Instance *_instance);
void FibaroPlug_handle_swintrecport_switch_state(struct FibaroPlug_Instance *_instance, uint8_t swstate);
void FibaroPlug_handle_swintrecport_switch_ready(struct FibaroPlug_Instance *_instance);
void FibaroPlug_handle_swintrecport_no_change(struct FibaroPlug_Instance *_instance);
void FibaroPlug_handle_swintrecport_turned_on(struct FibaroPlug_Instance *_instance);
void FibaroPlug_handle_plugport_init_plug(struct FibaroPlug_Instance *_instance);
// Declaration of callbacks for incomming messages:
void register_FibaroPlug_send_plugport_plug_init_listener(void (*_listener)(struct FibaroPlug_Instance*));
void register_FibaroPlug_send_plugport_plug_exit_listener(void (*_listener)(struct FibaroPlug_Instance*));
void register_FibaroPlug_send_swintsendport_switch_state_listener(void (*_listener)(struct FibaroPlug_Instance*, uint8_t));
void register_FibaroPlug_send_swintsendport_switch_ready_listener(void (*_listener)(struct FibaroPlug_Instance*));
void register_FibaroPlug_send_swintsendport_turned_off_listener(void (*_listener)(struct FibaroPlug_Instance*));
void register_FibaroPlug_send_swintsendport_no_change_listener(void (*_listener)(struct FibaroPlug_Instance*));
void register_FibaroPlug_send_swintsendport_turned_on_listener(void (*_listener)(struct FibaroPlug_Instance*));

// Definition of the states:
#define PLUG_BEHAVIOR_STATE 0
#define PLUG_BEHAVIOR_START_STATE 1
#define PLUG_BEHAVIOR_READY_STATE 2
#define PLUG_BEHAVIOR_TURNEDONOROFF_STATE 3
#define PLUG_BEHAVIOR_TURNEDON_STATE 4
#define PLUG_BEHAVIOR_TURNINGOFF_STATE 5
#define PLUG_BEHAVIOR_TURNEDOFF_STATE 6
#define PLUG_BEHAVIOR_TURNINGON_STATE 7
#define PLUG_BEHAVIOR_EXIT_STATE 8




#endif //FibaroPlug_H_