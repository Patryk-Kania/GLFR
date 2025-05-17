#include <cstdio>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/trigonometric.hpp>

#include "GLFR/config.hh"
#include "GLFR/mesh.hh"
#include "GLFR/renderer.hh"

constexpr int g_kWindowWidth = 1200;
constexpr int g_kWindowHeight = 800;

int main()
{
	glfwInit();

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
	GLFWwindow *window = glfwCreateWindow(g_kWindowWidth, g_kWindowHeight, "GLFR v" GLFR_VERSION_STRING " test", nullptr, nullptr);

	glfwMakeContextCurrent(window);
	glewInit();

	glfr::Renderer renderer;
	renderer.Init(g_kWindowWidth, g_kWindowHeight);

	float vertices[] = {
		0.5f,  0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f,  0.5f, 0.0f   // top left 
	};

	unsigned int triangles[] = {  // note that we start from 0!
		0, 1, 3,  // first Triangle
		1, 2, 3   // second Triangle
	};

	glfr::Mesh mesh(4, vertices, 2, triangles);

	renderer.SetCameraPosition(glm::vec3 {0.0f, 0.0f, -2.0f});

	float lastTime = 0.0f;
	float deltaTime = 0.0f;

	while(!glfwWindowShouldClose(window))
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		glfwPollEvents();

		renderer.ClearColor(53);
		renderer.ClearDepth();

		renderer.DrawMesh(mesh, glm::mat4 {1.0});
		renderer.RotateCamera(glm::vec3 {0.0f, deltaTime * 45, 0.0f});

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}
