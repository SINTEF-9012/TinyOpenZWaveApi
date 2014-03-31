/*****************************************************
 *      THIS IS A GENERATED FILE. DO NOT EDIT.
 *        Implementation for Thing FibaroDoorWindow
 *  Generated from ThingML (http://www.thingml.org)
 *****************************************************/

#include "FibaroDoorWindow.h"

/*****************************************************************************
 * Implementation for type : FibaroDoorWindow
 *****************************************************************************/

// Declaration of prototypes:
void DoorWindow_behavior_OnExit(int state, struct FibaroDoorWindow_Instance *_instance);
void FibaroDoorWindow_send_doorwindowport_dw_closed(struct FibaroDoorWindow_Instance *_instance);
void FibaroDoorWindow_send_doorwindowport_dw_opened(struct FibaroDoorWindow_Instance *_instance);
void FibaroDoorWindow_send_doorwindowport_dw_init(struct FibaroDoorWindow_Instance *_instance);
void FibaroDoorWindow_send_doorwindowport_ready_to_monitor(struct FibaroDoorWindow_Instance *_instance);
void FibaroDoorWindow_send_dwintsendport_dw_changed(struct FibaroDoorWindow_Instance *_instance, int dwstate);
void FibaroDoorWindow_send_dwintsendport_dw_ready(struct FibaroDoorWindow_Instance *_instance);
void init_binarysensor_callback(void *_instance, ...);
void value_change_binarysensor_callback(void *_instance, ...);
void f_FibaroDoorWindow_init_doorwindow(struct FibaroDoorWindow_Instance *_instance);
int f_FibaroDoorWindow_getState(struct FibaroDoorWindow_Instance *_instance);

// Declaration of functions:
// Definition of function init_binarysensor_callback
void init_binarysensor_callback(void *_instance, ...) {
{
printf("THINGML: -> FibaroDoorWindow_send_dwintsendport_dw_ready\n");
FibaroDoorWindow_send_dwintsendport_dw_ready((FibaroDoorWindow_Instance *) _instance);
}
}

// Definition of function value_change_binarysensor_callback
void value_change_binarysensor_callback(void *_instance, ...) {
{
va_list arguments;
va_start(arguments, _instance);
int state = va_arg(arguments, int);
va_end(arguments);
printf("THINGML: -> FibaroDoorWindow_send_dwintsendport_dw_changed\n");
FibaroDoorWindow_send_dwintsendport_dw_changed((FibaroDoorWindow_Instance *) _instance, state);
}
}

// Definition of function init_doorwindow
void f_FibaroDoorWindow_init_doorwindow(struct FibaroDoorWindow_Instance *_instance) {
{
fprintf(stdout, "FibaroDoorWindow: initializing ... \n");

ThingMLCallback* value_changed = new ThingMLCallback(value_change_binarysensor_callback, _instance);
ThingMLCallback* device_init = new ThingMLCallback(init_binarysensor_callback, _instance);
_instance->DoorWindow_bs_var = new BinarySensor();;
_instance->DoorWindow_bs_var = _instance->DoorWindow_bs_var->BinarySensor::Init(OpenZWaveFacade::GetController(_instance->Config_pport_var), (uint8)_instance->DoorWindow_nodeId_var,(uint8)_instance->DoorWindow_cInstance_var, (uint8)_instance->DoorWindow_cIndex_var);;
_instance->DoorWindow_bs_var->setDeviceInitCallback(device_init);
_instance->DoorWindow_bs_var->setValueUpdatedCallback(value_changed);
}
}

// Definition of function getState
int f_FibaroDoorWindow_getState(struct FibaroDoorWindow_Instance *_instance) {
{
return _instance->DoorWindow_bs_var->getCurrentValue();
}
}


// On Entry Actions:
void DoorWindow_behavior_OnEntry(int state, struct FibaroDoorWindow_Instance *_instance) {
switch(state) {
case DOORWINDOW_BEHAVIOR_STATE:
_instance->DoorWindow_behavior_State = DOORWINDOW_BEHAVIOR_START_STATE;
DoorWindow_behavior_OnEntry(_instance->DoorWindow_behavior_State, _instance);
break;
case DOORWINDOW_BEHAVIOR_START_STATE:
{
fprintf(stdout, "DoorWindow: starting...\n");

}
break;
case DOORWINDOW_BEHAVIOR_INIT_STATE:
{
fprintf(stdout, "DoorWindow: initializing...\n");

f_FibaroDoorWindow_init_doorwindow(_instance);
printf("THINGML: -> FibaroDoorWindow_send_doorwindowport_dw_init\n");
FibaroDoorWindow_send_doorwindowport_dw_init(_instance);
}
break;
case DOORWINDOW_BEHAVIOR_READY_STATE:
{
fprintf(stdout, "DoorWindow: ready ...\n");

printf("THINGML: -> FibaroDoorWindow_send_doorwindowport_ready_to_monitor\n");
FibaroDoorWindow_send_doorwindowport_ready_to_monitor(_instance);
}
break;
case DOORWINDOW_BEHAVIOR_CLOSED_STATE:
{
fprintf(stdout, "DoorWindow: closed...\n");

}
break;
case DOORWINDOW_BEHAVIOR_OPENED_STATE:
{
fprintf(stdout, "DoorWindow: opened...\n");

}
break;
default: break;
}
}

