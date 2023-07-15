#pragma once

#include "../include/Vector3.hpp"

struct Scatter
{
	Vector3 color;
	Vector3 outDirection;
};

class Material
{
public:
	virtual Scatter scatterRay(const Vector3& inDirection, const Vector3& hit, const Vector3& normal) = 0;
};

class Lambertian : public Material
{
public:
	Vector3 baseColor;

	Lambertian(Vector3 col);

	Scatter scatterRay(const Vector3& inDirection, const Vector3& hit, const Vector3& normal);
};

class Metal : public Material
{
public:
	Vector3 baseColor;
	double roughness;

	Metal(Vector3 col, double r);

	Scatter scatterRay(const Vector3& inDirection, const Vector3& hit, const Vector3& normal);
};

class Glass : public Material
{
public:
	double refractiveIndex;

	Glass(double rI);

	Scatter scatterRay(const Vector3& inDirection, const Vector3& hit, const Vector3& normal);
private:
	const double reflectance(const double& cosineAngle, const double &rI);
};