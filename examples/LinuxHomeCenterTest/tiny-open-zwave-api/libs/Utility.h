/*
 * Utility.h
 *
 *  Created on: Oct 25, 2013
 *      Author: vassik
 */

#ifndef UTILITY_H_
#define UTILITY_H_

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

	//-------------------------------------------------------------------------
	//the actual definition of ValueCallback is in Device.h
	//-------------------------------------------------------------------------

	struct ValueCallback;

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
		std::map<ValueID, list<ValueCallback*> > m_value_callback;
	} NodeInfo;

	class ZNode {
		public:
			static int32 GetNodeCount();
			static ZNode* GetNode(int32 const _node_id);
			static NodeInfo* GetNodeInfo(Notification const* _data);
			static void AddNode(Notification const* _data);
			static void AddValue(Notification const* _data);
			static void RemoveNode(Notification const* _data);
			static void RemoveValue(Notification const* _data);
			static void ChangeValue(Notification const* _data);
			static void ControllerReady(Notification const* _data);
			static m_structCtrl* GetControllerInfo(uint32 const homeId);
			static void UpdateNodeProtocolInfo(uint32 const homeId, uint8 const nodeId);
			static void UpdateNodeEvent(Notification const* _data);
			static void AllNodeQueriedSomeDead(Notification const* _data);
			static void AllNodeQueried(Notification const* _data);

			static void MessageComplete(Notification const* _data);
			static void MessageAwake(Notification const* _data);
			static void MessageAlive(Notification const* _data);
	};

	struct DummyValueID {
		ValueID* valueID;
		uint32 home_id;
		uint8 node_id;
		uint8 command_class;
		uint8 instance;
		uint8 index;

		DummyValueID() : home_id(0), node_id(0), command_class(0), instance(0), index(0) {
			valueID = new ValueID(home_id , node_id, ValueID::ValueGenre_Basic, command_class, instance, index ,ValueID::ValueType_Bool);
		}
	};

	//TODO: using of this structure requires the -fpermissive flag while compiling since it is not type safe
	//probably we need to look into this
	typedef void (*pthingMLCallback)(void* _instance, ...);
	struct ThingMLCallback {
		pthingMLCallback fn_callback;
		void* instance;

		ThingMLCallback(pthingMLCallback _callback, void* _instance):
			fn_callback(_callback),
			instance(_instance){
		};
	};

	const char *genreToStr(ValueID::ValueGenre value);
	ValueID::ValueGenre genreToNum(char const* value);
	const char *typeToStr(ValueID::ValueType value);
	ValueID::ValueType typeToNum(char const* value);
	const char *nodeBasicToStr(uint8 value);
	const char *cclassToStr(uint8 value);
	uint8 cclassToNum(char const *value);
	const char *controllerErrorToStr(Driver::ControllerError error);

#endif /* UTILITY_H_ */
