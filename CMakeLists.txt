cmake_minimum_required(VERSION 3.22)

project(Snake VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics)

add_executable(Snake WIN32
    main.cpp
    bodyrectangle.cpp
    bodyrectangle.h
    foodrectangle.h
    globaldefs.h
    snakebody.cpp
    snakebody.h
    keyhandler.h
)

target_link_libraries(Snake PRIVATE SFML::Graphics)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/Zxunge Hand-Regular.ttf" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})


