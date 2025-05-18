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

## Progress
### GLFR v0.1.0
- Mesh class to easily initialize meshes
- Renderer class to setup and control camera and draw meshes (I guess thats two goals already?)
- GLFR supports single camera (And thats one more goal)
- There is currently one built-in shader that draws evertything in baby blue (it looks nice)
![image](https://github.com/user-attachments/assets/d69cf779-8ddf-43ee-9317-0fa5bfb9f145)

### GLFR v0.2.0
...
I might’ve messed up versioning a bit, so I’m skipping v0.2.0.

### GLFR v0.3.0
- Built-in meshes: quad and cube (I'll check it as a completed goal)
- Materials - can set base color and albedo texture (Partialy finished another goal)
- Texture mapping - can create textures from pixel array
![image](https://github.com/user-attachments/assets/04d65cb2-1c13-4e74-b134-5bbe4e28657d)

## Whats next:
**Lights**
- Default always active directional light
- Control directional light properties
- Create new lights: point and spot
- Materials with properties to control how light affects the object
- Support Multiple light sources
