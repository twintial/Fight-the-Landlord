#include<SettingScene.h>
USING_NS_CC;
Scene* SettingScene::CreateScene()
{
	return SettingScene::create();
}
bool SettingScene::init()
{
	if (!Scene::init())
	{
		return false;
	}
	ReturnButton();
	return true;
}
void SettingScene::ReturnStartScene(Ref *pSender)
{
	Director::getInstance()->popScene();
}
void SettingScene::ReturnButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto button = Sprite::create("return.png");
	auto returnItem = MenuItemSprite::create(button, button, CC_CALLBACK_1(SettingScene::ReturnStartScene, this));
	auto menu = Menu::create(returnItem, NULL);
	menu->setPosition(visibleSize.width - returnItem->getContentSize().width / 2, visibleSize.height - returnItem->getContentSize().height / 2);
	this->addChild(menu);
}