#pragma once

#include "../include/RenderObject.hpp"

class Triangle : public RenderObject
{
public:
	Vector3 vert1, vert2, vert3;

	Triangle();
	Triangle(Vector3 v1, Vector3 v2, Vector3 v3);

	double getIntersection(const Ray& r) const override;
	Vector3 getNormal(const Vector3& hit) const override;
};
