/*****************************************************
 *      THIS IS A GENERATED FILE. DO NOT EDIT.
 *        Implementation for Thing ZWaveHomeCenter
 *  Generated from ThingML (http://www.thingml.org)
 *****************************************************/

#include "ZWaveHomeCenter.h"

/*****************************************************************************
 * Implementation for type : ZWaveHomeCenter
 *****************************************************************************/

// Declaration of prototypes:
void HomeCenter_behavior_OnExit(int state, struct ZWaveHomeCenter_Instance *_instance);
void ZWaveHomeCenter_send_homeintsendport_devicesinitialized(struct ZWaveHomeCenter_Instance *_instance);
void ZWaveHomeCenter_send_homeintsendport_devicesquiried(struct ZWaveHomeCenter_Instance *_instance);
void ZWaveHomeCenter_send_switchport_turn_on(struct ZWaveHomeCenter_Instance *_instance);
void ZWaveHomeCenter_send_switchport_turn_off(struct ZWaveHomeCenter_Instance *_instance);
void ZWaveHomeCenter_send_plugport_init_plug(struct ZWaveHomeCenter_Instance *_instance);
void ZWaveHomeCenter_send_ctrlport_initialize(struct ZWaveHomeCenter_Instance *_instance);
void ZWaveHomeCenter_send_ctrlport_start(struct ZWaveHomeCenter_Instance *_instance);
void ZWaveHomeCenter_send_doorwindowport_init_dw(struct ZWaveHomeCenter_Instance *_instance);
void ZWaveHomeCenter_send_doorwindowport_start_monitoring(struct ZWaveHomeCenter_Instance *_instance);
void f_ZWaveHomeCenter_init_network(struct ZWaveHomeCenter_Instance *_instance);
void f_ZWaveHomeCenter_quite_network(struct ZWaveHomeCenter_Instance *_instance);

// Declaration of functions:
// Definition of function init_network
void f_ZWaveHomeCenter_init_network(struct ZWaveHomeCenter_Instance *_instance) {
{
OpenZWaveFacade::Init(_instance->Config_config_var,_instance->Config_zwdir_var,_instance->Config_domo_log_var,_instance->Config_enableLog_var,_instance->Config_enableZWLog_var,_instance->Config_polltime_var);
}
}

// Definition of function quite_network
void f_ZWaveHomeCenter_quite_network(struct ZWaveHomeCenter_Instance *_instance) {
{
OpenZWaveFacade::Quite();
}
}


// On Entry Actions:
void HomeCenter_behavior_OnEntry(int state, struct ZWaveHomeCenter_Instance *_instance) {
switch(state) {
case HOMECENTER_BEHAVIOR_STATE:
_instance->HomeCenter_behavior_State = HOMECENTER_BEHAVIOR_START_STATE;
HomeCenter_behavior_OnEntry(_instance->HomeCenter_behavior_State, _instance);
break;
case HOMECENTER_BEHAVIOR_START_STATE:
{
fprintf(stdout, "HomeCenter: initialize network ...\n");

f_ZWaveHomeCenter_init_network(_instance);
printf("THINGML: -> ZWaveHomeCenter_send_ctrlport_initialize\n");
ZWaveHomeCenter_send_ctrlport_initialize(_instance);
}
break;
case HOMECENTER_BEHAVIOR_INITDEVICE_STATE:
{
fprintf(stdout, "HomeCenter: initialize home device ...\n");

printf("THINGML: -> ZWaveHomeCenter_send_plugport_init_plug\n");
ZWaveHomeCenter_send_plugport_init_plug(_instance);
printf("THINGML: -> ZWaveHomeCenter_send_doorwindowport_init_dw\n");
ZWaveHomeCenter_send_doorwindowport_init_dw(_instance);
}
break;
case HOMECENTER_BEHAVIOR_STARTCONTROLLER_STATE:
{
fprintf(stdout, "HomeCenter: start controller ...\n");

printf("THINGML: -> ZWaveHomeCenter_send_ctrlport_start\n");
ZWaveHomeCenter_send_ctrlport_start(_instance);
}
break;
case HOMECENTER_BEHAVIOR_WAITFORDEVICES_STATE:
{
fprintf(stdout, "HomeCenter: waiting for device to be quiried ...\n");

}
break;
case HOMECENTER_BEHAVIOR_DEVICESAREREADY_STATE:
{
fprintf(stdout, "HomeCenter: all devices are ready to use");

printf("THINGML: -> ZWaveHomeCenter_send_doorwindowport_start_monitoring\n");
ZWaveHomeCenter_send_doorwindowport_start_monitoring(_instance);
}
break;
case HOMECENTER_BEHAVIOR_QUIT_STATE:
{
fprintf(stdout, "HomeCenter: Quit...\n");

f_ZWaveHomeCenter_quite_network(_instance);
}
break;
default: break;
}
}

