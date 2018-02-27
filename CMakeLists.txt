cmake_minimum_required(VERSION 3.5.1)
project(grafika)

set(CMAKE_CXX_STANDARD 11)
add_executable(grafika main.c AABB.c AABB.h camera.c camera.h draw.c draw.h model.c model.h)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )


target_link_libraries(grafika ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})
