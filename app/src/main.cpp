#include <iostream>
#include <string>

#include "httpClientImpl/HttpClientImpl.h"
#include "serviceImpl/SearchServiceProxyImpl.h"
#include "serviceImpl/MapBoxPlacesPathBuilder.h"

int main(int argc, char** argv)
{
    auto httpClient = std::make_unique<httpClientImpl::HttpClientImpl>("https://api.mapbox.com");

    std::string accessToken = "";
    auto        pathBuilder = std::make_unique<serviceImpl::MapBoxPlacesPathBuilder>(accessToken);

    auto searchService =
        std::make_unique<serviceImpl::SearchServiceProxyImpl>(std::move(httpClient), std::move(pathBuilder));


    std::cout << "Starting service..." << std::endl;

    searchService->searchPlaces("kfc", "", [](const std::string&){});

    std::cout << "Ending service..." << std::endl;

    return 0;
}