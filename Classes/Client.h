#ifndef  _CLIENT_H_
#define  _CLIENT_H_

#include<boost/asio.hpp>
#include<string>
using namespace boost::asio;
using namespace std;
using ip::tcp;
class Client
{
public:
	Client(string username);
	void Connect(ip::tcp::endpoint ep);
private:
	ip::tcp::socket sock;
	string user_name;
};
#endif