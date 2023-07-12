#pragma once

#include "Vector3.hpp"

class Ray
{
public:
	Vector3 origin;
	Vector3 direction;

	Ray(Vector3 orig, Vector3 dir);
};
