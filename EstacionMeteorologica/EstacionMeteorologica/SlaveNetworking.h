#pragma once
#include "Sensor.h"
#include "Event.h"

enum { DATA = 11, STATUS, RESET_ACK, SOFTWARE_ACK, EMERGENCY_SHUTDOWN_ACK, CONECTON_ACK, PING_RESPONSE, SENSOR_LIST };

class SlaveNetworking {
public:
	SlaveNetworking();
	~SlaveNetworking();
	void init();

	bool hayEvento();
	Event getEvent();
	bool sendPingResponse(vector<Sensor*> sensors);
	void sendConnectAck();
	void sendStatus(vector<Sensor*>& mySensors, uint8_t battery, bool busy);
	void sendData(vector<Sensor*>& mySensors);
	void getUpdate();
	void sendSensorList(vector<Sensor*>& mySensors);
	int sendPacket(vector<uint8_t>& packet);
private:
	//bool sendPacket(vector<uint8_t>& data);
	Event * ev;
	uint16_t myId, toId;
	uint32_t serverIp;
};
