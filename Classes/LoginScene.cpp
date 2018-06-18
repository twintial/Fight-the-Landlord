#include<LoginScene.h>
USING_NS_CC;
using namespace CocosDenshion;
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
		InputConnectIP();//��Ϊguest����hostIP
	}
	else
	{
		GetLocalIP();//��Ϊhost���ӱ���IP
	}
	OKbutton();
	ReturnButton();
	schedule(schedule_selector(LoginScene::timehandle),2);//���IP
	return true;
}
void LoginScene::timehandle(float t)
{
	log("%s",local->IP.c_str());
}//test
void LoginScene::InputUsername()
{
	//����ı��򱳾�
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("username.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
	addChild(background);

	auto text = Text::create("", "arial", 25);
	text->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 40));
	addChild(text);

	auto tf = TextField::create("Enter your name", "arial", 30);
	tf->setTextColor(Color4B(0,102, 205, 170));
	tf->setMaxLength(10);
	tf->setMaxLengthEnabled(true);
	tf->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 + 100));
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
	//����ı��򱳾�
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("IP.png");
	background->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 10));
	addChild(background);

	auto text = Text::create("", "arial", 25);
	text->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));
	addChild(text);

	auto tf = TextField::create("          ", "arial", 20);
	tf->setTextColor(Color4B::BLACK);
	tf->setMaxLength(15);
	tf->setMaxLengthEnabled(true);
	tf->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 10));
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
	/*	SimpleAudioEngine::getInstance()->stopBackgroundMusic();*/
		Director::getInstance()->pushScene(GameScene::CreateScene());
	}
}
void LoginScene::ReturnChooseScene(Ref *pSender)
{
	Director::getInstance()->popScene();
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
}//�����������������ӱ���IP����ȡ����IP
void LoginScene::SettingBackground()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("Lbackground.jpg");
	//background->setScale(1.2f);
	background->setPosition(visibleSize / 2);
	this->addChild(background);
}