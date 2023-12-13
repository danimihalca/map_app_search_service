project(map_app_search_service)

###### Project set-up ######
cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 17)

###### Dependencies ######

if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    set(CMAKE_MAP_IMPORTED_CONFIG_DEBUG RELEASE)
endif()

set(CONAN_DEPS_PATH ${CMAKE_CURRENT_SOURCE_DIR}/conanBuild)
list(PREPEND CMAKE_PREFIX_PATH ${CONAN_DEPS_PATH})

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

find_package(Drogon REQUIRED PATHS ${CONAN_DEPS_PATH})
if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    find_package(GTest REQUIRED PATHS ${CONAN_DEPS_PATH})
endif()

add_subdirectory(modules)
add_subdirectory(app)
if (${CMAKE_BUILD_TYPE} MATCHES "Debug")
    add_subdirectory(tests)
endif()
