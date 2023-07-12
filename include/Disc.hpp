#pragma once

#include "../include/RenderObject.hpp"

class Disc : public RenderObject
{
public:
	Vector3 position;
	Vector3 normal;

	Disc();
	Disc(Vector3 pos, Vector3 nor);
	Disc(Vector3 pos, Vector3 nor, double r);

	double getIntersection(const Ray& r) const override;
	Vector3 getNormal(const Vector3& hit) const override;
private:
	double sqrRadius;
};
