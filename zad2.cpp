#include "for_running/zad2.h"

#include <bitset>
#include <fstream>
#include <iostream>
#include <random>
#include <thread>

#include "CImg.h"
#include "gnuplot-iostream.h"

const int gridSide = 300;
const size_t bitsetSize = gridSide * gridSide;

const int squareSize = 5; // Size of each square in pixels
const int windowWidth = gridSide * squareSize;
const int windowHeight = gridSide * squareSize;

const int weight = 10;


using neigh_func = void (*)(int, int *);

using namespace cimg_library;
using namespace std;

// rewrite it to be more modular
int energy_4_neigh(int i, bitset<bitsetSize> boardData) {

	int energy = 0;
	boolean k = boardData[i];

	// up
	if ((i + gridSide) / bitsetSize > 0) {
		energy += boardData[(i + gridSide) % bitsetSize] == k ? -weight : weight;
	} else {
		energy += boardData[i + gridSide] == k ? -weight : weight;
	}

	// down
	if (i - gridSide < 0) {
		energy += boardData[bitsetSize + i - gridSide] == k ? -weight : weight;
	} else {
		energy += boardData[i - gridSide] == k ? -weight : weight;
	}

	// left
	if ((i + 1) % gridSide == 0) {
		energy += boardData[i + 1 - gridSide] == k ? -weight : weight;
	} else {
		energy += boardData[i + 1] == k ? -weight : weight;
	}

	// right
	if ((i - 1) % gridSide == 0 || i - 1 == -1) {
		energy += boardData[i - 1 + gridSide] == k ? -weight : weight;
	} else {
		energy += boardData[i - 1] == k ? -weight : weight;
	}

	return energy;
}

// for neigh_small_x
inline int mod(int a, int n) { return ((a % n) + n) % n; }

inline void neigh_small_x(int i, int *tab) {
	int row = i / gridSide;
	int col = i % gridSide;

	tab[0] = mod(row - 1, gridSide) * gridSide + mod(col + 1, gridSide);
	tab[1] = mod(row - 1, gridSide) * gridSide + mod(col - 1, gridSide);
	tab[2] = mod(row + 1, gridSide) * gridSide + mod(col + 1, gridSide);
	tab[3] = mod(row + 1, gridSide) * gridSide + mod(col - 1, gridSide);
}

inline void neigh_x(int i, int *tab) {
	int row = i / gridSide; // zamiast index / size
	int col = i % gridSide; // zamiast index % size

	tab[0] = mod(row - 1, gridSide) * gridSide + mod(col + 1, gridSide);
	tab[1] = mod(row - 2, gridSide) * gridSide + mod(col + 2, gridSide);

	tab[2] = mod(row - 1, gridSide) * gridSide + mod(col - 1, gridSide);
	tab[3] = mod(row - 2, gridSide) * gridSide + mod(col - 2, gridSide);

	tab[4] = mod(row + 1, gridSide) * gridSide + mod(col + 1, gridSide);
	tab[5] = mod(row + 2, gridSide) * gridSide + mod(col + 2, gridSide);

	tab[6] = mod(row + 1, gridSide) * gridSide + mod(col - 1, gridSide);
	tab[7] = mod(row + 2, gridSide) * gridSide + mod(col - 2, gridSide);
}

inline void neigh_big_x(int i, int *tab) {
	int row = i / gridSide;
	int col = i % gridSide;

	tab[0] = mod(row - 1, gridSide) * gridSide + mod(col + 1, gridSide);
	tab[1] = mod(row - 2, gridSide) * gridSide + mod(col + 2, gridSide);
	tab[2] = mod(row - 3, gridSide) * gridSide + mod(col + 3, gridSide);

	tab[3] = mod(row - 1, gridSide) * gridSide + mod(col - 1, gridSide);
	tab[4] = mod(row - 2, gridSide) * gridSide + mod(col - 2, gridSide);
	tab[5] = mod(row - 3, gridSide) * gridSide + mod(col - 3, gridSide);

	tab[6] = mod(row + 1, gridSide) * gridSide + mod(col + 1, gridSide);
	tab[7] = mod(row + 2, gridSide) * gridSide + mod(col + 2, gridSide);
	tab[8] = mod(row + 3, gridSide) * gridSide + mod(col + 3, gridSide);

	tab[9] = mod(row + 1, gridSide) * gridSide + mod(col - 1, gridSide);
	tab[10] = mod(row + 2, gridSide) * gridSide + mod(col - 2, gridSide);
	tab[11] = mod(row + 3, gridSide) * gridSide + mod(col - 3, gridSide);
}

