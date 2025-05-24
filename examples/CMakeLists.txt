add_executable(demo demo/demo.cc)
target_link_libraries(demo OpenGL::GL glfw GLEW::glew glm::glm glfr)
