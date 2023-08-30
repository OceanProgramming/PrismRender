#pragma once

#include "Renderer.hpp"
#include "Scene.hpp"
#include "Camera.hpp"

#define GLFW_INCLUDE_NONE
#include "glfw/glfw3.h"

namespace PrismRender
{
	class Application
	{
	public:
		Application();
		~Application();

		void run();
		void close();
	private:
		GLFWwindow* windowHandle = nullptr;
		int windowWidth, windowHeight;
		bool running = false;

		static void frameBufferSizeCallback(GLFWwindow* window, int width, int height);
		void onResize(int width, int height);

		Renderer renderer;
		Scene scene;
		Camera camera;
	};
}

