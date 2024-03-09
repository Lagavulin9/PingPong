#pragma once

#include <iostream>
#include <CommonAPI/CommonAPI.hpp>
#include <v1/pingpong/PongStubDefault.hpp>

using namespace v1::pingpong;

class PongStubImpl: public PongStubDefault
{
public:
	PongStubImpl();
	virtual ~PongStubImpl();

	void handlePing(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _ping, pingMeReply_t _reply);
};