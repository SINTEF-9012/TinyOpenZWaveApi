/*
 * types.h
 *
 *  Created on: Oct 25, 2013
 *      Author: vassik
 */

#ifndef TYPES_H_
#define TYPES_H_

#include "Driver.h"
#include "Notification.h"
#include "ValueStore.h"
#include "Value.h"
#include "ValueBool.h"
#include "ValueByte.h"
#include "ValueDecimal.h"
#include "ValueInt.h"
#include "ValueList.h"
#include "ValueShort.h"
#include "ValueString.h"

using namespace OpenZWave;

	//-----------------------------------------------------------------------------
	// Internal enum types
	//-----------------------------------------------------------------------------

	enum TypeNodeState
	{
		DZType_Unknown = 0,
		DZType_Alive,
		DZType_Dead,
		DZType_Sleep,
		DZType_Awake,
		DZType_Timeout
	};


	///////////////////////////////////////////////////////////////////////////////
	// Controller/homeId information, includes multiple controller support
	///////////////////////////////////////////////////////////////////////////////

	typedef struct
	{
		uint8		m_command;
		uint8		m_nodeId;
		time_t		m_time;
	} m_cmdItem;


	typedef struct
	{
		uint32		m_homeId;
		uint8		m_controllerId;
		uint32		m_controllerAllQueried;
		bool		m_controllerBusy;
		uint8		m_nodeId;
		list<m_cmdItem>	m_cmd;
		uint8		m_userCodeEnrollNode;
		time_t		m_userCodeEnrollTime;
		time_t		m_lastWriteXML;
	} m_structCtrl;

	// To enable polling we need a nodeId->ValueID mapping. I asked on the mailing
	// list and the only suggestion I got was to store them off when the values are
	// added. So we store a list of structs to hold this mapping.

	typedef struct
	{
		uint32		m_homeId;
		uint8		m_nodeId;
		uint8		basicmapping;
		uint8		instancecount;
		string		commandclass;
		time_t		m_LastSeen;
		TypeNodeState	m_DeviceState;
		std::map<int,string> instancecommandclass;
		std::map<int,string> instanceLabel;
		list<ValueID>	m_values;
	} NodeInfo;

	class ZNode {
		public:
			static int32 getNodeCount();
			static ZNode* getNode(int32 const _node_id);
			static NodeInfo* getNodeInfo(Notification const* _data);
			static void addNode(Notification const* _data);
			static void addValue(Notification const* _data);
			static void removeNode(Notification const* _data);
			static void removeValue(Notification const* _data);
			static void changeValue(Notification const* _data);
			static void controllerReady(Notification const* _data);
			static m_structCtrl* getControllerInfo(uint32 const homeId);
	};

#endif /* TYPES_H_ */
