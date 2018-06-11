#ifndef _SERVER_H_
#define _SERVER_H_

#include<cocos2d.h>
#include<boost/asio.hpp>
#include<string>
#include<vector>
#include<boost/bind.hpp>
#include<boost/thread.hpp>
#include "Player.h"
#include"Operation.h"
#include "GameScene.h"
using namespace boost::asio;
using namespace std;
using ip::tcp;
typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;
struct player_data_before_start_server
{
	int player_num;
	int isgamestart;
	char a_username[10];
	char b_username[10];
	char c_username[10];

};
class Server
{
public:
	Server(Player*local, GameScene* scene);
	friend class GameScene;
	void CreateAccept();
	void Accept_thread();

	void ReadyMsg();
	void ReadyMsg_thread();
	
	void DealAndSnatchlandlord();
	void DealAndSnatchlandlord_thread();

	void HandleRequest(socket_ptr sock);
	void AnalyzeRequest(socket_ptr sock, string msg);

	void CreateLoop();
	void Loop_thread();

	void AddLocalName();
	void AddRemoteName();

	string read_msg(socket_ptr sock);
	static size_t isbulid;
private:
	player_data_before_start_server datas;
	bool ishandsend;
	bool isroomjoin;
	bool isallready;
	int already_read;
	int max_point;
	int now_lord;
	char now_choose[1];
	Player* localplayer;
	GameScene* localscene;//无法利用localscene添加牌，原因不明
};
#endif