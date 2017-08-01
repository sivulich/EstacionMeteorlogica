#pragma once
#include "configs.h"

enum {INT=1,LONG,LONG_LONG,UINT,LONG_UINT,LONG_LONG_UINT,FLOAT,DOUBLE};
class Sensor
{
public:
	Sensor();
	virtual ~Sensor();
	vector<uint8_t> getData() { return data; };
	uint8_t getType();
	uint8_t getActive() { return active; };
	string getName() { return name; };
protected:
	string name;
	uint8_t sensor_number;
	uint8_t data_type;
	uint8_t active;
	vector<uint8_t> data;
};

