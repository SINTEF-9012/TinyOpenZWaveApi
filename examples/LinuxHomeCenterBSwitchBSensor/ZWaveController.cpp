/*****************************************************
 *      THIS IS A GENERATED FILE. DO NOT EDIT.
 *        Implementation for Thing ZWaveController
 *  Generated from ThingML (http://www.thingml.org)
 *****************************************************/

#include "ZWaveController.h"

/*****************************************************************************
 * Implementation for type : ZWaveController
 *****************************************************************************/

// Declaration of prototypes:
void Controller_behavior_OnExit(int state, struct ZWaveController_Instance *_instance);
void ZWaveController_send_ctrlport_initialized(struct ZWaveController_Instance *_instance);
void ZWaveController_send_ctrlport_controller_ready(struct ZWaveController_Instance *_instance);
void ZWaveController_send_ctrlport_started(struct ZWaveController_Instance *_instance);
void ZWaveController_send_ctrlport_node_quiried(struct ZWaveController_Instance *_instance, int nodeid);
void ZWaveController_send_ctrlport_all_nodes_quiried(struct ZWaveController_Instance *_instance);
void controller_ready_callback(void *_instance, ...);
void all_nodes_quiried_callback(void *_instance, ...);
void node_quiries_completed_callback(void *_instance, ...);
void f_ZWaveController_init_controller(struct ZWaveController_Instance *_instance);
void f_ZWaveController_start_controller(struct ZWaveController_Instance *_instance);

// Declaration of functions:
// Definition of function controller_ready_callback
void controller_ready_callback(void *_instance, ...) {
{
printf("THINGML: -> ZWaveController_send_ctrlport_controller_ready\n");
ZWaveController_send_ctrlport_controller_ready((ZWaveController_Instance *) _instance);
}
}

// Definition of function all_nodes_quiried_callback
void all_nodes_quiried_callback(void *_instance, ...) {
{
printf("THINGML: -> ZWaveController_send_ctrlport_all_nodes_quiried\n");
ZWaveController_send_ctrlport_all_nodes_quiried((ZWaveController_Instance *) _instance);
}
}

// Definition of function node_quiries_completed_callback
void node_quiries_completed_callback(void *_instance, ...) {
{
va_list arguments;
va_start(arguments, _instance);
int nodeid = va_arg(arguments, int);
va_end(arguments);
printf("THINGML: -> ZWaveController_send_ctrlport_node_quiried\n");
ZWaveController_send_ctrlport_node_quiried((ZWaveController_Instance *) _instance, nodeid);
}
}

// Definition of function init_controller
void f_ZWaveController_init_controller(struct ZWaveController_Instance *_instance) {
{
fprintf(stdout, "ZWaveNetwork: initializing ... \n");

ThingMLCallback* controller_ready = new ThingMLCallback(controller_ready_callback, _instance);
ThingMLCallback* all_nodes_quiried = new ThingMLCallback(all_nodes_quiried_callback, _instance);
ThingMLCallback* node_quiries_complete = new ThingMLCallback(node_quiries_completed_callback, _instance);
_instance->Controller_controller_var = OpenZWaveFacade::CreateController(_instance->Config_pport_var);
_instance->Controller_controller_var->setControllerReadyCallback(controller_ready);
_instance->Controller_controller_var->setAllNodeQueriedCallback(all_nodes_quiried);
_instance->Controller_controller_var->setNodeQueriesCompleteCallback(node_quiries_complete);
}
}

// Definition of function start_controller
void f_ZWaveController_start_controller(struct ZWaveController_Instance *_instance) {
{
fprintf(stdout, "ZWaveNetwork: starting ... \n");

_instance->Controller_controller_var->start();
}
}


// On Entry Actions:
void Controller_behavior_OnEntry(int state, struct ZWaveController_Instance *_instance) {
switch(state) {
case CONTROLLER_BEHAVIOR_STATE:
_instance->Controller_behavior_State = CONTROLLER_BEHAVIOR_START_STATE;
Controller_behavior_OnEntry(_instance->Controller_behavior_State, _instance);
break;
case CONTROLLER_BEHAVIOR_START_STATE:
{
fprintf(stdout, "Controller : waiting for command to initialize...\n");

}
break;
case CONTROLLER_BEHAVIOR_INIT_STATE:
{
fprintf(stdout, "Controller : initialize...\n");

f_ZWaveController_init_controller(_instance);
printf("THINGML: -> ZWaveController_send_ctrlport_initialized\n");
ZWaveController_send_ctrlport_initialized(_instance);
}
break;
case CONTROLLER_BEHAVIOR_RUN_STATE:
{
fprintf(stdout, "Controller : run...\n");

f_ZWaveController_start_controller(_instance);
printf("THINGML: -> ZWaveController_send_ctrlport_started\n");
ZWaveController_send_ctrlport_started(_instance);
}
break;
default: break;
}
}

