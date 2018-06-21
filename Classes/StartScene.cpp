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
	SimpleAudioEngine::getInstance()->playBackgroundMusic("start_bgm.mp3", true);
	SettingBackground();
	StartButton();
	SettingButton();
	CloseButton();
	return true;
}
void StartScene::EnterChooseScene(Ref *pSender)
{
	Director::getInstance()->pushScene(ChooseScene::CreateScene());
}
void StartScene::EnterSettingScene(Ref *pSender)
{
	Director::getInstance()->pushScene(SettingScene::CreateScene());
}
void StartScene::menuCloseCallback(Ref *pSender)
{
	Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}
void StartScene::SettingBackground()
{
	//Sprite::create("fangkuai_1.png");Sprite::create("fangkuai_2.png");Sprite::create("fangkuai_3.png");Sprite::create("fangkuai_4.png");Sprite::create("fangkuai_5.png");Sprite::create("fangkuai_6.png");
	//Sprite::create("fangkuai_7.png");Sprite::create("fangkuai_8.png");Sprite::create("fangkuai_9.png");Sprite::create("fangkuai_10.png");Sprite::create("fangkuai_J.png");Sprite::create("fangkuai_Q.png");Sprite::create("fangkuai_K.png");

	//Sprite::create("heitao_1.png");	Sprite::create("heitao_2.png");Sprite::create("heitao_3.png");Sprite::create("heitao_4.png");Sprite::create("heitao_5.png");Sprite::create("heitao_6.png");
	//Sprite::create("heitao_7.png");Sprite::create("heitao_8.png");Sprite::create("heitao_9.png");Sprite::create("heitao_10.png");Sprite::create("heitao_J.png");Sprite::create("heitao_Q.png");Sprite::create("heitao_K.png");

	//Sprite::create("hongxin_1.png");Sprite::create("hongxin_2.png");Sprite::create("hongxin_3.png");Sprite::create("hongxin_4.png");Sprite::create("hongxin_5.png");Sprite::create("hongxin_6.png");
	//Sprite::create("hongxin_7.png");Sprite::create("hongxin_8.png");Sprite::create("hongxin_9.png");	Sprite::create("hongxin_10.png");	Sprite::create("hongxin_J.png");Sprite::create("hongxin_Q.png");Sprite::create("hongxin_K.png");

	//Sprite::create("meihua_1.png");Sprite::create("meihua_2.png");Sprite::create("meihua_3.png");Sprite::create("meihua_4.png");Sprite::create("meihua_5.png");Sprite::create("meihua_6.png");
	//Sprite::create("meihua_7.png");Sprite::create("meihua_8.png");Sprite::create("meihua_9.png");Sprite::create("meihua_10.png");Sprite::create("meihua_J.png");Sprite::create("meihua_Q.png");Sprite::create("meihua_K.png");

	//Sprite::create("king_b.png");Sprite::create("king_s.png");


	//Sprite::create("m_fangkuai_1.png"); Sprite::create("m_fangkuai_2.png"); Sprite::create("m_fangkuai_3.png"); Sprite::create("m_fangkuai_4.png"); Sprite::create("m_fangkuai_5.png"); Sprite::create("m_fangkuai_6.png");
	//Sprite::create("m_fangkuai_7.png"); Sprite::create("m_fangkuai_8.png"); Sprite::create("m_fangkuai_9.png"); Sprite::create("m_fangkuai_10.png"); Sprite::create("m_fangkuai_J.png"); Sprite::create("m_fangkuai_Q.png"); Sprite::create("m_fangkuai_K.png");

	//Sprite::create("m_heitao_1.png");	Sprite::create("m_heitao_2.png"); Sprite::create("m_heitao_3.png"); Sprite::create("m_heitao_4.png"); Sprite::create("m_heitao_5.png"); Sprite::create("m_heitao_6.png");
	//Sprite::create("m_heitao_7.png"); Sprite::create("m_heitao_8.png"); Sprite::create("m_heitao_9.png"); Sprite::create("m_heitao_10.png"); Sprite::create("m_heitao_J.png"); Sprite::create("m_heitao_Q.png"); Sprite::create("m_heitao_K.png");

	//Sprite::create("m_hongxin_1.png"); Sprite::create("m_hongxin_2.png"); Sprite::create("m_hongxin_3.png"); Sprite::create("m_hongxin_4.png"); Sprite::create("m_hongxin_5.png"); Sprite::create("m_hongxin_6.png");
	//Sprite::create("m_hongxin_7.png"); Sprite::create("m_hongxin_8.png"); Sprite::create("m_hongxin_9.png");	Sprite::create("m_hongxin_10.png");	Sprite::create("m_hongxin_J.png"); Sprite::create("m_hongxin_Q.png"); Sprite::create("m_hongxin_K.png");

	//Sprite::create("m_meihua_1.png"); Sprite::create("m_meihua_2.png"); Sprite::create("m_meihua_3.png"); Sprite::create("m_meihua_4.png"); Sprite::create("m_meihua_5.png"); Sprite::create("m_meihua_6.png");
	//Sprite::create("m_meihua_7.png"); Sprite::create("m_meihua_8.png"); Sprite::create("m_meihua_9.png"); Sprite::create("m_meihua_10.png"); Sprite::create("m_meihua_J.png"); Sprite::create("m_meihua_Q.png"); Sprite::create("m_meihua_K.png");

	//Sprite::create("m_king_b.png"); Sprite::create("m_king_s.png");

	//Sprite::create("point_0.png"); Sprite::create("point_1.png"); Sprite::create("point_2.png"); Sprite::create("point_3.png");

	//Sprite::create("playbutton.png"); Sprite::create("skipbutton.png");

	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto background = Sprite::create("Sbackground.jpg");
	background->setPosition(visibleSize / 2);
	this->addChild(background);
}
void StartScene::StartButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto button = Sprite::create("start.png");
	auto menuitem = MenuItemSprite::create(button, button, CC_CALLBACK_1(StartScene::EnterChooseScene, this));
	auto menu = Menu::create(menuitem, NULL);
	menu->setPosition(visibleSize / 2);
	this->addChild(menu);
}
void StartScene::SettingButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto button = Sprite::create("settings1.png");
	auto menuitem = MenuItemSprite::create(button, button, CC_CALLBACK_1(StartScene::EnterSettingScene, this));
	auto menu = Menu::create(menuitem, NULL);
	menu->setPosition(menuitem->getContentSize().width / 2 + 30, visibleSize.height - menuitem->getContentSize().height / 2 - 30);
	this->addChild(menu);
}
void StartScene::CloseButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto button = Sprite::create("close.png");
	auto closeItem = MenuItemSprite::create(button, button, CC_CALLBACK_1(StartScene::menuCloseCallback, this));
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(visibleSize.width - closeItem->getContentSize().width / 2, visibleSize.height - closeItem->getContentSize().height / 2);
	this->addChild(menu);
}