project(map_app_search_service_bin)


###### Project set-up ######
cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 17)


###### Project specific ######

file(GLOB SRC src/*.cpp)

add_executable(${PROJECT_NAME} ${SRC})


###### Dependencies integration ######

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin
)
