#include "httpClientImpl/HttpClientImpl.h"
#include "httpClient/http_utils.h"

#include <iostream>

#include <emscripten/fetch.h>

namespace
{

void onRequestSuccess(emscripten_fetch_t *fetch)
{
    std::cout << "Request success for " << fetch->url << std::endl;

    emscripten_fetch_close(fetch);
}

void onRequestFail(emscripten_fetch_t *fetch)
{
    std::cout << "Request failed for " << fetch->url << std::endl;
    emscripten_fetch_close(fetch);
}


std::string httpRequestTypeToString(HttpRequestType type)
{
    switch (type)
    {
        case HttpRequestType::GET:
        {
            return "GET";
        }
        default:
        {
            std::cerr << "Unsupported HTTP request type: " << static_cast<int>(type);
            //TODO: assert somehow for debug build?
            // assert(false);
        }
    }
}
}  // namespace

namespace httpClientImpl
{

HttpClientImpl::HttpClientImpl(const std::string& url)
    : m_url{url}
{
}

void HttpClientImpl::sendRequest(const HttpRequest& request, const HttpResponseCallback& callback)
{
    auto requestTypeStr = httpRequestTypeToString(request.type);
    auto completeUrl = m_url + request.path;

    emscripten_fetch_attr_t attr;
    emscripten_fetch_attr_init(&attr);
    strcpy(attr.requestMethod, requestTypeStr.c_str());
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;
    attr.onsuccess = onRequestSuccess;
    attr.onerror = onRequestFail;
    emscripten_fetch(&attr, completeUrl.c_str());
    //TODO: forward response via input callback
}

}  // namespace httpClientImpl