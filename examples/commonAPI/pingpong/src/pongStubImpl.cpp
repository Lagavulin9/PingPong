#include "pongStubImpl.hpp"

PongStubImpl::PongStubImpl(){}

PongStubImpl::~PongStubImpl(){}

void PongStubImpl::handlePing(const std::shared_ptr<CommonAPI::ClientId> _client, std::string _ping, pingMeReply_t _reply)
{
	std::cout << "Pinged" << std::endl;
	std::cout << "Sending Pong..." << std::endl;
	_reply("Pong");
}