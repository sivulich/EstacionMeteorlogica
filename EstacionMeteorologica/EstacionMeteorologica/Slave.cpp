#include "Slave.h"
#include "temp_sensor.h"


Slave::Slave()
{
	onBattery = false;
	battery = 101;
	sensors.push_back(new temp_sensor);
	sensors[0]->setNumber(0);
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