// On Exit Actions:
void DoorWindow_behavior_OnExit(int state, struct FibaroDoorWindow_Instance *_instance) {
switch(state) {
case DOORWINDOW_BEHAVIOR_STATE:
DoorWindow_behavior_OnExit(_instance->DoorWindow_behavior_State, _instance);
break;
case DOORWINDOW_BEHAVIOR_START_STATE:
break;
case DOORWINDOW_BEHAVIOR_INIT_STATE:
break;
case DOORWINDOW_BEHAVIOR_READY_STATE:
break;
case DOORWINDOW_BEHAVIOR_CLOSED_STATE:
break;
case DOORWINDOW_BEHAVIOR_OPENED_STATE:
break;
default: break;
}
}

// Event Handlers for incomming messages:
void FibaroDoorWindow_handle_dwintrecport_dw_ready(struct FibaroDoorWindow_Instance *_instance) {
printf("THINGML: <- FibaroDoorWindow_handle_dwintrecport_dw_ready\n");
if (_instance->DoorWindow_behavior_State == DOORWINDOW_BEHAVIOR_INIT_STATE) {
if (1) {
DoorWindow_behavior_OnExit(DOORWINDOW_BEHAVIOR_INIT_STATE, _instance);
_instance->DoorWindow_behavior_State = DOORWINDOW_BEHAVIOR_READY_STATE;
{
_instance->DoorWindow_dwstate_var = f_FibaroDoorWindow_getState(_instance);
}
DoorWindow_behavior_OnEntry(DOORWINDOW_BEHAVIOR_READY_STATE, _instance);
}
}
}
void FibaroDoorWindow_handle_dwintrecport_dw_changed(struct FibaroDoorWindow_Instance *_instance, int dwstate) {
printf("THINGML: <- FibaroDoorWindow_handle_dwintrecport_dw_changed\n");
if (_instance->DoorWindow_behavior_State == DOORWINDOW_BEHAVIOR_CLOSED_STATE) {
if (dwstate == 0) {
DoorWindow_behavior_OnExit(DOORWINDOW_BEHAVIOR_CLOSED_STATE, _instance);
_instance->DoorWindow_behavior_State = DOORWINDOW_BEHAVIOR_OPENED_STATE;
{
printf("THINGML: -> FibaroDoorWindow_send_doorwindowport_dw_opened\n");
FibaroDoorWindow_send_doorwindowport_dw_opened(_instance);
}
DoorWindow_behavior_OnEntry(DOORWINDOW_BEHAVIOR_OPENED_STATE, _instance);
}
}
else if (_instance->DoorWindow_behavior_State == DOORWINDOW_BEHAVIOR_OPENED_STATE) {
if (dwstate == 1) {
DoorWindow_behavior_OnExit(DOORWINDOW_BEHAVIOR_OPENED_STATE, _instance);
_instance->DoorWindow_behavior_State = DOORWINDOW_BEHAVIOR_CLOSED_STATE;
{
printf("THINGML: -> FibaroDoorWindow_send_doorwindowport_dw_closed\n");
FibaroDoorWindow_send_doorwindowport_dw_closed(_instance);
}
DoorWindow_behavior_OnEntry(DOORWINDOW_BEHAVIOR_CLOSED_STATE, _instance);
}
}
}
void FibaroDoorWindow_handle_doorwindowport_start_monitoring(struct FibaroDoorWindow_Instance *_instance) {
printf("THINGML: <- FibaroDoorWindow_handle_doorwindowport_start_monitoring\n");
if (_instance->DoorWindow_behavior_State == DOORWINDOW_BEHAVIOR_READY_STATE) {
if (_instance->DoorWindow_dwstate_var == 0) {
DoorWindow_behavior_OnExit(DOORWINDOW_BEHAVIOR_READY_STATE, _instance);
_instance->DoorWindow_behavior_State = DOORWINDOW_BEHAVIOR_CLOSED_STATE;
DoorWindow_behavior_OnEntry(DOORWINDOW_BEHAVIOR_CLOSED_STATE, _instance);
}
else if (_instance->DoorWindow_dwstate_var == 1) {
DoorWindow_behavior_OnExit(DOORWINDOW_BEHAVIOR_READY_STATE, _instance);
_instance->DoorWindow_behavior_State = DOORWINDOW_BEHAVIOR_OPENED_STATE;
DoorWindow_behavior_OnEntry(DOORWINDOW_BEHAVIOR_OPENED_STATE, _instance);
}
}
}
void FibaroDoorWindow_handle_doorwindowport_init_dw(struct FibaroDoorWindow_Instance *_instance) {
printf("THINGML: <- FibaroDoorWindow_handle_doorwindowport_init_dw\n");
if (_instance->DoorWindow_behavior_State == DOORWINDOW_BEHAVIOR_START_STATE) {
if (1) {
DoorWindow_behavior_OnExit(DOORWINDOW_BEHAVIOR_START_STATE, _instance);
_instance->DoorWindow_behavior_State = DOORWINDOW_BEHAVIOR_INIT_STATE;
DoorWindow_behavior_OnEntry(DOORWINDOW_BEHAVIOR_INIT_STATE, _instance);
}
}
}

