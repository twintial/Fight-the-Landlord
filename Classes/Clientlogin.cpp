#include<ClientLogin.h>
USING_NS_CC;
Scene* ClientLogin::CreateScene()
{
	return ClientLogin::create();
}
bool ClientLogin::init()
{
	if (!Scene::init())
	{
		return false;
	}
	InputUsername();
	InputConnectIP();
	OKbutton();
	//schedule(schedule_selector(ClientLogin::timehandle),2);
	return true;
}
void ClientLogin::timehandle(float t)
{
	log("%s",IP);
}//test
void ClientLogin::InputUsername()
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
			string username = tf->getString();
			if (username.length() == 0)
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
void ClientLogin::InputConnectIP()
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
			IP = tf->getString();
			if (IP.length() == 0)
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
void ClientLogin::OKbutton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto button = Sprite::create("OKbutton.png");
	button->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 300);
	addChild(button);


}