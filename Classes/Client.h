#ifndef  _CLIENT_H_
#define  _CLIENT_H_

#include<boost/asio.hpp>
#include<string>
#include<Player.h>
#include <GameScene.h>
using namespace boost::asio;
using namespace std;
using ip::tcp;
struct player_data_before_start_client
{
	int player_num;
	int isgamestart;
	char a_username[10];
	char b_username[10];
	char c_username[10];

};
class Client
{
public:
	Client(Player*local, GameScene* scene);
	friend class GameScene;
	int CreateConnect();
	void Connect_thread();

	void ReadyMsg();
	void ReadyMsg_thread();

	void DealAndSnatchlandlord();
	void DealAndSnatchlandlord_thread();

	void Ask_to_server();
	void HandleAnswer_unstart();

	void CreateLoop();
	void Loop_thread();

	void AddLocalName();
	void AddLeftName(string leftname);
	void AddRightName(string rightname);

	string read_msg();
private:
	player_data_before_start_client datas;
	int already_read;
	int max_point;
	int now_lord;
	int islord;
	bool connect;
	bool isroomjoin;
	bool isallready;
	bool ishandreceive;
	char now_choose[1];
	Player* localplayer;
	GameScene* localscene;
	ip::tcp::socket sock;
};
#endif