#include "serviceImpl/SearchServiceProxyImpl.h"
#include "serviceImpl/PathBuilder.h"

#include "httpClient/HttpClient.h"
#include "httpClient/http_utils.h"

#include <algorithm>
#include <memory>

namespace serviceImpl
{

SearchServiceProxyImpl::SearchServiceProxyImpl(std::unique_ptr<httpClient::HttpClient>&& client,
                                               std::unique_ptr<PathBuilder>&&            pathBuilder)
    : m_client(std::move(client))
    , m_pathBuilder(std::move(pathBuilder))
{
}

void SearchServiceProxyImpl::searchPlaces(const std::string& queryText, const std::string& proximity,
                                          const service::SearchResponseCallback& callback)
{
    HttpRequest request;

    m_pathBuilder->reset();

    m_pathBuilder->withBasePath("/geocoding/v5/mapbox.places/");
    m_pathBuilder->withQuery(queryText);
    // m_pathBuilder->withParameter("limit", "2");
    m_pathBuilder->withParameter("proximity", proximity);

    request.path = m_pathBuilder->build();
    request.type = HttpRequestType::GET;

    m_client->sendRequest(request, [callback](const HttpResponse& response) { callback(response.body); });
}

}  // namespace serviceImpl