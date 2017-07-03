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
	uint8_t getBattery() { return battery; };
	bool getBusy() { return busy; };
private:
	vector<Sensor *>sensors;
	bool onBattery;
	bool busy;
	uint8_t battery;
};

