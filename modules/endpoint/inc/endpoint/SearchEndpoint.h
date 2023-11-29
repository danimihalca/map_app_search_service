#ifndef SEARCHENDPOINT_H
#define SEARCHENDPOINT_H

#include <string>

#include <drogon/drogon.h>

namespace endpoint
{

class SearchEndpoint : public drogon::HttpController<SearchEndpoint, false>
{
public:
    METHOD_LIST_BEGIN

    ADD_METHOD_TO(SearchEndpoint::places, "/search/places/{queryText}", drogon::Get);  // path is /api/v1/User/{arg1}

    METHOD_LIST_END

    void places(const drogon::HttpRequestPtr& request, std::function<void(const drogon::HttpResponsePtr&)>&& callback,
                const std::string& queryText);
};

}  // namespace endpoint

#endif  // SEARCHENDPOINT_H