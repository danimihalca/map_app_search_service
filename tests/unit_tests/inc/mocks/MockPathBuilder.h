#ifndef MOCKPATHBUILDER_H
#define MOCKPATHBUILDER_H

#include <gmock/gmock.h>

#include "serviceImpl/PathBuilder.h"

class MockPathBuilder : public serviceImpl::PathBuilder
{
public:
    MOCK_METHOD(void, withBasePath, (const std::string& basePath), (override));
    MOCK_METHOD(void, withQuery, (const std::string& query), (override));
    MOCK_METHOD(void, withParameter, (const std::string& key, const std::string& value), (override));
    MOCK_METHOD(std::string, build, (), (override));
    MOCK_METHOD(void, reset, (), (override));
};

#endif  // MOCKPATHBUILDER_H