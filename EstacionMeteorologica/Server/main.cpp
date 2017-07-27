#include "ServerNetworking.h"


int main(void)
{
	ServerNetworking net;
	bool exit=false;
	time_t timer=time(NULL);
	while (!exit)
	{
		exit=net.handleEvents();
		if (time(NULL)-timer >= SERVER_DATA_INTERVAL)
		{
			net.sendDataReq();
			timer = time(NULL);
		}
	}
	return 0;
}