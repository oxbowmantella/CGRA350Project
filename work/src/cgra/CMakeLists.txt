
SET(sources
  matrix.hpp
  mesh.hpp
  mesh.cpp
  shader.hpp
  shader.cpp
  wavefront.hpp
  wavefront.cpp
  imgui_impl_glfw_gl3.h
  imgui_impl_glfw_gl3.cpp stb_image.cpp stb_image.h)

target_relative_sources(${CGRA_PROJECT} ${sources})
