cmake_minimum_required(VERSION 3.30)
project(3DRenderer)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.1
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(3DRenderer src/main.cpp
        src/types.h
        src/Object.cpp
        src/Object.h
        src/includes.h
        src/Point.cpp
        src/Point.h
)

target_link_libraries(3DRenderer PRIVATE SFML::Graphics SFML::Window SFML::Audio)