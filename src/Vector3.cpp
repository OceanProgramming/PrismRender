#include "../include/Vector3.hpp"

Vector3::Vector3()
{
	x = 0;
	y = 0;
	z = 0;
}

Vector3::Vector3(double xx)
{
	x = xx;
	y = xx;
	z = xx;
}

Vector3::Vector3(double xx, double yy, double zz)
{
	x = xx;
	y = yy;
	z = zz;
}

Vector3 Vector3::operator + (const Vector3 &v) const
{
	return Vector3(x + v.x, y + v.y, z + v.z);
}

Vector3 Vector3::operator - (const Vector3 &v) const
{
	return Vector3(x - v.x, y - v.y, z - v.z);
}

Vector3 Vector3::operator - () const
{
	return Vector3(-x, -y, -z);
}

Vector3 Vector3::operator * (const Vector3 &v) const
{
	return Vector3(x * v.x, y * v.y, z * v.z);
}

Vector3 Vector3::operator * (const double &f) const
{
	return Vector3(x * f, y * f, z * f);
}

Vector3 Vector3::operator / (const double &f) const
{
	return Vector3(x / f, y / f, z / f);
}

double Vector3::length() const
{
	return std::sqrt(x * x + y * y + z * z);
}

double Vector3::sqrLength() const
{
	return x * x + y * y + z * z;
}

const Vector3 Vector3::normalize() const
{
	double length = this->length();
	return Vector3(x / length, y / length, z / length);
}

std::ostream& operator << (std::ostream &os, const Vector3 &v)
{
	return os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
}

const double randMax = (double)(RAND_MAX + 1);

double getRandom()
{
	return ((double)rand() + 1) / randMax;
}

double dot(const Vector3 &v1, const Vector3 &v2)
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

Vector3 cross(const Vector3 &v1, const Vector3 &v2)
{
	return Vector3(v1.y * v2.z - v1.z * v2.y, v1.z * v2.x - v1.x * v2.z, v1.x * v2.y - v1.y * v2.x);
}

Vector3 onUnitSphere()
{
	double u = 2 * 3.14159 * getRandom();
	double v = acos(2 * getRandom() - 1);
	return Vector3(cos(u) * cos(v), sin(u) * cos(v), sin(v));
}
