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
#include "libs/DomoZWave.h"
#include "libs/Utility.h"

using namespace OpenZWave;

void ZNode::addNode(Notification const* _notification){
	NodeInfo* nodeInfo = new NodeInfo();
	nodeInfo->m_nodeId = _notification->GetNodeId();
	nodeInfo->m_homeId = _notification->GetHomeId();
	nodeInfo->m_DeviceState = DZType_Unknown;
	nodeInfo->m_LastSeen = 0;
	DomoZWave_GetGNodes().push_back(nodeInfo);
	Log::Write(LogLevel_Info, "ZNode(): adding node value %d", nodeInfo->m_nodeId);
}

int32 ZNode::getNodeCount(){
	return DomoZWave_GetGNodes().size();
}

NodeInfo *ZNode::getNodeInfo(Notification const* _data){
	return DomoZWave_GetNodeInfo(_data);
}

void ZNode::addValue(Notification const* _data){
	NodeInfo *nodeInfo = getNodeInfo(_data);
	if(nodeInfo != NULL){
		nodeInfo->m_values.push_back(_data->GetValueID());
	}
	DomoZWave_RPC_ValueChanged( (int)_data->GetHomeId(), (int)_data->GetNodeId(), _data->GetValueID(), true );
}

void ZNode::removeNode(Notification const* _data){
	uint32 const homeId = _data->GetHomeId();
	uint8 const nodeId = _data->GetNodeId();
	list<NodeInfo*>& g_nodes = DomoZWave_GetGNodes();

	for ( list<NodeInfo*>::iterator it = g_nodes.begin(); it != g_nodes.end(); ++it ) {
		NodeInfo* nodeInfo = *it;
		if ( ( nodeInfo->m_homeId == homeId ) && ( nodeInfo->m_nodeId == nodeId ) ){
			g_nodes.erase( it );
			break;
		}
	}
	DomoZWave_RPC_NodeRemoved( (int)_data->GetHomeId(), (int)_data->GetNodeId() );
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
	DomoZWave_RPC_ValueRemoved((int)_data->GetHomeId(), (int)_data->GetNodeId(), _data->GetValueID());
}

void ZNode::changeValue(Notification const* _data){
	DomoZWave_RPC_ValueChanged((int)_data->GetHomeId(), (int)_data->GetNodeId(), _data->GetValueID(), false);

	NodeInfo* nodeInfo = ZNode::getNodeInfo(_data);
	// Update LastSeen and DeviceState
	if (nodeInfo != NULL){
		nodeInfo->m_LastSeen = time(NULL);
		nodeInfo->m_DeviceState = DZType_Alive;
	}

	// Check if zwcfg*xml has been written 3600+ sec, then flush to disk
	m_structCtrl* ctrl = DomoZWave_GetControllerInfo((int)_data->GetHomeId());
	if ( ctrl->m_lastWriteXML > 0 ){
		double seconds;
		seconds = difftime( time( NULL ), ctrl->m_lastWriteXML );

		if ( seconds > 3600 ){
			Manager::Get()->WriteConfig((int)_data->GetHomeId());
			DomoZWave_WriteLog(LogLevel_Debug, true, "DomoZWave_WriteConfig: HomeId=%d (%.f seconds)", (int)_data->GetHomeId(), seconds);
			ctrl->m_lastWriteXML = time(NULL);
		}
	}

	DomoZWave_callValueCallback(_data);
}

void ZNode::refreshedValue(Notification const* _data){

}

void ZNode::typeGroup(Notification const* _data){

}

void ZNode::controllerReady(Notification const* _data){
	DomoZWave_RPC_DriverReady(_data->GetHomeId(), _data->GetNodeId());
}

m_structCtrl* ZNode::getControllerInfo(uint32 const homeId){
	return DomoZWave_GetControllerInfo(homeId);
}

void ZNode::updateNodeProtocolInfo(uint32 const homeId, uint8 const nodeId){
	DomoZWave_RPC_NodeProtocolInfo((int)homeId, (int)nodeId);
}

void ZNode::updateNodeEvent(Notification const* _data){
	// Event caused by basic set or hail
	DomoZWave_RPC_NodeEvent((int)_data->GetHomeId(), (int)_data->GetNodeId(), _data->GetValueID(), (int)_data->GetEvent());
	NodeInfo* nodeInfo = DomoZWave_GetNodeInfo(_data);
	if(nodeInfo != NULL){
		nodeInfo->m_LastSeen = time(NULL);
		nodeInfo->m_DeviceState = DZType_Alive;
	}
}

void ZNode::allNodeQueriedSomeDead(Notification const* _data){
	m_structCtrl* ctrl = DomoZWave_GetControllerInfo((int)_data->GetHomeId());

	if(_data->GetType() == Notification::Type_AllNodesQueried ) DomoZWave_WriteLog( LogLevel_Debug, true, "AllNodesQueried: HomeId=%d", (int)_data->GetHomeId());
	if(_data->GetType() == Notification::Type_AwakeNodesQueried ) DomoZWave_WriteLog( LogLevel_Debug, true, "AwakeNodesQueried: HomeId=%d", (int)_data->GetHomeId());
	if(_data->GetType() == Notification::Type_AllNodesQueriedSomeDead ) DomoZWave_WriteLog( LogLevel_Debug, true, "AllNodesQueriedSomeDead: HomeId=%d", (int)_data->GetHomeId());

	if(ctrl->m_controllerAllQueried == 0){
		// Write zwcfg*xml file
		Manager::Get()->WriteConfig((int)_data->GetHomeId());

		// The zwcfg*xml is written, save the current time
		ctrl->m_lastWriteXML = time(NULL);

	}else{
		// If we got 2 or more a AllQueried, then there is something really wrong somewhere
		if ( ctrl->m_controllerAllQueried > 1 ) {
			DomoZWave_WriteLog( LogLevel_Error, true, "ERROR: AllNodesQueried happened %d times (max should be 2)", ctrl->m_controllerAllQueried );
		}
	}
	ctrl->m_controllerAllQueried++;
}

void ZNode::allNodeQueried(Notification const* _data){
	list<m_structCtrl*>& g_allControllers = DomoZWave_GetGControllers();
	for(list<m_structCtrl*>::iterator it = g_allControllers.begin(); it != g_allControllers.end(); ++it){
		uint32 homeId = (*it)->m_homeId;
		DomoZWave_WriteConfig(homeId);
		(*it)->m_lastWriteXML = time(NULL);
	}
	Log::Write(LogLevel_Info, "ZNode::allNodeQueried(): calling");
}

void ZNode::messageComplete(Notification const* _data){
	NodeInfo* nodeInfo = DomoZWave_GetNodeInfo(_data);
	if (nodeInfo != NULL){
		nodeInfo->m_LastSeen = time(NULL);
		nodeInfo->m_DeviceState = DZType_Alive;
	}
}

void ZNode::messageAwake(Notification const* _data){
	NodeInfo* nodeInfo = DomoZWave_GetNodeInfo(_data);
	if (nodeInfo != NULL){
		nodeInfo->m_LastSeen = time(NULL);
		nodeInfo->m_DeviceState = DZType_Awake;
	}
}

void ZNode::messageAlive(Notification const* _data){
	NodeInfo* nodeInfo = DomoZWave_GetNodeInfo(_data);
	if (nodeInfo != NULL){
		nodeInfo->m_LastSeen = time(NULL);
		nodeInfo->m_DeviceState = DZType_Alive;
	}
}


