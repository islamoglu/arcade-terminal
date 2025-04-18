cmake_minimum_required(VERSION 3.14)
project(arcade)

include(ExternalProject)

# External project: build ncurses using its Autotools system
ExternalProject_Add(
    ncurses_project
    SOURCE_DIR ${CMAKE_SOURCE_DIR}/external/ncurses
    CONFIGURE_COMMAND ${CMAKE_SOURCE_DIR}/external/ncurses/configure --prefix=${CMAKE_BINARY_DIR}/ncurses-install --with-termlib
    BUILD_COMMAND make
    INSTALL_COMMAND make install
)

# Tell CMake where to find the built libraries/headers
include_directories(${CMAKE_BINARY_DIR}/ncurses-install/include/ncursesw)
include_directories(${CMAKE_BINARY_DIR}/ncurses-install/include/)
link_directories(${CMAKE_BINARY_DIR}/ncurses-install/lib)

# Your arcade executable
file(GLOB_RECURSE CONFIG "config/*.cpp")
file(GLOB_RECURSE GAME "game/*.cpp")
file(GLOB_RECURSE LOGGING "logging/*.cpp")
file(GLOB_RECURSE SCREEN "screen/*.cpp")
file(GLOB_RECURSE USER "user/*.cpp")

include_directories(${CMAKE_SOURCE_DIR}/config)
include_directories(${CMAKE_SOURCE_DIR}/game)
include_directories(${CMAKE_SOURCE_DIR}/logging)
include_directories(${CMAKE_SOURCE_DIR}/screen)
include_directories(${CMAKE_SOURCE_DIR}/user)

add_executable(arcade Arcade.cpp ${CONFIG} ${GAME} ${LOGGING} ${SCREEN} ${USER})

# Make sure arcade waits for ncurses to finish building
add_dependencies(arcade ncurses_project)

# Link with ncurses
target_link_libraries(arcade PRIVATE
    ncurses++w
    ncursesw
    panelw
    menuw
    formw
    tinfow
)