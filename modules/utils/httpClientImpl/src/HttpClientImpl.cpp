#include "httpClientImpl/HttpClientImpl.h"
#include "httpClient/http_utils.h"

#include <iostream>

#include <emscripten/fetch.h>

namespace
{

void onRequestSuccess(emscripten_fetch_t *fetch)
{
    std::cout << "0Request success for " << fetch->url << std::endl;

    auto callback = *(const HttpResponseCallback *)fetch->userData;

    auto response = HttpResponse{HttpResponseStatus::OK_200, fetch->data};
    callback(response);

    emscripten_fetch_close(fetch);

}

void onRequestFail(emscripten_fetch_t *fetch)
{
    std::cout << "0Request failed for " << fetch->url << std::endl;

    auto callback = *(const HttpResponseCallback *)fetch->userData;

    //TODO: proper status conversion
    auto response = HttpResponse{HttpResponseStatus::OK_200, fetch->data};
    callback(response);

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
    attr.attributes = EMSCRIPTEN_FETCH_LOAD_TO_MEMORY | EMSCRIPTEN_FETCH_WAITABLE;
    attr.onsuccess = onRequestSuccess;
    attr.onerror = onRequestFail;
    attr.userData = (void*) &callback;
    emscripten_fetch_t * fetch = emscripten_fetch(&attr, completeUrl.c_str());

    // emscripten_fetch_wait(fetch, INFINITY);
    emscripten_sleep(100);
    std::cout << "After sleep send request" << std::endl;


//     EMSCRIPTEN_RESULT ret = EMSCRIPTEN_RESULT_TIMED_OUT;
//     while(ret == EMSCRIPTEN_RESULT_TIMED_OUT)
//     {
//         emscripten_sleep(0);
//         ret = emscripten_fetch_wait(fetch, 0);
//     }

//     if (fetch->status == 200)
//     {
//         std::cout << "Request success for " << fetch->url << std::endl;
//     }
//     else
//     {
//         std::cout << "Request failed for " <<fetch->status << " " << fetch->url << std::endl;
//     }

//     //TODO: proper status conversion
//     auto response = HttpResponse{HttpResponseStatus::OK_200, fetch->data};

//     emscripten_fetch_close(fetch);

//     callback(response);
}

}  // namespace httpClientImpl