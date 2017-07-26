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
	void setType(uint8_t t) { data_type = t };
	void setNumber(uint8_t number);
	uint8_t getNumber();
	uint8_t getActive() { return active; };
	string getName() { return name; };
	void setName(const string& s) { name = s; };
	void setData(const vector<uint8_t> d) { data = d; };
	void setActive(bool b) { active = b; };
protected:
	string name;
	uint8_t sensor_number;
	uint8_t data_type;
	uint8_t active;
	vector<uint8_t> data;
};

