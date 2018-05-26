#include<cocos2d.h>
#include<vector>
#include<algorithm>
#include<Player.h>
using namespace std;
class Operation
{
private:
	static vector<int>card;
	Player Lord;
public:
	void LordPoint(Player);
	void Snatchlord(Player a, Player b, Player c);
	static void CardShuffle(vector<int>);
	static void CardDeal(Player* a, Player* b, Player* c);
};