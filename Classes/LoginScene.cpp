#include<LoginScene.h>
USING_NS_CC;
size_t LoginScene::state;
Player* LoginScene::local;
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
	SettingBackground();
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
	ReturnButton();
	SettingButton();
	schedule(schedule_selector(LoginScene::timehandle),2);//输出IP
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
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
	addChild(background);

	auto text = Text::create("", "arial", 25);
	text->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 40));
	addChild(text);

	name_tf = TextField::create("Enter your name", "arial", 30);
	name_tf->setTextColor(Color4B(0,102, 205, 170));
	name_tf->setMaxLength(10);
	name_tf->setMaxLengthEnabled(true);
	name_tf->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
	addChild(name_tf);

	name_tf->addEventListener([=](Ref *pSender, TextField::EventType type)
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
			local->username = name_tf->getString();
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
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 10));
	addChild(background);

	auto text = Text::create("", "arial", 25);
	text->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));
	addChild(text);

	IP_tf = TextField::create("          ", "arial", 20);
	IP_tf->setTextColor(Color4B::BLACK);
	IP_tf->setMaxLength(15);
	IP_tf->setMaxLengthEnabled(true);
	IP_tf->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 10));
	addChild(IP_tf);

	IP_tf->addEventListener([=](Ref *pSender, TextField::EventType type)
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
			local->IP = IP_tf->getString();
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
	local->username = name_tf->getString();
	if (!state)
	{
		local->IP = IP_tf->getString();
	}
	if (local->IP != ""&&local->username != "")
	{
	/*	SimpleAudioEngine::getInstance()->stopBackgroundMusic();*/
		Director::getInstance()->pushScene(GameScene::CreateScene());
	}
}
void LoginScene::ReturnChooseScene(Ref *pSender)
{
	Director::getInstance()->popScene();
}
void LoginScene::EnterSettingScene(Ref *pSender)
{
	Director::getInstance()->pushScene(SettingScene::CreateScene());
}
void LoginScene::OKbutton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto button = Sprite::create("OKbutton.png");
	auto menuitem = MenuItemSprite::create(button, button, CC_CALLBACK_1(LoginScene::EnterGameScene, this));
	auto menu = Menu::create(menuitem, NULL);
	menu->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 170);
	addChild(menu);
}
void LoginScene::ReturnButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto button = Sprite::create("return.png");
	auto returnItem = MenuItemSprite::create(button, button, CC_CALLBACK_1(LoginScene::ReturnChooseScene, this));
	auto menu = Menu::create(returnItem, NULL);
	menu->setPosition(visibleSize.width - returnItem->getContentSize().width / 2, visibleSize.height - returnItem->getContentSize().height / 2);
	this->addChild(menu);
}
void LoginScene::SettingButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto button = Sprite::create("settings1.png");
	auto menuitem = MenuItemSprite::create(button, button, CC_CALLBACK_1(LoginScene::EnterSettingScene, this));
	auto menu = Menu::create(menuitem, NULL);
	menu->setPosition(menuitem->getContentSize().width / 2 + 30, visibleSize.height - menuitem->getContentSize().height / 2 - 30);
	this->addChild(menu);
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
	memcpy(&addr, phe->h_addr_list[0], sizeof(struct in_addr));
	local->IP = inet_ntoa(addr);
	return 1;
}//（若创建房间则连接本地IP）获取本地IP
void LoginScene::SettingBackground()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("Lbackground.jpg");
	//background->setScale(1.2f);
	background->setPosition(visibleSize / 2);
	this->addChild(background);
}