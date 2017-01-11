#pragma once
#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2d
{
	friend Vector2d operator+(Vector2d&, Vector2d&);

public:
	double i, j;

public:
	Vector2d();
	Vector2d(double i, double j);
	double getMagnitude();
	double dot(Vector2d v);
	Vector2d proj(Vector2d v);
	Vector2d getUnitVector();
	Vector2d plus(Vector2d v);
	Vector2d times(double scalar);
		
	~Vector2d();
};

//Vector2d operator+ (Vector2d &v1, Vector2d &v2)
//{
//	return Vector2d(v1.i + v2.i, v1.j + v2.j);
//}
//
//Vector2d operator* (Vector2d &v, double &scalar)
//{
//	return Vector2d(v.i * scalar, v.j * scalar);
//}
//
//Vector2d operator* (Vector2d &v, float &scalar)
//{
//	return Vector2d(v.i * scalar, v.j * scalar);
//}

#endif // !