// On Exit Actions:
void Controller_behavior_OnExit(int state, struct ZWaveController_Instance *_instance) {
switch(state) {
case CONTROLLER_BEHAVIOR_STATE:
Controller_behavior_OnExit(_instance->Controller_behavior_State, _instance);
break;
case CONTROLLER_BEHAVIOR_START_STATE:
break;
case CONTROLLER_BEHAVIOR_INIT_STATE:
break;
case CONTROLLER_BEHAVIOR_RUN_STATE:
break;
default: break;
}
}

// Event Handlers for incomming messages:
void ZWaveController_handle_ctrlport_start(struct ZWaveController_Instance *_instance) {
printf("THINGML: <- ZWaveController_handle_ctrlport_start\n");
if (_instance->Controller_behavior_State == CONTROLLER_BEHAVIOR_INIT_STATE) {
if (1) {
Controller_behavior_OnExit(CONTROLLER_BEHAVIOR_INIT_STATE, _instance);
_instance->Controller_behavior_State = CONTROLLER_BEHAVIOR_RUN_STATE;
Controller_behavior_OnEntry(CONTROLLER_BEHAVIOR_RUN_STATE, _instance);
}
}
}
void ZWaveController_handle_ctrlport_initialize(struct ZWaveController_Instance *_instance) {
printf("THINGML: <- ZWaveController_handle_ctrlport_initialize\n");
if (_instance->Controller_behavior_State == CONTROLLER_BEHAVIOR_START_STATE) {
if (1) {
Controller_behavior_OnExit(CONTROLLER_BEHAVIOR_START_STATE, _instance);
_instance->Controller_behavior_State = CONTROLLER_BEHAVIOR_INIT_STATE;
Controller_behavior_OnEntry(CONTROLLER_BEHAVIOR_INIT_STATE, _instance);
}
}
}

// Observers for outgoing messages:
void (*ZWaveController_send_ctrlport_initialized_listener)(struct ZWaveController_Instance*)= 0x0;
void register_ZWaveController_send_ctrlport_initialized_listener(void (*_listener)(struct ZWaveController_Instance*)){
ZWaveController_send_ctrlport_initialized_listener = _listener;
}
void ZWaveController_send_ctrlport_initialized(struct ZWaveController_Instance *_instance){
if (ZWaveController_send_ctrlport_initialized_listener != 0x0) ZWaveController_send_ctrlport_initialized_listener(_instance);
}
void (*ZWaveController_send_ctrlport_controller_ready_listener)(struct ZWaveController_Instance*)= 0x0;
void register_ZWaveController_send_ctrlport_controller_ready_listener(void (*_listener)(struct ZWaveController_Instance*)){
ZWaveController_send_ctrlport_controller_ready_listener = _listener;
}
void ZWaveController_send_ctrlport_controller_ready(struct ZWaveController_Instance *_instance){
if (ZWaveController_send_ctrlport_controller_ready_listener != 0x0) ZWaveController_send_ctrlport_controller_ready_listener(_instance);
}
void (*ZWaveController_send_ctrlport_started_listener)(struct ZWaveController_Instance*)= 0x0;
void register_ZWaveController_send_ctrlport_started_listener(void (*_listener)(struct ZWaveController_Instance*)){
ZWaveController_send_ctrlport_started_listener = _listener;
}
void ZWaveController_send_ctrlport_started(struct ZWaveController_Instance *_instance){
if (ZWaveController_send_ctrlport_started_listener != 0x0) ZWaveController_send_ctrlport_started_listener(_instance);
}
void (*ZWaveController_send_ctrlport_node_quiried_listener)(struct ZWaveController_Instance*, int)= 0x0;
void register_ZWaveController_send_ctrlport_node_quiried_listener(void (*_listener)(struct ZWaveController_Instance*, int)){
ZWaveController_send_ctrlport_node_quiried_listener = _listener;
}
void ZWaveController_send_ctrlport_node_quiried(struct ZWaveController_Instance *_instance, int nodeid){
if (ZWaveController_send_ctrlport_node_quiried_listener != 0x0) ZWaveController_send_ctrlport_node_quiried_listener(_instance, nodeid);
}
void (*ZWaveController_send_ctrlport_all_nodes_quiried_listener)(struct ZWaveController_Instance*)= 0x0;
void register_ZWaveController_send_ctrlport_all_nodes_quiried_listener(void (*_listener)(struct ZWaveController_Instance*)){
ZWaveController_send_ctrlport_all_nodes_quiried_listener = _listener;
}
void ZWaveController_send_ctrlport_all_nodes_quiried(struct ZWaveController_Instance *_instance){
if (ZWaveController_send_ctrlport_all_nodes_quiried_listener != 0x0) ZWaveController_send_ctrlport_all_nodes_quiried_listener(_instance);
}

