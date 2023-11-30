project(map_app_search_service_bin)


###### Project set-up ######
cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 17)


###### Project specific ######

file(GLOB SRC src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC})


###### Dependencies integration ######

target_include_directories(${PROJECT_NAME}
    PUBLIC ${Drogon_INCLUDE_DIR}
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC ${Drogon_LIBRARIES}
    PUBLIC endpoint
    PUBLIC httpClientImpl
    PUBLIC serviceImpl
)
