cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 14)

project(trabalho-cg)
add_executable(trabalho-cg src/main.cpp src/etc.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(trabalho-cg  ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )
