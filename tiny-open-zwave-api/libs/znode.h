/*
 * znode.h
 *
 *  Created on: Oct 19, 2013
 *      Author: vassik
 */

#ifndef ZNODE_H_
#define ZNODE_H_

#include "../Api.h"

using namespace TinyOpenZWaveApi;


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

	private:
		static int32 nodecount;
		int32 node_id;
		vector<ZValue*> values;

	public:
		static int32 getNodeCount();
		void dropZValueAt(uint8 n);
		void addZValue(ValueID id);
		int32 getValueCount();
		ZValue *getValueAt(uint8 n);
};


#endif /* ZNODE_H_ */
