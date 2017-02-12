


int main(void)
{
	/*
	bool exit=false;
	network.init();
	sensors.init();
	monitor.init();
	while(exit ==false)
	{
		whlie(network.hayEvento()==false);
		event in=network.getEvent();
		switch (in.type())
		{
			case PING:
				network.sendSerial();
				break;
			case CONNECT_TO_SLAVE:
				network.sendConnectAck();
				break;
			case GET_STATUS:
				network.sendStatus(monitor.getStatus());
				break;
			case DATA_REQUEST:
				network.sendData(sensors.getData());
				break;
			case RESET_SLAVE:
				monitor.reset();
				exit=true;
				break;
			case EMERGENCY_SHUTDOWN:
				system("shutdown -now"); //lookup real command
				exit(1);
			case SOFTWARE_UPDATE:
				network.getUpdate();
				monitor.update();
				exit=true;
				break;
			case REQUEST_SENSOR_LIST:
				network.sendSensorList(sensors.getList());
				break;

		}
	}

	*/
	return 0;
}