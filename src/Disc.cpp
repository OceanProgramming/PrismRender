#include "../include/Disc.hpp"

Disc::Disc()
{
	position = Vector3();
	normal = Vector3(0, 1, 0);
	sqrRadius = 1;
}

Disc::Disc(Vector3 pos, Vector3 nor)
{
	position = pos;
	normal = nor.normalize();
	sqrRadius = 1;
}

Disc::Disc(Vector3 pos, Vector3 nor, double r)
{
	position = pos;
	normal = nor.normalize();
	sqrRadius = r * r;
}

double Disc::getIntersection(const Ray& r) const
{
	double denom = dot(normal, r.direction);
	if (std::abs(denom) < 0.0001) return -1;
	double potentialHitDistance = dot(position - r.origin, normal) / denom;
	Vector3 planeHit = r.origin + r.direction * potentialHitDistance;
	if ((position - planeHit).sqrLength() > sqrRadius) return -1;
	return potentialHitDistance;
}

Vector3 Disc::getNormal(const Vector3& hit) const
{
	return normal;
}