project(wasmBinding)

###### Project specific ######

file(GLOB SRC src/*.cpp)

add_library(${PROJECT_NAME} ${SRC})

###### Dependencies integration ######

target_include_directories(${PROJECT_NAME}
    PUBLIC inc
)

target_link_libraries(${PROJECT_NAME}
    PUBLIC httpClientImpl
    PUBLIC serviceImpl
    embind
)
