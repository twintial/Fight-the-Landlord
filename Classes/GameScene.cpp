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
	auto background = Sprite::create("background.png");
	background->setPosition(visibleSize / 2);
	this->addChild(background);
	//test
	auto a = new Player();
	auto b = new Player();
	auto c = new Player();
	Operation::CardShuffle(card);
	Operation::CardDeal(*a, *b, *c, card);
	Operation::CardSort(*a);
	Operation::CardSort(*b);
	Operation::CardSort(*c);
	ArrangePokers_1(*a);
	auto sb = SkipButton();
	auto pb = PlayButton();
	//schedule(schedule_selector(GameScene::timehandle),2);
	Operation::Action(sb, pb, *a);
	return true;
}
void GameScene::timehandle(float t)
{

}
Sprite* GameScene::PointButton_0()
{
	auto point_zero= Sprite::create("point_0.png");
	point_zero->setPosition(200, 500);
	addChild(point_zero);
	return point_zero;
}
Sprite* GameScene::SkipButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto skip_button = Sprite::create("skipbutton.png");
	skip_button->setPosition(visibleSize.width / 2 + 140, 305);
	skip_button->setScale(0.78f);
	addChild(skip_button);
	return skip_button;
}
Sprite* GameScene::PlayButton()
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	auto play_button = Sprite::create("playbutton.png");
	play_button->setPosition(visibleSize.width / 2 - 140, 305);
	play_button->setScale(0.78f);
	addChild(play_button);
	return play_button;
}
void GameScene::ArrangePokers_1(Player& x)
{
	auto visibleSize = Director::getInstance()->getVisibleSize();
	for (int i = 0; i <= x.hand.size() - 1; i++)
	{
		x.handpoker.push_back(PokerCard(x.hand[i]));
	}
	x.handpoker[x.handpoker.size() - 1].card_picture->setPosition(210, 150);//set left poker
	size_t cx = x.handpoker[x.handpoker.size() - 1].card_picture->getPositionX();
	for (int i = x.handpoker.size() - 1; i >= 0; i--)
	{
		x.handpoker[i].card_picture->setPosition(cx + 50 * (x.handpoker.size() - 1 - i), 150);
	}
	for (int i = 0; i <= 16; i++)
	{
		x.handpoker[i].ClickTrigger();
		addChild(x.handpoker[i].card_picture, x.handpoker.size() - 1 - i);
	}
}
void GameScene::ArrangeoutPokers(Player& x)
{
	for (int i = 0; i <= 16; i++)
	{
		x.handpoker[i].m_card_picture->setPosition(500, 500);
		addChild(x.handpoker[i].m_card_picture);
	}
}
vector<int>GameScene::card;