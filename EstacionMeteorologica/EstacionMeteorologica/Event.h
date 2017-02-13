#pragma once

#include "configs.h"
typedef enum {PING,QUIT}ev_type;

class Event{
public:
	Event(ev_type ID) { this->ID=ID; };
	ev_type type() { return ID; };
private:
	ev_type ID;
};