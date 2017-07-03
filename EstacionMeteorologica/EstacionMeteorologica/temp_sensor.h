#ifndef TEMP_SENSOR_H_
#define TEMP_SENSOR_H_

#include "Sensor.h"
#include "DS18B20.hpp"

class temp_sensor : public Sensor
{
public:
	temp_sensor();
	virtual	vector<uint8_t> getData();
	~temp_sensor();
private:
	DS18B20 t_sensor;
};

#endif