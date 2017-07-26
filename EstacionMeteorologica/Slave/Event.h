#pragma once

#include "configs.h"
typedef enum {ERROR=0,DATA_REQUEST,GET_STATUS, RESET_SLAVE,EMERGENCY_SHUTDOWN,REQUEST_SENSOR_LIST,PING}ev_type;

class Event{
public:
	Event() { this->ID = ERROR; };
	Event(ev_type ID) { this->ID=ID; };
	ev_type type() { return ID; };
private:
	ev_type ID;
};