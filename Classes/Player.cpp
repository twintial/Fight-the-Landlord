#include"Player.h"
USING_NS_CC;
Player::Player()
{
	IP = "";
	username = "";
	vector<int>hand;
	status = -1;
	lord_point = -1;
}
Player& Player::operator=(Player& x)
{
	return x;
}
void Player::Action(Sprite* skipbutton, Sprite* playbutton,GameScene* scene)
{
	//skip
	auto listener_skip = EventListenerTouchOneByOne::create();
	listener_skip->onTouchBegan = [skipbutton, listener_skip](Touch *t, Event *e)
	{
		if (skipbutton->getBoundingBox().containsPoint(t->getLocation()))
		{
			listener_skip->setSwallowTouches(true);
		}
		return true;
	};
	listener_skip->onTouchEnded = [skipbutton, playbutton, this, listener_skip](Touch *t, Event *e)
	{
		if (skipbutton->getBoundingBox().containsPoint(t->getLocation()))
		{
			skipbutton->removeFromParent();
			playbutton->removeFromParent();
			//使牌移回
			for (int i = 0; i <= this->handpoker.size() - 1; i++)
			{
				if (this->handpoker[i].iostates == 1 && this->handpoker[i].played == 0)
				{
					this->handpoker[i].card_picture->runAction(MoveTo::create(0.01, Point(this->handpoker[i].card_picture->getPositionX(), this->handpoker[i].card_picture->getPositionY() - 28)));
					this->handpoker[i].iostates = 0;
				}
			}
		}
		listener_skip->setSwallowTouches(false);
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener_skip, skipbutton);

	//play
	auto listener_play = EventListenerTouchOneByOne::create();
	listener_play->onTouchBegan = [playbutton, listener_play](Touch *t, Event *e)
	{
		if (playbutton->getBoundingBox().containsPoint(t->getLocation()))
		{
			listener_play->setSwallowTouches(true);
		}
		return true;
	};
	listener_play->onTouchEnded = [skipbutton, playbutton, scene, this, listener_play](Touch *t, Event *e)
	{
		if (playbutton->getBoundingBox().containsPoint(t->getLocation()))
		{
			for (int i = 0; i <= this->handpoker.size() - 1; i++)
			{
				if (this->handpoker[i].iostates == 1 && this->handpoker[i].played == 0)
				{
					this->outpoker.push_back(PokerCard(this->hand[i]));//可能增加打出牌
				}
			}
			if (Operation::CardType(*this))//将改成与上家牌型的比较
			{
				log("%d", Operation::CardType(*this));
				for (int i = 0; i <= this->handpoker.size() - 1; i++)
				{
					if (this->handpoker[i].iostates == 1 && this->handpoker[i].played == 0)
					{
						this->handpoker[i].card_picture->removeFromParent();//移除
						this->handpoker[i].played = 1;//标记为打出,即符合牌型确定可出
					}
				}
				//skipbutton->removeFromParent();
				//playbutton->removeFromParent();
				scene->ArrangeoutPokers(this);
				scene->ArrangeHandPokers_afterplay(this);
			}
			else
			{
				this->outpoker.erase(this->outpoker.begin(), this->outpoker.end());
			}
		}
		listener_play->setSwallowTouches(false);
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener_play, playbutton);
}//remain