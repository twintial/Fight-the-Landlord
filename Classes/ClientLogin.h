#ifndef  _CLIENT_LOG_IN_H_
#define  _CLIENT_LOG_IN_H_

#include<cocos2d.h>
#include "ui/CocosGUI.h"
#include<GameScene.h>
#include<Player.h>
#include<string>
using namespace std;
using namespace ui;
class ClientLogin :public cocos2d::Scene
{
public:
	static cocos2d::Scene* CreateScene();
	virtual bool init();
	void InputUsername();
	void InputConnectIP();
	void OKbutton();
	CREATE_FUNC(ClientLogin);
	void timehandle(float t);//
private:
	string IP;
};

#endif