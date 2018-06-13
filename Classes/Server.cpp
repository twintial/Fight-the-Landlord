#include<Server.h>
USING_NS_CC;

extern char players[1] = { 0 };
int ready_players[3] = { 0 };//0,1Ϊclient 2Ϊhost
int hastold[2] = { 0 };

vector<socket_ptr> client;
vector<string> users_name;
boost::recursive_mutex cs;//��֤�̰߳�ȫ
size_t read_complete_server(char * buff, const boost::system::error_code & err, size_t bytes)
{
	bool found = std::find(buff, buff + bytes, '\n') < buff + bytes;// һ��һ����ȡֱ�������س���������
	return found ? 0 : 1;
}

Server::Server(Player* local, GameScene* scene)
{
	isroomjoin = false;
	isallready = false;
	ishandsend = false;
	isstart = false;
	play_swith = false;
	//isclick = false;
	//isrecv_struct = false;

	max_point = -1;
	now_lord = -1;
	already_read = 0;
	now_choose[0] = -1;
	islord = -1;
	now_play = -1;

	localplayer = new Player();
	localplayer->username = local->username;
	localplayer->IP = local->IP;
	localscene = scene;
	//��ʼ���ṹ��
	datas = new play_data;
	datas->card_amount = 0;
	datas->card_type = 0;
	datas->isplay_pokers = false;

}

void Server::CreateAccept()
{
	AddLocalName();
	players[0]++;
	localplayer->playercode = players[0];
	users_name.push_back(localplayer->username);
	//memcpy(datas.a_username, localplayer->username.c_str(), sizeof(localplayer->username));//���������������Ϊa
	io_service service;
	ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 8080));
	while (1)
	{
		socket_ptr sock(new ip::tcp::socket(service));
		log("is build");
		acceptor.accept(*sock);

		players[0]++;
		/*datas.player_num++;*/

		string connected_name = read_msg(sock);
		users_name.push_back(connected_name);

		sock->write_some(buffer(players));//�������ӵ���Ҵ��������Ŀ�����ڲ��ܷ���int���ͣ���char���棩
		boost::this_thread::sleep(boost::posix_time::millisec(100));
		if (players[0] == 2)
		{
			string userhost = users_name[0] + '\n';
			sock->write_some(buffer(userhost));
			boost::this_thread::sleep(boost::posix_time::millisec(100));
		}
		else if (players[0] == 3)
		{
			//���͸�3�����
			string userhost = users_name[0] + '\n';
			sock->write_some(buffer(userhost));
			boost::this_thread::sleep(boost::posix_time::millisec(100));
			string user_2 = users_name[1] + '\n';
			sock->write_some(buffer(user_2));
			boost::this_thread::sleep(boost::posix_time::millisec(100));
			//���͸�2��������ŵ����
			string user_3 = users_name[2] + '\n';
			client[0]->write_some(buffer(user_3));
		}
		client.push_back(sock);
		log("num=%d", client.size());
		//boost::this_thread::sleep(boost::posix_time::millisec(100));
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
		if (isroomjoin && (hastold[0] == 0 || hastold[1] == 0))
		{
			//log("0=%d", hastold[0]);
			//log("1=%d", hastold[1]);
			//host�Ƿ�׼��
			if (localplayer->isready)
			{
				ready_players[2] = 1;
			}
			//������������/��ȡ����
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
				//����
				char isready[1];
				isready[0] = isallready ? 1 : 0;
				client[i]->write_some(buffer(isready));
				if (isallready)
				{
					hastold[i] = 1;
				}
				if (hastold[0] == 1 && hastold[1] == 1)
				{
					break;
				}
			}
		}
	}
}
void Server::ReadyMsg_thread()
{
	boost::thread ReadyMsg(boost::bind(&Server::ReadyMsg, this));
}

