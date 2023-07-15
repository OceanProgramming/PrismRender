#include "..\include\Material.hpp"

Lambertian::Lambertian(Vector3 col)
{
	baseColor = col;
}

Scatter Lambertian::scatterRay(const Vector3& inDirection, const Vector3& hit, const Vector3& normal)
{
	Scatter scatter;

	scatter.outDirection = normal * 1.000001 + onUnitSphere();
	scatter.color = baseColor;

	return scatter;
}

Metal::Metal(Vector3 col, double r)
{
	baseColor = col;
	roughness = r;
}

Scatter Metal::scatterRay(const Vector3& inDirection, const Vector3& hit, const Vector3& normal)
{

	Scatter scatter;

	scatter.outDirection = (inDirection - normal * 2 * dot(inDirection, normal)) + onUnitSphere() * roughness;
	scatter.color = baseColor;

	return scatter;
}

Glass::Glass(double rI)
{
	refractiveIndex = rI;
}

const double Glass::reflectance(const double& cosAngle, const double& rI)
{
	double r0 = std::pow((1.0 - rI) / (1.0 + rI), 2);
	return r0 + (1.0 - r0) * std::pow((1.0 - cosAngle), 5);
}

Scatter Glass::scatterRay(const Vector3& inDirection, const Vector3& hit, const Vector3& normal)
{
	Scatter scatter;

	scatter.color = Vector3(1, 1, 1);
	double cosAngle = std::min(dot(-inDirection, normal), 1.0);
	double sinAngle = std::sqrt(1 - cosAngle * cosAngle);

	double rIRatio;
	Vector3 outNormal;

	if (dot(inDirection, normal) > 0.0)
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
		scatter.outDirection = (inDirection - outNormal * 2 * dot(inDirection, outNormal));
	}
	else
	{
		scatter.outDirection = (inDirection + outNormal * cosAngle) * rIRatio;
		scatter.outDirection = scatter.outDirection - outNormal * std::sqrt(std::abs(1.0 - scatter.outDirection.sqrLength()));
	}
	
	return scatter;
}
