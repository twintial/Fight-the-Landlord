#include<LoginScene.h>
USING_NS_CC;
Scene* LoginScene::CreateHost()
{
	local = new Player();
	state = 1;
	return LoginScene::create();
}
Scene* LoginScene::CreateGuest()
{
	local = new Player();
	state = 0;
	return LoginScene::create();
}
bool LoginScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	InputUsername();
	if (!state)
	{
		InputConnectIP();//作为guest连接hostIP
	}
	else
	{
		GetLocalIP();//作为host连接本地IP
	}
	OKbutton();
	schedule(schedule_selector(LoginScene::timehandle),2);
	return true;
}
void LoginScene::timehandle(float t)
{
	log("%s",local->IP.c_str());
}//test
void LoginScene::InputUsername()
{
	//添加文本框背景
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("username.png");
	background->setPosition(visibleSize / 2);
	addChild(background);

	auto text = Text::create("", "arial", 25);
	text->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));
	addChild(text);

	auto tf = TextField::create("Enter your name", "arial", 30);
	tf->setTextColor(Color4B(0,102, 205, 170));
	tf->setMaxLength(15);
	tf->setMaxLengthEnabled(true);
	tf->setPosition(visibleSize / 2);
	addChild(tf);

	tf->addEventListener([=](Ref *pSender, TextField::EventType type)
	{
		int f = 0;
		switch (type)
		{
		case cocos2d::ui::TextField::EventType::ATTACH_WITH_IME:
		{
			text->setString("");
			break;
		}
		case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
		{
			local->username = tf->getString();
			if (local->username.length() == 0)
			{
				text->setString("Please enter your name");
			}
			break;
		}
		case cocos2d::ui::TextField::EventType::INSERT_TEXT:
			break;
		case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
			break;
		default:
			break;
		}

	});
}
void LoginScene::InputConnectIP()
{
	//添加文本框背景
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("IP.png");
	background->setPosition(visibleSize.width / 2 + 300, visibleSize.height / 2);
	addChild(background);

	auto text = Text::create("", "arial", 25);
	text->setPosition(Vec2(visibleSize.width / 2 + 300, visibleSize.height / 2 - 50));
	addChild(text);

	auto tf = TextField::create("Enter join IP", "arial", 20);
	tf->setTextColor(Color4B(0, 102, 205, 170));
	tf->setMaxLength(15);
	tf->setMaxLengthEnabled(true);
	tf->setPosition(Vec2(visibleSize.width / 2 + 310, visibleSize.height / 2));
	addChild(tf);

	tf->addEventListener([=](Ref *pSender, TextField::EventType type)
	{
		switch (type)
		{
		case cocos2d::ui::TextField::EventType::ATTACH_WITH_IME:
		{
			text->setString("");
			break;
		}
		case cocos2d::ui::TextField::EventType::DETACH_WITH_IME:
		{
			local->IP = tf->getString();
			if (local->IP.length() == 0)
			{
				text->setString("Please enter correct IP");
			}
			break;
		}
		case cocos2d::ui::TextField::EventType::INSERT_TEXT:
			break;
		case cocos2d::ui::TextField::EventType::DELETE_BACKWARD:
			break;
		default:
			break;
		}

	});
}
void LoginScene::EnterGameScene(Ref *pSender)
{
	if (local->IP != ""&&local->username != "")
	{
		Director::getInstance()->pushScene(GameScene::CreateScene());
	}
}
void LoginScene::OKbutton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto button = Sprite::create("OKbutton.png");
	auto menuitem = MenuItemSprite::create(button, button, CC_CALLBACK_1(LoginScene::EnterGameScene, this));
	auto menu = Menu::create(menuitem, NULL);
	menu->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 300);
	addChild(menu);

}
int LoginScene::GetLocalIP()
{
	char host_name[255];
	if (gethostname(host_name, sizeof(host_name)) == SOCKET_ERROR)
	{

		log("Error %d when getting local host name\n", WSAGetLastError());
		return -1;
	}
	log("host name:%s\n", host_name);
	struct hostent *phe = gethostbyname(host_name);
	if (phe == 0)
	{

		log("Error host lookup\n");
		return -1;
	}

	struct in_addr addr;
	memcpy(&addr, phe->h_addr_list[1], sizeof(struct in_addr));
	local->IP = inet_ntoa(addr);
	return 1;
}//（若创建房间则连接本地IP）获取本地IP
size_t LoginScene::state;
Player* LoginScene::local;