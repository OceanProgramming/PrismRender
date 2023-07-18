#include <iostream>
#include <memory>
#include <vector>
#include <math.h>
#include <chrono>

#include "../include/Image.hpp"
#include "../include/Camera.hpp"
#include "../include/Ray.hpp"
#include "../include/Sphere.hpp"
#include "../include/Plane.hpp"
#include "../include/Disc.hpp"
#include "../include/Triangle.hpp"
#include "../include/Mesh.hpp"
#include "../include/Material.hpp"

Vector3 renderRay(const Ray& r, const std::vector<RenderObject*>& scene, const std::vector<Material*>& materials, Image* world, int bounces);

int main()
{
	const int width = 1024;
	const int height = 512;

	Image outputImage(width, height, 3);

	Image world("solitude_interior_4k.hdr");

	double aspectRatio = (double)width / height;
	Camera cam(Vector3(5, 3, 0), Vector3(0, 1, 1), aspectRatio, 1.5);
	cam.lookAt(Vector3(0, 1, 0));

	Lambertian diffuseRed(Vector3(1, 0.25, 0.25));
	Lambertian diffuseWhite(Vector3(1, 1, 1));
	//Metal metal(Vector3(1, 1, 1), 0);
	//Glass glass(1.45);

	std::vector<Material*> materials;
	materials.push_back(&diffuseRed);
	materials.push_back(&diffuseWhite);

	Disc d(Vector3(0, 0, 0), Vector3(0, 1, 0), 5);

	std::vector<RenderObject*> renderObjects;
	renderObjects.push_back(&d);

	Mesh heartMesh("mug.obj");
	heartMesh.materialIndex = 1;
	renderObjects.push_back(&heartMesh);

	const int samplesPerPixel = 100;
	const int bounceLimit = 20;
	const double gammaFactor = 1.0 / samplesPerPixel;

	auto startTime = std::chrono::high_resolution_clock::now();
	
	size_t index = 0;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Vector3 color(0, 0, 0);
			for (int s = 0; s < samplesPerPixel; s++)
			{
				Ray r = cam.generateRay(((double)x + getRandom()) / width, ((double)y + getRandom()) / height);
				color = color + renderRay(r, renderObjects, materials, &world, bounceLimit);
			}
			outputImage.buf[index++] = (int)(std::sqrt(color.x * gammaFactor) * 255);
			outputImage.buf[index++] = (int)(std::sqrt(color.y * gammaFactor) * 255);
			outputImage.buf[index++] = (int)(std::sqrt(color.z * gammaFactor) * 255);
		}
		std::cout << y + 1 << " / " << height << "\n";
	}

	auto endTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double, std::milli> ms_double = endTime - startTime;
	std::cout << "Rendered image in " << ms_double.count() << " milliseconds\n";

	outputImage.save("out.png");
	
	return 0;
}

Vector3 getSkyColor(Image* world, const Vector3 &dir)
{
	Vector3 d = -dir.normalize();
	double u = 0.5 + std::atan2(d.x, d.z) / (2 * M_PI);
	double v = 0.5 + std::asin(d.y) / M_PI;
	return world->getPixel(u, v);
}

Vector3 renderRay(const Ray &r, const std::vector<RenderObject*> &scene, const std::vector<Material*>& materials, Image* world, int bounces)
{
	if (bounces < 1)
	{
		return Vector3(0, 0, 0);
	}

	double distance = INFINITY;
	size_t hitIndex;

	for (size_t i = 0; i < scene.size(); i++)
	{
		double objectDistance = scene[i]->getIntersection(r);
		if (objectDistance < distance && objectDistance > 0.001)
		{
			distance = objectDistance;
			hitIndex = i;
		}
	}

	if (distance == INFINITY)
	{
		return getSkyColor(world, r.direction);
	}

	Vector3 hit = r.origin + r.direction * distance;
	Vector3 normal = scene[hitIndex]->getNormal(hit);

	Scatter scatter = materials[scene[hitIndex]->materialIndex]->scatterRay(r.direction, hit, normal);

	return scatter.color * renderRay(Ray(hit, scatter.outDirection), scene, materials, world, bounces - 1);
}
