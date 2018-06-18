#ifndef  _CHOOSE_SCENEN_H_
#define  _CHOOSE_SCENEN_H_

#include<cocos2d.h>
#include"LoginScene.h"
#include"SettingScene.h"
class ChooseScene:public cocos2d::Scene
{
public:
	static cocos2d::Scene* CreateScene();
	virtual bool init();
	void StartWithServer(Ref *pSender);
	void StartWithClient(Ref *pSender);
	void ReturnStartScene(Ref *pSender);
	void EnterSettingScene(Ref *pSender);
	void CreateButton();
	void JoinButton();
	void ReturnButton();
	void SettingButton();
	void SettingBackground();
	CREATE_FUNC(ChooseScene);
private:

};
#endif