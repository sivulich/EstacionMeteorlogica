#pragma once

#include "configs.h"
typedef enum {DATA_REQUEST = 1,GET_STATUS, RESET_SLAVE, SOFTWARE_UPDATE,EMERGENCY_SHUTDOWN,CONNECT_TO_SLAVE, PING_BROADCAST,REQUEST_SENSOR_LIST,DATA,STATUS,RESET_ACK,SOFTWARE_ACK,EMERGENCY_SHUTDOWN_ACK,CONNECTION_ACK, PING_RESPONSE,SENSOR_LIST}ev_type;

class Event{
public:
	Event(ev_type ID) { this->ID=ID; };
	ev_type type() { return ID; };
private:
	ev_type ID;
};