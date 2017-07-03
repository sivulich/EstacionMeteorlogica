#include "configs.h"
#include "SlaveNetworking.h"
#include "Event.h"
#include "Slave.h"

int main(void)
{
	bool quit=false;

	Slave sensors;
	sensors.init();
	//monitor.init();
	while(quit ==false)
	{
		SlaveNetworking network;
		network.init();				//check this, the slave networking makes a new of the event
		while(network.hayEvento()==false);
		Event in=network.getEvent();
		switch (in.type())
		{
			case PING_BROADCAST:
				cout << "Receive a ping broadcast" << endl;
				network.sendPingResponse(sensors.getSensors());
				break;
			case CONNECT_TO_SLAVE:
				network.sendConnectAck();
				break;
			case GET_STATUS:
				network.sendStatus(sensors.getSensors(), sensors.getBattery(), sensors.getBusy());
				break;
			case DATA_REQUEST:
				network.sendData(sensors.getSensors());
				break;
			case RESET_SLAVE:
				//monitor.reset();
				//exit=true;
				cout << "Reset Slave.." << endl;
				break;
			case EMERGENCY_SHUTDOWN:
				system("shutdown -P");
				exit(1);
			case SOFTWARE_UPDATE:
				//network.getUpdate();
				//monitor.update();
				break;
			case REQUEST_SENSOR_LIST:
				//network.sendSensorList(sensors.getList());
				break;
			default:
				break;

		}
	}
	return 0;
}