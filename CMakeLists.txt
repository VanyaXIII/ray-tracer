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
        geometry/utils/vector3.h
        geometry/utils/vector3.cpp
        main.cpp
        render/scene/color.cpp
        render/scene/color.h
        render/scene/pixmap.cpp
        render/scene/pixmap.h
        geometry/objects/ray.cpp
        geometry/objects/ray.h
        geometry/utils/compare.h
        geometry/objects/sphere.cpp
        geometry/objects/sphere.h
        geometry/utils/intersections.cpp
        geometry/utils/intersections.h
        render/scene/camera.cpp
        render/scene/camera.h
        geometry/utils/utils.h
        geometry/utils/utils.cpp
        render/objects/renderable.cpp
        render/objects/renderable.h
        render/objects/colored_sphere.cpp
        render/objects/colored_sphere.h
        render/scene/scene.cpp
        render/scene/scene.h
        render/objects/light.cpp
        render/objects/light.h
        geometry/objects/plane.cpp
        geometry/objects/plane.h
        render/objects/colored_plane.cpp
        render/objects/colored_plane.h
        render/scene/renderer.cpp
        render/scene/renderer.h)

if(TARGET SDL2::SDL2main)
    target_link_libraries(ray-tracer PRIVATE SDL2::SDL2main)
endif()

target_link_libraries(ray-tracer PRIVATE SDL2::SDL2)