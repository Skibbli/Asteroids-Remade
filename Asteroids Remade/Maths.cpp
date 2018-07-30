#include "stdafx.h"

#include "Maths.h"

int GenRandNo(int _min, int _max)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(_min, _max);

	return distr(eng);
}

Vec2 RotateAroundPoint(Vec2 _pivotPoint, Vec2 _pointToRot, float _angle)
{
	Vec2 newPoint;

	float s = sin(_angle);
	float c = cos(_angle);

	// translate point back to origin:
	_pointToRot.x = _pointToRot.x - _pivotPoint.x;
	_pointToRot.y = _pointToRot.y - _pivotPoint.y;

	// rotate point
	float xnew = _pointToRot.x * c - _pointToRot.y * s;
	float ynew = _pointToRot.x * s + _pointToRot.y * c;

	// translate point back:
	_pointToRot.x = xnew + _pivotPoint.x;
	_pointToRot.y = ynew + _pivotPoint.y;

	return _pointToRot;
}