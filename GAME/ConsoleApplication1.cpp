#include <iostream>
#include <Windows.h>
#include <time.h>
#include <string>
#include <vector>
#include "player.h"
#include "enemy.h"
#include "array.h"


#define T_UNIT (250)//１ゲームループの時間
#define ROUND (4)//全ラウンド数
#define HOI_X (15)//ホイホイ残数表示 x位置
#define BOMB_X (12)//爆弾残数表示 x位置

HANDLE hCons = GetStdHandle(STD_OUTPUT_HANDLE);//WindowsAPIのインスタンス
COORD pos;
void console_draw(int* x, int* y, std::string c);//画面の指定座標に文字を表示。
void console_draw_int(int x, int y, std::string c);//上に同じ。
void cursor_reset(void);//画面のカーソルを規定位置へ移動。

void ready(void);//ゲーム開始前の準備をする。
void gameclear(int* px_0, int* py_0, int* px_1, int* py_1);//ROUNDクリア処理
void gameover(int* px_0, int* py_0, int* px_1, int* py_1);//GAME OVER処理
void excellent(void);//全ROUNDクリア処理


int main()
{
	/*各種宣言・定義*/
	int enemy_num = 1;//敵の数
	int key = 1;//キー入力を格納する変数
	int s_time, e_time, c_period, round_num = 1;//ROUND数

	std::string psymbol[2] = { "◎","○" };	//プレーヤーを表す文字配列
	std::string bsymbol[8] = { "  ", "Ｂ", "Ｈ", "※", "＊", "■", "●", "◇"};	//Carray.vbackgd[][]の要素
	std::string esymbol[4][4] = { {"｜","◯","｜","●"}, {"Ο","Θ","(.",".)"},  {"∩","∪","⊂","⊃"},  {"ｏ","Ｏ","ｏ","Ｏ"} };//Cenemy.shape_typeに対応

	//タイトル画面、敵の数の選択と入力
	system("cls");
	Sleep(1000);
	frameonly();
	console_draw_int(2, 3, "敵の数を 1 ～ 5 からえらび、");
	console_draw_int(2, 5, "「1」 ～ 「5」のテンキーを");
	console_draw_int(3, 6, "押してください。");
	enemy_num = title_key_set();

	//各ROUNDの進行（ROUNDのループ）
	while (round_num <= ROUND) {

		//各インスタンス生成
		Carray* array = new Carray(enemy_num, round_num);
		Cplayer* player[2] = { new Cplayer(0), new Cplayer(1) };//プレーヤーのインスタンス

		int int_array[7], r = random(7);//{0,1,2,3,4,5,6}をスライドした配列を作成。
		for (int i = 0; i < 7; i++) {
			int_array[i] = (r + i) % 7;
		}
		std::vector<Cenemy*> enemy;//各敵のインスタンスを格納するvector
		for (int i = 0; i < enemy_num; i++) {
			enemy.push_back(new Cenemy(int_array[i], round_num));
		}

		//確率1/2でプレーヤー初期位置を入れ替える。
		if (random(2) == 0) {
			player[0]->change_x(7);
			player[1]->change_x(9);
		}

		//ゲーム開始前画面の準備
		system("cls");
		Sleep(1000);
		array->init_display();
		console_draw_int(8, 1, "◇");//ゴールを画面に表示。
		for (int i = 0; i < 2; i++) { //プレーヤーを画面に表示。
			console_draw(player[i]->get_px(), player[i]->get_py(), psymbol[i]);
		}
		console_draw_int(4, BLOCK_V, std::to_string(round_num));//ROUND数を画面に表示。
		ready();
		console_draw_int(HOI_X, BLOCK_V, std::to_string(array->get_hoi()));//ホイホイ残数を画面に表示。
		console_draw_int(BOMB_X, BLOCK_V, std::to_string(array->get_bomb()));//爆弾残数を画面に表示。
		for (unsigned int n = 0; n < array->vbackgd.size(); n++) {//Carray.vbackgd[][]を画面に表示。
			int* p_0 = &array->vbackgd[n][0];
			console_draw(p_0, p_0 + 1, bsymbol[*(p_0 + 2)]);
		}
		for (int i = 0; i < enemy_num; i++) { //敵を画面に表示
			console_draw(enemy[i]->get_px(), enemy[i]->get_py(), esymbol[enemy[i]->get_shapetype()][1]);
		}
		key_reset();//開始前に押したキーを無効化。

		//ゲーム進行（ゲームのループ）
		/*～パラメータ群（特に Carray の backgd[][]、ene_map[][]、bomb_area[][]、vbackgd[][]、vbomb_area1～4[][]）から、
		　次のフレームのパラメータ群を決定する。*/
		while (1) {

			s_time = clock();

			int* px[2] = { player[0]->get_px(),player[1]->get_px() };
			int* py[2] = { player[0]->get_py(),player[1]->get_py() };

			//RoundClear処理
			if (array->check_gameclear(px[0], py[0], px[1], py[1]) ) {
				gameclear(px[0], py[0], px[1], py[1]);
				break;
			}
			//GameOver処理
			if (array->check_gameover(px[0], py[0], px[1], py[1]) ) {
				for (int i = 0; i < 2; i++) {
					if (1 <= array->get_enemap(px[i], py[i])) {
						console_draw(px[i], py[i], "＋");
						cursor_reset();
					}
				}
				gameover(px[0], py[0], px[1], py[1]);
				round_num--;
				break;
			}

			//画面からの消去
			//  プレーヤーを画面から消去。
			for (int i = 0; i < 2; i++) {
				console_draw(px[i], py[i], "  ");
			}
			//  敵をCarray.ene_map[][]と画面から消去。（ene_map[][]の参照はすんでいるため、ここで消去しておく。）
			for (int i = 0; i < enemy_num; i++) {
				array->enemap_to_0(enemy[i]->get_px(), enemy[i]->get_py());
				console_draw(enemy[i]->get_px(), enemy[i]->get_py(), "　");
			}
			//  Carray.vbomb_area_4[][]に基づいて、爆風を画面から消去し、Carray.bomb_area[][]に -1 反映する。
			if (!array->vbomb_area_4.empty()) {
				for (unsigned int n = 0; n < array->vbomb_area_4.size(); n++) {
					int* p_0 = &array->vbomb_area_4[n][0];
					console_draw(p_0, p_0 + 1, "　");
					array->bomb_area_up(p_0, p_0 + 1, -1);
				}
				array->vbomb_area_4.clear();
			}
			//  Carray.vbomb_effect[][]に基づいて、敵の残がいを画面から消去。
			if (!array->vbomb_effect.empty()) {
				for (unsigned int n = 0; n < array->vbomb_effect.size(); n++) {
					int* p_0 = &array->vbomb_effect[n][0];
					console_draw(p_0, p_0 + 1, "　");
				}
				array->vbomb_effect.clear();
			}
			//↑ここまで画面からの消去

			//ホイホイ残数が0になり次第、Hパネルの出現（Hパネルを Carray.vbackgd[][]とCarray.backgd[][]に追加）
			if ((array->get_hoi() == 0) && (!array->get_Hpanel_on()) ) {
				int ran = random(4);
				for (int i = 0; i < 4; i++) {
					int j = 4 + (ran + i) % 4;//4～7をランダムに取り出す。
					int* ps_x = &array->swamp[j][0], * ps_y = &array->swamp[j][1];
					if (!player[0]->match(ps_x, ps_y) && !player[1]->match(ps_x, ps_y) && array->get_backgd(ps_x, ps_y) == NOTHING ){//画面上何もないところを探す。
						array->vbackgd.push_back({ array->swamp[j][0],array->swamp[j][1],HPANEL });
						array->change_backgd(&array->swamp[j][0], &array->swamp[j][1], HPANEL);
						array->exchange_H();
						break;
					}
				}
			}

			//プレーヤーが沼地に入ったときの処理（Cplayer.stop_countの変更）、パネルを取ったときの処理
			for (int i = 0; i < 2; i++) {
				if ((2 <= random(5)) && (array->get_backgd(px[i], py[i]) == SWAMP)) {//沼地
					player[i]->stopcount_add();
				}
				if (array->get_backgd(px[i], py[i]) == BPANEL) {//Bパネル
					array->change_backgd(px[i], py[i], NOTHING);
					array->got_Bpanel();
					for (int n = array->vbackgd.size() - 1; 0 <= n; n--) {//パネルをvbackgd[][]から消去。
						if ((array->vbackgd[n][2] == BPANEL)) {
							array->vbackgd.erase(array->vbackgd.begin() + n);
							break;
						}
					}
					console_draw_int(BOMB_X, BLOCK_V, std::to_string(array->get_bomb()) + " ");//画面のホイ爆弾残数の更新
				}
				if (array->get_backgd(px[i], py[i]) == HPANEL) {//Hパネル
					array->change_backgd(px[i], py[i], NOTHING);
					array->exchange_H();
					array->lhoi_up(10);
					for (int n = array->vbackgd.size() - 1; 0 <= n; n--) {//パネルをvbackgd[][]から消去。
						if ((array->vbackgd[n][2] == HPANEL)) {
							array->vbackgd.erase(array->vbackgd.begin() + n);
							break;
						}
					}
					console_draw_int(HOI_X, BLOCK_V, std::to_string(array->get_hoi()));//画面のホイホイ残数の更新
				}
			}

			//vbomb_areaの引き渡し
			//  Carray.vbomb_area_3[][]をCarray.vbomb_area_4[][]に引き渡す。
			if (!array->vbomb_area_3.empty()){
				array->vbomb_area_4 = array->vbomb_area_3;
				array->vbomb_area_3.clear();
			}
			//  Carray.vbomb_area_2[][]をCarray.vbomb_area_3[][]に引き渡す。
			if (!array->vbomb_area_2.empty()){
				array->vbomb_area_3 = array->vbomb_area_2;
				array->vbomb_area_2.clear();
			}

			//キー操作
			key = key_get();//キー入力を１つだけ格納。
			//　十字キーを押したとき、移動する。
			if (array->check_movekey_on(key)) {
				for (int i = 0; i < 2; i++) {
					if (player[i]->get_stopcount() == 0) {
						player[i]->decide_direct(key);
						int next_x = player[i]->get_nextx(), next_y = player[i]->get_nexty();
						if (array->get_backgd_int(next_x, next_y) != BLOCK) {//進行方向が存在すれば移動。
							player[i]->player_move();
						}
					}
				}
			}
			//  Tabキーを押したとき、ホイホイをvbackgd[][]とbackgd[][]に追加する。（既に置かれたホイホイ、沼地の上には置けない。）		
			else if (key == 9) {
				for (int i = 0; i < 2; i++) {
					if ((1 <= array->get_hoi()) && (array->get_backgd(px[i], py[i])) == NOTHING) {
						array->vbackgd.push_back({ *px[i], *py[i], HOI });
						array->change_backgd(px[i], py[i], HOI);
						array->lhoi_up(-1);
						console_draw_int(HOI_X, BLOCK_V, std::to_string(array->get_hoi()) + " ");//画面のホイホイ残数の更新
						cursor_reset();
					}
				}
			}
			//　Shiftキーを押したとき
			/*　　爆弾セットなし（vbomb_area_1[][]が空である）のとき、プレーヤー0について、爆弾をvbackgd[][]とbackgd[][]に追加する。（沼地の上には置けない。）
				  また「vbomb_area_1[][]」を作成する。*/
			else if ((key == 32) && (1 <= array->get_bomb()) && (array->vbomb_area_1.empty()) && (array->get_backgd(px[0], py[0]) != SWAMP)) {
				array->vbackgd.push_back({ *px[0], *py[0], BOMB });
				array->change_backgd(px[0], py[0], BLOCK);//爆弾はbackgd[][]上では、壁と同一視する。
				array->vbomb_area1_set(px[0], py[0]);
				array->lbomb_up(-1);
				console_draw_int(BOMB_X, BLOCK_V, "  ");//画面のホイ爆弾残数の更新
				console_draw_int(BOMB_X, BLOCK_V, std::to_string(array->get_bomb()));
				cursor_reset();

				//ホイホイの上に置いた場合は、そのホイホイをvbackgd[][]から消去する。
				for (int n = array->vbackgd.size() - 1; 0 <= n; n--) {
					if ((array->vbackgd[n][2] == HOI) && (array->vbackgd[n][0] == *px[0]) && (array->vbackgd[n][1] == *py[0])) {
						array->vbackgd.erase(array->vbackgd.begin() + n);
						break;
					}
				}

			}
			/*　　爆弾セットあり（vbomb_area_1[][]が空ではない）のとき、爆弾の効果範囲をbomb_area[][]に +1 反映し、爆弾をvbackgd[][]とbackgd[][]]から消去する。
				  また、vbomb_area_1をvbomb_area_2に引き渡す。*/
			else if ((key == 32) && (!array->vbomb_area_1.empty())) {
				for (int n = array->vbackgd.size() - 1; 0 <= n; n--) {
					if (array->vbackgd[n][2] == BOMB) {
						array->change_backgd(&array->vbackgd[n][0], &array->vbackgd[n][1], NOTHING);
						array->vbackgd.erase(array->vbackgd.begin() + n);
						break;
					}
				}
				for (unsigned int n = 0; n < array->vbomb_area_1.size(); n++) {
					int* p_0 = &array->vbomb_area_1[n][0];
					array->bomb_area_up(p_0, p_0 + 1, 1);
				}
				array->vbomb_area_2 = array->vbomb_area_1;
				array->vbomb_area_1.clear();
			}
			//　「0」キーを押したとき、DuoとSoloを切り替える。
			else if (key == 48) {
				player[1]->stopcount_exchange();
				if (0 <= player[1]->get_stopcount()) {
					console_draw_int(7, 12, " Duo ");
				}
				else if (player[1]->get_stopcount() == -1) {//プレーヤー１のstop_countが -1 のときは操作無効。
					console_draw_int(7, 12, " Solo");
				}
			}
			//　Escキーでゲームをやめる。
			else if (key == 27) {
				round_num = ROUND + 1;
				Sleep(500);
				system("cls");
				Sleep(1000);
				break;
			}
			//↑ここまでキー操作

			//プレーヤーのstop_countをリセット。
			for (int i = 0; i < 2; i++) {
				player[i]->stopcount_down();
			}

			//敵がホイホイに入ったときの処理、爆風にいるときの処理
			for (int i = 0; i < enemy_num; i++) {
				//敵がホイホイに入ったときの処理（Cenemy.stop_countの付加、ホイホイの消去）
				if ((enemy[i]->get_stopcount() == 0) && (array->get_backgd(enemy[i]->get_px(), enemy[i]->get_py()) == HOI) ) {
					enemy[i]->stopcount_add();

					//そのホイホイをvbackgd、backgd[][]から消去する。
					for (int n = array->vbackgd.size() - 1; 0 <= n; n--) {
						if ((array->vbackgd[n][2] == HOI) && (array->vbackgd[n][0] == *enemy[i]->get_px()) && (array->vbackgd[n][1] == *enemy[i]->get_py()) ) {
							array->vbackgd.erase(array->vbackgd.begin() + n);
							array->change_backgd(enemy[i]->get_px(), enemy[i]->get_py(), NOTHING);
							break;
						}
					}

				}
				//敵が爆風にいるときの処理（stop_countを -1 にし、常に動かないようにする。vbomb_effect[][]に反映する。）
				else if (1 <= array->get_bomb_area(enemy[i]->get_px(), enemy[i]->get_py()) && (0 <= enemy[i]->get_stopcount())) {
					enemy[i]->freeze_stopcount();
					array->vbomb_effect.push_back({ *enemy[i]->get_px(), *enemy[i]->get_py() });
				}
			}
			//  敵を移動し、ene_map[][]に加える。
			for (int i = 0; i < enemy_num; i++) {
				if (enemy[i]->get_stopcount() == 0) {//stop_countが 1 以上 または -1 のときは、敵は何もしない。
					if (enemy[i]->get_cyclecount() == 0) {
						enemy[i]->decide_perform(array);
					}
					enemy[i]->cyclecount_up();
				}
				/*stop_countが 0 と 1 の場合に限りene_map[][]に反映。
			     （敵がホイホイにかかっている間、触れても無事となる。）*/
				if ((enemy[i]->get_stopcount() == 0) || (enemy[i]->get_stopcount() == 1) ) {
					array->enemap_up(enemy[i]->get_px(), enemy[i]->get_py(), 1);
				}
				//敵のstop_countのリセット。
				enemy[i]->stopcount_down();
			}

			//画面に表示する（優先順位の順）。
			//  vbomb_area4[][]の要素（・）
			if (!array->vbomb_area_4.empty()) {
				for (unsigned int n = 0; n < array->vbomb_area_4.size(); n++) {
					int* p_0 = &array->vbomb_area_4[n][0];
					console_draw(p_0, p_0 + 1, "・");
				}
			}
			//  vbackgd[][]の要素
			for (unsigned int n = 0; n < array->vbackgd.size(); n++) {
				int* p_0 = &array->vbackgd[n][0];
				console_draw(p_0, p_0 + 1, bsymbol[*(p_0 + 2)]);
			}
			//  vbomb_area3[][]の要素（♯）
			if (!array->vbomb_area_3.empty()) {
				for (unsigned int n = 0; n < array->vbomb_area_3.size(); n++) {
					int* p_0 = &array->vbomb_area_3[n][0];
					console_draw(p_0, p_0 + 1, "♯");
				}
			}
			//  vbomb_area2[][]の要素（・）
			if (!array->vbomb_area_2.empty()) {
				for (unsigned int n = 0; n < array->vbomb_area_2.size(); n++) {
					int* p_0 = &array->vbomb_area_2[n][0];
					console_draw(p_0, p_0 + 1, "・");
				}
			}
			//  プレーヤー
			for (int i = 0; i < 2; i++) {
				console_draw(px[i], py[i], psymbol[i]);
			}
			//  敵
			for (int i = 0; i < enemy_num; i++){
				if (0 <= enemy[i]->get_stopcount()) {
					console_draw(enemy[i]->get_px(), enemy[i]->get_py(), esymbol[enemy[i]->get_shapetype()][*enemy[i]->get_shapenum()]);
				}
			}
			//  vbomb_effect[][]の要素
			if (!array->vbomb_effect.empty()) {
				for (unsigned int n = 0; n < array->vbomb_effect.size(); n++) {
					int* p_0 = &array->vbomb_effect[n][0];
					console_draw(p_0, p_0 + 1, "＋");
				}
			}

			cursor_reset();
			e_time = clock();

			c_period = e_time - s_time;//１ゲームループの時間がT_UNITに等しくなるように。
			if (c_period < T_UNIT) {
				Sleep(T_UNIT - c_period);
			}

		}//↑ここまでゲームのループ

		//インスタンスの解放
		delete array;
		delete player[0];
		delete player[1];
		for (int i = 0; i < enemy_num; i++) {
			delete enemy[i];
		}

		round_num++;

	}//↑ここまでROUNDのループ

	if (round_num == ROUND + 1) {//全ROUNDクリア
		system("cls");
		Sleep(2000);
		excellent();
	}
	if (round_num == ROUND + 2) {//Escボタンの処理
		frameonly();
		console_draw_int(6, 5, "See You !");
		cursor_reset();
		Sleep(2000);
	}

	return 0;
};


