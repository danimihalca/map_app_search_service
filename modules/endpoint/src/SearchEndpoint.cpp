#include "endpoint/SearchEndpoint.h"
#include <drogon/HttpResponse.h>

namespace endpoint
{

void SearchEndpoint::places(const drogon::HttpRequestPtr&                         request,
                            std::function<void(const drogon::HttpResponsePtr&)>&& callback,
                            const std::string&                                    queryText)
{
    auto response = drogon::HttpResponse::newHttpResponse();

    callback(response);
}

}  // namespace endpoint