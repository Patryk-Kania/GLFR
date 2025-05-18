#include <cstdio>
#include <cstdlib>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/mat4x4.hpp>
#include <glm/vec3.hpp>
#include <glm/trigonometric.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "GLFR/config.hh"
#include "GLFR/mesh.hh"
#include "GLFR/renderer.hh"
#include "GLFR/texture2d.hh"

constexpr int g_kWindowWidth = 1200;
constexpr int g_kWindowHeight = 800;

int main()
{
	glfwInit();

	glfwWindowHint( GLFW_RESIZABLE, GLFW_FALSE );
	GLFWwindow *window = glfwCreateWindow( g_kWindowWidth, g_kWindowHeight, "GLFR v" GLFR_VERSION_STRING " test", nullptr, nullptr );

	glfwMakeContextCurrent( window );
	glewInit();

	glfr::Renderer renderer;
	renderer.Init( g_kWindowWidth, g_kWindowHeight );

	glfr::Mesh mesh = glfr::Mesh::NewCube();
	
	float lastTime = 0.0f;
	float deltaTime = 0.0f;

	float rotationY = 0;

	while( !glfwWindowShouldClose( window ) )
	{
		float currentTime = glfwGetTime();
		deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		glfwPollEvents();

		renderer.ClearColor( 53 );
		renderer.ClearDepth();

		rotationY += glm::radians( 45.f ) * deltaTime;

		glm::mat4 meshTransform = glm::mat4 { 1.0f };
		meshTransform = glm::translate( meshTransform, glm::vec3 { 0.0f, 0.0f, -2.0f } );
		meshTransform = glm::rotate( meshTransform, rotationY, glm::vec3 { 0.f, 1.f, 0.f } );

		renderer.DrawMesh( mesh, meshTransform );

		glfwSwapBuffers( window );
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}
