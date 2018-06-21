#ifndef _OPERATION_H_
#define _OPERATION_H_

#include<cocos2d.h>
#include<vector>
#include<algorithm>
#include<Player.h>
#include<PokerCard.h>
#include"Settings.h"
using namespace std;
class Operation
{
public:
	Operation();
	~Operation();
	static void CardShuffle(vector<int>&card);
	static void CardDeal(Player& a, Player& b, Player& c, vector<int>&card);
	static void CardSort(Player&);
    static void OutCardSort(Player&);
	static int CardType(Player&);
	static int TypeCompare(Player&, play_data*);
private:
};
#endif