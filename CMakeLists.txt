cmake_minimum_required(VERSION 3.22)

project(Snake LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML COMPONENTS graphics window system REQUIRED)

add_executable(Snake WIN32
    main.cpp
    bodyrectangle.cpp
    bodyrectangle.h
    foodrectangle.h
    globaldefs.h
    snakebody.cpp
    snakebody.h
)

target_link_libraries(Snake sfml-graphics sfml-window sfml-system)
