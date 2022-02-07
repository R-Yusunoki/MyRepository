#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "array.h"

//（LEFT, BACK, RIGHT, FRONT）から、確率比（a, b, c, d）でひとつ取り出す。
int select(int a, int b, int c, int d);

class Cenemy {
private:
	int posi_x;//画面上の位置
	int posi_y;//上に同じ
	int direct_x;
	int direct_y;
	int shape_type;//esymbol（敵の形）の第１次元を決定する値
	bool roll_on_move;//敵の形が、trueなら進行方法によらず、falseなら進行方向に従ったものとなる。
	int shape_num;////esymbol（敵の形）の第２次元を決定する値
	int wait_cycle;//待機フレーム数（大きいほど移動が遅くなる）。
	int ratio[4];//進行方向決定の確率比

	bool reversed;//dicide_direct()の前後で、(direct_x, direct_y)が反転すれば 1、しなければ 0。
	bool moved;//dicide_direct()の前後で、移動が実行されれば 1、されなければ 0。
	int cycle_count;//待機フレームを数えるための値
	int stop_count;//1以上のときは何もしない。

public:
	Cenemy(int n, int round);//0 <= n
	int turn_x(int* pdx, int* pdy, int dir);//方向（dx, dy）を dir の値に従って転換した後のx成分
	int turn_y(int* dx, int* dy, int dir);//上記のy成分
	bool can_turn(Carray* arr, int dir);//敵の上・下・左・右が空いているか、bool値を返す。
	void decide_direct(Carray* arr, bool boolL, bool boolB, bool boolR, bool boolF);//can_turn()の値とselect()から、(direct_x, direct_y)を決定する。
	void decide_perform(Carray* arr);//敵の動きを生成する。

	//ゲッター
	int* get_px(void);
	int* get_py(void);
	int* get_pdx(void);
	int* get_pdy(void);
	int get_shapetype(void);
	int* get_shapenum(void);
	bool get_reversed(void);//テストコード用
	bool get_moved(void);//テストコード用
	int get_cyclecount(void);
	int get_stopcount(void);

	//セッター
	void cyclecount_up(void);
	void stopcount_add(void);
	void stopcount_down(void);
	void freeze_stopcount(void);//stop_countを -1 にする。
};

#endif // _ENEMY_H_
