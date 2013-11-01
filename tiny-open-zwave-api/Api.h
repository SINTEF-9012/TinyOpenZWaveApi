/*
 * Api.h
 *
 *  Created on: Oct 17, 2013
 *      Author: vassik
 */

#ifndef API_H_
#define API_H_

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

#include "libs/Utility.h"


using namespace OpenZWave;

namespace TinyOpenZWaveApi{
	using namespace std;

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
};


#endif /* API_H_ */
