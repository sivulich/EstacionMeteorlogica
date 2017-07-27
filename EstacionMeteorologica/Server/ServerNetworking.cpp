#include "ServerNetworking.h"



ServerNetworking::ServerNetworking()
{
	mosq.connect(BROKER);

	mosq.subscribe("Welcome");
	mosq.subscribe("Goodbye");
	mosq.subscribe("Server/Control");
	vector<uint8_t> m(1);
	m[0] = 'P';
	mosq.publish("Control", m, false);
	cout << "Server Up" << endl;
}
void
ServerNetworking::parseList(string nam,vector<uint8_t> message)
{
	unsigned int i = 0;
	bool name=true,type=false,active=false;
	Sensor sen;
	string sensorName;
	sensorLists[nam].clear();
	while (i < message.size())
	{
		if (name)
		{
			if (message[i] != 0)
				sensorName.push_back(message[i]);
			else
			{
				sen.setName(sensorName);
				sensorName.clear();
				type = true;
				name = false;
			}
		}
		else if (type)
		{
			sen.setType(message[i]);
			type = false;
			active = true;
		}
		else if (active)
		{
			sen.setActive((bool)message[i]);
			
			sensorLists[nam].push_back(sen);
			name = true;
			active = false;
		}
		i++;
	}
}
bool
ServerNetworking::handleEvents()
{
	mosq.loop();
	if (mosq.newEvent())
	{
		string topic = mosq.getTopic();
		vector<uint8_t> message = mosq.getMessage();
		if (topic == "Welcome")
		{
			string name;
			for (auto c : message)
				name.push_back(c);
			if (find(slaves.begin(), slaves.end(), name) != slaves.end())
			{
				vector<uint8_t> m(1);
				m[0] = 'Q';
				mosq.publish("Slaves/" + name + "/Control", m, false);
				cout << "Duplicate of " << name << " tried to conect, kicking duplicates" << endl;
			}
			else
			{
				slaves.push_back(name);
				needList.push_back(name);
				mosq.subscribe("Slaves/" + name + "/List");
				vector<uint8_t> m(1);
				m[0] = 'L';
				mosq.publish("Slaves/" + name + "/Control", m, false);
				cout << "Slave " << name << " conected" << endl;
			}
			
		}
		if (topic == "Goodbye")
		{
			string name;
			for (auto c : message)
				name.push_back(c);
			slaves.erase(find(slaves.begin(), slaves.end(), name));
			sensorLists.erase(name);
			cout << "Slave " << name << " disconected" << endl;
		}
		if (needList.size() > 0)
		{
			list<string> toDel;
			for (auto& n : needList)
			{
				if (topic == "Slaves/" + n + "/List")
				{
					parseList(n, message);
					cout << "Slave " << n << " sent his sensor list:" << endl;
					for (auto& s : sensorLists[n])
						cout << "- " << s.getName() << endl;
					toDel.push_back(n);
					mosq.unsubscribe("Slaves/" + n + "/List");
				}
			}
			for (auto& n : toDel)
				needList.erase(find(needList.begin(), needList.end(), n));
		}
		if (topic == "Server/Control")
		{
			string comm;
			for (auto c : message)
				comm.push_back(c);
			if (comm == "exit")
				return true;
		}
		
	}
	return false;
}
void
ServerNetworking::sendDataReq(const string name)
{
	vector<uint8_t> m(1);
	m[0] = 'D';
	if (name == "")
		mosq.publish("Control", m, false);
	else
		mosq.publish("Slaves/" + name + "/Control", m, false);
		
}
void
ServerNetworking::sendEmergencyShutdown(const string name)
{
	vector<uint8_t> m(1);
	m[0] = 'E';
	if (name == "")
		mosq.publish("Control", m, false);
	else
		mosq.publish("Slaves/" + name + "/Control", m, false);
}
void
ServerNetworking::sendStatusReq(const string name)
{
	vector<uint8_t> m(1);
	m[0] = 'S';
	if (name == "")
		mosq.publish("Control", m, false);
	else
		mosq.publish("Slaves/" + name + "/Control", m, false);
}
void
ServerNetworking::sendReset(const string name)
{
	vector<uint8_t> m(1);
	m[0] = 'R';
	if (name == "")
		mosq.publish("Control", m, false);
	else
		mosq.publish("Slaves/" + name + "/Control", m, false);
}
ServerNetworking::~ServerNetworking()
{
	mosq.close();
}
