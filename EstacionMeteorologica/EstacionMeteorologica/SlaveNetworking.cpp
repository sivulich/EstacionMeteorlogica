#include "SlaveNetworking.h"
#include "configs.h"
#include "fstream"

SlaveNetworking::SlaveNetworking()
{

}

SlaveNetworking::~SlaveNetworking()
{
	if (ev != nullptr) delete ev;
}

void
SlaveNetworking::init()
{
	cout << "Initializing networking..." << endl;
}

bool
SlaveNetworking::hayEvento()
{
	char c = getchar();
	if (c == 'P')
	{
		Event * ev = new Event(PING);
		this->ev = ev;
		return true;
	}
	else if(c == 'Q')
	{
		Event * ev = new Event(QUIT);
		this->ev = ev;
		return true;
	}
	return false;
}

Event
SlaveNetworking::getEvent()
{
	return *ev;
}

void
SlaveNetworking::sendConnectAck()
{
	cout << "Sending ACK" << endl;
}

void
SlaveNetworking::sendData(vector<char>& data)
{
	cout << "Sending data" << endl;
}

bool
SlaveNetworking::sendSerial()
{
	bool retVal = false;
	//packetCode type;
	//clear();
	//type = PING_RESPONSE;
	vector<char> tempData;
	unsigned int tempSize = 0;
	//finding serial number..
	std::ifstream serialFile("/proc/cpuinfo", std::ifstream::in);
	if (serialFile.is_open())
	{
		std::string temp, serialNum;
		while (std::getline(serialFile, temp))		//reading the file
		{
			if (temp.substr(0, 6) == "Serial")		//looking for "Serial"
			{
				serialNum = temp.substr(18, 16);	//found it!!
				break;
			}
		}
		if (serialNum.size() != 0)					//check if the serial number was found
		{
			//creating packet..
			//memcpy(&tempData[tempSize], serialNum.c_str(), serialNum.size());
			//tempSize += serialNum.size();
			//tempData[tempSize++] = numberOfSensors;
			//retVal = createNewPacket(type, tempData, size);
			cout << serialNum << endl;
		}
		serialFile.close();
	}
	return retVal;
}

void
SlaveNetworking::sendStatus()
{
	cout << "Sending status" << endl;
}

void
SlaveNetworking::getUpdate()
{
	cout << "getting update" << endl;
}

void
SlaveNetworking::sendSensorList(list<Sensor*>& mySensors)
{
	cout << "Sending sensor list" << endl;
}