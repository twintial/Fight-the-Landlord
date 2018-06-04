#include<ServerLogin.h>
Scene* ServerLogin::CreateScene()
{
	return ServerLogin::create();
}
bool ServerLogin::init()
{
	if (!Scene::init())
	{
		return false;
	}

	return true;
}