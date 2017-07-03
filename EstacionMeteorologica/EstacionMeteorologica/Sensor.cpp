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

void
Sensor::setNumber(uint8_t number)
{
	this->sensor_number = number;
}

uint8_t
Sensor::getNumber()
{
	return this->sensor_number;
}