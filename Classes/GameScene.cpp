#include"GameScene.h"
#include"PokerCard.h"
USING_NS_CC;
Client * local_client;
Server * local_server;
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

	schedule(schedule_selector(GameScene::timehandle),0.1);//
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
	//test
	//auto a = local_server->localplayer;
	//auto b = new Player();
	//auto c = new Player();
	//Operation::CardShuffle(card);vf54321145y78
	//Operation::CardDeal(*a, *b, *c, card);
	//Operation::CardSort(*a);

	//auto sb = SkipButton();
	//auto pb = PlayButton();
	//a->Action(sb, pb, this);
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
void GameScene::timehandle(float t)
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
			ArrangePokers_1(local->handpoker);
			auto sb = SkipButton();
			auto pb = PlayButton();
			local->Action(sb, pb, this);
			this->unschedule(schedule_selector(GameScene::timehandle));
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
			ArrangePokers_1(local->handpoker);
			auto sb = SkipButton();
			auto pb = PlayButton();
			local->Action(sb, pb, this);
			this->unschedule(schedule_selector(GameScene::timehandle));
		}
	}
}
Sprite* GameScene::PointButton_0()
{
	auto point_zero= Sprite::create("point_0.png");
	point_zero->setPosition(200, 500);
	addChild(point_zero);
	return point_zero;
}//未添加的sprite
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
void GameScene::ArrangePokers_1(vector<PokerCard>& handpoker)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	handpoker[handpoker.size() / 2].card_picture->setPosition(visibleSize.width / 2, 150);//set center poker
	size_t cx = handpoker[handpoker.size() / 2].card_picture->getPositionX();
	for (int i = 0; i <= handpoker.size() - 1; i++)
	{
		handpoker[i].card_picture->setPosition(cx - 50 * (i - (handpoker.size() / 2)), 150);
	}
	for (int i = 0; i <= 16; i++)
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
vector<int> GameScene::card;