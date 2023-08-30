#pragma once

#include "glm/glm.hpp"

namespace PrismRender
{
	struct Scatter
	{
		glm::vec3 color;
		glm::vec3 outDirection;
	};

	class Material
	{
	public:
		virtual Scatter scatterRay(const glm::vec3& inDirection, const glm::vec3& hit, const glm::vec3& normal) = 0;
	};

	class Lambertian : public Material
	{
	public:
		Lambertian(glm::vec3 col);

		Scatter scatterRay(const glm::vec3& inDirection, const glm::vec3& hit, const glm::vec3& normal);

		glm::vec3 baseColor;
	};

	class Metal : public Material
	{
	public:
		Metal(glm::vec3 col, float r);

		Scatter scatterRay(const glm::vec3& inDirection, const glm::vec3& hit, const glm::vec3& normal);

		glm::vec3 baseColor;
		float roughness;
	};

	class Glass : public Material
	{
	public:
		Glass(float rI);

		Scatter scatterRay(const glm::vec3& inDirection, const glm::vec3& hit, const glm::vec3& normal);

		float refractiveIndex;
	private:
		const float reflectance(const float& cosineAngle, const float& rI);
	};
}