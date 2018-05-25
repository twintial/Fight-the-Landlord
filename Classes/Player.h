#include"cocos2d.h"
#include"vector"
using namespace std;
class Player
{
private:
	vector<int>hand;
	int status;
public:
	friend class GameScene;
};