#include "endpoint/SearchEndpoint.h"
#include <drogon/HttpResponse.h>

#include "service/SearchService.h"

namespace endpoint
{

SearchEndpoint::SearchEndpoint(std::unique_ptr<service::SearchService>&& service)
    : m_searchService(std::move(service))
{
}

void SearchEndpoint::places(const drogon::HttpRequestPtr&                         request,
                            std::function<void(const drogon::HttpResponsePtr&)>&& callback,
                            const std::string&                                    queryText)
{
    m_searchService->searchPlaces(queryText, [callback](const std::string& response) {
        auto resp = drogon::HttpResponse::newHttpResponse();
        resp->setBody(response);
        resp->addHeader("Access-Control-Allow-Origin", "*");
        callback(resp);
    });
}

}  // namespace endpoint