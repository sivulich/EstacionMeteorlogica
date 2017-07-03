#include "ServerNetworking.h"



ServerNetworking::ServerNetworking()
{
	cout << "Initializing server..." << endl;
}


ServerNetworking::~ServerNetworking()
{
}

void
ServerNetworking::init()
{
	cout << "Init" << endl;
}
int
ServerNetworking::sendPacket(vector<uint8_t>& packet)
{
	/*	ofstream out("packet.pkt");
	for (auto& b : packet)
	out << b;
	out.close();
	string command = string("python sendPacket.py ") + to_string(serverIp);
	return system(command.c_str());*/
	cout << "Sending packet with this info:" << endl;
	for (auto& u : packet)
		cout << u;
	cout << endl << endl;
	return 0;
}

void 
ServerNetworking::sendEmptyPacket(ev_type type)
{
	cout << "Sending Empty Packet" << endl;
	vector<uint8_t> packet;
	vector<uint8_t> id(2);
	*((uint16_t*)id.data()) = myId;
	packet.insert(packet.end(), id.begin(), id.end());
	*((uint16_t*)id.data()) = toId;
	packet.insert(packet.end(), id.begin(), id.end());
	packet.push_back(uint8_t(type));
	packet.push_back(0);
	uint32_t size = packet.size();
	vector<uint8_t> s(4);
	*((uint32_t*)s.data()) = size;
	packet.insert(packet.begin(), s.begin(), s.end());
	sendPacket(packet);
}

void
ServerNetworking::sendConnectToSlave()
{
	cout << "Sending Connect to Slave" << endl;
	vector<uint8_t> packet;
	//To ID and my ID
	vector<uint8_t> id(2);
	*((uint16_t*)id.data()) = myId;
	packet.insert(packet.end(), id.begin(), id.end());
	*((uint16_t*)id.data()) = toId;
	packet.insert(packet.end(), id.begin(), id.end());
	//Packet type
	packet.push_back(uint8_t(CONNECT_TO_SLAVE));
	//Data
	vector<uint8_t> data(2);
	*((uint16_t*)id.data()) = (uint16_t)101;
	packet.insert(packet.end(), data.begin(), data.end());
	packet.push_back(0);
	//Size
	uint32_t size = packet.size();
	vector<uint8_t> s(4);
	*((uint32_t*)s.data()) = size;
	packet.insert(packet.begin(), s.begin(), s.end());
	sendPacket(packet);
}