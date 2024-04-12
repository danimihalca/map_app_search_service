#ifndef SEARCH_SERVICE_WRAPPER_H
#define SEARCH_SERVICE_WRAPPER_H

#include <memory>

#include "service/SearchService.h"


class SearchServiceWrapper
{
public:
    SearchServiceWrapper(std::string accessToken);
    std::string searchPlaces(const std::string& queryText, const std::string& proximity);

private:
    std::unique_ptr<service::SearchService> m_searchService;
};

#endif // SEARCH_SERVICE_WRAPPER_H