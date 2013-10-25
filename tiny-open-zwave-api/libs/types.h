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


#endif /* TYPES_H_ */
