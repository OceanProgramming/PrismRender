#pragma once

#include "Image.hpp"
#include "Scene.hpp"
#include "Camera.hpp"

#include "glm/glm.hpp"

namespace PrismRender
{
	class Renderer
	{
	public:
		Renderer() : output(1280, 720, 3) {};

		void render(Scene* scene, Camera* camera);
		glm::vec3 getSkyColor(const Image* world, const glm::vec3& dir);
		glm::vec3 Renderer::renderRay(const Ray& r, int bounces);
		Image output;
	private:
		Scene* activeScene = nullptr;
		Camera* activeCamera = nullptr;
	};
}