#pragma once

#include "Sphere.hpp"
#include "Material.hpp"
#include "Image.hpp"

#include <vector>

namespace PrismRender
{
	struct Scene
	{
		Scene() : environment("solitude_interior_4k.hdr") {};

		std::vector<Sphere> renderObjects;
		std::vector<Material*> materials;
		Image environment;
	};
}