project(map_app_search_service)

cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 11)

file(GLOB SRC src/*.cpp)

add_executable(${CMAKE_PROJECT_NAME} ${SRC})