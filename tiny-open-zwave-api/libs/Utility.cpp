/*
 * types.cpp
 *
 *  Created on: Nov 1, 2013
 *      Author: vassik
 */

#include <string.h>

#include "openzwave/Log.h"
#include "openzwave/Driver.h"
#include "openzwave/Notification.h"
#include "openzwave/ValueStore.h"
#include "openzwave/Value.h"
#include "openzwave/ValueBool.h"
#include "openzwave/ValueByte.h"
#include "openzwave/ValueDecimal.h"
#include "openzwave/ValueInt.h"
#include "openzwave/ValueList.h"
#include "openzwave/ValueShort.h"
#include "openzwave/ValueString.h"

#include "Utility.h"
#include "DomoZWave.h"


namespace TinyOpenZWaveApi {


const char *genreToStr (ValueID::ValueGenre vg)
{
  switch (vg) {
  case ValueID::ValueGenre_Basic:
    return "basic";
  case ValueID::ValueGenre_User:
    return "user";
  case ValueID::ValueGenre_Config:
    return "config";
  case ValueID::ValueGenre_System:
    return "system";
  case ValueID::ValueGenre_Count:
    return "count";
  }
  return "unknown";
}

ValueID::ValueGenre genreToNum (char const *str)
{
  if (strcmp(str, "basic") == 0)
    return ValueID::ValueGenre_Basic;
  else if (strcmp(str, "user") == 0)
    return ValueID::ValueGenre_User;
  else if (strcmp(str, "config") == 0)
    return ValueID::ValueGenre_Config;
  else if (strcmp(str, "system") == 0)
    return ValueID::ValueGenre_System;
  else if (strcmp(str, "count") == 0)
    return ValueID::ValueGenre_Count;
  else
    return (ValueID::ValueGenre)255;
}

const char *typeToStr (ValueID::ValueType vt)
{
  switch (vt) {
  case ValueID::ValueType_Bool:
    return "bool";
  case ValueID::ValueType_Byte:
    return "byte";
  case ValueID::ValueType_Decimal:
    return "decimal";
  case ValueID::ValueType_Int:
    return "int";
  case ValueID::ValueType_List:
    return "list";
  case ValueID::ValueType_Schedule:
    return "schedule";
  case ValueID::ValueType_String:
    return "string";
  case ValueID::ValueType_Short:
    return "short";
  case ValueID::ValueType_Button:
    return "button";
  case ValueID::ValueType_Raw:
    return "raw";
  }
  return "unknown";
}

ValueID::ValueType typeToNum (char const *str)
{
  if (strcmp(str, "bool") == 0)
    return ValueID::ValueType_Bool;
  else if (strcmp(str, "byte") == 0)
    return ValueID::ValueType_Byte;
  else if (strcmp(str, "decimal") == 0)
    return ValueID::ValueType_Decimal;
  else if (strcmp(str, "int") == 0)
    return ValueID::ValueType_Int;
  else if (strcmp(str, "list") == 0)
    return ValueID::ValueType_List;
  else if (strcmp(str, "schedule") == 0)
    return ValueID::ValueType_Schedule;
  else if (strcmp(str, "short") == 0)
    return ValueID::ValueType_Short;
  else if (strcmp(str, "string") == 0)
    return ValueID::ValueType_String;
  else if (strcmp(str, "button") == 0)
    return ValueID::ValueType_Button;
  else if (strcmp(str, "raw") == 0)
    return ValueID::ValueType_Raw;
  else
    return (ValueID::ValueType)255;
}

const char *nodeBasicToStr (uint8 basic)
{
  switch (basic) {
  case 1:
    return "Controller";
  case 2:
    return "Static Controller";
  case 3:
    return "Slave";
  case 4:
    return "Routing Slave";
  }
  return "unknown";
}

const char *cclassToStr (uint8 cc)
{
  switch (cc) {
  default:
  case COMMAND_CLASS_NO_OPERATION:
    return "COMMAND_CLASS_NO_OPERATION";
  case COMMAND_CLASS_BASIC:
    return "COMMAND_CLASS_BASIC";
  case COMMAND_CLASS_CONTROLLER_REPLICATION:
    return "COMMAND_CLASS_CONTROLLER_REPLICATION";
  case COMMAND_CLASS_APPLICATION_STATUS:
    return "COMMAND_CLASS_APPLICATION_STATUS";
  case COMMAND_CLASS_ZIP_SERVICES:
    return "COMMAND_CLASS_ZIP_SERVICES";
  case COMMAND_CLASS_ZIP_SERVER:
    return "COMMAND_CLASS_ZIP_SERVER";
  case COMMAND_CLASS_SWITCH_BINARY:
    return "COMMAND_CLASS_SWITCH_BINARY";
  case COMMAND_CLASS_SWITCH_MULTILEVEL:
    return "SWITCH MULTILEVEL";
  case COMMAND_CLASS_SWITCH_ALL:
    return "SWITCH ALL";
  case COMMAND_CLASS_SWITCH_TOGGLE_BINARY:
    return "SWITCH TOGGLE BINARY";
  case COMMAND_CLASS_SWITCH_TOGGLE_MULTILEVEL:
    return "SWITCH TOGGLE MULTILEVEL";
  case COMMAND_CLASS_CHIMNEY_FAN:
    return "CHIMNEY FAN";
  case COMMAND_CLASS_SCENE_ACTIVATION:
    return "SCENE ACTIVATION";
  case COMMAND_CLASS_SCENE_ACTUATOR_CONF:
    return "SCENE ACTUATOR CONF";
  case COMMAND_CLASS_SCENE_CONTROLLER_CONF:
    return "SCENE CONTROLLER CONF";
  case COMMAND_CLASS_ZIP_CLIENT:
    return "ZIP CLIENT";
  case COMMAND_CLASS_ZIP_ADV_SERVICES:
    return "ZIP ADV SERVICES";
  case COMMAND_CLASS_SENSOR_BINARY:
    return "SENSOR BINARY";
  case COMMAND_CLASS_SENSOR_MULTILEVEL:
    return "SENSOR MULTILEVEL";
  case COMMAND_CLASS_METER:
    return "METER";
  case COMMAND_CLASS_ZIP_ADV_SERVER:
    return "ZIP ADV SERVER";
  case COMMAND_CLASS_ZIP_ADV_CLIENT:
    return "ZIP ADV CLIENT";
  case COMMAND_CLASS_METER_PULSE:
    return "METER PULSE";
  case COMMAND_CLASS_THERMOSTAT_HEATING:
    return "THERMOSTAT HEATING";
  case COMMAND_CLASS_THERMOSTAT_MODE:
    return "THERMOSTAT MODE";
  case COMMAND_CLASS_THERMOSTAT_OPERATING_STATE:
    return "THERMOSTAT OPERATING STATE";
  case COMMAND_CLASS_THERMOSTAT_SETPOINT:
    return "THERMOSTAT SETPOINT";
  case COMMAND_CLASS_THERMOSTAT_FAN_MODE:
    return "THERMOSTAT FAN MODE";
  case COMMAND_CLASS_THERMOSTAT_FAN_STATE:
    return "THERMOSTAT FAN STATE";
  case COMMAND_CLASS_CLIMATE_CONTROL_SCHEDULE:
    return "CLIMATE CONTROL SCHEDULE";
  case COMMAND_CLASS_THERMOSTAT_SETBACK:
    return "THERMOSTAT SETBACK";
  case COMMAND_CLASS_DOOR_LOCK_LOGGING:
    return "DOOR LOCK LOGGING";
  case COMMAND_CLASS_SCHEDULE_ENTRY_LOCK:
    return "SCHEDULE ENTRY LOCK";
  case COMMAND_CLASS_BASIC_WINDOW_COVERING:
    return "BASIC WINDOW COVERING";
  case COMMAND_CLASS_MTP_WINDOW_COVERING:
    return "MTP WINDOW COVERING";
  case COMMAND_CLASS_MULTI_INSTANCE:
    return "MULTI INSTANCE";
  case COMMAND_CLASS_DOOR_LOCK:
    return "DOOR LOCK";
  case COMMAND_CLASS_USER_CODE:
    return "USER CODE";
  case COMMAND_CLASS_CONFIGURATION:
    return "CONFIGURATION";
  case COMMAND_CLASS_ALARM:
    return "ALARM";
  case COMMAND_CLASS_MANUFACTURER_SPECIFIC:
    return "MANUFACTURER SPECIFIC";
  case COMMAND_CLASS_POWERLEVEL:
    return "POWERLEVEL";
  case COMMAND_CLASS_PROTECTION:
    return "PROTECTION";
  case COMMAND_CLASS_LOCK:
    return "LOCK";
  case COMMAND_CLASS_NODE_NAMING:
    return "NODE NAMING";
  case COMMAND_CLASS_FIRMWARE_UPDATE_MD:
    return "FIRMWARE UPDATE MD";
  case COMMAND_CLASS_GROUPING_NAME:
    return "GROUPING NAME";
  case COMMAND_CLASS_REMOTE_ASSOCIATION_ACTIVATE:
    return "REMOTE ASSOCIATION ACTIVATE";
  case COMMAND_CLASS_REMOTE_ASSOCIATION:
    return "REMOTE ASSOCIATION";
  case COMMAND_CLASS_BATTERY:
    return "BATTERY";
  case COMMAND_CLASS_CLOCK:
    return "CLOCK";
  case COMMAND_CLASS_HAIL:
    return "HAIL";
  case COMMAND_CLASS_WAKE_UP:
    return "WAKE UP";
  case COMMAND_CLASS_ASSOCIATION:
    return "ASSOCIATION";
  case COMMAND_CLASS_VERSION:
    return "VERSION";
  case COMMAND_CLASS_INDICATOR:
    return "INDICATOR";
  case COMMAND_CLASS_PROPRIETARY:
    return "PROPRIETARY";
  case COMMAND_CLASS_LANGUAGE:
    return "LANGUAGE";
  case COMMAND_CLASS_TIME:
    return "TIME";
  case COMMAND_CLASS_TIME_PARAMETERS:
    return "TIME PARAMETERS";
  case COMMAND_CLASS_GEOGRAPHIC_LOCATION:
    return "GEOGRAPHIC LOCATION";
  case COMMAND_CLASS_COMPOSITE:
    return "COMPOSITE";
  case COMMAND_CLASS_MULTI_INSTANCE_ASSOCIATION:
    return "MULTI INSTANCE ASSOCIATION";
  case COMMAND_CLASS_MULTI_CMD:
    return "MULTI CMD";
  case COMMAND_CLASS_ENERGY_PRODUCTION:
    return "ENERGY PRODUCTION";
  case COMMAND_CLASS_MANUFACTURER_PROPRIETARY:
    return "MANUFACTURER PROPRIETARY";
  case COMMAND_CLASS_SCREEN_MD:
    return "SCREEN MD";
  case COMMAND_CLASS_SCREEN_ATTRIBUTES:
    return "SCREEN ATTRIBUTES";
  case COMMAND_CLASS_SIMPLE_AV_CONTROL:
    return "SIMPLE AV CONTROL";
  case COMMAND_CLASS_AV_CONTENT_DIRECTORY_MD:
    return "AV CONTENT DIRECTORY MD";
  case COMMAND_CLASS_AV_RENDERER_STATUS:
    return "AV RENDERER STATUS";
  case COMMAND_CLASS_AV_CONTENT_SEARCH_MD:
    return "AV CONTENT SEARCH MD";
  case COMMAND_CLASS_SECURITY:
    return "SECURITY";
  case COMMAND_CLASS_AV_TAGGING_MD:
    return "AV TAGGING MD";
  case COMMAND_CLASS_IP_CONFIGURATION:
    return "IP CONFIGURATION";
  case COMMAND_CLASS_ASSOCIATION_COMMAND_CONFIGURATION:
    return "ASSOCIATION COMMAND CONFIGURATION";
  case COMMAND_CLASS_SENSOR_ALARM:
    return "SENSOR ALARM";
  case COMMAND_CLASS_SILENCE_ALARM:
    return "SILENCE ALARM";
  case COMMAND_CLASS_SENSOR_CONFIGURATION:
    return "SENSOR CONFIGURATION";
  case COMMAND_CLASS_MARK:
    return "MARK";
  case COMMAND_CLASS_NON_INTEROPERABLE:
    return "NON INTEROPERABLE";
  }
  return "UNKNOWN";
}

uint8 cclassToNum (char const *str)
{
  if (strcmp(str, "NO OPERATION") == 0)
    return COMMAND_CLASS_NO_OPERATION;
  else if (strcmp(str, "BASIC") == 0)
    return COMMAND_CLASS_BASIC;
  else if (strcmp(str, "CONTROLLER REPLICATION") == 0)
    return COMMAND_CLASS_CONTROLLER_REPLICATION;
  else if (strcmp(str, "APPLICATION STATUS") == 0)
    return COMMAND_CLASS_APPLICATION_STATUS;
  else if (strcmp(str, "ZIP SERVICES") == 0)
    return COMMAND_CLASS_ZIP_SERVICES;
  else if (strcmp(str, "ZIP SERVER") == 0)
    return COMMAND_CLASS_ZIP_SERVER;
  else if (strcmp(str, "SWITCH BINARY") == 0)
    return COMMAND_CLASS_SWITCH_BINARY;
  else if (strcmp(str, "SWITCH MULTILEVEL") == 0)
    return COMMAND_CLASS_SWITCH_MULTILEVEL;
  else if (strcmp(str, "SWITCH ALL") == 0)
    return COMMAND_CLASS_SWITCH_ALL;
  else if (strcmp(str, "SWITCH TOGGLE BINARY") == 0)
    return COMMAND_CLASS_SWITCH_TOGGLE_BINARY;
  else if (strcmp(str, "SWITCH TOGGLE MULTILEVEL") == 0)
    return COMMAND_CLASS_SWITCH_TOGGLE_MULTILEVEL;
  else if (strcmp(str, "CHIMNEY FAN") == 0)
    return COMMAND_CLASS_CHIMNEY_FAN;
  else if (strcmp(str, "SCENE ACTIVATION") == 0)
    return COMMAND_CLASS_SCENE_ACTIVATION;
  else if (strcmp(str, "SCENE ACTUATOR CONF") == 0)
    return COMMAND_CLASS_SCENE_ACTUATOR_CONF;
  else if (strcmp(str, "SCENE CONTROLLER CONF") == 0)
    return COMMAND_CLASS_SCENE_CONTROLLER_CONF;
  else if (strcmp(str, "ZIP CLIENT") == 0)
    return COMMAND_CLASS_ZIP_CLIENT;
  else if (strcmp(str, "ZIP ADV SERVICES") == 0)
    return COMMAND_CLASS_ZIP_ADV_SERVICES;
  else if (strcmp(str, "SENSOR BINARY") == 0)
    return COMMAND_CLASS_SENSOR_BINARY;
  else if (strcmp(str, "SENSOR MULTILEVEL") == 0)
    return COMMAND_CLASS_SENSOR_MULTILEVEL;
  else if (strcmp(str, "METER") == 0)
    return COMMAND_CLASS_METER;
  else if (strcmp(str, "ZIP ADV SERVER") == 0)
    return COMMAND_CLASS_ZIP_ADV_SERVER;
  else if (strcmp(str, "ZIP ADV CLIENT") == 0)
    return COMMAND_CLASS_ZIP_ADV_CLIENT;
  else if (strcmp(str, "METER PULSE") == 0)
    return COMMAND_CLASS_METER_PULSE;
  else if (strcmp(str, "THERMOSTAT HEATING") == 0)
    return COMMAND_CLASS_THERMOSTAT_HEATING;
  else if (strcmp(str, "THERMOSTAT MODE") == 0)
    return COMMAND_CLASS_THERMOSTAT_MODE;
  else if (strcmp(str, "THERMOSTAT OPERATING STATE") == 0)
    return COMMAND_CLASS_THERMOSTAT_OPERATING_STATE;
  else if (strcmp(str, "THERMOSTAT SETPOINT") == 0)
    return COMMAND_CLASS_THERMOSTAT_SETPOINT;
  else if (strcmp(str, "THERMOSTAT FAN MODE") == 0)
    return COMMAND_CLASS_THERMOSTAT_FAN_MODE;
  else if (strcmp(str, "THERMOSTAT FAN STATE") == 0)
    return COMMAND_CLASS_THERMOSTAT_FAN_STATE;
  else if (strcmp(str, "CLIMATE CONTROL SCHEDULE") == 0)
    return COMMAND_CLASS_CLIMATE_CONTROL_SCHEDULE;
  else if (strcmp(str, "THERMOSTAT SETBACK") == 0)
    return COMMAND_CLASS_THERMOSTAT_SETBACK;
  else if (strcmp(str, "DOOR LOCK LOGGING") == 0)
    return COMMAND_CLASS_DOOR_LOCK_LOGGING;
  else if (strcmp(str, "SCHEDULE ENTRY LOCK") == 0)
    return COMMAND_CLASS_SCHEDULE_ENTRY_LOCK;
  else if (strcmp(str, "BASIC WINDOW COVERING") == 0)
    return COMMAND_CLASS_BASIC_WINDOW_COVERING;
  else if (strcmp(str, "MTP WINDOW COVERING") == 0)
    return COMMAND_CLASS_MTP_WINDOW_COVERING;
  else if (strcmp(str, "MULTI INSTANCE") == 0)
    return COMMAND_CLASS_MULTI_INSTANCE;
  else if (strcmp(str, "DOOR LOCK") == 0)
    return COMMAND_CLASS_DOOR_LOCK;
  else if (strcmp(str, "USER CODE") == 0)
    return COMMAND_CLASS_USER_CODE;
  else if (strcmp(str, "CONFIGURATION") == 0)
    return COMMAND_CLASS_CONFIGURATION;
  else if (strcmp(str, "ALARM") == 0)
    return COMMAND_CLASS_ALARM;
  else if (strcmp(str, "MANUFACTURER SPECIFIC") == 0)
    return COMMAND_CLASS_MANUFACTURER_SPECIFIC;
  else if (strcmp(str, "POWERLEVEL") == 0)
    return COMMAND_CLASS_POWERLEVEL;
  else if (strcmp(str, "PROTECTION") == 0)
    return COMMAND_CLASS_PROTECTION;
  else if (strcmp(str, "LOCK") == 0)
    return COMMAND_CLASS_LOCK;
  else if (strcmp(str, "NODE NAMING") == 0)
    return COMMAND_CLASS_NODE_NAMING;
  else if (strcmp(str, "FIRMWARE UPDATE MD") == 0)
    return COMMAND_CLASS_FIRMWARE_UPDATE_MD;
  else if (strcmp(str, "GROUPING NAME") == 0)
    return COMMAND_CLASS_GROUPING_NAME;
  else if (strcmp(str, "REMOTE ASSOCIATION ACTIVATE") == 0)
    return COMMAND_CLASS_REMOTE_ASSOCIATION_ACTIVATE;
  else if (strcmp(str, "REMOTE ASSOCIATION") == 0)
    return COMMAND_CLASS_REMOTE_ASSOCIATION;
  else if (strcmp(str, "BATTERY") == 0)
    return COMMAND_CLASS_BATTERY;
  else if (strcmp(str, "CLOCK") == 0)
    return COMMAND_CLASS_CLOCK;
  else if (strcmp(str, "HAIL") == 0)
    return COMMAND_CLASS_HAIL;
  else if (strcmp(str, "WAKE UP") == 0)
    return COMMAND_CLASS_WAKE_UP;
  else if (strcmp(str, "ASSOCIATION") == 0)
    return COMMAND_CLASS_ASSOCIATION;
  else if (strcmp(str, "VERSION") == 0)
    return COMMAND_CLASS_VERSION;
  else if (strcmp(str, "INDICATOR") == 0)
    return COMMAND_CLASS_INDICATOR;
  else if (strcmp(str, "PROPRIETARY") == 0)
    return COMMAND_CLASS_PROPRIETARY;
  else if (strcmp(str, "LANGUAGE") == 0)
    return COMMAND_CLASS_LANGUAGE;
  else if (strcmp(str, "TIME") == 0)
    return COMMAND_CLASS_TIME;
  else if (strcmp(str, "TIME PARAMETERS") == 0)
    return COMMAND_CLASS_TIME_PARAMETERS;
  else if (strcmp(str, "GEOGRAPHIC LOCATION") == 0)
    return COMMAND_CLASS_GEOGRAPHIC_LOCATION;
  else if (strcmp(str, "COMPOSITE") == 0)
    return COMMAND_CLASS_COMPOSITE;
  else if (strcmp(str, "MULTI INSTANCE ASSOCIATION") == 0)
    return COMMAND_CLASS_MULTI_INSTANCE_ASSOCIATION;
  else if (strcmp(str, "MULTI CMD") == 0)
    return COMMAND_CLASS_MULTI_CMD;
  else if (strcmp(str, "ENERGY PRODUCTION") == 0)
    return COMMAND_CLASS_ENERGY_PRODUCTION;
  else if (strcmp(str, "MANUFACTURER PROPRIETARY") == 0)
    return COMMAND_CLASS_MANUFACTURER_PROPRIETARY;
  else if (strcmp(str, "SCREEN MD") == 0)
    return COMMAND_CLASS_SCREEN_MD;
  else if (strcmp(str, "SCREEN ATTRIBUTES") == 0)
    return COMMAND_CLASS_SCREEN_ATTRIBUTES;
  else if (strcmp(str, "SIMPLE AV CONTROL") == 0)
    return COMMAND_CLASS_SIMPLE_AV_CONTROL;
  else if (strcmp(str, "AV CONTENT DIRECTORY MD") == 0)
    return COMMAND_CLASS_AV_CONTENT_DIRECTORY_MD;
  else if (strcmp(str, "AV RENDERER STATUS") == 0)
    return COMMAND_CLASS_AV_RENDERER_STATUS;
  else if (strcmp(str, "AV CONTENT SEARCH MD") == 0)
    return COMMAND_CLASS_AV_CONTENT_SEARCH_MD;
  else if (strcmp(str, "SECURITY") == 0)
    return COMMAND_CLASS_SECURITY;
  else if (strcmp(str, "AV TAGGING MD") == 0)
    return COMMAND_CLASS_AV_TAGGING_MD;
  else if (strcmp(str, "IP CONFIGURATION") == 0)
    return COMMAND_CLASS_IP_CONFIGURATION;
  else if (strcmp(str, "ASSOCIATION COMMAND CONFIGURATION") == 0)
    return COMMAND_CLASS_ASSOCIATION_COMMAND_CONFIGURATION;
  else if (strcmp(str, "SENSOR ALARM") == 0)
    return COMMAND_CLASS_SENSOR_ALARM;
  else if (strcmp(str, "SILENCE ALARM") == 0)
    return COMMAND_CLASS_SILENCE_ALARM;
  else if (strcmp(str, "SENSOR CONFIGURATION") == 0)
    return COMMAND_CLASS_SENSOR_CONFIGURATION;
  else if (strcmp(str, "MARK") == 0)
    return COMMAND_CLASS_MARK;
  else if (strcmp(str, "NON INTEROPERABLE") == 0)
    return COMMAND_CLASS_NON_INTEROPERABLE;
  else
    return COMMAND_CLASS_NON_UNKNOWN;
}

const char *controllerErrorToStr (Driver::ControllerError err)
{
  switch (err) {
  case Driver::ControllerError_None:
    return "None";
  case Driver::ControllerError_ButtonNotFound:
    return "Button Not Found";
  case Driver::ControllerError_NodeNotFound:
    return "Node Not Found";
  case Driver::ControllerError_NotBridge:
    return "Not a Bridge";
  case Driver::ControllerError_NotPrimary:
    return "Not Primary Controller";
  case Driver::ControllerError_IsPrimary:
    return "Is Primary Controller";
  case Driver::ControllerError_NotSUC:
    return "Not Static Update Controller";
  case Driver::ControllerError_NotSecondary:
    return "Not Secondary Controller";
  case Driver::ControllerError_NotFound:
    return "Not Found";
  case Driver::ControllerError_Busy:
    return "Controller Busy";
  case Driver::ControllerError_Failed:
    return "Failed";
  case Driver::ControllerError_Disabled:
    return "Disabled";
  case Driver::ControllerError_Overflow:
    return "Overflow";
  default:
    return "Unknown error";
  }
}

ValueID findValueID(list<ValueID> values, uint8 command_class, uint8 instance, uint8 index){
	for (list<ValueID>::iterator it = values.begin(); it != values.end(); ++it){
		uint8 id = (*it).GetCommandClassId();
		uint8 inst = (*it).GetInstance();
		uint8 ind = (*it).GetIndex();
		if(command_class == id && inst == instance && index == ind){
			return (*it);
		}
	}
	return NullValueID::GetValue();
}

ValueID* NullValueID::nullValueID = NULL;

bool NullValueID::IsNull(ValueID valueID) {
	return (valueID == GetValue()) ? true : false;
}
ValueID NullValueID::GetValue() {
	if(nullValueID == NULL)
		nullValueID = GreateInstance();
	return *nullValueID;
};

ValueID* NullValueID::GreateInstance(){
	return new ValueID(home_id , node_id, ValueID::ValueGenre_Basic, command_class, instance, index ,ValueID::ValueType_Bool);
}

void NullValueID::Destroy() {
	if(nullValueID == NULL)
		return;
	delete nullValueID;
	nullValueID = NULL;
}

ValueCallback::~ValueCallback(){
	Log::Write(LogLevel_Info, "ValueCallback::~ValueCallback() : 0x%08x", this);
}

}


