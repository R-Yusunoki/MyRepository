#ifndef _MULTIMAT_H_
#define _MULTIMAT_H_

#include <iostream>
#include <type_traits>
#include <vector>

#define MAX_ROWS (10)
#define MAX_COLUMNS (10)


template<typename T_1, typename T_2>

class multimat {
private:
	bool within_the_standard;//行列の積を定義できるかどうかの判定
	int rows;//積の行数
	int columns;//積の列数
	std::vector<std::remove_all_extents_t<T_1>> newmat;//T_1の要素型であるvector

public:
	multimat(T_1 mat_1, T_2 mat_2) {

		int rows_1 = std::extent<T_1, 0>::value;//mat_1の行数
		int common_num = std::extent<T_1, 1>::value;//mat_1の列数
		int rows_2 = std::extent<T_2, 0>::value;//mat_2の行数
		int columns_2 = std::extent<T_2, 1>::value;//mat_2の列数

		//mat_1 * mat_2 を定義できるかどうか、within_the_standard に格納。
		if (common_num == rows_2) {
			within_the_standard = true;
			rows = rows_1;
			columns = columns_2;
		}
		else {
			within_the_standard = false;//積を定義できなければ、1行１列の行列を設定する。
			rows = 1;
			columns = 1;
		}

		if (within_the_standard) {
			//積の要素を１つずつ newmat に追加。
			for (int i = 0; i < rows_1; i++) {
				for (int j = 0; j < columns_2; j++) {

					std::remove_all_extents_t<T_1> sum = 0;

					for (int k = 0; k < common_num; k++) {
						sum += mat_1[i][k] * mat_2[k][j];
					}

					newmat.push_back(sum);
				}
			}

		}

		else {
			newmat.push_back(0);//積を定義できなければ、1行１列の行列{ 0 }を設定する。
		}

	}

	//積の(i, j)成分を返す。
	std::remove_all_extents_t<T_1> get_entry(int m, int n) {
		return newmat[(m - 1) * columns + (n - 1)];
	}

	//積をコンソールに表示（行、列共に最大 10 まで）。
	void display_mat() {
		if (within_the_standard) {
			for (int i = 0; (i < rows) && (i < MAX_ROWS); i++) {
				for (int j = 0; (j < columns) && (j < MAX_COLUMNS); j++) {
					std::cout << newmat[i * columns + j];
					if (j != columns - 1) {
						std::cout << ", ";
					}
				}
				if (MAX_COLUMNS < columns) {
					std::cout << "..";
				}
				std::cout << "\n";
			}
			if (MAX_ROWS < rows) {
				std::cout << "....." << "\n";
			}
		}
		else {
			std::cout << 0 << "\n";
		}
		std::cout << "\n";
	}

	int get_rows() {
		return rows;
	}

	int get_columns() {
		return columns;
	}

	bool get_within_std() {
		return within_the_standard;
	}
	//積の要素の型をコンソールに表示。
	void display_typename() {
		std::cout << typeid(newmat[0]).name();
	}

};

#endif // _MULTIMAT_H_