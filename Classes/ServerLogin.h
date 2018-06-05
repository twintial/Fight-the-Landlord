#ifndef  _SERVER_LOG_IN_H_
#define  _SERVER_LOG_IN_H_

#include<cocos2d.h>
#include<GameScene.h>
#include "ui/CocosGUI.h"
#include<boost/asio.hpp>
using namespace boost::asio;
using namespace std;
using ip::tcp;
using namespace ui;
class ServerLogin :public cocos2d::Scene
{
public:
	static cocos2d::Scene* CreateScene();
	virtual bool init();
	void InputUsername();
	void OKbutton();
	void BuildServer();
	CREATE_FUNC(ServerLogin);
private:
	io_service service;
};

#endif