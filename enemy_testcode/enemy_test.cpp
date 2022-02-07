#include <iostream>
#include <conio.h>
#include "enemy.h"
#include "array.h"
#include "test_func.h"

int dx, dy;
bool premoved;
bool perform_test_1(bool premoved, bool rev, bool moved) {//decide_perform()�e�X�g�p
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
	
	//select() �e�X�g
	title("select(a, b, c, d)");
	int dir;

	//  ���̂P
	value_disp("(a, b, c, d) = (1, 2, 1, 2)", "0, 1, 2, 3 �̂����ꂩ��K���Ԃ��B");
	dir = select(1, 2, 1, 2);
	res(compare(1, compare(0, dir) + compare(1, dir) + compare(2, dir) + compare(3, dir)));//���ʕ\��
	//  ���̂Q
	value_disp("(a, b, c, d) = (3, 0, 3, 8)", "0, 1, 2, 3 �̂����ꂩ��K���Ԃ��B");
	dir = select(3, 0, 3, 8);
	res(compare(1, compare(0, dir) + compare(1, dir) + compare(2, dir) + compare(3, dir)));
	//  ���̂R
	value_disp("(a, b, c, d) = (2, 5, 0, 1)", "0, 1, 2, 3 �̂����ꂩ��K���Ԃ��B");
	dir = select(2, 5, 0, 1);
	res(compare(1, compare(0, dir) + compare(1, dir) + compare(2, dir) + compare(3, dir)));

	
	Carray* array;
	Cenemy* enemy;

	//turn_x(), turn_y() �e�X�g
	array = new Carray(1, 1);
	enemy = new Cenemy(0, 1);

	int* pdx = enemy->get_pdx(), * pdy = enemy->get_pdy();

	title("turn_x(), turn_y()");

	//  ���̂P
	value_disp("(direct_x, direct_y) = (0, 1), LEFT", "(direct_x, direct_y) = (1, 0)");
	res(compare(1, enemy->turn_x(pdx, pdy, 0)) * compare(0, enemy->turn_y(pdx, pdy, 0)) );//���ʕ\��
	//  ���̂Q
	value_disp("(direct_x, direct_y) = (0, 1), BACK", "(direct_x, direct_y) = (0, -1)");
	res(compare(0, enemy->turn_x(pdx, pdy, 1)) * compare(-1, enemy->turn_y(pdx, pdy, 1)));
	//  ���̂R
	value_disp("(direct_x, direct_y) = (0, 1), RIGHT", "(direct_x, direct_y) = (-1, 0)");
	res(compare(-1, enemy->turn_x(pdx, pdy, 2)) * compare(0, enemy->turn_y(pdx, pdy, 2)));
	// ���̂S
	value_disp("(direct_x, direct_y) = (0, 1), FRONT", "(direct_x, direct_y) = (0, 1)");
	res(compare(0, enemy->turn_x(pdx, pdy, 3)) * compare(1, enemy->turn_y(pdx, pdy, 3)));

	delete array;
	delete enemy;


	//can_turn() �e�X�g
	array = new Carray(1, 1);
	enemy = new Cenemy(0, 1);

	title("can_turn()");
	
	//  ���̂P
	value_disp("ROUND1 (posi_x, posi_y) = (5, 1), (direct_x, direct_y) = (0, 1), LEFT", "true");
	res(compare(1, enemy->can_turn(array, 0)) );//���ʕ\��
	//  ���̂Q
	value_disp("ROUND1 (posi_x, posi_y) = (5, 1), (direct_x, direct_y) = (0, 1), BACK", "false");
	res(compare(0, enemy->can_turn(array, 1)));
	//  ���̂R
	value_disp("ROUND1 (posi_x, posi_y) = (5, 1), (direct_x, direct_y) = (0, 1), RIGHT", "true");
	res(compare(1, enemy->can_turn(array, 2)));
	//  ���̂S
	value_disp("ROUND1 (posi_x, posi_y) = (5, 1), (direct_x, direct_y) = (0, 1), FRONT", "true");
	res(compare(1, enemy->can_turn(array, 3)));

	delete array;
	delete enemy;


	//stopcount_down() �e�X�g
	enemy = new Cenemy(0, 1);

	title("stopcount_down()");
	
	//  ���̂P
	value_disp("stop_count = 1", "stop_count = 0");

	enemy->stopcount_down();
	res(compare(0, enemy->get_stopcount()));//���ʕ\��
	//  ���̂Q
	value_disp("stop_count = 0", "stop_count = 0");

	enemy->stopcount_down();
	res(compare(0, enemy->get_stopcount()));

	delete enemy;


	//stopcount_add() �e�X�g
	enemy = new Cenemy(0, 1);

	title("stopcount_add()");
	
	//  ���̂P
	value_disp("stop_count = 1", "stop_count = 1");

	enemy->stopcount_add();
	res(compare(1, enemy->get_stopcount()));//���ʕ\��
	//  ���̂Q
	enemy->stopcount_down();//stop_count��0�ɂ���B
	value_disp("stop_count = 0", "stop_count = 18");

	enemy->stopcount_add();
	res(compare(18, enemy->get_stopcount()));

	delete enemy;


	//decide_perform() �e�X�g

	title("dicide_perform()");
	array = new Carray(1, 1);
	enemy = new Cenemy(0, 1);

	//  �P�ڂ̃e�X�g
	std::cout << "�ˁu�o�͎�moved = false�v�́u���͎�moved = true�A�o�͎�reversed = true�v�̂Ƃ��Ɍ���B\n";
	
	//    ���̂P
	premoved = enemy->get_moved();
	enemy->decide_perform(array);
	std::cout << "decide_moved()���s: (�o�͎�moved | �o�͎�reversed, ���͎�moved) = (" << enemy->get_moved() <<", " << enemy->get_reversed() << ", " << premoved << ")\n";
	res(perform_test_1(premoved, enemy->get_reversed(), enemy->get_moved()));//���ʕ\��
	//    ���̂Q
	premoved = enemy->get_moved();
	enemy->decide_perform(array);
	std::cout << "decide_moved()���s: (�o�͎�moved | �o�͎�reversed, ���͎�moved) = (" << enemy->get_moved() << ", " << enemy->get_reversed() << ", " << premoved << ")\n";
	res(perform_test_1(premoved, enemy->get_reversed(), enemy->get_moved()));
	//    ���̂R
	premoved = enemy->get_moved();
	enemy->decide_perform(array);
	std::cout << "decide_moved()���s: (�o�͎�moved | �o�͎�reversed, ���͎�moved) = (" << enemy->get_moved() << ", " << enemy->get_reversed() << ", " << premoved << ")\n";
	res(perform_test_1(premoved, enemy->get_reversed(), enemy->get_moved()));
	//    ���̂S
	while (enemy->get_moved() == true) {//moved �� false �ɂȂ�܂Œ����B
		premoved = enemy->get_moved();
		enemy->decide_perform(array);
	}
	std::cout << "decide_moved()���s: (�o�͎�moved | �o�͎�reversed, ���͎�moved) = (" << enemy->get_moved() << ", " << enemy->get_reversed() << ", " << premoved << ")\n";
	res(perform_test_1(premoved, enemy->get_reversed(), enemy->get_moved()));

	delete array;
	delete enemy;

	array = new Carray(1, 1);
	enemy = new Cenemy(0, 1);

	//  �Q�ڂ̃e�X�g
	std::cout << "\n" << "�˓��͎�(moved, reversed) = (false, true), (direct_x, direct_y) �� (dx, dy) �Ƃ���Ƃ��A�o�͂� (dx, dy) �����ւ̈ړ��ƂȂ�B\n";
	
	//    ���̂P
	value_disp("moved = false, reversed = true, (direct_x, direct_y) �� (dx, dy) �Ƃ���", "moved = true, direct_x = dx, direct_y = dy");

	while ((enemy->get_moved() == true) || (enemy->get_reversed() == false)) {//(moved, reversed)��(false, true)�ɂȂ�܂Œ����B
		enemy->decide_perform(array);
	}
	dx = *enemy->get_pdx(), dy = *enemy->get_pdy();

	enemy->decide_perform(array);
	bool test_1 = (enemy->get_moved() == true) && (*enemy->get_pdx() == dx) && (*enemy->get_pdy() == dy);
	res(test_1);//���ʕ\��

	//    ���̂Q
	value_disp("moved = false, reversed = true, (direct_x, direct_y) �� (dx, dy) �Ƃ���", "moved = true, direct_x = dx, direct_y = dy");

	while ((enemy->get_moved() == true) || (enemy->get_reversed() == false)) {//(moved, reversed)��(false, true)�ɂȂ�܂Œ����B
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