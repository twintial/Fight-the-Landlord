#ifndef  _CLIENT_H_
#define  _CLIENT_H_

#include<boost/asio.hpp>
#include<string>
#include<Player.h>
#include <GameScene.h>
#include "Settings.h"
using namespace boost::asio;
using namespace std;
using ip::tcp;
//struct player_data_before_start_client
//{
//	int player_num;
//	int isgamestart;
//	char a_username[10];
//	char b_username[10];
//	char c_username[10];
//
//};
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

	void Play();
	void Play_thread();

	//void Ask_to_server();
	//void HandleAnswer_unstart();

	//void CreateLoop();
	//void Loop_thread();

	void AddLocalName();
	void AddLeftName(string leftname);
	void AddRightName(string rightname);

	string read_msg();
	void read_struct();
	void send_struct();
private:
	int already_read;
	int max_point;
	int now_lord;
	int islord;
	int now_play;//目前谁出牌

	bool connect;
	bool isroomjoin;
	bool isallready;
	bool ishandreceive;
	bool isstart;
	bool play_swith;
	//bool isclick;//是否点击
	//bool isrecv_struct;//是否收到数据包

	char now_choose[1];
	play_data* datas;
	Player* localplayer;
	GameScene* localscene;
	ip::tcp::socket sock;
};
#endif