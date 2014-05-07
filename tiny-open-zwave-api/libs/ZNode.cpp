/*
 * ZNode.cpp
 *
 *  Created on: Feb 27, 2014
 *      Author: vassik
 */

#include <string.h>

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

#include "ZNode.h"
#include "DomoZWave.h"
#include "Utility.h"
#include "../devices/TinyController.h"
#include "../observer/NodeSubject.h"
#include "../observer/ControllerSubject.h"
#include "../devices/Device.h"


namespace TinyOpenZWaveApi{

map<char const*, TinyController*> ZNode::controllers;
map<uint8, NodeSubject*> ZNode::m_nodeSub;
map<uint32, ControllerSubject*> ZNode::m_ctrlSub;

void ZNode::Init(const char* logname, bool enableLog){
	ZWave_Init(logname, enableLog);
	controllers.clear();
	m_nodeSub.clear();
	m_ctrlSub.clear();
}

void ZNode::Destroy(){
	ZWave_Destroy();
	controllers.clear();
	m_nodeSub.clear();
	m_ctrlSub.clear();
}

TinyController* ZNode::FindController(char const* port){
	for(std::map<char const*, TinyController*>::iterator it = ZNode::controllers.begin(); it != ZNode::controllers.end(); ++it){
		if(std::strcmp(it->first, port) == 0)
			return ZNode::controllers[it->first];
	}
	return NULL;
}

void ZNode::DeviceAdded(Device* device){
	list<NodeInfo*>& g_nodes = ZWave_GetGNodes();
	NodeInfo *node = NULL;
	for(list<NodeInfo*>::iterator it = g_nodes.begin(); it != g_nodes.end(); ++it){

		if(device->getNodeId() == (*it)->m_nodeId && device->getController()->homeId == (*it)->m_homeId){
			node = (*it);
			break;
		}
	}
	if(node != NULL && m_nodeSub.find(device->getNodeId()) != m_nodeSub.end()){
		NodeSubject* nodeSubject = m_nodeSub[device->getNodeId()];
		if(nodeSubject->getNodeInfo() == node){
			nodeSubject->attach(device);
			device->setUp(node);
		}
	}
}

void ZNode::AddNode(Notification const* _notification){
	NodeInfo* nodeInfo = new NodeInfo();
	nodeInfo->m_nodeId = _notification->GetNodeId();
	nodeInfo->m_homeId = _notification->GetHomeId();
	nodeInfo->m_DeviceState = DZType_Unknown;
	nodeInfo->m_LastSeen = 0;
	Log::Write(LogLevel_Info, "ZNode::AddNode() : adding node value %d", nodeInfo->m_nodeId);
	ZWave_GetGNodes().push_back(nodeInfo);

	string controllerPath = Manager::Get()->GetControllerPath(nodeInfo->m_homeId);
	TinyController* controller = FindController(controllerPath.c_str());
	if(controller == NULL){
		Log::Write(LogLevel_Error, "ZNode::AddNode() : can not find proper controller with homeID 0x%08x", nodeInfo->m_homeId);
		return;
	}
	NodeSubject* nodeSubject = new NodeSubject(nodeInfo, _notification);
	list<Device*> devices = controller->getDevices();
	for(list<Device*>::iterator it = devices.begin(); it != devices.end(); ++it){
		if(nodeInfo->m_nodeId == (*it)->getNodeId()  && nodeInfo->m_homeId == (*it)->getController()->homeId){
			nodeSubject->attach((*it));
		}
	}
	m_nodeSub[nodeInfo->m_nodeId] = nodeSubject;
	nodeSubject->notify();
}

int32 ZNode::GetNodeCount(){
	return ZWave_GetGNodes().size();
}

NodeInfo *ZNode::GetNodeInfo(Notification const* _data){
	NodeInfo* info = ZWave_GetNodeInfo(_data);
	return info;
}

void ZNode::AddValue(Notification const* _data){
	NodeInfo *nodeInfo = GetNodeInfo(_data);
	if(nodeInfo != NULL){
		nodeInfo->m_values.push_back(_data->GetValueID());
	}
	ZWave_RPC_ValueChanged( (int)_data->GetHomeId(), (int)_data->GetNodeId(), _data->GetValueID(), true );

	if(m_nodeSub.find((int)_data->GetNodeId()) != m_nodeSub.end()){
		NodeSubject* nodeSubject = m_nodeSub[(int)_data->GetNodeId()];
		nodeSubject->setNodeInfo(nodeInfo);
		nodeSubject->setNotification(_data);
		nodeSubject->notify();
	}else{
		Log::Write(LogLevel_Error, "ZNode::AddValue() : value changes, can not find subject for the given node"
				"(nodeId %d, homeID 0x%08x) in the list", (int)_data->GetNodeId(), (int)_data->GetHomeId());
	}
}

void ZNode::RemoveNode(Notification const* _data){
	uint32 const homeId = _data->GetHomeId();
	uint8 const nodeId = _data->GetNodeId();
	list<NodeInfo*>& g_nodes = ZWave_GetGNodes();

	for ( list<NodeInfo*>::iterator it = g_nodes.begin(); it != g_nodes.end(); ++it ) {
		NodeInfo* nodeInfo = *it;
		if ( ( nodeInfo->m_homeId == homeId ) && ( nodeInfo->m_nodeId == nodeId ) ){
			g_nodes.erase( it );
			break;
		}
	}
	ZWave_RPC_NodeRemoved( (int)_data->GetHomeId(), (int)_data->GetNodeId() );
}

void ZNode::NewNode(Notification const* _data){

}

void ZNode::RemoveValue(Notification const* _data){
	NodeInfo* nodeInfo = ZNode::GetNodeInfo(_data);
	if (nodeInfo != NULL){
		// Remove the value from out list
		for (list<ValueID>::iterator it = nodeInfo->m_values.begin(); it != nodeInfo->m_values.end(); ++it) {
			if ((*it) == _data->GetValueID())
			{
				nodeInfo->m_values.erase( it );
				break;
			}
		}
	}
	ZWave_RPC_ValueRemoved((int)_data->GetHomeId(), (int)_data->GetNodeId(), _data->GetValueID());

	if(m_nodeSub.find((int)_data->GetNodeId()) != m_nodeSub.end()){
		NodeSubject* nodeSubject = m_nodeSub[(int)_data->GetNodeId()];
		nodeSubject->setNodeInfo(nodeInfo);
		nodeSubject->setNotification(_data);
		nodeSubject->notify();
	}else{
		Log::Write(LogLevel_Error, "ZNode::RemoveValue() : value changes, can not find subject for the given node"
				"(nodeId %d, homeID 0x%08x) in the list", (int)_data->GetNodeId(), (int)_data->GetHomeId());
	}
}

void ZNode::ChangeValue(Notification const* _data){
	ZWave_RPC_ValueChanged((int)_data->GetHomeId(), (int)_data->GetNodeId(), _data->GetValueID(), false);

	NodeInfo* nodeInfo = ZNode::GetNodeInfo(_data);
	// Update LastSeen and DeviceState
	if (nodeInfo != NULL){
		nodeInfo->m_LastSeen = time(NULL);
		nodeInfo->m_DeviceState = DZType_Alive;
	}

	// Check if zwcfg*xml has been written 3600+ sec, then flush to disk
	m_structCtrl* ctrl = ZWave_GetControllerInfo((int)_data->GetHomeId());
	if ( ctrl->m_lastWriteXML > 0 ){
		double seconds;
		seconds = difftime( time( NULL ), ctrl->m_lastWriteXML );

		if ( seconds > 3600 ){
			Manager::Get()->WriteConfig((int)_data->GetHomeId());
			Log::Write(LogLevel_Debug, "ZNode::changeValue: HomeId=%d (%.f seconds)", (int)_data->GetHomeId(), seconds);
			ctrl->m_lastWriteXML = time(NULL);
		}
	}

	if(m_nodeSub.find((int)_data->GetNodeId()) != m_nodeSub.end()){
		NodeSubject* nodeSubject = m_nodeSub[(int)_data->GetNodeId()];
		nodeSubject->setNodeInfo(nodeInfo);
		nodeSubject->setNotification(_data);
		nodeSubject->notify();
	}else{
		Log::Write(LogLevel_Error, "ZNode::changeValue: value changes, can not find subject for the given node"
				"(nodeId %d, homeID 0x%08x) in the list", (int)_data->GetNodeId(), (int)_data->GetHomeId());
	}
}

void ZNode::RefreshedValue(Notification const* _data){

}

void ZNode::TypeGroup(Notification const* _data){

}

void ZNode::ControllerReady(Notification const* _data){
	ZWave_RPC_DriverReady(_data->GetHomeId(), _data->GetNodeId());
	string controllerPath = Manager::Get()->GetControllerPath(_data->GetHomeId());
	TinyController* controller = FindController(controllerPath.c_str());
	if(controller == NULL){
		Log::Write(LogLevel_Error, " ZNode::controllerReady : can not find proper controller with homeID 0x%08x", _data->GetHomeId());
		return;
	}
	m_structCtrl* info = ZWave_GetControllerInfo(_data->GetHomeId());
	ControllerSubject* subject = new ControllerSubject(info, _data);
	subject->attach(controller);
	m_ctrlSub[_data->GetHomeId()] = subject;
	subject->notify();

}

void ZNode::ControllerFailed(Notification const* _data){

}

void ZNode::ControllerReset(Notification const* _data){

}

m_structCtrl* ZNode::GetControllerInfo(uint32 const homeId){
	m_structCtrl* info = ZWave_GetControllerInfo(homeId);
	return info;
}

void ZNode::UpdateNodeProtocolInfo(uint32 const homeId, uint8 const nodeId){
	ZWave_RPC_NodeProtocolInfo((int)homeId, (int)nodeId);
}

void ZNode::UpdateNodeEvent(Notification const* _data){
	// Event caused by basic set or hail
	ZWave_RPC_NodeEvent((int)_data->GetHomeId(), (int)_data->GetNodeId(), _data->GetValueID(), (int)_data->GetEvent());
	NodeInfo* nodeInfo = ZWave_GetNodeInfo(_data);
	if(nodeInfo != NULL){
		nodeInfo->m_LastSeen = time(NULL);
		nodeInfo->m_DeviceState = DZType_Alive;
	}
}

void ZNode::AllNodeQueriedSomeDead(Notification const* _data){
	m_structCtrl* ctrl = ZWave_GetControllerInfo((int)_data->GetHomeId());

	if(_data->GetType() == Notification::Type_AllNodesQueried ) ZWave_WriteLog( LogLevel_Debug, true, "AllNodesQueried: HomeId=%d", (int)_data->GetHomeId());
	if(_data->GetType() == Notification::Type_AwakeNodesQueried ) ZWave_WriteLog( LogLevel_Debug, true, "AwakeNodesQueried: HomeId=%d", (int)_data->GetHomeId());
	if(_data->GetType() == Notification::Type_AllNodesQueriedSomeDead ) ZWave_WriteLog( LogLevel_Debug, true, "AllNodesQueriedSomeDead: HomeId=%d", (int)_data->GetHomeId());

	if(ctrl->m_controllerAllQueried == 0){
		// Write zwcfg*xml file
		Manager::Get()->WriteConfig((int)_data->GetHomeId());

		// The zwcfg*xml is written, save the current time
		ctrl->m_lastWriteXML = time(NULL);

	}else{
		// If we got 2 or more a AllQueried, then there is something really wrong somewhere
		if ( ctrl->m_controllerAllQueried > 1 ) {
			ZWave_WriteLog( LogLevel_Error, true, "ERROR: AllNodesQueried happened %d times (max should be 2)", ctrl->m_controllerAllQueried );
		}
	}
	ctrl->m_controllerAllQueried++;

	if(m_ctrlSub.find(_data->GetHomeId()) != m_ctrlSub.end()){
		ControllerSubject* subject = m_ctrlSub[_data->GetHomeId()];
		subject->setControllerInfo(ctrl);
		subject->setNotification(_data);
		subject->notify();
	}else{
		Log::Write(LogLevel_Info, "ZNode::AllNodeQueriedSomeDead(): can not find controller to notify for homeID 0x%08x", _data->GetHomeId());
	}
}

void ZNode::AllNodeQueried(Notification const* _data){
	list<m_structCtrl*>& g_allControllers = ZWave_GetGControllers();
	for(list<m_structCtrl*>::iterator it = g_allControllers.begin(); it != g_allControllers.end(); ++it){
		uint32 homeId = (*it)->m_homeId;
		ZWave_WriteConfig(homeId);
		(*it)->m_lastWriteXML = time(NULL);
	}
	m_structCtrl* ctrl = ZWave_GetControllerInfo(_data->GetHomeId());
	if(m_ctrlSub.find(_data->GetHomeId()) != m_ctrlSub.end()){
		ControllerSubject* subject = m_ctrlSub[_data->GetHomeId()];
		subject->setControllerInfo(ctrl);
		subject->setNotification(_data);
		subject->notify();
	}else{
		Log::Write(LogLevel_Info, "ZNode::AllNodeQueried(): can not find controller to notify for homeID 0x%08x", _data->GetHomeId());
	}
}

void ZNode::AwakeNodesQueried(Notification const* _data){
	m_structCtrl* ctrl = ZWave_GetControllerInfo(_data->GetHomeId());
	if(m_ctrlSub.find(_data->GetHomeId()) != m_ctrlSub.end()){
		ControllerSubject* subject = m_ctrlSub[_data->GetHomeId()];
		subject->setControllerInfo(ctrl);
		subject->setNotification(_data);
		subject->notify();
	}else{
		Log::Write(LogLevel_Info, "ZNode::AwakeNodesQueried(): can not find controller to notify for homeID 0x%08x", _data->GetHomeId());
	}
}

void ZNode::NodeQueriesComplete(Notification const* _data){
	m_structCtrl* ctrl = ZWave_GetControllerInfo(_data->GetHomeId());
	if(m_ctrlSub.find(_data->GetHomeId()) != m_ctrlSub.end()){
		ControllerSubject* subject = m_ctrlSub[_data->GetHomeId()];
		subject->setControllerInfo(ctrl);
		subject->setNotification(_data);
		subject->notify();
	}else{
		Log::Write(LogLevel_Info, "ZNode::NodeQueriesComplete(): can not find controller to notify for homeID 0x%08x", _data->GetHomeId());
	}
}

void ZNode::MessageComplete(Notification const* _data){
	NodeInfo* nodeInfo = ZWave_GetNodeInfo(_data);
	if (nodeInfo != NULL){
		nodeInfo->m_LastSeen = time(NULL);
		nodeInfo->m_DeviceState = DZType_Alive;
	}
}

void ZNode::MessageAwake(Notification const* _data){
	NodeInfo* nodeInfo = ZWave_GetNodeInfo(_data);
	if (nodeInfo != NULL){
		nodeInfo->m_LastSeen = time(NULL);
		nodeInfo->m_DeviceState = DZType_Awake;
	}
}

void ZNode::MessageAlive(Notification const* _data){
	NodeInfo* nodeInfo = ZWave_GetNodeInfo(_data);
	if (nodeInfo != NULL){
		nodeInfo->m_LastSeen = time(NULL);
		nodeInfo->m_DeviceState = DZType_Alive;
	}
}

char* ZNode::GetValueIDValue(ValueID valueID){
	static char dev_value[1024] = "";
	int type = valueID.GetType();
	uint8 byte_value;
	bool bool_value;
	string decimal_value;
	string list_value;
	string string_value;
	int int_value;
	int16 short_value;
	switch ( type ) {
		case ValueID::ValueType_Bool:
			Manager::Get()->GetValueAsBool( valueID, &bool_value );
			snprintf( dev_value, 1024, "%i", bool_value );
			Log::Write(LogLevel_Info, "ZNode::getValueIDValue() : Type=Bool (raw value=%s)", dev_value);
			break;
		case ValueID::ValueType_Byte:
			Manager::Get()->GetValueAsByte( valueID, &byte_value );
			snprintf( dev_value, 1024, "%i", byte_value );
			Log::Write(LogLevel_Info, "ZNode::getValueIDValue() : Type=Byte (raw value=%s)", dev_value);
			break;
		case ValueID::ValueType_Decimal:
			Manager::Get()->GetValueAsString( valueID, &decimal_value );
			snprintf( dev_value, 1024, "%s", strdup( decimal_value.c_str() ) );
			Log::Write(LogLevel_Info, "ZNode::getValueIDValue() : Type=Decimal (raw value=%s)", dev_value );
			break;
		case ValueID::ValueType_Int:
			Manager::Get()->GetValueAsInt( valueID, &int_value );
			snprintf( dev_value, 1024, "%d", int_value );
			Log::Write(LogLevel_Info, "ZNode::getValueIDValue() : Type=Integer (raw value=%s)", dev_value );
			break;
		case ValueID::ValueType_Short:
			Manager::Get()->GetValueAsShort( valueID, &short_value );
			snprintf( dev_value, 1024, "%d", short_value );
			Log::Write(LogLevel_Info, "ZNode::getValueIDValue() : Type=Short (raw value=%s)", dev_value );
			break;
		case ValueID::ValueType_Schedule:
			Log::Write(LogLevel_Info, "ZNode::getValueIDValue() : Type=Schedule (not implemented)" );
			break;
		case ValueID::ValueType_String:
			Manager::Get()->GetValueAsString( valueID, &string_value );
			snprintf( dev_value, 1024, "%s", strdup( string_value.c_str() ) );
			Log::Write(LogLevel_Info, "Type=String (raw value=%s)", dev_value );
			break;
		case ValueID::ValueType_Button:
			Log::Write(LogLevel_Info, "ZNode::getValueIDValue() : Type=Button (not implemented)");
			break;
		case ValueID::ValueType_List:
			Manager::Get()->GetValueListSelection( valueID, &list_value );
			snprintf( dev_value, 1024, "%s", strdup( list_value.c_str() ) );
			Log::Write(LogLevel_Info, "ZNode::getValueIDValue() : Type=List (raw value=%s)", dev_value);
			break;
		case ValueID::ValueType_Raw:
			// We can use AsString on a Raw
			Manager::Get()->GetValueAsString( valueID, &string_value );
			snprintf( dev_value, 1024, "%s", strdup( string_value.c_str() ) );
			Log::Write(LogLevel_Info, "ZNode::getValueIDValue() : Type=Raw (raw value=%s)", dev_value);
			break;
		default:
			Log::Write(LogLevel_Info, "ZNode::getValueIDValue() : Type=Unknown");
			break;
	}
	return dev_value;
}

void ZNode::SetValueIDValue(ValueID valueID, int32 value){
	int command_class = valueID.GetCommandClassId();
	string label = Manager::Get()->GetValueLabel(valueID);
	if (command_class == COMMAND_CLASS_SWITCH_MULTILEVEL || command_class == COMMAND_CLASS_SWITCH_BINARY) {
		switch (command_class) {
			case COMMAND_CLASS_SWITCH_BINARY:
				// "Switch" is mandatory, otherwise not a switch and value should be 0(off) or 255(on)
				if (!(label == "Switch" && (value == 0 || value == 255))){
					Log::Write(LogLevel_Info, "ZNode::SetValueIDValue() : value is COMMAND_CLASS_SWITCH_BINARY,"
							"but is not labeled as a Switch or value is not 0 either 255 : Label '%s', %d ", label.c_str(), value);
					return;
				}
				break;
			case COMMAND_CLASS_SWITCH_MULTILEVEL:
				// label="Level" is mandatory, otherwise not a dimmer type device
				if (label != "Level") {
					Log::Write(LogLevel_Info, "ZNode::SetValueIDValue() : value is COMMAND_CLASS_SWITCH_MULTILEVEL,"
							"but is not labeled as a Level : Label '%s', %d ", label.c_str(), value);
					return;
				}
				break;
			default:
				Log::Write(LogLevel_Info, "ZNode::SetValueIDValue() : unsupported command class of the ValueID to set a value"
						"Genre %s Class %s Instance %d Index %d Type %s", genreToStr(valueID.GetGenre()),
						cclassToStr(valueID.GetCommandClassId()), valueID.GetInstance(),
						valueID.GetIndex(), typeToStr(valueID.GetType()));
		}

		bool response = false;
		switch(valueID.GetType()){
			case ValueID::ValueType_Bool :
				response = Manager::Get()->SetValue(valueID, (bool) value);
				break;
			case ValueID::ValueType_Byte :
				response = Manager::Get()->SetValue(valueID, (uint8) value);
				break;
			case ValueID::ValueType_Short :
				response = Manager::Get()->SetValue(valueID, (uint16) value);
				break;
			case ValueID::ValueType_Int :
				response = Manager::Get()->SetValue(valueID, value);
				break;
			case ValueID::ValueType_List :
				response = Manager::Get()->SetValue(valueID, value );
				break;
			default:
				Log::Write(LogLevel_Info, "ZNode::SetValueIDValue() : unknown ValueType");
		}

		if(!response)
			Log::Write(LogLevel_Info, "ZNode::SetValueIDValue() : cannot set value for the given value"
					"Genre %s Class %s Instance %d Index %d Type %s", genreToStr(valueID.GetGenre()),
					cclassToStr(valueID.GetCommandClassId()), valueID.GetInstance(),
					valueID.GetIndex(), typeToStr(valueID.GetType()));
	}else{
		Log::Write(LogLevel_Info, "ZNode::SetValueIDValue() : unsupported command class, cannot set value"
				"Genre %s Class %s Instance %d Index %d Type %s", genreToStr(valueID.GetGenre()),
				cclassToStr(valueID.GetCommandClassId()), valueID.GetInstance(),
				valueID.GetIndex(), typeToStr(valueID.GetType()));
	}
}

}
