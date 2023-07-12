#include "../include/Plane.hpp"

Plane::Plane()
{
	position = Vector3();
	normal = Vector3(0, 1, 0);
}

Plane::Plane(Vector3 pos, Vector3 nor)
{
	position = pos;
	normal = nor.normalize();
}


Plane::Plane(Vector3 p1, Vector3 p2, Vector3 p3)
{
	Vector3 v1 = p2 - p1;
	Vector3 v2 = p3 - p1;
	normal = cross(v1, v2).normalize();
}

double Plane::getIntersection(const Ray &r) const
{
	double denom = dot(normal, r.direction);
	if (std::abs(denom) < 0.0001) return -1;
	return dot(position - r.origin, normal) / denom;
}

Vector3 Plane::getNormal(const Vector3 &hit) const
{
	return normal;
}