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
#include "Settings.h"
using namespace boost::asio;
using namespace std;
using ip::tcp;
typedef boost::shared_ptr<ip::tcp::socket> socket_ptr;

class Server
{
public:
	Server(Player*local, GameScene* scene);
	~Server();
	friend class GameScene;
	void CreateAccept();
	void Accept_thread();

	void ReadyMsg();
	void ReadyMsg_thread();
	
	void DealAndSnatchlandlord();
	void DealAndSnatchlandlord_thread();

	void Play();
	void Play_thread();

	void AddLocalName();
	void AddRemoteName();

	string read_msg(socket_ptr sock);
	void send_struct(socket_ptr sock);
	void read_struct(socket_ptr sock);
	static size_t isbulid;
private:
	bool ishandsend;
	bool isroomjoin;
	bool isallready;
	bool isstart;
	bool play_swith;

	int already_read;
	int max_point;//Ŀǰ����ߵ�����
	int now_lord;//Ŀǰ����������ߵ��ˣ������󽫱�Ϊ����
	int islord;//�Ƿ�Ϊ����
	int now_play;//Ŀǰ˭����

	char now_choose[1];
	play_data* datas;
	Player* localplayer;
	GameScene* localscene;//�޷�����localscene�����
};
#endif