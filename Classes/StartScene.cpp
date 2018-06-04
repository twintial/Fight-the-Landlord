#include<StartScene.h>
USING_NS_CC;
Scene* StartScene::CreateScene()
{
	return StartScene::create();
}
bool StartScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	SettingBackgroud();
	StartButton();
	return true;
}
void StartScene::EnterChooseScene(Ref *pSender)
{
	Director::getInstance()->replaceScene(ChooseScene::CreateScene());
}
void StartScene::SettingBackgroud()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("Sbackground.jpg");
	background->setPosition(visibleSize / 2);
	this->addChild(background);
}
void StartScene::StartButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("start.png");
	auto menuitem = MenuItemSprite::create(background, background, CC_CALLBACK_1(StartScene::EnterChooseScene, this));
	auto menu = Menu::create(menuitem, NULL);
	menu->setPosition(visibleSize / 2);
	this->addChild(menu);
}