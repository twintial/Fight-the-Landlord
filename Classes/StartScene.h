#ifndef  _START_SCENE_H_
#define  _START_SCENE_H_

#include<cocos2d.h>
#include<ChooseScene.h>
class StartScene:public cocos2d::Scene
{
public:
	static cocos2d::Scene* CreateScene();
	virtual bool init();
	void SettingBackgroud();
	void StartButton();
	CREATE_FUNC(StartScene);
	void EnterChooseScene(Ref *pSender);
private:

};
#endif