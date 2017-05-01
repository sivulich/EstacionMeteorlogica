#pragma once
#include "configs.h"
#include "Sensor.h"

class Slave
{
public:
	Slave();
	~Slave();
	void init();
	vector<Sensor*> getSensors();
private:
	vector<Sensor *>sensors;
};

