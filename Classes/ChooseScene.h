#ifndef  _CHOOSE_SCENEN_H_
#define  _CHOOSE_SCENEN_H_

#include<cocos2d.h>
#include<GameScene.h>
class ChooseScene:public cocos2d::Scene
{
public:
	static cocos2d::Scene* CreateScene();
	virtual bool init();
	void CreateButton();
	void JoinButton();
	CREATE_FUNC(GameScene);
private:

};
#endif