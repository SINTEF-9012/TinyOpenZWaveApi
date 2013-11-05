/*
 * TMLcallback.cpp
 *
 *  Created on: Nov 4, 2013
 *      Author: vassik
 */

#include "TMLcallback.h"

void ThingML_binary_switch_turned_on(){
	//thingML turnOn message here
}

void ThingML_binary_switch_turned_off(){
	//thingML turnOff message here
}

void ThingML_binary_switch_nochange(){
	//thingML nochange callback. For example, we set polling for a value,
	//the the value is not actually changed, but reported as changed...
}

void ThingML_network_ready(){
	//network ready callback, to let thingML now that we are ready to work
}



