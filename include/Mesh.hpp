#pragma once

#include <vector>

#include "rapidobj/rapidobj.hpp"

#include "../include/RenderObject.hpp"

class Mesh : public RenderObject
{
public:
	std::vector<Vector3> vertices;
	std::vector<int> indices;
	mutable Vector3 currentNormal;

	Mesh(const char* fileName);

	double getIntersection(const Ray& r) const override;
	Vector3 getNormal(const Vector3& hit) const override;
};
