#include<Client.h>
io_service service;
Client::Client(string username) :sock(service)
{}
void Client::Connect(ip::tcp::endpoint ep)
{
	sock.connect(ep);
}