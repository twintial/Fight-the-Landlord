#ifndef  _CLIENT_H_
#define  _CLIENT_H_

#include<boost/asio.hpp>
#include<string>
#include<Player.h>
#include <GameScene.h>
using namespace boost::asio;
using namespace std;
using ip::tcp;
class Client
{
public:
	Client(Player*local);
	friend class GameScene;
	int Connect();
	void Ask_to_server();
	void HandleAnswer();
	void Loop_thread();
private:
	bool connect;
	Player* localplayer;
	ip::tcp::socket sock;
};
#endif