#pragma once
#include "configs.h"
#include "Sensor.h"

class Slave
{
public:
	Slave();
	~Slave();
	void init();
	vector<char> getData();
private:
	list<Sensor *>sensors;
};

