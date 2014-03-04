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
#include "../TinyZWaveFacade.h"


using namespace TinyOpenZWaveApi;

std::map<int, NodeSubject*> m_nodeSub;
std::map<uint32, ControllerSubject*> m_ctrlSub;

void ZNode::zwaveInit(const char* logname, bool enableLog){
	ZWave_Init(logname, enableLog);
}

void ZNode::zwaveDetroy(){
	ZWave_Destroy();
}

void ZNode::deviceAdded(Device* device){
	Log::Write(LogLevel_Info,"ZNode::deviceAdded() is called");
	list<NodeInfo*>& g_nodes = ZWave_GetGNodes();
	NodeInfo *node = NULL;
	for(list<NodeInfo*>::iterator it = g_nodes.begin(); it != g_nodes.end(); ++it){

		if(device->nodeId == (*it)->m_nodeId && device->controller->controllerHomeId == (*it)->m_homeId){
			node = (*it);
			break;
		}
	}
	if(node != NULL && m_nodeSub.find(device->nodeId) != m_nodeSub.end()){
		NodeSubject* nodeSubject = m_nodeSub[device->nodeId];
		if(nodeSubject->getNodeInfo() == node){
			nodeSubject->attach(device);
			device->setUp(node);
		}
	}
}

void ZNode::addNode(Notification const* _notification){
	NodeInfo* nodeInfo = new NodeInfo();
	nodeInfo->m_nodeId = _notification->GetNodeId();
	nodeInfo->m_homeId = _notification->GetHomeId();
	nodeInfo->m_DeviceState = DZType_Unknown;
	nodeInfo->m_LastSeen = 0;
	Log::Write(LogLevel_Info, "ZNode::addNode() : adding node value %d", nodeInfo->m_nodeId);
	ZWave_GetGNodes().push_back(nodeInfo);

	string controllerPath = Manager::Get()->GetControllerPath(nodeInfo->m_homeId);
	TinyController* controller = OpenZWaveFacade::GetController(controllerPath.c_str());
	if(controller == NULL){
		Log::Write(LogLevel_Error, "ZNode::addNode() : can not find proper controller with homeID 0x%08x", nodeInfo->m_homeId);
		return;
	}
	NodeSubject* nodeSubject = new NodeSubject(nodeInfo, _notification);
	list<Device*> devices = controller->getDevices();
	for(list<Device*>::iterator it = devices.begin(); it != devices.end(); ++it){
		if(nodeInfo->m_nodeId == (*it)->nodeId  && nodeInfo->m_homeId == (*it)->controller->controllerHomeId){
			nodeSubject->attach((*it));
		}
	}
	m_nodeSub[nodeInfo->m_nodeId] = nodeSubject;
	nodeSubject->notify();
}

int32 ZNode::getNodeCount(){
	return ZWave_GetGNodes().size();
}

NodeInfo *ZNode::getNodeInfo(Notification const* _data){
	NodeInfo* info = ZWave_GetNodeInfo(_data);
	return info;
}

void ZNode::addValue(Notification const* _data){
	NodeInfo *nodeInfo = getNodeInfo(_data);
	if(nodeInfo != NULL){
		nodeInfo->m_values.push_back(_data->GetValueID());
	}
	ZWave_RPC_ValueChanged( (int)_data->GetHomeId(), (int)_data->GetNodeId(), _data->GetValueID(), true );
}

void ZNode::removeNode(Notification const* _data){
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

void ZNode::newNode(Notification const* _data){

}

void ZNode::removeValue(Notification const* _data){
	NodeInfo* nodeInfo = ZNode::getNodeInfo(_data);
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
}

void ZNode::changeValue(Notification const* _data){
	ZWave_RPC_ValueChanged((int)_data->GetHomeId(), (int)_data->GetNodeId(), _data->GetValueID(), false);

	NodeInfo* nodeInfo = ZNode::getNodeInfo(_data);
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

void ZNode::refreshedValue(Notification const* _data){

}

void ZNode::typeGroup(Notification const* _data){

}

void ZNode::controllerReady(Notification const* _data){
	ZWave_RPC_DriverReady(_data->GetHomeId(), _data->GetNodeId());
	string controllerPath = Manager::Get()->GetControllerPath(_data->GetHomeId());
	TinyController* controller = OpenZWaveFacade::GetController(controllerPath.c_str());
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

m_structCtrl* ZNode::getControllerInfo(uint32 const homeId){
	m_structCtrl* info = ZWave_GetControllerInfo(homeId);
	return info;
}

void ZNode::updateNodeProtocolInfo(uint32 const homeId, uint8 const nodeId){
	ZWave_RPC_NodeProtocolInfo((int)homeId, (int)nodeId);
}

void ZNode::updateNodeEvent(Notification const* _data){
	// Event caused by basic set or hail
	ZWave_RPC_NodeEvent((int)_data->GetHomeId(), (int)_data->GetNodeId(), _data->GetValueID(), (int)_data->GetEvent());
	NodeInfo* nodeInfo = ZWave_GetNodeInfo(_data);
	if(nodeInfo != NULL){
		nodeInfo->m_LastSeen = time(NULL);
		nodeInfo->m_DeviceState = DZType_Alive;
	}
}

void ZNode::allNodeQueriedSomeDead(Notification const* _data){
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
}

void ZNode::allNodeQueried(Notification const* _data){
	list<m_structCtrl*>& g_allControllers = ZWave_GetGControllers();
	for(list<m_structCtrl*>::iterator it = g_allControllers.begin(); it != g_allControllers.end(); ++it){
		uint32 homeId = (*it)->m_homeId;
		ZWave_WriteConfig(homeId);
		(*it)->m_lastWriteXML = time(NULL);
	}
	Log::Write(LogLevel_Info, "ZNode::allNodeQueried(): calling");
}

void ZNode::messageComplete(Notification const* _data){
	NodeInfo* nodeInfo = ZWave_GetNodeInfo(_data);
	if (nodeInfo != NULL){
		nodeInfo->m_LastSeen = time(NULL);
		nodeInfo->m_DeviceState = DZType_Alive;
	}
}

void ZNode::messageAwake(Notification const* _data){
	NodeInfo* nodeInfo = ZWave_GetNodeInfo(_data);
	if (nodeInfo != NULL){
		nodeInfo->m_LastSeen = time(NULL);
		nodeInfo->m_DeviceState = DZType_Awake;
	}
}

void ZNode::messageAlive(Notification const* _data){
	NodeInfo* nodeInfo = ZWave_GetNodeInfo(_data);
	if (nodeInfo != NULL){
		nodeInfo->m_LastSeen = time(NULL);
		nodeInfo->m_DeviceState = DZType_Alive;
	}
}


