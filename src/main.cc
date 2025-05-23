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
#include "GLFR/color.hh"
#include "GLFR/light.hh"

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

	glfr::Light sunLight;
	sunLight.type = glfr::Light::DIRECTIONAL_LIGHT;
	sunLight.direction = glm::vec3( -1.0f, -1.0f, -1.0f );
	sunLight.intensity = 0.5f;

	glfr::Light l1;
	l1.type = glfr::Light::POINT_LIGHT;
	l1.position = glm::vec3{ -2.0f, -0.5f, -4.0f };
	l1.color = glfr::Color::Magenta(); 
	l1.range = 4.0f;

	glfr::Light l2;
	l2.type = glfr::Light::SPOT_LIGHT;
	l2.position = glm::vec3{ 2.0f, -0.9f, -4.0f };
	l2.direction = glm::vec3{ -1.0f, 0.0f, 0.0f };
	l2.color = glfr::Color::White();
	l2.intensity = 0.8f;
	l2.spotAngle = 30.0f;
	l2.range = 4.0f;

	renderer.AddLight( sunLight );
	renderer.AddLight( l1 );
	renderer.AddLight( l2 );

	glfr::Mesh mesh = glfr::Mesh::NewCube();
	glfr::Mesh floor = glfr::Mesh::NewQuad();
	glfr::Mesh lightSource = glfr::Mesh::NewCube();

	mesh.material.ambientColor = glfr::Color::Cyan();
	mesh.material.diffuseColor = glfr::Color::Cyan();
	mesh.material.specularColor = glfr::Color::Cyan();

	lightSource.material.isAffectedByLight = false;
	lightSource.material.diffuseColor = glfr::Color::Magenta();
	
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
		meshTransform = glm::translate( meshTransform, glm::vec3 { 0.0f, -0.5f, -4.0f } );
		meshTransform = glm::rotate( meshTransform, rotationY, glm::vec3 { 0.f, 1.f, 0.f } );

		glm::mat4 floorTransform = glm::mat4{ 1.0f };
		floorTransform = glm::translate( floorTransform, glm::vec3{ 0.0f, -1.0f, -2.0f } );
		floorTransform = glm::rotate( floorTransform, glm::radians(-90.0f), glm::vec3{ 1.0f, 0.0f, 0.0f } );
		floorTransform = glm::scale( floorTransform, glm::vec3{ 10.0f, 10.0f, 1.0f } );

		glm::mat4 lightSourceTransform = glm::mat4{ 1.0f };
		lightSourceTransform = glm::translate( lightSourceTransform, glm::vec3{ -2.0f, -0.5f, -4.0f } );
		lightSourceTransform = glm::scale( lightSourceTransform, glm::vec3{ 0.2f, 0.2f, 0.2f } );


		renderer.DrawMesh( mesh, meshTransform );
		renderer.DrawMesh( lightSource, lightSourceTransform );
		renderer.DrawMesh( floor, floorTransform );

		glfwSwapBuffers( window );
	}

	glfwTerminate();

	return EXIT_SUCCESS;
}
