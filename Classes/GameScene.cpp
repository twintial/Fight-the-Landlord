#include"GameScene.h"
USING_NS_CC;
Client * local_client;
Server * local_server;
vector<int> GameScene::card;
vector<PokerCard> left_pokers;
vector<PokerCard> right_pokers;
Button* a;
Button* b;
Button* c;
Button* d;
Button* skip;
Button* play;
Sprite* left_skip;
Sprite* right_skip;
LabelTTF* playing;//等待出牌
LabelTTF* left_num;//左边的牌数显示
LabelTTF* right_num;//右边的牌数显示

Scene* GameScene::CreateScene()
{
	return GameScene::create();
}
bool GameScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	//SimpleAudioEngine::getInstance()->playBackgroundMusic("game_bgm.mp3", true);
	lord_first_play = false;
    isclick = false;
	isrecv_struct = false;
	isadded = -1;
	for (int i = 0; i <= 2; i++)
	{
		pokers_num.push_back(-1);
	}
	if (LoginScene::state)
	{
		local_server = new Server(LoginScene::local, this);
	}
	else
	{
		local_client = new Client(LoginScene::local, this);
	}
	local = new Player();
	Settingbackgroud();
	ReadyButton();

	schedule(schedule_selector(GameScene::ArrangePoker_before),0.1);
	schedule(schedule_selector(GameScene::ArrangePoker_lord), 0.1);
	schedule(schedule_selector(GameScene::ArrangeLordbutton), 0.1);
	schedule(schedule_selector(GameScene::LocalPlay), 0.1);
	//创建连接服务器
	if (LoginScene::state)
	{
		//创建连接服务器
		local_server->Accept_thread();
		//准备状况
		local_server->ReadyMsg_thread();
		//发牌，抢地主
		local_server->DealAndSnatchlandlord_thread();
		//开始游戏
		local_server->Play_thread();
	}
	else
	{
		local_client->Connect_thread();
		//准备状况
		local_client->ReadyMsg_thread();
		//发牌，抢地主
		local_client->DealAndSnatchlandlord_thread();
		//开始游戏
		local_client->Play_thread();
	}
	return true;
}
void GameScene::Settingbackgroud()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto background = Sprite::create("background.png");
	background->setPosition(visibleSize / 2);
	this->addChild(background);
}

