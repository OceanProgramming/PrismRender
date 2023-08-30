#pragma once

#include "Ray.hpp"

#include "glm/glm.hpp"

namespace PrismRender
{
	class Sphere
	{
	public:
		Sphere();
		Sphere(glm::vec3 pos, float r);

		float getIntersection(const Ray& r) const;
		glm::vec3 getNormal(const glm::vec3& hit) const;

		glm::vec3 position;
		float radius;

		int materialIndex = 0;
	};
}
