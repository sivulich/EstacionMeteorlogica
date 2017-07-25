#include "Slave.h"
#include "temp_sensor.h"


Slave::Slave()
{
	onBattery = false;
	battery = 101;
}


Slave::~Slave()
{
}

void
Slave::init()
{
	cout << "initializing Slave..." << endl;
}

vector<Sensor*>
Slave::getSensors()
{
	return sensors;
}