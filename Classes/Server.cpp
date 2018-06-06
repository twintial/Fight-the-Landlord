#include<Server.h>
io_service service;
void Server::CreateAccept_thread()
{
	ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 8080));
	while (true)
	{

	}
}