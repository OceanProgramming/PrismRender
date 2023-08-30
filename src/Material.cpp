#include "Material.hpp"

#include "Ray.hpp"

#include "glm/gtc/random.hpp"
#include "glm/gtx/norm.hpp"

#include <algorithm>

namespace PrismRender
{
	Lambertian::Lambertian(glm::vec3 col)
	{
		baseColor = col;
	}

	Scatter Lambertian::scatterRay(const glm::vec3& inDirection, const glm::vec3& hit, const glm::vec3& normal)
	{
		Scatter scatter;

		scatter.outDirection = normal * 1.000001f + glm::sphericalRand(1.0f);
		scatter.color = baseColor;

		return scatter;
	}

	Metal::Metal(glm::vec3 col, float r)
	{
		baseColor = col;
		roughness = r;
	}

	Scatter Metal::scatterRay(const glm::vec3& inDirection, const glm::vec3& hit, const glm::vec3& normal)
	{

		Scatter scatter;

		scatter.outDirection = (inDirection - normal * 2.0f * glm::dot(inDirection, normal)) + glm::sphericalRand(1.0f) * roughness;
		scatter.color = baseColor;

		return scatter;
	}

	Glass::Glass(float rI)
	{
		refractiveIndex = rI;
	}

	const float Glass::reflectance(const float& cosAngle, const float& rI)
	{
		float r0 = std::pow((1.0 - rI) / (1.0 + rI), 2);
		return r0 + (1.0 - r0) * std::pow((1.0 - cosAngle), 5);
	}

	Scatter Glass::scatterRay(const glm::vec3& inDirection, const glm::vec3& hit, const glm::vec3& normal)
	{
		Scatter scatter;

		scatter.color = glm::vec3(1, 1, 1);
		float cosAngle = std::min(glm::dot(-inDirection, normal), 1.0f);
		float sinAngle = std::sqrtf(1 - cosAngle * cosAngle);

		float rIRatio;
		glm::vec3 outNormal;

		if (glm::dot(inDirection, normal) > 0.0)
		{
			rIRatio = refractiveIndex;
			outNormal = -normal;
		}
		else
		{
			rIRatio = (1 / refractiveIndex);
			outNormal = normal;
		}

		if (rIRatio * sinAngle > 1.0 || reflectance(cosAngle, rIRatio) > getRandom())
		{
			scatter.outDirection = (inDirection - outNormal * 2.0f * dot(inDirection, outNormal));
		}
		else
		{
			scatter.outDirection = (inDirection + outNormal * cosAngle) * rIRatio;
			scatter.outDirection = scatter.outDirection - outNormal * std::sqrtf(std::abs(1.0 - glm::length2(scatter.outDirection)));
		}

		return scatter;
	}
}