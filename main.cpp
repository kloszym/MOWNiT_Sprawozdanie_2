#include "for_running/zad1.h"
#include "for_running/zad2.h"
#include "for_running/zad3.h"

int main() {

	zad1("uni_random", 0, 1414.0, 0.99993, 100000.0, true, 20.0);
	zad1("uni_next", 0, 1414.0, 0.99993, 100000.0, false, 20.0);
	zad1("normal1", 1, 1414.0, 0.99993, 100000.0, true, 40.0);
	zad1("normal2", 1, 1414.0, 0.99993, 100000.0, true, 40.0);
	zad1("noraml3", 1, 1414.0, 0.99993, 100000.0, true, 40.0);
	zad1("normal4", 1, 1414.0, 0.99993, 100000.0, true, 40.0);
	zad1("9_section", 2, 1414.0, 0.9999, 100000.0, true, 40.0);

	zad2("small_cross", 0.1, 5000, 0.999995, 2000000, 0);
	zad2("small_x", 0.1, 5000, 0.999995, 2000000, 1);
	zad2("x", 0.1, 5000, 0.999995, 2000000, 2);
	zad2("big_x", 0.1, 5000, 0.999995, 2000000, 3);
	zad2("big_cross", 0.1, 5000, 0.999995, 2000000, 4);
	zad2("long", 0.1, 5000, 0.999995, 2000000, 5);
	zad2("slash", 0.1, 5000, 0.999995, 2000000, 6);
	zad2("weird", 0.1, 5000, 0.999995, 2000000, 7);

	zad3("normal_sudoku", false, 100, 0.9999, 50000);
	zad3("hard_sudoku", true, 100, 0.9999, 50000);
}
