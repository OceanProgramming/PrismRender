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

Scatter Glass::scatterRay(const Vector3& inDirection, const Vector3& hit, const Vector3& normal)
{
	Scatter scatter;

	scatter.color = Vector3(1, 1, 1);
	double cosAngle = std::min(dot(-inDirection, normal), 1.0);
	double sinAngle = std::sqrt(1 - cosAngle * cosAngle);
	double rIRatio = (dot(inDirection, normal) > 0) ? refractiveIndex : (1 / refractiveIndex);

	if (rIRatio * sinAngle > 1.0)
	{
		scatter.outDirection = (inDirection - normal * 2 * dot(inDirection, normal));
	}
	else
	{
		scatter.outDirection = (inDirection + normal * cosAngle) * rIRatio;
		scatter.outDirection = scatter.outDirection + normal * -std::sqrt(std::abs(1.0 - scatter.outDirection.sqrLength()));
	}
	
	return scatter;
}
