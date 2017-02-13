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
vector<char>
Slave::getData()
{
	vector<char> data;
	for (auto& sens : sensors)
	{
		//sens->getData(data);		//each sensor attach its information to the vector as describe in the protocol
	}
	return data;
}