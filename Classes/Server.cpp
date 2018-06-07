#include<Server.h>
USING_NS_CC;

extern char players[1] = { 0 };
char pre[512];
vector<socket_ptr> client;
vector<string> users_name;
boost::recursive_mutex cs;//保证线程安全
size_t read_complete_server(char * buff, const boost::system::error_code & err, size_t bytes)
{
	bool found = std::find(buff, buff + bytes, '\n') < buff + bytes;// 我们一个一个读取直到读到回车，不缓存
	return found ? 0 : 1;
}

Server::Server(Player* local, GameScene* scene)
{
	localplayer = new Player();
	localplayer->username = local->username;
	localplayer->IP = local->IP;
	localscene = scene;
}
void Server::CreateAccept()
{
	AddLocalName();
	players[0]++;
	users_name.push_back(localplayer->username);
	io_service service;
	ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 8080));
	while (players[0] < 3)
	{
		socket_ptr sock(new ip::tcp::socket(service));
		log("is build");
		acceptor.accept(*sock);
		boost::recursive_mutex::scoped_lock lk(cs);//防止死锁

		players[0]++;

		int bytes = read(*sock, buffer(pre), boost::bind(read_complete_server, pre, _1, _2));
		string msg(pre, bytes - 1);
		users_name.push_back(msg);
		memset(pre, 0, sizeof(pre));

		sock->write_some(buffer(players));//给刚连接的玩家传入玩家数目（由于不能发送int类型，用char代替）

		client.push_back(sock);
		AddRemoteName();
	}
	log("player member has been full");
}
void Server::Accept_thread()
{
	boost::thread accept(boost::bind(&Server::CreateAccept, this));
}
void Server::HandleRequest(socket_ptr sock)
{
	int bytes = read(*sock, buffer(pre), boost::bind(read_complete_server, pre, _1, _2));
	string msg(pre, bytes - 1);
	memset(pre, 0, sizeof(pre));
	if (msg == "ping")
	{
		Answer_to_client_unstart(sock);
	}
}
void Server::Answer_to_client_unstart(socket_ptr sock)
{
	sock->write_some(buffer(players));
}
void Server::Loop_thread()
{
	boost::recursive_mutex::scoped_lock lk(cs);//防止死锁
	while (1)
	{
		for (auto b = client.begin(), e = client.end(); b != e; b++)
		{
			HandleRequest(*b);
		}
		boost::this_thread::sleep(boost::posix_time::millisec(100));
	}
}
void Server::AddLocalName()
{
	auto localusername = LabelTTF::create(localplayer->username, "arial", 30);
	localusername->setPosition(110, 100);
	localscene->addChild(localusername);
}
void Server::AddRemoteName()
{
	auto remoteusername = LabelTTF::create(users_name[players[0] - 1], "arial", 30);
	if (players[0] == 2)
	{
		remoteusername->setPosition(1100, 500);
	}
	else
	{
		remoteusername->setPosition(45, 500);
	}
	localscene->addChild(remoteusername);
}