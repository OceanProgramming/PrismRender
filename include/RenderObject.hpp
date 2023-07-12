#pragma once

#include "../include/Ray.hpp"
#include "../include/Material.hpp"

class RenderObject
{
public:
	int materialIndex = 0;

	virtual double getIntersection(const Ray &r) const;
	virtual Vector3 getNormal(const Vector3 &hit) const;
};
