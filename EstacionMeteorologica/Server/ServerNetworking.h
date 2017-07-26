#pragma once
#include "mosquitto.hpp"
#include "configs.h"
#include "Sensor.h"
#define BROKER "192.168.1.41"

class ServerNetworking
{
public:
	ServerNetworking();
	vector<string> getSlaves() { return slaves; };
	vector<Sensor> getSlaveList(string s) { if (sensorLists.find(s) != sensorLists.end()) return sensorLists[s]; return vector<Sensor>(); };
	void sendDataReq(const string name="");
	void sendStatusReq(const string name = "");
	void sendEmergencyShutdown(const string name = "");
	void sendReset(const string name = "");
	void parseList(string name, vector<uint8_t> message);
	bool handleEvents();
	~ServerNetworking();
private:
	Mosquitto mosq;
	vector<string> slaves;
	map<string, vector<Sensor>> sensorLists;
	list<string> needList;
};