void GameScene::ArrangePoker_before(float t)
{
	if (LoginScene::state)
	{
		if (local_server->ishandsend)
		{
			local->hand.resize(17);
			for (int i = 0; i <= 16; i++)
			{
				local->hand[i] = local_server->localplayer->hand[i];
			}
			Operation::CardSort(*local);
			ArrangePokers(local->handpoker);
			this->unschedule(schedule_selector(GameScene::ArrangePoker_before));
		}
	}
	else
	{
		if (local_client->ishandreceive)
		{
			local->hand.resize(17);
			for (int i = 0; i <= 16; i++)
			{
				local->hand[i] = local_client->localplayer->hand[i];
			}
			Operation::CardSort(*local);
			ArrangePokers(local->handpoker);
			this->unschedule(schedule_selector(GameScene::ArrangePoker_before));
		}
	}
}
void GameScene::ArrangeLordbutton(float t)
{
	if (LoginScene::state)
	{
		if (local_server->localplayer->playercode == local_server->now_choose[0])
		{
			a = PointButton_0();
			b = PointButton_1();
			c = PointButton_2();
			d = PointButton_3();
			if (local_server->max_point == 1)
			{
				b->setBright(false);
				b->setTouchEnabled(false);
			}
			else if (local_server->max_point == 2)
			{
				b->setBright(false);
				b->setTouchEnabled(false);
				c->setBright(false);
				c->setTouchEnabled(false);
			}
			this->unschedule(schedule_selector(GameScene::ArrangeLordbutton));
		}
	}
	else
	{
		if (local_client->localplayer->playercode == local_client->now_choose[0])
		{
			a = PointButton_0();
			b = PointButton_1();
			c = PointButton_2();
			d = PointButton_3();
			if (local_client->max_point == 1)
			{
				b->setBright(false);
				b->setTouchEnabled(false);
			}
			else if (local_client->max_point == 2)
			{
				b->setBright(false);
				b->setTouchEnabled(false);
				c->setBright(false);
				c->setTouchEnabled(false);
			}
			this->unschedule(schedule_selector(GameScene::ArrangeLordbutton));
		}
	}
}
void GameScene::ArrangePoker_lord(float t)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto lord_mark = Sprite::create("lordmark.png");
	lord_mark->setPosition(visibleSize / 2);
	if (LoginScene::state)
	{
		if (local_server->islord != -1)
		{
			addChild(lord_mark);
			//在屏幕最上方添加地主牌
			auto temp_player = Player();
			temp_player.hand.resize(3);
			for (int i = 0; i <= 2; i++)
			{
				temp_player.hand[i] = local_server->localplayer->hand[i + 17];
			}
			Operation::CardSort(temp_player);
			for (int i = 0; i <= 2; i++)
			{
				temp_player.handpoker[i].m_card_picture->setPosition(visibleSize.width / 2 + 30 * (i - 1), visibleSize.height / 2 + 300);
				addChild(temp_player.handpoker[i].m_card_picture);
			}


			if (local_server->islord)
			{
				for (int i = 0; i <= 16; i++)
				{
					local->handpoker[i].card_picture->removeFromParent();
				}
				local->hand.resize(20);
				local->handpoker.erase(local->handpoker.begin(), local->handpoker.end());
				for (int i = 0; i <= 19; i++)
				{
					local->hand[i] = local_server->localplayer->hand[i];//这三张牌就是local_server->localplayer->hand[i]的最后三张
				}
				Operation::CardSort(*local);
				ArrangePokers(local->handpoker);
				//使地主牌突出
				for (int i = 0; i <= local->handpoker.size() - 1; i++)
				{
					for (int j = 0; j <= 2; j++)
					{
						if (local->handpoker[i].num == local_server->localplayer->hand[j + 17])
						{
							local->handpoker[i].card_picture->setPosition(local->handpoker[i].card_picture->getPositionX(), local->handpoker[i].card_picture->getPositionY() + 28);
							local->handpoker[i].iostates = 1;
						}
					}
				}
				//添加地主标志
				lord_mark->runAction(MoveTo::create(1, Point(60, 80)));
			}
			else
			{
				int delta = local_server->now_lord == 3 ? -1 : 1;
				lord_mark->runAction(MoveTo::create(1, Point(visibleSize.width / 2 + delta * 570, 550)));
			}
			//添加牌数背景
			auto back_left = Sprite::create("back.png");
			back_left->setPosition(80, 500);
			addChild(back_left);
			auto back_right = Sprite::create("back.png");
			back_right->setPosition(1142, 500);
			addChild(back_right);
			//添加牌数
			for (int i = 0; i <= 2; i++)
			{
				if (i == local_server->now_lord - 1)
				{
					pokers_num[i] = 20;
				}
				else
				{
					pokers_num[i] = 17;
				}
			}
			left_num = LabelTTF::create(to_string(pokers_num[2]), "arial", 25);
			right_num = LabelTTF::create(to_string(pokers_num[1]), "arial", 25);
			left_num->setPosition(80, 500);
			right_num->setPosition(1142, 500);
			addChild(left_num);
			addChild(right_num);

			local_server->isstart = true;
			this->unschedule(schedule_selector(GameScene::ArrangePoker_lord));
		}
	}
	else
	{
		if (local_client->islord != -1)
		{
			addChild(lord_mark);
			//在屏幕最上方添加地主牌
			auto temp_player = Player();
			temp_player.hand.resize(3);
			for (int i = 0; i <= 2; i++)
			{
				temp_player.hand[i] = local_client->localplayer->hand[i + 17];
			}
			Operation::CardSort(temp_player);
			for (int i = 0; i <= 2; i++)
			{
				temp_player.handpoker[i].m_card_picture->setPosition(visibleSize.width / 2 + 30 * (i - 1), visibleSize.height / 2 + 300);
				addChild(temp_player.handpoker[i].m_card_picture);
			}

			if (local_client->islord)
			{
				for (int i = 0; i <= 16; i++)
				{
					local->handpoker[i].card_picture->removeFromParent();
				}
				local->hand.resize(20);
				local->handpoker.erase(local->handpoker.begin(), local->handpoker.end());
				for (int i = 0; i <= 19; i++)
				{
					local->hand[i] = local_client->localplayer->hand[i];
				}
				Operation::CardSort(*local);
				ArrangePokers(local->handpoker);
				//使地主牌突出
				for (int i = 0; i <= local->handpoker.size() - 1; i++)
				{
					for (int j = 0; j <= 2; j++)
					{
						if (local->handpoker[i].num == local_client->localplayer->hand[j + 17])
						{
							local->handpoker[i].card_picture->setPosition(local->handpoker[i].card_picture->getPositionX(), local->handpoker[i].card_picture->getPositionY() + 28);
							local->handpoker[i].iostates = 1;
						}
					}
				}
				lord_mark->runAction(MoveTo::create(1, Point(60, 80)));
			}
			else
			{
				if (local_client->localplayer->playercode == 2)
				{
					int delta = local_client->now_lord == 1 ? -1 : 1;
					lord_mark->runAction(MoveTo::create(1, Point(visibleSize.width / 2 + delta * 570, 550)));
				}
				else
				{
					int delta = local_client->now_lord == 2 ? -1 : 1;
					lord_mark->runAction(MoveTo::create(1, Point(visibleSize.width / 2 + delta * 570, 550)));
				}
			}
			//添加牌数背景
			auto back_left = Sprite::create("back.png");
			back_left->setPosition(80, 500);
			addChild(back_left);
			auto back_right = Sprite::create("back.png");
			back_right->setPosition(1142, 500);
			addChild(back_right);
			//添加牌数
			for (int i = 0; i <= 2; i++)
			{
				if (i == local_client->now_lord - 1)
				{
					pokers_num[i] = 20;
				}
				else
				{
					pokers_num[i] = 17;
				}
			}
			left_num = LabelTTF::create(to_string(pokers_num[local_client->localplayer->playercode - 2]), "arial", 25);
			right_num = LabelTTF::create(to_string(pokers_num[local_client->localplayer->playercode == 2 ? 2 : 0]), "arial", 25);
			left_num->setPosition(80, 500);
			right_num->setPosition(1142, 500);
			addChild(left_num);
			addChild(right_num);

			local_client->isstart = true;
			this->unschedule(schedule_selector(GameScene::ArrangePoker_lord));
		}
	}
}
void GameScene::LocalPlay(float t)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	if (LoginScene::state)
	{
		if (local_server->play_swith)
		{
			ClearOutPokers(local->outpoker);
			skip = SkipButton();
			play = PlayButton();
			local->Action(skip, play, local_server->datas, this);
			if ((getChildByTag(1) != NULL && getChildByTag(2) != NULL) || lord_first_play)
			{
				skip->setBright(false);
				skip->setTouchEnabled(false);
				//可以出任意合理牌
				local_server->datas->card_type = 0;
				lord_first_play = false;
			}
			local_server->play_swith = false;
		}
		else
		{
			//添加waiting
			if (isadded == 0)
			{
				playing = LabelTTF::create("waiting...", "arial", 30);
				if (local_server->now_play == 2)
				{
					playing->setPosition(1050, 600);
					addChild(playing);
					isadded = 1;
				}
				else if (local_server->now_play == 3)
				{
					playing->setPosition(174, 600);
					addChild(playing);
					isadded = 1;
				}
			}
			//接收别人的datas数据包，将其他玩家打的牌加入屏幕中
			if (isrecv_struct)
			{
				if (!local_server->datas->isplay_pokers)
				{
					//添加不出
					if (local_server->now_play == 2)
					{
						ClearOutPokers(right_pokers);
						//添加右边不出
						right_skip = Sprite::create("skip.png");
						right_skip->setTag(2);
						right_skip->setPosition(1050, 520);
						addChild(right_skip);
					}
					else
					{
						ClearOutPokers(left_pokers);
						//添加左边不出
						left_skip = Sprite::create("skip.png");
						left_skip->setTag(1);
						left_skip->setPosition(174, 520);
						addChild(left_skip);
					}
				}
				else
				{
					//添加这位玩家出的牌
					if (local_server->now_play == 2)
					{
						ClearOutPokers(right_pokers);
						for (int i = 0; i <= local_server->datas->card_amount - 1; i++)
						{
							right_pokers.push_back(PokerCard(local_server->datas->out_poker[i]));
						}
						ArrangeOutPokers_remote_right(right_pokers);
						//将出牌数减去
						pokers_num[1] -= local_server->datas->card_amount;
						right_num->setString(to_string(pokers_num[1]));
					}
					else
					{
						ClearOutPokers(left_pokers);
						for (int i = 0; i <= local_server->datas->card_amount - 1; i++)
						{
							left_pokers.push_back(PokerCard(local_server->datas->out_poker[i]));
						}
						ArrangeOutPokers_remote_left(left_pokers);
						//将出牌数减去
						pokers_num[2] -= local_server->datas->card_amount;
						left_num->setString(to_string(pokers_num[2]));
					}
				}
				isrecv_struct = false;
				local_server->now_play++;
				local_server->now_play = local_server->now_play > 3 ? (local_server->now_play - 3) : local_server->now_play;
				//移除等待出牌
				playing->removeFromParent();
				isadded = 0;
			}
		}
		//判断是否有人出完
		for (int i = 0; i <= 2; i++)
		{
			if (pokers_num[i] == 0)
			{
				if (i == local_server->now_lord - 1)
				{
					//地主赢，判断自己是地主还是农民
					if (local_server->islord)
					{
						auto win_logo = Sprite::create("win.png");
						win_logo->setPosition(visibleSize / 2);
						addChild(win_logo);
					}
					else
					{
						auto lose_logo = Sprite::create("lose.png");
						lose_logo->setPosition(visibleSize / 2);
						addChild(lose_logo);
					}
				}
				else
				{
					if (local_server->islord)
					{
						auto lose_logo = Sprite::create("lose.png");
						lose_logo->setPosition(visibleSize / 2);
						addChild(lose_logo);
					}
					else
					{
						auto win_logo = Sprite::create("win.png");
						win_logo->setPosition(visibleSize / 2);
						addChild(win_logo);
					}
				}
				this->unschedule(schedule_selector(GameScene::LocalPlay));
			}
		}
	}
	else
	{
		if (local_client->play_swith)
		{
			ClearOutPokers(local->outpoker);
			skip = SkipButton();
			play = PlayButton();
			local->Action(skip, play, local_client->datas, this);
			if ((getChildByTag(1) != NULL && getChildByTag(2) != NULL) || lord_first_play)
			{
				skip->setBright(false);
				skip->setTouchEnabled(false);
				//可以出任意合理牌
				local_client->datas->card_type = 0;
				lord_first_play = false;
			}
			local_client->play_swith = false;
		}
		else
		{
			//添加waiting
			if (isadded == 0)
			{
				playing = LabelTTF::create("waiting...", "arial", 30);
				if (local_client->localplayer->playercode == 2)
				{
					if (local_client->now_play == 1)
					{
						playing->setPosition(174, 600);
						addChild(playing);
						isadded = 1;
					}
					else if (local_client->now_play == 3)
					{
						playing->setPosition(1050, 600);
						addChild(playing);
						isadded = 1;
					}
				}
				else
				{
					if (local_client->now_play == 2)
					{
						playing->setPosition(174, 600);
						addChild(playing);
						isadded = 1;
					}
					else if (local_client->now_play == 1)
					{
						playing->setPosition(1050, 600);
						addChild(playing);
						isadded = 1;
					}
				}
			}
			//如果接受到了数据包
			if (isrecv_struct)
			{
				log("isplay?=%d", local_client->datas->isplay_pokers);
				if (!local_client->datas->isplay_pokers)
				{
					//添加不出
					if (local_client->localplayer->playercode == 2)
					{
						if (local_client->now_play == 1)
						{
							ClearOutPokers(left_pokers);
							//添加左边不出
							left_skip = Sprite::create("skip.png");
							left_skip->setTag(1);
							left_skip->setPosition(174, 520);
							addChild(left_skip);
						}
						else
						{
							ClearOutPokers(right_pokers);
							//添加右边不出
							right_skip = Sprite::create("skip.png");
							right_skip->setTag(2);
							right_skip->setPosition(1050, 520);
							addChild(right_skip);
						}
					}
					else
					{
						if (local_client->now_play == 2)
						{
							ClearOutPokers(left_pokers);
							//添加左边不出
							left_skip = Sprite::create("skip.png");
							left_skip->setTag(1);
							left_skip->setPosition(174, 520);
							addChild(left_skip);
						}
						else
						{
							ClearOutPokers(right_pokers);
							//添加右边不出
							right_skip = Sprite::create("skip.png");
							right_skip->setTag(2);
							right_skip->setPosition(1050, 520);
							addChild(right_skip);
						}
					}
				}
				else
				{
					//添加这位玩家出的牌
					if (local_client->localplayer->playercode == 2)
					{
						if (local_client->now_play == 1)
						{
							ClearOutPokers(left_pokers);
							for (int i = 0; i <= local_client->datas->card_amount - 1; i++)
							{
								left_pokers.push_back(PokerCard(local_client->datas->out_poker[i]));
							}
							ArrangeOutPokers_remote_left(left_pokers);
							//减去出牌数
							pokers_num[0] -= local_client->datas->card_amount;
							left_num->setString(to_string(pokers_num[0]));
						}
						else
						{
							ClearOutPokers(right_pokers);
							for (int i = 0; i <= local_client->datas->card_amount - 1; i++)
							{
								right_pokers.push_back(PokerCard(local_client->datas->out_poker[i]));
							}
							ArrangeOutPokers_remote_right(right_pokers);
							//减去出牌数
							pokers_num[2] -= local_client->datas->card_amount;
							right_num->setString(to_string(pokers_num[2]));
						}
					}
					else
					{
						if (local_client->now_play == 2)
						{
							ClearOutPokers(left_pokers);
							for (int i = 0; i <= local_client->datas->card_amount - 1; i++)
							{
								left_pokers.push_back(PokerCard(local_client->datas->out_poker[i]));
							}
							ArrangeOutPokers_remote_left(left_pokers);
							//减去出牌数
							pokers_num[1] -= local_client->datas->card_amount;
							left_num->setString(to_string(pokers_num[1]));
						}
						else
						{
							ClearOutPokers(right_pokers);
							for (int i = 0; i <= local_client->datas->card_amount - 1; i++)
							{
								right_pokers.push_back(PokerCard(local_client->datas->out_poker[i]));
							}
							ArrangeOutPokers_remote_right(right_pokers);
							//减去出牌数
							pokers_num[0] -= local_client->datas->card_amount;
							right_num->setString(to_string(pokers_num[0]));
						}
					}
				}
				isrecv_struct = false;
				local_client->now_play++;
				local_client->now_play = local_client->now_play > 3 ? (local_client->now_play - 3) : local_client->now_play;
				//移除等待出牌
				playing->removeFromParent();
				isadded = 0;
			}
		}
		//判断是否有人出完
		for (int i = 0; i <= 2; i++)
		{
			if (pokers_num[i] == 0)
			{
				if (i == local_client->now_lord - 1)
				{
					//地主赢，判断自己是地主还是农民
					if (local_client->islord)
					{
						auto win_logo = Sprite::create("win.png");
						win_logo->setPosition(visibleSize / 2);
						addChild(win_logo);
					}
					else
					{
						auto lose_logo = Sprite::create("lose.png");
						lose_logo->setPosition(visibleSize / 2);
						addChild(lose_logo);
					}
				}
				else
				{
					if (local_client->islord)
					{
						auto lose_logo = Sprite::create("lose.png");
						lose_logo->setPosition(visibleSize / 2);
						addChild(lose_logo);
					}
					else
					{
						auto win_logo = Sprite::create("win.png");
						win_logo->setPosition(visibleSize / 2);
						addChild(win_logo);
					}
				}
				this->unschedule(schedule_selector(GameScene::LocalPlay));
			}
		}
	}
}

