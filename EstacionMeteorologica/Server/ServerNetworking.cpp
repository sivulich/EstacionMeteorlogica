#include "ServerNetworking.h"



ServerNetworking::ServerNetworking()
{
	mosq.connect(BROKER);

	mosq.subscribe("Welcome");
	mosq.subscribe("Goodbye");
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
		}
		if (topic == "Goodbye")
		{
			string name;
			for (auto c : message)
				name.push_back(c);
			slaves.erase(find(slaves.begin(), slaves.end(), name));
			sensorLists.erase(name);
		}
		if (needList.size() > 0)
		{
			list<string> toDel;
			for (auto& n : needList)
			{
				if (topic == "Slaves/" + n + "/List")
				{
					parseList(n, message);
					toDel.push_back(n);
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
