#ifndef  _CHOOSE_SCENEN_H_
#define  _CHOOSE_SCENEN_H_

#include<cocos2d.h>

#include<LoginScene.h>
class ChooseScene:public cocos2d::Scene
{
public:
	static cocos2d::Scene* CreateScene();
	virtual bool init();
	void StartWithServer(Ref *pSender);
	void StartWithClient(Ref *pSender);
	void CreateButton();
	void JoinButton();
	CREATE_FUNC(ChooseScene);
private:

};
#endif