Button* GameScene::SkipButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto skip_button = Button::create("skipbutton.png");
	skip_button->setPosition(Vec2(visibleSize.width / 2 + 140, 305));
	skip_button->setScale(0.78f);
	addChild(skip_button);
	return skip_button;
}//在operation中实现操作因此返回sprite
Button* GameScene::PlayButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto play_button = Button::create("playbutton.png");
	play_button->setPosition(Vec2(visibleSize.width / 2 - 140, 305));
	play_button->setScale(0.78f);
	addChild(play_button);
	return play_button;
}//在operation中实现操作因此返回sprite
void GameScene::ReadyButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto ready_button = Button::create("ready.png");
	ready_button->setPosition(Vec2(visibleSize.width / 2, 305));
	ready_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::ENDED:
			if (LoginScene::state)
			{
				local_server->localplayer->isready = true;
			}
			else
			{
				local_client->localplayer->isready = true;
			}
			ready_button->removeFromParent();
		}
	});
	addChild(ready_button);
}//在此scene中实现功能

Button* GameScene::PointButton_0()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto zero_button = Button::create("point_0.png");
	zero_button->setPosition(Vec2(visibleSize.width / 2 - 300, 305));
	zero_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::ENDED:
			if (LoginScene::state)
			{
				local_server->localplayer->lord_point = 0;
			}
			else
			{
				local_client->localplayer->lord_point = 0;
			}
			a->removeFromParent();
			b->removeFromParent();
			c->removeFromParent();
			d->removeFromParent();
		}
	});
	addChild(zero_button);
	return zero_button;
}
Button* GameScene::PointButton_1()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto one_button = Button::create("point_1.png");
	one_button->setPosition(Vec2(visibleSize.width / 2 - 100, 305));
	one_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::ENDED:
			if (LoginScene::state)
			{
				local_server->localplayer->lord_point = 1;
			}
			else
			{
				local_client->localplayer->lord_point = 1;
			}
			a->removeFromParent();
			b->removeFromParent();
			c->removeFromParent();
			d->removeFromParent();
		}
	});
	addChild(one_button);
	return one_button;
}
Button* GameScene::PointButton_2()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto two_button = Button::create("point_2.png");
	two_button->setPosition(Vec2(visibleSize.width / 2 + 100, 305));
	two_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::ENDED:
			if (LoginScene::state)
			{
				local_server->localplayer->lord_point = 2;
			}
			else
			{
				local_client->localplayer->lord_point = 2;
			}
			a->removeFromParent();
			b->removeFromParent();
			c->removeFromParent();
			d->removeFromParent();
		}
	});
	addChild(two_button);
	return two_button;
}
Button* GameScene::PointButton_3()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto three_button = Button::create("point_3.png");
	three_button->setPosition(Vec2(visibleSize.width / 2 + 300, 305));
	three_button->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case Widget::TouchEventType::ENDED:
			if (LoginScene::state)
			{
				local_server->localplayer->lord_point = 3;
			}
			else
			{
				local_client->localplayer->lord_point = 3;
			}
			a->removeFromParent();
			b->removeFromParent();
			c->removeFromParent();
			d->removeFromParent();
		}
	});
	addChild(three_button);
	return three_button;
}

