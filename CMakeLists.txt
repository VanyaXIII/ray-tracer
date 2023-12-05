cmake_minimum_required(VERSION 3.26)
project(ray-tracer)

set(CMAKE_CXX_STANDARD 20)

include_directories(geometry)
include_directories(render)

add_executable(ray-tracer main.cpp
        geometry/vector3.h
        geometry/vector3.cpp
        main.cpp
        render/color.cpp
        render/color.h
        render/pixmap.cpp
        render/pixmap.h
        geometry/ray.cpp
        geometry/ray.h
        geometry/compare.h
        geometry/sphere.cpp
        geometry/sphere.h
        geometry/intersections.cpp
        geometry/intersections.h
        render/camera.cpp
        render/camera.h
        geometry/utils.h
        geometry/utils.cpp
        render/colorable.cpp
        render/colorable.h
        render/colored_sphere.cpp
        render/colored_sphere.h)