inline void neigh_small_cross(int i, int *tab) {
	int row = i / gridSide;
	int col = i % gridSide;

	tab[0] = mod(row, gridSide) * gridSide + mod(col + 1, gridSide);
	tab[1] = mod(row, gridSide) * gridSide + mod(col - 1, gridSide);
	tab[2] = mod(row + 1, gridSide) * gridSide + mod(col, gridSide);
	tab[3] = mod(row - 1, gridSide) * gridSide + mod(col, gridSide);
}

inline void neigh_big_cross(int i, int *tab) {
	int row = i / gridSide;
	int col = i % gridSide;


	tab[0] = mod(row + 3, gridSide) * gridSide + mod(col, gridSide);
	tab[1] = mod(row + 3, gridSide) * gridSide + mod(col + 1, gridSide);
	tab[2] = mod(row + 2, gridSide) * gridSide + mod(col, gridSide);
	tab[3] = mod(row + 1, gridSide) * gridSide + mod(col - 3, gridSide);
	tab[4] = mod(row + 1, gridSide) * gridSide + mod(col, gridSide);
	tab[5] = mod(row, gridSide) * gridSide + mod(col - 3, gridSide);
	tab[6] = mod(row, gridSide) * gridSide + mod(col - 2, gridSide);
	tab[7] = mod(row, gridSide) * gridSide + mod(col - 1, gridSide);
	tab[8] = mod(row, gridSide) * gridSide + mod(col + 1, gridSide);
	tab[9] = mod(row, gridSide) * gridSide + mod(col + 2, gridSide);
	tab[10] = mod(row, gridSide) * gridSide + mod(col + 3, gridSide);
	tab[11] = mod(row - 1, gridSide) * gridSide + mod(col, gridSide);
	tab[12] = mod(row - 1, gridSide) * gridSide + mod(col + 3, gridSide);
	tab[13] = mod(row - 2, gridSide) * gridSide + mod(col, gridSide);
	tab[14] = mod(row + 3, gridSide) * gridSide + mod(col - 1, gridSide);
	tab[15] = mod(row + 3, gridSide) * gridSide + mod(col, gridSide);
}

inline void neigh_elongated_vertical(int i, int *tab) {
	int row = i / gridSide;
	int col = i % gridSide;

	tab[0] = mod(row + 1, gridSide) * gridSide + mod(col, gridSide);
	tab[1] = mod(row + 2, gridSide) * gridSide + mod(col, gridSide);
	tab[2] = mod(row + 3, gridSide) * gridSide + mod(col, gridSide);
	tab[3] = mod(row - 1, gridSide) * gridSide + mod(col - 2, gridSide);
	tab[4] = mod(row - 1, gridSide) * gridSide + mod(col - 1, gridSide);
	tab[5] = mod(row - 1, gridSide) * gridSide + mod(col, gridSide);
	tab[6] = mod(row - 1, gridSide) * gridSide + mod(col + 1, gridSide);
	tab[7] = mod(row - 1, gridSide) * gridSide + mod(col + 2, gridSide);
}

inline void neigh_slash(int i, int *tab) {
	int row = i / gridSide;
	int col = i % gridSide;

	tab[0] = mod(row + 1, gridSide) * gridSide + mod(col + 1, gridSide);
	tab[1] = mod(row + 2, gridSide) * gridSide + mod(col + 2, gridSide);
	tab[2] = mod(row + 3, gridSide) * gridSide + mod(col + 3, gridSide);
	tab[3] = mod(row - 1, gridSide) * gridSide + mod(col - 1, gridSide);
	tab[4] = mod(row - 2, gridSide) * gridSide + mod(col - 2, gridSide);
	tab[5] = mod(row - 3, gridSide) * gridSide + mod(col - 3, gridSide);
}

