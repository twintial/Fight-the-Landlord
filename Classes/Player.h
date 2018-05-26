#include"cocos2d.h"
#include"vector"
using namespace std;
class Player
{
private:
	vector<int>hand;
	int status;
	int lord_point;
public:
	friend class Operation;
	friend class GameScene;
	Player();
	Player operator= (const Player&);
};