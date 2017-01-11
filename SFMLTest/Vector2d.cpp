#include "Vector2d.h"
#include <cmath>

Vector2d::Vector2d() : i(0), j(0) {}

Vector2d::Vector2d(double i, double j) 
	: i(i), j(j) {} 

double Vector2d::getMagnitude() 
{
	return sqrt(i*i + j*j);
}

double Vector2d::dot(Vector2d v) 
{
	return i*v.i + j*v.j;
}

Vector2d Vector2d::proj(Vector2d v) 
{
	double d = dot(v) / v.dot(v);
	return v.times(d);
}

Vector2d Vector2d::getUnitVector()
{
	return Vector2d(i / getMagnitude(), j / getMagnitude());
}

Vector2d Vector2d::plus(Vector2d v)
{
	return Vector2d(v.i + i, v.j + j);
}

Vector2d Vector2d::times(double scalar)
{
	return Vector2d(i*scalar, j*scalar);
}

Vector2d::~Vector2d() {}
