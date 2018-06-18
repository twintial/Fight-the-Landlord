#ifndef _SETTING_SCENE_H_
#define _SETTING_SCENE_H_

#include<cocos2d.h>
#include "ui/CocosGUI.h"
#include"SimpleAudioEngine.h"
class SettingScene:public cocos2d::Scene
{
public:
	static cocos2d::Scene* CreateScene();
	virtual bool init();
	void ReturnButton();
	void ReturnStartScene(Ref *pSender);
	void BGMVolume();
	CREATE_FUNC(SettingScene);
private:
};
#endif // _SETTING_SCENE_H_
