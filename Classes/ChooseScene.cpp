#include<ChooseScene.h>
USING_NS_CC;
Scene* ChooseScene::CreateScene()
{
	return ChooseScene::create();
}
bool ChooseScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	SettingBackground();
	CreateButton();
	JoinButton();
	ReturnButton();
	return true;
}
void ChooseScene::StartWithServer(Ref *pSender)
{
	Director::getInstance()->pushScene(LoginScene::CreateHost());
}
void ChooseScene::StartWithClient(Ref *pSender)
{
	Director::getInstance()->pushScene(LoginScene::CreateGuest());
}
void ChooseScene::ReturnStartScene(Ref *pSender)
{
	Director::getInstance()->popScene();
}
void ChooseScene::CreateButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto button = Sprite::create("create.png");
	auto menuitem = MenuItemSprite::create(button, button, CC_CALLBACK_1(ChooseScene::StartWithServer, this));
	auto menu = Menu::create(menuitem, NULL);
	menu->setPosition(visibleSize.width / 2, visibleSize.height / 2 + 100);
	this->addChild(menu);
}
void ChooseScene::JoinButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto button = Sprite::create("join.png");
	auto menuitem = MenuItemSprite::create(button, button, CC_CALLBACK_1(ChooseScene::StartWithClient, this));
	auto menu = Menu::create(menuitem, NULL);
	menu->setPosition(visibleSize.width / 2, visibleSize.height / 2 - 100);
	this->addChild(menu);
}
void ChooseScene::ReturnButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto button = Sprite::create("return.png");
	auto returnItem = MenuItemSprite::create(button, button, CC_CALLBACK_1(ChooseScene::ReturnStartScene, this));
	auto menu = Menu::create(returnItem, NULL);
	menu->setPosition(visibleSize.width - returnItem->getContentSize().width / 2, visibleSize.height - returnItem->getContentSize().height / 2);
	this->addChild(menu);
}
void ChooseScene::SettingBackground()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("Cbackground.jpg");
	background->setScale(1.2f);
	background->setPosition(visibleSize / 2);
	this->addChild(background);
}