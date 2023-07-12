#pragma once

#include "../include/RenderObject.hpp"

class Plane : public RenderObject
{
public:
	Vector3 position;
	Vector3 normal;

	Plane();
	Plane(Vector3 pos, Vector3 nor);
	Plane(Vector3 p1, Vector3 p2, Vector3 p3);

	double getIntersection(const Ray &r) const override;
	Vector3 getNormal(const Vector3 &hit) const override;
};
