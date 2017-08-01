#pragma once
#include "Sensor.h"
class RemoteSensor :
	public Sensor
{
public:
	RemoteSensor();
	void setName(const string& s) { name = s; };
	void setData(const vector<uint8_t> d) { data = d; };
	vector<uint8_t> getData() { return data; };
	void setActive(bool b) { active = b; };
	void setType(uint8_t t) { data_type = t; };
	~RemoteSensor();
};

