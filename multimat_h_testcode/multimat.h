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
	bool within_the_standard;//�s��̐ς��`�ł��邩�ǂ����̔���
	int rows;//�ς̍s��
	int columns;//�ς̗�
	std::vector<std::remove_all_extents_t<T_1>> newmat;//T_1�̗v�f�^�ł���vector

public:
	multimat(T_1 mat_1, T_2 mat_2) {

		int rows_1 = std::extent<T_1, 0>::value;//mat_1�̍s��
		int common_num = std::extent<T_1, 1>::value;//mat_1�̗�
		int rows_2 = std::extent<T_2, 0>::value;//mat_2�̍s��
		int columns_2 = std::extent<T_2, 1>::value;//mat_2�̗�

		//mat_1 * mat_2 ���`�ł��邩�ǂ����Awithin_the_standard �Ɋi�[�B
		if (common_num == rows_2) {
			within_the_standard = true;
			rows = rows_1;
			columns = columns_2;
		}
		else {
			within_the_standard = false;//�ς��`�ł��Ȃ���΁A1�s�P��̍s���ݒ肷��B
			rows = 1;
			columns = 1;
		}

		if (within_the_standard) {
			//�ς̗v�f���P���� newmat �ɒǉ��B
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
			newmat.push_back(0);//�ς��`�ł��Ȃ���΁A1�s�P��̍s��{ 0 }��ݒ肷��B
		}

	}

	//�ς�(i, j)������Ԃ��B
	std::remove_all_extents_t<T_1> get_entry(int m, int n) {
		return newmat[(m - 1) * columns + (n - 1)];
	}

	//�ς��R���\�[���ɕ\���i�s�A�񋤂ɍő� 10 �܂Łj�B
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
	//�ς̗v�f�̌^���R���\�[���ɕ\���B
	void display_typename() {
		std::cout << typeid(newmat[0]).name();
	}

};

#endif // _MULTIMAT_H_