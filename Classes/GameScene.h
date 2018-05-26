#include<cocos2d.h>
#include<vector>
#include<Player.h>
#include <algorithm>
using namespace std;
class GameScene:public cocos2d::Scene
{
private:

public:
	static cocos2d::Scene* CreateScene();
	virtual bool init();
	void PointButton();
	CREATE_FUNC(GameScene);
};
