#include"Player.h"
USING_NS_CC;
Player::Player()
{
	vector<int>hand;
	status = -1;
	lord_point = -1;
}
Player& Player::operator=(Player& x)
{
	return x;
}