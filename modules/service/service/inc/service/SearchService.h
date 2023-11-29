#ifndef SEARCHSERVICE_H
#define SEARCHSERVICE_H

#include <functional>
#include <string>

namespace service
{
using SearchResponseCallback = std::function<void(const std::string&)>;

class SearchService
{
public:
    virtual ~SearchService() = default;

    virtual void searchPlaces(const std::string& queryText, const SearchResponseCallback& callback) = 0;
};

}  // namespace service

#endif  // SEARCHSERVICE_H