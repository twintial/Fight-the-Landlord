#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"cocos2d.h"
#include"vector"
#include"PokerCard.h"
#include"GameScene.h"
using namespace std;
class Player
{
public:
	friend class Operation;
	friend class GameScene;
	Player();
	Player &operator= (Player&);
	void Action(Sprite*, Sprite*, GameScene*);
private:
	vector<int>hand;
	vector<PokerCard> handpoker;
	vector<PokerCard> outpoker;
	int status;//农民和地主的情况
	int lord_point;
};
#endif