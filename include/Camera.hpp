#pragma once

#include "Ray.hpp"

#include <vector>

namespace PrismRender
{
	class Camera
	{
	public:
		Camera();
		Camera(float aspect, float focal);

		const std::vector<glm::vec3>& getRayDirections() { return cachedRayDirections; };
		void resizeViewport(int width, int height);
		void lookAt(glm::vec3 point);

		glm::vec3 position;
		glm::vec3 direction;
		float aspectRatio;
		float focalLength;
	private:
		void recalculateUV();
		void recalculateRayDirections();
		
		int viewportWidth = 0, viewportHeight = 0;
		glm::vec3 uVec, vVec;
		std::vector<glm::vec3> cachedRayDirections;
	};
}