#include "Sphere.hpp"

Sphere::Sphere()
{
	position = glm::vec3();
	radius = 1;
}

Sphere::Sphere(glm::vec3 pos, float r)
{
	position = pos;
	radius = r;
}

float Sphere::getIntersection(const Ray &r) const
{
	glm::vec3 oc = r.origin - position;
	float a = glm::dot(r.direction, r.direction);
	float hb = glm::dot(oc, r.direction);
	float c = glm::dot(oc, oc) - radius * radius;

	float discriminant = hb * hb - a * c;
	
	if (discriminant < 0)
	{
		return -1;
	}
	else
	{
		return (-hb - std::sqrt(discriminant)) / a;
	}
}

glm::vec3 Sphere::getNormal(const glm::vec3 &hit) const
{
	return (hit - position) / radius;
}