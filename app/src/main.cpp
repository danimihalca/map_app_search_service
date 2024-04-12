#include <iostream>

#include <emscripten.h>

#include "wasmBinding/SearchServiceWrapper.h"

#include <emscripten/bind.h>

EMSCRIPTEN_BINDINGS(my_class_example) {
  emscripten::class_<SearchServiceWrapper>("SearchServiceWrapper")
    .constructor<std::string>()
    .function("searchPlaces", &SearchServiceWrapper::searchPlaces);
}


EMSCRIPTEN_KEEPALIVE
int main(int argc, char** argv)
{
    std::cout << "Starting service..." << std::endl;

    std::cout << "Ending service..." << std::endl;

    return 0;
}