// On Exit Actions:
void HomeCenter_behavior_OnExit(int state, struct ZWaveHomeCenter_Instance *_instance) {
switch(state) {
case HOMECENTER_BEHAVIOR_STATE:
HomeCenter_behavior_OnExit(_instance->HomeCenter_behavior_State, _instance);
break;
case HOMECENTER_BEHAVIOR_START_STATE:
break;
case HOMECENTER_BEHAVIOR_INITDEVICE_STATE:
break;
case HOMECENTER_BEHAVIOR_STARTCONTROLLER_STATE:
break;
case HOMECENTER_BEHAVIOR_WAITFORDEVICES_STATE:
break;
case HOMECENTER_BEHAVIOR_DEVICESAREREADY_STATE:
break;
case HOMECENTER_BEHAVIOR_QUIT_STATE:
break;
default: break;
}
}

// Event Handlers for incomming messages:
void ZWaveHomeCenter_handle_ctrlport_initialized(struct ZWaveHomeCenter_Instance *_instance) {
printf("THINGML: <- ZWaveHomeCenter_handle_ctrlport_initialized\n");
if (_instance->HomeCenter_behavior_State == HOMECENTER_BEHAVIOR_START_STATE) {
if (1) {
HomeCenter_behavior_OnExit(HOMECENTER_BEHAVIOR_START_STATE, _instance);
_instance->HomeCenter_behavior_State = HOMECENTER_BEHAVIOR_INITDEVICE_STATE;
HomeCenter_behavior_OnEntry(HOMECENTER_BEHAVIOR_INITDEVICE_STATE, _instance);
}
}
}
void ZWaveHomeCenter_handle_ctrlport_controller_ready(struct ZWaveHomeCenter_Instance *_instance) {
printf("THINGML: <- ZWaveHomeCenter_handle_ctrlport_controller_ready\n");
if (_instance->HomeCenter_behavior_State == HOMECENTER_BEHAVIOR_STARTCONTROLLER_STATE) {
if (1) {
HomeCenter_behavior_OnExit(HOMECENTER_BEHAVIOR_STARTCONTROLLER_STATE, _instance);
_instance->HomeCenter_behavior_State = HOMECENTER_BEHAVIOR_WAITFORDEVICES_STATE;
HomeCenter_behavior_OnEntry(HOMECENTER_BEHAVIOR_WAITFORDEVICES_STATE, _instance);
}
}
}
void ZWaveHomeCenter_handle_ctrlport_node_quiried(struct ZWaveHomeCenter_Instance *_instance, int nodeid) {
printf("THINGML: <- ZWaveHomeCenter_handle_ctrlport_node_quiried\n");
if (_instance->HomeCenter_behavior_State == HOMECENTER_BEHAVIOR_WAITFORDEVICES_STATE) {
if (nodeid == _instance->HomeCenter_plugid_var) {
{
fprintf(stdout, "HomeCenter: plug is quiried ...\n");

_instance->HomeCenter_plugIsQuiried_var = 1;
if(_instance->HomeCenter_plugIsQuiried_var && _instance->HomeCenter_doorwindowIsQuiried_var) {
printf("THINGML: -> ZWaveHomeCenter_send_homeintsendport_devicesquiried\n");
ZWaveHomeCenter_send_homeintsendport_devicesquiried(_instance);
}
}
}
else if (nodeid == _instance->HomeCenter_doorwindowid_var) {
{
fprintf(stdout, "HomeCenter: doorwindow is quiried ...\n");

_instance->HomeCenter_doorwindowIsQuiried_var = 1;
if(_instance->HomeCenter_plugIsQuiried_var && _instance->HomeCenter_doorwindowIsQuiried_var) {
printf("THINGML: -> ZWaveHomeCenter_send_homeintsendport_devicesquiried\n");
ZWaveHomeCenter_send_homeintsendport_devicesquiried(_instance);
}
}
}
}
}
void ZWaveHomeCenter_handle_plugport_plug_exit(struct ZWaveHomeCenter_Instance *_instance) {
printf("THINGML: <- ZWaveHomeCenter_handle_plugport_plug_exit\n");
if (_instance->HomeCenter_behavior_State == HOMECENTER_BEHAVIOR_DEVICESAREREADY_STATE) {
if (1) {
HomeCenter_behavior_OnExit(HOMECENTER_BEHAVIOR_DEVICESAREREADY_STATE, _instance);
_instance->HomeCenter_behavior_State = HOMECENTER_BEHAVIOR_QUIT_STATE;
HomeCenter_behavior_OnEntry(HOMECENTER_BEHAVIOR_QUIT_STATE, _instance);
}
}
}
void ZWaveHomeCenter_handle_plugport_plug_init(struct ZWaveHomeCenter_Instance *_instance) {
printf("THINGML: <- ZWaveHomeCenter_handle_plugport_plug_init\n");
if (_instance->HomeCenter_behavior_State == HOMECENTER_BEHAVIOR_INITDEVICE_STATE) {
if (1) {
{
fprintf(stdout, "HomeCenter: plug is ready \n");

_instance->HomeCenter_plugIsInitialized_var = 1;
if(_instance->HomeCenter_plugIsInitialized_var && _instance->HomeCenter_doorwindowInitialized_var) {
printf("THINGML: -> ZWaveHomeCenter_send_homeintsendport_devicesinitialized\n");
ZWaveHomeCenter_send_homeintsendport_devicesinitialized(_instance);
}
}
}
}
}
void ZWaveHomeCenter_handle_homeintrecport_devicesinitialized(struct ZWaveHomeCenter_Instance *_instance) {
printf("THINGML: <- ZWaveHomeCenter_handle_homeintrecport_devicesinitialized\n");
if (_instance->HomeCenter_behavior_State == HOMECENTER_BEHAVIOR_INITDEVICE_STATE) {
if (1) {
HomeCenter_behavior_OnExit(HOMECENTER_BEHAVIOR_INITDEVICE_STATE, _instance);
_instance->HomeCenter_behavior_State = HOMECENTER_BEHAVIOR_STARTCONTROLLER_STATE;
HomeCenter_behavior_OnEntry(HOMECENTER_BEHAVIOR_STARTCONTROLLER_STATE, _instance);
}
}
}
void ZWaveHomeCenter_handle_homeintrecport_devicesquiried(struct ZWaveHomeCenter_Instance *_instance) {
printf("THINGML: <- ZWaveHomeCenter_handle_homeintrecport_devicesquiried\n");
if (_instance->HomeCenter_behavior_State == HOMECENTER_BEHAVIOR_WAITFORDEVICES_STATE) {
if (1) {
HomeCenter_behavior_OnExit(HOMECENTER_BEHAVIOR_WAITFORDEVICES_STATE, _instance);
_instance->HomeCenter_behavior_State = HOMECENTER_BEHAVIOR_DEVICESAREREADY_STATE;
HomeCenter_behavior_OnEntry(HOMECENTER_BEHAVIOR_DEVICESAREREADY_STATE, _instance);
}
}
}
void ZWaveHomeCenter_handle_doorwindowport_dw_closed(struct ZWaveHomeCenter_Instance *_instance) {
printf("THINGML: <- ZWaveHomeCenter_handle_doorwindowport_dw_closed\n");
if (_instance->HomeCenter_behavior_State == HOMECENTER_BEHAVIOR_DEVICESAREREADY_STATE) {
if (1) {
{
printf("THINGML: -> ZWaveHomeCenter_send_switchport_turn_on\n");
ZWaveHomeCenter_send_switchport_turn_on(_instance);
printf("THINGML: -> ZWaveHomeCenter_send_switchport_turn_off\n");
ZWaveHomeCenter_send_switchport_turn_off(_instance);
}
}
}
}
void ZWaveHomeCenter_handle_doorwindowport_dw_opened(struct ZWaveHomeCenter_Instance *_instance) {
printf("THINGML: <- ZWaveHomeCenter_handle_doorwindowport_dw_opened\n");
if (_instance->HomeCenter_behavior_State == HOMECENTER_BEHAVIOR_DEVICESAREREADY_STATE) {
if (1) {
{
printf("THINGML: -> ZWaveHomeCenter_send_switchport_turn_on\n");
ZWaveHomeCenter_send_switchport_turn_on(_instance);
printf("THINGML: -> ZWaveHomeCenter_send_switchport_turn_off\n");
ZWaveHomeCenter_send_switchport_turn_off(_instance);
}
}
}
}
void ZWaveHomeCenter_handle_doorwindowport_dw_init(struct ZWaveHomeCenter_Instance *_instance) {
printf("THINGML: <- ZWaveHomeCenter_handle_doorwindowport_dw_init\n");
if (_instance->HomeCenter_behavior_State == HOMECENTER_BEHAVIOR_INITDEVICE_STATE) {
if (1) {
{
fprintf(stdout, "HomeCenter: doorwindow is ready \n");

_instance->HomeCenter_doorwindowInitialized_var = 1;
if(_instance->HomeCenter_plugIsInitialized_var && _instance->HomeCenter_doorwindowInitialized_var) {
printf("THINGML: -> ZWaveHomeCenter_send_homeintsendport_devicesinitialized\n");
ZWaveHomeCenter_send_homeintsendport_devicesinitialized(_instance);
}
}
}
}
}

