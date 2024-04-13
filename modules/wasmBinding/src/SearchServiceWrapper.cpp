#include "wasmBinding/SearchServiceWrapper.h"

#include "httpClientImpl/HttpClientImpl.h"
#include "serviceImpl/SearchServiceProxyImpl.h"
#include "serviceImpl/MapBoxPlacesPathBuilder.h"

#include <emscripten.h>
#include <iostream>

SearchServiceWrapper::SearchServiceWrapper(std::string accessToken)
{
    auto httpClient = std::make_unique<httpClientImpl::HttpClientImpl>("https://api.mapbox.com");
    auto pathBuilder = std::make_unique<serviceImpl::MapBoxPlacesPathBuilder>(accessToken);

    m_searchService =
        std::make_unique<serviceImpl::SearchServiceProxyImpl>(std::move(httpClient), std::move(pathBuilder));
}

void SearchServiceWrapper::searchPlaces(const std::string& queryText, const std::string& proximity, emscripten::val callback)
{
    m_searchService->searchPlaces(queryText, proximity, [=](const std::string& result){
        callback(result);
    });
}
