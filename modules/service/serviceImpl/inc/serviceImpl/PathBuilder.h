#ifndef PATHBUILDER_H
#define PATHBUILDER_H

#include <string>

namespace serviceImpl
{
class PathBuilder
{
public:
    virtual ~PathBuilder() = default;

    virtual void        withBasePath(const std::string& basePath)                       = 0;
    virtual void        withQuery(const std::string& query)                             = 0;
    virtual void        withParameter(const std::string& key, const std::string& value) = 0;
    virtual std::string build()                                                         = 0;
    virtual void        reset()                                                         = 0;
};

}  // namespace serviceImpl

#endif  // PATHBUILDER_H
