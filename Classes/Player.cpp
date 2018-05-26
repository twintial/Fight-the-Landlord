#include"Player.h"
USING_NS_CC;
Player::Player()
{
	status = -1;
	lord_point = -1;
}
Player Player::operator=(const Player& x)
{
	return x;
}