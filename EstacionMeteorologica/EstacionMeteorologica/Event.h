#pragma once

#include "configs.h"

class Event{
public:
	Event(int ID) { this->ID=ID; };
	int type() { return ID; };
private:
	int ID;
};