#pragma once

#include "../include/Vector3.hpp"
#include "../include/Ray.hpp"

class Camera
{
public:
	Vector3 position;
	Vector3 direction;
	double aspectRatio;
	double focalLength;

	Camera();
	Camera(Vector3 pos, Vector3 dir, double ar);
	Camera(Vector3 pos, Vector3 dir, double ar, double fl);

	Ray generateRay(double u, double v);

	void lookAt(Vector3 point);

private:
	Vector3 uVec;
	Vector3 vVec;

	void recalculateUV();
};
