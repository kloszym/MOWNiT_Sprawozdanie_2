#include "for_running/zad1.h"
#include <cmath>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
#include "gnuplot-iostream.h"
#include "zad1_pack/Point.h"

using namespace std;

double distance(const Point &a, const Point &b) {
	double xd = a.getX() - b.getX();
	double yd = a.getY() - b.getY();
	return sqrt(xd * xd + yd * yd);
}

vector<Point> toSwapped2opt(const vector<Point> nodes, const int v1, const int v2) {
	vector<Point> result;

	for (int i = 0; i < v1; ++i)
		result.push_back(nodes[i]);

	for (int i = v2; i >= v1; --i)
		result.push_back(nodes[i]);

	for (int i = v2 + 1; i < nodes.size(); ++i)
		result.push_back(nodes[i]);

	return result;
}

double calculateLength(const vector<Point> nodes) {
	double result = 0;
	size_t size = nodes.size();
	for (size_t i = 0; i < size - 1; i++) {
		result += distance(nodes[i], nodes[i + 1]);
	}
	result += distance(nodes[size - 1], nodes[0]);
	return result;
}


vector<Point> getNextNeighbor(vector<Point> nodes, int v1) {

	size_t size = nodes.size();
	int v2 = v1 + 1 == size ? 0 : v1 + 1;

	if (v1 > v2) {
		int temp = v1;
		v1 = v2;
		v2 = temp;
	}
	return toSwapped2opt(nodes, v1, v2);
}

vector<Point> getRandomNeighbor(vector<Point> nodes) {

	size_t size = nodes.size();

	int v1 = rand() % size;
	int v2 = rand() % size;

	while (v1 == v2) {
		v2 = rand() % size;
	}
	if (v1 > v2) {
		int temp = v1;
		v1 = v2;
		v2 = temp;
	}
	return toSwapped2opt(nodes, v1, v2);
}

auto tsp(vector<Point> nodes, double initialT, double multi, size_t kmax, bool ifRandom) {
	size_t iterations = 0;
	vector<Point> currentPath = nodes;
	size_t size = nodes.size();

	double currentLength = calculateLength(currentPath);

	double t = initialT;

	vector<Point> globalBestPath = currentPath;
	double globalBestLength = currentLength;

	ofstream f("func.dat");

	for (size_t i = 0; i < kmax; i++) {
		if (i % 1000 == 0)
			cout << "iteration: " << i << "\n";
		iterations++;

		t *= multi;

		vector<Point> neighbor;

		if (ifRandom) {
			neighbor = getRandomNeighbor(currentPath);
		} else {
			neighbor = getNextNeighbor(currentPath, i % size);
		}


		const double neighborLength = calculateLength(neighbor);

		const double delta = neighborLength - currentLength;

		if (delta < 0 || exp(-delta / t) >= static_cast<float>(rand()) / static_cast<float>(RAND_MAX)) {
			currentPath = neighbor;
			currentLength = neighborLength;
			f << i << " " << neighborLength << "\n";
			if (currentLength < globalBestLength) {
				globalBestPath = currentPath;
				globalBestLength = currentLength;
			}
		}
	}
	f.close();
	return globalBestPath;
}

void visualizeGraph(vector<Point> nodes, string name, double point_size) {
	Gnuplot gp("");
	ofstream graphFile("graph.dat");
	size_t size = nodes.size();
	for (size_t i = 0; i < size - 1; i++) {
		graphFile << nodes[i].getX() << " " << nodes[i].getY() << " " << nodes[i].getId() << "\n";
		graphFile << nodes[i + 1].getX() << " " << nodes[i + 1].getY() << " " << nodes[i + 1].getId() << "\n\n";
	}
	graphFile << nodes[size - 1].getX() << " " << nodes[size - 1].getY() << " " << nodes[size - 1].getId() << "\n";
	graphFile << nodes[0].getX() << " " << nodes[0].getY() << " " << nodes[0].getId() << "\n";
	graphFile.close();
	string plotCommand =
			"plot 'graph.dat' using 1:2       with lines lc rgb \"black\" lw 2 notitle, 'graph.dat' using 1:2:(";
	plotCommand.append(to_string(point_size));
	plotCommand.append(") with circles fill solid lc rgb \"black\" notitle, 'graph.dat' using 1:2:3     with labels tc "
					   "rgb \"white\" offset (0,0) font 'Arial Bold' notitle\n");
	gp << plotCommand;
	gp << "set terminal svg size 800, 800; set output '../img/" << name << ".svg'; " << plotCommand;
}

random_device random;
mt19937 gnr(random()); // seed the generator
uniform_real_distribution<> between(0.0, 1000.0);

vector<Point> uniform_distribution_graph() {
	vector<Point> nodes;
	for (int i = 0; i < 100; ++i) {
		double x = between(gnr);
		double y = between(gnr);
		nodes.emplace_back(Point(x, y, i));
	}
	return nodes;
}

vector<Point> normal_distribution_graph(double mean, double stddev) {
	normal_distribution dist(mean, stddev);
	vector<Point> nodes;
	for (int i = 0; i < 100; ++i) {
		double x = dist(gnr);
		double y = dist(gnr);
		nodes.emplace_back(Point(x, y, i));
	}
	return nodes;
}

vector<Point> nine_clusters_graph() {
	vector<pair<double, double>> places = {
			make_pair(0, 0),	 make_pair(900, 0),	   make_pair(-900, 0),	 make_pair(0, 900),		make_pair(0, -900),
			make_pair(636, 636), make_pair(636, -636), make_pair(-636, 636), make_pair(-636, -636),
	};
	uniform_int_distribution<> place(0, 8);
	uniform_real_distribution<> dist(50.0, 250.0);
	vector<Point> nodes;
	for (int i = 0; i < 81; ++i) {
		pair<double, double> origin = places[place(gnr)];
		double x = get<0>(origin) + dist(gnr);
		double y = get<1>(origin) + dist(gnr);
		nodes.emplace_back(Point(x, y, i));
	}
	return nodes;
}

int zad1(string name, int type, double initialT, double multi, size_t k_max, bool isRandom, double point_size) {
	srand(time(NULL));
	vector<Point> nodes;
	switch (type) {
		case 0: {
			nodes = uniform_distribution_graph();
			break;
		}
		case 1: {
			uniform_real_distribution<> dist(0.0, 1000.0);
			nodes = normal_distribution_graph(dist(gnr), dist(gnr));
			break;
		}
		case 2: {
			nodes = nine_clusters_graph();
			break;
		}
		default: {
			nodes = uniform_distribution_graph();
			break;
		}
	}

	visualizeGraph(nodes, name, point_size);
	vector<Point> result = tsp(nodes, initialT, multi, k_max, isRandom);
	visualizeGraph(result, "post_" + name, point_size);
	Gnuplot gpp;
	// gpp << "plot 'func.dat' with lines\n";
	gpp << "set terminal svg size 800, 800; set output '../img/" << name
		<< "_function.svg'; plot 'func.dat' with lines\n";
	return 0;
}
