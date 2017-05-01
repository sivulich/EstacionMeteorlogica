#include "Slave.h"



Slave::Slave()
{
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