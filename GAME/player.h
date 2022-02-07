#ifndef _PLAYER_H_
#define _PLAYER_H_

class Cplayer{
private:
	int posi_x;//��ʏ�̈ʒu
	int posi_y;//��ɓ���
	int direct_x;
	int direct_y;

	int coef;//1 or -1
	int stop_count;//1�ȏ�̂Ƃ��͉������Ȃ��B

public:
	Cplayer(int n);
	void decide_direct(int key);//key����(direct_x, direct_y)�����肷��B
	void player_move();//(posi_x, posi_y)�����肷��B

	bool match(int* px, int* py);//(*px, *py)�Ɉ�v���Ă���Ƃ� true

	//�Q�b�^�[
	int* get_px(void);
	int* get_py(void);
	int get_nextx(void);//posi_x + direct_x ���擾�B
	int get_nexty(void);//��ɓ��l
	int get_stopcount(void);
	//�Z�b�^�[
	void stopcount_add(void);
	void stopcount_down(void);
	void stopcount_exchange(void);//stop_count���A0�ȏ��-1�ƂŐ؂�ւ���B
	void change_x(int x);//posi_x��ύX����B
};

int key_get(void);//�L�[�ԍ���Ԃ��B
void key_reset(void);//���擾�̃L�[����𖳌�������B
int title_key_set(void);//�^�C�g����ʂł̃L�[�ԍ���Ԃ��B
int random(int n);//0�`n-1�̐����������_���ɕԂ��B

#endif // _PLAYER_H_
