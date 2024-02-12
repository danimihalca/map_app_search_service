# Map App Search Service

## Description

Basic search service implemented as a reverse proxy on top of Mapbox's `Geocoding places` endpoint.

## Technologies
* .NET 8.0

## Build

### Local build
* Prerequisites:
    - [.NET 8.0](https://learn.microsoft.com/en-us/dotnet/core/install/)

* Build project:
```
dotnet build
```
* Run service:
```
dotnet run -- <MAPBOX_TOKEN>
```

### Docker build
* Build Docker image:
```
docker build --target runner -t <SEARCH_SERVICE_IMG> .
```
* Run Docker container:
```
docker run -p 12345:12345 -e MAPBOX_TOKEN=<MAPBOX_TOKEN> -dit <SEARCH_SERVICE_IMG>
```