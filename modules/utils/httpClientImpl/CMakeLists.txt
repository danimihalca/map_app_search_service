project(httpClientImpl)

###### Project specific ######

file(GLOB SRC src/*.cpp)

add_library(${PROJECT_NAME} ${SRC})

###### Dependencies integration ######

target_include_directories(${PROJECT_NAME}
    PUBLIC ${Drogon_INCLUDE_DIR}
    PUBLIC inc
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC ${Drogon_LIBRARIES}
    PUBLIC httpClient
)
