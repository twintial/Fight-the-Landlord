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
class GameScene:public cocos2d::Scene
{
public:
	static bool start;//游戏是否已经开始

	static cocos2d::Scene* CreateScene();
	virtual bool init();
	Sprite* PointButton_0();
	Sprite* SkipButton();
	Sprite* PlayButton();
	void ReadyButton();
	void Settingbackgroud();
	void ArrangePokers_1(Player&);
	void timehandle(float t);//
	bool ArrangeoutPokers(Player*);
	void ArrangeHandPokers_afterplay(Player* x);
	CREATE_FUNC(GameScene);
private:
	static vector<int> card;
};
#endif
