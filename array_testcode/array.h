#ifndef _DISPLAY_H_
#define _DISPLAY_H_

#include <vector>

#define BLOCK_V (12)//画面縦マス数
#define BLOCK_H (17)//画面横マス数

enum backgd_num { NOTHING, BPANEL, HPANEL, HOI, SWAMP, BLOCK, BOMB, GOAL };
int random(int n);//0～n-1の整数をランダムに返す。
void frameonly(void);//backgd[][]を外枠のみにする。

class Carray {
private:
	int backgd[BLOCK_V][BLOCK_H];//画面上の、固定物体の位置と名前情報を表す。画面(x,y)はbackgd[y][x]に対応。
	                             //(enum:backgd_num に対応）
	int ene_map[BLOCK_V][BLOCK_H];//画面上の敵の位置情報を表す。画面(x,y)はene_map[y][x]に対応。
                                  //（いない:0, いる:1以上）
	int bomb_area[BLOCK_V][BLOCK_H];//画面上のホイ爆弾有効範囲の位置情報を表す。画面(x,y)はbomb_area[y][x]に対応。
                                    //（範囲外:0, 範囲内:1以上）
	int hoi_left;//ホイホイ残数
	bool Hpanel_on;//Hパネルが画面にあるとき true
	int bomb_unit;//Bパネルを取ったときに増えるホイ爆弾数
	int bomb_left;//ホイ爆弾残数

public:
	std::vector<std::vector<int>> vbackgd;//esymbolの要素（固定の物体）の情報を格納する2次元vector（第２次元は x, y, bsymbol番号）
	std::vector<std::vector<int>> vbomb_area_1;//ホイ爆弾有効範囲の位置情報１
	std::vector<std::vector<int>> vbomb_area_2;//ホイ爆弾有効範囲の位置情報２（画面に「・」を表示）
	std::vector<std::vector<int>> vbomb_area_3;//ホイ爆弾有効範囲の位置情報３（画面に「♯」を表示）
	std::vector<std::vector<int>> vbomb_area_4;//ホイ爆弾有効範囲の位置情報４（画面に「・」を表示）
	std::vector<std::vector<int>> vbomb_effect;//ホイ爆弾による、敵の残がいの位置情報（画面に「＋」を表示）

	int swamp[8][2] = {//沼地（第１次元 0～3）とパネル（第１次元 4～7）の位置(第２次元は x, y)
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
	void init_display(void);//backgd[][]を画面表示する。
	bool check_gameclear(int* px_0, int* py_0, int* px_1, int* py_1);//ROUNDクリアを判定。
	bool check_gameover(int* px_0, int* py_0, int* px_1, int* py_1);//GAME OVERを判定。
	bool check_movekey_on(int key);//引数が方向キーなら true
	void vbomb_area1_set(int* x, int* y);//vbomb_area1[][]に爆風エリアを追加する。

	int get_backgd(int* x, int* y);//backgd[x][y]の値を取得する。
	int get_backgd_int(int x, int y);//backgd[x][y]の値を取得する。
	void change_backgd(int* x, int* y, int n);//backgd[x][y]の値をnとする。
	void change_backgd_int(int x, int y, int n);//backgd[x][y]の値をnとする。

	int get_enemap(int* x, int* y);//ene_map[x][y]の値を取得する。
	void enemap_up(int* x, int* y, int n);//enemap[x][y]の値を +n とする。
	void enemap_to_0(int* x, int* y); //enemap[x][y]の値を 0 にする。

	int get_bomb_area(int* x, int* y);//bomb_area[x][y]の値を取得する。
	void bomb_area_up(int* x, int* y, int n);//bomb_area[x][y]の値を +n とする。

	int get_hoi(void);//hoi_leftを取得。
	bool get_Hpanel_on(void);//Hpanel_onを取得。
	int get_bomb(void);//bomb_leftを取得
	void lhoi_up(int n);//hoi_leftの値を +n とする。
	void exchange_H(void);//Hpanel_on（bool）を切り替える。
	void lbomb_up(int n);//bomb_leftの値を +n とする。
	void got_Bpanel(void);//Bパネル取得時にbomb_leftを増やす。
};

#endif // _DISPLAY_H_