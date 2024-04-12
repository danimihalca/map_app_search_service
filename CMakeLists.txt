project(map_app_search_service)

###### Project set-up ######
cmake_minimum_required(VERSION 3.22)

set(CMAKE_CXX_STANDARD 17)

###### Dependencies ######

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

add_subdirectory(modules)

add_subdirectory(app)
