project(map_app_search_service_unit_tests)


###### Project set-up ######
cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 17)


###### Project specific ######

file(GLOB_RECURSE SRC src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC})


###### Dependencies integration ######

target_include_directories(${PROJECT_NAME}
    PUBLIC ${GTest_INCLUDE_DIR}
    PRIVATE inc
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC ${GTest_LIBRARIES}
    PUBLIC serviceImpl
)
