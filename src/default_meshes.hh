#ifndef GLFR_DEFAULT_MESHES_HH
#define GLFR_DEFAULT_MESHES_HH

#include <GL/glew.h>

namespace glfr
{
	namespace Quad
	{
		const GLfloat vertices[] = 
		{
			0.5f,  0.5f, 0.0f,
			0.5f, -0.5f, 0.0f,
			-0.5f, -0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};

		const GLfloat UVs[] =
		{
			1.0f, 1.0f,
			1.0f, 0.0f,
			0.0f, 0.0f,
			0.0f, 1.0f
		};

		const GLfloat normals[] =
		{
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f,
			0.0f, 0.0f, 1.0f
		};

		const GLuint triangles[] = 
		{
			0, 1, 3,
			1, 2, 3
		};
	}

	namespace Cube
	{
		const GLfloat vertices[] = 
		{
			// Front face
			-0.5f, -0.5f,  0.5f, // 0
			0.5f, -0.5f,  0.5f, // 1
			0.5f,  0.5f,  0.5f, // 2
			-0.5f,  0.5f,  0.5f, // 3

			// Back face
			0.5f, -0.5f, -0.5f, // 4
			-0.5f, -0.5f, -0.5f, // 5
			-0.5f,  0.5f, -0.5f, // 6
			0.5f,  0.5f, -0.5f, // 7

			// Left face
			-0.5f, -0.5f, -0.5f, // 8
			-0.5f, -0.5f,  0.5f, // 9
			-0.5f,  0.5f,  0.5f, //10
			-0.5f,  0.5f, -0.5f, //11

			// Right face
			0.5f, -0.5f,  0.5f, //12
			0.5f, -0.5f, -0.5f, //13
			0.5f,  0.5f, -0.5f, //14
			0.5f,  0.5f,  0.5f, //15

			// Top face
			-0.5f,  0.5f,  0.5f, //16
			0.5f,  0.5f,  0.5f, //17
			0.5f,  0.5f, -0.5f, //18
			-0.5f,  0.5f, -0.5f, //19

			// Bottom face
			-0.5f, -0.5f, -0.5f, //20
			0.5f, -0.5f, -0.5f, //21
			0.5f, -0.5f,  0.5f, //22
			-0.5f, -0.5f,  0.5f  //23
		};

		const GLfloat UVs[] = 
		{
			// Front
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			// Back
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			// Left
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			// Right
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			// Top
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f,

			// Bottom
			0.0f, 0.0f,
			1.0f, 0.0f,
			1.0f, 1.0f,
			0.0f, 1.0f
		};

		const GLfloat normals[] = {
			// Front face (0, 0, 1)
			0.0f,  0.0f,  1.0f,
			0.0f,  0.0f,  1.0f,
			0.0f,  0.0f,  1.0f,
			0.0f,  0.0f,  1.0f,

			// Back face (0, 0, -1)
			0.0f,  0.0f, -1.0f,
			0.0f,  0.0f, -1.0f,
			0.0f,  0.0f, -1.0f,
			0.0f,  0.0f, -1.0f,

			// Left face (-1, 0, 0)
			-1.0f,  0.0f,  0.0f,
			-1.0f,  0.0f,  0.0f,
			-1.0f,  0.0f,  0.0f,
			-1.0f,  0.0f,  0.0f,

			// Right face (1, 0, 0)
			1.0f,  0.0f,  0.0f,
			1.0f,  0.0f,  0.0f,
			1.0f,  0.0f,  0.0f,
			1.0f,  0.0f,  0.0f,

			// Top face (0, 1, 0)
			0.0f,  1.0f,  0.0f,
			0.0f,  1.0f,  0.0f,
			0.0f,  1.0f,  0.0f,
			0.0f,  1.0f,  0.0f,

			// Bottom face (0, -1, 0)
			0.0f, -1.0f,  0.0f,
			0.0f, -1.0f,  0.0f,
			0.0f, -1.0f,  0.0f,
			0.0f, -1.0f,  0.0f
		};

		const GLuint triangles[] = 
		{
			// Front face
			0, 1, 2,
			2, 3, 0,

			// Back face
			4, 5, 6,
			6, 7, 4,

			// Left face
			8, 9,10,
			10,11, 8,

			// Right face
			12,13,14,
			14,15,12,

			// Top face
			16,17,18,
			18,19,16,

			// Bottom face
			20,21,22,
			22,23,20
		};
	}
}

#endif
