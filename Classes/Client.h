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
	Client(Player*local, GameScene* scene);
	friend class GameScene;
	int Connect();
	void Ask_to_server();
	void HandleAnswer_unstart();
	void Loop_thread();
private:
	bool connect;
	Player* localplayer;
	GameScene* localscene;
	ip::tcp::socket sock;
};
#endif