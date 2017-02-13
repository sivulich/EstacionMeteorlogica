#pragma once
#include "Sensor.h"
#include "Event.h"

class SlaveNetworking {
public:
	SlaveNetworking();
	~SlaveNetworking();
	void init();

	bool hayEvento();
	Event getEvent();
	bool sendSerial();
	void sendConnectAck();
	void sendStatus();
	void sendData(vector<char>& data);
	void getUpdate();
	void sendSensorList(list<Sensor*>& mySensors);
private:
	Event * ev;
};
