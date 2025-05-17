#include <cstdio>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "GLFR/config.hh"
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

	while(!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		renderer.ClearColor(53);
		renderer.ClearDepth();

		glfwSwapBuffers(window);
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}
