#include<Client.h>
io_service service;
char _data[512];
size_t read_complete_client(char * buff, const boost::system::error_code & err, size_t bytes)
{
	bool found = std::find(buff, buff + bytes, '\n') < buff + bytes;// ����һ��һ����ȡֱ�������س���������
	return found ? 0 : 1;
}

Client::Client(Player* local, GameScene* scene) :sock(service)
{
	max_point = -1;
	now_lord = -1;
	already_read = 0;
	islord = -1;
	now_play = -1;

	connect = false;
	isroomjoin = false;
	isallready = false;
	ishandreceive = false;
	isstart = false;
	play_swith = false;
	//isclick = false;
	//isrecv_struct = false;

	localplayer = new Player();
	localplayer->username = local->username;
	localplayer->IP = local->IP;
	localscene = scene;
	//��ʼ���ṹ��
	datas = new play_data;
	datas->card_amount = 0;
	datas->card_type = 0;
	datas->isplay_pokers = true;
}

int Client::CreateConnect()
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

	AddLocalName();

	localplayer->username += '\n';
	sock.write_some(buffer(localplayer->username));

	char player_num[1];
	sock.read_some(buffer(player_num));
	localplayer->playercode = player_num[0];//��ȡ�Լ�Ϊ�ڼ�λ���

	if (localplayer->playercode == 2)
	{
		string leftname = read_msg();
	
		AddLeftName(leftname);
		string rightname = read_msg();

		AddRightName(rightname);
	}
	if (localplayer->playercode == 3)
	{
		string rightname = read_msg();
		//boost::this_thread::sleep(boost::posix_time::millisec(100));
		AddRightName(rightname);
		string leftname = read_msg();
		//boost::this_thread::sleep(boost::posix_time::millisec(100));
		AddLeftName(leftname);
	}
	log("play_num=%d", localplayer->playercode);
	connect = true;//������
	isroomjoin = true;
	log("connected");//��־
	return 0;
}
void Client::Connect_thread()
{
	boost::thread connect(boost::bind(&Client::CreateConnect, this));
}

void Client::ReadyMsg()
{
	while (true)
	{
		//log("%d",isallready);
		if (isroomjoin && !isallready)
		{
			char ready[1];
			ready[0] = localplayer->isready ? 1 : 0;
			try 
			{
				sock.write_some(buffer(ready));
			}
			catch (boost::system::system_error e)
			{
				MessageBox("write", "wrong");
				log("%d", e.code());
			}
			//��ȡ����������
			char isready[1];
			sock.read_some(buffer(isready));
			log("isready=%d", isready[0]);
			if (isready[0])
			{
				isallready = true;
				break;
			}
		}
	}
}
void Client::ReadyMsg_thread()
{
	boost::thread ReadyMsg(boost::bind(&Client::ReadyMsg, this));
}

