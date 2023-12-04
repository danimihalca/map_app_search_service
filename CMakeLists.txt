project(map_app_search_service)

###### Project set-up ######
cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 17)

###### Dependencies ######

set(CONAN_DEPS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/conanBuild)
list(PREPEND CMAKE_PREFIX_PATH ${CONAN_DEPS_PATH})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

find_package(Drogon REQUIRED PATHS ${CONAN_DEPS_PATH})
find_package(GTest REQUIRED PATHS ${CONAN_DEPS_PATH})

add_subdirectory(modules)
add_subdirectory(app)
add_subdirectory(tests)
