/*****************************************************
 *      THIS IS A GENERATED FILE. DO NOT EDIT.
 *           Header for Thing ZWaveHomeCenter
 *  Generated from ThingML (http://www.thingml.org)
 *****************************************************/

#ifndef ZWaveHomeCenter_H_
#define ZWaveHomeCenter_H_


#include "thingml_typedefs.h"

/*****************************************************************************
 * Headers for type : ZWaveHomeCenter
 *****************************************************************************/


// BEGIN: Code from the c_header annotation ZWaveHomeCenter

#include "tinyozw/TinyZWaveFacade.h"
#include "tinyozw/libs/Utility.h"

using namespace TinyOpenZWaveApi;

// END: Code from the c_header annotation ZWaveHomeCenter

// Definition of the instance stuct:
struct ZWaveHomeCenter_Instance {
// Variables for the ID of the instance
int id;
// Variables for the current instance state
int HomeCenter_behavior_State;
// Variables for the properties of the instance
int HomeCenter_plugid_var;
int HomeCenter_doorwindowid_var;
uint8_t HomeCenter_plugIsInitialized_var;
uint8_t HomeCenter_doorwindowInitialized_var;
uint8_t HomeCenter_plugIsQuiried_var;
uint8_t HomeCenter_doorwindowIsQuiried_var;
const char* Config_pport_var;
const char* Config_config_var;
const char* Config_zwdir_var;
const char* Config_domo_log_var;
uint8_t Config_enableLog_var;
uint8_t Config_enableZWLog_var;
int Config_polltime_var;
};

// Declaration of prototypes outgoing messages:
void HomeCenter_behavior_OnEntry(int state, struct ZWaveHomeCenter_Instance *_instance);
void ZWaveHomeCenter_handle_ctrlport_initialized(struct ZWaveHomeCenter_Instance *_instance);
void ZWaveHomeCenter_handle_ctrlport_controller_ready(struct ZWaveHomeCenter_Instance *_instance);
void ZWaveHomeCenter_handle_ctrlport_node_quiried(struct ZWaveHomeCenter_Instance *_instance, int nodeid);
void ZWaveHomeCenter_handle_plugport_plug_exit(struct ZWaveHomeCenter_Instance *_instance);
void ZWaveHomeCenter_handle_plugport_plug_init(struct ZWaveHomeCenter_Instance *_instance);
void ZWaveHomeCenter_handle_homeintrecport_devicesinitialized(struct ZWaveHomeCenter_Instance *_instance);
void ZWaveHomeCenter_handle_homeintrecport_devicesquiried(struct ZWaveHomeCenter_Instance *_instance);
void ZWaveHomeCenter_handle_doorwindowport_dw_closed(struct ZWaveHomeCenter_Instance *_instance);
void ZWaveHomeCenter_handle_doorwindowport_dw_opened(struct ZWaveHomeCenter_Instance *_instance);
void ZWaveHomeCenter_handle_doorwindowport_dw_init(struct ZWaveHomeCenter_Instance *_instance);
// Declaration of callbacks for incomming messages:
void register_ZWaveHomeCenter_send_homeintsendport_devicesinitialized_listener(void (*_listener)(struct ZWaveHomeCenter_Instance*));
void register_ZWaveHomeCenter_send_homeintsendport_devicesquiried_listener(void (*_listener)(struct ZWaveHomeCenter_Instance*));
void register_ZWaveHomeCenter_send_switchport_turn_on_listener(void (*_listener)(struct ZWaveHomeCenter_Instance*));
void register_ZWaveHomeCenter_send_switchport_turn_off_listener(void (*_listener)(struct ZWaveHomeCenter_Instance*));
void register_ZWaveHomeCenter_send_plugport_init_plug_listener(void (*_listener)(struct ZWaveHomeCenter_Instance*));
void register_ZWaveHomeCenter_send_ctrlport_initialize_listener(void (*_listener)(struct ZWaveHomeCenter_Instance*));
void register_ZWaveHomeCenter_send_ctrlport_start_listener(void (*_listener)(struct ZWaveHomeCenter_Instance*));
void register_ZWaveHomeCenter_send_doorwindowport_init_dw_listener(void (*_listener)(struct ZWaveHomeCenter_Instance*));
void register_ZWaveHomeCenter_send_doorwindowport_start_monitoring_listener(void (*_listener)(struct ZWaveHomeCenter_Instance*));

// Definition of the states:
#define HOMECENTER_BEHAVIOR_STATE 0
#define HOMECENTER_BEHAVIOR_START_STATE 1
#define HOMECENTER_BEHAVIOR_INITDEVICE_STATE 2
#define HOMECENTER_BEHAVIOR_STARTCONTROLLER_STATE 3
#define HOMECENTER_BEHAVIOR_WAITFORDEVICES_STATE 4
#define HOMECENTER_BEHAVIOR_DEVICESAREREADY_STATE 5
#define HOMECENTER_BEHAVIOR_QUIT_STATE 6




#endif //ZWaveHomeCenter_H_