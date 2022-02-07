#include <iostream>
#include <vector>
#include <conio.h>
#include "array.h"
#include "test_func.h"


int main()
{
	info();

	Carray* array;
	int x, y;//画面上の位置


	//check_gameclear() テスト
	array = new Carray(1, 1);//(enemy_num, round)

	title("check_gameclear()");

	int a, b, c, d;
	//  その１
	a = 7, b = 1, c = 9, d = 1;
	value_disp("(x_0, y_0) = (7, 1), (x_1, y_1) = (9, 1)", "true");
	res(compare(1, array->check_gameclear(&a, &b, &c, &d)));//結果表示
	//  その２
	a = 9, b = 1, c = 7, d = 1;
	value_disp("(x_0, y_0) = (9, 1), (x_1, y_1) = (7, 1)", "true");
	res(compare(1, array->check_gameclear(&a, &b, &c, &d)));
	
	std::cout << "上記２パターン以外は false を返す。\n";
	//  その３
	a = 5, b = 4, c = 7, d = 1;
	value_disp("(x_0, y_0) = (5, 4), (x_1, y_1) = (7, 1)", "false");
	res(compare(0, array->check_gameclear(&a, &b, &c, &d)));

	delete array;


	//check_gameover() テスト
	array = new Carray(1, 1);

	title("check_gameover()");
	x = 1, y = 1;
	array->enemap_up(&x, &y, 1);//敵が(x, y)=(1, 1)にだけいる状態。

	//  その１
	int p_1[2][2] = { {1,1},{15,10} };
	value_disp("敵(1, 1), プレーヤー0(1, 1), プレーヤー1(15, 10)", "true");
	res(compare(1, array->check_gameover(&p_1[0][0], &p_1[0][1], &p_1[1][0], &p_1[1][1])));//結果表示
	//  その２
	int p_2[2][2] = { {15,10},{1,1} };
	value_disp("敵(1, 1), プレーヤー0(15, 10), プレーヤー1(1, 1)", "true");
	res(compare(1, array->check_gameover(&p_2[0][0], &p_2[0][1], &p_2[1][0], &p_2[1][1])));
	//  その３
	int p_3[2][2] = { {5,3},{11,5} };
	value_disp("敵(1, 1), プレーヤー0(5, 3), プレーヤー1(11, 5)", "false");
	res(compare(0, array->check_gameover(&p_3[0][0], &p_3[0][1], &p_3[1][0], &p_3[1][1])));

	delete array;


	//vbomb_area1_set() テスト
	array = new Carray(1, 1);
	vector<vector<int>> vtest;

	title("vbomb_area1_set()");

	//  その１
	value_disp("(x, y) = (7, 7)", "vbomb_area_1要素 (7, 8), (7, 6), (7, 5), (7, 7)");

	int atest_1[4] = { 8,6,5,7 };
	for (int i = 0; i < 4; i++) {
		vtest.push_back({ 7,atest_1[i] });
	}

	x = 7, y = 7;
	array->vbomb_area1_set(&x, &y);

	bool btest_1 = (array->vbomb_area_1 == vtest);
	res(btest_1);//結果表示

	array->vbomb_area_1.clear();
	vtest.clear();

	//  その２
	value_disp("(x, y) = (13, 4)", "vbomb_area_1要素 (14, 4), (15, 4), (12, 4), (11, 4), (13, 3), (13, 2), (13, 4)");
	
	int atest_2[7][2] = { {14,4},{15,4},{12,4},{11,4},{13,3},{13,2},{13,4} };
	for (int i = 0; i < 7; i++) {
		vtest.push_back({ atest_2[i][0],atest_2[i][1] });
	}

	x = 13, y = 4;
	array->vbomb_area1_set(&x, &y);

	bool btest_2 = (array->vbomb_area_1 == vtest);
	res(btest_2);

	vtest.clear();
	delete array;


	int key = _getch();
	return 0;
}