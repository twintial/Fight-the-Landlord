#include<iostream>
#include<cocos2d.h>
#pragma once
using namespace cocos2d;
using namespace std;
class PokerCard
{
private:
	int card_number;
	int kind;
	mutable int iostates;
	Sprite* card_picture;
	Sprite* m_card_picture;
public:
	PokerCard(int num);
	void ClickOut()const;
	void ClickIn()const;
	void ClickTrigger();
	friend class GameScene;
	friend class Operation;
	~PokerCard();
};
 

