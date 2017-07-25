#pragma once
#include "Sensor.h"
#include "Event.h"
#include "mosquitto.hpp"

#define BROKER "192.168.1.43"

class SlaveNetworking {
public:
	SlaveNetworking();
	~SlaveNetworking();

	bool hayEvento();
	Event getEvent();
	void sendStatus(const vector<Sensor*>& mySensors, uint8_t battery, bool busy);
	void sendData(const vector<Sensor*>& mySensors);
	void getUpdate();
	void sendSensorList(const vector<Sensor*>& mySensors);
	bool publish(const string& subTopic, const vector<uint8_t>& message);
private:
	Event ev;
	uint16_t myId, toId;
	uint32_t serverIp;
	Mosquitto mosq;
	string serial;
};
