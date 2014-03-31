/*****************************************************
 *      THIS IS A GENERATED FILE. DO NOT EDIT.
 *        Implementation for Thing FibaroPlug
 *  Generated from ThingML (http://www.thingml.org)
 *****************************************************/

#include "FibaroPlug.h"

/*****************************************************************************
 * Implementation for type : FibaroPlug
 *****************************************************************************/

// Declaration of prototypes:
void Plug_behavior_OnExit(int state, struct FibaroPlug_Instance *_instance);
void FibaroPlug_send_plugport_plug_init(struct FibaroPlug_Instance *_instance);
void FibaroPlug_send_plugport_plug_exit(struct FibaroPlug_Instance *_instance);
void FibaroPlug_send_swintsendport_switch_state(struct FibaroPlug_Instance *_instance, uint8_t swstate);
void FibaroPlug_send_swintsendport_switch_ready(struct FibaroPlug_Instance *_instance);
void FibaroPlug_send_swintsendport_turned_off(struct FibaroPlug_Instance *_instance);
void FibaroPlug_send_swintsendport_no_change(struct FibaroPlug_Instance *_instance);
void FibaroPlug_send_swintsendport_turned_on(struct FibaroPlug_Instance *_instance);
void turned_on_callback(void *_instance, ...);
void turned_off_callback(void *_instance, ...);
void no_change_callback(void *_instance, ...);
void init_callback(void *_instance, ...);
void f_FibaroPlug_init_plug(struct FibaroPlug_Instance *_instance);
void f_FibaroPlug_turn_on(struct FibaroPlug_Instance *_instance);
void f_FibaroPlug_turn_off(struct FibaroPlug_Instance *_instance);
uint8_t f_FibaroPlug_isOn(struct FibaroPlug_Instance *_instance);

// Declaration of functions:
// Definition of function turned_on_callback
void turned_on_callback(void *_instance, ...) {
{
printf("THINGML: -> FibaroPlug_send_swintsendport_turned_on\n");
FibaroPlug_send_swintsendport_turned_on((FibaroPlug_Instance *) _instance);
}
}

// Definition of function turned_off_callback
void turned_off_callback(void *_instance, ...) {
{
printf("THINGML: -> FibaroPlug_send_swintsendport_turned_off\n");
FibaroPlug_send_swintsendport_turned_off((FibaroPlug_Instance *) _instance);
}
}

// Definition of function no_change_callback
void no_change_callback(void *_instance, ...) {
{
printf("THINGML: -> FibaroPlug_send_swintsendport_no_change\n");
FibaroPlug_send_swintsendport_no_change((FibaroPlug_Instance *) _instance);
}
}

// Definition of function init_callback
void init_callback(void *_instance, ...) {
{
printf("THINGML: -> FibaroPlug_send_swintsendport_switch_ready\n");
FibaroPlug_send_swintsendport_switch_ready((FibaroPlug_Instance *) _instance);
}
}

// Definition of function init_plug
void f_FibaroPlug_init_plug(struct FibaroPlug_Instance *_instance) {
{
fprintf(stdout, "FibaroPlug: initializing ... \n");

ThingMLCallback* turned_on = new ThingMLCallback(turned_on_callback, _instance);
ThingMLCallback* turned_off = new ThingMLCallback(turned_off_callback, _instance);
ThingMLCallback* no_change = new ThingMLCallback(no_change_callback, _instance);
ThingMLCallback* device_init = new ThingMLCallback(init_callback, _instance);
_instance->Plug_bs_var = new BinarySwitch();;
_instance->Plug_bs_var = _instance->Plug_bs_var->BinarySwitch::Init(OpenZWaveFacade::GetController(_instance->Config_pport_var), (uint8)_instance->Plug_nodeId_var,(uint8)_instance->Plug_cInstance_var, (uint8)_instance->Plug_cIndex_var);;
_instance->Plug_bs_var->setDeviceInitCallback(device_init);
_instance->Plug_bs_var->setTurnedOnCallback(turned_on);
_instance->Plug_bs_var->setTurnedOffCallback(turned_off);
_instance->Plug_bs_var->setNoChangeCallback(no_change);
}
}

