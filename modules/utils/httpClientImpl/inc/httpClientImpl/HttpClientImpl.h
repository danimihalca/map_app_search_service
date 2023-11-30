#ifndef HTTPCLIENTIMPL_H
#define HTTPCLIENTIMPL_H

#include <drogon/HttpClient.h>

#include "httpClient/HttpClient.h"

namespace httpClientImpl
{

class HttpClientImpl : public httpClient::HttpClient
{
public:
    HttpClientImpl(const std::string& url);

public:  // Implements httpClient::HttpClient
    virtual void sendRequest(const HttpRequest& request, const HttpResponseCallback& callback) override;

private:
    drogon::HttpClientPtr m_drogonHttpClient;
};

}  // namespace httpClientImpl

#endif  // HTTPCLIENTIMPL_H