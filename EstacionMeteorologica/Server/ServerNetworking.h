#pragma once
#include "mosquitto.hpp"
#include "configs.h"
#include "Sensor.h"
#define BROKER "192.168.1.43"

class ServerNetworking
{
public:
	ServerNetworking();
	vector<string> getSlaves() { return slaves; };
	vector<Sensor> getSlaveList(string s) { if (sensorLists.find(s) != sensorLists.end()) return sensorLists[s]; return vector<Sensor>(); };
	void parseList(string name, vector<uint8_t> message);
	void handleEvents();
	~ServerNetworking();
private:
	Mosquitto mosq;
	vector<string> slaves;
	map<string, vector<Sensor>> sensorLists;
	list<string> needList;
};