// Observers for outgoing messages:
void (*ZWaveHomeCenter_send_homeintsendport_devicesinitialized_listener)(struct ZWaveHomeCenter_Instance*)= 0x0;
void register_ZWaveHomeCenter_send_homeintsendport_devicesinitialized_listener(void (*_listener)(struct ZWaveHomeCenter_Instance*)){
ZWaveHomeCenter_send_homeintsendport_devicesinitialized_listener = _listener;
}
void ZWaveHomeCenter_send_homeintsendport_devicesinitialized(struct ZWaveHomeCenter_Instance *_instance){
if (ZWaveHomeCenter_send_homeintsendport_devicesinitialized_listener != 0x0) ZWaveHomeCenter_send_homeintsendport_devicesinitialized_listener(_instance);
}
void (*ZWaveHomeCenter_send_homeintsendport_devicesquiried_listener)(struct ZWaveHomeCenter_Instance*)= 0x0;
void register_ZWaveHomeCenter_send_homeintsendport_devicesquiried_listener(void (*_listener)(struct ZWaveHomeCenter_Instance*)){
ZWaveHomeCenter_send_homeintsendport_devicesquiried_listener = _listener;
}
void ZWaveHomeCenter_send_homeintsendport_devicesquiried(struct ZWaveHomeCenter_Instance *_instance){
if (ZWaveHomeCenter_send_homeintsendport_devicesquiried_listener != 0x0) ZWaveHomeCenter_send_homeintsendport_devicesquiried_listener(_instance);
}
void (*ZWaveHomeCenter_send_switchport_turn_on_listener)(struct ZWaveHomeCenter_Instance*)= 0x0;
void register_ZWaveHomeCenter_send_switchport_turn_on_listener(void (*_listener)(struct ZWaveHomeCenter_Instance*)){
ZWaveHomeCenter_send_switchport_turn_on_listener = _listener;
}
void ZWaveHomeCenter_send_switchport_turn_on(struct ZWaveHomeCenter_Instance *_instance){
if (ZWaveHomeCenter_send_switchport_turn_on_listener != 0x0) ZWaveHomeCenter_send_switchport_turn_on_listener(_instance);
}
void (*ZWaveHomeCenter_send_switchport_turn_off_listener)(struct ZWaveHomeCenter_Instance*)= 0x0;
void register_ZWaveHomeCenter_send_switchport_turn_off_listener(void (*_listener)(struct ZWaveHomeCenter_Instance*)){
ZWaveHomeCenter_send_switchport_turn_off_listener = _listener;
}
void ZWaveHomeCenter_send_switchport_turn_off(struct ZWaveHomeCenter_Instance *_instance){
if (ZWaveHomeCenter_send_switchport_turn_off_listener != 0x0) ZWaveHomeCenter_send_switchport_turn_off_listener(_instance);
}
void (*ZWaveHomeCenter_send_plugport_init_plug_listener)(struct ZWaveHomeCenter_Instance*)= 0x0;
void register_ZWaveHomeCenter_send_plugport_init_plug_listener(void (*_listener)(struct ZWaveHomeCenter_Instance*)){
ZWaveHomeCenter_send_plugport_init_plug_listener = _listener;
}
void ZWaveHomeCenter_send_plugport_init_plug(struct ZWaveHomeCenter_Instance *_instance){
if (ZWaveHomeCenter_send_plugport_init_plug_listener != 0x0) ZWaveHomeCenter_send_plugport_init_plug_listener(_instance);
}
void (*ZWaveHomeCenter_send_ctrlport_initialize_listener)(struct ZWaveHomeCenter_Instance*)= 0x0;
void register_ZWaveHomeCenter_send_ctrlport_initialize_listener(void (*_listener)(struct ZWaveHomeCenter_Instance*)){
ZWaveHomeCenter_send_ctrlport_initialize_listener = _listener;
}
void ZWaveHomeCenter_send_ctrlport_initialize(struct ZWaveHomeCenter_Instance *_instance){
if (ZWaveHomeCenter_send_ctrlport_initialize_listener != 0x0) ZWaveHomeCenter_send_ctrlport_initialize_listener(_instance);
}
void (*ZWaveHomeCenter_send_ctrlport_start_listener)(struct ZWaveHomeCenter_Instance*)= 0x0;
void register_ZWaveHomeCenter_send_ctrlport_start_listener(void (*_listener)(struct ZWaveHomeCenter_Instance*)){
ZWaveHomeCenter_send_ctrlport_start_listener = _listener;
}
void ZWaveHomeCenter_send_ctrlport_start(struct ZWaveHomeCenter_Instance *_instance){
if (ZWaveHomeCenter_send_ctrlport_start_listener != 0x0) ZWaveHomeCenter_send_ctrlport_start_listener(_instance);
}
void (*ZWaveHomeCenter_send_doorwindowport_init_dw_listener)(struct ZWaveHomeCenter_Instance*)= 0x0;
void register_ZWaveHomeCenter_send_doorwindowport_init_dw_listener(void (*_listener)(struct ZWaveHomeCenter_Instance*)){
ZWaveHomeCenter_send_doorwindowport_init_dw_listener = _listener;
}
void ZWaveHomeCenter_send_doorwindowport_init_dw(struct ZWaveHomeCenter_Instance *_instance){
if (ZWaveHomeCenter_send_doorwindowport_init_dw_listener != 0x0) ZWaveHomeCenter_send_doorwindowport_init_dw_listener(_instance);
}
void (*ZWaveHomeCenter_send_doorwindowport_start_monitoring_listener)(struct ZWaveHomeCenter_Instance*)= 0x0;
void register_ZWaveHomeCenter_send_doorwindowport_start_monitoring_listener(void (*_listener)(struct ZWaveHomeCenter_Instance*)){
ZWaveHomeCenter_send_doorwindowport_start_monitoring_listener = _listener;
}
void ZWaveHomeCenter_send_doorwindowport_start_monitoring(struct ZWaveHomeCenter_Instance *_instance){
if (ZWaveHomeCenter_send_doorwindowport_start_monitoring_listener != 0x0) ZWaveHomeCenter_send_doorwindowport_start_monitoring_listener(_instance);
}

