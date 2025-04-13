//
// Created by klosz on 08.04.2025.
//

#ifndef POINT_H
#define POINT_H

class Point {
public:
	Point();
	Point(double, double, int);
	~Point();
	Point &operator=(Point);
	double getX() const;
	double getY() const;
	int getId() const;

private:
	double x;
	double y;
	int id;
};

#endif // POINT_H
