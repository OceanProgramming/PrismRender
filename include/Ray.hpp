#pragma once

#include "glm/glm.hpp"

namespace PrismRender
{
	struct Ray
	{
		Ray(glm::vec3 orig, glm::vec3 dir) : origin(orig), direction(dir) {};

		glm::vec3 origin;
		glm::vec3 direction;
	};

	inline float getRandom()
	{
		return ((float)rand() + 1) / (RAND_MAX + 1);
	}
}