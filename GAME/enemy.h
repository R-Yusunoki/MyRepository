#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "array.h"

//�iLEFT, BACK, RIGHT, FRONT�j����A�m����ia, b, c, d�j�łЂƂ��o���B
int select(int a, int b, int c, int d);

class Cenemy {
private:
	int posi_x;//��ʏ�̈ʒu
	int posi_y;//��ɓ���
	int direct_x;
	int direct_y;
	int shape_type;//esymbol�i�G�̌`�j�̑�P���������肷��l
	bool roll_on_move;//�G�̌`���Atrue�Ȃ�i�s���@�ɂ�炸�Afalse�Ȃ�i�s�����ɏ]�������̂ƂȂ�B
	int shape_num;////esymbol�i�G�̌`�j�̑�Q���������肷��l
	int wait_cycle;//�ҋ@�t���[�����i�傫���قǈړ����x���Ȃ�j�B
	int ratio[4];//�i�s��������̊m����

	bool reversed;//dicide_direct()�̑O��ŁA(direct_x, direct_y)�����]����� 1�A���Ȃ���� 0�B
	bool moved;//dicide_direct()�̑O��ŁA�ړ������s������ 1�A����Ȃ���� 0�B
	int cycle_count;//�ҋ@�t���[���𐔂��邽�߂̒l
	int stop_count;//1�ȏ�̂Ƃ��͉������Ȃ��B

public:
	Cenemy(int n, int round);//0 <= n
	int turn_x(int* pdx, int* pdy, int dir);//�����idx, dy�j�� dir �̒l�ɏ]���ē]���������x����
	int turn_y(int* dx, int* dy, int dir);//��L��y����
	bool can_turn(Carray* arr, int dir);//�G�̏�E���E���E�E���󂢂Ă��邩�Abool�l��Ԃ��B
	void decide_direct(Carray* arr, bool boolL, bool boolB, bool boolR, bool boolF);//can_turn()�̒l��select()����A(direct_x, direct_y)�����肷��B
	void decide_perform(Carray* arr);//�G�̓����𐶐�����B

	//�Q�b�^�[
	int* get_px(void);
	int* get_py(void);
	int* get_pdx(void);
	int* get_pdy(void);
	int get_shapetype(void);
	int* get_shapenum(void);
	bool get_reversed(void);//�e�X�g�R�[�h�p
	bool get_moved(void);//�e�X�g�R�[�h�p
	int get_cyclecount(void);
	int get_stopcount(void);

	//�Z�b�^�[
	void cyclecount_up(void);
	void stopcount_add(void);
	void stopcount_down(void);
	void freeze_stopcount(void);//stop_count�� -1 �ɂ���B
};

#endif // _ENEMY_H_
