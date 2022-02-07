#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <vector>

#define BLOCK_V (12)//��ʏc�}�X��
#define BLOCK_H (17)//��ʉ��}�X��

enum backgd_num { NOTHING, BPANEL, HPANEL, HOI, SWAMP, BLOCK, BOMB, GOAL };
int random(int n);//0�`n-1�̐����������_���ɕԂ��B
void frameonly(void);//backgd[][]���O�g�݂̂ɂ���B

class Carray {
private:
	int backgd[BLOCK_V][BLOCK_H];//��ʏ�́A�Œ蕨�̂̈ʒu�Ɩ��O����\���B���(x,y)��backgd[y][x]�ɑΉ��B
	                             //(enum:backgd_num �ɑΉ��j
	int ene_map[BLOCK_V][BLOCK_H];//��ʏ�̓G�̈ʒu����\���B���(x,y)��ene_map[y][x]�ɑΉ��B
                                  //�i���Ȃ�:0, ����:1�ȏ�j
	int bomb_area[BLOCK_V][BLOCK_H];//��ʏ�̃z�C���e�L���͈͂̈ʒu����\���B���(x,y)��bomb_area[y][x]�ɑΉ��B
                                    //�i�͈͊O:0, �͈͓�:1�ȏ�j
	int hoi_left;//�z�C�z�C�c��
	bool Hpanel_on;//H�p�l������ʂɂ���Ƃ� true
	int bomb_unit;//B�p�l����������Ƃ��ɑ�����z�C���e��
	int bomb_left;//�z�C���e�c��

public:
	std::vector<std::vector<int>> vbackgd;//esymbol�̗v�f�i�Œ�̕��́j�̏����i�[����2����vector�i��Q������ x, y, bsymbol�ԍ��j
	std::vector<std::vector<int>> vbomb_area_1;//�z�C���e�L���͈͂̈ʒu���P
	std::vector<std::vector<int>> vbomb_area_2;//�z�C���e�L���͈͂̈ʒu���Q�i��ʂɁu�E�v��\���j
	std::vector<std::vector<int>> vbomb_area_3;//�z�C���e�L���͈͂̈ʒu���R�i��ʂɁu��v��\���j
	std::vector<std::vector<int>> vbomb_area_4;//�z�C���e�L���͈͂̈ʒu���S�i��ʂɁu�E�v��\���j
	std::vector<std::vector<int>> vbomb_effect;//�z�C���e�ɂ��A�G�̎c�����̈ʒu���i��ʂɁu�{�v��\���j

	int swamp[8][2] = {//���n�i��P���� 0�`3�j�ƃp�l���i��P���� 4�`7�j�̈ʒu(��Q������ x, y)
	{13,2},
	{7,4},
	{11,6},
	{3,7},

	{4,1},
	{3,4},
	{11,4},
	{15,6}
	};

	Carray(int enemy_num, int round);
	void init_display(void);//backgd[][]����ʕ\������B
	bool check_gameclear(int* px_0, int* py_0, int* px_1, int* py_1);//ROUND�N���A�𔻒�B
	bool check_gameover(int* px_0, int* py_0, int* px_1, int* py_1);//GAME OVER�𔻒�B
	bool check_movekey_on(int key);//�����������L�[�Ȃ� true
	void vbomb_area1_set(int* x, int* y);//vbomb_area1[][]�ɔ����G���A��ǉ�����B

	int get_backgd(int* x, int* y);//backgd[x][y]�̒l���擾����B
	int get_backgd_int(int x, int y);//backgd[x][y]�̒l���擾����B
	void change_backgd(int* x, int* y, int n);//backgd[x][y]�̒l��n�Ƃ���B
	void change_backgd_int(int x, int y, int n);//backgd[x][y]�̒l��n�Ƃ���B

	int get_enemap(int* x, int* y);//ene_map[x][y]�̒l���擾����B
	void enemap_up(int* x, int* y, int n);//enemap[x][y]�̒l�� +n �Ƃ���B
	void enemap_to_0(int* x, int* y); //enemap[x][y]�̒l�� 0 �ɂ���B

	int get_bomb_area(int* x, int* y);//bomb_area[x][y]�̒l���擾����B
	void bomb_area_up(int* x, int* y, int n);//bomb_area[x][y]�̒l�� +n �Ƃ���B

	int get_hoi(void);//hoi_left���擾�B
	bool get_Hpanel_on(void);//Hpanel_on���擾�B
	int get_bomb(void);//bomb_left���擾
	void lhoi_up(int n);//hoi_left�̒l�� +n �Ƃ���B
	void exchange_H(void);//Hpanel_on�ibool�j��؂�ւ���B
	void lbomb_up(int n);//bomb_left�̒l�� +n �Ƃ���B
	void got_Bpanel(void);//B�p�l���擾����bomb_left�𑝂₷�B
};

#endif // _DISPLAY_H_