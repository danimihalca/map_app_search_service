# Map App Search Service

## Description

Basic search service implemented as a reverse proxy on top of Mapbox's `Geocoding places` endpoint.

## Technologies
* C++17
* CMake
* Drogon Framework
* Google Test and Google Mock
* Conan

Altenartive minimal implementation using ASP.NET Core on **dotnet_implementation** branch.


## Architecture

### Class Diagram

![./class_diagram.plantuml](https://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/danimihalca/map_app_search_service/main/class_diagram.plantuml)

## Sequence Diagrams

### Search Places API
![./search_places_sequence_diagram.plantuml](https://www.plantuml.com/plantuml/proxy?cache=no&src=https://raw.githubusercontent.com/danimihalca/map_app_search_service/main/search_places_sequence_diagram.plantuml)


## Build

### Local build
* Prerequisites:
    - CMake 3.25
    - Conan 2.0.14

* Initialize all submodules:

```
git submodule update --init --recursive
```

* Build dependencies via `conan`:
```
cd map_app_search_service_base
conan install conanfile.txt --output-folder=<CONAN_BUILD_FOLDER> --build=missing -s build_type=<Debug/Release> --deployer=full_deploy
```
* Configure CMake project:
```
cd <BUILD_FOLDER>
cmake -DCMAKE_BUILD_TYPE=<Debug/Release> -DCMAKE_INSTALL_PREFIX=out -DCONAN_DEPS_PATH=<CONAN_BUILD_FOLDER> <SRC_PATH>
```
* Build project:
```
make install
* Run service:
cd <BUILD_FOLDER>/out/bin && ./map_app_search_service_bin <MAPBOX_TOKEN>

```
* Optional: Run unit tests (only in Debug):
```
cd <BUILD_FOLDER>/out/bin && ./map_app_search_service_unit_tests
```
* Optional: Run coverage (only in Debug):
```
make coverage
```
Result path: `<BUILD_FOLDER>/tests/unit_tests/coverage/index.html`

### Docker build
* Build base image with environment and dependencies: 
```
cd map_app_search_service_base
docker build --target=map-app-search-service-dep-build \
    `./docker_build/source-build-args.sh docker_build/args/release.args` \
    -t <SEARCH_SERVICE_BASE_ENV_IMG> .
```
* Build Docker image:
```
docker build --build-arg="BASE_ENV=<SEARCH_SERVICE_BASE_ENV_IMG>" \
    --target runner -t <SEARCH_SERVICE_IMG> .
```
* Run Docker container:
```
docker run -p 12345:12345 -e MAPBOX_TOKEN=<MAPBOX_TOKEN> -dit <SEARCH_SERVICE_IMG>
```
