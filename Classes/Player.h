#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"cocos2d.h"
#include"vector"
#include"PokerCard.h"
#include"GameScene.h"
using namespace std;
class Player
{
private:
	vector<int>hand;
	vector<PokerCard> handpoker;
	vector<PokerCard> outpoker;
	int status;
	int lord_point;
public:
	friend class Operation;
	friend class GameScene;
	Player();
	Player &operator= (Player&);
	void Action(Sprite*, Sprite*, GameScene*);
};
#endif