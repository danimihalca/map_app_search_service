#ifndef SEARCHSERVICEPROXYIMPL_H
#define SEARCHSERVICEPROXYIMPL_H

#include "service/SearchService.h"

namespace serviceImpl
{

class SearchServiceProxyImpl : public service::SearchService
{
public:  // Implements service::SearchService
    virtual void searchPlaces(const std::string& queryText, const service::SearchResponseCallback& callback) override;
};

}  // namespace serviceImpl

#endif  // SEARCHSERVICEPROXYIMPL_H