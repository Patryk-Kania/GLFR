cmake_minimum_required(VERSION 3.10)

project(GLFR	VERSION 0.1.3
		DESCRIPTION "OpenGL Forward Renderer"
		LANGUAGES CXX
	)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/lib")

configure_file(src/config.hh.in include/GLFR/config.hh)

find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)
find_package(glm REQUIRED)

add_library(glfr STATIC src/renderer.cc src/shader.cc src/mesh.cc)
target_include_directories(glfr PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include" "${CMAKE_CURRENT_BINARY_DIR}/include"
				PRIVATE "${CMAKE_CURRENT_BINARY_DIR}/src")

add_executable(test src/main.cc)
target_link_libraries(test OpenGL::GL glfw GLEW::glew glm::glm glfr)