// Definition of function turn_on
void f_FibaroPlug_turn_on(struct FibaroPlug_Instance *_instance) {
{
fprintf(stdout, "FibaroPlug: turning plug on ... \n");

_instance->Plug_bs_var->turnOn();
}
}

// Definition of function turn_off
void f_FibaroPlug_turn_off(struct FibaroPlug_Instance *_instance) {
{
fprintf(stdout, "FibaroPlug: turning plug off ... \n");

_instance->Plug_bs_var->turnOff();
}
}

// Definition of function isOn
uint8_t f_FibaroPlug_isOn(struct FibaroPlug_Instance *_instance) {
{
return _instance->Plug_bs_var->isOn();;
}
}


// On Entry Actions:
void Plug_behavior_OnEntry(int state, struct FibaroPlug_Instance *_instance) {
switch(state) {
case PLUG_BEHAVIOR_STATE:
_instance->Plug_behavior_State = PLUG_BEHAVIOR_START_STATE;
Plug_behavior_OnEntry(_instance->Plug_behavior_State, _instance);
break;
case PLUG_BEHAVIOR_START_STATE:
{
fprintf(stdout, "Plug: starting...\n");

}
break;
case PLUG_BEHAVIOR_READY_STATE:
{
fprintf(stdout, "Plug: initializing...\n");

f_FibaroPlug_init_plug(_instance);
printf("THINGML: -> FibaroPlug_send_plugport_plug_init\n");
FibaroPlug_send_plugport_plug_init(_instance);
}
break;
case PLUG_BEHAVIOR_TURNEDONOROFF_STATE:
{
fprintf(stdout, "Plug: finding out plug state...\n");

printf("THINGML: -> FibaroPlug_send_swintsendport_switch_state\n");
FibaroPlug_send_swintsendport_switch_state(_instance, f_FibaroPlug_isOn(_instance));
}
break;
case PLUG_BEHAVIOR_TURNEDON_STATE:
{
fprintf(stdout, "Plug: is on...\n");

}
break;
case PLUG_BEHAVIOR_TURNINGOFF_STATE:
{
fprintf(stdout, "Plug: attempting to turn off the plug...\n");

f_FibaroPlug_turn_off(_instance);
_instance->Plug_attempts_var = _instance->Plug_attempts_var + 1;
}
break;
case PLUG_BEHAVIOR_TURNEDOFF_STATE:
{
fprintf(stdout, "Plug: is off...\n");

}
break;
case PLUG_BEHAVIOR_TURNINGON_STATE:
{
fprintf(stdout, "Plug: attempting to turn on the plug...\n");

f_FibaroPlug_turn_on(_instance);
_instance->Plug_attempts_var = _instance->Plug_attempts_var + 1;
}
break;
case PLUG_BEHAVIOR_EXIT_STATE:
{
fprintf(stdout, "Plug : exiting...\n");

printf("THINGML: -> FibaroPlug_send_plugport_plug_exit\n");
FibaroPlug_send_plugport_plug_exit(_instance);
}
break;
default: break;
}
}

// On Exit Actions:
void Plug_behavior_OnExit(int state, struct FibaroPlug_Instance *_instance) {
switch(state) {
case PLUG_BEHAVIOR_STATE:
Plug_behavior_OnExit(_instance->Plug_behavior_State, _instance);
break;
case PLUG_BEHAVIOR_START_STATE:
break;
case PLUG_BEHAVIOR_READY_STATE:
break;
case PLUG_BEHAVIOR_TURNEDONOROFF_STATE:
break;
case PLUG_BEHAVIOR_TURNEDON_STATE:
break;
case PLUG_BEHAVIOR_TURNINGOFF_STATE:
break;
case PLUG_BEHAVIOR_TURNEDOFF_STATE:
break;
case PLUG_BEHAVIOR_TURNINGON_STATE:
break;
case PLUG_BEHAVIOR_EXIT_STATE:
break;
default: break;
}
}

