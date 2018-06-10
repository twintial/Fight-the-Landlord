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
	Sprite::create("fangkuai_1.png");Sprite::create("fangkuai_2.png");Sprite::create("fangkuai_3.png");Sprite::create("fangkuai_4.png");Sprite::create("fangkuai_5.png");Sprite::create("fangkuai_6.png");
	Sprite::create("fangkuai_7.png");Sprite::create("fangkuai_8.png");Sprite::create("fangkuai_9.png");Sprite::create("fangkuai_10.png");Sprite::create("fangkuai_J.png");Sprite::create("fangkuai_Q.png");Sprite::create("fangkuai_K.png");

	Sprite::create("heitao_1.png");	Sprite::create("heitao_2.png");Sprite::create("heitao_3.png");Sprite::create("heitao_4.png");Sprite::create("heitao_5.png");Sprite::create("heitao_6.png");
	Sprite::create("heitao_7.png");Sprite::create("heitao_8.png");Sprite::create("heitao_9.png");Sprite::create("heitao_10.png");Sprite::create("heitao_J.png");Sprite::create("heitao_Q.png");Sprite::create("heitao_K.png");

	Sprite::create("hongxin_1.png");Sprite::create("hongxin_2.png");Sprite::create("hongxin_3.png");Sprite::create("hongxin_4.png");Sprite::create("hongxin_5.png");Sprite::create("hongxin_6.png");
	Sprite::create("hongxin_7.png");Sprite::create("hongxin_8.png");Sprite::create("hongxin_9.png");	Sprite::create("hongxin_10.png");	Sprite::create("hongxin_J.png");Sprite::create("hongxin_Q.png");Sprite::create("hongxin_K.png");

	Sprite::create("meihua_1.png");Sprite::create("meihua_2.png");Sprite::create("meihua_3.png");Sprite::create("meihua_4.png");Sprite::create("meihua_5.png");Sprite::create("meihua_6.png");
	Sprite::create("meihua_7.png");Sprite::create("meihua_8.png");Sprite::create("meihua_9.png");Sprite::create("meihua_10.png");Sprite::create("meihua_J.png");Sprite::create("meihua_Q.png");Sprite::create("meihua_K.png");

	Sprite::create("king_b.png");Sprite::create("king_s.png");

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