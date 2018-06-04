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

	CreateButton();
	JoinButton();
	return true;
}
void ChooseScene::StartWithServer(Ref *pSender)
{
	Director::getInstance()->replaceScene(ServerLogin::CreateScene());
}
void ChooseScene::StartWithClient(Ref *pSender)
{
	Director::getInstance()->replaceScene(ClientLogin::CreateScene());
}
void ChooseScene::CreateButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto button = Sprite::create("create.png");
	auto menuitem = MenuItemSprite::create(button, button, CC_CALLBACK_1(ChooseScene::StartWithServer, this));
	auto menu = Menu::create(menuitem, NULL);
	menu->setPosition(visibleSize.width/2+400,visibleSize.height/2);
	this->addChild(menu);
}
void ChooseScene::JoinButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto button = Sprite::create("join.png");
	auto menuitem = MenuItemSprite::create(button, button, CC_CALLBACK_1(ChooseScene::StartWithClient, this));
	auto menu = Menu::create(menuitem, NULL);
	menu->setPosition(visibleSize / 2);
	this->addChild(menu);
}