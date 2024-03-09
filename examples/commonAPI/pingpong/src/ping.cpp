#include <CommonAPI/CommonAPI.hpp>
#include <v1/pingpong/PongProxy.hpp>
#include <thread>

using namespace v1::pingpong;

int main()
{
	std::shared_ptr<CommonAPI::Runtime> runtime = CommonAPI::Runtime::get();

	std::string domain = "local";
	std::string instance = "pingpong.Pong";
	std::string connection = "ping";

	std::shared_ptr<PongProxy<>> pongProxy = runtime->buildProxy<PongProxy>(domain, instance, connection);
	std::cout << "Checking availability!" << std::endl;

	while (!pongProxy->isAvailable())
		std::this_thread::sleep_for(std::chrono::microseconds(10));
	std::cout << "Available..." << std::endl;

	CommonAPI::CallStatus callStatus;
	CommonAPI::CallInfo info(1000);
	info.sender_ = 1234;
	std::string reply;

	while (true)
	{
		std::cout << "Ping..." << std::endl;
		pongProxy->pingMe("Ping", callStatus, reply, &info);
		if (callStatus != CommonAPI::CallStatus::SUCCESS)
		{
			std::cerr << "Remote call failed" << std::endl;
			return -1;
		}
		info.timeout_ += 1000;

		std::cout << "Reply: " << reply << std::endl;
		std::this_thread::sleep_for(std::chrono::seconds(1));
	}

	return 0; 
}