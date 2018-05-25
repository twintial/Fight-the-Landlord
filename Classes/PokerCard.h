#include<iostream>
#include<cocos2d.h>
using namespace cocos2d;
class PokerCard
{
private:
	int card_number;
	int kind;
	mutable int iostates;
	Sprite * card_picture;
public:
	PokerCard(int num);
	void ClickOut()const;
	void ClickIn()const;
	static void ClickTrigger(PokerCard);
	friend class GameScene;
	~PokerCard();
};

