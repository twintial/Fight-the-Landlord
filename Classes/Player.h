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
	friend class Server;
	Player();
	Player &operator= (Player&);
	void Action(Sprite*, Sprite*, GameScene*);
private:
	vector<int>hand;
	vector<PokerCard> handpoker;
	vector<PokerCard> outpoker;
	int status;//ũ��͵��������
	int lord_point;//��������
	int playercode;//�ڼ�λ������Ϸ�����
	bool isready;
	string username;
	string IP;
};
#endif