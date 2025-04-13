//
// Created by klosz on 08.04.2025.
//
#include "Point.h"

Point::Point() {
	x = 0;
	y = 0;
	id = 0;
}

Point::Point(double const w, double const z, int const ind) : x(w), y(z), id(ind) {}

Point::~Point(){}

Point& Point::operator=(const Point other) {
	this->x = other.x;
	this->y = other.y;
	this->id = other.id;
	return *this;
}

double Point::getX() const {
	return x;
}

double Point::getY() const {
	return y;
}

int Point::getId() const {
	return id;
}