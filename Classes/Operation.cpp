#include<Operation.h>
USING_NS_CC;
//void Operation::Snatchlord(Player& a, Player& b, Player& c)//��ȷ�Դ�����
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
//		LordPoint(mapPlayer[now_snatch]);//֪ͨ�����������������ȡ��ҵĵ�������Player::Lordpoint
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
//				/*fun:disable the point button <= the max point except bujiao(0)   ʹ������<=�ķ���������Ч����ʵ�֣�*/
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
	}//3-k-1-2������
	for (int i = 0; i <= x.hand.size() - 1; i++)
	{
		if (x.hand[i] == 52)
		{
			hand_temp.push_back(x.hand[i]);
		}
		else
		{
			if (x.hand[i] == 53 && hand_temp.size() == 16)
			{
				hand_temp.push_back(x.hand[i]);
			}
		}
	}//��С������
	x.hand = hand_temp;
}
void Operation::OutCardSort(Player& x)
{
	int max = 0;
	int maxnum = 0;
	vector<int>num(54);//��¼ÿ�����ָ������˼���
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
	enum CardType
	{
		ERROR_TYPE = 0,
		SINGLE_CARD,//����
		PAIR,//����
		TRIPLET,//��«
		TRIPLET_SINGLE,//����һ
		TRIPLET_PAIR,//������
		SEQUENCE,//˳��
		SEQUENCE_OF_PAIR,//����
		SEQUENCE_OF_TRIPLET,//�ɻ�
		SEQUENCE_OF_TRIPLET_SINGLE,
		SEQUENCE_OF_TRIPLET_PAIR,
		BOMB,//ը��
		ROCKET,//��ը
		QUADPLEX_TWO_SINGLE,//�Ĵ�һ*2
		QUADPLEX_TWO_PAIR,//�Ĵ���*2
	};
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
	}//˳��

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
	}//����

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
	}//�ɻ�

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