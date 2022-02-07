#include <iostream>
#include <conio.h>
#include "enemy.h"
#include "array.h"
#include "test_func.h"

int dx, dy;
bool premoved;
bool perform_test_1(bool premoved, bool rev, bool moved) {//decide_perform()テスト用
	if (!moved) {
		if (premoved && rev) {
			return true;
		}
		else {
			return false;
		}
	}
	else {
		if (premoved && rev) {
			return false;
		}
		else {
			return true;
		}
	}
}


int main()
{
	info();
	
	//select() テスト
	title("select(a, b, c, d)");
	int dir;

	//  その１
	value_disp("(a, b, c, d) = (1, 2, 1, 2)", "0, 1, 2, 3 のいずれかを必ず返す。");
	dir = select(1, 2, 1, 2);
	res(compare(1, compare(0, dir) + compare(1, dir) + compare(2, dir) + compare(3, dir)));//結果表示
	//  その２
	value_disp("(a, b, c, d) = (3, 0, 3, 8)", "0, 1, 2, 3 のいずれかを必ず返す。");
	dir = select(3, 0, 3, 8);
	res(compare(1, compare(0, dir) + compare(1, dir) + compare(2, dir) + compare(3, dir)));
	//  その３
	value_disp("(a, b, c, d) = (2, 5, 0, 1)", "0, 1, 2, 3 のいずれかを必ず返す。");
	dir = select(2, 5, 0, 1);
	res(compare(1, compare(0, dir) + compare(1, dir) + compare(2, dir) + compare(3, dir)));

	
	Carray* array;
	Cenemy* enemy;

	//turn_x(), turn_y() テスト
	array = new Carray(1, 1);
	enemy = new Cenemy(0, 1);

	int* pdx = enemy->get_pdx(), * pdy = enemy->get_pdy();

	title("turn_x(), turn_y()");

	//  その１
	value_disp("(direct_x, direct_y) = (0, 1), LEFT", "(direct_x, direct_y) = (1, 0)");
	res(compare(1, enemy->turn_x(pdx, pdy, 0)) * compare(0, enemy->turn_y(pdx, pdy, 0)) );//結果表示
	//  その２
	value_disp("(direct_x, direct_y) = (0, 1), BACK", "(direct_x, direct_y) = (0, -1)");
	res(compare(0, enemy->turn_x(pdx, pdy, 1)) * compare(-1, enemy->turn_y(pdx, pdy, 1)));
	//  その３
	value_disp("(direct_x, direct_y) = (0, 1), RIGHT", "(direct_x, direct_y) = (-1, 0)");
	res(compare(-1, enemy->turn_x(pdx, pdy, 2)) * compare(0, enemy->turn_y(pdx, pdy, 2)));
	// その４
	value_disp("(direct_x, direct_y) = (0, 1), FRONT", "(direct_x, direct_y) = (0, 1)");
	res(compare(0, enemy->turn_x(pdx, pdy, 3)) * compare(1, enemy->turn_y(pdx, pdy, 3)));

	delete array;
	delete enemy;


	//can_turn() テスト
	array = new Carray(1, 1);
	enemy = new Cenemy(0, 1);

	title("can_turn()");
	
	//  その１
	value_disp("ROUND1 (posi_x, posi_y) = (5, 1), (direct_x, direct_y) = (0, 1), LEFT", "true");
	res(compare(1, enemy->can_turn(array, 0)) );//結果表示
	//  その２
	value_disp("ROUND1 (posi_x, posi_y) = (5, 1), (direct_x, direct_y) = (0, 1), BACK", "false");
	res(compare(0, enemy->can_turn(array, 1)));
	//  その３
	value_disp("ROUND1 (posi_x, posi_y) = (5, 1), (direct_x, direct_y) = (0, 1), RIGHT", "true");
	res(compare(1, enemy->can_turn(array, 2)));
	//  その４
	value_disp("ROUND1 (posi_x, posi_y) = (5, 1), (direct_x, direct_y) = (0, 1), FRONT", "true");
	res(compare(1, enemy->can_turn(array, 3)));

	delete array;
	delete enemy;


	//stopcount_down() テスト
	enemy = new Cenemy(0, 1);

	title("stopcount_down()");
	
	//  その１
	value_disp("stop_count = 1", "stop_count = 0");

	enemy->stopcount_down();
	res(compare(0, enemy->get_stopcount()));//結果表示
	//  その２
	value_disp("stop_count = 0", "stop_count = 0");

	enemy->stopcount_down();
	res(compare(0, enemy->get_stopcount()));

	delete enemy;


	//stopcount_add() テスト
	enemy = new Cenemy(0, 1);

	title("stopcount_add()");
	
	//  その１
	value_disp("stop_count = 1", "stop_count = 1");

	enemy->stopcount_add();
	res(compare(1, enemy->get_stopcount()));//結果表示
	//  その２
	enemy->stopcount_down();//stop_countを0にする。
	value_disp("stop_count = 0", "stop_count = 18");

	enemy->stopcount_add();
	res(compare(18, enemy->get_stopcount()));

	delete enemy;


	//decide_perform() テスト

	title("dicide_perform()");
	array = new Carray(1, 1);
	enemy = new Cenemy(0, 1);

	//  １つ目のテスト
	std::cout << "⇒「出力時moved = false」は「入力時moved = true、出力時reversed = true」のときに限る。\n";
	
	//    その１
	premoved = enemy->get_moved();
	enemy->decide_perform(array);
	std::cout << "decide_moved()実行: (出力時moved | 出力時reversed, 入力時moved) = (" << enemy->get_moved() <<", " << enemy->get_reversed() << ", " << premoved << ")\n";
	res(perform_test_1(premoved, enemy->get_reversed(), enemy->get_moved()));//結果表示
	//    その２
	premoved = enemy->get_moved();
	enemy->decide_perform(array);
	std::cout << "decide_moved()実行: (出力時moved | 出力時reversed, 入力時moved) = (" << enemy->get_moved() << ", " << enemy->get_reversed() << ", " << premoved << ")\n";
	res(perform_test_1(premoved, enemy->get_reversed(), enemy->get_moved()));
	//    その３
	premoved = enemy->get_moved();
	enemy->decide_perform(array);
	std::cout << "decide_moved()実行: (出力時moved | 出力時reversed, 入力時moved) = (" << enemy->get_moved() << ", " << enemy->get_reversed() << ", " << premoved << ")\n";
	res(perform_test_1(premoved, enemy->get_reversed(), enemy->get_moved()));
	//    その４
	while (enemy->get_moved() == true) {//moved が false になるまで調整。
		premoved = enemy->get_moved();
		enemy->decide_perform(array);
	}
	std::cout << "decide_moved()実行: (出力時moved | 出力時reversed, 入力時moved) = (" << enemy->get_moved() << ", " << enemy->get_reversed() << ", " << premoved << ")\n";
	res(perform_test_1(premoved, enemy->get_reversed(), enemy->get_moved()));

	delete array;
	delete enemy;

	array = new Carray(1, 1);
	enemy = new Cenemy(0, 1);

	//  ２つ目のテスト
	std::cout << "\n" << "⇒入力時(moved, reversed) = (false, true), (direct_x, direct_y) を (dx, dy) とするとき、出力は (dx, dy) 方向への移動となる。\n";
	
	//    その１
	value_disp("moved = false, reversed = true, (direct_x, direct_y) を (dx, dy) とする", "moved = true, direct_x = dx, direct_y = dy");

	while ((enemy->get_moved() == true) || (enemy->get_reversed() == false)) {//(moved, reversed)が(false, true)になるまで調整。
		enemy->decide_perform(array);
	}
	dx = *enemy->get_pdx(), dy = *enemy->get_pdy();

	enemy->decide_perform(array);
	bool test_1 = (enemy->get_moved() == true) && (*enemy->get_pdx() == dx) && (*enemy->get_pdy() == dy);
	res(test_1);//結果表示

	//    その２
	value_disp("moved = false, reversed = true, (direct_x, direct_y) を (dx, dy) とする", "moved = true, direct_x = dx, direct_y = dy");

	while ((enemy->get_moved() == true) || (enemy->get_reversed() == false)) {//(moved, reversed)が(false, true)になるまで調整。
		enemy->decide_perform(array);
	}
	dx = *enemy->get_pdx(), dy = *enemy->get_pdy();

	enemy->decide_perform(array);
	bool test_2 = (enemy->get_moved() == true) && (*enemy->get_pdx() == dx) && (*enemy->get_pdy() == dy);
	res(test_2);

	delete array;
	delete enemy;




	int key=_getch();
	return 0;
}