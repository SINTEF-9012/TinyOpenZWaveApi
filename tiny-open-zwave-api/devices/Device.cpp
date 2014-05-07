/*
 * Device.cpp
 *
 *  Created on: Nov 1, 2013
 *      Author: vassik
 */

#include <iostream>
#include <typeinfo>

#include "openzwave/Log.h"
#include "openzwave/Node.h"

#include "TinyController.h"
#include "Device.h"
#include "../libs/DomoZWave.h"
#include "../libs/Utility.h"
#include "../observer/NodeSubject.h"


namespace TinyOpenZWaveApi {

	uint8 Device::COMMAND_CLASS = COMMAND_CLASS_NON_UNKNOWN;

	Device::Device(){
		this->DEVICE_NAME = "Device";
		this->deviceInitCallback = NULL;
		this->node = NULL;
		this->valueID = NullValueID::GreateInstance();
		this->controller = 0;
		this->nodeId = 0;
		this->instance = 0;
		this->index = 0;
		this->valueLastSeen = 0;
	}

	Device* Device::Init(TinyController* const controller, uint8 const _nodeId, uint8 const _instance, uint8 const _index) {
		this->controller = controller;
		this->nodeId = _nodeId;
		this->instance = _instance;
		this->index = _index;
		controller->addDevice(this);
		return this;
	}

	uint8 Device::getComandClass(){
		return COMMAND_CLASS;
	}

	void Device::Destroy(){
		Log::Write(LogLevel_Info, "Device::Destroy() : 0x%08x", this);
		delete this;
	}

	Device::~Device(){
		Log::Write(LogLevel_Info, "Device::~Device(): 0x%08x", this);
		for(list<ValueCallback*>::iterator it = callbacks.begin(); it != callbacks.end(); ++it)
			delete *it;
		callbacks.clear();
		delete this->valueID;
	}

	void Device::update(NodeSubject* subject){
		Log::Write(LogLevel_Info, "%s::update(): is called for the node %d 0x%08x", getDeviceName(), this->nodeId, this);
		Notification const* notification = subject->getNotification();
		if(notification->GetValueID().GetCommandClassId() != getComandClass())
			return;

		ValueID valueId = notification->GetValueID();
		switch (notification->GetType()) {
			case Notification::Type_ValueAdded:
				Log::Write(LogLevel_Info, "%s::update(): value added...", getDeviceName());
				this->setUp(subject->getNodeInfo());
				break;
			case Notification::Type_ValueChanged:
				Log::Write(LogLevel_Info, "%s::update(): value changed, calling callback...", getDeviceName());
				Device::CallValueCallback(getNodeInfo(), valueId, notification);
				break;
			case Notification::Type_ValueRemoved:
				Log::Write(LogLevel_Info, "%s::update(): value removed...", getDeviceName());
				Device::RemoveValueIDCallback(getNodeInfo(), valueId);
				*this->valueID = NullValueID::GetValue();
				break;
			default:
				Log::Write(LogLevel_Info, "%s::update(): not handled case...", getDeviceName());
				break;
		}
	}

	int Device::setUp(NodeInfo* nodeInfo){
		int result = 0;
		if(getNodeInfo() == NULL || NullValueID::IsNull(*this->valueID)){
			ValueID valueId = findValueID(nodeInfo->m_values, getComandClass(), this->instance, this->index);
			if(!NullValueID::IsNull(valueId)){
				Log::Write(LogLevel_Info, "%s::setUp(): is called for the node %d 0x%08x", getDeviceName(), this->nodeId, this);
				this->node = nodeInfo;
				*this->valueID = valueId;
			}else{
				Log::Write(LogLevel_Info, "%s::setUp(): ValueID is not known yet for"
						"Home 0x%08x Node %d Class %s Instance %d Index %d", getDeviceName(),
						controller->homeId, this->nodeId,
						getComandClass(), this->instance, this->index);
				result = 1;
			}
		}else {
			Log::Write(LogLevel_Info, "%s::setUp(): node is not NULL and valueID is already set, skipping..."
				"Value : Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s", getDeviceName(),
					controller->homeId, this->node->m_nodeId, genreToStr((*this->valueID).GetGenre()),
					cclassToStr((*this->valueID).GetCommandClassId()), (*this->valueID).GetInstance(),
					(*this->valueID).GetIndex(), typeToStr((*this->valueID).GetType()));
			result = 2;
		}
		return result;
	}

