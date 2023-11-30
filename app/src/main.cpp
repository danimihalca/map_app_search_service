#include <memory>

#include "httpClientImpl/HttpClientImpl.h"
#include "serviceImpl/SearchServiceProxyImpl.h"
#include "serviceImpl/MapBoxPlacesPathBuilder.h"

#include "endpoint/SearchEndpoint.h"

int main(int argc, char** argv)
{
    drogon::app().setLogLevel(trantor::Logger::LogLevel::kTrace);
    drogon::app().addListener("0.0.0.0", 12345);

    auto httpClient = std::make_unique<httpClientImpl::HttpClientImpl>("https://api.mapbox.com");

    std::string accessToken(argv[1]);
    auto        pathBuilder = std::make_unique<serviceImpl::MapBoxPlacesPathBuilder>(accessToken);

    auto searchService =
        std::make_unique<serviceImpl::SearchServiceProxyImpl>(std::move(httpClient), std::move(pathBuilder));

    auto searchEndpoint = std::make_shared<endpoint::SearchEndpoint>(std::move(searchService));

    searchEndpoint->initPathRouting();
    drogon::app().registerController(searchEndpoint);

    drogon::app().run();

    return 0;
}