inline void neigh_some_wierd(int i, int *tab) {
	int row = i / gridSide;
	int col = i % gridSide;

	tab[0] = mod(row + 1, gridSide) * gridSide + mod(col, gridSide);
	tab[1] = mod(row + 2, gridSide) * gridSide + mod(col, gridSide);
	tab[2] = mod(row + 1, gridSide) * gridSide + mod(col + 1, gridSide);
	tab[3] = mod(row + 2, gridSide) * gridSide + mod(col + 1, gridSide);
	tab[4] = mod(row - 1, gridSide) * gridSide + mod(col, gridSide);
	tab[5] = mod(row - 2, gridSide) * gridSide + mod(col, gridSide);
	tab[6] = mod(row - 1, gridSide) * gridSide + mod(col - 1, gridSide);
	tab[7] = mod(row - 2, gridSide) * gridSide + mod(col - 1, gridSide);
}

int energy_for_neigh(int i, bitset<bitsetSize> boardData, neigh_func foo, size_t big) {

	int energy = 0;
	boolean k = boardData[i];

	int tab[big];
	foo(i, tab);

	for (int j: tab) {
		energy += boardData[j] == k ? -weight : weight;
	}

	return energy;
}


int all_energy(bitset<bitsetSize> boardData, neigh_func foo, size_t big) {
	int energy = 0;
	for (int i = 0; i < bitsetSize; i++) {
		energy += energy_for_neigh(i, boardData, foo, big);
	}
	return energy;
}


bitset<bitsetSize> generate_bitset(double delta) {

	std::bitset<bitsetSize> result;
	for (size_t i = 0; i < bitsetSize; i++) {
		double random_chance = static_cast<double>(rand()) / (static_cast<double>(RAND_MAX) + 1.0);
		result[i] = (random_chance < delta);
	}
	return result;
}

random_device rd;
mt19937 gen(rd()); // seed the generator
uniform_int_distribution<> distr(0, bitsetSize);
auto change_two_bits(bitset<bitsetSize> boardData, neigh_func foo, size_t big) {

	int i = distr(gen);
	int j = distr(gen);
	while (i == j) {
		j = distr(gen);
	}
	bitset<bitsetSize> result = boardData;

	int pre_energy = 0;
	int energy = 0;
	try {
		if (result[i] != result[j]) {

			int tabi[big];
			int tabj[big];
			int tabi_neigh[big];
			int tabj_neigh[big];
			foo(i, tabi);
			foo(j, tabj);

			for (int k: tabi) {
				foo(k, tabi_neigh);
				for (int l: tabi_neigh) {
					if (l < 0 || l >= bitsetSize)
						throw l;
					pre_energy += energy_for_neigh(l, result, foo, big);
				}
			}
			for (int k: tabj) {
				foo(k, tabj_neigh);
				for (int l: tabj_neigh) {
					if (l < 0 || l >= bitsetSize)
						throw l;
					pre_energy += energy_for_neigh(l, result, foo, big);
				}
			}

			result[i] = !result[i];
			result[j] = !result[j];

			for (int k: tabi) {
				foo(k, tabi_neigh);
				for (int l: tabi_neigh) {
					energy += energy_for_neigh(l, result, foo, big);
				}
			}
			for (int k: tabj) {
				foo(k, tabj_neigh);
				for (int l: tabj_neigh) {
					energy += energy_for_neigh(l, result, foo, big);
				}
			}
		}
	} catch (int ind) {
		cerr << "i: " << i << " j: " << j << "trying access: " << ind << '\n';
	}
	return pair(result, pre_energy - energy);
}

