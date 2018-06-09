#include<Server.h>
USING_NS_CC;

extern char players[1] = { 0 };
int ready_players[3] = { 0 };//0,1为client 2为host
vector<socket_ptr> client;
vector<string> users_name;
boost::recursive_mutex cs;//保证线程安全
size_t read_complete_server(char * buff, const boost::system::error_code & err, size_t bytes)
{
	bool found = std::find(buff, buff + bytes, '\n') < buff + bytes;// 一个一个读取直到读到回车，不缓存
	return found ? 0 : 1;
}

Server::Server(Player* local, GameScene* scene)
{
	isroomjoin = false;
	isallready = false;

	datas.player_num = 0;
	datas.isgamestart = 0;

	already_read = 0;
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
	memcpy(datas.a_username, localplayer->username.c_str(), sizeof(localplayer->username));//将服务器的玩家作为a
	io_service service;
	ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 8080));
	while (1)
	{
		socket_ptr sock(new ip::tcp::socket(service));
		log("is build");
		acceptor.accept(*sock);

		players[0]++;
		datas.player_num++;

		string connected_name = read_msg(sock);
		users_name.push_back(connected_name);

		sock->write_some(buffer(players));//给刚连接的玩家传入玩家数目（由于不能发送int类型，用char代替）
		if (players[0] == 2)
		{
			string userhost = users_name[0] + '\n';
			sock->write_some(buffer(userhost));
		}
		else if (players[0] == 3)
		{
			//发送给3号玩家
			string userhost = users_name[0] + '\n';
			sock->write_some(buffer(userhost));
			string user_2 = users_name[1] + '\n';
			sock->write_some(buffer(user_2));
			//发送给2号玩家三号的情况
			string user_3 = users_name[2] + '\n';
			client[0]->write_some(buffer(user_3));
		}
		client.push_back(sock);
		log("num=%d", client.size());
		boost::this_thread::sleep(boost::posix_time::millisec(100));//sleep
		AddRemoteName();
		if (players[0] == 3)
		{
			isroomjoin = true;
		}
	}
	log("player member has been full");
}
void Server::Accept_thread()
{
	boost::thread accept(boost::bind(&Server::CreateAccept, this));
}

void Server::ReadyMsg()
{
	while (true)
	{
		if (isroomjoin)
		{
			//host是否准备
			if (localplayer->isready)
			{
				ready_players[2] = 1;
			}
			//给服务器发送/读取数据
			for (int i = 0; i <= client.size() - 1; i++)
			{
				char readymsg[1];
				try
				{
					client[i]->read_some(buffer(readymsg));
				}
				catch (boost::system::system_error e)
				{
					MessageBox("read", "wrong");
					log("%d", e.code());
				}
				if (readymsg[0])
				{
					ready_players[i] = 1;
				}
				if (ready_players[0]==1&&ready_players[1]==1)
				{
					if (ready_players[2] == 1)
					{
						isallready = true;
					}
				}
				//发送
				char isready[1];
				isready[0] = isallready ? 1 : 0;
				client[i]->write_some(buffer(isready));
				boost::this_thread::sleep(boost::posix_time::millisec(500));
			}
		}
	}
}
void Server::ReadyMsg_thread()
{
	boost::thread ReadyMsg(boost::bind(&Server::ReadyMsg, this));
}

void Server::HandleRequest(socket_ptr sock)
{
	//if (localplayer->isready)
	//{
	//	ready_num++;
	//	localplayer->isready = false;
	//}
	//log("readyread");
	//try
	//{
	//	//AnalyzeRequest(sock, msg);
	//}
	//catch (boost::system::system_error & err)
	//{
	//	MessageBox("server read error", "server read error");
	//}

}
void Server::AnalyzeRequest(socket_ptr sock, string msg)
{
	//if (msg == "clientstate"||msg=="0clientstate")
	//{
	//	char send_buff[512];
	//	memset(send_buff, 0, sizeof(send_buff));
	//	memcpy(send_buff, &datas, sizeof(datas));
	//	try 
	//	{
	//		sock->write_some(buffer(send_buff));
	//	}
	//	catch (boost::system::system_error & err)
	//	{
	//		MessageBox("server write error", "server write error");
	//	}

	//	//读取此玩家的准备情况
	//	//log("isread=%s", isready.c_str());
	//	//if (isready == "1")
	//	//{
	//	//	ready_num++;
	//	//}
	//	if (ready_num == 3)
	//	{
	//		GameScene::start = true;
	//		datas.isgamestart = 1;
	//	}
	//}
}

void Server::CreateLoop()
{
	log("enter server loop");
	//boost::recursive_mutex::scoped_lock lk(cs);//防止死锁
	while (1)
	{
		
		if (client.size() != 0)
		{
			log("server looping");
			for (auto b = client.begin(), e = client.end(); b != e; ++b)
			{
				//boost::this_thread::sleep(boost::posix_time::millisec(100));
				boost::recursive_mutex::scoped_lock lk(cs);
				HandleRequest(*b);
			}
		}
	}
}
void Server::Loop_thread()
{
	boost::thread loop(boost::bind(&Server::CreateLoop, this));
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

string Server::read_msg(socket_ptr sock)
{
	char pre[512];
	int bytes = read(*sock, buffer(pre), boost::bind(read_complete_server, pre, _1, _2));
	string msg(pre, bytes - 1);
	return msg;
}