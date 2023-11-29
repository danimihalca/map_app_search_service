#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include "httpClient/http_utils.h"

namespace httpClient
{

class HttpClient
{
public:
    virtual ~HttpClient() = default;

    /**
     * @brief Sends a HTTP request
     *
     * @param request - Request structure.
     * @param callback - Response callback.
     */
    virtual void sendRequest(const HttpRequest& request, const HttpResponseCallback& callback) = 0;
};

}  // namespace httpClient

#endif  // HTTPCLIENT_H