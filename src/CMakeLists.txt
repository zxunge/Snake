add_executable(Snake WIN32
    main.cpp
    globaldefs.h
)

add_subdirectory(core)
add_subdirectory(ui)

target_link_libraries(Snake PRIVATE SFML::Graphics gamemenu)
target_include_directories(Snake PRIVATE ${CMAKE_CURRENT_LIST_DIR})
