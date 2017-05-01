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
	vector<uint8_t> packet;
	packet.push_back(myId);
	packet.push_back(toId);
	packet.push_back(uint8_t(CONNECTION_ACK));
	packet.push_back(0);
	sendPacket(packet);
}

void
SlaveNetworking::sendData(vector<Sensor*>& mySensors)
{
	cout << "Sending data" << endl;
	vector<uint8_t> packet;
	int nOf = 0;
	packet.push_back(myId);
	packet.push_back(toId);
	packet.push_back(uint8_t(DATA));
	for (auto& sen : mySensors)
	{
		if (sen->getActive() == 1)
		{
			nOf++;
			packet.push_back(sen->getNumber());
			packet.push_back(0);
			packet.push_back(sen->getType());
			packet.insert(packet.end(),sen->getData().begin(),sen->getData().end());
		}
	}
	packet.insert(packet.begin()+3, nOf);
	packet.push_back(0);
	sendPacket(packet);
}

bool
SlaveNetworking::sendPingResponse(vector<Sensor*> sensors)
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
			vector<uint8_t> packet;
			packet.push_back(myId);
			packet.push_back(toId);
			packet.push_back(uint8_t(PING_RESPONSE));
			packet.insert(packet.end(), serialNum.begin(), serialNum.end());
			packet.push_back(sensors.size());
			packet.push_back(0);
			sendPacket(packet);
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
SlaveNetworking::sendSensorList(vector<Sensor*>& mySensors)
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