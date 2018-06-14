#include<Operation.h>
USING_NS_CC;
//void Operation::Snatchlord(Player& a, Player& b, Player& c)//正确性待检验
//{
//	int max_point = 0;
//	srand((int)time(0));
//	int now_snatch = rand() % 3 + 1;
//	map<int, Player>mapPlayer;
//	mapPlayer[1] = a;
//	mapPlayer[2] = b;
//	mapPlayer[3] = c;
//	for (int i = 0; i <= 2; i++)
//	{
//		if (++now_snatch > 3)
//		{
//			now_snatch -= 3;
//		}
//		LordPoint(mapPlayer[now_snatch]);//通知这名玩家抢地主并获取玩家的地主分数Player::Lordpoint
//		if (mapPlayer[now_snatch].lord_point == 3)
//		{
//			Lord = mapPlayer[now_snatch];
//			break;
//		}
//		else
//		{
//			if (mapPlayer[now_snatch].lord_point > max_point)
//			{
//				max_point = mapPlayer[now_snatch].lord_point;
//				Lord = mapPlayer[now_snatch];
//				/*fun:disable the point button <= the max point except bujiao(0)   使比最大分<=的分数按键无效（待实现）*/
//			}
//		}
//	}
//	if (mapPlayer[1].lord_point == 0 && mapPlayer[2].lord_point == 0 && mapPlayer[3].lord_point == 0)
//	{
//		//restart
//	}
//}
void Operation::LordPoint(Player)
{

}
void Operation::CardShuffle(vector<int>&card)
{
	srand(unsigned(time(NULL)));
	for (int i = 0; i <= 53; i++)
	{
		card.push_back(i);
	}
	random_shuffle(card.begin(), card.end());
}
void Operation::CardDeal(Player& a, Player& b, Player& c, vector<int>&card)
{
	for (int i = 0; i < 51;)
	{
		a.hand.push_back(card[i]);
		i++;
		b.hand.push_back(card[i]);
		i++;
		c.hand.push_back(card[i]);
		i++;
	}
}
void Operation::CardSort(Player& x)
{
	sort(x.hand.begin(), x.hand.end());
	vector<int>hand_temp;
	for (int i = 2; i <= 12; i++)
	{
		for (int j = 0; j <= x.hand.size() - 1; j++)
		{
			if (x.hand[j] % 13 == i && x.hand[j] <= 51)
			{
				hand_temp.push_back(x.hand[j]);
			}
		}
	}
	for (int i = 0; i <= 1; i++)
	{
		for (int j = 0; j <= x.hand.size() - 1; j++)
		{
			if (x.hand[j] % 13 == i && x.hand[j] <= 51)
			{
				hand_temp.push_back(x.hand[j]);
			}
		}
	}//3-k-1-2的排序
	for (int i = 0; i <= x.hand.size() - 1; i++)
	{
		if (x.hand[i] == 52)
		{
			hand_temp.push_back(x.hand[i]);
		}
		else
		{
			if (x.hand[i] == 53 && hand_temp.size() == x.hand.size() - 1)//16
			{
				hand_temp.push_back(x.hand[i]);
			}
		}
	}//大小王排序
	x.hand = hand_temp;

	for (int i = 0; i <= x.hand.size() - 1; i++)
	{
		x.handpoker.push_back(PokerCard(x.hand[i]));
	}
}
void Operation::OutCardSort(Player& x)
{
	int max = 0;
	int maxnum = 0;
	vector<int>num(54);//记录每个数字各出现了几次
	for (int i = 0; i <= x.outpoker.size() - 1; i++)
	{
		num[x.outpoker[i].card_number]++;
	}
	vector<PokerCard>temp;
	for (int i = 0; i <= x.outpoker.size() - 1; i++)
	{
		if (num[x.outpoker[i].card_number] == 4)
		{
			temp.push_back(x.outpoker[i]);
		}
	}
	for (int i = 0; i <= x.outpoker.size() - 1; i++)
	{
		if (num[x.outpoker[i].card_number] == 3)
		{
			temp.push_back(x.outpoker[i]);
		}
	}
	for (int i = 0; i <= x.outpoker.size() - 1; i++)
	{
		if (num[x.outpoker[i].card_number] == 2)
		{
			temp.push_back(x.outpoker[i]);
		}
	}
	for (int i = 0; i <= x.outpoker.size() - 1; i++)
	{
		if (num[x.outpoker[i].card_number] == 1)
		{
			temp.push_back(x.outpoker[i]);
		}
	}
	x.outpoker = temp;
}
int Operation::CardType(Player& x)
{
	if (x.outpoker.empty())
	{
		return ERROR_TYPE;
	}
	OutCardSort(x);
	if (x.outpoker.size() == 1)
	{
		return SINGLE_CARD;
	}
	if (x.outpoker.size() == 2)
	{
		if (x.outpoker[0].card_number == x.outpoker[1].card_number)
		{
			return PAIR;
		}
		else if (x.outpoker[0].card_number == 52 && x.outpoker[1].card_number == 53)
		{
			return ROCKET;
		}
	}
	if (x.outpoker.size() == 3 && x.outpoker[0].card_number == x.outpoker[1].card_number&&x.outpoker[1].card_number == x.outpoker[2].card_number)
	{
		return TRIPLET;
	}
	if (x.outpoker.size() == 4)
	{
		if (x.outpoker[0].card_number == x.outpoker[1].card_number&&x.outpoker[1].card_number == x.outpoker[2].card_number)
		{
			if (x.outpoker[0].card_number == x.outpoker[3].card_number)
			{
				return BOMB;
			}
			else
			{
				return TRIPLET_SINGLE;
			}
		}
	}
	if (x.outpoker.size() >= 5)
	{
		int flag = 0;
		for (int i = 0; i <= x.outpoker.size() - 2; i++)
		{
			if (x.outpoker[i].card_number + 1 != x.outpoker[i + 1].card_number)
			{
				flag = 1;
				break;
			}
		}
		if (!flag)
		{
			return SEQUENCE;
		}
	}//顺子
	if (x.outpoker.size() >= 6 && x.outpoker.size() % 2 == 0)
	{
		int flag = 0;
		for (int i = 0; i <= x.outpoker.size() - 2; i += 2)
		{
			if (x.outpoker[i].card_number != x.outpoker[i + 1].card_number)
			{
				flag = 1;
				break;
			}
		}
		for (int i = 0; i <= x.outpoker.size() - 4; i += 2)
		{
			if (x.outpoker[i].card_number + 1 != x.outpoker[i + 2].card_number)
			{
				flag = 1;
				break;
			}
		}
		if (!flag)
		{
			return SEQUENCE_OF_PAIR;
		}
	}//连对
	if (x.outpoker.size() == 5)
	{
		if (x.outpoker[0].card_number == x.outpoker[1].card_number&&x.outpoker[1].card_number == x.outpoker[2].card_number&&x.outpoker[3].card_number == x.outpoker[4].card_number)
		{
			return TRIPLET_PAIR;
		}
	}
	if (x.outpoker.size() >= 6 && x.outpoker.size() % 3 == 0)
	{
		int flag = 0;
		for (int i = 0; i <= x.outpoker.size() - 3; i += 3)
		{
			if (x.outpoker[i].card_number != x.outpoker[i + 1].card_number || x.outpoker[i].card_number != x.outpoker[i + 2].card_number || x.outpoker[i + 1].card_number != x.outpoker[i + 2].card_number)
			{
				flag = 1;
				break;
			}
		}
		for (int i = 0; i <= x.outpoker.size() - 6; i += 3)
		{
			if (x.outpoker[i].card_number + 1 != x.outpoker[i + 3].card_number)
			{
				flag = 1;
				break;
			}
		}
		if (!flag)
		{
			return SEQUENCE_OF_TRIPLET;
		}
	}//飞机
	if (x.outpoker.size() >= 8 && x.outpoker.size() % 4 == 0)
	{
		int flag = 0;
		int triplet_num = x.outpoker.size() / 4;
		for (int i = 0; i <= x.outpoker.size() - 1 - triplet_num; i += 3)
		{
			if (x.outpoker[i].card_number != x.outpoker[i + 1].card_number || x.outpoker[i].card_number != x.outpoker[i + 2].card_number || x.outpoker[i + 1].card_number != x.outpoker[i + 2].card_number)
			{
				flag = 1;
				break;
			}
		}
		if (!flag)
		{
			return SEQUENCE_OF_TRIPLET_SINGLE;
		}
	}
	if (x.outpoker.size() >= 10 && x.outpoker.size() % 5 == 0)
	{
		int flag = 0;
		int triplet_num = x.outpoker.size() / 5;
		for (int i = 0; i <= x.outpoker.size() - 1 - 2 * triplet_num; i += 3)
		{
			if (x.outpoker[i].card_number != x.outpoker[i + 1].card_number || x.outpoker[i].card_number != x.outpoker[i + 2].card_number || x.outpoker[i + 1].card_number != x.outpoker[i + 2].card_number)
			{
				flag = 1;
				break;
			}
		}
		for (int i = x.outpoker.size() - 2 * triplet_num; i <= x.outpoker.size() - 1; i += 2)
		{
			if (x.outpoker[i].card_number + 1 != x.outpoker[i + 2].card_number)
			{
				flag = 1;
				break;
			}
		}
		if (!flag)
		{
			return SEQUENCE_OF_TRIPLET_PAIR;
		}
	}
	if (x.outpoker.size() == 6)
	{
		if (x.outpoker[0].card_number == x.outpoker[1].card_number&&x.outpoker[1].card_number == x.outpoker[2].card_number&&x.outpoker[2].card_number == x.outpoker[3].card_number)
		{
			return QUADPLEX_TWO_SINGLE;
		}
	}
	if (x.outpoker.size() == 8)
	{
		if (x.outpoker[0].card_number == x.outpoker[1].card_number&&x.outpoker[1].card_number == x.outpoker[2].card_number&&x.outpoker[2].card_number == x.outpoker[3].card_number)
		{
			if (x.outpoker[4].card_number == x.outpoker[5].card_number&&x.outpoker[6].card_number == x.outpoker[7].card_number&&x.outpoker[5].card_number != x.outpoker[6].card_number)
			{
				return QUADPLEX_TWO_PAIR;
			}
		}
	}
	return ERROR_TYPE;
}
int Operation::TypeCompare(Player& x, play_data* datas)
{
	int my_tpye = CardType(x);
	if (my_tpye == ERROR_TYPE)
	{
		return 0;
	}
	//能出的牌都可以出，即目前场上无牌
	if (datas->card_type == ERROR_TYPE)
	{
		return 1;
	}
	auto first = PokerCard(datas->out_poker[0]);
	//先判断出牌数量
	if (x.outpoker.size() == datas->card_amount)
	{
		//判断牌型一致
		if (my_tpye == ROCKET)
		{
			return 1;
		}
		if (my_tpye == BOMB && datas->card_type != BOMB)
		{
			return 1;
		}
		if (my_tpye == datas->card_type)
		{
			if (x.outpoker[0].card_number > first.card_number)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
		else
		{
			return 0;
		}
	}
	else if (my_tpye == BOMB)//如果我出的是炸弹
	{
		if (datas->card_type == ROCKET)
		{
			return 0;
		}
		else
		{
			return 1;
		}
	}
	else if(my_tpye==ROCKET)//如果我出的是王炸
	{
		return 1;
	}
	else
	{
		return 0;
	}
}