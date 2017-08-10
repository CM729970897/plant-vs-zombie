#ifndef __ENTITY_CONST_H__
#define __ENTITY_CONST_H__


#include"cocos2d.h"
USING_NS_CC;
//������Ϸʵ�峣��
//@hanjie 2017.1.7
typedef enum {
	begin_plant = 100,
	sunflower,//���տ�
	wallnut,//���ǽ
	peashooter,//�㶹����
	cherrybomb,//ӣ��ը��
	jalapeno,//������
	flashbamboo,//������
	end_plant,
	torchwood = 130,//�����׮�������ӳɵ��ߣ�
	iceshroom,//����������ʬ���ٵ��ߣ�
	begin_zombie = 150,
	zombie,//��ͨ��ʬ
	buckethead_zombie,//��Ͱ��ʬ
	conehead_zombie,//·�Ͻ�ʬ
	flag_zombie,//���Ľ�ʬ
	end_zombie
}GameEntityType;//��Ϸʵ������

typedef enum{
	invalid  = 0,//��Ч״̬�����ɼ���
	album,//ͼ��״̬��������ʵ�彻������ײ��⣬����Ϸʵ��������ֻ������һ��ʵ�崦�ڸ�״̬��
	valid,//��Ч״̬��ֲ��Ϊ�ڳ�״̬����ʬΪ����״̬��
	attack,//����״̬����ʬ���е�״̬��
	boom//��ը״̬
}GameEntityStatus;//��Ϸʵ��״̬

typedef enum{
	begin_derived_entity_type = 200,
	sunshine,//����
	peabullet,//�㶹�ӵ�
	fire_peabullet,//ӵ�й����ӳɵ��㶹�ӵ�
	gold,//��ʬ�����������Ľ��
	bambooshoot,//�����ӵ�
	end_derived_entity_type
}DerivedEntityType;//����ʵ������

typedef enum{
	nobuff = 400,//û�мӳ�
	fire//�����ӳ�
}BuffType;//��������

typedef enum{
	success = 500,//��Ϸͨ��
	failure,//��Ϸʧ��
	on//��Ϸ����
}GameStatus;

typedef enum{
	main_menu = 600,//��Ϸ�˵�����
	adventure_mode,//��Ϸð��ģʽ����
	survival_mode//��Ϸ����ģʽ����
}GameScene;

//ֲ�����
struct OPT
{
	Point start;       // ֲ���ʼ������е�λ��
	int value;
	int x;
	int y;
};
struct ONOFF
{
	bool on;
	bool on2;
	int value;
	int score;
};

#endif