cmake_minimum_required(VERSION 3.15)
project(Assi3 C)

set(CMAKE_C_STANDARD 99)

add_executable(Assi3 main.c Vertex.h Face.h Object.h Scene.h)