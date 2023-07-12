#include "../include/Sphere.hpp"

Sphere::Sphere()
{
	position = Vector3();
	radius = 1;
}

Sphere::Sphere(Vector3 pos, double r)
{
	position = pos;
	radius = r;
}

double Sphere::getIntersection(const Ray &r) const
{
	Vector3 oc = r.origin - position;
	double a = dot(r.direction, r.direction);
	double hb = dot(oc, r.direction);
	double c = dot(oc, oc) - radius * radius;

	double discriminant = hb * hb - a * c;
	
	if (discriminant < 0)
	{
		return -1;
	}
	else
	{
		return (-hb - std::sqrt(discriminant)) / a;
	}
}

Vector3 Sphere::getNormal(const Vector3 &hit) const
{
	return (hit - position) / radius;
}