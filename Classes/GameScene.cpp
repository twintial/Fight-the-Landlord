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
	//test
	Player a = Player();
	Player b = Player();
	Player c = Player();
	log("///");
	Operation::CardShuffle(card);
	log("shu ok");
	log("%d", card.size());
	Operation::CardDeal(a, b, c, card);
	Operation::CardSort(a);
	Operation::CardSort(b);
	Operation::CardSort(c);
	ArrangePokers_1(a);
	return true;
}
void GameScene::PointButton()
{

}
void GameScene::ArrangePokers_1(Player x)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	vector<PokerCard>poker;
	for (int i = 0; i <= x.hand.size() - 1; i++)
	{
		poker.push_back(PokerCard(x.hand[i]));
	}
	poker[0].card_picture->setPosition(200, 150);
	size_t cx = poker[0].card_picture->getPositionX();
	for (int i = 0; i <= poker.size() - 1; i++)
	{
		poker[i].card_picture->setPosition(cx + 50 * i, 150);
	}
	for (int i = 0; i <= 16; i++)
	{
		PokerCard::ClickTrigger(poker[i]);
		addChild(poker[i].card_picture);
	}
}
vector<int>GameScene::card;