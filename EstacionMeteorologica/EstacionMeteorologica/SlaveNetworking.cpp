#include "SlaveNetworking.h"
#include "configs.h"
#include "fstream"

SlaveNetworking::SlaveNetworking()
{
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
			serial = serialNum;
		}
		serialFile.close();
	}
	mosq.connect("192.168.1.43");
	mosq.subscribe("Control");
	mosq.subscribe("Slaves/" + serial + "/Control");
	vector<uint8_t> ser;
	ser.insert(ser.end(), serial.begin(), serial.end());
	mosq.publish("Welcome", ser);
}

SlaveNetworking::~SlaveNetworking()
{
	vector<uint8_t> ser;
	ser.insert(ser.end(), serial.begin(), serial.end());
	mosq.publish("Goodbye", ser);
	mosq.close();
	mosq.cleanup_library();
}

bool
SlaveNetworking::publish(const string& subTopic, const vector<uint8_t>& message)
{
	mosq.publish("Slaves/" + serial +"/"+ subTopic, message);
	return true;
}

void
SlaveNetworking::init()
{
	cout << "Initializing networking..." << endl;
	
}

bool
SlaveNetworking::hayEvento()
{
	mosq.loop();
	bool retval = false;
	if (mosq.newEvent())
	{
		vector<uint8_t> data=mosq.getMessage();
		uint8_t opcode = data[0];
		switch (opcode)
		{
			case 'D':
				ev = DATA_REQUEST;
				retval = true;
				break;
			case 'S':
				ev = REQUEST_SENSOR_LIST;
				retval = true;
				break;
			case 'E':
				ev = EMERGENCY_SHUTDOWN;
				retval = true;
				break;
			case 'T':
				ev = GET_STATUS;
				retval = true;
				break;
			case 'R':
				ev = RESET_SLAVE;
				retval = true;
				break;
			default:
				break;
		}
			
	}
	
	return retval;
}

Event
SlaveNetworking::getEvent()
{
	return ev;
}



void
SlaveNetworking::sendData(const vector<Sensor*>& mySensors)
{
	cout << "Sending data" << endl;
	uint8_t active=0;
	for (auto& sen : mySensors)
	{
		if (sen->getActive() == 1)
		{
			active++;
			publish(sen->getName(), sen->getData());
		}
	}
	vector<uint8_t> a(1);
	a[0] = active;
	publish("Active", a);
	
}

void
SlaveNetworking::sendStatus(const vector<Sensor*>& mySensors,uint8_t battery,bool busy)
{
	cout << "Sending status" << endl;
	vector<uint8_t> packet;
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
	publish("Status", packet);
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
	for (auto& sen : mySensors)
	{
		for (auto& c : sen->getName())
			packet.push_back(uint8_t(c));
		packet.push_back(0);
		packet.push_back(sen->getType());
		packet.push_back(sen->getActive());
	}
	packet.push_back(0);
	publish("List", packet);
	
}