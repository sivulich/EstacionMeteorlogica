#pragma once

#include "Event.h"


class ServerNetworking
{
public:
	ServerNetworking();
	~ServerNetworking();
	void init();

	bool hayEvento();
	Event getEvent();

	//bool sendPingResponse(vector<Sensor*> sensors);
	void sendEmptyPacket(ev_type type);
	//void sendSoftwareUpdate();
	void sendConnectToSlave();
	int sendPacket(vector<uint8_t>& packet);
private:
	Event ev;
	uint16_t myId, toId;
};

