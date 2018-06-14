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
	int status;//ũ��͵��������
	int lord_point;//��������
	int playercode;//�ڼ�λ������Ϸ�����
	int now_cardtype;//��һλ���Ƶ�����
	bool isready;
	bool isplay_pokers;//�Ƿ����
	string username;
	string IP;
	Sprite* local_skip;
};
#endif