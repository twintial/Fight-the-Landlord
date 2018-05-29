#include "PokerCard.h"
PokerCard::PokerCard(int num)
{
	iostates = 0;
	if (num <= 51)
	{
		card_number = num % 13 + 1;
	}
	else
	{
		card_number = num;
	}
	//��������

	if (num <= 51)
	{
		kind = num / 13 + 1;
	}
	else
	{
		kind = 0;
	}
	//���滨ɫ
	switch (num)
	{
	case 0:card_picture = Sprite::create("fangkuai_1.png"); break;
	case 1:card_picture = Sprite::create("fangkuai_2.png"); break;
	case 2:card_picture = Sprite::create("fangkuai_3.png"); break;
	case 3:card_picture = Sprite::create("fangkuai_4.png"); break;
	case 4:card_picture = Sprite::create("fangkuai_5.png"); break;
	case 5:card_picture = Sprite::create("fangkuai_6.png"); break;
	case 6:card_picture = Sprite::create("fangkuai_7.png"); break;
	case 7:card_picture = Sprite::create("fangkuai_8.png"); break;
	case 8:card_picture = Sprite::create("fangkuai_9.png"); break;
	case 9:card_picture = Sprite::create("fangkuai_10.png"); break;
	case 10:card_picture = Sprite::create("fangkuai_J.png"); break;
	case 11:card_picture = Sprite::create("fangkuai_Q.png"); break;
	case 12:card_picture = Sprite::create("fangkuai_K.png"); break;
	case 13:card_picture = Sprite::create("meihua_1.png"); break;
	case 14:card_picture = Sprite::create("meihua_2.png"); break;
	case 15:card_picture = Sprite::create("meihua_3.png"); break;
	case 16:card_picture = Sprite::create("meihua_4.png"); break;
	case 17:card_picture = Sprite::create("meihua_5.png"); break;
	case 18:card_picture = Sprite::create("meihua_6.png"); break;
	case 19:card_picture = Sprite::create("meihua_7.png"); break;
	case 20:card_picture = Sprite::create("meihua_8.png"); break;
	case 21:card_picture = Sprite::create("meihua_9.png"); break;
	case 22:card_picture = Sprite::create("meihua_10.png"); break;
	case 23:card_picture = Sprite::create("meihua_J.png"); break;
	case 24:card_picture = Sprite::create("meihua_Q.png"); break;
	case 25:card_picture = Sprite::create("meihua_K.png"); break;
	case 26:card_picture = Sprite::create("hongxin_1.png"); break;
	case 27:card_picture = Sprite::create("hongxin_2.png"); break;
	case 28:card_picture = Sprite::create("hongxin_3.png"); break;
	case 29:card_picture = Sprite::create("hongxin_4.png"); break;
	case 30:card_picture = Sprite::create("hongxin_5.png"); break;
	case 31:card_picture = Sprite::create("hongxin_6.png"); break;
	case 32:card_picture = Sprite::create("hongxin_7.png"); break;
	case 33:card_picture = Sprite::create("hongxin_8.png"); break;
	case 34:card_picture = Sprite::create("hongxin_9.png"); break;
	case 35:card_picture = Sprite::create("hongxin_10.png"); break;
	case 36:card_picture = Sprite::create("hongxin_J.png"); break;
	case 37:card_picture = Sprite::create("hongxin_Q.png"); break;
	case 38:card_picture = Sprite::create("hongxin_K.png"); break;
	case 39:card_picture = Sprite::create("heitao_1.png"); break;
	case 40:card_picture = Sprite::create("heitao_2.png"); break;
	case 41:card_picture = Sprite::create("heitao_3.png"); break;
	case 42:card_picture = Sprite::create("heitao_4.png"); break;
	case 43:card_picture = Sprite::create("heitao_5.png"); break;
	case 44:card_picture = Sprite::create("heitao_6.png"); break;
	case 45:card_picture = Sprite::create("heitao_7.png"); break;
	case 46:card_picture = Sprite::create("heitao_8.png"); break;
	case 47:card_picture = Sprite::create("heitao_9.png"); break;
	case 48:card_picture = Sprite::create("heitao_10.png"); break;
	case 49:card_picture = Sprite::create("heitao_J.png"); break;
	case 50:card_picture = Sprite::create("heitao_Q.png"); break;
	case 51:card_picture = Sprite::create("heitao_K.png"); break;
	case 52:card_picture = Sprite::create("king_s.png"); break;
	case 53:card_picture = Sprite::create("king_b.png"); break;
	}
}
void PokerCard::ClickOut()const
{
	card_picture->runAction(MoveTo::create(0.1, Point(card_picture->getPositionX(), card_picture->getPositionY() + 28)));
	iostates = 1;
}
void PokerCard::ClickIn()const
{
	card_picture->runAction(MoveTo::create(0.1, Point(card_picture->getPositionX(), card_picture->getPositionY() - 28)));
	iostates = 0;
}
void PokerCard::ClickTrigger(PokerCard elem)
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = [elem,listener](Touch *t, Event *e)
	{
		if (elem.card_picture->getBoundingBox().containsPoint(t->getLocation()))
		{
			listener->setSwallowTouches(true);
		}
		return true;
	};
	listener->onTouchEnded = [elem,listener](Touch *t, Event *e)
	{
		if (elem.card_picture->getBoundingBox().containsPoint(t->getLocation()))
		{
			if (elem.iostates == 0)
			{
				elem.ClickOut();
			}
			else
			{
				elem.ClickIn();
			}
		}
		listener->setSwallowTouches(false);
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, elem.card_picture);
}
PokerCard::~PokerCard()
{
}