bitset<bitsetSize> simulated_annealing(bitset<bitsetSize> boardData, double initialT, double multi, size_t kmax,
									   int neighbourhood) {
	size_t iterations = 0;

	size_t how_many_neigh;
	neigh_func func;
	switch (neighbourhood) {
		case 0:
			how_many_neigh = 4;
			func = neigh_small_cross;
			break;
		case 1:
			how_many_neigh = 4;
			func = neigh_small_x;
			break;
		case 2:
			how_many_neigh = 8;
			func = neigh_x;
			break;
		case 3:
			how_many_neigh = 12;
			func = neigh_big_x;
			break;
		case 4:
			how_many_neigh = 16;
			func = neigh_big_cross;
			break;
		case 5:
			how_many_neigh = 8;
			func = neigh_elongated_vertical;
			break;
		case 6:
			how_many_neigh = 6;
			func = neigh_slash;
			break;
		case 7:
			how_many_neigh = 8;
			func = neigh_some_wierd;
			break;
		default:
			how_many_neigh = 4;
			func = neigh_small_x;
			break;
	}

	bitset<bitsetSize> result = boardData;

	double currentEnergy = all_energy(result, func, how_many_neigh);

	double t = initialT;

	bitset<bitsetSize> globalLowestState = result;
	double globalBestEnergy = currentEnergy;

	ofstream f("func_zad2.dat");

	for (size_t i = 0; i < kmax; i++) {
		iterations++;
		if (i % 1000 == 0)
			cout << i << "\n";
		t *= multi;

		auto odp = change_two_bits(result, func, how_many_neigh);

		bitset<bitsetSize> neighbor = get<0>(odp);

		const double neighborEnergy = currentEnergy - get<1>(odp);

		f << i << " " << neighborEnergy << "\n";

		const double delta = neighborEnergy - currentEnergy;

		if (delta < 0 || exp(-delta / t) >= static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) {
			result = neighbor;

			currentEnergy = neighborEnergy;
			if (currentEnergy < globalBestEnergy) {
				globalLowestState = result;
				globalBestEnergy = currentEnergy;
			}
		}
	}
	f.close();
	return globalLowestState;
}


int draw_bitset(bitset<bitsetSize> boardData, const string name) {

	CImg<unsigned char> image(windowWidth, windowHeight, 1, 3, 0);

	const unsigned char black[] = {15, 15, 15};
	const unsigned char white[] = {240, 240, 240};

	std::cout << "Drawing grid..." << std::endl;
	for (size_t i = 0; i < boardData.size(); ++i) {
		int row = i / gridSide;
		int col = i % gridSide;

		int x0 = col * squareSize;
		int y0 = row * squareSize;

		int x1 = x0 + squareSize - 1;
		int y1 = y0 + squareSize - 1;

		const unsigned char *color = boardData[i] ? black : white;

		image.draw_rectangle(x0, y0, x1, y1, color, 1.0f);
	}
	std::cout << "Drawing complete." << std::endl;

	try {

		// image.display(name.c_str());
		std::cout << "Display window closed." << std::endl;
		image.save_bmp(("../img/" + name + ".bmp").c_str());
		std::cout << "Image saved as bitset_grid.png" << std::endl;

	} catch (const CImgException &e) {
		std::cerr << "CImg Error: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}

void plot_func(string name) {
	Gnuplot gpp;
	// gpp << "plot 'func_zad2.dat' with lines\n";
	gpp << "set terminal svg size 800, 800; set output '../img/" << name
		<< "_function.svg'; plot 'func_zad2.dat' with lines\n";
}

int zad2(string name, double delta, double initialT, double multi, size_t kmax, int mode) {

	srand(time(NULL));

	bitset<bitsetSize> boardData = generate_bitset(delta);

	thread first(draw_bitset, boardData, name);

	bitset<bitsetSize> wynik = simulated_annealing(boardData, initialT, multi, kmax, mode);


	thread second(draw_bitset, wynik, "post_" + name);

	thread plotting(plot_func, name);


	first.join();
	second.join();
	plotting.join();
	return 0;
}
