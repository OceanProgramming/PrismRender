#include "../include/Camera.hpp"

Camera::Camera()
{
	position = Vector3();
	direction = Vector3(0, 0, -1);
	aspectRatio = 1;
	focalLength = 1;
	recalculateUV();
}

Camera::Camera(Vector3 pos, Vector3 dir, double ar)
{
	position = pos;
	direction = dir.normalize();
	aspectRatio = ar;
	focalLength = 1;
	recalculateUV();
}

Camera::Camera(Vector3 pos, Vector3 dir, double ar, double fl)
{
	position = pos;
	direction = dir.normalize();
	aspectRatio = ar;
	focalLength = fl;
	recalculateUV();
}

Ray Camera::generateRay(double u, double v)
{
	const double rayU = aspectRatio * (u - 0.5);
	const double rayV = v - 0.5;

	Vector3 rayDir = direction * focalLength + uVec * rayU + vVec * rayV;

	return Ray(position, rayDir.normalize());
}

void Camera::lookAt(Vector3 point)
{
	direction = (point - position).normalize();
	recalculateUV();
}

void Camera::recalculateUV()
{
	uVec = cross(direction, Vector3(0, 1, 0)).normalize();
	vVec = cross(direction, uVec).normalize();
}