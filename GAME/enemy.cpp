#include "enemy.h"

enum enemy_type { P_1, TH_2,  U_3, O_4 };//「_ 」の右の数字はwait_cycleを表す。
enum enemy_shape { TYPE_P, TYPE_TH, TYPE_U, TYPE_O };
enum direction{ LEFT, BACK, RIGHT, FRONT };
//方向転換を表す行列（LEFT, BACK, RIGHT, FRONT）
int turn[4][2][2] = { {{0,1},{-1,0}},{{-1,0},{0,-1}},{{0,-1},{1,0}},{{1,0},{0,1}} };

//以下メンバ定義。
Cenemy::Cenemy(int n, int round) : direct_x(0), direct_y(1), shape_num(1), reversed(false), moved(true), cycle_count(0), stop_count(1){
	//諸定数の準備
	int para[4][7] = {//敵のタイプのパラメータ。行はenum"enemy_type"、列は一部のメンバ変数に対応する。
	{TYPE_P,1,1,50,1,50,250},//P_1
	{TYPE_TH,2,0,2,1,2,6},//TH_2
	{TYPE_U,3,0,3,1,3,4},//U_3
	{TYPE_O,4,1,3,1,3,4}//O_4
	};
	int init_enemyposi[7][2] = {//(posi_x, posi_y)を決定する配列。
	{5,1},
	{13,1},
	{7,3},
	{1,4},
	{15,4},
	{3,6},
	{13,6},
	};
	int enemy_type_sample[4][8] = {//敵のタイプを決定する配列。行はROUND数、列はenum"enemy_type"に対応する。
		{U_3,U_3,U_3,U_3,O_4,O_4,O_4,O_4},//ROUND 1
		{TH_2,TH_2,U_3,U_3,U_3,U_3,O_4,O_4},//ROUND 2
		{P_1,P_1,TH_2,TH_2,TH_2,TH_2,U_3,U_3},//ROUND 3
		{P_1,P_1,P_1,P_1,P_1,P_1,P_1,P_1}//ROUND 4
	};

	//メンバ変数初期化
	posi_x = init_enemyposi[n][0];
	posi_y = init_enemyposi[n][1];
	//  enemy_type_sample[][]から敵のタイプを選び、メンバ変数にpara[][]の各列要素を設定する。、
	int type = enemy_type_sample[round - 1][random(8)];
	for (int i = 0; i < 4; i++) {
		shape_type = para[type][0];
		roll_on_move = para[type][2];
		wait_cycle = para[type][1];
		ratio[i] = para[type][i + 3];
	}
};

int Cenemy::turn_x(int* pdx, int* pdy, int dir) {
	return turn[dir][0][0] * *pdx + turn[dir][0][1] * *pdy;
}
int Cenemy::turn_y(int* pdx, int* pdy, int dir) {
	return turn[dir][1][0] * *pdx + turn[dir][1][1] * *pdy;
}

bool Cenemy::can_turn(Carray* arr, int dir) {
	int vir_nextx = posi_x + turn_x(&direct_x, &direct_y, dir);
	int vir_nexty = posi_y + turn_y(&direct_x, &direct_y, dir);
	if (arr->get_backgd(&vir_nextx, &vir_nexty) != BLOCK) {
		return true;
	}
	else {
		return false;
	}
}

void Cenemy::decide_direct(Carray* arr, bool boolL, bool boolB, bool boolR, bool boolF) {
	int dir = select(boolL*ratio[0], boolB*ratio[1], boolR*ratio[2], boolF*ratio[3]);
	int dx = turn_x(&direct_x, &direct_y, dir), dy = turn_y(&direct_x, &direct_y, dir);
	direct_x = dx;
	direct_y = dy;
}


void Cenemy::decide_perform(Carray* arr) {
	bool boolL = can_turn(arr, LEFT), boolB = can_turn(arr, BACK), boolR = can_turn(arr, RIGHT), boolF = can_turn(arr, FRONT);

	if (1 <= boolL + boolB + boolR + boolF) {
		int dx = direct_x, dy = direct_y;

		if (moved) {//前回のフレームで移動があればdecide_direct()を実行する。
			decide_direct(arr, boolL, boolB, boolR, boolF);
			//(direct_x, direct_y)が反転するかどうか、reversedに格納。
			if ((direct_x == -1 * dx) && (direct_y == -1 * dy)) {
				reversed = true;
			}
			else {
				reversed = false;
			}
			//反転しなければ移動し、反転するときは１フレームの間留まる。
			if (!reversed) {
				posi_x = posi_x + direct_x;
				posi_y = posi_y + direct_y;
				moved = true;
			}
			else {
				moved = false;
			}
		}

		else {//前回のフレームで移動がなければ、(direct_x, direct_y)に沿ってそのまま移動する。
			posi_x = posi_x + direct_x;
			posi_y = posi_y + direct_y;
			moved = true;
			reversed = false;
		}
	}
	//shape_numの決定
	if (!roll_on_move) {//(direct_x, direct_y)に従って決定。
		if ((direct_x == 0) && (direct_y == -1)) {
			shape_num = 0;
		}
		else if ((direct_x == 0) && (direct_y == 1)) {
			shape_num = 1;
		}
		else if ((direct_x == -1) && (direct_y == 0)) {
			shape_num = 2;
		}
		else if ((direct_x == 1) && (direct_y == 0)) {
			shape_num = 3;
		}
	}
	else {
		shape_num = (shape_num + 1) % 4;//0～3を繰り返す。
	}
}

int* Cenemy::get_px() {
	return &posi_x;
}
int* Cenemy::get_py() {
	return &posi_y;
}
int* Cenemy::get_pdx() {
	return &direct_x;
}
int* Cenemy::get_pdy() {
	return &direct_y;
}
int Cenemy::get_shapetype() {
	return shape_type;
}
int* Cenemy::get_shapenum() {
	return &shape_num;
}
bool Cenemy::get_reversed() {
	return reversed;
}
bool Cenemy::get_moved() {
	return moved;
}
int Cenemy::get_cyclecount() {
	return cycle_count;
}
int Cenemy::get_stopcount() {
	return stop_count;
}
void Cenemy::cyclecount_up() {//0～wait_cycleを繰り返す。
	if (1 <= wait_cycle) {
		int c = cycle_count;
		cycle_count = (c + 1) % wait_cycle;
	}
}
void Cenemy::stopcount_add() {
	if (stop_count == 0) {
		stop_count = 18;
	}
}
void Cenemy::stopcount_down() {
	if (0 < stop_count) {
		stop_count--;
	}
}
void Cenemy::freeze_stopcount() {
	stop_count = -1;
}



int select(int a, int b, int c, int d) {
	int r = random(a + b + c + d);
	if (r <= a - 1) {
		return LEFT;
	}
	else if ((a <= r) && (r <= a + b - 1) ) {
		return BACK;
	}
	else if ((a + b <= r) && (r <= a + b + c - 1) ){
		return RIGHT;
	}
	else {
		return FRONT;
	}
}