// Event Handlers for incomming messages:
void FibaroPlug_handle_switchport_turn_off(struct FibaroPlug_Instance *_instance) {
printf("THINGML: <- FibaroPlug_handle_switchport_turn_off\n");
if (_instance->Plug_behavior_State == PLUG_BEHAVIOR_TURNEDON_STATE) {
if (1) {
Plug_behavior_OnExit(PLUG_BEHAVIOR_TURNEDON_STATE, _instance);
_instance->Plug_behavior_State = PLUG_BEHAVIOR_TURNINGOFF_STATE;
Plug_behavior_OnEntry(PLUG_BEHAVIOR_TURNINGOFF_STATE, _instance);
}
}
}
void FibaroPlug_handle_switchport_turn_on(struct FibaroPlug_Instance *_instance) {
printf("THINGML: <- FibaroPlug_handle_switchport_turn_on\n");
if (_instance->Plug_behavior_State == PLUG_BEHAVIOR_TURNEDOFF_STATE) {
if (1) {
Plug_behavior_OnExit(PLUG_BEHAVIOR_TURNEDOFF_STATE, _instance);
_instance->Plug_behavior_State = PLUG_BEHAVIOR_TURNINGON_STATE;
Plug_behavior_OnEntry(PLUG_BEHAVIOR_TURNINGON_STATE, _instance);
}
}
}
void FibaroPlug_handle_swintrecport_turned_off(struct FibaroPlug_Instance *_instance) {
printf("THINGML: <- FibaroPlug_handle_swintrecport_turned_off\n");
if (_instance->Plug_behavior_State == PLUG_BEHAVIOR_TURNINGOFF_STATE) {
if (_instance->Plug_exit_after_tries_var < _instance->Plug_MAX_EXIT_AFTER_var || _instance->Plug_exit_after_tries_var == _instance->Plug_MAX_EXIT_AFTER_var) {
Plug_behavior_OnExit(PLUG_BEHAVIOR_TURNINGOFF_STATE, _instance);
_instance->Plug_behavior_State = PLUG_BEHAVIOR_TURNEDOFF_STATE;
{
_instance->Plug_exit_after_tries_var = _instance->Plug_exit_after_tries_var + 1;
}
Plug_behavior_OnEntry(PLUG_BEHAVIOR_TURNEDOFF_STATE, _instance);
}
else if (_instance->Plug_exit_after_tries_var > _instance->Plug_MAX_EXIT_AFTER_var) {
Plug_behavior_OnExit(PLUG_BEHAVIOR_TURNINGOFF_STATE, _instance);
_instance->Plug_behavior_State = PLUG_BEHAVIOR_EXIT_STATE;
Plug_behavior_OnEntry(PLUG_BEHAVIOR_EXIT_STATE, _instance);
}
}
}
void FibaroPlug_handle_swintrecport_switch_state(struct FibaroPlug_Instance *_instance, uint8_t swstate) {
printf("THINGML: <- FibaroPlug_handle_swintrecport_switch_state\n");
if (_instance->Plug_behavior_State == PLUG_BEHAVIOR_TURNEDONOROFF_STATE) {
if (swstate) {
Plug_behavior_OnExit(PLUG_BEHAVIOR_TURNEDONOROFF_STATE, _instance);
_instance->Plug_behavior_State = PLUG_BEHAVIOR_TURNEDON_STATE;
Plug_behavior_OnEntry(PLUG_BEHAVIOR_TURNEDON_STATE, _instance);
}
else if ( !swstate) {
Plug_behavior_OnExit(PLUG_BEHAVIOR_TURNEDONOROFF_STATE, _instance);
_instance->Plug_behavior_State = PLUG_BEHAVIOR_TURNEDOFF_STATE;
Plug_behavior_OnEntry(PLUG_BEHAVIOR_TURNEDOFF_STATE, _instance);
}
}
}
void FibaroPlug_handle_swintrecport_switch_ready(struct FibaroPlug_Instance *_instance) {
printf("THINGML: <- FibaroPlug_handle_swintrecport_switch_ready\n");
if (_instance->Plug_behavior_State == PLUG_BEHAVIOR_READY_STATE) {
if (1) {
Plug_behavior_OnExit(PLUG_BEHAVIOR_READY_STATE, _instance);
_instance->Plug_behavior_State = PLUG_BEHAVIOR_TURNEDONOROFF_STATE;
Plug_behavior_OnEntry(PLUG_BEHAVIOR_TURNEDONOROFF_STATE, _instance);
}
}
}
void FibaroPlug_handle_swintrecport_no_change(struct FibaroPlug_Instance *_instance) {
printf("THINGML: <- FibaroPlug_handle_swintrecport_no_change\n");
if (_instance->Plug_behavior_State == PLUG_BEHAVIOR_TURNINGOFF_STATE) {
if (_instance->Plug_attempts_var < _instance->Plug_MAX_ATTEMPTS_var) {
Plug_behavior_OnExit(PLUG_BEHAVIOR_TURNINGOFF_STATE, _instance);
_instance->Plug_behavior_State = PLUG_BEHAVIOR_TURNINGOFF_STATE;
Plug_behavior_OnEntry(PLUG_BEHAVIOR_TURNINGOFF_STATE, _instance);
}
else if (_instance->Plug_attempts_var == _instance->Plug_MAX_ATTEMPTS_var || _instance->Plug_attempts_var > _instance->Plug_MAX_ATTEMPTS_var) {
Plug_behavior_OnExit(PLUG_BEHAVIOR_TURNINGOFF_STATE, _instance);
_instance->Plug_behavior_State = PLUG_BEHAVIOR_TURNEDONOROFF_STATE;
_instance->Plug_attempts_var = 0;
Plug_behavior_OnEntry(PLUG_BEHAVIOR_TURNEDONOROFF_STATE, _instance);
}
}
else if (_instance->Plug_behavior_State == PLUG_BEHAVIOR_TURNINGON_STATE) {
if (_instance->Plug_attempts_var < _instance->Plug_MAX_ATTEMPTS_var) {
Plug_behavior_OnExit(PLUG_BEHAVIOR_TURNINGON_STATE, _instance);
_instance->Plug_behavior_State = PLUG_BEHAVIOR_TURNINGON_STATE;
Plug_behavior_OnEntry(PLUG_BEHAVIOR_TURNINGON_STATE, _instance);
}
else if (_instance->Plug_attempts_var == _instance->Plug_MAX_ATTEMPTS_var || _instance->Plug_attempts_var > _instance->Plug_MAX_ATTEMPTS_var) {
Plug_behavior_OnExit(PLUG_BEHAVIOR_TURNINGON_STATE, _instance);
_instance->Plug_behavior_State = PLUG_BEHAVIOR_TURNEDONOROFF_STATE;
_instance->Plug_attempts_var = 0;
Plug_behavior_OnEntry(PLUG_BEHAVIOR_TURNEDONOROFF_STATE, _instance);
}
}
}
void FibaroPlug_handle_swintrecport_turned_on(struct FibaroPlug_Instance *_instance) {
printf("THINGML: <- FibaroPlug_handle_swintrecport_turned_on\n");
if (_instance->Plug_behavior_State == PLUG_BEHAVIOR_TURNINGON_STATE) {
if (_instance->Plug_exit_after_tries_var < _instance->Plug_MAX_EXIT_AFTER_var || _instance->Plug_exit_after_tries_var == _instance->Plug_MAX_EXIT_AFTER_var) {
Plug_behavior_OnExit(PLUG_BEHAVIOR_TURNINGON_STATE, _instance);
_instance->Plug_behavior_State = PLUG_BEHAVIOR_TURNEDON_STATE;
{
_instance->Plug_exit_after_tries_var = _instance->Plug_exit_after_tries_var + 1;
}
Plug_behavior_OnEntry(PLUG_BEHAVIOR_TURNEDON_STATE, _instance);
}
else if (_instance->Plug_exit_after_tries_var > _instance->Plug_MAX_EXIT_AFTER_var) {
Plug_behavior_OnExit(PLUG_BEHAVIOR_TURNINGON_STATE, _instance);
_instance->Plug_behavior_State = PLUG_BEHAVIOR_EXIT_STATE;
Plug_behavior_OnEntry(PLUG_BEHAVIOR_EXIT_STATE, _instance);
}
}
}
void FibaroPlug_handle_plugport_init_plug(struct FibaroPlug_Instance *_instance) {
printf("THINGML: <- FibaroPlug_handle_plugport_init_plug\n");
if (_instance->Plug_behavior_State == PLUG_BEHAVIOR_START_STATE) {
if (1) {
Plug_behavior_OnExit(PLUG_BEHAVIOR_START_STATE, _instance);
_instance->Plug_behavior_State = PLUG_BEHAVIOR_READY_STATE;
Plug_behavior_OnEntry(PLUG_BEHAVIOR_READY_STATE, _instance);
}
}
}

