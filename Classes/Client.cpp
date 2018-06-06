#include<Client.h>
io_service service;
Client::Client(Player* local) :sock(service)
{
	connect = false;
	localplayer = new Player();
	localplayer->username = local->username;
	localplayer->IP = local->username;
}
int Client::Connect()
{
	ip::tcp::endpoint ep(ip::address::from_string(localplayer->IP), 8080);
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
	char player_num[1];
	sock.read_some(buffer(player_num));
	localplayer->playercode = player_num[0];//读取自己为第几位玩家
	
	return 0;
}
void Client::HandleAnswer()
{

}
void Client::Ask_to_server()
{

}
void Client::Loop_thread()
{
	while (connect)
	{
		Ask_to_server();
		HandleAnswer();
	}
}