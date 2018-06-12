#include"Player.h"
USING_NS_CC;
Player::Player()
{
	IP = "";
	username = "";
	vector<int>hand;
	status = -1;
	lord_point = -1;
	playercode = -1;
	isready = false;
}
Player& Player::operator=(Player& x)
{
	return x;
}
void Player::Action(Button* skipbutton, Button* playbutton,GameScene* scene)
{
	//skip
	skipbutton->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::ENDED:
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
			break;
		default:
			break;
		}
	});
	//play
	playbutton->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::ENDED:
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
				skipbutton->removeFromParent();
				playbutton->removeFromParent();
				scene->ArrangeoutPokers(this);
				scene->ArrangeHandPokers_afterplay(this);
			}
			else
			{
				this->outpoker.erase(this->outpoker.begin(), this->outpoker.end());
			}
			break;
		}
	});
}//remain