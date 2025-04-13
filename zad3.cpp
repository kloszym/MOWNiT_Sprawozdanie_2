#include "for_running/zad3.h"

#include <array>
#include <fstream>
#include <iostream>
#include <random>
#include <set>

#include "gnuplot-iostream.h"

using namespace std;

void print_sudoku(array<array<int, 9>, 9> tab) {
	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 9; j++) {
			cout << tab[i][j] << " ";
		}
		cout << "\n";
	}
	cout << "\n";
}

int calcEnergy(array<array<int, 9>, 9> tab) {
	int energy = 0;
	for (size_t i = 0; i < 9; i++) {
		int row[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
		int col[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
		int square[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
		for (size_t j = 0; j < 9; j++) {
			row[tab[i][j] - 1]++;
			col[tab[j][i] - 1]++;
			square[tab[((i / 3) * 3) + (j / 3)][(j % 3) + (i % 3) * 3] - 1]++;
		}

		for (size_t j = 0; j < 9; j++) {
			energy += row[j] > 1 ? row[j] : 0;
			energy += col[j] > 1 ? col[j] : 0;
			energy += square[j] > 1 ? square[j] : 0;
		}
	}
	return energy;
}

random_device rnd;
mt19937 generator(rnd()); // seed the generator
uniform_int_distribution<> btwn(0, 8);
array<array<int, 9>, 9> change_random(array<array<int, 9>, 9> tab, set<pair<int, int>> not_changing) {

	array<array<int, 9>, 9> res = tab;

	int x1 = btwn(generator);
	int y1 = btwn(generator);
	int x2 = btwn(generator);
	int y2 = btwn(generator);


	while (x1 == x2 && y1 == y2) {
		x2 = btwn(generator);
		y2 = btwn(generator);
	}

	auto search1 = not_changing.find(make_pair(x1, y1));
	auto search2 = not_changing.find(make_pair(x2, y2));

	if ((res[x1][y1] != res[x2][y2]) && search1 == not_changing.end() && search2 == not_changing.end()) {
		int temp = res[x1][y1];
		res[x1][y1] = res[x2][y2];
		res[x2][y2] = temp;
	}

	return res;
}

array<array<int, 9>, 9> annealing(array<array<int, 9>, 9> sudoku, set<pair<int, int>> not_changing, double initialT,
								  double multi, size_t kmax) {

	size_t iterations = 0;
	auto currentSudoku = sudoku;

	double currentEnergy = calcEnergy(currentSudoku);

	double t = initialT;

	auto globalBestSudoku = currentSudoku;
	double globalBestEnergy = currentEnergy;

	ofstream f("func_zad3.dat");

	for (size_t i = 0; i < kmax; i++) {
		// cout << "iteration: " << i << "\n";
		iterations++;

		t *= 0.999;

		auto neighbor = change_random(currentSudoku, not_changing);

		const double neighborEnergy = calcEnergy(neighbor);

		const double delta = neighborEnergy - currentEnergy;

		if (delta < 0 || exp(-delta / t) >= static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) {
			currentSudoku = neighbor;
			currentEnergy = neighborEnergy;

			f << i << " " << neighborEnergy << "\n";

			if (currentEnergy < globalBestEnergy) {
				globalBestSudoku = currentSudoku;
				globalBestEnergy = currentEnergy;
			}
		}
	}
	f.close();
	cout << "\n\n" << globalBestEnergy << "\n\n";
	return globalBestSudoku;
}

int zad3(string name, bool isHard, double initialT, double multi, size_t kmax) {

	array<array<int, 9>, 9> sudoku;
	int digits[9] = {0, 0, 0, 0, 0, 0, 0, 0, 0};
	set<pair<int, int>> not_changing;

	ifstream sudoku_file;
	if (isHard) {
		sudoku_file.open("sudoku_hard.txt");
	} else {
		sudoku_file.open("sudoku.txt");
	}


	set<int> digit_row;

	if (!sudoku_file.is_open()) {
		cerr << "File not found" << endl;
		return 1;
	} else {
		int i = 0;
		int j = 0;
		char piece;
		while ((piece = sudoku_file.get()) != EOF) {
			if (std::isdigit(piece)) {
				int num = piece - '0';
				sudoku[i][j] = num;
				not_changing.insert(make_pair(i, j));
				digits[num - 1]++;
				j++;
			}
			if (piece == 'x') {
				sudoku[i][j] = 0;
				j++;
			}
			if (j == 9) {
				i++;
				j = 0;
			}
			// if (i == 9) {
			// 	break;
			// }
		}
	}
	sudoku_file.close();

	// print_sudoku(sudoku);

	int digit = 0;
	for (size_t i = 0; i < 9; i++) {
		for (size_t j = 0; j < 9; j++) {
			if (sudoku[i][j] == 0) {
				sudoku[i][j] = digit + 1;
				digits[digit]++;
			}
			if (digits[digit] == 9)
				digit++;
		}
	}
	cout << "\n\n";
	// print_sudoku(sudoku);

	// cout << "\n\n" << calcEnergy(sudoku) << "\n\n";

	array<array<int, 9>, 9> result = annealing(sudoku, not_changing, initialT, multi, kmax);

	print_sudoku(result);
	Gnuplot gpp;
	// gpp << "set terminal qt\n";
	// gpp << "plot 'func_zad3.dat' with lines\n";
	gpp << "set terminal svg size 800, 800; set output '../img/" << name
		<< "_function.svg'; plot 'func_zad3.dat' with lines\n";

	return 0;
}
