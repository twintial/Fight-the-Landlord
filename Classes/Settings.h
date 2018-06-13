#ifndef _SETTINGS_H_
#define _SETTINGS_H_
#include <vector>;
using namespace std;

struct play_data
{
	int card_type;//Ҫ���Ƶ�����
	int card_amount;//Ҫ�����Ƶ�����
	bool isplay_pokers;//�����û�г���
	int out_poker[20];//Ҫ������
};
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
//bool isclick = false;
//bool isrecv_struct = false;
#endif // _SETTINGS_H_