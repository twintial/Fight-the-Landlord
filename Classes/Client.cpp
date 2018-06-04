#include<Client.h>
Client::Client(string username) :sock(Client::service)
{}
void Client::Connect(ip::tcp::endpoint ep)
{
	sock.connect(ep);
}
io_service Client::service;