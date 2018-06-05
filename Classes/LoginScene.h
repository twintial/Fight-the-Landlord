#ifndef  _CLIENT_LOG_IN_H_
#define  _CLIENT_LOG_IN_H_

#include<cocos2d.h>
#include "ui/CocosGUI.h"
#include<GameScene.h>
#include<Player.h>
#include<string>
using namespace std;
using namespace ui;
class LoginScene :public cocos2d::Scene
{
public:
	static Player* local;
	static cocos2d::Scene* CreateHost();
	static cocos2d::Scene* CreateGuest();
	virtual bool init();
	void InputUsername();
	void InputConnectIP();
	void EnterGameScene(Ref *pSender);
	void OKbutton();
	int GetLocalIP();
	CREATE_FUNC(LoginScene);
	void timehandle(float t);//
private:
	static size_t state;
};

#endif