#include "httpClientImpl/HttpClientImpl.h"
#include "httpClient/http_utils.h"
#include <drogon/HttpClient.h>
#include <drogon/HttpRequest.h>
#include <drogon/HttpResponse.h>
#include <drogon/HttpTypes.h>
#include <iostream>

namespace
{
drogon::HttpMethod httpRequestTypeToDrogonMethod(HttpRequestType type)
{
    switch (type)
    {
        case HttpRequestType::GET:
        {
            return drogon::HttpMethod::Get;
        }
        default:
        {
            std::cerr << "Unsupported HTTP request type: " << static_cast<int>(type);
            assert(false);
        }
    }
}
}  // namespace

HttpResponseStatus drogonReqResultToHttpResponseStatus(drogon::ReqResult statusCode)
{
    switch (statusCode)
    {
        case drogon::ReqResult::Ok:
        {
            return HttpResponseStatus::OK_200;
        }

        case drogon::ReqResult::BadResponse:
        {
            return HttpResponseStatus::NOT_FOUND_404;
        }

        default:
        {
            std::cerr << "Unsupported HTTP status code: " << drogon::to_string_view(statusCode);
            assert(false);
        }
    }
}

namespace httpClientImpl
{

HttpClientImpl::HttpClientImpl(const std::string& url)
    : m_drogonHttpClient(drogon::HttpClient::newHttpClient(url))
{
}

void HttpClientImpl::sendRequest(const HttpRequest& request, const HttpResponseCallback& callback)
{
    auto drogonRequest = drogon::HttpRequest::newHttpRequest();
    drogonRequest->setPath(request.path);
    drogonRequest->setMethod(::httpRequestTypeToDrogonMethod(request.type));

    m_drogonHttpClient->sendRequest(drogonRequest, [callback](drogon::ReqResult result, drogon::HttpResponsePtr resp) {
        HttpResponse response;

        response.status = ::drogonReqResultToHttpResponseStatus(result);
        response.body   = resp->getBody();

        callback(response);
    });
}

}  // namespace httpClientImpl