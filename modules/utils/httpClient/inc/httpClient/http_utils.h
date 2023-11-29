#ifndef HTTPUTILS_H
#define HTTPUTILS_H

#include <string>
#include <functional>

// TODO: add as needed for MVP

enum class HttpRequestType
{
    GET,
    POST,
    PUT,
    UPDATE
};

struct HttpRequest
{
    HttpRequestType type;
    std::string     path;
};

enum class HttpResponseStatus
{
    OK_200,
    NOT_FOUND_404
};

struct HttpResponse
{
    HttpResponseStatus status;
    std::string        body;
};

using HttpResponseCallback = std::function<void(const HttpResponse&)>;

#endif  // HTTPUTILS_H