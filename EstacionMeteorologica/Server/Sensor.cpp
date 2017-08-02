#include "Sensor.h"


Sensor::Sensor()
{
}


Sensor::~Sensor()
{
}

uint8_t
Sensor::getType()
{
	return this->data_type;
}

uint8_t Sensor::getActive() { return active; };
string Sensor::getName() { return name; };