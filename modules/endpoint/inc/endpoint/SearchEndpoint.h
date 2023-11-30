#ifndef SEARCHENDPOINT_H
#define SEARCHENDPOINT_H

#include <memory>
#include <string>

#include <drogon/drogon.h>

namespace service
{
class SearchService;
}

namespace endpoint
{

class SearchEndpoint : public drogon::HttpController<SearchEndpoint, false>
{
public:
    METHOD_LIST_BEGIN

    ADD_METHOD_TO(SearchEndpoint::places, "/search/places/{queryText}", drogon::Get);  // path is /api/v1/User/{arg1}

    METHOD_LIST_END

public:
    SearchEndpoint(std::unique_ptr<service::SearchService>&& service);

    void places(const drogon::HttpRequestPtr& request, std::function<void(const drogon::HttpResponsePtr&)>&& callback,
                const std::string& queryText);

private:
    std::unique_ptr<service::SearchService> m_searchService;
};

}  // namespace endpoint

#endif  // SEARCHENDPOINT_H