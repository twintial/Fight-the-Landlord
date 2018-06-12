#ifndef _POKER_CARD_H_
#define _POKER_CARD_H_

#include<iostream>
#include<cocos2d.h>
using namespace cocos2d;
using namespace std;
class PokerCard
{
public:
	PokerCard(int num);
	void ClickOut()const;
	void ClickIn()const;
	void ClickTrigger();
	friend class GameScene;
	friend class Operation;
	friend class Player;
	friend class Server;//
	~PokerCard();
private:
	int num;
	int card_number;
	int kind;
	mutable int iostates;
	int played;//0��ʾ��������,1��ʾ�����,-1��ʾ�Ѿ������Ƶļ�϶����,������Ҳ����ʹ�ô���
	Sprite* card_picture;
	Sprite* m_card_picture;
};
#endif