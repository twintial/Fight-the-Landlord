#include<cocos2d.h>
#include<vector>
#include<Player.h>
#include <algorithm>
using namespace std;
USING_NS_CC;
class GameScene:public Scene
{
private:
	static vector<int>card;
public:
	static cocos2d::Scene* CreateScene();
	virtual bool init();
	static void CardShuffle(vector<int>);
	static void CardDeal(Player* a, Player* b, Player* c);
	CREATE_FUNC(GameScene);
};