// Observers for outgoing messages:
void (*FibaroDoorWindow_send_doorwindowport_dw_closed_listener)(struct FibaroDoorWindow_Instance*)= 0x0;
void register_FibaroDoorWindow_send_doorwindowport_dw_closed_listener(void (*_listener)(struct FibaroDoorWindow_Instance*)){
FibaroDoorWindow_send_doorwindowport_dw_closed_listener = _listener;
}
void FibaroDoorWindow_send_doorwindowport_dw_closed(struct FibaroDoorWindow_Instance *_instance){
if (FibaroDoorWindow_send_doorwindowport_dw_closed_listener != 0x0) FibaroDoorWindow_send_doorwindowport_dw_closed_listener(_instance);
}
void (*FibaroDoorWindow_send_doorwindowport_dw_opened_listener)(struct FibaroDoorWindow_Instance*)= 0x0;
void register_FibaroDoorWindow_send_doorwindowport_dw_opened_listener(void (*_listener)(struct FibaroDoorWindow_Instance*)){
FibaroDoorWindow_send_doorwindowport_dw_opened_listener = _listener;
}
void FibaroDoorWindow_send_doorwindowport_dw_opened(struct FibaroDoorWindow_Instance *_instance){
if (FibaroDoorWindow_send_doorwindowport_dw_opened_listener != 0x0) FibaroDoorWindow_send_doorwindowport_dw_opened_listener(_instance);
}
void (*FibaroDoorWindow_send_doorwindowport_dw_init_listener)(struct FibaroDoorWindow_Instance*)= 0x0;
void register_FibaroDoorWindow_send_doorwindowport_dw_init_listener(void (*_listener)(struct FibaroDoorWindow_Instance*)){
FibaroDoorWindow_send_doorwindowport_dw_init_listener = _listener;
}
void FibaroDoorWindow_send_doorwindowport_dw_init(struct FibaroDoorWindow_Instance *_instance){
if (FibaroDoorWindow_send_doorwindowport_dw_init_listener != 0x0) FibaroDoorWindow_send_doorwindowport_dw_init_listener(_instance);
}
void (*FibaroDoorWindow_send_doorwindowport_ready_to_monitor_listener)(struct FibaroDoorWindow_Instance*)= 0x0;
void register_FibaroDoorWindow_send_doorwindowport_ready_to_monitor_listener(void (*_listener)(struct FibaroDoorWindow_Instance*)){
FibaroDoorWindow_send_doorwindowport_ready_to_monitor_listener = _listener;
}
void FibaroDoorWindow_send_doorwindowport_ready_to_monitor(struct FibaroDoorWindow_Instance *_instance){
if (FibaroDoorWindow_send_doorwindowport_ready_to_monitor_listener != 0x0) FibaroDoorWindow_send_doorwindowport_ready_to_monitor_listener(_instance);
}
void (*FibaroDoorWindow_send_dwintsendport_dw_changed_listener)(struct FibaroDoorWindow_Instance*, int)= 0x0;
void register_FibaroDoorWindow_send_dwintsendport_dw_changed_listener(void (*_listener)(struct FibaroDoorWindow_Instance*, int)){
FibaroDoorWindow_send_dwintsendport_dw_changed_listener = _listener;
}
void FibaroDoorWindow_send_dwintsendport_dw_changed(struct FibaroDoorWindow_Instance *_instance, int dwstate){
if (FibaroDoorWindow_send_dwintsendport_dw_changed_listener != 0x0) FibaroDoorWindow_send_dwintsendport_dw_changed_listener(_instance, dwstate);
}
void (*FibaroDoorWindow_send_dwintsendport_dw_ready_listener)(struct FibaroDoorWindow_Instance*)= 0x0;
void register_FibaroDoorWindow_send_dwintsendport_dw_ready_listener(void (*_listener)(struct FibaroDoorWindow_Instance*)){
FibaroDoorWindow_send_dwintsendport_dw_ready_listener = _listener;
}
void FibaroDoorWindow_send_dwintsendport_dw_ready(struct FibaroDoorWindow_Instance *_instance){
if (FibaroDoorWindow_send_dwintsendport_dw_ready_listener != 0x0) FibaroDoorWindow_send_dwintsendport_dw_ready_listener(_instance);
}

