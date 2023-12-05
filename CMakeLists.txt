cmake_minimum_required(VERSION 3.26)
project(ray-tracer)

set(CMAKE_CXX_STANDARD 20)

add_executable(ray-tracer main.cpp
        geometry/vector3.h
        geometry/vector3.cpp
        main.cpp
        render/color.cpp
        render/color.h
        render/pixmap.cpp
        render/pixmap.h
        geometry/ray.cpp
        geometry/ray.h)
