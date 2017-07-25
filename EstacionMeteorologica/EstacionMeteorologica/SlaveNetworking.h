#pragma once
#include "Sensor.h"
#include "Event.h"
#include "mosquitto.hpp"

class SlaveNetworking {
public:
	SlaveNetworking();
	~SlaveNetworking();
	void init();

	bool hayEvento();
	Event getEvent();
	void setID(uint16_t id);
	bool sendPingResponse(const vector<Sensor*> sensors);
	void sendConnectAck();
	void sendStatus(const vector<Sensor*>& mySensors, uint8_t battery, bool busy);
	void sendData(const vector<Sensor*>& mySensors);
	void getUpdate();
	void sendSensorList(const vector<Sensor*>& mySensors);
	bool publish(const string& subTopic, const vector<uint8_t>& message);
private:
	//bool sendPacket(vector<uint8_t>& data);
	Event ev;
	uint16_t myId, toId;
	uint32_t serverIp;
	Mosquitto mosq;
	string serial;
};
