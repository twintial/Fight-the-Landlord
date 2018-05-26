#include<Operation.h>
USING_NS_CC;
void Operation::Snatchlord(Player a, Player b, Player c)//正确性待检验
{
	int max_point = 0;
	srand((int)time(0));
	int now_snatch = rand() % 3 + 1;
	map<int, Player>mapPlayer;
	mapPlayer[1] = a;
	mapPlayer[2] = b;
	mapPlayer[3] = c;
	for (int i = 0; i <= 2; i++)
	{
		if (++now_snatch > 3)
		{
			now_snatch -= 3;
		}
		LordPoint(mapPlayer[now_snatch]);//通知这名玩家抢地主
		if (mapPlayer[now_snatch].lord_point == 3)
		{
			Lord = mapPlayer[now_snatch];
			break;
		}
		else
		{
			if (mapPlayer[now_snatch].lord_point > max_point)
			{
				max_point = mapPlayer[now_snatch].lord_point;
				Lord = mapPlayer[now_snatch];
				/*fun:disable the point button <= the max point except bujiao(0)   使比最大分<=的分数按键无效（待实现）*/
			}
		}
	}
	if (mapPlayer[1].lord_point == 0 && mapPlayer[2].lord_point == 0 && mapPlayer[3].lord_point == 0)
	{
		//restart
	}
}
void Operation::LordPoint(Player)
{

}
void Operation::CardShuffle(vector<int>card)
{
	for (int i = 0; i <= 54; i++)
	{
		card.push_back(i);
	}
	random_shuffle(card.begin() + 1, card.end());
}
void Operation::CardDeal(Player* a, Player* b, Player* c)
{
	for (int i = 0; i < 51;)
	{
		i++;
		a->hand.push_back(card[i]);
		i++;
		b->hand.push_back(card[i]);
		i++;
		c->hand.push_back(card[i]);
	}
}
vector<int>Operation::card;