#include "../include/Camera.hpp"

namespace PrismRender
{
	Camera::Camera()
	{
		position = glm::vec3();
		direction = glm::vec3(0, 0, -1);
		viewportWidth = 1280;
		viewportHeight = 720;
		aspectRatio = (float)viewportWidth / viewportHeight;
		focalLength = 1;
		resizeViewport(viewportWidth, viewportHeight);
	}

	Camera::Camera(float aspect, float focal)
	{
		position = glm::vec3();
		direction = glm::vec3(0, 0, -1);
		viewportWidth = 1280;
		viewportHeight = 720;
		aspectRatio = aspect;
		focalLength = focal;
		resizeViewport(viewportWidth, viewportHeight);
	}

	void Camera::resizeViewport(int width, int height)
	{
		viewportWidth = width;
		viewportHeight = height;
		aspectRatio = (float)viewportWidth / viewportHeight;
		cachedRayDirections.resize(viewportWidth * viewportHeight);
		recalculateRayDirections();
	}

	void Camera::lookAt(glm::vec3 point)
	{
		direction = glm::normalize(point - position);
		recalculateUV();
		recalculateRayDirections();
	}

	void Camera::recalculateUV()
	{
		uVec = glm::normalize(glm::cross(direction, glm::vec3(0, 1, 0)));
		vVec = glm::normalize(glm::cross(direction, uVec));
	}
	void Camera::recalculateRayDirections()
	{
		for (int y = 0; y < viewportHeight; y++)
		{
			for (int x = 0; x < viewportWidth; x++)
			{
				glm::vec2 ndc((float)x / (float)viewportWidth, (float)y / (float)viewportHeight);
				ndc = ndc * 2.0f - 1.0f;
				ndc.x = ndc.x * aspectRatio;
				glm::vec3 dir = direction * focalLength + uVec * ndc.x + vVec * ndc.y;
				cachedRayDirections[x + y * viewportWidth] = dir;
			}
		}
	}
}