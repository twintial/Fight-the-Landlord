#include<Operation.h>
USING_NS_CC;
void Operation::Snatchlord(Player& a, Player& b, Player& c)//正确性待检验
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
		LordPoint(mapPlayer[now_snatch]);//通知这名玩家抢地主并获取玩家的地主分数Player::Lordpoint
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
			if (x.hand[i] == 53 && hand_temp.size() == 16)
			{
				hand_temp.push_back(x.hand[i]);
			}
		}
	}//大小王排序
	x.hand = hand_temp;
}
void Operation::Action(Sprite* skipbutton, Sprite*playbutton, Player& x)
{
	auto listener_skip = EventListenerTouchOneByOne::create();
	listener_skip->onTouchBegan = [skipbutton, listener_skip](Touch *t, Event *e)
	{
		if (skipbutton->getBoundingBox().containsPoint(t->getLocation()))
		{
			listener_skip->setSwallowTouches(true);
		}
		return true;
	};
	listener_skip->onTouchEnded = [skipbutton, playbutton, listener_skip](Touch *t, Event *e)
	{
		if (skipbutton->getBoundingBox().containsPoint(t->getLocation()))
		{
			skipbutton->removeFromParent();
			playbutton->removeFromParent();
		}
		listener_skip->setSwallowTouches(false);
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener_skip, skipbutton);
	//skip


	auto listener_play = EventListenerTouchOneByOne::create();
	listener_play->onTouchBegan = [playbutton, listener_play](Touch *t, Event *e)
	{
		if (playbutton->getBoundingBox().containsPoint(t->getLocation()))
		{
			listener_play->setSwallowTouches(true);
		}
		return true;
	};
	listener_play->onTouchEnded = [skipbutton, playbutton, &x, listener_play](Touch *t, Event *e)
	{
		if (playbutton->getBoundingBox().containsPoint(t->getLocation()))
		{
			for (int i = 0; i <= x.handpoker.size() - 1; i++)
			{
				if (x.handpoker[i].iostates == 1)
				{
					x.handpoker[i].card_picture->removeFromParent();
					skipbutton->removeFromParent();
					playbutton->removeFromParent();
					
					/*x.handpoker.erase(x.handpoker.begin() + i);*/
					x.handpoker[i].iostates = 0;
				}
			}
		}
		listener_play->setSwallowTouches(false);
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener_play, playbutton);
	//play
}//remain