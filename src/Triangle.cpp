#include "../include/Triangle.hpp"

Triangle::Triangle()
{
	vert1 = Vector3();
	vert2 = Vector3();
	vert3 = Vector3();
}

Triangle::Triangle(Vector3 v1, Vector3 v2, Vector3 v3)
{
	vert1 = v1;
	vert2 = v2;
	vert3 = v3;
}

double Triangle::getIntersection(const Ray& r) const
{
	Vector3 v1v2 = vert2 - vert1;
	Vector3 v1v3 = vert3 - vert1;

	Vector3 p = cross(r.direction, v1v3);
	double determinant = dot(v1v2, p);
	if (determinant > -0.001 && determinant < 0.001) return -1;

	double invDet = 1.0 / determinant;

	Vector3 t = r.origin - vert1;
	double u = dot(t, p) * invDet;
	if (u < 0 || u > 1) return -1;
	
	Vector3 q = cross(t, v1v2);
	double v = dot(r.direction, q) * invDet;
	if (v < 0 || u + v > 1) return -1;

	return dot(v1v3, q) * invDet;
}

Vector3 Triangle::getNormal(const Vector3& hit) const
{
	Vector3 v1v2 = vert2 - vert1;
	Vector3 v1v3 = vert3 - vert1;
	return cross(v1v2, v1v3);
}