void GameScene::ArrangePokers(vector<PokerCard>& handpoker)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	handpoker[handpoker.size() / 2].card_picture->setPosition(visibleSize.width / 2, 150);//set center poker
	size_t cx = handpoker[handpoker.size() / 2].card_picture->getPositionX();
	for (int i = 0; i <= handpoker.size() - 1; i++)
	{
		handpoker[i].card_picture->setPosition(cx - 50 * (i - (handpoker.size() / 2)), 150);
	}
	for (int i = 0; i <= handpoker.size() - 1; i++)//16
	{
		handpoker[i].ClickTrigger();
		this->addChild(handpoker[i].card_picture, handpoker.size() - 1 - i);
	}
}
void GameScene::ArrangeHandPokers_afterplay(Player* x)
{
	for (int i = 0; i <= x->handpoker.size() - 1; i++)
	{
		if (x->handpoker[i].played == 1)
		{
			for (int j = 0; j <= x->handpoker.size() - 1; j++)
			{
				if (x->handpoker[j].played == 0)
				{
					int delta = j < i ? -1 : 1;
					x->handpoker[j].card_picture->runAction(MoveBy::create(0.01, Point(delta * 25, 0)));
				}
			}
			x->handpoker[i].played = -1;
		}
	}
}
bool GameScene::ArrangeOutPokers(Player* x)
{
	if (x->outpoker.size() == 0)
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	x->outpoker[x->outpoker.size() / 2].m_card_picture->setPosition(visibleSize.width / 2, 320);
	size_t cx = x->outpoker[x->outpoker.size() / 2].m_card_picture->getPositionX();
	for (int i = 0; i <= x->outpoker.size() - 1; i++)
	{
		x->outpoker[i].m_card_picture->setPosition(cx + 30 * (i - (x->outpoker.size() / 2)), 320);
	}
	for (int i = 0; i <= x->outpoker.size() - 1; i++)
	{
		addChild(x->outpoker[i].m_card_picture);
	}
	//x->outpoker.erase(x->outpoker.begin(), x->outpoker.end());//在以后需要改动
	return true;
}
bool GameScene::ArrangeOutPokers_remote_left(vector<PokerCard> &remote_outpoker)
{
	if (remote_outpoker.size() == 0)
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	remote_outpoker[0].m_card_picture->setPosition(visibleSize.width / 2 - 460, 520);
	size_t cx = remote_outpoker[0].m_card_picture->getPositionX();
	for (int i = 0; i <= remote_outpoker.size() - 1; i++)
	{
		remote_outpoker[i].m_card_picture->setPosition(cx + 30 * i, 520);
	}
	for (int i = 0; i <= remote_outpoker.size() - 1; i++)
	{
		addChild(remote_outpoker[i].m_card_picture);
	}
	return true;
}
bool GameScene::ArrangeOutPokers_remote_right(vector<PokerCard> &remote_outpoker)
{
	if (remote_outpoker.size() == 0)
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	remote_outpoker[remote_outpoker.size() - 1].m_card_picture->setPosition(visibleSize.width / 2 + 460, 520);
	size_t cx = remote_outpoker[remote_outpoker.size() - 1].m_card_picture->getPositionX();
	for (int i = 0; i <= remote_outpoker.size() - 1; i++)
	{
		remote_outpoker[i].m_card_picture->setPosition(cx - 30 * (remote_outpoker.size() - 1 - i), 520);
	}
	for (int i = 0; i <= remote_outpoker.size() - 1; i++)
	{
		addChild(remote_outpoker[i].m_card_picture);
	}
	return true;
}
void GameScene::ClearOutPokers(vector<PokerCard> &outpokers)
{
	if (LoginScene::state)
	{
		if (local_server->now_play == 2)
		{
			if (getChildByTag(2) != NULL)
			{
				right_skip->removeFromParent();
			}
		}
		else if (local_server->now_play == 3)
		{
			if (getChildByTag(1) != NULL)
			{
				left_skip->removeFromParent();
			}
		}
	}
	else if (local_client->localplayer->playercode == 2)
	{
		if (local_client->now_play == 3)
		{
			if (getChildByTag(2) != NULL)
			{
				right_skip->removeFromParent();
			}
		}
		else if (local_client->now_play == 1)
		{
			if (getChildByTag(1) != NULL)
			{
				left_skip->removeFromParent();
			}
		}
	}
	else if (local_client->localplayer->playercode == 3)
	{
		if (local_client->now_play == 1)
		{
			if (getChildByTag(2) != NULL)
			{
				right_skip->removeFromParent();
			}
		}
		else if (local_client->now_play == 2)
		{
			if (getChildByTag(1) != NULL)
			{
				left_skip->removeFromParent();
			}
		}
	}
	if (!outpokers.empty())
	{
		for (int i = 0; i <= outpokers.size() - 1; i++)
		{
			outpokers[i].m_card_picture->removeFromParent();
		}
		outpokers.erase(outpokers.begin(), outpokers.end());
	}
}