#pragma once

#define _USE_MATH_DEFINES
#include <math.h>
#include <cstdlib>
#include <iostream>

class Vector3
{
public:
	double x, y, z;

	Vector3();
	Vector3(double xx);
	Vector3(double xx, double yy, double zz);

	Vector3 operator + (const Vector3 &v) const;
	Vector3 operator - (const Vector3 &v) const;
	Vector3 operator - () const;
	Vector3 operator * (const double &f) const;
	Vector3 operator * (const Vector3 &v) const;
	Vector3 operator / (const double &f) const;
	bool operator == (const Vector3& v) const;
	
	double sqrLength() const;
	double length() const;

	const Vector3 normalize() const;

	friend std::ostream& operator << (std::ostream &os, const Vector3 &v);
};

double getRandom();
double dot(const Vector3 &v1, const Vector3 &v2);
Vector3 cross(const Vector3 &v1, const Vector3 &v2);
Vector3 onUnitSphere();

template<> struct std::hash<Vector3>
{
	size_t operator()(const Vector3& v) const
	{
		return std::hash<double>()(v.x) ^ (std::hash<double>()(v.y) << 1) ^ std::hash<double>()(v.z);
	}
};