void Client::DealAndSnatchlandlord()
{
	try
	{
		while (true)
		{
			if (isallready)
			{
				if (!ishandreceive)
				{
					localplayer->hand.resize(17);
					sock.read_some(buffer(localplayer->hand));
					ishandreceive = true;
				}
				sock.read_some(buffer(now_choose));
				//Ŀǰ����ߵ�����
				for (int i = 0; i <= 2; i++)
				{
					if (localplayer->playercode == now_choose[0])
					{
						while (true)
						{
						    if (localplayer->lord_point != -1)
							{
								char local_lordpoint[1];
								local_lordpoint[0] = localplayer->lord_point;
								sock.write_some(buffer(local_lordpoint));
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
						sock.read_some(buffer(remote_lordpoint));
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
		//��ӵ�����
		vector<int>lord_poker(3);
		sock.read_some(buffer(lord_poker));
		localplayer->hand.push_back(lord_poker[0]);
		localplayer->hand.push_back(lord_poker[1]);
		localplayer->hand.push_back(lord_poker[2]);
		//localplayer���������Ϊ�����ƣ�localplayer�Ʋ���ʹ��
		islord = now_lord == localplayer->playercode ? 1 : 0;
		if (islord)
		{
			localscene->lord_first_play = true;
		}
	}
	catch (boost::system::system_error e)
	{
		MessageBox("new", "wrong");
		log("%d", e.code());
	}
}
void Client::DealAndSnatchlandlord_thread()
{
	boost::thread DealAndSnatchlandlord(boost::bind(&Client::DealAndSnatchlandlord, this));
}

void Client::Play()
{
	while (true)
	{
		if (isstart)
		{
			log("is=%d", isstart);
			now_play = now_lord;
			localscene->isadded = 0;
			//��ʼ��Ϸ
			while (true)
			{
				if (localplayer->playercode == now_play)
				{
					play_swith = true;
					//�ȴ����
					while (true)
					{
						if (localscene->isclick)
						{
							if (datas->isplay_pokers)
							{
								localscene->pokers_num[localplayer->playercode - 1] -= datas->card_amount;//��ȥ�Լ��ĳ���
							}
							//�������ݸ�������
							send_struct();
							localscene->isclick = false;
							now_play++;
							now_play = now_play > 3 ? (now_play - 3) : now_play;
							break;
						}
					}
				}
				else
				{
					read_struct();
					localscene->isrecv_struct = true;
				}
				boost::this_thread::sleep(boost::posix_time::millisec(500));
			}
		}
	}
}
void Client::Play_thread()
{
	boost::thread Play(boost::bind(&Client::Play, this));
}

//void Client::Ask_to_server()
//{
//	if (!GameScene::start)
//	{
//		string request = "clientstate";
//		if (localplayer->isready)
//		{
//			string msg = request + '\n' + '1';
//			sock.write_some(buffer(msg));
//			localplayer->isready = false;
//		}
//		else
//		{
//			string msg = request + '\n' + '0';
//			try
//			{
//				sock.write_some(buffer(msg));
//			}
//			catch (boost::system::system_error & err)
//			{
//				MessageBox("client write error", "client write error");
//			}
//			log("asked");
//		}
//
//		char recv_buff[512];
//		memset(recv_buff, 0, sizeof(recv_buff));
//		try 
//		{
//			sock.read_some(buffer(recv_buff));
//		}
//		catch (boost::system::system_error & err)
//		{
//			MessageBox("client read error","client read error");
//		}
//		memset(&datas, 0, sizeof(datas));//��ȡ֮ǰ���datas
//		memcpy(&datas, recv_buff, sizeof(datas));
//
//		log("%d", datas.isgamestart);
//
//		HandleAnswer_unstart();
//	}
//	else
//	{
//
//	}
//
//}
//void Client::HandleAnswer_unstart()
//{
//	if (datas.isgamestart)
//	{
//		GameScene::start = true;
//	}
//	if (localplayer->playercode == 2)
//	{
//		if (datas.player_num == 2 && isadd[0] == 0)
//		{
//			auto a_username = LabelTTF::create(datas.a_username, "arial", 30);
//			a_username->setPosition(45, 500);
//			localscene->addChild(a_username);
//			isadd[0] = 1;
//		}
//		else if (datas.player_num == 3 && isadd[1] == 0)
//		{
//			auto c_username = LabelTTF::create(datas.c_username, "arial", 30);
//			c_username->setPosition(1100, 500);
//			localscene->addChild(c_username);
//			isadd[1] = 1;
//		}
//	}
//	else if (localplayer->playercode == 3)
//	{
//
//		if (datas.player_num == 3 && isadd[0] == 0)
//		{
//			auto a_username = LabelTTF::create(datas.a_username, "arial", 30);
//			a_username->setPosition(1100, 500);
//			localscene->addChild(a_username);
//			isadd[0] = 1;
//
//			auto b_username = LabelTTF::create(datas.b_username, "arial", 30);
//			b_username->setPosition(45, 500);
//			localscene->addChild(b_username);
//			isadd[0] = 1;
//		}
//	}
//}
//
//void Client::CreateLoop()
//{
//	log("client loop");
//	while (1)
//	{
//		if (connect)
//		{
//			log("looping client");
//			Ask_to_server();
//		}
//	}
//}
//void Client::Loop_thread()
//{
//	boost::thread loop(boost::bind(&Client::CreateLoop, this));
//	
//}

void Client::AddLocalName()
{
	auto localusername = LabelTTF::create(localplayer->username, "arial", 30);
	localusername->setPosition(130, 40);
	localscene->addChild(localusername);
}
void Client::AddLeftName(string leftname)
{
	auto left_name = LabelTTF::create(leftname, "arial", 30);
	left_name->setPosition(70, 450);
	localscene->addChild(left_name);
}
void Client::AddRightName(string rightname)
{
	auto right_name = LabelTTF::create(rightname, "arial", 30);
	right_name->setPosition(1154, 450);
	localscene->addChild(right_name);
}

string Client::read_msg()
{
	char pre[512];
	int bytes = read(sock, buffer(pre), boost::bind(read_complete_client, pre, _1, _2));
	string msg(pre, bytes - 1);
	return msg;
}
void Client::read_struct()
{
	char rec_buff[512];
	memset(rec_buff, 0, sizeof(rec_buff));
	sock.read_some(buffer(rec_buff));
	memset(datas, 0, sizeof(*datas));
	memcpy(datas, rec_buff, sizeof(*datas));
}
void Client::send_struct()
{
	char msg[512];
	memset(msg, 0, sizeof(msg));
	memcpy(msg, datas, sizeof(*datas));
	sock.write_some(buffer(msg));
}