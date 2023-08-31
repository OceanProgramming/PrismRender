#include "Renderer.hpp"

#include "Material.hpp"

#include <math.h>
#ifndef  M_PI
#define  M_PI  3.1415926535897932384626433
#endif
#include <chrono>
#include <iostream>
#include <algorithm>

namespace PrismRender
{
	void Renderer::render(Scene* scene, Camera* camera)
	{
		activeScene = scene;
		activeCamera = camera;

		const int samplesPerPixel = 10;
		const int bounceLimit = 20;
		const double gammaFactor = 1.0 / samplesPerPixel;

		size_t index = 0;
		for (int y = 0; y < output.height; y++)
		{
			for (int x = 0; x < output.width; x++)
			{
				glm::vec3 color(0, 0, 0);
				for (int s = 0; s < samplesPerPixel; s++)
				{
					Ray r(activeCamera->position, activeCamera->getRayDirections()[x + y * output.width]);
					color = color + renderRay(r, bounceLimit);
				}
				output.buffer[index++] = (uint8_t)(std::sqrt(color.x * gammaFactor) * 255.0f);
				output.buffer[index++] = (uint8_t)(std::sqrt(color.y * gammaFactor) * 255.0f);
				output.buffer[index++] = (uint8_t)(std::sqrt(color.z * gammaFactor) * 255.0f);
			}
		}
	}

	glm::vec3 Renderer::getSkyColor(const Image* world, const glm::vec3& dir)
	{
		glm::vec3 d = glm::normalize(-dir);
		float u = 0.5f + std::atan2f(d.z, d.x) / (2.0f * M_PI);
		float v = 0.5f + std::asinf(d.y) / M_PI;
		return world->getPixel(u, v);
	}

	glm::vec3 Renderer::renderRay(const Ray& r, int bounces)
	{
		if (bounces < 1)
		{
			return glm::vec3(0, 0, 0);
		}

		float distance = INFINITY;
		size_t hitIndex;

		for (size_t i = 0; i < activeScene->renderObjects.size(); i++)
		{
			float objectDistance = activeScene->renderObjects[i].getIntersection(r);
			if (objectDistance < distance && objectDistance > 0.001)
			{
				distance = objectDistance;
				hitIndex = i;
			}
		}

		if (distance == INFINITY)
		{
			return getSkyColor(&activeScene->environment, r.direction);
		}

		glm::vec3 hit = r.origin + r.direction * distance;
		glm::vec3 normal = activeScene->renderObjects[hitIndex].getNormal(hit);
		
		Scatter scatter = activeScene->materials[activeScene->renderObjects[hitIndex].materialIndex]->scatterRay(r.direction, hit, normal);

		return scatter.color * renderRay(Ray(hit, scatter.outDirection), bounces - 1);
	}
}