	void Device::finalizeSetUp(){
		valueLastSeen = time(NULL);
		Device::TestValueIDCallback(this->node, *this->valueID, callbacks);
		if(deviceInitCallback)
			deviceInitCallback->fn_callback(deviceInitCallback->instance);
	}

	void Device::TestValueIDCallback(NodeInfo *nodeInfo, ValueID valueID, list<ValueCallback*> callbacks){
		if(nodeInfo->m_value_callback.find(valueID) != nodeInfo->m_value_callback.end()){
			for(list<ValueCallback*>::iterator it = callbacks.begin(); it != callbacks.end(); ++it){
				bool found = false;
				list<ValueCallback*> c_list = nodeInfo->m_value_callback[valueID];
				for(list<ValueCallback*>::iterator iti = c_list.begin(); iti != c_list.end(); ++iti){
					if(*iti == *it){
						found = true;
						break;
					}
				}
				if(found == false){
					nodeInfo->m_value_callback[valueID].push_back((*it));
					Log::Write(LogLevel_Info, true, "Device::TestValueIDCallback() : Appending the callback for a value : "
							"Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
							valueID.GetHomeId(), valueID.GetNodeId(),
							genreToStr(valueID.GetGenre()), cclassToStr(valueID.GetCommandClassId()), valueID.GetInstance(),
							valueID.GetIndex(), typeToStr(valueID.GetType()));
				}
			}
		}else{
			nodeInfo->m_value_callback[valueID] = callbacks;
			Log::Write(LogLevel_Info, "Device::TestValueIDCallback() : Adding %d callbacks for a value :"
					"Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
					callbacks.size(), valueID.GetHomeId(), valueID.GetNodeId(),
					genreToStr(valueID.GetGenre()), cclassToStr(valueID.GetCommandClassId()), valueID.GetInstance(),
					valueID.GetIndex(), typeToStr(valueID.GetType()));
		}
	}

	void Device::RemoveValueIDCallback(NodeInfo *nodeInfo, ValueID valueID) {
		if(nodeInfo->m_value_callback.find(valueID) != nodeInfo->m_value_callback.end()){
			nodeInfo->m_value_callback.erase(valueID);
			Log::Write(LogLevel_Info, true, "Device::RemoveValueIDCallback() : Removing value and its callbacks : "
					"Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
					valueID.GetHomeId(), valueID.GetNodeId(),
					genreToStr(valueID.GetGenre()), cclassToStr(valueID.GetCommandClassId()), valueID.GetInstance(),
					valueID.GetIndex(), typeToStr(valueID.GetType()));
		}else{
			Log::Write(LogLevel_Info, true, "Device::RemoveValueIDCallback() : Can not find any callback for the value : "
					"Home 0x%08x Node %d Genre %s Class %s Instance %d Index %d Type %s",
					valueID.GetHomeId(), valueID.GetNodeId(),
					genreToStr(valueID.GetGenre()), cclassToStr(valueID.GetCommandClassId()), valueID.GetInstance(),
					valueID.GetIndex(), typeToStr(valueID.GetType()));
		}
	}

	void  Device::CallValueCallback(NodeInfo *nodeInfo, ValueID valueId, Notification const* notification){
		if(nodeInfo->m_value_callback.find(valueId) != nodeInfo->m_value_callback.end()){
			for(list<ValueCallback*>::iterator it = nodeInfo->m_value_callback[valueId].begin(); it != nodeInfo->m_value_callback[valueId].end(); ++it){
				Log::Write(LogLevel_Info, "Device::CallValueCallback() : calling callback for a value : "
						"Node %d Genre %s Class %s Instance %d Index %d Type %s",
						 nodeInfo->m_nodeId, genreToStr(valueId.GetGenre()), cclassToStr(valueId.GetCommandClassId()), valueId.GetInstance(),
						valueId.GetIndex(), typeToStr(valueId.GetType()));
				(*it)->fn_callback((*it)->fn_device, notification);
			}
		}else{
			Log::Write(LogLevel_Info,"Device::TestValueIDCallback() : can not find any callback for the given value");
		}
	}
}
