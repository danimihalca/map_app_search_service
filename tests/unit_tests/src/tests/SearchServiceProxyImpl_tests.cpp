#include <functional>
#include <memory>
#include <string>

#include <gtest/gtest.h>

#include "httpClient/http_utils.h"
#include "serviceImpl/SearchServiceProxyImpl.h"

#include "mocks/MockPathBuilder.h"
#include "mocks/MockHttpClient.h"

bool operator==(const HttpRequest& lhs, const HttpRequest& rhs)
{
    return lhs.type == rhs.type && lhs.path == rhs.path;
}

class SearchServiceProxyImplTest : public testing::Test
{
protected:
    void SetUp() override
    {
        m_httpClient    = std::make_unique<MockHttpCLient>();
        m_httpClientPtr = m_httpClient.get();

        m_pathBuilder    = std::make_unique<MockPathBuilder>();
        m_pathBuilderPtr = m_pathBuilder.get();
    }

    void TearDown() override
    {
    }

protected:
    std::unique_ptr<MockHttpCLient> m_httpClient;
    MockHttpCLient*                 m_httpClientPtr;

    std::unique_ptr<MockPathBuilder> m_pathBuilder;
    MockPathBuilder*                 m_pathBuilderPtr;
};

TEST_F(SearchServiceProxyImplTest, basic_flow)
{
    auto service = serviceImpl::SearchServiceProxyImpl(std::move(m_httpClient), std::move(m_pathBuilder));

    testing::Expectation resetExp = EXPECT_CALL(*m_pathBuilderPtr, reset()).Times(1);

    testing::ExpectationSet pathSetupExp;

    const std::string mockPath = "<CUSTOM_PATH>";

    ON_CALL(*m_pathBuilderPtr, build()).WillByDefault(testing::Return(mockPath));

    pathSetupExp += EXPECT_CALL(*m_pathBuilderPtr, withBasePath(testing::_)).Times(1).After(resetExp);
    pathSetupExp += EXPECT_CALL(*m_pathBuilderPtr, withQuery(testing::_)).Times(1).After(resetExp);
    pathSetupExp += EXPECT_CALL(*m_pathBuilderPtr, withParameter(testing::_, testing::_)).Times(1).After(resetExp);

    EXPECT_CALL(*m_pathBuilderPtr, build()).Times(1).After(pathSetupExp);

    HttpRequest httpRequest = {HttpRequestType::GET, mockPath};

    std::function<void(const HttpResponse&)> internalServiceCallback;

    EXPECT_CALL(*m_httpClientPtr, sendRequest(httpRequest, testing::_))
        .Times(1)
        .WillOnce(testing::SaveArg<1>(&internalServiceCallback));

    testing::MockFunction<void(const std::string&)> mockCallback;
    service.searchPlaces("kfc", "23, 45", mockCallback.AsStdFunction());

    HttpResponse response = {HttpResponseStatus::OK_200, "<BODY>"};
    EXPECT_CALL(mockCallback, Call("<BODY>")).Times(1);

    internalServiceCallback(response);
}