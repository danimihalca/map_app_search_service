project(map_app_search_service)

###### Project set-up ######
cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 17)

###### Dependencies ######

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake-modules)

#TODO: reenable after adapting exporting service to WASM and adapting httpClient to use emscripten fetch  
# add_subdirectory(modules)

add_subdirectory(app)
