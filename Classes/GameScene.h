#ifndef  _GAME_SCENE_H_
#define  _GAME_SCENE_H_

#include<cocos2d.h>
#include<vector>
#include <algorithm>
#include"Operation.h"
#include"Player.h"
#include"LoginScene.h"
#include"Client.h"
#include"Server.h"
#include"PokerCard.h"
#include"ChooseScene.h"
#include"SimpleAudioEngine.h"
using namespace std;
using namespace ui;
using namespace CocosDenshion;
class GameScene:public cocos2d::Scene
{
public:
	friend class Server;
	friend class Client;
	friend class Player;
	static cocos2d::Scene* CreateScene();
	virtual bool init();

	Button* SkipButton();
	Button* PlayButton();
	void ReadyButton();

	void Settingbackgroud();
	void ArrangePokers(vector<PokerCard>& handpoker);
	void ArrangePoker_before(float t);
	void ArrangePoker_lord(float t);
	void ArrangeLordbutton(float t);

	void TimePass(float t);
	void TimePass_guest(float);

	void SettingButton();

	//void RestartButton();

	void EnterSettingScene(Ref *pSender);
	void LocalPlay(float t);
	bool ArrangeOutPokers(Player*);
	bool ArrangeOutPokers_remote_left(vector<PokerCard>&);
	bool ArrangeOutPokers_remote_right(vector<PokerCard>&);
	void ArrangeHandPokers_afterplay(Player* x);
	void ClearOutPokers(vector<PokerCard>&);
	void SetClock();

	Button* PointButton_0();
	Button* PointButton_1();
	Button* PointButton_2();
	Button* PointButton_3();
	CREATE_FUNC(GameScene);
private:
	static vector<int> card;
	vector<int> pokers_num;
	Player* local;//��gamescene�������ʱʹ�ã�������Ϊ�������
	bool isclick;
	bool isrecv_struct;
	bool lord_first_play;
	int isadded;//�Ƿ����waiting
};
#endif
