#include<Client.h>
io_service service;
size_t read_complete_client(char * buff, const boost::system::error_code & err, size_t bytes)
{
	bool found = std::find(buff, buff + bytes, '\n') < buff + bytes;// 我们一个一个读取直到读到回车，不缓存
	return found ? 0 : 1;
}

Client::Client(Player* local, GameScene* scene) :sock(service)
{
	connect = false;
	localplayer = new Player();
	localplayer->username = local->username;
	localplayer->IP = local->IP;
	localscene = scene;
}
int Client::Connect()
{
	ip::tcp::endpoint ep(ip::address::from_string(localplayer->IP), 8080);
	log("%s", localplayer->IP.c_str());
	try
	{
		sock.connect(ep);
	}
	catch (boost::system::system_error & err)
	{
		MessageBox("can't find host", "wrong IP");
		return -1;
	}
	connect = true;//已连接
	log("connected");//日志

	localplayer->username += '\n';
	sock.write_some(buffer(localplayer->username));

	char player_num[1];
	sock.read_some(buffer(player_num));
	localplayer->playercode = player_num[0];//读取自己为第几位玩家
	log("play_num=%d", localplayer->playercode);

	return 0;
}

void Client::Ask_to_server()
{
	if (!GameScene::start)
	{
		sock.write_some(buffer("ping/n"));
		HandleAnswer_unstart();
	}
	else
	{

	}

}
void Client::HandleAnswer_unstart()
{

}
void Client::Loop_thread()
{
	while (connect)
	{
		Ask_to_server();
	}
}