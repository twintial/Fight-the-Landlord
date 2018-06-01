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
void Player::Action(Sprite* skipbutton, Sprite* playbutton,GameScene* scene)
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
	listener_play->onTouchEnded = [skipbutton, playbutton, scene, this, listener_play](Touch *t, Event *e)
	{
		if (playbutton->getBoundingBox().containsPoint(t->getLocation()))
		{
			for (int i = 0; i <= this->handpoker.size() - 1; i++)
			{
				if (this->handpoker[i].iostates == 1 && this->handpoker[i].played == 0)
				{
					this->handpoker[i].card_picture->removeFromParent();//移除
					this->outpoker.push_back(PokerCard(this->hand[i]));//增加打出牌
					this->handpoker[i].played = 1;//标记为打出
				}
			}
			//skipbutton->removeFromParent();
			//playbutton->removeFromParent();

			scene->ArrangeoutPokers(this);
			scene->ArrangeHandPokers_afterplay(this);
		}
		listener_play->setSwallowTouches(false);
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener_play, playbutton);
	//play
}//remain