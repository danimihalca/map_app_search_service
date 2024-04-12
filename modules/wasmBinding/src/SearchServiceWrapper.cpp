#include <memory>

#include "httpClientImpl/HttpClientImpl.h"
#include "serviceImpl/SearchServiceProxyImpl.h"
#include "serviceImpl/MapBoxPlacesPathBuilder.h"

#include <emscripten/bind.h>

class SearchServiceWrapper
{
public:
    SearchServiceWrapper(const std::string& accessToken)
    {
        auto httpClient = std::make_unique<httpClientImpl::HttpClientImpl>("https://api.mapbox.com");
        auto pathBuilder = std::make_unique<serviceImpl::MapBoxPlacesPathBuilder>(accessToken);

        m_searchService =
            std::make_unique<serviceImpl::SearchServiceProxyImpl>(std::move(httpClient), std::move(pathBuilder));
    }

    void searchPlaces(const std::string& queryText, const std::string& proximity)
    {
        m_searchService->searchPlaces(queryText, proximity, [](const std::string&){});
    }

private:
    std::unique_ptr<service::SearchService> m_searchService;

};


EMSCRIPTEN_BINDINGS(my_class_example) {
  emscripten::class_<SearchServiceWrapper>("SearchServiceWrapper")
    .constructor<const std::string&>()
    .function("searchPlaces", &SearchServiceWrapper::searchPlaces)
    ;
}