#include "SlaveNetworking.h"
#include "configs.h"
#include "fstream"

SlaveNetworking::SlaveNetworking()
{
	serverIp = 0; //Agregar el ip del server o algo que lo busque!
}

SlaveNetworking::~SlaveNetworking()
{
	cout << "Destroying evet.." << endl;
	if (ev != nullptr) delete ev;
}

int
SlaveNetworking::sendPacket(const vector<uint8_t>& packet)
{
/*	ofstream out("packet.pkt");
	for (auto& b : packet)
		out << b;
	out.close();
	string command = string("python sendPacket.py ") + to_string(serverIp);
	return system(command.c_str());*/
	cout << "Sending packet with this info:" << endl;
	for (auto& u : packet)
		cout << bitset<8>(u) << " ";
	cout << endl << endl;
	return 0;
}

void
SlaveNetworking::init()
{
	cout << "Initializing networking..." << endl;
}

bool
SlaveNetworking::hayEvento()
{
	/*
	system("python recievePacket.py");
	ifstream in("packet.pkt");
	uint8_t temp='a';
	vector<uint8_t> packet;
	while(temp!=EOF)
	{
		in.read(*temp,1);
		packet.push_back(temp);
	}
	*/
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
		//ev = new Event(EMERGENCY_SHUTDOWN);
		this->ev = ev;
		break;
	case 'C':
		ev = new Event(CONNECT_TO_SLAVE);
		this->ev = ev;
		break;
	case 'S':
		ev = new Event(GET_STATUS);
		this->ev = ev;
		break;
	case 'D':
		ev = new Event(DATA_REQUEST);
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
	vector<uint8_t> id(2);
	*((uint16_t*)id.data()) = myId;
	packet.insert(packet.end(), id.begin(), id.end());
	*((uint16_t*)id.data()) = toId;
	packet.insert(packet.end(), id.begin(), id.end());
	packet.push_back(uint8_t(CONNECTION_ACK));
	packet.push_back(0);
	uint32_t size = packet.size();
	vector<uint8_t> s(4);
	*((uint32_t*)s.data()) = size;
	packet.insert(packet.begin(), s.begin(), s.end());
	sendPacket(packet);
}

void
SlaveNetworking::sendData(const vector<Sensor*>& mySensors)
{
	cout << "Sending data" << endl;
	vector<uint8_t> packet;
	int nOf = 0;
	vector<uint8_t> id(2);
	*((uint16_t*)id.data()) = myId;
	packet.insert(packet.end(), id.begin(), id.end());
	*((uint16_t*)id.data()) = toId;
	packet.insert(packet.end(), id.begin(), id.end());
	packet.push_back(uint8_t(DATA));
	for (auto& sen : mySensors)
	{
		if (sen->getActive() == 1)
		{
			nOf++;
			packet.push_back(sen->getNumber());
			packet.push_back(0);
			packet.push_back(sen->getType());
			vector<uint8_t> data = sen->getData();
			packet.insert(packet.end(),data.begin(),data.end());
		}
	}
	packet.insert(packet.begin()+3, nOf);
	packet.push_back(0);
	uint32_t size = packet.size();
	vector<uint8_t> s(4);
	*((uint32_t*)s.data()) = size;
	packet.insert(packet.begin(), s.begin(), s.end());
	sendPacket(packet);
}

bool
SlaveNetworking::sendPingResponse(const vector<Sensor*> sensors)
{
	bool retVal = false;
	
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
			vector<uint8_t> id(2);
			*((uint16_t*)id.data()) = myId;
			packet.insert(packet.end(), id.begin(), id.end());
			*((uint16_t*)id.data()) = toId;
			packet.insert(packet.end(), id.begin(), id.end());
			packet.push_back(uint8_t(PING_RESPONSE));
			packet.insert(packet.end(), serialNum.begin(), serialNum.end());
			packet.push_back(sensors.size());
			packet.push_back(0);
			uint32_t size = packet.size();
			vector<uint8_t> s(4);
			*((uint32_t*)s.data()) = size;
			packet.insert(packet.begin(), s.begin(), s.end());
			sendPacket(packet);
			cout << serialNum << endl;
		}
		serialFile.close();
	}
	return retVal;
}

void
SlaveNetworking::sendStatus(const vector<Sensor*>& mySensors,uint8_t battery,bool busy)
{
	cout << "Sending status" << endl;
	vector<uint8_t> packet;
	vector<uint8_t> id(2);
	*((uint16_t*)id.data()) = myId;
	packet.insert(packet.end(), id.begin(), id.end());
	*((uint16_t*)id.data()) = toId;
	packet.insert(packet.end(), id.begin(), id.end());
	packet.push_back(uint8_t(STATUS));
	packet.push_back(battery);
	packet.push_back(uint8_t(busy));
	packet.push_back(uint8_t(mySensors.size()));
	uint8_t active = 0;
	for (auto& s : mySensors)
	{
		if (s->getActive() == 1)
			active++;
	}
	packet.push_back(active);
	packet.push_back(0);
	uint32_t size = packet.size();
	vector<uint8_t> s(4);
	*((uint32_t*)s.data()) = size;
	packet.insert(packet.begin(), s.begin(), s.end());
	sendPacket(packet);
	return;
}

void
SlaveNetworking::getUpdate()
{
	cout << "getting update" << endl;
}

void
SlaveNetworking::sendSensorList(const vector<Sensor*>& mySensors)
{
	cout << "Sending sensor list" << endl;
	vector<uint8_t> packet;
	packet.reserve(5 + 1 + 53 * mySensors.size() +1); // 5 header + 1 for number of sensors + 53 *n maxsize for a sensor in the list + 1 the ending null char
	packet.push_back(myId);
	packet.push_back(toId);
	packet.push_back(uint8_t(SENSOR_LIST));
	for (auto& sen : mySensors)
	{
		for (auto& c : sen->getName())
			packet.push_back(uint8_t(c));
		packet.push_back(0);
		packet.push_back(sen->getType());
		packet.push_back(sen->getActive());
	}
	packet.push_back(0);
	uint32_t size = packet.size();
	vector<uint8_t> s(4);
	*((uint32_t*)s.data()) = size;
	packet.insert(packet.begin(), s.begin(), s.end());
	sendPacket(packet);
}