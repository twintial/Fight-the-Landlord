#ifndef _SERVER_H_
#define _SERVER_H_

#include<cocos2d.h>
#include<boost/asio.hpp>
#include<string>
#include<vector>
#include<boost/bind.hpp>
#include<boost/thread.hpp>
#include "Player.h"
using namespace boost::asio;
using namespace std;
using ip::tcp;
typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;
class Server
{
public:
	Server(Player*local);
	friend class GameScene;
	void CreateAccept();
	void Accept_thread();
	static void Answer_to_client(socket_ptr sock);
	static void HandleRequest(socket_ptr sock);
	void Loop_thread();
	static size_t isbulid;
private:
	Player * localplayer;
};
#endif