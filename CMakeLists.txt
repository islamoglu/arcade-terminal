cmake_minimum_required(VERSION 3.0)
project(arcade-terminal VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
add_subdirectory(external/spdlog)
include_directories(external/spdlog/include)

add_subdirectory(external/json)
include_directories(external/json/include)

add_executable(arcade-terminal src/main.cpp src/arcade.cpp src/config.cpp src/log.cpp)
target_include_directories(arcade-terminal PRIVATE inc/)

target_link_libraries(arcade-terminal PRIVATE spdlog::spdlog)
target_link_libraries(arcade-terminal PRIVATE nlohmann_json)

