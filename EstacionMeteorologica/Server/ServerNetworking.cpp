#include "ServerNetworking.h"



ServerNetworking::ServerNetworking()
{
	mosq.connect(BROKER);

	mosq.subscribe("Welcome");
	mosq.subscribe("Goodbye");
	vector<uint8_t> m(1);
	m[0] = 'P';
	mosq.publish("Control", m, false);
	cout << "Server Up" << endl;
}
void
ServerNetworking::parseList(string nam,vector<uint8_t> message)
{
	int i = 1;
	int n = message[0];
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
void
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
			slaves.push_back(name);
			needList.push_back(name);
			mosq.subscribe("Slaves/" + name + "/List");
			vector<uint8_t> m(1);
			m[0] = 'S';
			mosq.publish("Slaves/" + name + "/Control", m, false);
			cout << "Slave " << name << " conected" << endl;
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
		
	}
}

ServerNetworking::~ServerNetworking()
{
	mosq.close();
}