//関数の定義
void console_draw(int* x, int* y, std::string c) {
	pos.X = 2 * *x;
	pos.Y = *y;
	SetConsoleCursorPosition(hCons, pos);
	std::cout << c;
}
void console_draw_int(int x, int y, std::string c) {
	pos.X = 2 * x;
	pos.Y = y;
	SetConsoleCursorPosition(hCons, pos);
	std::cout << c;
}

void cursor_reset() {
	console_draw_int(BLOCK_H - 2, BLOCK_V - 1, "■");
}

void ready() {
	std::string Lnum[5] = { "　　　", "□３□","□２□","□１□","START." };
	int time[5] = { 1000, 1000,1000,1000,1000 };
	for (int i = 0; i < 5; i++) {
		console_draw_int(7, 12, Lnum[i]);
		cursor_reset();
		Sleep(time[i]);
	}
	console_draw_int(8, 1, "◇");//ゴールを画面に表示。
	console_draw_int(7, 12, " Duo 　");
	console_draw_int(BOMB_X - 1, BLOCK_V, "B:");
	console_draw_int(HOI_X - 1, BLOCK_V, "h:");
}

void gameclear(int* px_0, int* py_0, int* px_1, int* py_1) {
	system("cls");
	frameonly();
	console_draw_int(8, 1, "◇");
	console_draw(px_0, py_0, "◎");
	console_draw(px_1, py_1, "○");
	console_draw_int(8, 1, "◆");
	cursor_reset();
	Sleep(2000);
	console_draw_int(1, 6, "　　　□ ROUND  CLEAR □　　　");
	cursor_reset();
	Sleep(2000);
}
void gameover(int* px_0, int* py_0, int* px_1, int* py_1) {
	Sleep(1000);
	system("cls");
	Sleep(1000);
	frameonly();
	console_draw_int(8, 1, "◇");
	console_draw_int(1, 12, "　　　　×GAME  OVER×　　　　");
	console_draw(px_0, py_0, "◎");
	console_draw(px_1, py_1, "○");
	cursor_reset();
	Sleep(3000);
}
void excellent() {
	frameonly();
	console_draw_int(4, 5, "Ｅｘｃｅｌｌｅｎｔ");
	cursor_reset();
	Sleep(1000);
	std::string symbol_array[30] = { "※","○","◇","◎","＊","●","Ο","∩","ｏ","♯","Ｏ","∪","Θ","◯","｜","◯","｜","◯","｜","◯","｜","◯","｜","◯","｜","◯","｜","◯","｜","◯", };
	int xy_array[30][2] = { {14,5},{10,3},{8,3},{6,3},{2,5},{4,7},{5,7},{6,7},{7,7},{8,7},{9,7},{10,7},{11,7},{12,7},{4,7},{4,7},{5,7},{5,7},{6,7},{6,7},{7,7},{7,7},{8,7},{8,7},{9,7},{9,7},{10,7},{10,7},{11,7},{11,7} };
	for (int i = 0; i < 30; i++) {
		console_draw_int(xy_array[i][0], xy_array[i][1], symbol_array[i]);
		cursor_reset();
		Sleep(300);
	}
	Sleep(2000);
}