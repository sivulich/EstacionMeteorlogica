#include "Slave.h"
#include "temp_sensor.h"


Slave::Slave()
{
	onBattery = false;
	battery = 101;
	/*Testing*/
	Sensor* s1, *s2;
	s1 = new Sensor;
	s2 = new Sensor;
	s1->setName("Sensor 1");
	s1->setType(INT);
	s1->setActive(false);
	s2->setName("Sensor 2");
	s2->setType(LONG);
	s2->setActive(false);
	sensors.push_back(s1);
	sensors.push_back(s2);
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