// Observers for outgoing messages:
void (*FibaroPlug_send_plugport_plug_init_listener)(struct FibaroPlug_Instance*)= 0x0;
void register_FibaroPlug_send_plugport_plug_init_listener(void (*_listener)(struct FibaroPlug_Instance*)){
FibaroPlug_send_plugport_plug_init_listener = _listener;
}
void FibaroPlug_send_plugport_plug_init(struct FibaroPlug_Instance *_instance){
if (FibaroPlug_send_plugport_plug_init_listener != 0x0) FibaroPlug_send_plugport_plug_init_listener(_instance);
}
void (*FibaroPlug_send_plugport_plug_exit_listener)(struct FibaroPlug_Instance*)= 0x0;
void register_FibaroPlug_send_plugport_plug_exit_listener(void (*_listener)(struct FibaroPlug_Instance*)){
FibaroPlug_send_plugport_plug_exit_listener = _listener;
}
void FibaroPlug_send_plugport_plug_exit(struct FibaroPlug_Instance *_instance){
if (FibaroPlug_send_plugport_plug_exit_listener != 0x0) FibaroPlug_send_plugport_plug_exit_listener(_instance);
}
void (*FibaroPlug_send_swintsendport_switch_state_listener)(struct FibaroPlug_Instance*, uint8_t)= 0x0;
void register_FibaroPlug_send_swintsendport_switch_state_listener(void (*_listener)(struct FibaroPlug_Instance*, uint8_t)){
FibaroPlug_send_swintsendport_switch_state_listener = _listener;
}
void FibaroPlug_send_swintsendport_switch_state(struct FibaroPlug_Instance *_instance, uint8_t swstate){
if (FibaroPlug_send_swintsendport_switch_state_listener != 0x0) FibaroPlug_send_swintsendport_switch_state_listener(_instance, swstate);
}
void (*FibaroPlug_send_swintsendport_switch_ready_listener)(struct FibaroPlug_Instance*)= 0x0;
void register_FibaroPlug_send_swintsendport_switch_ready_listener(void (*_listener)(struct FibaroPlug_Instance*)){
FibaroPlug_send_swintsendport_switch_ready_listener = _listener;
}
void FibaroPlug_send_swintsendport_switch_ready(struct FibaroPlug_Instance *_instance){
if (FibaroPlug_send_swintsendport_switch_ready_listener != 0x0) FibaroPlug_send_swintsendport_switch_ready_listener(_instance);
}
void (*FibaroPlug_send_swintsendport_turned_off_listener)(struct FibaroPlug_Instance*)= 0x0;
void register_FibaroPlug_send_swintsendport_turned_off_listener(void (*_listener)(struct FibaroPlug_Instance*)){
FibaroPlug_send_swintsendport_turned_off_listener = _listener;
}
void FibaroPlug_send_swintsendport_turned_off(struct FibaroPlug_Instance *_instance){
if (FibaroPlug_send_swintsendport_turned_off_listener != 0x0) FibaroPlug_send_swintsendport_turned_off_listener(_instance);
}
void (*FibaroPlug_send_swintsendport_no_change_listener)(struct FibaroPlug_Instance*)= 0x0;
void register_FibaroPlug_send_swintsendport_no_change_listener(void (*_listener)(struct FibaroPlug_Instance*)){
FibaroPlug_send_swintsendport_no_change_listener = _listener;
}
void FibaroPlug_send_swintsendport_no_change(struct FibaroPlug_Instance *_instance){
if (FibaroPlug_send_swintsendport_no_change_listener != 0x0) FibaroPlug_send_swintsendport_no_change_listener(_instance);
}
void (*FibaroPlug_send_swintsendport_turned_on_listener)(struct FibaroPlug_Instance*)= 0x0;
void register_FibaroPlug_send_swintsendport_turned_on_listener(void (*_listener)(struct FibaroPlug_Instance*)){
FibaroPlug_send_swintsendport_turned_on_listener = _listener;
}
void FibaroPlug_send_swintsendport_turned_on(struct FibaroPlug_Instance *_instance){
if (FibaroPlug_send_swintsendport_turned_on_listener != 0x0) FibaroPlug_send_swintsendport_turned_on_listener(_instance);
}

