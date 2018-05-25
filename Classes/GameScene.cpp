#include"GameScene.h"
#include"PokerCard.h"
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


	PokerCard a = PokerCard(23);
	a.card_picture->setPosition(visibleSize / 2);
	addChild(a.card_picture);
	PokerCard::ClickTrigger(a);
	return true;
}
void GameScene::CardShuffle(vector<int>card)
{
	for (int i = 0; i <= 54; i++)
	{
		card.push_back(i);
	}
	random_shuffle(card.begin() + 1, card.end());
}
void GameScene::CardDeal(Player* a, Player* b, Player* c)
{
	for (int i = 0; i < 51;)
	{
		i++;
		a->hand.push_back(card[i]);
		i++;
		b->hand.push_back(card[i]);
		i++;
		c->hand.push_back(card[i]);
	}
}
vector<int>GameScene::card;