cmake_minimum_required(VERSION 3.22)

project(Snake VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics)

add_subdirectory(3rdparty)
add_subdirectory(src)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/sansation.ttf" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


