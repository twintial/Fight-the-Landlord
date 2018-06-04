#ifndef  _SERVER_LOG_IN_H_
#define  _SERVER_LOG_IN_H_

#include<cocos2d.h>
#include<GameScene.h>
class ServerLogin :public cocos2d::Scene
{
public:
	static cocos2d::Scene* CreateScene();
	virtual bool init();
	CREATE_FUNC(ServerLogin);
private:

};

#endif