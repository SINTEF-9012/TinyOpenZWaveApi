/*****************************************************
 *      THIS IS A GENERATED FILE. DO NOT EDIT.
 *      Implementation for Application LinuxHomeCenterBSwitchBSensor
 *  Generated from ThingML (http://www.thingml.org)
 *****************************************************/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#include <pthread.h>
#include "thingml_typedefs.h"
#include "runtime.h"
#include "FibaroDoorWindow.h"
#include "ZWaveHomeCenter.h"
#include "FibaroPlug.h"
#include "ZWaveController.h"


// NO C_HEADERS Annotation


/*****************************************************************************
 * Definitions for configuration : LinuxHomeCenterBSwitchBSensor
 *****************************************************************************/

//Declaration of instance variables
struct FibaroDoorWindow_Instance LinuxHomeCenterBSwitchBSensor_dw_var;
struct ZWaveHomeCenter_Instance LinuxHomeCenterBSwitchBSensor_app_var;
struct FibaroPlug_Instance LinuxHomeCenterBSwitchBSensor_p1_var;
struct ZWaveController_Instance LinuxHomeCenterBSwitchBSensor_n_var;

// Enqueue of messages FibaroDoorWindow::doorwindowport::dw_init
void enqueue_FibaroDoorWindow_send_doorwindowport_dw_init(struct FibaroDoorWindow_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (1 >> 8) & 0xFF );
_fifo_enqueue( 1 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
else {
printf("THINGML: FIFO FULL (lost msg dw_init)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages FibaroDoorWindow::doorwindowport::dw_opened
void enqueue_FibaroDoorWindow_send_doorwindowport_dw_opened(struct FibaroDoorWindow_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (2 >> 8) & 0xFF );
_fifo_enqueue( 2 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
else {
printf("THINGML: FIFO FULL (lost msg dw_opened)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages FibaroDoorWindow::doorwindowport::ready_to_monitor
void enqueue_FibaroDoorWindow_send_doorwindowport_ready_to_monitor(struct FibaroDoorWindow_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (3 >> 8) & 0xFF );
_fifo_enqueue( 3 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
else {
printf("THINGML: FIFO FULL (lost msg ready_to_monitor)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages FibaroDoorWindow::doorwindowport::dw_closed
void enqueue_FibaroDoorWindow_send_doorwindowport_dw_closed(struct FibaroDoorWindow_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (4 >> 8) & 0xFF );
_fifo_enqueue( 4 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
else {
printf("THINGML: FIFO FULL (lost msg dw_closed)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages FibaroDoorWindow::dwintsendport::dw_ready
void enqueue_FibaroDoorWindow_send_dwintsendport_dw_ready(struct FibaroDoorWindow_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (5 >> 8) & 0xFF );
_fifo_enqueue( 5 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
else {
printf("THINGML: FIFO FULL (lost msg dw_ready)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages FibaroDoorWindow::dwintsendport::dw_changed
void enqueue_FibaroDoorWindow_send_dwintsendport_dw_changed(struct FibaroDoorWindow_Instance *_instance, int dwstate){
fifo_lock();
if ( fifo_byte_available() > 6 ) {

_fifo_enqueue( (6 >> 8) & 0xFF );
_fifo_enqueue( 6 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );

// parameter dwstate
_fifo_enqueue((dwstate>>8) & 0xFF);
_fifo_enqueue(dwstate & 0xFF);
}
else {
printf("THINGML: FIFO FULL (lost msg dw_changed)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages ZWaveHomeCenter::homeintsendport::devicesinitialized
void enqueue_ZWaveHomeCenter_send_homeintsendport_devicesinitialized(struct ZWaveHomeCenter_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (7 >> 8) & 0xFF );
_fifo_enqueue( 7 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
else {
printf("THINGML: FIFO FULL (lost msg devicesinitialized)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages ZWaveHomeCenter::homeintsendport::devicesquiried
void enqueue_ZWaveHomeCenter_send_homeintsendport_devicesquiried(struct ZWaveHomeCenter_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (8 >> 8) & 0xFF );
_fifo_enqueue( 8 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
else {
printf("THINGML: FIFO FULL (lost msg devicesquiried)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages ZWaveHomeCenter::switchport::turn_on
void enqueue_ZWaveHomeCenter_send_switchport_turn_on(struct ZWaveHomeCenter_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (9 >> 8) & 0xFF );
_fifo_enqueue( 9 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
else {
printf("THINGML: FIFO FULL (lost msg turn_on)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages ZWaveHomeCenter::switchport::turn_off
void enqueue_ZWaveHomeCenter_send_switchport_turn_off(struct ZWaveHomeCenter_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (10 >> 8) & 0xFF );
_fifo_enqueue( 10 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
else {
printf("THINGML: FIFO FULL (lost msg turn_off)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages ZWaveHomeCenter::plugport::init_plug
void enqueue_ZWaveHomeCenter_send_plugport_init_plug(struct ZWaveHomeCenter_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (11 >> 8) & 0xFF );
_fifo_enqueue( 11 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
else {
printf("THINGML: FIFO FULL (lost msg init_plug)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages ZWaveHomeCenter::ctrlport::start
void enqueue_ZWaveHomeCenter_send_ctrlport_start(struct ZWaveHomeCenter_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (12 >> 8) & 0xFF );
_fifo_enqueue( 12 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
else {
printf("THINGML: FIFO FULL (lost msg start)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages ZWaveHomeCenter::ctrlport::initialize
void enqueue_ZWaveHomeCenter_send_ctrlport_initialize(struct ZWaveHomeCenter_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (13 >> 8) & 0xFF );
_fifo_enqueue( 13 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
else {
printf("THINGML: FIFO FULL (lost msg initialize)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages ZWaveHomeCenter::doorwindowport::init_dw
void enqueue_ZWaveHomeCenter_send_doorwindowport_init_dw(struct ZWaveHomeCenter_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (14 >> 8) & 0xFF );
_fifo_enqueue( 14 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
else {
printf("THINGML: FIFO FULL (lost msg init_dw)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages ZWaveHomeCenter::doorwindowport::start_monitoring
void enqueue_ZWaveHomeCenter_send_doorwindowport_start_monitoring(struct ZWaveHomeCenter_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (15 >> 8) & 0xFF );
_fifo_enqueue( 15 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
else {
printf("THINGML: FIFO FULL (lost msg start_monitoring)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages FibaroPlug::plugport::plug_init
void enqueue_FibaroPlug_send_plugport_plug_init(struct FibaroPlug_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (16 >> 8) & 0xFF );
_fifo_enqueue( 16 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
else {
printf("THINGML: FIFO FULL (lost msg plug_init)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages FibaroPlug::plugport::plug_exit
void enqueue_FibaroPlug_send_plugport_plug_exit(struct FibaroPlug_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (17 >> 8) & 0xFF );
_fifo_enqueue( 17 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
else {
printf("THINGML: FIFO FULL (lost msg plug_exit)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages FibaroPlug::swintsendport::turned_on
void enqueue_FibaroPlug_send_swintsendport_turned_on(struct FibaroPlug_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (18 >> 8) & 0xFF );
_fifo_enqueue( 18 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
else {
printf("THINGML: FIFO FULL (lost msg turned_on)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages FibaroPlug::swintsendport::turned_off
void enqueue_FibaroPlug_send_swintsendport_turned_off(struct FibaroPlug_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (19 >> 8) & 0xFF );
_fifo_enqueue( 19 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
else {
printf("THINGML: FIFO FULL (lost msg turned_off)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages FibaroPlug::swintsendport::no_change
void enqueue_FibaroPlug_send_swintsendport_no_change(struct FibaroPlug_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (20 >> 8) & 0xFF );
_fifo_enqueue( 20 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
else {
printf("THINGML: FIFO FULL (lost msg no_change)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages FibaroPlug::swintsendport::switch_state
void enqueue_FibaroPlug_send_swintsendport_switch_state(struct FibaroPlug_Instance *_instance, uint8_t swstate){
fifo_lock();
if ( fifo_byte_available() > 6 ) {

_fifo_enqueue( (21 >> 8) & 0xFF );
_fifo_enqueue( 21 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );

// parameter swstate
_fifo_enqueue((swstate>>8) & 0xFF);
_fifo_enqueue(swstate & 0xFF);
}
else {
printf("THINGML: FIFO FULL (lost msg switch_state)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages FibaroPlug::swintsendport::switch_ready
void enqueue_FibaroPlug_send_swintsendport_switch_ready(struct FibaroPlug_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (22 >> 8) & 0xFF );
_fifo_enqueue( 22 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
else {
printf("THINGML: FIFO FULL (lost msg switch_ready)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages ZWaveController::ctrlport::controller_ready
void enqueue_ZWaveController_send_ctrlport_controller_ready(struct ZWaveController_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (23 >> 8) & 0xFF );
_fifo_enqueue( 23 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
else {
printf("THINGML: FIFO FULL (lost msg controller_ready)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages ZWaveController::ctrlport::started
void enqueue_ZWaveController_send_ctrlport_started(struct ZWaveController_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (24 >> 8) & 0xFF );
_fifo_enqueue( 24 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
else {
printf("THINGML: FIFO FULL (lost msg started)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages ZWaveController::ctrlport::initialized
void enqueue_ZWaveController_send_ctrlport_initialized(struct ZWaveController_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (25 >> 8) & 0xFF );
_fifo_enqueue( 25 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
else {
printf("THINGML: FIFO FULL (lost msg initialized)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages ZWaveController::ctrlport::all_nodes_quiried
void enqueue_ZWaveController_send_ctrlport_all_nodes_quiried(struct ZWaveController_Instance *_instance){
fifo_lock();
if ( fifo_byte_available() > 4 ) {

_fifo_enqueue( (26 >> 8) & 0xFF );
_fifo_enqueue( 26 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );
}
else {
printf("THINGML: FIFO FULL (lost msg all_nodes_quiried)\n");
}
fifo_unlock_and_notify();
}
// Enqueue of messages ZWaveController::ctrlport::node_quiried
void enqueue_ZWaveController_send_ctrlport_node_quiried(struct ZWaveController_Instance *_instance, int nodeid){
fifo_lock();
if ( fifo_byte_available() > 6 ) {

_fifo_enqueue( (27 >> 8) & 0xFF );
_fifo_enqueue( 27 & 0xFF );

// ID of the source instance
_fifo_enqueue( (_instance->id >> 8) & 0xFF );
_fifo_enqueue( _instance->id & 0xFF );

// parameter nodeid
_fifo_enqueue((nodeid>>8) & 0xFF);
_fifo_enqueue(nodeid & 0xFF);
}
else {
printf("THINGML: FIFO FULL (lost msg node_quiried)\n");
}
fifo_unlock_and_notify();
}

// Dispatch for messages FibaroDoorWindow::doorwindowport::dw_init
void dispatch_FibaroDoorWindow_send_doorwindowport_dw_init(struct FibaroDoorWindow_Instance *_instance){
if (_instance == &LinuxHomeCenterBSwitchBSensor_dw_var) {
ZWaveHomeCenter_handle_doorwindowport_dw_init(&LinuxHomeCenterBSwitchBSensor_app_var);
}
}
// Dispatch for messages FibaroDoorWindow::doorwindowport::dw_opened
void dispatch_FibaroDoorWindow_send_doorwindowport_dw_opened(struct FibaroDoorWindow_Instance *_instance){
if (_instance == &LinuxHomeCenterBSwitchBSensor_dw_var) {
ZWaveHomeCenter_handle_doorwindowport_dw_opened(&LinuxHomeCenterBSwitchBSensor_app_var);
}
}
// Dispatch for messages FibaroDoorWindow::doorwindowport::ready_to_monitor
void dispatch_FibaroDoorWindow_send_doorwindowport_ready_to_monitor(struct FibaroDoorWindow_Instance *_instance){
if (_instance == &LinuxHomeCenterBSwitchBSensor_dw_var) {
}
}
// Dispatch for messages FibaroDoorWindow::doorwindowport::dw_closed
void dispatch_FibaroDoorWindow_send_doorwindowport_dw_closed(struct FibaroDoorWindow_Instance *_instance){
if (_instance == &LinuxHomeCenterBSwitchBSensor_dw_var) {
ZWaveHomeCenter_handle_doorwindowport_dw_closed(&LinuxHomeCenterBSwitchBSensor_app_var);
}
}
// Dispatch for messages FibaroDoorWindow::dwintsendport::dw_ready
void dispatch_FibaroDoorWindow_send_dwintsendport_dw_ready(struct FibaroDoorWindow_Instance *_instance){
if (_instance == &LinuxHomeCenterBSwitchBSensor_dw_var) {
FibaroDoorWindow_handle_dwintrecport_dw_ready(&LinuxHomeCenterBSwitchBSensor_dw_var);
}
}
// Dispatch for messages FibaroDoorWindow::dwintsendport::dw_changed
void dispatch_FibaroDoorWindow_send_dwintsendport_dw_changed(struct FibaroDoorWindow_Instance *_instance, int dwstate){
if (_instance == &LinuxHomeCenterBSwitchBSensor_dw_var) {
FibaroDoorWindow_handle_dwintrecport_dw_changed(&LinuxHomeCenterBSwitchBSensor_dw_var, dwstate);
}
}
// Dispatch for messages ZWaveHomeCenter::homeintsendport::devicesinitialized
void dispatch_ZWaveHomeCenter_send_homeintsendport_devicesinitialized(struct ZWaveHomeCenter_Instance *_instance){
if (_instance == &LinuxHomeCenterBSwitchBSensor_app_var) {
ZWaveHomeCenter_handle_homeintrecport_devicesinitialized(&LinuxHomeCenterBSwitchBSensor_app_var);
}
}
// Dispatch for messages ZWaveHomeCenter::homeintsendport::devicesquiried
void dispatch_ZWaveHomeCenter_send_homeintsendport_devicesquiried(struct ZWaveHomeCenter_Instance *_instance){
if (_instance == &LinuxHomeCenterBSwitchBSensor_app_var) {
ZWaveHomeCenter_handle_homeintrecport_devicesquiried(&LinuxHomeCenterBSwitchBSensor_app_var);
}
}
// Dispatch for messages ZWaveHomeCenter::switchport::turn_on
void dispatch_ZWaveHomeCenter_send_switchport_turn_on(struct ZWaveHomeCenter_Instance *_instance){
if (_instance == &LinuxHomeCenterBSwitchBSensor_app_var) {
FibaroPlug_handle_switchport_turn_on(&LinuxHomeCenterBSwitchBSensor_p1_var);
}
}
// Dispatch for messages ZWaveHomeCenter::switchport::turn_off
void dispatch_ZWaveHomeCenter_send_switchport_turn_off(struct ZWaveHomeCenter_Instance *_instance){
if (_instance == &LinuxHomeCenterBSwitchBSensor_app_var) {
FibaroPlug_handle_switchport_turn_off(&LinuxHomeCenterBSwitchBSensor_p1_var);
}
}
// Dispatch for messages ZWaveHomeCenter::plugport::init_plug
void dispatch_ZWaveHomeCenter_send_plugport_init_plug(struct ZWaveHomeCenter_Instance *_instance){
if (_instance == &LinuxHomeCenterBSwitchBSensor_app_var) {
FibaroPlug_handle_plugport_init_plug(&LinuxHomeCenterBSwitchBSensor_p1_var);
}
}
// Dispatch for messages ZWaveHomeCenter::ctrlport::start
void dispatch_ZWaveHomeCenter_send_ctrlport_start(struct ZWaveHomeCenter_Instance *_instance){
if (_instance == &LinuxHomeCenterBSwitchBSensor_app_var) {
ZWaveController_handle_ctrlport_start(&LinuxHomeCenterBSwitchBSensor_n_var);
}
}
// Dispatch for messages ZWaveHomeCenter::ctrlport::initialize
void dispatch_ZWaveHomeCenter_send_ctrlport_initialize(struct ZWaveHomeCenter_Instance *_instance){
if (_instance == &LinuxHomeCenterBSwitchBSensor_app_var) {
ZWaveController_handle_ctrlport_initialize(&LinuxHomeCenterBSwitchBSensor_n_var);
}
}
// Dispatch for messages ZWaveHomeCenter::doorwindowport::init_dw
void dispatch_ZWaveHomeCenter_send_doorwindowport_init_dw(struct ZWaveHomeCenter_Instance *_instance){
if (_instance == &LinuxHomeCenterBSwitchBSensor_app_var) {
FibaroDoorWindow_handle_doorwindowport_init_dw(&LinuxHomeCenterBSwitchBSensor_dw_var);
}
}
// Dispatch for messages ZWaveHomeCenter::doorwindowport::start_monitoring
void dispatch_ZWaveHomeCenter_send_doorwindowport_start_monitoring(struct ZWaveHomeCenter_Instance *_instance){
if (_instance == &LinuxHomeCenterBSwitchBSensor_app_var) {
FibaroDoorWindow_handle_doorwindowport_start_monitoring(&LinuxHomeCenterBSwitchBSensor_dw_var);
}
}
// Dispatch for messages FibaroPlug::plugport::plug_init
void dispatch_FibaroPlug_send_plugport_plug_init(struct FibaroPlug_Instance *_instance){
if (_instance == &LinuxHomeCenterBSwitchBSensor_p1_var) {
ZWaveHomeCenter_handle_plugport_plug_init(&LinuxHomeCenterBSwitchBSensor_app_var);
}
}
// Dispatch for messages FibaroPlug::plugport::plug_exit
void dispatch_FibaroPlug_send_plugport_plug_exit(struct FibaroPlug_Instance *_instance){
if (_instance == &LinuxHomeCenterBSwitchBSensor_p1_var) {
ZWaveHomeCenter_handle_plugport_plug_exit(&LinuxHomeCenterBSwitchBSensor_app_var);
}
}
// Dispatch for messages FibaroPlug::swintsendport::turned_on
void dispatch_FibaroPlug_send_swintsendport_turned_on(struct FibaroPlug_Instance *_instance){
if (_instance == &LinuxHomeCenterBSwitchBSensor_p1_var) {
FibaroPlug_handle_swintrecport_turned_on(&LinuxHomeCenterBSwitchBSensor_p1_var);
}
}
// Dispatch for messages FibaroPlug::swintsendport::turned_off
void dispatch_FibaroPlug_send_swintsendport_turned_off(struct FibaroPlug_Instance *_instance){
if (_instance == &LinuxHomeCenterBSwitchBSensor_p1_var) {
FibaroPlug_handle_swintrecport_turned_off(&LinuxHomeCenterBSwitchBSensor_p1_var);
}
}
// Dispatch for messages FibaroPlug::swintsendport::no_change
void dispatch_FibaroPlug_send_swintsendport_no_change(struct FibaroPlug_Instance *_instance){
if (_instance == &LinuxHomeCenterBSwitchBSensor_p1_var) {
FibaroPlug_handle_swintrecport_no_change(&LinuxHomeCenterBSwitchBSensor_p1_var);
}
}
// Dispatch for messages FibaroPlug::swintsendport::switch_state
void dispatch_FibaroPlug_send_swintsendport_switch_state(struct FibaroPlug_Instance *_instance, uint8_t swstate){
if (_instance == &LinuxHomeCenterBSwitchBSensor_p1_var) {
FibaroPlug_handle_swintrecport_switch_state(&LinuxHomeCenterBSwitchBSensor_p1_var, swstate);
}
}
// Dispatch for messages FibaroPlug::swintsendport::switch_ready
void dispatch_FibaroPlug_send_swintsendport_switch_ready(struct FibaroPlug_Instance *_instance){
if (_instance == &LinuxHomeCenterBSwitchBSensor_p1_var) {
FibaroPlug_handle_swintrecport_switch_ready(&LinuxHomeCenterBSwitchBSensor_p1_var);
}
}
// Dispatch for messages ZWaveController::ctrlport::controller_ready
void dispatch_ZWaveController_send_ctrlport_controller_ready(struct ZWaveController_Instance *_instance){
if (_instance == &LinuxHomeCenterBSwitchBSensor_n_var) {
ZWaveHomeCenter_handle_ctrlport_controller_ready(&LinuxHomeCenterBSwitchBSensor_app_var);
}
}
// Dispatch for messages ZWaveController::ctrlport::started
void dispatch_ZWaveController_send_ctrlport_started(struct ZWaveController_Instance *_instance){
if (_instance == &LinuxHomeCenterBSwitchBSensor_n_var) {
}
}
// Dispatch for messages ZWaveController::ctrlport::initialized
void dispatch_ZWaveController_send_ctrlport_initialized(struct ZWaveController_Instance *_instance){
if (_instance == &LinuxHomeCenterBSwitchBSensor_n_var) {
ZWaveHomeCenter_handle_ctrlport_initialized(&LinuxHomeCenterBSwitchBSensor_app_var);
}
}
// Dispatch for messages ZWaveController::ctrlport::all_nodes_quiried
void dispatch_ZWaveController_send_ctrlport_all_nodes_quiried(struct ZWaveController_Instance *_instance){
if (_instance == &LinuxHomeCenterBSwitchBSensor_n_var) {
}
}
// Dispatch for messages ZWaveController::ctrlport::node_quiried
void dispatch_ZWaveController_send_ctrlport_node_quiried(struct ZWaveController_Instance *_instance, int nodeid){
if (_instance == &LinuxHomeCenterBSwitchBSensor_n_var) {
ZWaveHomeCenter_handle_ctrlport_node_quiried(&LinuxHomeCenterBSwitchBSensor_app_var, nodeid);
}
}

void processMessageQueue() {
fifo_lock();
while (fifo_empty()) fifo_wait();
byte mbuf[4];
uint8_t mbufi = 0;

// Read the code of the next port/message in the queue
uint16_t code = fifo_dequeue() << 8;

code += fifo_dequeue();

// Switch to call the appropriate handler
switch(code) {
case 1:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_FibaroDoorWindow_send_doorwindowport_dw_init((struct FibaroDoorWindow_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 2:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_FibaroDoorWindow_send_doorwindowport_dw_opened((struct FibaroDoorWindow_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 3:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_FibaroDoorWindow_send_doorwindowport_ready_to_monitor((struct FibaroDoorWindow_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 4:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_FibaroDoorWindow_send_doorwindowport_dw_closed((struct FibaroDoorWindow_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 5:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_FibaroDoorWindow_send_dwintsendport_dw_ready((struct FibaroDoorWindow_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 6:
while (mbufi < 4) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_FibaroDoorWindow_send_dwintsendport_dw_changed((struct FibaroDoorWindow_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */,
(mbuf[2]<<8) + mbuf[3] /* dwstate */ );
break;
case 7:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_ZWaveHomeCenter_send_homeintsendport_devicesinitialized((struct ZWaveHomeCenter_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 8:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_ZWaveHomeCenter_send_homeintsendport_devicesquiried((struct ZWaveHomeCenter_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 9:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_ZWaveHomeCenter_send_switchport_turn_on((struct ZWaveHomeCenter_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 10:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_ZWaveHomeCenter_send_switchport_turn_off((struct ZWaveHomeCenter_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 11:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_ZWaveHomeCenter_send_plugport_init_plug((struct ZWaveHomeCenter_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 12:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_ZWaveHomeCenter_send_ctrlport_start((struct ZWaveHomeCenter_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 13:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_ZWaveHomeCenter_send_ctrlport_initialize((struct ZWaveHomeCenter_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 14:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_ZWaveHomeCenter_send_doorwindowport_init_dw((struct ZWaveHomeCenter_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 15:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_ZWaveHomeCenter_send_doorwindowport_start_monitoring((struct ZWaveHomeCenter_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 16:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_FibaroPlug_send_plugport_plug_init((struct FibaroPlug_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 17:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_FibaroPlug_send_plugport_plug_exit((struct FibaroPlug_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 18:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_FibaroPlug_send_swintsendport_turned_on((struct FibaroPlug_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 19:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_FibaroPlug_send_swintsendport_turned_off((struct FibaroPlug_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 20:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_FibaroPlug_send_swintsendport_no_change((struct FibaroPlug_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 21:
while (mbufi < 4) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_FibaroPlug_send_swintsendport_switch_state((struct FibaroPlug_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */,
(mbuf[2]<<8) + mbuf[3] /* swstate */ );
break;
case 22:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_FibaroPlug_send_swintsendport_switch_ready((struct FibaroPlug_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 23:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_ZWaveController_send_ctrlport_controller_ready((struct ZWaveController_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 24:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_ZWaveController_send_ctrlport_started((struct ZWaveController_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 25:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_ZWaveController_send_ctrlport_initialized((struct ZWaveController_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 26:
while (mbufi < 2) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_ZWaveController_send_ctrlport_all_nodes_quiried((struct ZWaveController_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */);
break;
case 27:
while (mbufi < 4) mbuf[mbufi++] = fifo_dequeue();
fifo_unlock();
dispatch_ZWaveController_send_ctrlport_node_quiried((struct ZWaveController_Instance*)instance_by_id((mbuf[0] << 8) + mbuf[1]) /* instance */,
(mbuf[2]<<8) + mbuf[3] /* nodeid */ );
break;
}
}

void initialize_configuration_LinuxHomeCenterBSwitchBSensor() {
// Initialize connectors
register_FibaroDoorWindow_send_doorwindowport_dw_closed_listener(enqueue_FibaroDoorWindow_send_doorwindowport_dw_closed);
register_FibaroDoorWindow_send_doorwindowport_dw_opened_listener(enqueue_FibaroDoorWindow_send_doorwindowport_dw_opened);
register_FibaroDoorWindow_send_doorwindowport_dw_init_listener(enqueue_FibaroDoorWindow_send_doorwindowport_dw_init);
register_FibaroDoorWindow_send_doorwindowport_ready_to_monitor_listener(enqueue_FibaroDoorWindow_send_doorwindowport_ready_to_monitor);
register_FibaroDoorWindow_send_dwintsendport_dw_changed_listener(enqueue_FibaroDoorWindow_send_dwintsendport_dw_changed);
register_FibaroDoorWindow_send_dwintsendport_dw_ready_listener(enqueue_FibaroDoorWindow_send_dwintsendport_dw_ready);
register_ZWaveHomeCenter_send_homeintsendport_devicesinitialized_listener(enqueue_ZWaveHomeCenter_send_homeintsendport_devicesinitialized);
register_ZWaveHomeCenter_send_homeintsendport_devicesquiried_listener(enqueue_ZWaveHomeCenter_send_homeintsendport_devicesquiried);
register_ZWaveHomeCenter_send_switchport_turn_on_listener(enqueue_ZWaveHomeCenter_send_switchport_turn_on);
register_ZWaveHomeCenter_send_switchport_turn_off_listener(enqueue_ZWaveHomeCenter_send_switchport_turn_off);
register_ZWaveHomeCenter_send_plugport_init_plug_listener(enqueue_ZWaveHomeCenter_send_plugport_init_plug);
register_ZWaveHomeCenter_send_ctrlport_initialize_listener(enqueue_ZWaveHomeCenter_send_ctrlport_initialize);
register_ZWaveHomeCenter_send_ctrlport_start_listener(enqueue_ZWaveHomeCenter_send_ctrlport_start);
register_ZWaveHomeCenter_send_doorwindowport_init_dw_listener(enqueue_ZWaveHomeCenter_send_doorwindowport_init_dw);
register_ZWaveHomeCenter_send_doorwindowport_start_monitoring_listener(enqueue_ZWaveHomeCenter_send_doorwindowport_start_monitoring);
register_FibaroPlug_send_plugport_plug_init_listener(enqueue_FibaroPlug_send_plugport_plug_init);
register_FibaroPlug_send_plugport_plug_exit_listener(enqueue_FibaroPlug_send_plugport_plug_exit);
register_FibaroPlug_send_swintsendport_switch_state_listener(enqueue_FibaroPlug_send_swintsendport_switch_state);
register_FibaroPlug_send_swintsendport_switch_ready_listener(enqueue_FibaroPlug_send_swintsendport_switch_ready);
register_FibaroPlug_send_swintsendport_turned_off_listener(enqueue_FibaroPlug_send_swintsendport_turned_off);
register_FibaroPlug_send_swintsendport_no_change_listener(enqueue_FibaroPlug_send_swintsendport_no_change);
register_FibaroPlug_send_swintsendport_turned_on_listener(enqueue_FibaroPlug_send_swintsendport_turned_on);
register_ZWaveController_send_ctrlport_initialized_listener(enqueue_ZWaveController_send_ctrlport_initialized);
register_ZWaveController_send_ctrlport_controller_ready_listener(enqueue_ZWaveController_send_ctrlport_controller_ready);
register_ZWaveController_send_ctrlport_started_listener(enqueue_ZWaveController_send_ctrlport_started);
register_ZWaveController_send_ctrlport_node_quiried_listener(enqueue_ZWaveController_send_ctrlport_node_quiried);
register_ZWaveController_send_ctrlport_all_nodes_quiried_listener(enqueue_ZWaveController_send_ctrlport_all_nodes_quiried);

// Init the ID, state variables and properties for instance LinuxHomeCenterBSwitchBSensor_dw
LinuxHomeCenterBSwitchBSensor_dw_var.id = add_instance( (void*) &LinuxHomeCenterBSwitchBSensor_dw_var);
LinuxHomeCenterBSwitchBSensor_dw_var.DoorWindow_behavior_State = DOORWINDOW_BEHAVIOR_START_STATE;
LinuxHomeCenterBSwitchBSensor_dw_var.DoorWindow_nodeId_var = 3;
LinuxHomeCenterBSwitchBSensor_dw_var.DoorWindow_cInstance_var = 1;
LinuxHomeCenterBSwitchBSensor_dw_var.DoorWindow_cIndex_var = 0;
LinuxHomeCenterBSwitchBSensor_dw_var.Config_pport_var = "/dev/ttyUSB0";
LinuxHomeCenterBSwitchBSensor_dw_var.Config_config_var = "/usr/local/share/openzwave/config/";
LinuxHomeCenterBSwitchBSensor_dw_var.Config_zwdir_var = "";
LinuxHomeCenterBSwitchBSensor_dw_var.Config_domo_log_var = "./DomoZWave_Log";
LinuxHomeCenterBSwitchBSensor_dw_var.Config_enableLog_var = 1;
LinuxHomeCenterBSwitchBSensor_dw_var.Config_enableZWLog_var = 0;
LinuxHomeCenterBSwitchBSensor_dw_var.Config_polltime_var = 0;

// Init the ID, state variables and properties for instance LinuxHomeCenterBSwitchBSensor_app
LinuxHomeCenterBSwitchBSensor_app_var.id = add_instance( (void*) &LinuxHomeCenterBSwitchBSensor_app_var);
LinuxHomeCenterBSwitchBSensor_app_var.HomeCenter_behavior_State = HOMECENTER_BEHAVIOR_START_STATE;
LinuxHomeCenterBSwitchBSensor_app_var.HomeCenter_plugid_var = 2;
LinuxHomeCenterBSwitchBSensor_app_var.HomeCenter_doorwindowid_var = 3;
LinuxHomeCenterBSwitchBSensor_app_var.HomeCenter_plugIsInitialized_var = 0;
LinuxHomeCenterBSwitchBSensor_app_var.HomeCenter_doorwindowInitialized_var = 0;
LinuxHomeCenterBSwitchBSensor_app_var.HomeCenter_plugIsQuiried_var = 0;
LinuxHomeCenterBSwitchBSensor_app_var.HomeCenter_doorwindowIsQuiried_var = 0;
LinuxHomeCenterBSwitchBSensor_app_var.Config_pport_var = "/dev/ttyUSB0";
LinuxHomeCenterBSwitchBSensor_app_var.Config_config_var = "/usr/local/share/openzwave/config/";
LinuxHomeCenterBSwitchBSensor_app_var.Config_zwdir_var = "";
LinuxHomeCenterBSwitchBSensor_app_var.Config_domo_log_var = "./DomoZWave_Log";
LinuxHomeCenterBSwitchBSensor_app_var.Config_enableLog_var = 1;
LinuxHomeCenterBSwitchBSensor_app_var.Config_enableZWLog_var = 0;
LinuxHomeCenterBSwitchBSensor_app_var.Config_polltime_var = 0;

// Init the ID, state variables and properties for instance LinuxHomeCenterBSwitchBSensor_p1
LinuxHomeCenterBSwitchBSensor_p1_var.id = add_instance( (void*) &LinuxHomeCenterBSwitchBSensor_p1_var);
LinuxHomeCenterBSwitchBSensor_p1_var.Plug_behavior_State = PLUG_BEHAVIOR_START_STATE;
LinuxHomeCenterBSwitchBSensor_p1_var.Plug_nodeId_var = 2;
LinuxHomeCenterBSwitchBSensor_p1_var.Plug_cInstance_var = 1;
LinuxHomeCenterBSwitchBSensor_p1_var.Plug_cIndex_var = 0;
LinuxHomeCenterBSwitchBSensor_p1_var.Plug_attempts_var = 0;
LinuxHomeCenterBSwitchBSensor_p1_var.Plug_exit_after_tries_var = 0;
LinuxHomeCenterBSwitchBSensor_p1_var.Plug_MAX_ATTEMPTS_var = 3;
LinuxHomeCenterBSwitchBSensor_p1_var.Plug_MAX_EXIT_AFTER_var = 20;
LinuxHomeCenterBSwitchBSensor_p1_var.Config_pport_var = "/dev/ttyUSB0";
LinuxHomeCenterBSwitchBSensor_p1_var.Config_config_var = "/usr/local/share/openzwave/config/";
LinuxHomeCenterBSwitchBSensor_p1_var.Config_zwdir_var = "";
LinuxHomeCenterBSwitchBSensor_p1_var.Config_domo_log_var = "./DomoZWave_Log";
LinuxHomeCenterBSwitchBSensor_p1_var.Config_enableLog_var = 1;
LinuxHomeCenterBSwitchBSensor_p1_var.Config_enableZWLog_var = 0;
LinuxHomeCenterBSwitchBSensor_p1_var.Config_polltime_var = 0;

// Init the ID, state variables and properties for instance LinuxHomeCenterBSwitchBSensor_n
LinuxHomeCenterBSwitchBSensor_n_var.id = add_instance( (void*) &LinuxHomeCenterBSwitchBSensor_n_var);
LinuxHomeCenterBSwitchBSensor_n_var.Controller_behavior_State = CONTROLLER_BEHAVIOR_START_STATE;
LinuxHomeCenterBSwitchBSensor_n_var.Config_pport_var = "/dev/ttyUSB0";
LinuxHomeCenterBSwitchBSensor_n_var.Config_config_var = "/usr/local/share/openzwave/config/";
LinuxHomeCenterBSwitchBSensor_n_var.Config_zwdir_var = "";
LinuxHomeCenterBSwitchBSensor_n_var.Config_domo_log_var = "./DomoZWave_Log";
LinuxHomeCenterBSwitchBSensor_n_var.Config_enableLog_var = 1;
LinuxHomeCenterBSwitchBSensor_n_var.Config_enableZWLog_var = 0;
LinuxHomeCenterBSwitchBSensor_n_var.Config_polltime_var = 0;

DoorWindow_behavior_OnEntry(DOORWINDOW_BEHAVIOR_STATE, &LinuxHomeCenterBSwitchBSensor_dw_var);
HomeCenter_behavior_OnEntry(HOMECENTER_BEHAVIOR_STATE, &LinuxHomeCenterBSwitchBSensor_app_var);
Plug_behavior_OnEntry(PLUG_BEHAVIOR_STATE, &LinuxHomeCenterBSwitchBSensor_p1_var);
Controller_behavior_OnEntry(CONTROLLER_BEHAVIOR_STATE, &LinuxHomeCenterBSwitchBSensor_n_var);
}


// NO C_GLOBALS Annotation

int main(int argc, char *argv[]) {
  init_runtime();
  // NO C_MAIN Annotation
  printf("THINGML: Starting in debug mode...\n");
initialize_configuration_LinuxHomeCenterBSwitchBSensor();

  while (1) {
    
    processMessageQueue();
  }
  return 0;
}