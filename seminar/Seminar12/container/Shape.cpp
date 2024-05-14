#include "Shape.h"

Shape::Shape(int pointsCount) : pointsCount(pointsCount) {
	points = new point[pointsCount]; 
}

void Shape::copyFrom(const Shape& other) {
	points = new point[other.pointsCount];
	
	for (int i = 0; i < other.pointsCount; i++){
        points[i] = other.points[i];
    }
		
	pointsCount = other.pointsCount;
}
void Shape::free() {
	delete[] points;
}

Shape::Shape(const Shape& other) {
	copyFrom(other);
}

Shape& Shape::operator= (const Shape& other) {
	if (this != &other)
	{
		free();
		copyFrom(other);
	}
	return *this;
}

Shape::~Shape() {
	free();
}

const Shape::point& Shape::getPointAtIndex(int index) const {
	if (index >= pointsCount)
		throw std::invalid_argument("Invalid point index!");

	return  points[index];
}

void Shape::setPoint(int pointIndex, int x, int y)
{
	if (pointIndex >= pointsCount)
		throw std::invalid_argument("Invalid point index!");

	points[pointIndex] = point(x, y);
}