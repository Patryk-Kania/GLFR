# GLFR - OpenGL Forward Renderer
> This project is built in stages. Each feature is added incrementally and documented in commits. Expect refactors and restructures as I learn better design and OpenGL practices.

**GLFR** is a learning project focused on building a simple, modern forward renderer using OpenGL. It’s intended to help me understand how to structure and implement a rendering pipeline from scratch.

## Goals
- Render basic 3D meshes
- Render built-in primitives (e.g., cube, sphere, quad)
- Material system
- Support for multiple light sources
- Simple shadow rendering
- Single controllable camera

## Development Environment

This project is written in C++11 and built using CMake. It uses:
- OpenGL as the graphics API
- GLFW for window creation and input handling
- GLEW as the OpenGL extension loader
- GLM for math
  
The project is designed to build and run on both **Linux** and **Windows**.

> macOS is explicitly unsupported due to OpenGL deprecation and personal preference.
