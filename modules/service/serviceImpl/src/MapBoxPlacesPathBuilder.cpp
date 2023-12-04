#include <numeric>

#include "serviceImpl/MapBoxPlacesPathBuilder.h"

namespace serviceImpl
{

MapBoxPlacesPathBuilder::MapBoxPlacesPathBuilder(const std::string& accessToken)
    : m_accessToken(accessToken)
{
}

void MapBoxPlacesPathBuilder::withBasePath(const std::string& basePath)
{
    m_basePath = basePath;
}

void MapBoxPlacesPathBuilder::withQuery(const std::string& query)
{
    m_query = query;
}

void MapBoxPlacesPathBuilder::withParameter(const std::string& key, const std::string& value)
{
    m_extraParameters.insert({key, value});
}

std::string MapBoxPlacesPathBuilder::build()
{
    std::string output;

    output += m_basePath;
    output += m_query;
    output += ".json";

    if (!m_accessToken.empty() || m_extraParameters.size())
    {
        output += "?";
    }

    bool firstParameter = true;
    if (m_extraParameters.size())
    {
        output += accumulate(std::begin(m_extraParameters), std::end(m_extraParameters), std::string(),
                             [&firstParameter](std::string& acc, std::pair<std::string, std::string> pair) {
                                 if (firstParameter)
                                 {
                                     firstParameter = false;
                                     return acc + pair.first + '=' + pair.second;
                                 }
                                 return acc + '&' + pair.first + '=' + pair.second;
                             });
    }

    if (!m_accessToken.empty())
    {
        if (firstParameter)
        {
            output += "access_token=" + m_accessToken;
        }
        else
        {
            output += "&access_token=" + m_accessToken;
        }
    }

    return output;
}

void MapBoxPlacesPathBuilder::reset()
{
    m_basePath.clear();
    m_query.clear();
    m_extraParameters.clear();
}

}  // namespace serviceImpl