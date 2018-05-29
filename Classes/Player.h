#include"cocos2d.h"
#include"vector"
#include<PokerCard.h>
#pragma once
using namespace std;
class Player
{
private:
	vector<int>hand;
	int status;
	int lord_point;
public:
	friend class Operation;
	friend class GameScene;
	Player();
	Player &operator= (Player&);
};