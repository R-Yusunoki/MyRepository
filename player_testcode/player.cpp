#include <conio.h>
#include "player.h"

int key_get() {
	int key = 1;

	if (_kbhit()) {
		key = _getch();
		if (key == 0 || key == 224) {
			key = _getch();
		}
	}
	return key;
}
void key_reset() {
	int key;
	while (_kbhit()) {
		key = _getch();
	}
	key = 1;
}
int title_key_set() {
	int key;
	while (1){
		key = _getch();
		if ((49 <= key) && (key <= 53)) {
			break;
		}
	}
	return key - 48;
}

//以下メンバ定義。
Cplayer::Cplayer(int n) : direct_x(0), direct_y(0), stop_count(0){
	//定数の定義
	int player_para[2][3] = {//(x,y,coef)を与える配列
	{9,10,1},
	{7,10,-1}
	};
	posi_x = player_para[n][0];
	posi_y = player_para[n][1];
	coef = player_para[n][2];
}

void Cplayer::decide_direct(int key) {
	switch (key) {
	case 75://左
		direct_x = -1 * coef;
		direct_y = 0;
		break;
	case 77://右
		direct_x = 1 * coef;
		direct_y = 0;
		break;
	case 72://上
		direct_x = 0;
		direct_y = -1;
		break;
	case 80://下
		direct_x = 0;
		direct_y = 1;
		break;
	}
}

void Cplayer::player_move() {
	posi_x = posi_x + direct_x;
	posi_y = posi_y + direct_y;
}


int* Cplayer::get_px() {
	return &posi_x;
}
int* Cplayer::get_py() {
	return &posi_y;
}

int Cplayer::get_nextx() {
	return posi_x + direct_x;
}
int Cplayer::get_nexty() {
	return posi_y + direct_y;
}

int Cplayer::get_stopcount(){
	return stop_count;
}
void Cplayer::stopcount_add() {
	if (stop_count == 0) {
		stop_count = 1;
	}
}
void Cplayer::stopcount_down() {
	if (0 < stop_count) {
		stop_count -= 1;
	}
}
void Cplayer::stopcount_exchange() {
	if (0 <= stop_count) {
		stop_count = -1;
	}
	else if (stop_count == -1) {
		stop_count = 0;
	}
}
void Cplayer::change_x(int x) {
	posi_x = x;
}
bool Cplayer::match(int* px, int* py) {
	if ((posi_x == *px) && (posi_y == *py)) {
		return true;
	}
	else {
		return false;
	}
}