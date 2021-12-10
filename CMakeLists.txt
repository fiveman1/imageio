cmake_minimum_required(VERSION 3.10.2)
project(imageiov2)

set(CMAKE_CXX_STANDARD 11)

include_directories(include include/imageio)

file(GLOB source_files CONFIGURE_DEPENDS
        src/*.cpp
        demo/*.cpp
        demo/*.h
        )

add_executable(image_processor ${source_files})
