#include <iostream>
#include <conio.h>
#include "player.h"
#include "test_func.h"


int main()
{
	info();

	Cplayer* player_0;
	Cplayer* player_1;
	int x, y;//画面上の位置	

	//get_nextx(),get_nexty() テスト
	player_0 = new Cplayer(0);

	title("get_nextx()");

	value_disp("posi_x = 9, direct_x = 0", "9");
	res(compare(9, player_0->get_nextx()));//結果表示

	title("get_nexty()");

	value_disp("posi_y = 10, direct_y = 0", "10");
	res(compare(10, player_0->get_nexty()));//結果表示

	delete player_0;


	//decide_direct() テスト
	player_0 = new Cplayer(0);
	player_1 = new Cplayer(1);
	title("decide_direct()");

	//  その１
	value_disp("キー = 上", "direct_x = 0, direct_y = -1");

	player_0->decide_direct(72);
	res(compare(0, player_0->get_nextx() - *player_0->get_px()) * compare(-1, player_0->get_nexty() - *player_0->get_py()));//結果表示
	//  その２
	value_disp("（◎に対して）キー = 左", "direct_x = -1, direct_y = 0");

	player_0->decide_direct(75);
	res(compare(-1, player_0->get_nextx() - *player_0->get_px()) * compare(0, player_0->get_nexty() - *player_0->get_py()));
	//  その３
	value_disp("（〇に対して）キー = 左", "direct_x = 1, direct_y = 0");

	player_1->decide_direct(75);
	res(compare(1, player_1->get_nextx() - *player_1->get_px()) * compare(0, player_1->get_nexty() - *player_1->get_py()));

	delete player_0;
	delete player_1;


	//player_move() テスト
	player_0 = new Cplayer(0);
	player_1 = new Cplayer(1);
	title("player_move()");

	//  その１
	value_disp("キー = 上, posi_x = 9, posi_y = 10", "posi_x = 9, posi_y = 9");

	player_0->decide_direct(72);
	player_0->player_move();
	res(compare(9, *player_0->get_px()) * compare(9, *player_0->get_py()));//結果表示
	//  その２
	value_disp("（◎に対して）キー = 左, posi_x = 9, posi_y = 9", "posi_x = 8, posi_y = 9");

	player_0->decide_direct(75);
	player_0->player_move();
	res(compare(8, *player_0->get_px()) * compare(9, *player_0->get_py()));
	//  その３
	value_disp("（〇に対して）キー = 左, posi_x = 7, posi_y = 10", "posi_x = 8, posi_y = 10");

	player_1->decide_direct(75);
	player_1->player_move();
	res(compare(8, *player_1->get_px()) * compare(10, *player_1->get_py()));

	delete player_0;
	delete player_1;


	//stopcount_add() テスト
	player_0 = new Cplayer(0);
	title("stopcount_add()");

	//  その１
	value_disp("stopcount = 0", "stopcount = 1");

	player_0->stopcount_add();
	res(compare(1, player_0->get_stopcount() ));//結果表示
	//  その２
	value_disp("stopcount = 1", "stopcount = 1");

	player_0->stopcount_add();
	res(compare(1, player_0->get_stopcount() ));

	delete player_0;


	//stopcount_down() テスト
	player_0 = new Cplayer(0);
	title("stopcount_down()");

	//  その１
	value_disp("stopcount = 1", "stopcount = 0");

	player_0->stopcount_down();
	res(compare(0, player_0->get_stopcount()));//結果表示
	//  その２
	value_disp("stopcount = 0", "stopcount = 0");

	player_0->stopcount_down();
	res(compare(0, player_0->get_stopcount()));

	delete player_0;


	//stopcount_exchange() テスト
	player_0 = new Cplayer(0);
	title("stopcount_exchange()");

	//  その１
	value_disp("stopcount = 0", "stopcount = -1");

	player_0->stopcount_exchange();
	res(compare(-1, player_0->get_stopcount()));//結果表示
	//  その２
	value_disp("stopcount = -1", "stopcount = 0");

	player_0->stopcount_exchange();
	res(compare(0, player_0->get_stopcount()));

	delete player_0;


	//match() テスト
	player_0 = new Cplayer(0);
	title("match()");

	std::cout << "プレーヤー(9, 10)に対して\n";
	//  その１
	value_disp("位置(9, 10)", "true");

	x = 9, y = 10;
	res(player_0->match(&x, &y));//結果表示
	//  その２
	value_disp("位置(5, 5)", "false");

	x = 5, y = 5;
	res(compare(0,player_0->match(&x, &y)) );

	delete player_0;



	int key = _getch();
	return 0;
}