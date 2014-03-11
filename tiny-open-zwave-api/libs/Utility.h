/*
 * Utility.h
 *
 *  Created on: Oct 25, 2013
 *      Author: vassik
 */

#ifndef UTILITY_H_
#define UTILITY_H_

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


using namespace OpenZWave;

	//-------------------------------------------------------------------------
	//Structures for a valueID callback
	//-------------------------------------------------------------------------

	class Device;

	typedef void (*pvfCallback)(Device *_device, Notification const* _data);

	struct ValueCallback {
		pvfCallback fn_callback;
		Device *fn_device;

		ValueCallback(pvfCallback _callback, Device *_device):
			fn_callback(_callback),
			fn_device(_device){
		};

		~ValueCallback();
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

	class NullValueID {
		public:
			static ValueID* nullValueID;

		public:
			static const uint32 home_id = 0;
			static const uint8 node_id = 0;
			static const uint8 command_class = 0;
			static const uint8 instance = 0;
			static const uint8 index = 0;

			static bool IsNull(ValueID valueID);
			static ValueID GetValue();
			static ValueID* GreateInstance();
			static void Destroy();
	};

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

	ValueID findValueID(list<ValueID> values, uint8 command_class, uint8 instance, uint8 index);

#endif /* UTILITY_H_ */
