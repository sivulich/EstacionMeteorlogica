#pragma once
#include "mosquitto.hpp"
#include "configs.h"
#include "RemoteSensor.h"
#define BROKER "192.168.1.33"

class ServerNetworking
{
public:
	ServerNetworking();
	vector<string> getSlaves() { return slaves; };
	vector<RemoteSensor> getSlaveList(string s) { if (sensorLists.find(s) != sensorLists.end()) return sensorLists[s]; return vector<RemoteSensor>(); };
	void sendDataReq(const string name="");
	void sendStatusReq(const string name = "");
	void sendEmergencyShutdown(const string name = "");
	void sendListReq(const string name = "");
	void sendReset(const string name = "");
	void parseList(string name, vector<uint8_t> message);
	bool handleEvents();
	~ServerNetworking();
private:
	Mosquitto mosq;
	vector<string> slaves;
	map<string, vector<RemoteSensor>> sensorLists;
	list<string> needList;
};

