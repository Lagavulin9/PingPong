#include "pong.hpp"

int main()
{
	Pong pong;
	if (pong.init())
	{
		pong.offer();
		pong.start();
	}
	return 0;
}
