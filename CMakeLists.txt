cmake_minimum_required(VERSION 3.20)
project(Spring_Lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML COMPONENTS Graphics Window System CONFIG REQUIRED)

add_executable(Spring_Lab main.cpp)

target_link_libraries(Spring_Lab PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)