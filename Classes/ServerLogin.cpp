#include<ServerLogin.h>
Scene* ServerLogin::CreateScene()
{
	return ServerLogin::create();
}
bool ServerLogin::init()
{
	if (!Scene::init())
	{
		return false;
	}

	InputUsername();
	OKbutton();
	return true;
}
void ServerLogin::InputUsername()
{
	//Ìí¼ÓÎÄ±¾¿ò±³¾°
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("username.png");
	background->setPosition(visibleSize / 2);
	addChild(background);

	auto text = Text::create("", "arial", 25);
	text->setPosition(Vec2(visibleSize.width / 2, visibleSize.height / 2 - 50));
	addChild(text);

	auto tf = TextField::create("Enter your name", "arial", 30);
	tf->setTextColor(Color4B(0, 102, 205, 170));
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
void ServerLogin::OKbutton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto button = Sprite::create("OKbutton.png");
	button->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 300);
	addChild(button);
}
void ServerLogin::BuildServer()
{
	ip::tcp::acceptor acceptor(service, ip::tcp::endpoint(ip::tcp::v4(), 8080));
}