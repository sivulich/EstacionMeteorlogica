#include "ServerNetworking.h"

int main(void)
{
	ServerNetworking net;
	while (1)
	{
		net.handleEvents();
	}
	return 0;
}