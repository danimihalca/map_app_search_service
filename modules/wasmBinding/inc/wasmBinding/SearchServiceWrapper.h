#ifndef SEARCH_SERVICE_WRAPPER_H
#define SEARCH_SERVICE_WRAPPER_H

#include <memory>

#include "service/SearchService.h"

#include <emscripten/val.h>

class SearchServiceWrapper
{
public:
    SearchServiceWrapper(std::string accessToken);
    void searchPlaces(const std::string& queryText, const std::string& proximity, emscripten::val callback);

private:
    std::unique_ptr<service::SearchService> m_searchService;
};

#endif // SEARCH_SERVICE_WRAPPER_H