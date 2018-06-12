#include"GameScene.h"
#include"PokerCard.h"
USING_NS_CC;
Client * local_client;
Server * local_server;
vector<int> GameScene::card;
Button* a;
Button* b;
Button* c;
Button* d;
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
	//创建连接服务器
	if (LoginScene::state)
	{
		local_server->Accept_thread();
	}
	else
	{
		local_client->Connect_thread();
	}
	//数据传输
	//准备状况
	if (LoginScene::state)
	{
		local_server->ReadyMsg_thread();
	}
	else
	{
		local_client->ReadyMsg_thread();
	}
	//发牌，抢地主
	if (LoginScene::state)
	{
		local_server->DealAndSnatchlandlord_thread();
	}
	else
	{
		local_client->DealAndSnatchlandlord_thread();
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
				lord_mark->runAction(MoveTo::create(1, Point(visibleSize.width / 2 + delta * 580, 550)));
			}
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
					lord_mark->runAction(MoveTo::create(1, Point(visibleSize.width / 2 + delta * 580, 550)));
				}
				else
				{
					int delta = local_client->now_lord == 2 ? -1 : 1;
					lord_mark->runAction(MoveTo::create(1, Point(visibleSize.width / 2 + delta * 580, 550)));
				}
			}
			this->unschedule(schedule_selector(GameScene::ArrangePoker_lord));
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

Sprite* GameScene::SkipButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto skip_button = Sprite::create("skipbutton.png");
	skip_button->setPosition(visibleSize.width / 2 + 140, 305);
	skip_button->setScale(0.78f);
	addChild(skip_button);
	return skip_button;
}//在operation中实现操作因此返回sprite
Sprite* GameScene::PlayButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto play_button = Sprite::create("playbutton.png");
	play_button->setPosition(visibleSize.width / 2 - 140, 305);
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
bool GameScene::ArrangeoutPokers(Player* x)
{
	if (x->outpoker.size() == 0)
	{
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();
	x->outpoker[x->outpoker.size() / 2].m_card_picture->setPosition(visibleSize.width / 2, 300);
	size_t cx = x->outpoker[x->outpoker.size() / 2].m_card_picture->getPositionX();
	for (int i = 0; i <= x->outpoker.size() - 1; i++)
	{
		x->outpoker[i].m_card_picture->setPosition(cx + 30 * (i - (x->outpoker.size() / 2)), 300);
	}
	for (int i = 0; i <= x->outpoker.size() - 1; i++)
	{
		addChild(x->outpoker[i].m_card_picture);
	}
	x->outpoker.erase(x->outpoker.begin(), x->outpoker.end());//在以后需要改动
	return true;
}