#include "ping.hpp"

int main()
{
	Ping ping;
	if (ping.init())
	{
		ping.start();
	}
	return 0;
}
