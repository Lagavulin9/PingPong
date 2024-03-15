#include <vsomeip/vsomeip.hpp>
#include <iostream>

int main()
{
	std::shared_ptr<vsomeip::application> app;
	std::shared_ptr<vsomeip::runtime> runtime;

	runtime = vsomeip::runtime::get();
	app = runtime->create_application("myApp");
	if (!app->init())
	{
		std::cerr << "Failed to initialize application" << std::endl;
		return 1;
	}

	app->start();

	return 0;
}