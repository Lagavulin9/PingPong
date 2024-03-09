#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>
#include <vsomeip/vsomeip.hpp>
#include "defines.hpp"

class Ping
{
private:
	std::mutex mutex_;
	std::shared_ptr<vsomeip::application> app_;
	bool is_registered_;
	bool is_running_;

public:
	Ping();
	~Ping();

	bool init();
	void start();
	void stop();
	void on_state(vsomeip::state_type_e _state);
	void on_available(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available);
	void on_message(const std::shared_ptr<vsomeip::message> &_message);
	void sendPing();
};

Ping::Ping():
	app_(vsomeip::runtime::get()->create_application("PingExample")),
	is_registered_(false),
	is_running_(false)
{}

Ping::~Ping(){}

bool Ping::init()
{
	std::lock_guard<std::mutex> its_lock(mutex_);

	if (!app_->init())
	{
		std::cerr << "Failed to initialize application" << std::endl;
		return false;
	}
	app_->register_state_handler(
		std::bind(&Ping::on_state, this, std::placeholders::_1));
	app_->register_availability_handler(
		PONG_SERVICE_ID, PONG_INSTANCE_ID,
		std::bind(&Ping::on_available, this,
				std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	app_->register_message_handler(
		PONG_SERVICE_ID, PONG_INSTANCE_ID, vsomeip::ANY_METHOD,
		std::bind(&Ping::on_message, this, std::placeholders::_1));
	return true;
}

void Ping::start()
{
	app_->start();
}

void Ping::stop()
{
	app_->clear_all_handler();
	app_->release_service(PING_SERVICE_ID, PING_INSTANCE_ID);
	app_->stop();
}

void Ping::on_state(vsomeip::state_type_e _state)
{
	std::cout << "Application " << app_->get_name() << " is "
			<< (_state == vsomeip::state_type_e::ST_REGISTERED ?
				"registered" : "deregistered")
			<< std::endl;
	if (_state == vsomeip::state_type_e::ST_REGISTERED)
	{
		std::cout << "Requesting Pong Service..." << std::endl;
		app_->request_service(PONG_SERVICE_ID, PONG_INSTANCE_ID);
	}
}

void Ping::on_available(vsomeip::service_t _service, vsomeip::instance_t _instance, bool _is_available)
{
	std::cout << "Pong service is available" << std::endl;

	sendPing();
}

void Ping::on_message(const std::shared_ptr<vsomeip::message> &_msg)
{
	std::cout << "Received a message with Client/Session ["
			<< std::setfill('0') << std::hex
			<< std::setw(4) << _msg->get_client() << "/"
			<< std::setw(4) << _msg->get_session() << "]"
			<< std::endl;

	std::shared_ptr<vsomeip::payload> payload = _msg->get_payload();
	std::string response = std::string(
		reinterpret_cast<const char*>(payload->get_data()), 0, payload->get_length());
	std::cout << "Received message: " << response.c_str() << std::endl;

	std::this_thread::sleep_for(std::chrono::seconds(1));
	sendPing();
}

void Ping::sendPing()
{
	std::shared_ptr<vsomeip::runtime> runtime = vsomeip::runtime::get();

	std::shared_ptr<vsomeip::message> request = runtime->create_request();
	request->set_service(PONG_SERVICE_ID);
	request->set_instance(PONG_INSTANCE_ID);
	request->set_method(PING_METHOD_ID);

	std::string msg("Ping");
	std::vector<vsomeip::byte_t> payload_date(std::begin(msg), std::end(msg));

	std::shared_ptr<vsomeip::payload> payload = runtime->create_payload();
	payload->set_data(payload_date);
	request->set_payload(payload);
	std::cout << "Sending: " << msg << std::endl;
	app_->send(request);
}

int main()
{
	Ping ping;
	if (ping.init())
	{
		ping.start();
	}
	return 0;
}
