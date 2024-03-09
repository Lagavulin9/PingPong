#include <CommonAPI/CommonAPI.hpp>
#include "pongStubImpl.hpp"
#include <thread>

int main()
{
	std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();

	std::string domain = "local";
	std::string instance = "pingpong.Pong";
	std::string connection = "ping-pong";

	std::shared_ptr<PongStubImpl> pongService = std::make_shared<PongStubImpl>();
	while (!runtime->registerService(domain, instance, pongService, connection))
	{
		std::cout << "Register Service failed, trying again in 100 milliseconds..." << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	};
	std::cout << "Successfully Registered Pong Service!" << std::endl;

	while (true) {
		std::cout << "Waiting for calls... (Abort with CTRL+C)" << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(60));
	}

	return 0;
}