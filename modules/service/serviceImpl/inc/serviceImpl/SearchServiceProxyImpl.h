#ifndef SEARCHSERVICEPROXYIMPL_H
#define SEARCHSERVICEPROXYIMPL_H

#include <memory>

#include "service/SearchService.h"

namespace httpClient
{
class HttpClient;
}

namespace serviceImpl
{
class PathBuilder;

class SearchServiceProxyImpl : public service::SearchService
{
public:
    SearchServiceProxyImpl(std::unique_ptr<httpClient::HttpClient>&& client,
                           std::unique_ptr<PathBuilder>&&            pathBuilder);

public:  // Implements service::SearchService
    virtual void searchPlaces(const std::string& queryText, const std::string& proximity, const service::SearchResponseCallback& callback) override;

private:
    std::unique_ptr<httpClient::HttpClient> m_client;
    std::unique_ptr<PathBuilder>            m_pathBuilder;
};

}  // namespace serviceImpl

#endif  // SEARCHSERVICEPROXYIMPL_H