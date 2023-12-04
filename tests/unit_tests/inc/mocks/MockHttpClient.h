#ifndef MOCKHTTPCLIENT_H
#define MOCKHTTPCLIENT_H

#include <gmock/gmock.h>

#include "httpClient/HttpClient.h"

class MockHttpCLient : public httpClient::HttpClient
{
public:
    MOCK_METHOD(void, sendRequest, (const HttpRequest& request, const HttpResponseCallback& callback), (override));
};

#endif  // MOCKHTTPCLIENT_H