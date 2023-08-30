#include "Application.hpp"

#include "ShaderProgram.hpp"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include "glad/glad.h"
#include "glm/glm.hpp"

#include <iostream>

namespace PrismRender
{
	Application::Application()
	{
		windowWidth = 1280;
		windowHeight = 720;

		if (!glfwInit())
		{
			std::cerr << "[Error] Failed to initialize glfw" << std::endl;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		windowHandle = glfwCreateWindow(windowWidth, windowHeight, "Prism Render", nullptr, nullptr);
		if (windowHandle == nullptr)
		{
			std::cerr << "[Error] Failed to create glfw window" << std::endl;
			glfwTerminate();
		}
		glfwMakeContextCurrent(windowHandle);
		glfwSetWindowUserPointer(windowHandle, this);
		glfwSetWindowSizeCallback(windowHandle, frameBufferSizeCallback);
		glfwSwapInterval(1);

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		{
			std::cerr << "[Error] Failed to initialize glad" << std::endl;
		}
		glViewport(0, 0, windowWidth, windowHeight);

		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		ImGui::StyleColorsDark();

		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		ImGui_ImplGlfw_InitForOpenGL(windowHandle, true);
		ImGui_ImplOpenGL3_Init();

		scene.environment = Image("solitude_interior_4k.hdr");

		float aspectRatio = (float)windowWidth / windowHeight;
		Camera cam(aspectRatio, 1.5f);
		cam.position = glm::vec3(0, 5, 15);
		cam.lookAt(glm::vec3(0, 0, 0));
		cam.resizeViewport(windowWidth, windowHeight);

		Lambertian* diffuseRed = new Lambertian(glm::vec3(1, 0.25, 0.25));
		scene.materials.push_back(diffuseRed);

		Lambertian* diffuseWhite = new Lambertian(glm::vec3(1, 1, 1));
		scene.materials.push_back(diffuseWhite);

		Sphere sphere1(glm::vec3(0, 0, 0), 2.0f);
		sphere1.materialIndex = 1;
		scene.renderObjects.push_back(sphere1);

		camera = cam;
	}

	Application::~Application()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
		glfwDestroyWindow(windowHandle);
		glfwTerminate();
		running = false;
	}

	void Application::run()
	{
		running = true;

		Shader* vertexShader = new Shader("src/Shaders/shader.vert", GL_VERTEX_SHADER);
		Shader* fragmentShader = new Shader("src/Shaders/shader.frag", GL_FRAGMENT_SHADER);
		std::vector<Shader> shaders { *vertexShader, *fragmentShader };
		ShaderProgram shaderProgram(shaders);
		delete vertexShader;
		delete fragmentShader;

		float vertices[] =
		{
			// Vertex positions		// Texture coordinates
			 1.0f,  1.0f, 0.0f,		1.0f, 0.0f,
			 1.0f, -1.0f, 0.0f,		1.0f, 1.0f,
			-1.0f, -1.0f, 0.0f,		0.0f, 1.0f,
			-1.0f,  1.0f, 0.0f,		0.0f, 0.0f 
		};
		unsigned int indices[] =
		{
			0, 1, 3,
			1, 2, 3
		};

		unsigned int VAO, VBO, EBO;
		glGenVertexArrays(1, &VAO);
		glBindVertexArray(VAO);

		glGenBuffers(1, &VBO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glGenBuffers(1, &EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		unsigned int texture;
		glGenTextures(1, &texture);
		glBindTexture(GL_TEXTURE_2D, texture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		renderer.render(&scene, &camera);
		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, renderer.output.width, renderer.output.height, 0, GL_RGB, GL_UNSIGNED_BYTE, renderer.output.buffer);
		//glGenerateMipmap(GL_TEXTURE_2D);

		shaderProgram.bind();
		glUniform1i(glGetUniformLocation(shaderProgram.programID, "renderTexture"), 0);

		ImGuiIO& io = ImGui::GetIO();

		while (!glfwWindowShouldClose(windowHandle) && running)
		{
			glfwPollEvents();

			ImGui_ImplOpenGL3_NewFrame();
			ImGui_ImplGlfw_NewFrame();
			ImGui::NewFrame();

			ImGui::ShowDemoWindow();

			glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture);
			camera.position += glm::vec3(0, 0, -0.51);
			camera.lookAt(glm::vec3(0, 0, 0));
			renderer.render(&scene, &camera);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, renderer.output.width, renderer.output.height, 0, GL_RGB, GL_UNSIGNED_BYTE, renderer.output.buffer);
			//glGenerateMipmap(GL_TEXTURE_2D);

			shaderProgram.bind();
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

			ImGui::Render();
			ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

			if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
			{
				GLFWwindow* backup_current_context = glfwGetCurrentContext();
				ImGui::UpdatePlatformWindows();
				ImGui::RenderPlatformWindowsDefault();
				glfwMakeContextCurrent(backup_current_context);
			}

			glfwSwapBuffers(windowHandle);
		}
	}

	void Application::close()
	{
		running = false;
	}

	void Application::frameBufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		Application* app = static_cast<Application*>(glfwGetWindowUserPointer(window));
		if (app)
			app->onResize(width, height);
		else
			std::cerr << "[Error] No valid Application instance" << std::endl;
	}

	void Application::onResize(int width, int height)
	{
		windowWidth = width;
		windowHeight = height;
		glViewport(0, 0, width, height);
		camera.resizeViewport(width, height);
		renderer.output.resizeBuffer(width, height);
	}
}