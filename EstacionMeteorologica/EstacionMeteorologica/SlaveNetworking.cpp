#include "SlaveNetworking.h"
#include "configs.h"
#include "fstream"

SlaveNetworking::SlaveNetworking()
{

}

SlaveNetworking::~SlaveNetworking()
{
	cout << "Destroying evet.." << endl;
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
	bool retVal = true;
	char c = getchar();
	Event * ev;
	switch (c)
	{
	case 'P':
		ev = new Event(PING_BROADCAST);
		this->ev = ev;
		break;
	case 'E':
		ev = new Event(EMERGENCY_SHUTDOWN);
		this->ev = ev;
		break;
	case 'C':
		ev = new Event(CONNECT_TO_SLAVE);
		this->ev = ev;
		break;
	default:
		retVal = false;
		break;
	}
	return retVal;
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
SlaveNetworking::sendData(list<Sensor*>& mySensors)
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
	vector<uint8_t> data;
	data.reserve(5 + 1 + 53 * mySensors.size() +1); // 5 header + 1 for number of sensors + 53 *n maxsize for a sensor in the list + 1 the ending null char
	data.push_back(myId);
	data.push_back(toId);
	data.push_back(uint8_t(SENSOR_LIST));
	for (auto& sen : mySensors)
	{
		for (auto& c : sen->getName())
			data.push_back(uint8_t(c));
		data.push_back(0);
		data.push_back(sen->getType());
		data.push_back(sen->getActive());
	}
	data.push_back(0);
	sendPacket(data);
}