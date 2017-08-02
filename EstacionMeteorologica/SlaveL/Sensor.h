#pragma once
#include "configs.h"

enum { INT = 1, LONG, LONG_LONG, UINT, LONG_UINT, LONG_LONG_UINT, FLOAT, DOUBLE };
class Sensor
{
public:
	Sensor();
	virtual ~Sensor();
	virtual vector<uint8_t> getData();
	virtual bool tryUpdateData();
	uint8_t getType();
	uint8_t getActive();
	string getName();
protected:
	string name;
	uint8_t sensor_number;
	uint8_t data_type;
	uint8_t active;
	vector<uint8_t> data;
};


