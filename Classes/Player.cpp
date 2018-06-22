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
	isplay_pokers = false;//
}
Player::~Player()
{

}
Player& Player::operator=(Player& x)
{
	return x;
}
void Player::Action(Button* skipbutton, Button* playbutton, play_data* datas, GameScene* scene)
{
	//�����Լ��Ĳ���ͼƬ
	if (scene->getChildByTag(3) != NULL)
	{
		local_skip->removeFromParent();
	}
	//skip
	skipbutton->addTouchEventListener([=](Ref* pSender, Widget::TouchEventType type)
	{
		switch (type)
		{
		case cocos2d::ui::Widget::TouchEventType::ENDED:
			skipbutton->removeFromParent();
			playbutton->removeFromParent();
			//����������
			datas->isplay_pokers = false;
			local_skip = Sprite::create("skip.png");
			local_skip->setTag(3);
			local_skip->setPosition(612, 320);
			scene->addChild(local_skip);
			//ʹ���ƻ�
			for (int i = 0; i <= this->handpoker.size() - 1; i++)
			{
				if (this->handpoker[i].iostates == 1 && this->handpoker[i].played == 0)
				{
					this->handpoker[i].card_picture->runAction(MoveTo::create(0.01, Point(this->handpoker[i].card_picture->getPositionX(), this->handpoker[i].card_picture->getPositionY() - 28)));
					this->handpoker[i].iostates = 0;
				}
			}
			//ȥ����ʱ��
			if (scene->getChildByTag(30) != NULL)
			{
				scene->removeChildByTag(30, true);
				scene->unschedule(schedule_selector(GameScene::TimePass));
			}
			scene->isclick = true;
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
			////���֮ǰ��outpoker��ûɾ����ɾ��
			//if (this->outpoker.size() != 0)
			//{
			//	this->outpoker.erase(this->outpoker.begin(), this->outpoker.end());
			//}
			for (int i = 0; i <= this->handpoker.size() - 1; i++)
			{
				if (this->handpoker[i].iostates == 1 && this->handpoker[i].played == 0)
	    		{
					this->outpoker.push_back(PokerCard(this->hand[i]));//�������Ӵ����
				}
			}
			if (Operation::TypeCompare(*this,datas))//���ĳ����ϼ����͵ıȽ�
			{
				log("ct=%d", Operation::CardType(*this));
				for (int i = 0; i <= this->handpoker.size() - 1; i++)
				{
					if (this->handpoker[i].iostates == 1 && this->handpoker[i].played == 0)
					{
						this->handpoker[i].card_picture->removeFromParent();//�Ƴ�
						this->handpoker[i].played = 1;//���Ϊ���,����������ȷ���ɳ�
					}
				}
				skipbutton->removeFromParent();
				playbutton->removeFromParent();
				scene->ArrangeOutPokers(this);
				scene->ArrangeHandPokers_afterplay(this);

				datas->card_amount = this->outpoker.size();
				datas->card_type = Operation::CardType(*this);
				datas->isplay_pokers = true;
				//��������ӽ����ݰ���
				memset(datas->out_poker, 0, sizeof(datas->out_poker));
				for (int i = 0; i <= this->outpoker.size() - 1; i++)
				{
					datas->out_poker[i] = this->outpoker[i].num;
				}
				//ȥ����ʱ��
				if (scene->getChildByTag(30) != NULL)
				{
					scene->removeChildByTag(30, true);
					scene->unschedule(schedule_selector(GameScene::TimePass));
				}
				scene->isclick = true;
			}
			else
			{
				log("not allowed");
				this->outpoker.erase(this->outpoker.begin(), this->outpoker.end());
			}
			break;
		default:
			break;
		}
	});
}//remain