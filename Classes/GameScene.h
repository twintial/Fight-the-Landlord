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
using namespace std;
using namespace ui;
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
	void LocalPlay(float t);
	bool ArrangeoutPokers(Player*);
	bool ArrangeoutPokers_remote(vector<PokerCard>);
	void ArrangeHandPokers_afterplay(Player* x);
	Button* PointButton_0();
	Button* PointButton_1();
	Button* PointButton_2();
	Button* PointButton_3();
	CREATE_FUNC(GameScene);
private:
	static vector<int> card;
	Player* local;//再gamescene上添加牌时使用，其手牌为整理过。
	bool isclick;
	bool isrecv_struct;
};
#endif
