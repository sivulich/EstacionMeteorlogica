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
	SlaveNetworking network;
	while(quit ==false)
	{
		while(network.hayEvento()==false);
		Event in=network.getEvent();
		switch (in.type())
		{
			case GET_STATUS:
				network.sendStatus(sensors.getSensors(), sensors.getBattery(), sensors.getBusy());
				break;
			case DATA_REQUEST:
				network.sendData(sensors.getSensors());
				break;
			case RESET_SLAVE:
				system("shutdown -r now");
				break;
			case EMERGENCY_SHUTDOWN:
				system("shutdown -h now");
				exit(1);
			case REQUEST_SENSOR_LIST:
				network.sendSensorList(sensors.getSensors());
				break;
			default:
				break;

		}
	}
	return 0;
}