#include "multimat.h"
#include "test_func.h"
#include <iostream>
#include <conio.h>


int main()
{
	info();
	
	std::cout << "ÅÀÇQçsóÒÇÃêœ AÅ~B Ç…Ç¬Ç¢Çƒ\n\n";


	//get_within_std() ÉeÉXÉg
	title("get_within_std()");

	//  ÇªÇÃÇP
	value_disp("A[3][4], B[4][2]", "true");
	
	int a_1[3][4] = { 0 }, b_1[4][2] = { 0 };

	multimat<decltype(a_1), decltype(b_1)>* mat_1;
	mat_1 = new multimat<decltype(a_1), decltype(b_1)>(a_1, b_1);

	res(mat_1->get_within_std());//åãâ ï\é¶

	delete mat_1;

	//  ÇªÇÃÇQ
	value_disp("A[3][4], B[3][1]", "false");

	int a_2[3][4] = { 0 }, b_2[3][1] = { 0 };

	multimat<decltype(a_2), decltype(b_2)>* mat_2;
	mat_2 = new multimat<decltype(a_2), decltype(b_2)>(a_2, b_2);

	res(compare(0,mat_2->get_within_std()) );

	delete mat_2;


	//get_entry() ÉeÉXÉg	
	title("get_entry()");

	//  ÇªÇÃÇP
	value_disp("\nA[3][4] = intå^ {{1,2,3,4},{5,6,3,2},{4,3,2,1}}, \nB[4][2] = intå^ {{1,2},{2,1},{-2.-1},{-1,-2}}\n",
		"intå^ {{-5,-7},{9,9},{5,7}}");

	int a_3[3][4] = { {1,2,3,4},{5,6,3,2},{4,3,2,1} }, b_3[4][2] = { {1,2},{2,1},{-2,- 1},{-1,-2} };
	int c_3[3][2] = { {-5,-7},{9,9},{5,7} };

	multimat<decltype(a_3), decltype(b_3)>* mat_3;
	mat_3 = new multimat<decltype(a_3), decltype(b_3)>(a_3, b_3);

	bool bool_3 = (typeid(a_3[0][0]) == typeid(mat_3->get_entry(1,1)) );//a_3ÇÃóvëfÇ∆ÅAêœÇÃóvëfÇÃå^Ç™àÍívÇµÇƒÇ¢ÇÈÇ©ÅB
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 2; j++) {
			bool_3 = bool_3 && (c_3[i][j] == mat_3->get_entry(i + 1, j + 1));
		}
	}
	res(bool_3);//åãâ ï\é¶

	delete mat_3;

	//  ÇªÇÃÇQ
	value_disp("\nA[5][2] = floatå^ {{10,12},{5,7},{24,28},{15,18},{-2,-8}}, \nB[2][4] = floatå^ {{1.5,5,10.5,18},{-20,5,-10.5,8.5}}\n",
		"floatå^ {{-225,110,-21,282},{-132.5,60,-21,149.5},{-524,260,-42,670},{-337.5,165,-31.5,423},{157,-50,63,-104}}");
	
	float a_4[5][2] = { {10,12},{5,7},{24,28},{15,18},{-2,-8} }, b_4[2][4] = { {1.5,5,10.5,18},{-20,5,-10.5,8.5} };
	float c_4[5][4] = { {-225,110,-21,282},{-132.5,60,-21,149.5},{-524,260,-42,670},{-337.5,165,-31.5,423},{157,-50,63,-104} };

	multimat<decltype(a_4), decltype(b_4)>* mat_4;
	mat_4 = new multimat<decltype(a_4), decltype(b_4)>(a_4, b_4);

	bool bool_4 = (typeid(a_4[0][0]) == typeid(mat_4->get_entry(1, 1)) );
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			bool_4 = bool_4 && (c_4[i][j] == mat_4->get_entry(i + 1, j + 1));
		}
	}
	res(bool_4);

	delete mat_4;

	//  ÇªÇÃÇR
	value_disp("\nA[5][2] = doubleå^ {{2.5,5},{6.5,3.5},{12,15},{11.5,16.5},{-2.5,-8}}, \nB[2][4] = doubleå^ {{-1.5,5,9.5,15.5},{-6.5,10.5,-8.5,10.5}}\n",
		"doubleå^ {{-36.25,65,-18.75,91.25},{-32.5,69.25,32,137.5},{-115.5,217.5,-13.5,343.5},{-124.5,230.75,-31,351.5},{55.75,-96.5,44.25,-122.75}}");
	
	double a_5[5][2] = { {2.5,5},{6.5,3.5},{12,15},{11.5,16.5},{-2.5,-8} }, b_5[2][4] = { {-1.5,5,9.5,15.5},{-6.5,10.5,-8.5,10.5} };
	double c_5[5][4] = { {-36.25,65,-18.75,91.25},{-32.5,69.25,32,137.5},{-115.5,217.5,-13.5,343.5},{-124.5,230.75,-31,351.5},{55.75,-96.5,44.25,-122.75} };
	
	multimat<decltype(a_5), decltype(b_5)>* mat_5;
	mat_5 = new multimat<decltype(a_5), decltype(b_5)>(a_5, b_5);
	
	bool bool_5 = (typeid(a_5[0][0]) == typeid(mat_5->get_entry(1, 1)) );
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 4; j++) {
			bool_5 = bool_5 && (c_5[i][j] == mat_5->get_entry(i + 1, j + 1));
		}
	}
	res(bool_5);

	delete mat_5;

	//  ÇªÇÃÇS
	value_disp("\nA[2][1] = doubleå^ {{1},{2}}, \nB[1][2] = floatå^ {{1,-1}}\n", "doubleå^ {{1,-1},{2,-2}}");

	double a_6[2][1] = { {1},{2} };
	float b_6[1][2] = { {1,-1} };
	double c_6[2][2] = { {1,-1},{2,-2} };

	multimat<decltype(a_6), decltype(b_6)>* mat_6;
	mat_6 = new multimat<decltype(a_6), decltype(b_6)>(a_6, b_6);

	bool bool_6 = (typeid(a_6[0][0]) == typeid(mat_6->get_entry(1, 1)) );
	for (int i = 0; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			bool_6 = bool_6 && (c_6[i][j] == mat_6->get_entry(i + 1, j + 1));
		}
	}
	res(bool_6);

	delete mat_6;


	//get_rows() ÉeÉXÉg
	title("get_rows()");

	//  ÇªÇÃÇP
	value_disp("A[3][4], B[4][2]", "3");

	int a_7[3][4] = { 0 }, b_7[4][2] = { 0 };

	multimat<decltype(a_7), decltype(b_7)>* mat_7;
	mat_7 = new multimat<decltype(a_7), decltype(b_7)>(a_7, b_7);

	res(compare(3,mat_7->get_rows()) );//åãâ ï\é¶

	delete mat_7;

	//  ÇªÇÃÇQ
	value_disp("A[3][4], B[3][1]", "1");

	int a_8[3][4] = { 0 }, b_8[3][1] = { 0 };

	multimat<decltype(a_8), decltype(b_8)>* mat_8;
	mat_8 = new multimat<decltype(a_8), decltype(b_8)>(a_8, b_8);

	res(compare(1, mat_8->get_rows()) );

	delete mat_8;


	//get_columns() ÉeÉXÉg
	title("get_columns()");

	//  ÇªÇÃÇP
	value_disp("A[3][4], B[4][2]", "2");

	int a_9[3][4] = { 0 }, b_9[4][2] = { 0 };

	multimat<decltype(a_9), decltype(b_9)>* mat_9;
	mat_9 = new multimat<decltype(a_9), decltype(b_9)>(a_9, b_9);

	res(compare(2, mat_9->get_columns()) );//åãâ ï\é¶

	delete mat_9;

	//  ÇªÇÃÇQ
	value_disp("A[3][4], B[3][1]", "1");

	int a_10[3][4] = { 0 }, b_10[3][1] = { 0 };

	multimat<decltype(a_10), decltype(b_10)>* mat_10;
	mat_10 = new multimat<decltype(a_10), decltype(b_10)>(a_10, b_10);

	res(compare(1, mat_10->get_columns()) );

	delete mat_10;



	int key = _getch();
	return 0;
}