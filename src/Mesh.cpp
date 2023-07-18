#include "../include/Mesh.hpp"
#include "../include/Triangle.hpp"

Mesh::Mesh(const char* fileName)
{
	rapidobj::Result result = rapidobj::ParseFile(fileName);

	if (result.error)
	{
		std::cerr << result.error.code.message() << "\n";
	}

	bool success = rapidobj::Triangulate(result);

	if (!success)
	{
		std::cerr << result.error.code.message() << "\n";
	}

	for (size_t i = 0; i < result.attributes.positions.size(); i += 3)
	{
		vertices.push_back(Vector3(result.attributes.positions[i], result.attributes.positions[i + 1], result.attributes.positions[i + 2]));
	}

	for (const auto& shape : result.shapes)
	{
		for (size_t i = 0; i < shape.mesh.indices.size(); i++)
		{
			indices.push_back(shape.mesh.indices[i].position_index);
		}
	}
}

double Mesh::getIntersection(const Ray& r) const
{
	double minDist = INFINITY;

	int minIndex = 0;

	for (int i = 0; i < indices.size(); i += 3)
	{
		int index1 = indices[i];
		int index2 = indices[i + 1];
		int index3 = indices[i + 2];
		Vector3 edge1 = vertices[index2] - vertices[index1];
		Vector3 edge2 = vertices[index3] - vertices[index1];

		Vector3 p = cross(r.direction, edge2);
		double determinant = dot(edge1, p);
		if (determinant > -0.001 && determinant < 0.001) continue;

		double invDet = 1.0 / determinant;

		Vector3 t = r.origin - vertices[index1];
		double u = dot(t, p) * invDet;
		if (u < 0 || u > 1) continue;

		Vector3 q = cross(t, edge1);
		double v = dot(r.direction, q) * invDet;
		if (v < 0 || u + v > 1) continue;

		double distance = dot(edge2, q) * invDet;

		if (distance < minDist && distance > 0.001)
		{
			minDist = distance;
			minIndex = i;
		}
	}
	Vector3 e1 = vertices[indices[minIndex + 1]] - vertices[indices[minIndex]];
	Vector3 e2 = vertices[indices[minIndex + 2]] - vertices[indices[minIndex]];
	currentNormal = cross(e1, e2).normalize();

	return minDist;
}

Vector3 Mesh::getNormal(const Vector3& hit) const
{
	return currentNormal;
}