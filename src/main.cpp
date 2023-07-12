#include <iostream>
#include <memory>
#include <vector>
#include <math.h>

#include "../include/Image.hpp"
#include "../include/Camera.hpp"
#include "../include/Ray.hpp"
#include "../include/Sphere.hpp"
#include "../include/Plane.hpp"
#include "../include/Disc.hpp"
#include "../include/Material.hpp"

Vector3 renderRay(const Ray& r, const std::vector<RenderObject*>& scene, const std::vector<Material*>& materials, Image* world, int bounces);

int main()
{
	const int width = 1024;
	const int height = 512;

	Image img(width, height, 3);
	int* sampled = new int[width * height * 3]();

	Image world("solitude_interior_2k.hdr");

	double aspectRatio = (double)width / height;
	Camera cam(Vector3(0, 0, 5), Vector3(0, 0, -1), aspectRatio, 1.5);

	Metal purple(Vector3(0.5, 0.1, 0.2), 0);
	Lambertian blue(Vector3(1, 1, 1));
	Glass glass(1.45);

	std::vector<Material*> materials;
	materials.push_back(&purple);
	materials.push_back(&blue);
	materials.push_back(&glass);

	Sphere s(Vector3(0, 0.25, -5), 1.5);
	Sphere s2(Vector3(0.5, 0.5, 2.5), 0.5);
	s2.materialIndex = 2;
	Disc d(Vector3(0, -1.5, -5), Vector3(0, 1, 0), 5);
	d.materialIndex = 1;

	std::vector<RenderObject*> renderObjects;
	renderObjects.push_back(&s);
	renderObjects.push_back(&s2);
	renderObjects.push_back(&d);

	const int pixelSamples = 10;
	const double gammaFactor = 1.0 / pixelSamples;
	
	size_t index = 0;
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			Vector3 color(0, 0, 0);
			for (int s = 0; s < pixelSamples; s++)
			{
				Ray r = cam.generateRay(((float)x + getRandom()) / width, ((float)y + getRandom()) / height);
				color = color + renderRay(r, renderObjects, materials, &world, 10);
			}
			img.buf[index++] = (int)(std::sqrt(color.x * gammaFactor) * 255);
			img.buf[index++] = (int)(std::sqrt(color.y * gammaFactor) * 255);
			img.buf[index++] = (int)(std::sqrt(color.z * gammaFactor) * 255);
		}
	}

	img.save("out.png");
	
	return 0;
}

Vector3 getSkyColor(Image* world, const Vector3 &dir)
{
	Vector3 d = -dir.normalize();
	double u = 0.5 + std::atan2(d.x, d.z) / (2 * 3.14159);
	double v = 0.5 + std::asin(d.y) / 3.14159;
	return world->getPixel(u, v);
}

Vector3 renderRay(const Ray &r, const std::vector<RenderObject*> &scene, const std::vector<Material*>& materials, Image* world, int bounces)
{
	if (bounces < 1)
	{
		return Vector3(0, 0, 0);
	}

	double minDist = INFINITY;
	size_t hitIndex;

	for (size_t i = 0; i < scene.size(); i++)
	{
		double distance = scene[i]->getIntersection(r);
		if (distance < minDist && distance > 0.0001)
		{
			minDist = distance;
			hitIndex = i;
		}
	}

	if (minDist == INFINITY)
	{	
		return getSkyColor(world, r.direction);
	}

	Vector3 hit = r.origin + r.direction * minDist;
	Vector3 normal = scene[hitIndex]->getNormal(hit);

	Scatter scatter = materials[scene[hitIndex]->materialIndex]->scatterRay(r.direction, hit, normal);

	return scatter.color * renderRay(Ray(hit, scatter.outDirection), scene, materials, world, bounces - 1);
}
