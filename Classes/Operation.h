#include<cocos2d.h>
#include<vector>
#include<algorithm>
#include<Player.h>
#include<PokerCard.h>
using namespace std;
class Operation
{
private:
	Player Lord;
public:
	void LordPoint(Player);
	void Snatchlord(Player& a, Player& b, Player& c);
	void ArrangePokers_1(Player*);
	static void CardShuffle(vector<int>&card);
	static void CardDeal(Player& a, Player& b, Player& c, vector<int>&card);
	static void CardSort(Player&);
};