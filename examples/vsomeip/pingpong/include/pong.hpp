#pragma once
#ifndef __PONG_HPP__
# define __PONG_HPP__
#endif

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <thread>
#include <mutex>
#include <vsomeip/vsomeip.hpp>
#include "defines.hpp"

class Pong
{
private:
	std::mutex mutex_;
	std::shared_ptr<vsomeip::application> app_;
	bool is_registered_;
	bool is_running_;

public:
	Pong();
	~Pong();

	bool init();
	void start();
	void stop();
	void offer();
	void stop_offer();
	void on_state(vsomeip::state_type_e _state);
	void on_message(const std::shared_ptr<vsomeip::message> &_request);
	void sendPong(const std::shared_ptr<vsomeip::message> &_request);
};

Pong::Pong():
	app_(vsomeip::runtime::get()->create_application("PongExample")),
	is_registered_(false),
	is_running_(false)
{}

Pong::~Pong(){}

bool Pong::init()
{
	std::lock_guard<std::mutex> its_lock(mutex_);

	if (!app_->init())
	{
		std::cerr << "Failed to initialize application" << std::endl;
		return false;
	}
	app_->register_state_handler(
		std::bind(&Pong::on_state, this, std::placeholders::_1));
	app_->register_message_handler(
		PONG_SERVICE_ID, PONG_INSTANCE_ID, vsomeip::ANY_METHOD,
		std::bind(&Pong::on_message, this, std::placeholders::_1));
	return true;
}

void Pong::start()
{
	app_->start();
}

void Pong::stop()
{
	is_running_ = false;
	app_->clear_all_handler();
	stop_offer();
	app_->stop();
}

void Pong::offer()
{
	app_->offer_service(PONG_SERVICE_ID, PONG_INSTANCE_ID);
	std::cout << "Offering Service: "
			<< std::hex << "0x" << PONG_SERVICE_ID << std::endl;
}

void Pong::stop_offer()
{
	app_->stop_offer_service(PONG_SERVICE_ID, PONG_INSTANCE_ID);
	std::cout << "Stop Offering Service: "
			<< std::hex << "0x" << PONG_SERVICE_ID << std::endl;
}

void Pong::on_state(vsomeip::state_type_e _state)
{
	std::cout << "Application " << app_->get_name() << " is "
			<< (_state == vsomeip::state_type_e::ST_REGISTERED ?
				"registered" : "deregistered")
			<< std::endl;
}

void Pong::on_message(const std::shared_ptr<vsomeip::message> &_request)
{
	std::cout << "Received a message with Client/Session ["
			<< std::setfill('0') << std::hex
			<< std::setw(4) << _request->get_client() << "/"
			<< std::setw(4) << _request->get_session() << "]"
			<< std::endl;

	std::shared_ptr<vsomeip::payload> payload = _request->get_payload();
	std::string recv = std::string(
		reinterpret_cast<const char*>(payload->get_data()), 0, payload->get_length());
	std::cout << "Received message: " << recv.c_str() << std::endl;

	sendPong(_request);
}

void Pong::sendPong(const std::shared_ptr<vsomeip::message> &_request)
{
	std::shared_ptr<vsomeip::runtime> runtime = vsomeip::runtime::get();
	std::shared_ptr<vsomeip::message> response = runtime->create_response(_request);
	std::shared_ptr<vsomeip::payload> payload = runtime->create_payload();

	std::string msg = "Pong";
	std::vector<vsomeip::byte_t> payload_data(std::begin(msg), std::end(msg));
	payload->set_data(payload_data);
	response->set_payload(payload);

	std::cout << "Sending response: " << msg << std::endl;
	app_->send(response);
}
