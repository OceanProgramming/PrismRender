#pragma once

#include "../include/RenderObject.hpp"

class Sphere : public RenderObject
{
public:
	Vector3 position;
	double radius;

	Sphere();
	Sphere(Vector3 pos, double r);

	double getIntersection(const Ray &r) const override;
	Vector3 getNormal(const Vector3 &hit) const override;
};
