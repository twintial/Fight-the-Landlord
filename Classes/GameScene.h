#ifndef  _GAME_SCENE_H_
#define  _GAME_SCENE_H_

#include<cocos2d.h>
#include<vector>
#include <algorithm>
#include"Operation.h"
#include"Player.h"
using namespace std;
class GameScene:public cocos2d::Scene
{
private:
	static vector<int>card;
public:
	static cocos2d::Scene* CreateScene();
	virtual bool init();
	Sprite* PointButton_0();
	Sprite* SkipButton();
	Sprite* PlayButton();
	void ArrangePokers_1(Player&);
	void timehandle(float t);//
	bool ArrangeoutPokers(Player*);
	void ArrangePokers_afterplay(Player* x);
	CREATE_FUNC(GameScene);
};
#endif
