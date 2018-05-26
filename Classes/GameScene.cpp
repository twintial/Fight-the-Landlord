#include"GameScene.h"
#include"PokerCard.h"
USING_NS_CC;
Scene* GameScene::CreateScene()
{
	return GameScene::create();
}
bool GameScene::init()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto* background = Sprite::create("background.png");
	background->setPosition(visibleSize / 2);
	this->addChild(background);


	PokerCard a = PokerCard(15);
	a.card_picture->setPosition(visibleSize / 2);
	addChild(a.card_picture);
	PokerCard::ClickTrigger(a);
	return true;
}
void GameScene::PointButton()
{

}