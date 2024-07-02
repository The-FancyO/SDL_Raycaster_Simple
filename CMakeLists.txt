cmake_minimum_required(VERSION 3.10)

project(MySDLGame)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SDL2 REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} ${SDL2_LIBRARIES})

set(CMAKE_BUILD_TYPE Release)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)