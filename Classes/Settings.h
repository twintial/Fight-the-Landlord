#ifndef _SETTINGS_H_
#define _SETTINGS_H_
#include <vector>;
using namespace std;

struct play_data
{
	int card_type;//要出牌的牌型
	int card_amount;//要出的牌的数量
	bool isplay_pokers;//玩家有没有出牌
	int out_poker[20];//要出的牌
};
enum CardType
{
	ERROR_TYPE = 0,
	SINGLE_CARD,//单牌
	PAIR,//对子
	TRIPLET,//葫芦
	TRIPLET_SINGLE,//三带一
	TRIPLET_PAIR,//三带二
	SEQUENCE,//顺子
	SEQUENCE_OF_PAIR,//连对
	SEQUENCE_OF_TRIPLET,//飞机
	SEQUENCE_OF_TRIPLET_SINGLE,
	SEQUENCE_OF_TRIPLET_PAIR,
	BOMB,//炸弹
	ROCKET,//王炸
	QUADPLEX_TWO_SINGLE,//四带一*2
	QUADPLEX_TWO_PAIR,//四带二*2
};
//bool isclick = false;
//bool isrecv_struct = false;
#endif // _SETTINGS_H_