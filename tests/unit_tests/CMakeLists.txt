project(map_app_search_service_unit_tests)


###### Project set-up ######
cmake_minimum_required(VERSION 3.25)

include(CodeCoverage)
append_coverage_compiler_flags()

###### Project specific ######

file(GLOB_RECURSE SRC src/*.cpp)
set(TESTED_SRC $<TARGET_PROPERTY:serviceImpl,SOURCES> )

add_executable(${PROJECT_NAME} ${SRC} ${TESTED_SRC})


###### Dependencies integration ######

target_include_directories(${PROJECT_NAME}
    PRIVATE ${GTest_INCLUDE_DIR}
    PRIVATE inc
    PRIVATE $<TARGET_PROPERTY:serviceImpl,INTERFACE_INCLUDE_DIRECTORIES>
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE ${GTest_LIBRARIES}
)

set(COVERAGE_EXCLUDES
    "/usr/include/*"
    "${GTest_INCLUDE_DIR}/*"
    "tests/*"
    "*/inc/*"
)

setup_target_for_coverage_lcov(
    NAME coverage
    EXECUTABLE ${PROJECT_NAME}
    BASE_DIRECTORY ${CMAKE_SOURCE_DIR}
)

install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin
)
