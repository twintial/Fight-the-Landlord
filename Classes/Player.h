#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"cocos2d.h"
#include<vector>
#include<string>
#include"PokerCard.h"
#include"GameScene.h"
using namespace std;
class Player
{
public:
	friend class Operation;
	friend class GameScene;
	friend class LoginScene;
	friend class Client;
	Player();
	Player &operator= (Player&);
	void Action(Sprite*, Sprite*, GameScene*);
private:
	vector<int>hand;
	vector<PokerCard> handpoker;
	vector<PokerCard> outpoker;
	int status;//农民和地主的情况
	int lord_point;
	int playercode;//第几位加入游戏的玩家
	int isready;
	string username;
	string IP;
};
#endif