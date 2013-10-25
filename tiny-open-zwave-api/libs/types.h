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

	class ZValue {
	  friend class ZNode;

	 public:
	  ZValue(ValueID _id);
	  ~ZValue();
	  ValueID getId();
	 private:
	  ValueID id;
	};

	class ZNode {
		public:
			ZNode(int32 const _node_id);
			~ZNode();
			static void Destroy();

		private:
			static int32 nodecount;
			int32 node_id;
			vector<ZValue*> values;

		public:
			static int32 getNodeCount();
			static ZNode* getNode(int32 const _node_id);
			void dropZValueAt(uint8 n);
			void dropZValue(ValueID id);
			void addZValue(ValueID id);
			int32 getValueCount();
			ZValue *getValueAt(uint8 n);
			int32 getNodeId();

			//delete this
			vector<ZValue*> getValueValues();
	};

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

	// Define serialport string, we require the serialport if we want to stop the
	// Open Z-Wave library properly
	list<string> serialPortName;

	///////////////////////////////////////////////////////////////////////////////
	// Basic Command Class Mapping
	///////////////////////////////////////////////////////////////////////////////

	// Define map/hash to store COMMAND_CLASS_BASIC to other COMMAND_CLASS mapping
	// This prevents multi ValueChanged events for a single event
	// NOTE: This information is known in the Open Z-Wave library, but not accessible
	//       for us. Maybe in the future this is possible?
	std::map<string, int> MapCommandClassBasic;


	static list<m_structCtrl*> g_allControllers;


	///////////////////////////////////////////////////////////////////////////////
	// Structure of internal Open Z-Wave node information
	///////////////////////////////////////////////////////////////////////////////

	static list<NodeInfo*> g_nodes;


#endif /* TYPES_H_ */
