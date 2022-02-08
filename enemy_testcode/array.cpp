#include <iostream>
#include <stdlib.h>
#include "array.h"


Carray::Carray(int enemy_num, int round) : Hpanel_on(false), bomb_left(0) {
	//諸定数の準備
	int init_block[4][BLOCK_V][BLOCK_H] = {//ROUNDごとのブロック位置情報
	{
	{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
	{5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
	{5,0,5,5,5,0,5,5,5,0,5,0,5,0,5,0,5},
	{5,5,5,0,5,0,5,0,5,0,5,5,5,0,5,5,5},
	{5,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5},
	{5,0,5,5,5,5,5,0,5,5,5,0,5,5,5,0,5},
	{5,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5},
	{5,5,5,0,5,0,5,0,5,0,5,5,5,0,5,5,5},
	{5,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5},
	{5,0,5,5,5,5,5,5,5,5,5,0,5,5,5,0,5},
	{5,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5},
	{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5}
	},

	{
	{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
	{5,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,5},
	{5,0,5,5,5,0,5,5,5,5,5,0,5,0,5,0,5},
	{5,5,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5},
	{5,0,0,0,0,0,0,0,5,0,0,0,5,0,0,0,5},
	{5,0,5,5,5,5,5,0,5,5,5,0,5,5,5,0,5},
	{5,0,0,0,0,0,0,0,5,0,5,0,0,0,0,0,5},
	{5,0,5,0,5,0,5,5,5,0,5,5,5,0,5,5,5},
	{5,0,0,0,0,0,0,0,5,0,0,0,5,0,0,0,5},
	{5,5,5,5,5,5,5,0,5,0,5,0,5,0,5,0,5},
	{5,0,0,0,0,0,0,0,5,0,5,0,0,0,0,0,5},
	{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5}
	},

	{
	{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
	{5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
	{5,0,5,0,5,0,5,5,5,5,5,0,5,0,5,0,5},
	{5,0,5,0,5,0,5,0,5,0,5,5,5,5,5,0,5},
	{5,0,0,0,5,0,0,0,5,0,0,0,5,0,0,0,5},
	{5,0,5,5,5,0,5,5,5,5,5,0,5,0,5,5,5},
	{5,0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,5},
	{5,5,5,0,5,5,5,0,5,0,5,5,5,5,5,0,5},
	{5,0,0,0,5,0,0,0,5,0,0,0,0,0,0,0,5},
	{5,0,5,0,5,0,5,0,5,5,5,0,5,0,5,5,5},
	{5,0,0,0,0,0,5,0,5,0,0,0,0,0,0,0,5},
	{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5}
	},

	{
	{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5},
	{5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
	{5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5},
	{5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
	{5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5},
	{5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
	{5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5},
	{5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
	{5,0,5,0,5,0,5,0,5,0,5,0,5,0,5,0,5},
	{5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5},
	{5,5,5,5,5,5,5,0,5,0,5,5,5,5,5,5,5},
	{5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5}
	}
	};
	int init_weapon[5][2] = { {4,3},{8,6},{12,9},{16,12},{20,15} };//hoi_left, bomb_unitを決定するための配列

	//メンバ変数初期化
	for (int i = 0; i < BLOCK_V; i++) {//backgd[][]
		for (int j = 0; j < BLOCK_H; j++) {
			backgd[i][j] = init_block[round - 1][i][j];
		}
	}
	for (int i = 0; i < BLOCK_V; i++) {//ene_map[][]
		for (int j = 0; j < BLOCK_H; j++) {
			ene_map[i][j] = 0;
		}
	}
	vbackgd.push_back({ 8,1,GOAL });//ゴールをvbackgd[][]に追加
	for (int i = 0; i < 4; i++) {//沼地をbackgd[][]とvbackgd[][]に追加。
		backgd[swamp[i][1]][swamp[i][0]] = SWAMP;
		vbackgd.push_back({ swamp[i][0], swamp[i][1], SWAMP });
	}
	for (int i = 0; i < BLOCK_V; i++) {//bomb_area[][]
		for (int j = 0; j < BLOCK_H; j++) {
			bomb_area[i][j] = 0;
		}
	}
	int ran = random(4) + 4;//Ｂパネルをbackgd[][]とvbackgd[][]に追加。
	backgd[swamp[ran][1]][swamp[ran][0]] = BPANEL;
	vbackgd.push_back({ swamp[ran][0], swamp[ran][1], BPANEL });

	hoi_left = init_weapon[enemy_num - 1][0];
	bomb_unit = init_weapon[enemy_num - 1][1];
}

void Carray::init_display() {
	for (int i = 0; i < BLOCK_V; i++) {
		for (int j = 0; j < BLOCK_H; j++) {
			switch (backgd[i][j]){
				case BLOCK:
					std::cout << "■";
					break;
				default:
					std::cout << "  ";
					break;
			}
		}
		std::cout << "\n";
	}
	std::cout << "  ROUND" << "\n";
}

bool Carray::check_gameclear(int* px_0, int* py_0, int* px_1, int* py_1) {
	if ((*py_0 == 1) && (*py_1 == 1)) {
		if ((*px_0 == 7) && (*px_1 == 9)) {
			return true;
		}
		else if ((*px_0 == 9) && (*px_1 == 7)) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		return false;
	}
}
bool Carray::check_gameover(int* px_0, int* py_0, int* px_1, int* py_1) {
	bool c_0 = (1 <= get_enemap(px_0, py_0)) && (get_backgd(px_0, py_0) != HOI) && (get_backgd(px_0, py_0) != SWAMP);
	bool c_1 = (1 <= get_enemap(px_1, py_1)) && (get_backgd(px_1, py_1) != HOI) && (get_backgd(px_1, py_1) != SWAMP);

	return (c_0 || c_1);
}
bool Carray::check_movekey_on(int key) {
	if ((key == 72) || (key == 75) || (key == 77) || (key == 80)) {
		return true;
	}
	else {
		return false;
	}
}
void Carray::vbomb_area1_set(int* x, int* y) {
	for (int n = 1; n <= 2; n++) {
		if (backgd[*y][*x + n] != BLOCK) {
			vbomb_area_1.push_back({*x + n, *y});
		}
		else {
			break;
		}
	}
	for (int n = -1; -2 <= n; n--) {
		if (backgd[*y][*x + n] != BLOCK) {
			vbomb_area_1.push_back({ *x + n, *y });
		}
		else {
			break;
		}
	}
	for (int n = 1; n <= 2; n++) {
		if (backgd[*y + n][*x] != BLOCK){
			vbomb_area_1.push_back({ *x, *y + n });
		}
		else {
			break;
		}
	}
	for (int n = -1; -2 <= n; n--) {
		if (backgd[*y + n][*x] != BLOCK) {
			vbomb_area_1.push_back({ *x, *y + n });
		}
		else {
			break;
		}
	}
	vbomb_area_1.push_back({ *x, *y });
}

int Carray::get_backgd(int* x, int* y) {
	return backgd[*y][*x];
}
int Carray::get_backgd_int(int x, int y) {
	return backgd[y][x];
}
void Carray::change_backgd(int* x, int* y, int n) {
	backgd[*y][*x] = n;
}
void Carray::change_backgd_int(int x, int y, int n) {
	backgd[y][x] = n;
}
int Carray::get_enemap(int* x, int* y) {
	return ene_map[*y][*x];
}
void Carray::enemap_up(int* x, int* y, int n) {
	ene_map[*y][*x] += n;
}
void Carray::enemap_to_0(int* x, int* y) {
	ene_map[*y][*x] = 0;
}
int Carray::get_bomb_area(int* x, int* y) {
	return bomb_area[*y][*x];
}
void Carray::bomb_area_up(int* x, int* y, int n) {
	bomb_area[*y][*x] += n;
}

int Carray::get_hoi() {
	return hoi_left;
}
bool Carray::get_Hpanel_on() {
	return Hpanel_on;
}
int Carray::get_bomb() {
	return bomb_left;
}
void Carray::lhoi_up(int n) {
	hoi_left += n;
}
void Carray::exchange_H() {
	Hpanel_on = (Hpanel_on + 1) % 2;
}
void Carray::lbomb_up(int n) {
	bomb_left += n;
}
void Carray::got_Bpanel(){
	bomb_left += bomb_unit;
}


int random(int n) {
	return rand() % n;
}
void frameonly() {
	int frame[BLOCK_V][BLOCK_H];
	for (int i = 0; i < BLOCK_V; i++) {
		for (int k = 1; k < BLOCK_H - 1; k++) {
			frame[i][k] = NOTHING;
		}
		frame[i][0] = BLOCK;
		frame[i][BLOCK_H - 1] = BLOCK;
	}
	for (int j = 1; j < BLOCK_H - 1; j++) {
		frame[0][j] = BLOCK;
		frame[BLOCK_V - 1][j] = BLOCK;
	}

	for (int i = 0; i < BLOCK_V; i++) {
		for (int j = 0; j < BLOCK_H; j++) {
			switch (frame[i][j]) {
			case BLOCK:
				std::cout << "■";
				break;
			case NOTHING:
				std::cout << "　";
				break;
			}
		}
		std::cout << "\n";
	}
}