void Server::DealAndSnatchlandlord()
{
	boost::recursive_mutex::scoped_lock lk(cs);
	vector<int>card;
	Operation::CardShuffle(card);
	auto b = new Player();
	auto c = new Player();
	//����
	Operation::CardDeal(*localplayer, *b, *c, card);
	while (true)
	{
		if (hastold[0] == 1 && hastold[1] == 1)
		{
			if (!ishandsend)
			{
				client[0]->write_some(buffer(b->hand));
				client[1]->write_some(buffer(c->hand));
				ishandsend = true;
			}
			boost::this_thread::sleep(boost::posix_time::millisec(100));
			//ѡ����
			srand((unsigned)time(NULL));
			now_choose[0] = rand() % 3 + 1;
			//��ͻ��˴����һ��ѡ����
			client[0]->write_some(buffer(now_choose));
			client[1]->write_some(buffer(now_choose));
			log("now choose=%d", now_choose[0]);
			//Ŀǰ����ߵ�����
			for (int i = 0; i <= 2; i++)
			{
				if (localplayer->playercode == now_choose[0])
				{

					while (true)
					{
						if (localplayer->lord_point != -1)
						{
							log("lord_point=%d", localplayer->lord_point);
							char local_lordpoint[1];
							local_lordpoint[0] = localplayer->lord_point;
							client[0]->write_some(buffer(local_lordpoint));
							client[1]->write_some(buffer(local_lordpoint));
							if (local_lordpoint[0] > max_point)
							{
								max_point = local_lordpoint[0];
								now_lord = now_choose[0];
							}
							break;
						}
					}
				}
				else
				{
					char remote_lordpoint[1];
					client[now_choose[0] - 2]->read_some(buffer(remote_lordpoint));
					//ת������һ���ͻ������
					client[3 - now_choose[0]]->write_some(buffer(remote_lordpoint));
					if (remote_lordpoint[0] > max_point)
					{
						max_point = remote_lordpoint[0];
						now_lord = now_choose[0];
					}
				}
				if (max_point == 3)
				{
					break;
				}
				now_choose[0]++;
				now_choose[0] = now_choose[0] > 3 ? (now_choose[0] - 3) : now_choose[0];
			}
			break;
		}
	}
	//�������Ʒ����ͻ������
	vector<int>lord_poker;
	lord_poker.push_back(card[51]);
	lord_poker.push_back(card[52]);
	lord_poker.push_back(card[53]);
	client[0]->write_some(buffer(lord_poker));
	client[1]->write_some(buffer(lord_poker));
	//��ӵ�����
	localplayer->hand.push_back(card[51]);
	localplayer->hand.push_back(card[52]);
	localplayer->hand.push_back(card[53]);
	//localplayer���������Ϊ�����ƣ�localplayer�Ʋ���ʹ��
	islord = now_lord == localplayer->playercode ? 1 : 0;
}
void Server::DealAndSnatchlandlord_thread()
{
	boost::thread DealAndSnatchlandlord(boost::bind(&Server::DealAndSnatchlandlord, this));
}

void Server::Play()
{
	while (true)
	{
		log("isstart=%d", isstart);
		if (isstart)
		{
			now_play = now_lord;
			//��ʼ��Ϸ
			//while (true)
			//{
				if (localplayer->playercode = now_play)
				{
					play_swith = true;
					//�ȴ����
					while (true)
					{
						//������������ͻ��˷������ݰ�
						if (localscene->isclick)
						{
							send_struct(client[0]);
							send_struct(client[1]);
							log("ca=%d", datas->card_amount);
							log("card_type=%d", datas->card_type);
							log("%d", datas->isplay_pokers);
							for (int i = 0; i <= datas->card_amount - 1; i++)
							{
								log("%d=%d", i, datas->out_poker[i]);
							}
							localscene->isclick = false;
							break;
						}
					}
				}
				else
				{

				}
			//}
		}
	}
}
void Server::Play_thread()
{
	boost::thread Play(boost::bind(&Server::Play, this));
}

//void Server::HandleRequest(socket_ptr sock)
//{
//	//if (localplayer->isready)
//	//{
//	//	ready_num++;
//	//	localplayer->isready = false;
//	//}
//	//log("readyread");
//	//try
//	//{
//	//	//AnalyzeRequest(sock, msg);
//	//}
//	//catch (boost::system::system_error & err)
//	//{
//	//	MessageBox("server read error", "server read error");
//	//}
//
//}
//void Server::AnalyzeRequest(socket_ptr sock, string msg)
//{
//	//if (msg == "clientstate"||msg=="0clientstate")
//	//{
//	//	char send_buff[512];
//	//	memset(send_buff, 0, sizeof(send_buff));
//	//	memcpy(send_buff, &datas, sizeof(datas));
//	//	try 
//	//	{
//	//		sock->write_some(buffer(send_buff));
//	//	}
//	//	catch (boost::system::system_error & err)
//	//	{
//	//		MessageBox("server write error", "server write error");
//	//	}
//
//	//	//��ȡ����ҵ�׼�����
//	//	//log("isread=%s", isready.c_str());
//	//	//if (isready == "1")
//	//	//{
//	//	//	ready_num++;
//	//	//}
//	//	if (ready_num == 3)
//	//	{
//	//		GameScene::start = true;
//	//		datas.isgamestart = 1;
//	//	}
//	//}
//}
//
//void Server::CreateLoop()
//{
//	log("enter server loop");
//	//boost::recursive_mutex::scoped_lock lk(cs);//��ֹ����
//	while (1)
//	{
//		
//		if (client.size() != 0)
//		{
//			log("server looping");
//			for (auto b = client.begin(), e = client.end(); b != e; ++b)
//			{
//				//boost::this_thread::sleep(boost::posix_time::millisec(100));
//				boost::recursive_mutex::scoped_lock lk(cs);
//				HandleRequest(*b);
//			}
//		}
//	}
//}
//void Server::Loop_thread()
//{
//	boost::thread loop(boost::bind(&Server::CreateLoop, this));
//}

void Server::AddLocalName()
{
	auto localusername = LabelTTF::create(localplayer->username, "arial", 30);
	localusername->setPosition(130, 40);
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
void Server::send_struct(socket_ptr sock)
{
	char msg[512];
	memset(msg, 0, sizeof(msg));
	memcpy(msg, datas, sizeof(*datas));
	sock->write_some(buffer(msg));
}
