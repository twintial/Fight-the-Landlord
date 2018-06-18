#ifndef  _START_SCENE_H_
#define  _START_SCENE_H_

#include<cocos2d.h>
#include"ChooseScene.h"
#include"SettingScene.h"
#include"SimpleAudioEngine.h"
using namespace CocosDenshion;
class StartScene:public cocos2d::Scene
{
public:
	static cocos2d::Scene* CreateScene();
	virtual bool init();
	void SettingBackground();
	void StartButton();
	void SettingButton();
	void CloseButton();
	CREATE_FUNC(StartScene);
	void EnterChooseScene(Ref *pSender);
	void EnterSettingScene(Ref *pSender);
	void menuCloseCallback(Ref *pSender);
private:

};
#endif