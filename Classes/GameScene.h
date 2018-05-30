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
	void ArrangeoutPokers(Player&);
	CREATE_FUNC(GameScene);
};
