#ifndef _OPERATION_H_
#define _OPERATION_H_

#include<cocos2d.h>
#include<vector>
#include<algorithm>
#include<Player.h>
#include<PokerCard.h>
using namespace std;
class Operation
{
public:
	void LordPoint(Player);
	void Snatchlord(Player& a, Player& b, Player& c);
	static void CardShuffle(vector<int>&card);
	static void CardDeal(Player& a, Player& b, Player& c, vector<int>&card);
	static void CardSort(Player&);
    static void OutCardSort(Player&);
	static int CardType(Player&);
private:
};
#endif