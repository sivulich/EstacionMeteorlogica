#include "ServerNetworking.h"

int main(void)
{
	ServerNetworking net;
	bool exit=false;
	while (!exit)
	{
		net.handleEvents();
	}
	return 0;
}