#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"cocos2d.h"
#include<vector>
#include<string>
#include"PokerCard.h"
#include"GameScene.h"
#include "ui/CocosGUI.h"
#include "Settings.h"
using namespace std;
using namespace ui;
class Player
{
public:
	friend class Operation;
	friend class GameScene;
	friend class LoginScene;
	friend class Client;
	friend class Server;
	Player();
	Player &operator= (Player&);
	void Action(Button*, Button*, play_data* ,GameScene*);
private:
	vector<int>hand;
	vector<PokerCard> handpoker;
	vector<PokerCard> outpoker;
	int status;//农民和地主的情况
	int lord_point;//地主分数
	int playercode;//第几位加入游戏的玩家
	int now_cardtype;//上一位出牌的牌型
	bool isready;
	bool isplay_pokers;//是否出牌
	string username;
	string IP;
	Sprite* local_skip;
};
#endif