#ifndef _SERVER_H_
#define _SERVER_H_

#include<boost/asio.hpp>
#include<string>
using namespace boost::asio;
using namespace std;
using ip::tcp;
class Server
{
public:
	void CreateAccept_thread();
private:
};
#endif