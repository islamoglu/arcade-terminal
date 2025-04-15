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
#TODO file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/*.cpp")
add_executable(arcade Arcade.cpp Config.cpp DefaultConfig.cpp FileLogger.cpp LocalUser.cpp Logger.cpp Screen.cpp TerminalScreen.cpp User.cpp)

# Make sure arcade waits for ncurses to finish building
add_dependencies(arcade ncurses_project)

# Link with ncurses
target_link_libraries(arcade PRIVATE ncursesw)
target_link_libraries(arcade PRIVATE ncurses++w)
target_link_libraries(arcade PRIVATE tinfow)
target_link_libraries(arcade PRIVATE panelw)
target_link_libraries(arcade PRIVATE menuw)
target_link_libraries(arcade PRIVATE formw)