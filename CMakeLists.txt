cmake_minimum_required(VERSION 3.21)
project(ray-tracer)

set(CMAKE_CXX_STANDARD 20)

include_directories(geometry)
include_directories(render)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)

find_package(OpenMP)
if (OpenMP_CXX_FOUND)
    if(COMPILER_SUPPORTS_MARCH_NATIVE)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native -mfpmath=sse -O3 ${OpenMP_CXX_FLAGS}")
    else()
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS} -O3")
    endif()
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
else()
    message(WARNING "OpenMP not found!")
endif()

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)
include_directories(ray-tracer ${SDL2_INCLUDE_DIRS})

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
        render/renderable.cpp
        render/renderable.h
        render/colored_sphere.cpp
        render/colored_sphere.h
        render/scene.cpp
        render/scene.h
        render/light.cpp
        render/light.h
        geometry/plane.cpp
        geometry/plane.h
        render/colored_plane.cpp
        render/colored_plane.h)

if(TARGET SDL2::SDL2main)
    target_link_libraries(ray-tracer PRIVATE SDL2::SDL2main)
endif()

target_link_libraries(ray-tracer PRIVATE SDL2::SDL2)