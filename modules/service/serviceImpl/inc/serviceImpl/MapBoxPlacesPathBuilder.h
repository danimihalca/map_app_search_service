#ifndef MAPBOXPLACESPATHBUILDER_H
#define MAPBOXPLACESPATHBUILDER_H

#include <string>
#include <map>

#include "serviceImpl/PathBuilder.h"

namespace serviceImpl
{

class MapBoxPlacesPathBuilder : public PathBuilder
{
public:
    MapBoxPlacesPathBuilder(const std::string& accessToken);

    virtual void        withBasePath(const std::string& basePath) override;
    virtual void        withQuery(const std::string& query) override;
    virtual void        withParameter(const std::string& key, const std::string& value) override;
    virtual std::string build() override;
    virtual void        reset() override;

private:
    std::string                        m_basePath;
    std::string                        m_query;
    std::map<std::string, std::string> m_extraParameters;
    std::string                        m_accessToken;
};
}  // namespace serviceImpl

#endif  // MAPBOXPLACESPATHBUILDER_H