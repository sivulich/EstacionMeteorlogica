#pragma once
#include "configs.h"

class Sensor
{
public:
	Sensor();
	virtual ~Sensor();

	virtual	vector<uint8_t> getData() = 0;
	uint8_t getType();
	void setNumber(uint8_t number);
	uint8_t getNumber();
	uint8_t getActive() { return active; };
	string getName() { return name; };
	void setName(string& s) { name = s; };
protected:
	string name;
	uint8_t sensor_number;
	uint8_t data_type;
	uint8_t active;


};

